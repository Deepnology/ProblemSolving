#ifndef DESCRIBE_POINTER_H
#define DESCRIBE_POINTER_H

#ifdef __cplusplus

#include <filesystem>
#include <iostream>
#include <system_error>
#include <mutex>
#include <string>
#include <cstdio>
#include <cstdint>
#include <sstream>

#if defined(_WIN32)

    // ===== Windows: DbgHelp-based =====
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>
#include <psapi.h>

#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "Psapi.lib")

namespace DbgPltfUtls {
    inline ::std::string format_last_error_(DWORD e) {
        if (!e) return {};
        LPVOID msg = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, e, 0,
            (LPSTR)&msg, 0, nullptr);
        ::std::string s = msg ? (char*)msg : "unknown";
        if (msg) LocalFree(msg);
        return s;
    }

    inline bool has_symsrv_() {
        HMODULE h = LoadLibraryA("symsrv.dll");
        if (h) { FreeLibrary(h); return true; }
        return false;
    }

    inline ::std::string build_symbol_path_(const char* extra = nullptr) {
        char exePath[MAX_PATH] = {};
        GetModuleFileNameA(nullptr, exePath, MAX_PATH);
        ::std::string dir(exePath);
        if (auto pos = dir.find_last_of("\\/"); pos != ::std::string::npos) dir.resize(pos);

        ::std::ostringstream oss;
        oss << dir; // exe/pdb folder

        // Add user-provided search path env if present
        char envPath[32768];
        if (DWORD n = GetEnvironmentVariableA("_NT_SYMBOL_PATH", envPath, sizeof(envPath));
            n && n < sizeof(envPath)) {
            oss << ";" << envPath;
        }

        if (extra && *extra) oss << ";" << extra; // e.g. your build dir with PDBs

        // Public Microsoft server only if symsrv is available
        if (has_symsrv_()) {
            oss << ";srv*C:\\symbols*https://msdl.microsoft.com/download/symbols";
        }
        return oss.str();
    }

    inline void force_load_modules_(HANDLE proc) {
        HMODULE mods[1024];
        DWORD bytes = 0;
        if (EnumProcessModules(proc, mods, sizeof(mods), &bytes)) {
            size_t count = bytes / sizeof(HMODULE);
            MODULEINFO mi{};
            char path[MAX_PATH];
            for (size_t i = 0; i < count; ++i) {
                if (GetModuleInformation(proc, mods[i], &mi, sizeof(mi)) &&
                    GetModuleFileNameA(mods[i], path, MAX_PATH)) {
                    SymLoadModuleEx(proc, nullptr, path, nullptr,
                        (DWORD64)mods[i], mi.SizeOfImage,
                        nullptr, 0);
                }
            }
        }
    }

    inline bool ensure_initialized_(const char* extraSearchPath) {
        static ::std::once_flag flag;
        static bool ok = false;
        ::std::call_once(flag, [extraSearchPath] {
            HANDLE proc = GetCurrentProcess(); // pseudo-handle (-1) is expected
            SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
            const ::std::string sp = build_symbol_path_(extraSearchPath);
            ok = SymInitialize(proc, sp.c_str(), FALSE) != FALSE; // manual module loading
            if (ok) force_load_modules_(proc);
            });
        return ok;
    }

    /// Windows version:
    /// extraSearchPath: optional semicolon-separated dirs with your PDBs
    inline ::std::string describe_pointer(const void* p,
        const char* extraSearchPath = nullptr,
        bool includeModule = true,
        bool prettyNames = true,
        bool includeOffset = true)
    {
        if (!p) return "null";
        if (!ensure_initialized_(extraSearchPath))
            return ::std::string("DbgHelp init failed: ") + format_last_error_(GetLastError());

        static std::mutex mu; // DbgHelp is not thread-safe
        std::lock_guard<std::mutex> lk(mu);

        HANDLE proc = GetCurrentProcess();
        const DWORD64 addr = (DWORD64)p;

        // Resolve symbol
        char symbuf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
        PSYMBOL_INFO sym = reinterpret_cast<PSYMBOL_INFO>(symbuf);
        sym->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym->MaxNameLen = MAX_SYM_NAME;

        DWORD64 disp = 0;
        ::std::string symName;
        if (SymFromAddr(proc, addr, &disp, sym)) {
            if (prettyNames) {
                char und[MAX_SYM_NAME];
                if (UnDecorateSymbolName(sym->Name, und, MAX_SYM_NAME, UNDNAME_COMPLETE))
                    symName = und;
                else
                    symName = sym->Name;
            }
            else {
                symName = sym->Name;
            }
        }
        else {
            DWORD e = GetLastError();
            symName = ::std::string("<no-symbol> (") + ::std::to_string(e) + ": " + format_last_error_(e) + ")";
        }

        // Resolve module
        ::std::string moduleStr;
        if (includeModule) {
            IMAGEHLP_MODULE64 mod = { sizeof(mod) };
            if (SymGetModuleInfo64(proc, addr, &mod)) {
                if (mod.ImageName && *mod.ImageName) moduleStr = mod.ImageName;
                else if (mod.LoadedImageName && *mod.LoadedImageName) moduleStr = mod.LoadedImageName;
                else if (mod.ModuleName && *mod.ModuleName) moduleStr = mod.ModuleName;
                else moduleStr = "<unknown-module>";
            }
            else {
                DWORD e = GetLastError();
                moduleStr = ::std::string("<unknown-module> (") + ::std::to_string(e) + ": " + format_last_error_(e) + ")";
            }
        }

        // Optional offset from symbol
        ::std::string offsetStr;
        if (includeOffset && disp) {
            char buf[64];
            int n = ::std::snprintf(buf, sizeof(buf), " + 0x%llx",
                (unsigned long long)disp);
            if (n > 0) offsetStr.assign(buf, buf + n);
        }

        // Address suffix
        char addrBuf[48];
        int an = ::std::snprintf(addrBuf, sizeof(addrBuf), " [0x%p]", p);

        // Assemble
        ::std::string out = includeModule ? (moduleStr + "!" + symName + offsetStr)
            : (symName + offsetStr);
        if (an > 0) out.append(addrBuf, addrBuf + an);
        return out;
    }
} // namespace DbgPltfUtls

#elif defined(__linux__) // ================= LINUX =================

#include <dlfcn.h>
#include <cstddef>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

#if __has_include(<gelf.h>) && __has_include(<libelf.h>)
  #include <gelf.h>
  #include <libelf.h>
  #define DBG_HAVE_LIBELF 1
#else
  #define DBG_HAVE_LIBELF 0
#endif

namespace DbgPltfUtls {

// ---- demangle via dlsym(__cxa_demangle) ----
namespace _dbg_demangle {
using demangle_f_t = char* (*)(const char*, char*, ::std::size_t*, int*);
inline demangle_f_t resolve_once_() {
    void* sym = dlsym(RTLD_DEFAULT, "__cxa_demangle");
    if (!sym) {
        #if defined(__APPLE__)
            const char* libs[] = {"libc++abi.dylib", "libstdc++.6.dylib", nullptr};
        #else
            const char* libs[] = {"libstdc++.so.6", "libc++abi.so.1", "libsupc++.so.6", nullptr};
        #endif
        for (int i = 0; !sym && libs[i]; ++i) {
            if (void* h = dlopen(libs[i], RTLD_LAZY | RTLD_LOCAL)) {
                sym = dlsym(h, "__cxa_demangle");
                // keep lib open
            }
        }
    }
    return reinterpret_cast<demangle_f_t>(sym);
}
inline ::std::string demangle(const char* name) {
    if (!name || !*name) return {};
    static demangle_f_t f = resolve_once_();
    if (!f) return ::std::string(name);
    int status = 0;
    char* out = f(name, nullptr, nullptr, &status);
    ::std::string s = (status == 0 && out) ? ::std::string(out) : ::std::string(name);
    if (out) ::std::free(out);
    return s;
}
} // namespace _dbg_demangle

#if DBG_HAVE_LIBELF
// ---- ELF .symtab fallback (nearest symbol) ----
struct _ElfSymHit {
    ::std::string name;
    ::std::uintptr_t sym_addr = 0;
    ::std::uintptr_t delta = ~::std::uintptr_t(0);
};

inline bool _elf_best_from_table(Elf* e, GElf_Shdr& shdr, Elf_Scn* scn,
                                 ::std::uintptr_t base, ::std::uintptr_t addr,
                                 _ElfSymHit& best)
{
    Elf_Data* data = elf_getdata(scn, nullptr);
    if (!data || shdr.sh_entsize == 0) return false;
    const size_t count = shdr.sh_size / shdr.sh_entsize;

    for (size_t i = 0; i < count; ++i) {
        GElf_Sym sym;
        if (!gelf_getsym(data, i, &sym)) continue;
        unsigned type = GELF_ST_TYPE(sym.st_info);
        if (type == STT_SECTION || type == STT_FILE) continue;
        if (sym.st_name == 0) continue;

        ::std::uintptr_t sym_addr = base + (::std::uintptr_t)sym.st_value;
        if (addr < sym_addr) continue;
        ::std::uintptr_t delta = addr - sym_addr;
        if (delta < best.delta) {
            const char* nm = elf_strptr(e, shdr.sh_link, sym.st_name);
            if (!nm || !*nm) continue;
            best.name = nm;
            best.sym_addr = sym_addr;
            best.delta = delta;
            if (delta == 0) return true; // exact match, can early exit
        }
    }
    return best.delta != ~::std::uintptr_t(0);
}

inline bool _elf_lookup_nearest(const char* soPath,
                                ::std::uintptr_t base,
                                ::std::uintptr_t addr,
                                _ElfSymHit& out)
{
    int fd = open(soPath, O_RDONLY);
    if (fd < 0) return false;

    if (elf_version(EV_CURRENT) == EV_NONE) { close(fd); return false; }
    Elf* e = elf_begin(fd, ELF_C_READ, nullptr);
    if (!e) { close(fd); return false; }

    bool found = false;
    Elf_Scn* scn = nullptr;
    while ((scn = elf_nextscn(e, scn)) != nullptr) {
        GElf_Shdr shdr;
        if (!gelf_getshdr(scn, &shdr)) continue;
        if (shdr.sh_type == SHT_SYMTAB || shdr.sh_type == SHT_DYNSYM) {
            if (_elf_best_from_table(e, shdr, scn, base, addr, out)) {
                found = true;
                if (out.delta == 0 && shdr.sh_type == SHT_SYMTAB) break;
            }
        }
    }

    elf_end(e);
    close(fd);
    return found;
}
#endif // DBG_HAVE_LIBELF

inline ::std::string describe_pointer(const void* p,
                                    const char* /*extraSearchPath*/ = nullptr,
                                    bool includeModule = true,
                                    bool prettyNames   = true,
                                    bool includeOffset = true)
{
    if (!p) return "null";

    Dl_info info{};
    const bool ok = dladdr(p, &info) != 0;

    // Module
    ::std::string modStr;
    void* fbase = nullptr;
    if (includeModule) {
        if (ok && info.dli_fname && *info.dli_fname) {
            modStr = info.dli_fname;
            fbase = info.dli_fbase;
        } else {
            modStr = "<unknown-module>";
        }
    } else if (ok) {
        fbase = info.dli_fbase;
    }

    // Symbol from dladdr
    ::std::string symName;
    ::std::uintptr_t offset = 0;
    if (ok && info.dli_sname) {
        symName = prettyNames ? _dbg_demangle::demangle(info.dli_sname)
                              : ::std::string(info.dli_sname);
        if (includeOffset && info.dli_saddr) {
            auto pa = reinterpret_cast<::std::uintptr_t>(p);
            auto sa = reinterpret_cast<::std::uintptr_t>(info.dli_saddr);
            if (pa >= sa) offset = pa - sa;
        }
    } else {
        symName = "<no-symbol>";
    }

#if DBG_HAVE_LIBELF
    // Fallback to ELF .symtab if dladdr gave no name
    if ((symName == "<no-symbol>" || symName.empty()) && ok && info.dli_fname && fbase) {
        _ElfSymHit hit;
        ::std::uintptr_t base = reinterpret_cast<::std::uintptr_t>(fbase);
        ::std::uintptr_t addr = reinterpret_cast<::std::uintptr_t>(p);
        if (_elf_lookup_nearest(info.dli_fname, base, addr, hit)) {
            symName = prettyNames ? _dbg_demangle::demangle(hit.name.c_str())
                                  : hit.name;
            if (includeOffset) offset = addr - hit.sym_addr;
        }
    }
#endif

    // Offset string
    ::std::string offStr;
    if (includeOffset && offset) {
        char buf[64];
        int n = ::std::snprintf(buf, sizeof(buf), " + 0x%zx", (size_t)offset);
        if (n > 0) offStr.assign(buf, buf + n);
    }

    // Address suffix
    char addrBuf[48];
    int an = ::std::snprintf(addrBuf, sizeof(addrBuf), " [0x%p]", p);

    ::std::string out = includeModule ? (modStr + "!" + symName + offStr)
                                    : (symName + offStr);
    if (an > 0) out.append(addrBuf, addrBuf + an);
    return out;
}

} // namespace DbgPltfUtls

#endif //__linux__

#endif //__cplusplus
#endif
