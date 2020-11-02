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
/*
Leetcode: Design File System
You are asked to design a file system that allows you to create new paths and associate them with different values.
The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string "" and "/" are not.
Implement the FileSystem class:
bool createPath(string path, int value) Creates a new path and associates a value to it if possible and returns true. Returns false if the path already exists or its parent path doesn't exist.
int get(string path) Returns the value associated with path or returns -1 if the path doesn't exist.
Example 1:
Input:
["FileSystem","createPath","get"]
[[],["/a",1],["/a"]]
Output:
[null,true,1]
Explanation:
FileSystem fileSystem = new FileSystem();
fileSystem.createPath("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:
Input:
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output:
[null,true,true,2,false,-1]
Explanation:
FileSystem fileSystem = new FileSystem();
fileSystem.createPath("/leet", 1); // return true
fileSystem.createPath("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.
 */
class DesignInMemoryFileSystem2
{
    struct Trie
    {
        Trie(int v):val(v){}
        int val;
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
    DesignInMemoryFileSystem2()
    {
        root = new Trie(-1);
    }
    bool createPath(std::string path, int value)
    {
        std::vector<std::string> tokens = splitPath(path);
        int N = tokens.size();
        int i = 0;
        Trie * cur = root;
        while (i < N-1)
        {
            if (cur->children.count(tokens[i]))
                cur = cur->children[tokens[i]];
            else
                return false;
            ++i;
        }
        if (cur->children.count(tokens[i]))
            return false;
        cur->children[tokens[i]] = new Trie(value);
        return true;
    }
    int get(std::string path)
    {
        std::vector<std::string> tokens = splitPath(path);
        int N = tokens.size();
        int i = 0;
        Trie * cur = root;
        while (i < N)
        {
            if (!cur->children.count(tokens[i]))
                return -1;
            cur = cur->children[tokens[i]];
            ++i;
        }
        return cur->val;
    }
};
#endif
