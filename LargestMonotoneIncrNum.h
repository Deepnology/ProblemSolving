#ifndef _LARGEST_MONOTONE_INCR_NUM_H
#define _LARGEST_MONOTONE_INCR_NUM_H
#include "Debug.h"
/*
Leetcode: Monotone Increasing Digits
Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.
(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)
Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299
 */
class LargestMonotoneIncrNum
{
public:
    LargestMonotoneIncrNum(){}

    int Linear(int num)
    {
        std::string s = std::to_string(num);
        int N = s.size();
        int idx = N;//the leftmost idx that must transform to digit 9
        for (int i = N-1; i > 0; --i)
            if (!(s[i-1] <= s[i]))//s[i-1] > s[i]
            {
                --s[i-1];//decrement prev digit
                idx = i;//transform cur digit and all its right digits to 9
            }
        for (int i = idx; i < N; ++i)
            s[i] = '9';

        int res = stoi(s);
        std::cout << "LargestMonotoneIncrNum for " << num << ": " << res << std::endl;
        return res;
    }
};
/*
LargestMonotoneIncrNum for 332: 299
 */
#endif
