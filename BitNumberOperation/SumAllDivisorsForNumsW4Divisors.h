#ifndef _SUM_ALL_DIVISORS_FOR_NUMS_W_4_DIVISORS_H
#define _SUM_ALL_DIVISORS_FOR_NUMS_W_4_DIVISORS_H
#include "Debug.h"
/*
Leetcode: Four Divisors
Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.
If there is no such integer in the array, return 0.
Example 1:
Input: nums = [21,4,7]
Output: 32
Explanation:
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.
 */
class SumAllDivisorsForNumsW4Divisors
{
public:
    int Solve(std::vector<int> & nums)
    {
        int res = 0;
        for (auto & n : nums)
        {
            int sum = 0;
            int count = 0;
            for (int i = 1; i <= sqrt(n); ++i)
            {
                if (n%i == 0)
                {
                    if (n/i == i)
                    {
                        sum += i;
                        ++count;
                    }
                    else
                    {
                        sum += i + (n/i);
                        count += 2;
                    }
                }
                if (count > 4) break;
            }
            if (count == 4) res += sum;
        }
        return res;
    }
};
#endif
