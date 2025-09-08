#ifndef _FILE_SYS_UTL_H_
#define _FILE_SYS_UTL_H_

#ifdef __cplusplus
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <functional>
#include <stdexcept>

namespace FileSysUtl
{
    inline void deleteDirectory(const std::filesystem::path& dir)
    {
        std::error_code ec;
        if (std::filesystem::exists(dir))
        {
            std::filesystem::remove_all(dir, ec);
            if (ec)
            {
                throw std::runtime_error(
                    "Failed to delete directory " + dir.string() + ": " + ec.message()
                );
            }
        }
    }
    inline constexpr unsigned int FileSizeBit = 1;
    inline constexpr unsigned int FileModifiedDateBit = 2;
    inline std::string getFileMetaDataSuffix(const std::filesystem::path& p, unsigned int metaOptions)
    {
        std::ostringstream oss;
        if (metaOptions & FileSizeBit)
        {
            try
            {
                auto sz = std::filesystem::file_size(p);
                oss << "|" << sz;
            }
            catch (const std::exception& ex)
            {
                std::cerr << "Error get file size: " << ex.what() << '\n';
            }
        }
        if (metaOptions & FileModifiedDateBit)
        {
            try
            {
                // last write time -> system_clock
                auto ftime = std::filesystem::last_write_time(p);
                auto sctp = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
                std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
                oss << "|" << std::put_time(std::localtime(&cftime), "%Y-%m-%d %H:%M:%S");
            }
            catch (const std::exception& ex)
            {
                std::cerr << "Error get file modified date: " << ex.what() << '\n';
            }
        }
        return oss.str();
    }
    inline std::vector<std::string> listFiles(
        const std::filesystem::path& directory, int fullPath,
        const std::vector<std::string>& extFilters, bool sortResults,
        int maxDepth = -1, int metaOptions = 0)
    {
        if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
            throw std::runtime_error(directory.string() + " is not a valid directory");
        }

        std::vector<std::string> results;
        std::filesystem::recursive_directory_iterator it{ directory }, end;

        for (; it != end; ++it)
        {
            // depth guard
            if (maxDepth >= 0 && it.depth() > maxDepth)
            {
                it.disable_recursion_pending();
                if (it.depth() > maxDepth)
                    continue;
            }

            if (!it->is_regular_file())
                continue;

            // extension filter
            std::string ext = it->path().extension().string();

            if (!extFilters.empty() &&
                std::find(extFilters.begin(), extFilters.end(), ext) == extFilters.end())
            {
                continue;
            }

            // base entry
            std::string entry = (fullPath == 1) ? it->path().string() 
                : (fullPath == 0) ? std::filesystem::relative(it->path(), directory).string() 
                : it->path().filename().string();
            
            std::string metaSuffix = getFileMetaDataSuffix(it->path(), metaOptions);
            results.push_back(entry + metaSuffix);
        }

        if (sortResults) {
            std::sort(results.begin(), results.end());
        }
        return results;
    }
    inline void listFilesDump(
        const std::filesystem::path& directory, int fullPath,
        const std::vector<std::string>& extFilters, bool sortResults, 
        int maxDepth, int metaOptions,
        const std::filesystem::path& dump)
    {
        auto results = listFiles(directory, fullPath, extFilters, sortResults, maxDepth, metaOptions);
        if (!dump.empty())
        {
            std::ofstream logfs;
            logfs.open(dump, std::ios::out | std::ios::trunc);
            if (!logfs)
                std::cerr << "Warning: failed to open dump file: " << dump << "\n";
            for (const auto& s : results)
                logfs << s << "\n";
        }
    }
    namespace detail
    {
        namespace fs = std::filesystem;
        inline std::vector<std::string> readListFile(const fs::path& listFile, bool stripMeta = true)
        {
            std::ifstream ifs{ listFile };
            if (!ifs)
                throw std::runtime_error("Cannot open list file: " + listFile.string());

            std::vector<std::string> entries;
            std::string line;
            while (std::getline(ifs, line))
            {
                // trim
                auto a = line.find_first_not_of(" \t\r\n");
                if (a == std::string::npos) continue;
                auto b = line.find_last_not_of(" \t\r\n");
                std::string tmp = line.substr(a, b - a + 1);

                if (stripMeta)
                {
                    auto pos = tmp.find('|');
                    if (pos != std::string::npos)
                        tmp = tmp.substr(0, pos);
                }
                entries.push_back(tmp);
            }
            return entries;
        }
        inline std::vector<fs::path> removeDiffSrcDirPrefix(const std::vector<std::string>& rawEntries, const fs::path& diffSrcDirPrefix)
        {
            std::vector<fs::path> paths;
            for (auto& s : rawEntries)
            {
                fs::path p(s);
                fs::path rel;
                if (p.is_absolute())
                {
                    std::error_code ec;
                    rel = fs::relative(p, diffSrcDirPrefix, ec);
                    if (ec || rel.empty() || rel.begin()->string().starts_with(".."))
                    {
                        rel = p; // not under sourceDir, use original absolute path
                    }
                }
                else
                {
                    // already relative
                    rel = p;
                }
                paths.push_back(rel);
            }
            return paths;
        }
        inline void copyFromList(const std::vector<fs::path>& sourcePaths, const std::vector<fs::path>& sourceDirs, const fs::path& destDir, bool preserveDirStructure)
        {
            fs::create_directories(destDir);
            for (auto & sourceDir : sourceDirs)
            {
                if (!fs::is_directory(sourceDir))
                    continue;
                
                for (auto& entryPath : sourcePaths)
                {
                    fs::path rel;
                    fs::path src;
                    if (entryPath.is_absolute()) // if entryPath is absolute, assume it is inside sourceDir
                    {
                        std::error_code ec;
                        rel = fs::relative(entryPath, sourceDir, ec);
                        if (ec || rel.empty() || rel.begin()->string().starts_with(".."))
                        {
                            //std::cerr << "Warning: \"" << entryPath << "\" not under \"" << sourceDir << "\"\n";
                            continue;
                        }
                        src = entryPath;
                    }
                    else // if entryPath is relative, assume it is under sourceDir
                    {
                        rel = entryPath;
                        src = sourceDir / entryPath;
                    }

                    if (!fs::is_regular_file(src))
                    {
                        std::cerr << "Warning: entry not found: " << src << "\n";
                        continue;
                    }

                    fs::path dst = preserveDirStructure ? destDir / rel : destDir / rel.filename();

                    fs::create_directories(dst.parent_path());
                    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
                }
            }
        }
        inline void copyExceptList(const std::unordered_set<fs::path>& skipPaths, const std::vector<fs::path>& sourceDirs, const fs::path& destDir, bool preserveStructure)
        {
            fs::create_directories(destDir);
            for (auto & sourceDir : sourceDirs)
            {
                if (!fs::is_directory(sourceDir))
                    continue;
                for (auto const& entry : fs::recursive_directory_iterator(sourceDir))
                {
                    if (!entry.is_regular_file()) continue;
                    if (skipPaths.count(entry.path())) continue;//check absolute path
                    fs::path rel = fs::relative(entry.path(), sourceDir);
                    if (skipPaths.count(rel)) continue;//check relative path

                    fs::path dst = preserveStructure ? destDir / rel : destDir / entry.path().filename();
                    fs::create_directories(dst.parent_path());
                    fs::copy_file(entry.path(), dst, fs::copy_options::overwrite_existing);
                }
            }
        }
        /// Read a rename log where each line is "oldPath|newPath"
        inline std::vector<std::pair<fs::path,fs::path>> readRenameLog(const fs::path& logFile)
        {
            std::ifstream ifs{logFile};
            if (!ifs) {
                throw std::runtime_error{"Cannot open rename log: " + logFile.string()};
            }

            std::vector<std::pair<fs::path,fs::path>> mappings;
            std::string line;
            while (std::getline(ifs, line)) {
                if (line.empty()) continue;
                auto delim = line.find('|');
                if (delim == std::string::npos) {
                    std::cerr << "Warning: skipping malformed line in log: " << line << "\n";
                    continue;
                }
                fs::path oldP = line.substr(0, delim);
                fs::path newP = line.substr(delim + 1);
                mappings.emplace_back(oldP, newP);
            }
            return mappings;
        }
    }//detail

    inline bool copyFromList(const std::vector<std::string>& sourcePaths, const std::vector<std::filesystem::path>& sourceDirs, const std::filesystem::path& destDir,
        bool preserveDirStructure, const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false)
    {
        try
        {
            auto matchedPaths = detail::removeDiffSrcDirPrefix(sourcePaths, diffSrcDirPrefix);
            deleteDirectory(destDir);
            if (!exclude)
                detail::copyFromList(matchedPaths, sourceDirs, destDir, preserveDirStructure);
            else
            {
                std::unordered_set<std::filesystem::path> skipSet(matchedPaths.begin(), matchedPaths.end());
                detail::copyExceptList(skipSet, sourceDirs, destDir, preserveDirStructure);
            }
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << "\n";
            return false;
        }
    }
    inline bool copyFromListFile(const std::filesystem::path& listFile, const std::vector<std::filesystem::path>& sourceDirs, const std::filesystem::path& destDir,
        bool preserveDirStructure, const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false)
    {
        auto raw = detail::readListFile(listFile);
        return copyFromList(raw, sourceDirs, destDir, preserveDirStructure, diffSrcDirPrefix, exclude);
    }

    inline bool renameFromList(const std::vector<std::string>& sourcePaths, const std::vector<std::filesystem::path>& sourceDirs,
        std::function<std::filesystem::path(const std::filesystem::path&)> renameFileLambda,
        const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false, const std::filesystem::path& renameLog = {})
    {
        try
        {
            auto matchedPaths = detail::removeDiffSrcDirPrefix(sourcePaths, diffSrcDirPrefix);
            std::unordered_set<std::filesystem::path> listSet(matchedPaths.begin(), matchedPaths.end());

            // Open log file if requested
            std::ofstream logfs;
            if (!renameLog.empty())
            {
                logfs.open(renameLog, std::ios::out | std::ios::trunc);
                if (!logfs)
                    std::cerr << "Warning: failed to open rename log: " << renameLog << "\n";
            }
            for (auto & sourceDir : sourceDirs)
            {
                for (auto const& entry : std::filesystem::recursive_directory_iterator(sourceDir))
                {
                    if (!entry.is_regular_file())
                        continue;

                    auto rel = std::filesystem::relative(entry.path(), sourceDir);
                    bool inList = listSet.count(entry.path()) || listSet.count(rel);
                    if ((!exclude && !inList) || (exclude && inList))
                        continue;

                    auto oldPath = entry.path();
                    auto newPath = renameFileLambda(oldPath);
                    std::filesystem::create_directories(newPath.parent_path());
                    std::filesystem::rename(oldPath, newPath);

                    if (logfs)
                        logfs << oldPath.string() << "|" << newPath.string() << "\n";
                }
            }
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << "\n";
            return false;
        }
    }
    inline bool renameFromListFile(const std::filesystem::path& listFile, const std::vector<std::filesystem::path>& sourceDirs,
        std::function<std::filesystem::path(const std::filesystem::path&)> renameFileLambda,
        const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false, const std::filesystem::path& renameLog = {})
    {
        auto raw = detail::readListFile(listFile);
        return renameFromList(raw, sourceDirs, renameFileLambda, diffSrcDirPrefix, exclude, renameLog);
    }

    inline bool restoreFromRenameLog(const std::filesystem::path& logFile)
    {
        try
        {
            auto mappings = detail::readRenameLog(logFile);

            // Reverse the order so that deeper files get restored first
            for (auto it = mappings.rbegin(); it != mappings.rend(); ++it)
            {
                const auto& oldP = it->first;
                const auto& newP = it->second;

                if (!std::filesystem::exists(newP))
                {
                    std::cerr << "Warning: cannot restore, file not found: " << newP << "\n";
                    continue;
                }

                // Make sure the target directory for the old path exists
                std::filesystem::create_directories(oldP.parent_path());

                // Perform the rename back
                std::filesystem::rename(newP, oldP);
            }

            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR in restoreFromRenameLog: " << e.what() << "\n";
            return false;
        }
    }
}

#endif
#endif




