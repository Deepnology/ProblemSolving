#ifndef LONGEST_EQUAL_SUM_SUB_ARR_FROM_2_ARR_H
#define LONGEST_EQUAL_SUM_SUB_ARR_FROM_2_ARR_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Amazon
https://sites.google.com/site/spaceofjameschen/annnocements/findindicesijsuchthatsumofelementsfromitojinbotharraysisequalandj-i--amazon
Given 2 binary arrays A and B i.e. containing only 0s and 1s each of size N.
Find indices i, j such that sum of elements from i to j in both arrays is equal and j-i (i.e. the length of the set i,j) is the maximum possible value.

BruteForce_PrefixSums: O(n^2) time, O(n) space
See also MaxSubArraySum.h
*/
class LongestEqualSumSubArrFrom2Arr
{
public:
	LongestEqualSumSubArrFrom2Arr(){}
	~LongestEqualSumSubArrFrom2Arr(){}

	void PrefixSumMap(const std::vector<int> & v1, const std::vector<int> & v2)//still can't think of better ways....
	{
		int N = v1.size();
		std::unordered_map<int, int> prefixSumMap1;//key: prefixSum, val: index
		std::unordered_map<int, int> prefixSumMap2;//key: prefixSum, val: index
		int prefixSum1 = 0;
		int prefixSum2 = 0;
		int maxLen = INT_MIN;
		int maxLeft = -1;
		int maxRight = -1;
		for (int i = 0; i < N; ++i)
		{
			prefixSum1 += v1[i];
			prefixSum2 += v2[i];
			if (prefixSum1 == prefixSum2)
			{
				if (i > maxLen)
				{
					maxLen = i;
					maxLeft = 0;
					maxRight = i;
				}
			}
			//else if ()
		}
	}

	void BruteForce_PrefixSums(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int N = v1.size();
		std::vector<int> prefixSum1(N);
		std::vector<int> prefixSum2(N);
		prefixSum1[0] = v1[0];
		prefixSum2[0] = v2[0];
		for (int i = 1; i < N; ++i)
		{
			prefixSum1[i] = prefixSum1[i - 1] + v1[i];
			prefixSum2[i] = prefixSum2[i - 1] + v2[i];
		}

		int maxLen = 0;
		int maxLeft = 0;
		int maxRight = 0;

		//enumerate all possible subarrays whose sum is equal to prefixSum[right]-prefixSum[left-1]
		for (int right = 0; right < N; ++right)
		{
			for (int left = 0; left <= right; ++left)
			{
				if ((left == 0 && prefixSum1[right] == prefixSum2[right]) ||
					(left != 0 && (prefixSum1[right] - prefixSum1[left - 1] == prefixSum2[right] - prefixSum2[left - 1])))
					if (right - (left - 1) > maxLen)
					{
						maxLen = right - (left - 1);
						maxLeft = left;
						maxRight = right;
					}
			}
		}
		std::cout << Debug::ToStr1D<int>()(prefixSum1) << std::endl;
		std::cout << Debug::ToStr1D<int>()(prefixSum2) << std::endl;
		if (maxLen == 0)
			std::cout << "LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for \"" << Debug::ToStr1D<int>()(v1) << "\", \"" << Debug::ToStr1D<int>()(v2) << "\": Not Found" << std::endl;
		else
			std::cout << "LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for \"" << Debug::ToStr1D<int>()(v1) << "\", \"" << Debug::ToStr1D<int>()(v2) << "\": " << maxLen << ", [" << Debug::ToStr1D<int>()(v1, maxLeft, maxRight) << "], [" << Debug::ToStr1D<int>()(v2, maxLeft, maxRight) << "]" << std::endl;
	}
};
/*
0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3
1, 1, 2, 3, 4, 4, 5, 6, 6, 7, 7
LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for "0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0", "1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0": 4, [1, 0, 0, 1], [0, 1, 1, 0]
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0", "1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1": Not Found
1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4
0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7
LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for "1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0", "0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1": 8, [1, 1, 1, 1, 0, 0, 0, 0], [0, 0, 0, 0, 1, 1, 1, 1]
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7
LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for "1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0", "0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1": 5, [1, 0, 0, 0, 0], [0, 0, 0, 0, 1]
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
LongestEqualSumSubArrFrom2Arr BruteForce_PrefixSums for "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1", "0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0": 11, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1], [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
*/
#endif