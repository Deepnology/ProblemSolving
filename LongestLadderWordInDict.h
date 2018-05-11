#ifndef _LONGEST_LADDER_WORD_IN_DICT_H
#define _LONGEST_LADDER_WORD_IN_DICT_H
#include "Debug.h"
/*
Leetcode: Longest Word In Dictionary
Given a list of strings words representing an English Dictionary, find the longest word in words that can be built one character at a time by other words in words.
If there is more than one possible answer, return the longest word with the smallest lexicographical order.
If there is no answer, return the empty string.
Example 1:
Input:
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation:
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input:
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation:
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
 */
class LongestLadderWordInDict
{
public:
    LongestLadderWordInDict(){}
private:
    struct Trie
    {
        Trie(bool _isWord = false):children(26,NULL),isWord(_isWord){}
        std::vector<Trie*> children;
        bool isWord;
    };
    void Insert(Trie * root, const std::string & s)
    {
        int N = s.size();
        int i = 0;
        while (i < N)
        {
            if (!root->children[s[i]-'a'])
                root->children[s[i]-'a'] = new Trie;
            if (i == N-1)
                root->children[s[i]-'a']->isWord = true;
            root = root->children[s[i]-'a'];
            ++i;
        }
    }
    void Recur(Trie * cur, std::string & path, std::string & res)
    {
        if (path.size() > res.size())
            res = path;
        for (int i = 0; i < 26; ++i)
            if (cur->children[i] && cur->children[i]->isWord)//only traverse isWord nodes !!
            {
                path.push_back(i+'a');
                Recur(cur->children[i], path, res);
                path.pop_back();
            }
    }
public:
    std::string UseTrie(const std::vector<std::string> & words)
    {
        Trie * root = new Trie;
        for (auto s : words)
            Insert(root, s);
        std::string res;
        std::string path;
        Recur(root, path, res);
        std::cout << "LongestLadderWordInDict UseTrie for [" << Debug::ToStr1D<std::string>()(words) << "]: " << res << std::endl;
        return res;
    }

    std::string SortHashSet(std::vector<std::string> && words)
    {
        std::sort(words.begin(), words.end());//so that latter words can be built from former, ex: a, ab, abc, ...
        std::string res;
        std::unordered_set<std::string> build;//contains only words that can be built from others
        for (auto s : words)
        {
            if (s.size() == 1 || build.count(s.substr(0, s.size()-1)))
            {
                if (s.size() > res.size())
                    res = s;
                build.insert(s);
            }
        }
        std::cout << "LongestLadderWordInDict SortHashSet for [" << Debug::ToStr1D<std::string>()(words) << "]: " << res << std::endl;
        return res;
    }
};
/*
LongestLadderWordInDict UseTrie for [a, banana, app, appl, ap, apply, apple]: apple
LongestLadderWordInDict SortHashSet for [a, ap, app, appl, apple, apply, banana]: apple
 */
#endif
