#ifndef _DESIGN_IN_MEMORY_FILE_SYSTEM_H
#define _DESIGN_IN_MEMORY_FILE_SYSTEM_H
#include "Debug.h"
/*
Leetcode: Design In-memory File System
Design an in-memory file system to simulate the following functions:
ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. If it is a directory path, return the list of file and directory names in this directory. Your output (file and directory names together) should in lexicographic order.
mkdir: Given a directory path that does not exist, you should make a new directory according to the path. If the middle directories in the path don't exist either, you should create them as well. This function has void return type.
addContentToFile: Given a file path and file content in string format. If the file doesn't exist, you need to create that file containing given content. If the file already exists, you need to append given content to original content. This function has void return type.
readContentFromFile: Given a file path, return its content in string format.

Input:
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
Output:
[null,[],null,null,["a"],"hello"]
 */
class DesignInMemoryFileSystem
{
    struct Trie
    {
        Trie():isFile(false){}
        bool isFile;
        std::string content;
        std::unordered_map<std::string,Trie*> children;
    };
    Trie * root;
    std::vector<std::string> splitPath(const std::string & path)
    {
        std::vector<std::string> res;
        int i = 0;
        int N = path.size();
        while (i < N)
        {
            while (i < N && path[i] == '/')
                ++i;
            int begin = i;
            while (i < N && path[i] != '/')
                ++i;
            if (i-begin > 0)
                res.push_back(path.substr(begin, i-begin));
        }
        return res;
    }


public:
    DesignInMemoryFileSystem()
    {
        root = new Trie;
    }

    std::vector<std::string> ls(std::string path)
    {
        std::vector<std::string> tokens = splitPath(path);
        std::vector<std::string> res;
        int N = tokens.size();
        int i = 0;
        Trie * cur = root;
        while (i < N)
        {
            if (!cur->children.count(tokens[i]))
                return res;
            cur = cur->children[tokens[i]];
            ++i;
        }
        if (cur->isFile)
            res.push_back(tokens.back());
        else
        {
            for (auto & p : cur->children)
                res.push_back(p.first);
        }
        std::sort(res.begin(), res.end());
        return res;
    }

    void mkdir(std::string path)
    {
        std::vector<std::string> tokens = splitPath(path);
        int N = tokens.size();
        int i = 0;
        Trie * cur = root;
        while (i < N)
        {
            if (!cur->children.count(tokens[i]))
                cur->children[tokens[i]] = new Trie;
            cur = cur->children[tokens[i]];
            ++i;
        }
    }

    void addContentToFile(std::string filePath, std::string content)
    {
        std::vector<std::string> tokens = splitPath(filePath);
        int N = tokens.size();
        int i = 0;
        Trie * cur = root;
        while (i < N)
        {
            if (!cur->children.count(tokens[i]))
                cur->children[tokens[i]] = new Trie;
            cur = cur->children[tokens[i]];
            ++i;
        }
        cur->isFile = true;
        cur->content += content;
    }

    std::string readContentFromFile(std::string filePath)
    {
        std::vector<std::string> tokens = splitPath(filePath);
        int N = tokens.size();
        int i = 0;
        std::string res;
        Trie * cur = root;
        while (i < N)
        {
            if (!cur->children.count(tokens[i]))
                return res;
            cur = cur->children[tokens[i]];
            ++i;
        }
        if (!cur->isFile)
            return res;
        return res = cur->content;
    }
};
#endif
