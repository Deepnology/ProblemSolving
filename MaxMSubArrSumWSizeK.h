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

*/
class MaxMSubArrSumWSizeK
{
public:
	MaxMSubArrSumWSizeK() {}

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
};
#endif
