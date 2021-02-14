#ifndef _LONGEST_SAME_CHAR_SUBARR_WITH_1_SWAP_H
#define _LONGEST_SAME_CHAR_SUBARR_WITH_1_SWAP_H
#include "Debug.h"
/*
Leetcode: Swap For Longest Repeated Character Substring
Given a string text, we are allowed to swap two of the characters in the string.
Find the length of the longest substring with repeated characters.
Example 1:
Input: text = "ababa"
Output: 3
Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa", which its length is 3.
Example 2:
Input: text = "aaabaaa"
Output: 6
Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa", which its length is 6.
Example 3:
Input: text = "aaabbaaa"
Output: 4
Example 4:
Input: text = "aaaaa"
Output: 5
Explanation: No need to swap, longest repeated character substring is "aaaaa", length is 5.
Example 5:
Input: text = "abcdef"
Output: 1
 */
class LongestSameCharSubarrWith1Swap
{
public:
    int UseHashMap(std::string text)
    {
        std::vector<std::vector<int>> toIdx(26, std::vector<int>());
        for (auto i = 0; i < text.size(); ++i)
            toIdx[text[i]-'a'].push_back(i);
        int res = 0;
        for (auto i = 0; i < 26; ++i)
        {
            int j = 0;
            int countPre = 0;
            int idxPre = 0;
            int total = 0;//total len of CountPre+CountCur where there is 1 char gap in btw CountPre and CountCur
            while (j < toIdx[i].size())
            {
                int jj = j+1;
                while (jj < toIdx[i].size() && toIdx[i][jj-1]+1==toIdx[i][jj])
                    ++jj;
                int countCur = jj-j;
                if (toIdx[i][idxPre]+2 == toIdx[i][j])
                    total = std::max(total, countPre+countCur);
                else
                    total = std::max(total, countCur);
                countPre = countCur;
                idxPre = jj-1;
                j = jj;
            }
            res = std::max(res, total + (total<toIdx[i].size()?1:0));//if there is a gap, add 1 char that can be swapped to fill the gap
        }
        return res;
    }

    int UseHashMap2(std::string text)
    {
        std::vector<std::vector<int>> toIdx(26, std::vector<int>());
        for (auto i = 0; i < text.size(); ++i)
            toIdx[text[i]-'a'].push_back(i);
        int res = 0;
        for (auto i = 0; i < 26; ++i)
        {
            int countCur = 1;
            int countPre = 0;
            int total = 0;
            for (auto j = 1; j < toIdx[i].size(); ++j)
            {
                if (toIdx[i][j-1]+1==toIdx[i][j])
                    countCur++;
                else
                {
                    if (toIdx[i][j-1]+2==toIdx[i][j])
                        countPre = countCur;
                    else
                        countPre = 0;
                    countCur = 1;
                }
                total = std::max(total, countCur+countPre);
            }
            res = std::max(res, total + (total<toIdx[i].size()?1:0));//if there is a gap, add 1 char that can be swapped to fill the gap
        }
        return res;
    }
};
#endif
