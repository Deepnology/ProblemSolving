#ifndef _IS_ARMSTRONG_NUMBER_H
#define _IS_ARMSTRONG_NUMBER_H
#include "Debug.h"
/*
Leetcode: Armstrong Number
The k-digit number N is an Armstrong number if and only if the k-th power of each digit sums to N.
Given a positive integer N, return true if and only if it is an Armstrong number.
Example 1:
Input: 153
Output: true
Explanation:
153 is a 3-digit number, and 153 = 1^3 + 5^3 + 3^3.
Example 2:
Input: 123
Output: false
Explanation:
123 is a 3-digit number, and 123 != 1^3 + 2^3 + 3^3 = 36.
 */
class IsArmstrongNumber
{
public:
    bool Solve(int N)
    {
        int powSum = 0;
        std::string s = std::to_string(N);
        for (auto & c : s)
            powSum += pow((c-'0'),s.size());
        int res = powSum == N;
        std::cout << "IsArmstrongNumber for " << N << ": " << res << std::endl;
        return res;
    }
};
/*
IsArmstrongNumber for 153: 1
 */
#endif
