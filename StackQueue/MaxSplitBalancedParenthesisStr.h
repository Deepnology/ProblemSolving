#ifndef _MAX_SPLIT_BALANCED_PARENTHESIS_STR_H
#define _MAX_SPLIT_BALANCED_PARENTHESIS_STR_H
#include "Debug.h"
/*
Leetcode: Split a String in Balanced Strings
Balanced strings are those who have equal quantity of 'L' and 'R' characters.
Given a balanced string s split it in the maximum amount of balanced strings.
Return the maximum amount of splitted balanced strings.
Example 1:
Input: s = "RLRRLLRLRL"
Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
Example 2:
Input: s = "RLLLLRRRLR"
Output: 3
Explanation: s can be split into "RL", "LLLRRR", "LR", each substring contains same number of 'L' and 'R'.
Example 3:
Input: s = "LLLLRRRR"
Output: 1
Explanation: s can be split into "LLLLRRRR".
Example 4:
Input: s = "RLRRRLLRLL"
Output: 2
Explanation: s can be split into "RL", "RRRLLRLL", since each substring contains an equal number of 'L' and 'R'
 */
class MaxSplitBalancedParenthesisStr
{
public:
    int Count(std::string s)
    {
        int res = 0;
        int balance = 0;
        for (auto & c : s)
        {
            if (c == 'L')
                ++balance;
            else
                --balance;
            if (balance == 0) //balanced
                ++res;
        }
        return res;
    }
};
#endif
