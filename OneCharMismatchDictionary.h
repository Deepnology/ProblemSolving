#ifndef _ONE_CHAR_MISMATCH_DICTIONARY_H
#define _ONE_CHAR_MISMATCH_DICTIONARY_H
#include "Debug.h"
/*
Leetcode: Implement Magic Dictionary
Implement a magic directory with buildDict, and search methods.
For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.
For the method search, you'll be given a word, and judge whether if you modify exactly one character
 into another character in this word, the modified word is in the dictionary you just built.
Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases.
 */
class OneCharMismatchDictionary
{
    struct Trie
    {
        std::vector<Trie*> children;
        bool isKey;
        Trie():children(26,NULL), isKey(false){}
    };
    void Insert(Trie * root, std::string & s)
    {
        int N = s.size();
        int cur = 0;
        while (true)
        {
            if (!root->children[s[cur]-'a'])
                root->children[s[cur]-'a'] = new Trie;
            if (cur == N-1)
            {
                root->children[s[cur]-'a']->isKey = true;
                break;
            }
            root = root->children[s[cur]-'a'];
            ++cur;
        }
    }
    bool searchRecur(Trie * root, std::string & s, int cur, int misMatchCount)
    {
        if (root == NULL) return false;
        if (misMatchCount == 2) return false;
        int N = s.size();
        if (cur == N)
        {
            if (root->isKey && misMatchCount == 1)
                return true;
            return false;
        }
        for (int i = 0; i < 26; ++i)
        {
            if (searchRecur(root->children[i], s, cur+1, s[cur]-'a'==i ? misMatchCount:misMatchCount+1))
                return true;
        }
        return false;
    }
    Trie * root;
public:
    /** Initialize your data structure here. */
    OneCharMismatchDictionary()
    {
        root = new Trie;
    }

    /** Build a dictionary through a list of words */
    void BuildDict(std::vector<std::string> dict)
    {
        for (auto & s : dict)
            Insert(root, s);
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool Search(std::string word)
    {
        bool found = searchRecur(root, word, 0, 0);
        std::cout << "OneCharMismatchDiction Search [" << word << "]: " << found << std::endl;
        return found;
    }
};
/*
OneCharMismatchDiction Search [hello]: 0
OneCharMismatchDiction Search [hhllo]: 1
OneCharMismatchDiction Search [hell]: 0
OneCharMismatchDiction Search [leetcoded]: 0
 */
#endif
