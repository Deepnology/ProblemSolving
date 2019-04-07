#ifndef _COUNT_SUBARR_W_SUM_DIVISIBLE_BY_K_H
#define _COUNT_SUBARR_W_SUM_DIVISIBLE_BY_K_H
#include "Debug.h"
/*
Leetcode: Subarray Sums Divisible By K
Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.
Example 1:
Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 */
class CountSubArrWSumDivisibleByK
{
public:
    CountSubArrWSumDivisibleByK(){}
    ~CountSubArrWSumDivisibleByK(){}

    int UsePrefixSumMap(std::vector<int> && A, int K)
    {
        std::unordered_map<int,int> modCount;
        modCount[0] = 1;
        int N = A.size();
        int res = 0;
        int prefixSum = 0;
        for (int i = 0; i < N; ++i)
        {
            prefixSum += A[i];
            int curMod = (prefixSum%K+K)%K;
            //Because -1 % 5 = -1, but we need the positive mod 4
            //if sum[0, i] % K == sum[0, j] % K, sum[i + 1, j] is divisible by by K
            if (modCount.count(curMod))
            {
                res += modCount[curMod];//accumulate prev count of curMod
                ++modCount[curMod];
            }
            else
                modCount[curMod] = 1;
        }
        std::cout << "CountSubArrWSumDivisibleByK UsePrefixSumMap for [" << Debug::ToStr1D<int>()(A) << "], " << K << ": " << res << std::endl;
        return res;
    }
};
/*
CountSubArrWSumDivisibleByK UsePrefixSumMap for [4, 5, 0, -2, -3, 1], 5: 7
 */
#endif
