/*BitNumberOperation*/
#ifndef COLLECTIONS_SELF_DIVIDING_NUMBERS_H
#define COLLECTIONS_SELF_DIVIDING_NUMBERS_H
#include "Debug.h"
/*
Leetcode: Self Dividing Numbers
A self-dividing number is a number that is divisible by every digit it contains.
For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.
Also, a self-dividing number is not allowed to contain the digit zero.
Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.
Example 1:
Input:
left = 1, right = 22
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
Note:
The boundaries of each input argument are 1 <= left <= right <= 10000.
 */
class SelfDividingNumbers
{
public:
    SelfDividingNumbers(){}
    std::vector<int> BruteForce(int left, int right)
    {
        std::vector<int> res;
        for (int i = left; i <= right; ++i)
        {
            bool valid = true;
            int cur = i;
            while (cur)
            {
                int digit = cur % 10;
                if (digit == 0 || i % digit != 0)
                {
                    valid = false;
                    break;
                }
                cur /= 10;
            }
            if (valid) res.push_back(i);
        }

        std::cout << "SelfDividingNumbers BruteForce for [" << left << "," << right << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
SelfDividingNumbers BruteForce for [1,22]: 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22
*/
#endif
