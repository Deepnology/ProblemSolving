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
};
/*
RepeatRemoveAdjDuplicatesInString UseStack for [abbaca]: ca
 */
#endif
