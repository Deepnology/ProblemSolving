#ifndef _SEARCH_WORD_WITH_PREFIX_SUFFIX_H
#define _SEARCH_WORD_WITH_PREFIX_SUFFIX_H
#include "Debug.h"
/*
Leetcode: Prefix and Suffix Search
Given many words, words[i] has weight i.
Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix).
It will return the word with given prefix and suffix with maximum weight.
If no word exists, return -1.
Examples:
Input:
WordFilter(["apple"])
WordFilter.f("a", "e") // returns 0
WordFilter.f("b", "") // returns -1
Note:
words has length in range [1, 15000].
For each test case, up to words.length queries WordFilter.f may be made.
words[i] has length in range [1, 10].
prefix, suffix have lengths in range [0, 10].
words[i] and prefix, suffix queries consist of lowercase letters only.

=> find the word that satisfies both the prefix and suffix with max index from the input array
 */
class SearchWordWithPrefixSuffix_1
{
    struct Trie
    {
        std::vector<Trie*> children;
        std::vector<int> weight;
        Trie():children(26, NULL), weight(){}
    };
    void Insert(Trie * root, const std::string & s, int weight)
    {
        root->weight.push_back(weight);
        int N = s.size();
        int cur = 0;
        while (true)
        {
            if (!root->children[s[cur]-'a'])
                root->children[s[cur]-'a'] = new Trie;
            root->children[s[cur]-'a']->weight.push_back(weight);
            if (cur == N-1)
                break;
            root = root->children[s[cur]-'a'];
            ++cur;
        }
    }
    std::vector<int> Find(Trie * root, const std::string & prefix)
    {
        int N = prefix.size();
        if (N == 0) return root->weight;
        int cur = 0;
        while (cur < N)
        {
            root = root->children[prefix[cur]-'a'];
            if (!root) return std::vector<int>();
            ++cur;
        }
        return root->weight;
    }
    Trie * fwdRoot;
    Trie * bwdRoot;
public:
    SearchWordWithPrefixSuffix_1(const std::vector<std::string> & words) : fwdRoot(new Trie), bwdRoot(new Trie)
    {
        int N = words.size();
        for (int i = 0; i < N; ++i)
        {
            Insert(fwdRoot, words[i], i);
            std::string r(words[i]);
            std::reverse(r.begin(), r.end());
            Insert(bwdRoot, r, i);
        }
    }
    int Search(std::string prefix, std::string suffix)
    {
        std::vector<int> prefixWt = Find(fwdRoot, prefix);
        std::reverse(suffix.begin(), suffix.end());
        std::vector<int> suffixWt = Find(bwdRoot, suffix);
        int N = prefixWt.size();
        int M = suffixWt.size();
        int i = N-1;
        int j = M-1;
        while (i >= 0 && j >= 0)
        {
            if (prefixWt[i] == suffixWt[j]) return prefixWt[i];
            if (prefixWt[i] > suffixWt[j]) --i;
            else --j;
        }
        return -1;
    }
};
class SearchWordWithPrefixSuffix_2
{
    struct Trie
    {
        std::vector<Trie*> children;
        int weight;
        Trie():children(27, NULL), weight(-1){}
    };
    void Insert(Trie * root, const std::string & s, int weight)
    {
        int N = s.size();
        int cur = 0;
        while (true)
        {
            if (!root->children[s[cur]-'a'])
                root->children[s[cur]-'a'] = new Trie;
            root->children[s[cur]-'a']->weight = weight;//overwrite with max weight
            if (cur == N-1)
                break;
            root = root->children[s[cur]-'a'];
            ++cur;
        }
    }
    int Find(Trie * root, const std::string & prefix)
    {
        int N = prefix.size();
        int cur = 0;
        while (cur < N)
        {
            root = root->children[prefix[cur]-'a'];
            if (!root) return -1;
            ++cur;
        }
        return root->weight;
    }
    Trie * root;
public:
    SearchWordWithPrefixSuffix_2(const std::vector<std::string> & words) : root(new Trie)
    {
        int N = words.size();
        for (int i = 0; i < N; ++i)
        {
            int M = words[i].size();
            for (int j = 0; j <= M; ++j)
                Insert(root, words[i].substr(M-j) + "{" + words[i], i);//use '{' because '{'-'a' = 26
            //ex: apple => {apple, e{apple, le{apple, ple{apple, pple{apple, apple{apple
        }
    }
    int Search(std::string prefix, std::string suffix)
    {
        std::string composite(suffix + "{" + prefix);
        return Find(root, composite);
    }
};
#endif
