#ifndef EQUAL_SUM_4_SUB_ARR_EXCLUDE_SPLITTER_H
#define EQUAL_SUM_4_SUB_ARR_EXCLUDE_SPLITTER_H
#include "Debug.h"
/*
Leetcode: Split Array With Equal Sum
Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:
0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5.
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1
Note:
1 <= n <= 2000.
Elements in the given array will be in range [-1,000,000, 1,000,000].
*/
class EqualSum4SubArrExcludeSplitter
{
public:
	EqualSum4SubArrExcludeSplitter() {}

	bool CanSplit(const std::vector<int> & v)
	{
		int N = v.size();
		if (N < 7) return false;//[a,i,b,j,c,k,d]
		std::vector<int> prefixSum(N, 0);
		prefixSum[0] = v[0];
		for (int i = 1; i < N; ++i)
			prefixSum[i] += prefixSum[i - 1] + v[i];
		for (int j = 3; j < N - 3; ++j)
		{
			//1. record left side equal sum partition
			std::unordered_set<int> sums;
			for (int i = 1; i < j - 1; ++i)
			{
				int leftSum = prefixSum[i - 1];
				int rightSum = prefixSum[j - 1] - prefixSum[i];
				if (leftSum == rightSum)
					sums.insert(leftSum);
			}

			//2. check if right side can be partitioned into 2 subarrays w/ the sums from left side
			for (int k = j + 2; k < N - 1; ++k)
			{
				int leftSum = prefixSum[k - 1] - prefixSum[j];
				int rightSum = prefixSum[N - 1] - prefixSum[k];
				if (leftSum == rightSum && sums.count(leftSum))
				{
					std::cout << "EqualSum4SubArrExcludeSplitter CanSplit for \"" << Debug::ToStr1D<int>()(v) << "\": 1" << std::endl;
					return true;
				}
			}
		}

		std::cout << "EqualSum4SubArrExcludeSplitter CanSplit for \"" << Debug::ToStr1D<int>()(v) << "\": 0" << std::endl;
		return false;
	}
};
/*
EqualSum4SubArrExcludeSplitter CanSplit for "1, 2, 1, 2, 1, 2, 1": 1
*/
#endif
