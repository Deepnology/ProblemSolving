#ifndef _PRINT_CALL_STACK_H_
#define _PRINT_CALL_STACK_H_

#ifdef __cplusplus
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>   // strrchr

namespace DbgPltfUtls {

    // Shared helper: basename only
    inline const char* basename_only(const char* fullPath) {
        if (!fullPath || !*fullPath) return "";
        const char* bslash = std::strrchr(fullPath, '\\');
        const char* fslash = std::strrchr(fullPath, '/');
        const char* p = (bslash > fslash ? bslash : fslash);
        return p ? (p + 1) : fullPath;
    }

} // namespace DbgPltfUtls


#if defined(_WIN32)

#include "CommWintUtl.h"
#include <sdkddkver.h>

#if NTDDI_VERSION <= NTDDI_WINXP
#pragma comment(lib, "ntdll.lib")
    extern "C" __declspec(dllimport) USHORT WINAPI RtlCaptureStackBackTrace(
        ULONG  FramesToSkip,
        ULONG  FramesToCapture,
        PVOID * BackTrace,
        PULONG BackTraceHash
    );

    // make the documented name map to it
#define CaptureStackBackTrace RtlCaptureStackBackTrace
#endif

namespace DbgPltfUtls {

    inline bool EnsureSymbolsInitialized()
    {
        static bool done = false;
        if (!done)
        {
            SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
            done = SymInitialize(GetCurrentProcess(), nullptr, TRUE) != FALSE;
        }
        return done;
    }

    inline const char* FilenameOnly(const char* fullPath)
    {
        const char* p1 = strrchr(fullPath, '\\');
        const char* p2 = strrchr(fullPath, '/');
        const char* p = (p1 > p2 ? p1 : p2);
        return p ? p + 1 : fullPath;
    }

    inline ::std::string GetPrintCallStack(::std::vector<::std::vector<::std::string>>& outStk, unsigned int skip = 0, unsigned int maxFrames = 10)
    {
        if (!EnsureSymbolsInitialized()) return {};

        void* stack[64];
        USHORT frames = CaptureStackBackTrace(skip + 1, ::std::min<USHORT>(maxFrames, 64), stack, nullptr);

        const size_t bufSize = sizeof(SYMBOL_INFO) + 256 * sizeof(char);
        SYMBOL_INFO* sym = (SYMBOL_INFO*)::std::calloc(1, bufSize);
        if (!sym) return {};

        sym->MaxNameLen = 255;
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);

        ::std::ostringstream oss;
        for (USHORT i = 0; i < frames; ++i)
        {
            DWORD64 displacement = 0;
            DWORD64 addr64 = reinterpret_cast<DWORD64>(stack[i]);

            oss << "  " << i << ": ";

            ::std::vector<::std::string> cur(3, ::std::string());
            // Module name
            if (DWORD64 base = SymGetModuleBase64(GetCurrentProcess(), addr64))
            {
                CHAR modName[MAX_PATH] = {};
                if (GetModuleFileNameA((HMODULE)base, modName, MAX_PATH))
                {
                    auto filename = basename_only(modName);
                    oss << filename << " ";
                    cur[0] = filename;
                }
            }

            // Function name + offset
            oss << "!";
            if (SymFromAddr(GetCurrentProcess(), addr64, &displacement, sym))
            {
                oss << sym->Name << " +0x" << ::std::hex << displacement << ::std::dec;
                cur[1] = sym->Name;
            }
            else
            {
                oss << "[0x" << ::std::hex << addr64 << ::std::dec << "]";
            }

            // File:line
            IMAGEHLP_LINE64 lineInfo = {};
            lineInfo.SizeOfStruct = sizeof(lineInfo);
            DWORD lineDisp = 0;
            if (SymGetLineFromAddr64(GetCurrentProcess(), addr64, &lineDisp, &lineInfo))
            {
                auto filename = FilenameOnly(lineInfo.FileName);
                oss << " (" << filename << ":" << lineInfo.LineNumber << ")";
                cur[2] = filename;
            }

            oss << "\n";
            outStk.push_back(cur);
        }

        ::std::free(sym);
        return oss.str();
    }

} // namespace DbgPltfUtls

#elif defined(__linux__) // ================= LINUX =================

#include <execinfo.h>  // backtrace
#include <dlfcn.h>     // dladdr
#include <cxxabi.h>    // __cxa_demangle
#include <memory>

#define CALLSTACK_ENABLE_ADDR2LINE

#ifdef CALLSTACK_ENABLE_ADDR2LINE
#include <cstdio>      // popen/pclose
#endif

#if __has_include(<gelf.h>) && __has_include(<libelf.h>)
#include <libelf.h>
#include <gelf.h>
#include <fcntl.h>
#include <unistd.h>
#define CALLSTACK_HAS_LIBELF 1
#else
#define CALLSTACK_HAS_LIBELF 0
#endif

namespace DbgPltfUtls {

#ifdef CALLSTACK_ENABLE_ADDR2LINE
    inline ::std::string try_addr2line(const char* moduleFullPath, void* addr) {
        if (!moduleFullPath || !*moduleFullPath) return {};
        char cmd[1024];
        ::std::snprintf(cmd, sizeof(cmd), "addr2line -Cfpe \"%s\" %p", moduleFullPath, addr);
        ::std::string out;
        if (FILE* fp = popen(cmd, "r")) {
            char buf[512];
            while (::std::fgets(buf, sizeof(buf), fp)) out += buf;
            pclose(fp);
            while (!out.empty() && (out.back() == '\n' || out.back() == '\r')) out.pop_back();
        }
        return out;
}
#endif

#if CALLSTACK_HAS_LIBELF
    // Best-effort: find the function symbol that contains rel_addr in modulePath
    inline bool elf_lookup_symbol(const char* modulePath,
        ::std::uintptr_t rel_addr,
        ::std::string& name,
        ::std::uintptr_t& sym_start,
        ::std::size_t& sym_size)
    {
        if (!modulePath || !*modulePath) return false;
        if (elf_version(EV_CURRENT) == EV_NONE) return false;

        int fd = ::open(modulePath, O_RDONLY);
        if (fd < 0) return false;

        Elf* elf = elf_begin(fd, ELF_C_READ, nullptr);
        if (!elf) { ::close(fd); return false; }

        bool found = false;
        Elf_Scn* scn = nullptr;
        GElf_Shdr shdr;

        auto scan_table = [&](Elf_Scn* s) {
            if (!s) return;
            if (!gelf_getshdr(s, &shdr)) return;
            if (shdr.sh_type != SHT_SYMTAB && shdr.sh_type != SHT_DYNSYM) return;

            Elf_Data* data = elf_getdata(s, nullptr);
            if (!data || !data->d_size || !shdr.sh_entsize) return;

            const ::std::size_t count = shdr.sh_size / shdr.sh_entsize;
            GElf_Sym sym{};
            ::std::uintptr_t best_start = 0;
            ::std::size_t    best_size = 0;
            const char* best_name = nullptr;

            for (::std::size_t i = 0; i < count; ++i) {
                if (!gelf_getsym(data, i, &sym)) continue;
                if (GELF_ST_TYPE(sym.st_info) != STT_FUNC) continue;
                if (sym.st_value == 0 || sym.st_size == 0) continue;

                if (sym.st_value <= rel_addr && rel_addr < sym.st_value + sym.st_size) {
                    if (!best_name || sym.st_value > best_start) {
                        best_start = sym.st_value;
                        best_size = sym.st_size;
                        best_name = elf_strptr(elf, shdr.sh_link, sym.st_name);
                    }
                }
            }

            if (best_name) {
                name.assign(best_name);
                sym_start = best_start;
                sym_size = best_size;
                found = true;
            }
            };

        while ((scn = elf_nextscn(elf, scn)) != nullptr) {
            scan_table(scn);
        }

        elf_end(elf);
        ::close(fd);
        return found;
    }
#endif // CALLSTACK_HAS_LIBELF

    inline ::std::string GetPrintCallStack(::std::vector<::std::vector<::std::string>>& outStk, unsigned skip = 0, unsigned maxFrames = 10) {
        const int cap = static_cast<int>(::std::min<unsigned>(64, maxFrames + skip + 1));
        void* addrs[64]{};
        int n = backtrace(addrs, cap);
        if (n <= 0) return {};

        ::std::ostringstream oss;

        for (int i = skip + 1, fi = 0; i < n && fi < static_cast<int>(maxFrames); ++i, ++fi) {
            void* addr = addrs[i];
            Dl_info info{};
            const bool has = dladdr(addr, &info) != 0;

            const char* modFull = has ? info.dli_fname : nullptr;
            const char* modBase = has ? basename_only(info.dli_fname) : "??";

            // Preferred function name
            const char* mangled = (has && info.dli_sname) ? info.dli_sname : nullptr;

#if CALLSTACK_HAS_LIBELF
            ::std::string elfName;
            ::std::uintptr_t symStart = 0;
            ::std::size_t    symSize = 0;
            if ((!mangled || !*mangled) && has && info.dli_fname && info.dli_fbase) {
                ::std::uintptr_t rel =
                    reinterpret_cast<::std::uintptr_t>(addr) -
                    reinterpret_cast<::std::uintptr_t>(info.dli_fbase);
                if (elf_lookup_symbol(info.dli_fname, rel, elfName, symStart, symSize)) {
                    mangled = elfName.c_str();
                }
            }
#endif

            // Demangle if possible
            int status = -1;
            ::std::unique_ptr<char, void(*)(void*)> dem(nullptr, ::std::free);
            if (mangled) dem.reset(abi::__cxa_demangle(mangled, nullptr, nullptr, &status));
            const char* func = (dem && status == 0) ? dem.get() : (mangled ? mangled : "??");

            // Offset into function if we have its start
            ::std::uintptr_t offset = 0;
            if (has && info.dli_saddr) {
                offset = reinterpret_cast<::std::uintptr_t>(addr)
                    - reinterpret_cast<::std::uintptr_t>(info.dli_saddr);
            }

            oss << "  " << fi << ": " << func
                << " +0x" << ::std::hex << offset << ::std::dec
                << " in " << (modBase ? modBase : "??");

#ifdef CALLSTACK_ENABLE_ADDR2LINE
            if (modFull && *modFull) {
                ::std::string fl = try_addr2line(modFull, addr);
                if (!fl.empty()) {
                    auto pos = fl.find('\n');
                    if (pos != ::std::string::npos) {
                        ::std::string second = fl.substr(pos + 1);
                        const char* src = second.c_str();
                        const char* only = basename_only(src);
                        if (only != src) {
                            auto colon = second.rfind(':');
                            ::std::string ln = (colon != ::std::string::npos)
                                ? (::std::string(only) + second.substr(colon))
                                : ::std::string(only);
                            oss << " (" << ln << ")";
                        }
                        else {
                            oss << " (" << second << ")";
                        }
                    }
                    else {
                        oss << " (" << fl << ")";
                    }
                }
            }
#endif
            oss << "\n";
        }

        return oss.str();
    }

} // namespace DbgPltfUtls

#endif //__linux__

#endif //__cplusplus
#endif
