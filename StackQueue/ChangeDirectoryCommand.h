#ifndef _CHANGE_DIRECTORY_COMMAND_H
#define _CHANGE_DIRECTORY_COMMAND_H
#include "Debug.h"
/*
asked at TicTok interview
 */
class ChangeDirectoryCommand
{
public:
    std::string cd(const std::string & src, const std::string & tgt)
    {
        std::vector<std::string> sV = SplitSlash(src);
        std::vector<std::string> tV = SplitSlash(tgt);
        std::vector<std::string> stk;
        if (!tgt.empty() && tgt[0] != '/') //add src to stk
        {
            for (auto & s : sV)
                if (s == "..")
                {
                    if (!stk.empty())
                        stk.pop_back();
                }
                else if (s.empty() || s == ".") { } //skip
                else
                    stk.push_back(s);
        }
        for (auto & s : tV) //add tgt to stk
            if (s == "..")
            {
                if (!stk.empty())
                    stk.pop_back();
            }
            else if (s.empty() || s == ".") { } //skip
            else
                stk.push_back(s);

        std::string res;
        if (stk.empty())
            res += "/";
        else
            for (auto & s : stk)
                res += "/" + s;

        std::cout << "ChangeDirectoryCommand from \"" << src << "\" to \"" << tgt << "\": " << res << std::endl;
        return res;
    }
private:
    std::vector<std::string> SplitSlash(const std::string & s)
    {
        int N = s.size();
        std::vector<std::string> res;
        int i = 0;
        while (i < N)
        {
            int begin = i;
            while (i < N && s[i] != '/')
                ++i;
            res.push_back(s.substr(begin, i-begin));//might contain "..", ".", "", non-empty string
            ++i;//skip '/'
        }
        return res;
    }

public:
    void Test()
    {
        std::string path("/a/b/c/d");
        path = cd(path, "../x");
        path = cd(path, "..");
        path = cd(path, "./");
        path = cd(path, "x");
        path = cd(path, "/a/b/c");
        path = cd(path, "../../x");
        path = cd(path, "./x/../../y");
        path = cd(path, "/x/../../y");
        path = cd(path, "../../../..");
        path = cd(path, "x/..");
        path = cd(path, "");
        path = cd(path, "/");
    }
};
/*
ChangeDirectoryCommand from "/a/b/c/d" to "../x": /a/b/c/x
ChangeDirectoryCommand from "/a/b/c/x" to "..": /a/b/c
ChangeDirectoryCommand from "/a/b/c" to "./": /a/b/c
ChangeDirectoryCommand from "/a/b/c" to "x": /a/b/c/x
ChangeDirectoryCommand from "/a/b/c/x" to "/a/b/c": /a/b/c
ChangeDirectoryCommand from "/a/b/c" to "../../x": /a/x
ChangeDirectoryCommand from "/a/x" to "./x/../../y": /a/y
ChangeDirectoryCommand from "/a/y" to "/x/../../y": /y
ChangeDirectoryCommand from "/y" to "../../../..": /
ChangeDirectoryCommand from "/" to "x/..": /
ChangeDirectoryCommand from "/" to "": /
ChangeDirectoryCommand from "/" to "/": /
 */
#endif
