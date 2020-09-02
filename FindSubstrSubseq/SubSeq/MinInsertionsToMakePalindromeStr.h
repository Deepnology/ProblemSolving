#ifndef _MIN_INSERTIONS_TO_MAKE_PALINDROME_STR_H
#define _MIN_INSERTIONS_TO_MAKE_PALINDROME_STR_H
#include "Debug.h"
/*
Leetcode: Minimum Insertion Steps to Make a String Palindrome
Given a string s. In one step you can insert any character at any index of the string.
Return the minimum number of steps to make s palindrome.
A Palindrome String is one that reads the same backward as well as forward.
Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.
Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".
Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".
Example 4:
Input: s = "g"
Output: 0
Example 5:
Input: s = "no"
Output: 1
Constraints:
1 <= s.length <= 500
All characters of s are lower case English letters.
 */
class MinInsertionsToMakePalindromeStr
{
public:
    int DP2D(std::string s)
    {
        //equivalent to s.size() - LongestPalindromeSubseq(s)
        //O(n^2) time, O(n^2) space
        std::vector<std::vector<int>> dp(s.size(), std::vector<int>(s.size(), 0));
        for (auto len = 2; len <= s.size(); ++len)
        {
            for (auto begin = 0; begin + len - 1 < s.size(); ++begin)
            {
                auto end = begin + len - 1;
                if (s[begin] == s[end])
                    dp[begin][end] = dp[begin+1][end-1]; //don't need to insert any char
                else
                    dp[begin][end] = 1 + std::min(dp[begin+1][end], dp[begin][end-1]); //can choose to insert a char on the left side or right side
            }
        }

        return dp[0][s.size()-1];

        //can use "std::vector<int> prev, cur" to reduce space complexity to O(n)
    }
};
#endif
