#ifndef _VALID_NUMS_ROTATING_ALL_DIGITS_UPSIDE_DOWN_H
#define _VALID_NUMS_ROTATING_ALL_DIGITS_UPSIDE_DOWN_H
#include "Debug.h"
/*
Leetcode: Rotated Digits
X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.
Each digit must be rotated - we cannot choose to leave it alone.
A number is valid if each digit remains a digit after rotation.
0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other
 , and the rest of the numbers do not rotate to any other number and become invalid.
Now given a positive number N, how many numbers X from 1 to N are good?
Example:
Input: 10
Output: 4
Explanation:
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
 */
class ValidNumsRotatingAllDigitsUpsideDown
{
public:
    int CountDiffValidNumsFrom1toN_Better(int N)
    {
        //there is O(logN) time solution
        //O(N) time, O(N) space
        //                      0 1 2 3 4 5 6 7 8 9
        std::vector<int> valid({1,1,2,0,0,2,2,0,1,2});
        std::vector<int> dp(N + 1);
        dp[0] = 1;
        int res = 0;
        for (int i = 1; i <= N; ++i)
        {
            int isValid = 1;
            isValid *= valid[i % 10] * dp[i / 10];
            if (isValid >= 2) ++res;
            dp[i] = isValid >= 2 ? 2 : isValid;
        }
        std::cout << "ValidNumsRotatingAllDigitsUpsideDown_Better from 1 to " << N << ": " << res << std::endl;
        return res;
    }
    int CountDiffValidNumsFrom1toN(int N)
    {
        //O(NlogN) time, O(1) space
        //                      0 1 2 3 4 5 6 7 8 9
        std::vector<int> valid({1,1,2,0,0,2,2,0,1,2});
        int res = 0;
        for (int i = 1; i <= N; ++i)
        {
            int isValid = 1;
            int num = i;
            while (num)
            {
                isValid *= valid[num%10];
                num /= 10;
            }
            if (isValid >= 2) ++res;
        }
        std::cout << "ValidNumsRotatingAllDigitsUpsideDown from 1 to " << N << ": " << res << std::endl;
        return res;
    }
};
/*
ValidNumsRotatingAllDigitsUpsideDown from 1 to 10: 4
ValidNumsRotatingAllDigitsUpsideDown_Better from 1 to 10: 4
 */
#endif
