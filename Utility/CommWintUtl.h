//only include this header in source file
//do not include this header in header file
#ifndef _COMM_WINT_UTL_H_
#define _COMM_WINT_UTL_H_

#include <windows.h>
#include <tlhelp32.h>

#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

#ifdef __cplusplus

#include <filesystem>
#include <vector>
#include <iostream>
#include <system_error>
#include <sstream>

namespace CommWintUtl
{
    // Converts UTF-16 wstring to a UTF-8 std::string
    inline std::string w2u(const std::wstring& w)
    {
        if (w.empty()) return {};
        int sz = ::WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(),
            nullptr, 0, nullptr, nullptr);
        std::string s(sz, '\0');
        ::WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(),
            s.data(), sz, nullptr, nullptr);
        return s;
    }

    inline std::string demangleMSVC(const std::string& mangled)
    {
        char buffer[1024] = {};
        if (UnDecorateSymbolName(mangled.c_str(), buffer, sizeof(buffer),
            UNDNAME_COMPLETE  // get full signature
        ))
        {
            return buffer;
        }
        // if undecoration fails, just return the mangled name
        return mangled;
    }

    // Helper: extract file version string (e.g. "10.0.19041.388")
    inline std::string getFileVersion(const std::filesystem::path& p)
    {
        auto wpath = p.wstring();
        DWORD handle = 0, size = GetFileVersionInfoSizeW(wpath.c_str(), &handle);
        if (!size) return {};

        std::vector<BYTE> data(size);
        if (!GetFileVersionInfoW(wpath.c_str(), handle, size, data.data()))
            return {};

        VS_FIXEDFILEINFO* info = nullptr;
        UINT infoSize = 0;
        if (!VerQueryValueW(data.data(), L"\\", reinterpret_cast<LPVOID*>(&info), &infoSize)
            || infoSize < sizeof(VS_FIXEDFILEINFO))
        {
            return {};
        }

        std::ostringstream oss;
        oss << HIWORD(info->dwFileVersionMS) << '.'
            << LOWORD(info->dwFileVersionMS) << '.'
            << HIWORD(info->dwFileVersionLS) << '.'
            << LOWORD(info->dwFileVersionLS);
        return oss.str();
    }


}

#endif//__cplusplus
#endif
