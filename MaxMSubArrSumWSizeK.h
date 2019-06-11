#ifndef MAX_M_SUB_ARR_SUM_W_SIZE_K_H
#define MAX_M_SUB_ARR_SUM_W_SIZE_K_H
#include "Debug.h"
/*
http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=229718&extra=page%3D1%26filter%3Dsortid%26sortid%3D311%26sortid%3D311
http://www.waytocrack.com/forum/71/sum-of-max-m-subarray-non-overlapping-of-size-k
https://www.careercup.com/question?id=5629539583524864
Given an integer array, an integer M, and an integer K.
Find the maximum sum of M non-overlapping subarray sums with each subarray size equal to K.
When M==1: Simple Sliding Window

Leetcode: Maximum Sum of 3 Non-overlapping Subarrays
In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.
Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.
Return the result as a list of indices representing the starting position of each interval (0-indexed).
If there are multiple answers, return the lexicographically smallest one.
Example:
Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

see also MaxSum2NonOvlpSubArrays.h
*/
class MaxMSubArrSumWSizeK
{
public:
	MaxMSubArrSumWSizeK() {}

    std::vector<int> DP2D(const std::vector<int> & nums, int K, int M)
    {
        int N = nums.size();
        std::vector<int> prefixSum(N, 0);
        for (int i = 0; i < N; ++i)
            prefixSum[i] = (i-1<0?0:prefixSum[i-1]) + nums[i];

        std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));
        std::vector<std::vector<int>> idx(M, std::vector<int>(N, 0));

        for (int m = 0; m < M; ++m) // enumerate num of subarrays
        {
            for (int i = (m+1)*K-1; i < N; ++i) // i is the end idx of each subarray: sliding window of size K
            {
                // curSum = prefixSum[i] - prefixSum[i-K] + dp[m-1][i-K]
                int curSum = prefixSum[i] - (i-K<0?0:prefixSum[i-K]) + (m-1<0||i-K<0?0:dp[m-1][i-K]);
                if (curSum > dp[m][i-1])
                {
                    dp[m][i] = curSum;
                    idx[m][i] = i-K+1; // the begin idx of cur subarray
                }
                else
                {
                    dp[m][i] = dp[m][i-1];
                    idx[m][i] = idx[m][i-1];
                }
            }
        }

        std::vector<int> res(M); // the begin idx of each subarray
        int prev = N-1;
        for (int m = M-1; m >= 0; --m)
        {
            res[m] = idx[m][prev];
            prev = res[m]-1;
        }

        Debug::Print2D<int>()(dp, false);
        Debug::Print2D<int>()(idx, false);
        std::cout << "MaxMSubArrSumWSizeK DP2D for [" << Debug::ToStr1D<int>()(nums) << "], K=" << K << ", M=" << M << ": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

/*
	int Recur(std::vector<int> & v)
	{

	}
	int recur(std::vector<int> & prefixSum, int begin, std::vector<int> & path, int K, int M, std::vector<std::vector<int>> & dp)
	{
		int N = prefixSum.size();
		if (path.size() == M)
		{
			//dp[begin][M] = std::max(pdp[begin][M])
		}

		for (int i = begin; i < N; ++i)
		{

		}
	}
*/
};
/*
[rY][cX]
Row#0	= 0, 3, 3, 3, 8, 13, 13, 13
Row#1	= 0, 0, 0, 6, 11, 16, 20, 20
Row#2	= 0, 0, 0, 0, 0, 19, 23, 23

[rY][cX]
Row#0	= 0, 0, 0, 0, 3, 4, 4, 4
Row#1	= 0, 0, 0, 2, 3, 4, 5, 5
Row#2	= 0, 0, 0, 0, 0, 4, 5, 5

MaxMSubArrSumWSizeK DP2D for [1, 2, 1, 2, 6, 7, 5, 1], K=2, M=3: 0, 3, 5
 */
#endif
