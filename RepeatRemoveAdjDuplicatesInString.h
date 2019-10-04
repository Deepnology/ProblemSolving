#ifndef _REPEAT_REMOVE_ADJ_DUPLICATES_IN_STRING_H
#define _REPEAT_REMOVE_ADJ_DUPLICATES_IN_STRING_H
#include "Debug.h"
/*
Leetcode: Remove All Adjacent Duplicates In String
Given a string S of lowercase letters, a duplicate removal consists of choosing two adjacent and equal letters, and removing them.
We repeatedly make duplicate removals on S until we no longer can.
Return the final string after all such duplicate removals have been made.  It is guaranteed the answer is unique.
Example 1:
Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".
Note:
1 <= S.length <= 20000
S consists only of English lowercase letters.

Leetcode: Remove All Adjacent Duplicates In String II
Given a string s, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them causing the left and the right side of the deleted substring to concatenate together.
We repeatedly make k duplicate removals on s until we no longer can.
Return the final string after all such duplicate removals have been made.
It is guaranteed that the answer is unique.
Example 1:
Input: s = "abcd", k = 2
Output: "abcd"
Explanation: There's nothing to delete.
Example 2:
Input: s = "deeedbbcccbdaa", k = 3
Output: "aa"
Explanation:
First delete "eee" and "ccc", get "ddbbbdaa"
Then delete "bbb", get "dddaa"
Finally delete "ddd", get "aa"
Example 3:
Input: s = "pbbcggttciiippooaais", k = 2
Output: "ps"
 */
class RepeatRemoveAdjDuplicatesInString
{
public:
    std::string UseStack(std::string S)
    {
        std::string res;//works like stack
        for (auto & s : S)
            if (!res.empty() && res.back() == s)
                res.pop_back();
            else
                res.push_back(s);

        std::cout << "RepeatRemoveAdjDuplicatesInString UseStack for [" << S << "]: " << res << std::endl;
        return res;
    }

    std::string UseStack(std::string s, int k)
    {
        std::vector<std::pair<int,char>> stk;
        for (auto & c : s)
        {
            if (stk.empty() || stk.back().second != c)
                stk.push_back({1,c});
            else
            {
                ++stk.back().first;
                if (stk.back().first == k)
                    stk.pop_back();
            }
        }
        std::string res;
        for (auto & p : stk)
            res += std::string(p.first, p.second);

        std::cout << "RepeatRemoveAdjDuplicatesInString UseStack for [" << s << "], k=" << k << ": " << res << std::endl;
        return res;
    }
};
/*
RepeatRemoveAdjDuplicatesInString UseStack for [abbaca]: ca
RepeatRemoveAdjDuplicatesInString UseStack for [deeedbbcccbdaa], k=3: aa
 */
#endif
