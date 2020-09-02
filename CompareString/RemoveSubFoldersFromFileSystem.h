#ifndef _REMOVE_SUB_FOLDERS_FROM_FILE_SYSTEM_H
#define _REMOVE_SUB_FOLDERS_FROM_FILE_SYSTEM_H
#include "Debug.h"
/*
Leetcode: Remove Sub-Folders from the Filesystem
Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.
If a folder[i] is located within another folder[j], it is called a sub-folder of it.
The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters.
For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
Example 1:
Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
Example 2:
Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".
Example 3:
Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 */
class RemoveSubFoldersFromFileSystem
{
    struct Trie
    {
        Trie():key(), children(){}
        std::string key;
        std::unordered_map<std::string,Trie*> children;
    };
    void Insert(Trie * root, std::string & path)
    {
        std::istringstream iss(path);
        std::string token;
        std::vector<std::string> res;//list of folders in the path
        while (getline(iss, token, '/'))
            res.push_back(token);
        int N = res.size();
        for (int i = 0; i < N; ++i)//going down the path
        {
            if (!root->children.count(res[i]))
                root->children[res[i]] = new Trie;
            root = root->children[res[i]];
        }
        root->key = path;
    }
    void CollectRecur(Trie * root, std::vector<std::string> & res)
    {
        if (!root->key.empty())
        {
            res.push_back(root->key);
            return; //early return if cur node is key
        }
        for (auto itr = root->children.begin(); itr != root->children.end(); ++itr)
            CollectRecur(itr->second, res);
    }

public:
    std::vector<std::string> UseTrie(std::vector<std::string> & folder)
    {
        Trie* root = new Trie;
        for (auto & path : folder)
            Insert(root, path);
        std::vector<std::string> res;
        CollectRecur(root, res);
        return res;
    }
    std::vector<std::string> Sort_CheckIfPrevFolderIsRoot(std::vector<std::string> & folder)
    {
        std::sort(folder.begin(), folder.end());
        std::vector<std::string> res;
        res.push_back(*folder.begin());
        for (int i = 1; i < folder.size(); ++i)
        {
            std::string root = res.back() + "/";
            if (folder[i].substr(0, root.size()) != root)
                res.push_back(folder[i]);
        }
        return res;
    }
};
#endif
