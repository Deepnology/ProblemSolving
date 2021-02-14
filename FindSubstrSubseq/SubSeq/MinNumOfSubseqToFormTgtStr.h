#ifndef _MIN_NUM_OF_SUBSEQ_TO_FORM_TGT_STR_H
#define _MIN_NUM_OF_SUBSEQ_TO_FORM_TGT_STR_H
#include "Debug.h"
/*
Leetcode: Shortest Way to Form String
From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).
Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target.
If the task is impossible, return -1.
Example 1:
Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
Example 2:
Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
Example 3:
Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
Constraints:
Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
 */
class MinNumOfSubseqToFormTgtStr
{
public:
    int BruteForce(std::string source, std::string target)
    {
        //O(NM) time
        int N = source.size();
        int M = target.size();
        int i = 0, j = 0, res = 0;
        while (j < M)
        {
            int jj = j;
            for (i = 0; i < N; ++i)
                if (j < M && source[i] == target[j])
                    ++j;
            if (j == jj) return -1;
            ++res;
        }
        return res;
    }

    int UseHashMap(std::string source, std::string target)
    {
        //O(MlogN) time
        int N = source.size();
        int M = target.size();
        std::unordered_map<char, std::vector<int>> toIdx;
        for (int i = 0; i < N; ++i)
            toIdx[source[i]].push_back(i);
        int i = -1, j = 0, res = 0;
        while (j < M)
        {
            if (!toIdx.count(target[j])) return -1;
            auto ub = std::upper_bound(toIdx[target[j]].begin(), toIdx[target[j]].end(), i);
            if (ub == toIdx[target[j]].end())
            {
                i = -1;
                ++res;
            }
            else
            {
                i = *ub;
                ++j;
            }
        }
        return res+1;
    }
};
#endif
