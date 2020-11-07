#ifndef _LONGEST_STRING_CHAIN_H
#define _LONGEST_STRING_CHAIN_H
#include "Debug.h"
/*
Leetcode: Longest String Chain
Given a list of words, each word consists of English lowercase letters.
Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.
 For example, "abc" is a predecessor of "abac".
A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
Return the longest possible length of a word chain with words chosen from the given list of words.
Example 1:
Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".
 */
class LongestStringChain
{
public:
    int Sort_DP(std::vector<std::string> & words)
    {
        std::sort(words.begin(), words.end(), [](const std::string & a, const std::string & b)
        {
            return a.size() < b.size();
        });
        std::unordered_map<std::string, int> dp;
        int res = 0;
        for (std::string w : words)
        {
            for (int i = 0; i < w.length(); i++)
                dp[w] = std::max(dp[w], dp[w.substr(0, i) + w.substr(i + 1)] + 1);//+1: to include cur word
            res = std::max(res, dp[w]);
        }
        return res;
    }
};
#endif
