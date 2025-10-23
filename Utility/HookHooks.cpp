// IMPORTANT:
// 1) Compile *your app code* with /Gh /GH
// 2) EXCLUDE *this file* from /Gh /GH so the hooks don't instrument themselves.

#include "HookHooks.h"
#include <windows.h>
#include <dbghelp.h>
#include <string>
#include <mutex>
#include <atomic>
#include <vector>
#include <cstdio>
#include <climits>

// Link with DbgHelp
#pragma comment(lib, "Dbghelp.lib")

// ------------------------------------------------------------------
// Config (override via preprocessor or env):
// ------------------------------------------------------------------
#ifndef HH_LOG_PATH
#  define HH_LOG_PATH "trace.log"
#endif
#ifndef HH_LOG_FILELINE
#  define HH_LOG_FILELINE 1      // 1=try to print file:line
#endif

// ------------------------------------------------------------------
// Globals
// ------------------------------------------------------------------
static HANDLE g_logFile = INVALID_HANDLE_VALUE;
static std::mutex g_dbghelpMutex;              // DbgHelp is NOT thread-safe
static std::atomic<bool> g_symInit{false};
static DWORD g_pid = 0;

// Per-thread call depth for pretty indent; and re-entrancy guard
static __declspec(thread) int  t_depth = 0;
static __declspec(thread) bool t_inHook = false;

// -------- Per-thread gating (region control) --------
struct TraceGate {
    int baseDepth;         // depth at HH_BeginTrace time (children start at relDepth 0)
    int maxRelDepth;       // inclusive cap for relative depth
};
static __declspec(thread) std::vector<TraceGate> t_gateStack; // small, grows only on BeginTrace

// ------------------------------------------------------------------
// Utilities
// ------------------------------------------------------------------
static void OpenLogOnce()
{
    static std::once_flag once;
    std::call_once(once, [] {
        // Path: env HH_LOG_PATH wins, else default
        char path[MAX_PATH];
        DWORD n = GetEnvironmentVariableA("HH_LOG_PATH", path, MAX_PATH);
        const char* use = (n && n < MAX_PATH) ? path : HH_LOG_PATH;

        // Mode: overwrite each run (truncate). If you ever want append, add an env like HH_LOG_MODE.
        g_logFile = CreateFileA(
            use,
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            CREATE_ALWAYS,                 // truncates any existing file
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

        g_pid = GetCurrentProcessId();
    });
}

static void WriteRaw(const char* s, size_t len)
{
    if (g_logFile == INVALID_HANDLE_VALUE) return;
    DWORD bw = 0;
    WriteFile(g_logFile, s, (DWORD)len, &bw, nullptr);
}

static void InitSymbolsOnce()
{
    if (g_symInit.load(std::memory_order_acquire)) return;

    std::scoped_lock lk(g_dbghelpMutex);
    if (g_symInit.load(std::memory_order_relaxed)) return;

    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS);
    (void)SymInitialize(GetCurrentProcess(), nullptr, TRUE);
    g_symInit.store(true, std::memory_order_release);
}

struct Resolved
{
    std::string module;
    std::string decorated;
    std::string signature;   // undecorated, UNDNAME_COMPLETE when possible
    DWORD64     displacement = 0;
#if HH_LOG_FILELINE
    std::string file;
    DWORD       line = 0;
#endif
};

// Best effort demangle + module name + line
static Resolved ResolveAddr(DWORD_PTR ip /* an address inside the current function */)
{
    Resolved r;

    // serialize all DbgHelp calls
    std::scoped_lock lk(g_dbghelpMutex);

    // 1) symbol
    constexpr DWORD kMaxName = 2048;
    char symbuf[sizeof(SYMBOL_INFO) + kMaxName];
    auto* si = reinterpret_cast<PSYMBOL_INFO>(symbuf);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = kMaxName;

    if (SymFromAddr(GetCurrentProcess(), (DWORD64)ip, &r.displacement, si)) {
        r.decorated.assign(si->Name, si->NameLen);

        // undecorate to full signature if possible
        char undec[kMaxName];
        if (UnDecorateSymbolName(si->Name, undec, kMaxName, UNDNAME_COMPLETE)) {
            r.signature = undec;
        } else {
            r.signature = r.decorated; // fallback
        }
    } else {
        char tmp[64];
        sprintf_s(tmp, "0x%p", (void*)ip);
        r.decorated = tmp;
        r.signature = tmp;
    }

    // 2) module
    IMAGEHLP_MODULE64 mi{};
    mi.SizeOfStruct = sizeof(mi);
    if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)ip, &mi) && mi.ImageName) {
        // shorten to just file name
        const char* base = mi.ImageName;
        for (const char* p = mi.ImageName; *p; ++p) {
            if (*p == '\\' || *p == '/') base = p + 1;
        }
        r.module = base;
    }

#if HH_LOG_FILELINE
    // 3) file:line (optional)
    IMAGEHLP_LINE64 line{};
    line.SizeOfStruct = sizeof(line);
    DWORD dwDis = 0;
    if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)ip, &dwDis, &line)) {
        if (line.FileName) {
            const char* base = line.FileName;
            for (const char* p = line.FileName; *p; ++p) {
                if (*p == '\\' || *p == '/') base = p + 1;
            }
            r.file = base;
            r.line = line.LineNumber;
        }
    }
#endif
    return r;
}

// Decide whether we should log the current entry, given TLS state.
// NOTE: We always update t_depth in LogEnter/LogExit so the gating math works,
// but we only emit when at least one gate is active and the relative depth fits.
static bool ShouldLogThisEntry(/* current absolute depth before increment */ int currentDepth)
{
    if (t_gateStack.empty()) return false;
    const TraceGate& gate = t_gateStack.back();
    const int rel = currentDepth - gate.baseDepth; // first child => rel = 0
    return (rel >= 0) && (rel <= gate.maxRelDepth);
}

// Emit one nicely formatted line
static void LogEnterInternal(DWORD_PTR ipInsideFunction)
{
    OpenLogOnce();
    InitSymbolsOnce();

    char buf[4096];
    char* out = buf;
    char* end = buf + sizeof(buf);

    // indent for pretty tree
    for (int i = 0; i < t_depth && out + 2 < end; ++i) { *out++ = ' '; *out++ = ' '; }

    // [pid:tid]
    const DWORD tid = GetCurrentThreadId();
    int n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "[%lu:%lu] ", (unsigned long)g_pid, (unsigned long)tid);
    out += (n > 0 ? n : 0);

    // Resolve
    Resolved R = ResolveAddr(ipInsideFunction);

    // module!ShortName+disp — FullSignature
    if (!R.module.empty()) {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "%s!", R.module.c_str());
        out += (n > 0 ? n : 0);
    }

    // Try to get a short "Class::Func" for the left side
    char shortName[2048];
    if (!R.decorated.empty() &&
        UnDecorateSymbolName(R.decorated.c_str(), shortName, (DWORD)sizeof(shortName), UNDNAME_NAME_ONLY)) {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "%s", shortName);
        out += (n > 0 ? n : 0);
    } else {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "%s", R.decorated.c_str());
        out += (n > 0 ? n : 0);
    }

    if (R.displacement) {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "+0x%llx", (unsigned long long)R.displacement);
        out += (n > 0 ? n : 0);
    }

    if (!R.signature.empty()) {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, " — %s", R.signature.c_str());
        out += (n > 0 ? n : 0);
    }

#if HH_LOG_FILELINE
    if (!R.file.empty()) {
        n = _snprintf_s(out, (size_t)(end - out), _TRUNCATE, "  @ %s:%lu", R.file.c_str(), (unsigned long)R.line);
        out += (n > 0 ? n : 0);
    }
#endif

    if (out + 1 < end) { *out++ = '\n'; }

    WriteRaw(buf, (size_t)(out - buf));
}

static void LogEnter(DWORD_PTR ipInsideFunction)
{
    // prevent recursion if logging calls trigger instrumentation paths
    if (t_inHook) { ++t_depth; return; }
    t_inHook = true;

    // Only emit when a gate is active *and* the relative depth fits
    if (ShouldLogThisEntry(/* currentDepth */ t_depth)) {
        LogEnterInternal(ipInsideFunction);
    }

    // We increment absolute depth after deciding whether to print *this* frame.
    // Children will see a greater t_depth, which matches our gating math.
    ++t_depth;

    t_inHook = false;
}

static void LogExit()
{
    if (t_depth > 0) --t_depth;
}

// ------------------------------------------------------------------
// Naked hooks (stack math notes below)
// ------------------------------------------------------------------
extern "C" __declspec(naked) void __cdecl _penter()
{
    __asm {
        // Save regs & flags. pushad pushes: eax, ecx, edx, ebx, esp, ebp, esi, edi  (32 bytes)
        pushad
        pushfd                                         // +4  => total saved = 36 bytes

        // The original return address (to instruction after call _penter)
        // sits at [esp + 36]. That's an address *inside the instrumented function*,
        // suitable for SymFromAddr().
        mov   eax, [esp + 36]                          // eax = ip-inside-function
        push  eax

        call  LogEnter

        add   esp, 4                                   // pop param
        popfd
        popad
        ret
    }
}

extern "C" __declspec(naked) void __cdecl _pexit()
{
    __asm {
        call LogExit
        ret
    }
}

// ------------------------------------------------------------------
// Public gating API
// ------------------------------------------------------------------
extern "C" void __cdecl HH_BeginTrace(int maxRelativeDepth)
{
    if (maxRelativeDepth <= 0) maxRelativeDepth = 0; // only direct children if <=0 passed
    // Push a new gate with current absolute depth as the base
    t_gateStack.push_back(TraceGate{ t_depth, maxRelativeDepth });
}

extern "C" void __cdecl HH_EndTrace()
{
    if (!t_gateStack.empty())
        t_gateStack.pop_back();
}
