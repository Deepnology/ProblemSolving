#ifndef _COUNT_STEPPING_NUMS_FROM_LOW_TO_HIGH_H
#define _COUNT_STEPPING_NUMS_FROM_LOW_TO_HIGH_H
#include "Debug.h"
/*
Leetcode: Stepping Numbers
A Stepping Number is an integer such that all of its adjacent digits have an absolute difference of exactly 1.
For example, 321 is a Stepping Number while 421 is not.
Given two integers low and high, find and return a sorted list of all the Stepping Numbers in the range [low, high] inclusive.
Example 1:
Input: low = 0, high = 21
Output: [0,1,2,3,4,5,6,7,8,9,10,12,21]
 */
class CountSteppingNumsFromLowToHigh
{
public:
    std::vector<int> BFS(int low, int high)
    {
        std::vector<int> res;
        if (low > high) return res;
        std::queue<long> que;
        for (int i = 0; i <= 9; ++i)
            que.push(i);

        while (!que.empty())
        {
            long cur = que.front(); que.pop();
            if (cur >= low)
                res.push_back(cur);

            long lastDigit = cur%10;
            if (lastDigit > 0 && cur*10+lastDigit-1 <= (long)high)
                que.push(cur*10+lastDigit-1);
            if (cur != 0 && lastDigit < 9 && cur*10+lastDigit+1 <= (long)high)
                que.push(cur*10+lastDigit+1);
        }
        return res;
    }
};
#endif
