// ---------------------------------------------------------
// UnifiedHookHooks.cpp
// See header for supported modes.
// Build hints are at the bottom.
// ---------------------------------------------------------

#include "HookHooks.h"

#include <atomic>
#include <mutex>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <cstddef>

// ------------------------------------------------------------------
// Common state (OS-agnostic): TLS depth/gates, re-entrancy guard
// ------------------------------------------------------------------
struct HH_TraceGate { int baseDepth; int maxRelDepth; };

static thread_local int  hh_t_depth   = 0;
static thread_local bool hh_t_inHook  = false;
static thread_local std::vector<HH_TraceGate> hh_t_gates;

// forward decls for platform bits
static HH_ATTR_NOINSTR void hh_LogEnterPlatform(void* fnAddr);
static HH_ATTR_NOINSTR void hh_LogExitPlatform();

// Should we emit this entry?
static HH_ATTR_NOINSTR bool hh_ShouldLog(int currentDepth)
{
    if (hh_t_gates.empty()) return false;
    const HH_TraceGate& g = hh_t_gates.back();
    const int rel = currentDepth - g.baseDepth;     // first child -> 0
    return (rel >= 0) && (rel <= g.maxRelDepth);
}

// Shared top-level enter/exit (called by platform hook shims)
static HH_ATTR_NOINSTR void hh_LogEnter(void* fnAddr)
{
    if (hh_t_inHook) { ++hh_t_depth; return; } // avoid recursion loops
    hh_t_inHook = true;

    if (hh_ShouldLog(hh_t_depth)) {
        hh_LogEnterPlatform(fnAddr);  // does the real work + writes a line
    }

    ++hh_t_depth;   // children indent deeper
    hh_t_inHook = false;
}
static HH_ATTR_NOINSTR void hh_LogExit()
{
    if (hh_t_depth > 0) --hh_t_depth;
}

// Public gating API
HH_EXTERN_C_BEGIN
HH_DECL(void) HH_BeginTrace(int maxRelativeDepth) HH_NOEXCEPT
{
    if (maxRelativeDepth < 0) maxRelativeDepth = 0;
    hh_t_gates.push_back(HH_TraceGate{ hh_t_depth, maxRelativeDepth });
}
HH_DECL(void) HH_EndTrace(void) HH_NOEXCEPT
{
    if (!hh_t_gates.empty()) hh_t_gates.pop_back();
}
HH_EXTERN_C_END

// ==================================================================
//            Platform-specific backends start here
// ==================================================================

#if HH_OS_WINDOWS
// =========================== WINDOWS ==============================
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

#ifndef HH_LOG_PATH
#  define HH_LOG_PATH "trace.log"
#endif
#ifndef HH_LOG_FILELINE
#  define HH_LOG_FILELINE 1     // try to append file:line when PDBs present
#endif

// File sink + DbgHelp serialisation
static HH_ATTR_NOINSTR HANDLE hh_log = INVALID_HANDLE_VALUE;
static std::once_flag        hh_openOnce;
static std::mutex            hh_dbghelpMtx;
static std::atomic<bool>     hh_symInit{false};
static DWORD                 hh_pid = 0;

static HH_ATTR_NOINSTR void hh_OpenLogOnce()
{
    std::call_once(hh_openOnce, [] {
        char path[MAX_PATH]{};
        DWORD n = GetEnvironmentVariableA("HH_LOG_PATH", path, MAX_PATH);
        const char* use = (n && n < MAX_PATH) ? path : HH_LOG_PATH;

        hh_log = CreateFileA(use, GENERIC_WRITE,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             nullptr, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, nullptr);
        hh_pid = GetCurrentProcessId();
    });
}
static HH_ATTR_NOINSTR void hh_WriteRaw(const char* s, size_t len)
{
    if (hh_log == INVALID_HANDLE_VALUE) return;
    DWORD bw=0; WriteFile(hh_log, s, (DWORD)len, &bw, nullptr);
}
static HH_ATTR_NOINSTR void hh_InitDbgHelpOnce()
{
    if (hh_symInit.load(std::memory_order_acquire)) return;
    std::scoped_lock lk(hh_dbghelpMtx);
    if (hh_symInit.load(std::memory_order_relaxed)) return;
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS);
    (void)SymInitialize(GetCurrentProcess(), nullptr, TRUE);
    hh_symInit.store(true, std::memory_order_release);
}

struct HH_ResolvedW {
    std::string module, decorated, signature;
    DWORD64 disp = 0;
#if HH_LOG_FILELINE
    std::string file; DWORD line = 0;
#endif
};
static HH_ATTR_NOINSTR HH_ResolvedW hh_ResolveW(void* fn)
{
    HH_ResolvedW R;
    std::scoped_lock lk(hh_dbghelpMtx);

    constexpr DWORD MAXN = 2048;
    char symbuf[sizeof(SYMBOL_INFO) + MAXN];
    auto* si = reinterpret_cast<PSYMBOL_INFO>(symbuf);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen   = MAXN;

    DWORD64 disp=0;
    if (SymFromAddr(GetCurrentProcess(), (DWORD64)fn, &disp, si)) {
        R.decorated.assign(si->Name, si->NameLen);
        R.disp = disp;
        char undec[MAXN];
        if (UnDecorateSymbolName(si->Name, undec, MAXN, UNDNAME_COMPLETE))
            R.signature = undec;
        else
            R.signature = R.decorated;
    } else {
        char tmp[32]; _snprintf_s(tmp, sizeof tmp, _TRUNCATE, "0x%p", fn);
        R.decorated = tmp; R.signature = tmp;
    }

    IMAGEHLP_MODULE64 mi{}; mi.SizeOfStruct = sizeof mi;
    if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)fn, &mi) && mi.ImageName) {
        const char* base = mi.ImageName;
        for (const char* p=mi.ImageName; *p; ++p) if (*p=='\\' || *p=='/') base = p+1;
        R.module = base;
    }

#if HH_LOG_FILELINE
    IMAGEHLP_LINE64 ln{}; ln.SizeOfStruct = sizeof ln; DWORD d=0;
    if (SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)fn, &d, &ln) && ln.FileName) {
        const char* base = ln.FileName;
        for (const char* p=ln.FileName; *p; ++p) if (*p=='\\' || *p=='/') base = p+1;
        R.file = base; R.line = ln.LineNumber;
    }
#endif
    return R;
}

static HH_ATTR_NOINSTR void hh_LogEnterPlatform(void* fnAddr)
{
    hh_OpenLogOnce();
    hh_InitDbgHelpOnce();

    char buf[4096]; char* out=buf; char* end=buf+sizeof buf;

    // indent
    for (int i=0;i<hh_t_depth && out+2<end;++i){*out++=' ';*out++=' ';}

    // [pid:tid]
    DWORD tid = GetCurrentThreadId();
    int n = _snprintf_s(out, end-out, _TRUNCATE, "[%lu:%lu] ",
                        (unsigned long)hh_pid, (unsigned long)tid);
    out += (n>0?n:0);

    HH_ResolvedW R = hh_ResolveW(fnAddr);

    if (!R.module.empty()) {
        n = _snprintf_s(out, end-out, _TRUNCATE, "%s!", R.module.c_str());
        out += (n>0?n:0);
    }

    // short name
    char shortN[2048];
    if (!R.decorated.empty() &&
        UnDecorateSymbolName(R.decorated.c_str(), shortN, (DWORD)sizeof shortN, UNDNAME_NAME_ONLY))
        n = _snprintf_s(out, end-out, _TRUNCATE, "%s", shortN);
    else
        n = _snprintf_s(out, end-out, _TRUNCATE, "%s", R.decorated.c_str());
    out += (n>0?n:0);

    if (R.disp) {
        n = _snprintf_s(out, end-out, _TRUNCATE, "+0x%llx", (unsigned long long)R.disp);
        out += (n>0?n:0);
    }

    if (!R.signature.empty()) {
        n = _snprintf_s(out, end-out, _TRUNCATE, " — %s", R.signature.c_str());
        out += (n>0?n:0);
    }

#if HH_LOG_FILELINE
    if (!R.file.empty()) {
        n = _snprintf_s(out, end-out, _TRUNCATE, "  @ %s:%lu",
                        R.file.c_str(), (unsigned long)R.line);
        out += (n>0?n:0);
    }
#endif

    if (out+1<end) *out++='\n';
    hh_WriteRaw(buf, (size_t)(out-buf));
}
static HH_ATTR_NOINSTR void hh_LogExitPlatform(){ /* nothing extra */ }

// ----- Windows instrumentation entry points -----
// Windows x64 clang-cl OR Linux-like path on Windows (clang-cl):
#if (HH_OS_WINDOWS) && defined(__clang__)
HH_EXTERN_C_BEGIN
HH_DECL(void) __cyg_profile_func_enter(void* this_fn, void* /*call_site*/) HH_NOEXCEPT
{ hh_LogEnter(this_fn); }
HH_DECL(void) __cyg_profile_func_exit (void* /*this_fn*/, void* /*call_site*/) HH_NOEXCEPT
{ hh_LogExit(); }
HH_EXTERN_C_END
#endif

// Windows x86 MSVC: /Gh /GH
#if (HH_OS_WINDOWS) && defined(_MSC_VER) && !defined(__clang__) && defined(_M_IX86)
HH_EXTERN_C_BEGIN
__declspec(naked) void __cdecl _penter()
{
    __asm {
        pushad
        pushfd
        // ip-inside-function at [esp+36]
        mov   eax, [esp + 36]
        push  eax
        call  hh_LogEnter
        add   esp, 4
        popfd
        popad
        ret
    }
}
__declspec(naked) void __cdecl _pexit()
{
    __asm { call hh_LogExit ; ret }
}
HH_EXTERN_C_END
#endif

#else // =========================== LINUX ==============================

#include <dlfcn.h>
#include <cxxabi.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#ifndef HH_LOG_PATH
#  define HH_LOG_PATH "trace.log"
#endif
#ifndef HH_LOG_FILELINE
#  define HH_LOG_FILELINE 1
#endif
#ifndef HH_USE_LIBBACKTRACE
#  define HH_USE_LIBBACKTRACE 0
#endif

#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
  #include <backtrace.h>
  static backtrace_state* hh_btState = nullptr;
  static std::atomic<bool> hh_btInited{false};
  static HH_ATTR_NOINSTR void hh_btErr(void*, const char* m, int){ if(m) ::write(2,m,strlen(m)); }
#endif

static int              hh_fd = -1;
static std::once_flag   hh_openOnce;
static std::mutex       hh_symMtx;

static HH_ATTR_NOINSTR void hh_OpenLogOnce()
{
    std::call_once(hh_openOnce, []{
        const char* path = ::getenv("HH_LOG_PATH");
        if (!path || !*path) path = HH_LOG_PATH;
        hh_fd = ::open(path, O_CREAT|O_TRUNC|O_WRONLY, 0644);
        if (hh_fd < 0) hh_fd = 2; // stderr fallback
#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
        hh_btState = backtrace_create_state(nullptr, 1, hh_btErr, nullptr);
        hh_btInited.store(true, std::memory_order_release);
#endif
    });
}
static HH_ATTR_NOINSTR void hh_WriteRaw(const char* s, size_t n){ if (hh_fd>=0) (void)::write(hh_fd, s, n); }

static HH_ATTR_NOINSTR std::string hh_Base(const char* p){
    if(!p) return {};
    const char* b=p; for (const char* q=p; *q; ++q) if (*q=='/') b=q+1;
    return std::string(b);
}

struct HH_ResolvedL {
    std::string module, shortName, signature;
    uintptr_t disp = 0;
#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
    std::string file; unsigned line = 0;
#endif
};

#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
struct HH_PcInfo { std::string file; unsigned line=0; std::string func; };
static HH_ATTR_NOINSTR int hh_btPc(void* data, uintptr_t, const char* f, int ln, const char* fn)
{
    auto* o = static_cast<HH_PcInfo*>(data);
    if (f)  o->file = f;
    if (ln) o->line = (unsigned)ln;
    if (fn) o->func = fn;
    return 0;
}
static HH_ATTR_NOINSTR void hh_ResolveFileLine(void* pc, std::string& file, unsigned& line)
{
    if (!hh_btInited.load(std::memory_order_acquire) || !hh_btState) return;
    HH_PcInfo info;
    backtrace_pcinfo(hh_btState, (uintptr_t)pc, hh_btPc, hh_btErr, &info);
    if (!info.file.empty()) { file = hh_Base(info.file.c_str()); line = info.line; }
}
#endif

static HH_ATTR_NOINSTR HH_ResolvedL hh_ResolveL(void* fn)
{
    HH_ResolvedL R;
    std::scoped_lock lk(hh_symMtx);

    Dl_info di{};
    if (dladdr(fn, &di) && di.dli_sname) {
        int st=0;
        char* dem = abi::__cxa_demangle(di.dli_sname, nullptr, nullptr, &st);
        if (st==0 && dem) { R.shortName = dem; std::free(dem); }
        else              { R.shortName = di.dli_sname; }
        R.signature = R.shortName; // best effort on ELF
        R.module = hh_Base(di.dli_fname);
        if (di.dli_saddr) R.disp = (uintptr_t)fn - (uintptr_t)di.dli_saddr;
    } else {
        char tmp[32]; std::snprintf(tmp,sizeof tmp,"0x%p",fn);
        R.shortName = tmp; R.signature = tmp;
    }

#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
    hh_ResolveFileLine(fn, R.file, R.line);
#endif
    return R;
}

static HH_ATTR_NOINSTR void hh_LogEnterPlatform(void* fnAddr)
{
    hh_OpenLogOnce();

    char buf[4096]; char* out=buf; char* end=buf+sizeof buf;

    for (int i=0;i<hh_t_depth && out+2<end;++i){*out++=' ';*out++=' ';}

    pid_t pid = getpid();
    unsigned long tid = (unsigned long)pthread_self();
    int n = std::snprintf(out, end-out, "[%ld:%lu] ", (long)pid, tid);
    out += (n>0?n:0);

    HH_ResolvedL R = hh_ResolveL(fnAddr);

    if (!R.module.empty()) {
        n = std::snprintf(out, end-out, "%s!", R.module.c_str());
        out += (n>0?n:0);
    }

    n = std::snprintf(out, end-out, "%s", R.shortName.c_str());
    out += (n>0?n:0);

    if (R.disp) {
        n = std::snprintf(out, end-out, "+0x%zx", (size_t)R.disp);
        out += (n>0?n:0);
    }

    if (!R.signature.empty()) {
        n = std::snprintf(out, end-out, " — %s", R.signature.c_str());
        out += (n>0?n:0);
    }

#if HH_LOG_FILELINE && HH_USE_LIBBACKTRACE
    if (!R.file.empty()) {
        n = std::snprintf(out, end-out, "  @ %s:%u", R.file.c_str(), R.line);
        out += (n>0?n:0);
    }
#endif

    if (out+1<end) *out++='\n';
    hh_WriteRaw(buf, (size_t)(out-buf));
}
static HH_ATTR_NOINSTR void hh_LogExitPlatform(){ /* nothing extra */ }

// Linux/Clang/GCC entry points
HH_EXTERN_C_BEGIN
HH_DECL(void) __cyg_profile_func_enter(void* this_fn, void* /*call_site*/) HH_NOEXCEPT
{ hh_LogEnter(this_fn); }
HH_DECL(void) __cyg_profile_func_exit (void* /*this_fn*/, void* /*call_site*/) HH_NOEXCEPT
{ hh_LogExit(); }
HH_EXTERN_C_END

#endif // OS switch

// ==================================================================
//                         Build quick reference
// ==================================================================
//
// Linux (GCC/Clang):
//   g++ -std=c++17 -g -O2 -finstrument-functions \
//       UnifiedHookHooks.cpp your_sources.cpp \
//       -ldl -pthread \
//       -o your_app
//   # optional file:line (needs libbacktrace):
//   g++ ... -DHH_USE_LIBBACKTRACE=1 -lbacktrace ...
//
// Windows x64 (clang-cl toolset in VS):
//   Project -> C/C++ -> Command Line -> Additional Options:
//      /clang:-finstrument-functions
//   (Add UnifiedHookHooks.* to the project; link DbgHelp.lib)
//
// Windows x86 (MSVC cl.exe, NOT clang):
//   Enable /Gh /GH for *your* code (the TUs you want traced).
//   EXCLUDE UnifiedHookHooks.cpp from /Gh /GH.
//   Link DbgHelp.lib.
//
// Runtime:
//   - By default writes to "trace.log"; override with env var HH_LOG_PATH
//   - Call HH_BeginTrace(INT_MAX) / HH_EndTrace() to scope capture.
//   - Only functions compiled with the instrumentation flag are recorded.
//   - Inlining removes functions from traces; mark hot ones noinline if needed.
