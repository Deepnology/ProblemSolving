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
    namespace detail
    {
        namespace fs = std::filesystem;
        inline std::vector<std::string> readListFile(const fs::path& listFile)
        {
            std::ifstream ifs{listFile};
            if (!ifs.is_open())
                throw std::runtime_error("Cannot open list file: " + listFile.string());

            std::vector<std::string> entries;
            std::string line;
            while (std::getline(ifs, line))
            {
                auto start = line.find_first_not_of(" \t\r\n");
                if (start == std::string::npos) continue;
                auto end = line.find_last_not_of(" \t\r\n");
                entries.push_back(line.substr(start, end - start + 1));
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
                    if (ec || rel.empty())
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
        inline void copyFromList(const std::vector<fs::path>& sourcePaths, const fs::path& sourceDir, const fs::path& destDir, bool preserveDirStructure)
        {
            if (!fs::is_directory(sourceDir))
                throw std::runtime_error(sourceDir.string() + " is not a valid directory");

            fs::create_directories(destDir);

            for (auto& entryPath : sourcePaths)
            {
                fs::path rel;
                fs::path src;
                if (entryPath.is_absolute()) // if entryPath is absolute, assume it is inside sourceDir
                {
                    std::error_code ec;
                    rel = fs::relative(entryPath, sourceDir, ec);
                    if (ec || rel.empty())
                    {
                        std::cerr << "Warning: \"" << entryPath << "\" not under \"" << sourceDir << "\"\n";
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
        inline void copyExceptList(const std::unordered_set<fs::path>& skipPaths, const fs::path& sourceDir, const fs::path& destDir, bool preserveStructure)
        {
            if (!fs::is_directory(sourceDir)) {
                throw std::runtime_error{ "Invalid sourceDir: " + sourceDir.string() };
            }
            fs::create_directories(destDir);

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
        /// Read a rename log where each line is "oldPath|newPath"
        inline std::vector<std::pair<fs::path,fs::path>>
        readRenameLog(const fs::path& logFile)
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
    }

    inline bool copyFromListFile(const std::filesystem::path& listFile, const std::filesystem::path& sourceDir, const std::filesystem::path& destDir,
        bool preserveDirStructure, const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false)
    {
        try
        {
            auto raw = detail::readListFile(listFile);

            auto matchedPaths = detail::removeDiffSrcDirPrefix(raw, diffSrcDirPrefix);

            deleteDirectory(destDir);

            if (!exclude)
                detail::copyFromList(matchedPaths, sourceDir, destDir, preserveDirStructure);
            else
            {
                std::unordered_set<std::filesystem::path> skipSet(matchedPaths.begin(), matchedPaths.end());
                detail::copyExceptList(skipSet, sourceDir, destDir, preserveDirStructure);
            }
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << "\n";
            return false;
        }
    }

    inline bool renameFromListFile(const std::filesystem::path& listFile, const std::filesystem::path& sourceDir,
        std::function<std::filesystem::path(const std::filesystem::path&)> renameFileLambda,
        const std::filesystem::path& diffSrcDirPrefix = {}, bool exclude = false, const std::filesystem::path& renameLog = {})
    {
        try
        {
            auto raw= detail::readListFile(listFile);
            auto matchedPaths = detail::removeDiffSrcDirPrefix(raw, diffSrcDirPrefix);
            std::unordered_set<std::filesystem::path> listSet(matchedPaths.begin(), matchedPaths.end());

            // Open log file if requested
            std::ofstream logfs;
            if (!renameLog.empty())
            {
                logfs.open(renameLog, std::ios::out | std::ios::trunc);
                if (!logfs)
                    std::cerr << "Warning: failed to open rename log: " << renameLog << "\n";
            }

            for (auto const& entry : std::filesystem::recursive_directory_iterator(sourceDir)) {
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
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << "\n";
            return false;
        }
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
