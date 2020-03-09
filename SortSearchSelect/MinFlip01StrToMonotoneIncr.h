#ifndef _MIN_FLIP_01_STR_TO_MONOTONE_INCR_H
#define _MIN_FLIP_01_STR_TO_MONOTONE_INCR_H
#include "Debug.h"
/*
Leetcode: Flip String to Monotone Increasing
A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)
We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.
Return the minimum number of flips to make S monotone increasing.
Example 1:
Input: "00110"
Output: 1
Explanation: We flip the last digit to get 00111.
Example 2:
Input: "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.
Example 3:
Input: "00011000"
Output: 2
Explanation: We flip to get 00000000.
 */
class MinFlip01StrToMonotoneIncr
{
public:
    MinFlip01StrToMonotoneIncr(){}
    ~MinFlip01StrToMonotoneIncr(){}

    int PrefixSum(std::string S)
    {
        int N = S.size();
        std::vector<int> left1PrefixSum(N, 0);
        std::vector<int> right0PrefixSum(N, 0);
        for (int i = 0; i < N; ++i)
            left1PrefixSum[i] = i==0? (S[i]=='1') : (S[i]=='1') + left1PrefixSum[i-1];
        for (int i = N-1; i >= 0; --i)
            right0PrefixSum[i] = i==N-1? (S[i]=='0') : (S[i]=='0') + right0PrefixSum[i+1];
        int res = INT_MAX;
        for (int i = 0; i < N; ++i)
            res = std::min(res, i == 0 ? right0PrefixSum[i+1] : i==N-1 ? left1PrefixSum[i-1] : left1PrefixSum[i-1] + right0PrefixSum[i+1]);

        std::cout << "MinFlip01StrToMonotoneIncr PrefixSum for [" << S << "]: " << res << std::endl;
        return res;
    }

    int DP(std::string S)
    {
        int N = S.size();
        std::vector<int> dp(N+1,0);//dp[i]: min flip in S[0:i-1]
        int count1 = 0;
        for (int i = 0; i < N; ++i)
        {
            if (S[i] == '0')
                //2 options
                //1. flip '0' to '1': min flip = dp[i]+1
                //2. keep '0' and flip all prev 1s to 0s: min flip = count1
            {
                dp[i+1] = std::min(dp[i]+1, count1);
            }
            else//do nothing
            {
                ++count1;
                dp[i+1] = dp[i];
            }
        }

        std::cout << "MinFlip01StrToMonotoneIncr DP for [" << S << "]: " << dp[N] << std::endl;
        return dp[N];
    }
};
/*
MinFlip01StrToMonotoneIncr PrefixSum for [010110]: 2
MinFlip01StrToMonotoneIncr DP for [010110]: 2
 */
#endif
