#ifndef _COUNT_PRIME_SET_BITS_OF_NUMS_H
#define _COUNT_PRIME_SET_BITS_OF_NUMS_H
#include "Debug.h"
/*
Leetcode: Prime Number of Set Bits in Binary Representation
Given two integers L and R, find the count of numbers in the range [L, R] (inclusive) having a prime number of set bits in their binary representation.
(Recall that the number of set bits an integer has is the number of 1s present when written in binary.
For example, 21 written in binary is 10101 which has 3 set bits. Also, 1 is not a prime.)
Example 1:
Input: L = 6, R = 10
Output: 4
Explanation:
6 -> 110 (2 set bits, 2 is prime)
7 -> 111 (3 set bits, 3 is prime)
9 -> 1001 (2 set bits , 2 is prime)
10->1010 (2 set bits , 2 is prime)
Example 2:
Input: L = 10, R = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
 */
class CountPrimeSetBitsOfNums
{
public:
    CountPrimeSetBitsOfNums(){}

    int Solve(int L, int R)
    {
        std::unordered_set<int> primes({2,3,5,7,11,13,17,19,23,29});
        int res = 0;
        for (int num = L; num <= R; ++num)
        {
            int bitCount = 0;
            int curNum = num;
            while (curNum)
            {
                ++bitCount;
                curNum &= (curNum-1);
            }
            if (primes.count(bitCount))
                ++res;
        }

        std::cout << "CountPrimeSetBitsOfNums in [" << L << ":" << R << "]: " << res << std::endl;
        return res;
    }
};
/*
CountPrimeSetBitsOfNums in [10:15]: 5
 */
#endif
