/*DP*/
#ifndef LIS_CHAIN_OF_PAIRS_H
#define LIS_CHAIN_OF_PAIRS_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Longest Chain of Pairs
variation of LIS
Leetcode: Maximum Length of Pair Chain
http://www.geeksforgeeks.org/dynamic-programming-set-20-maximum-length-chain-of-pairs/
Given n pairs or numbers, where in every pair, the first number is always smaller than the second number.
A pair (c, d) can follow another pair (a, b) if b < c.
Chain of pairs can be formed in this fashion.
Find the longest chain which can be formed from a given set of pairs.
The original order of pairs doesn't need to maintain.

1. sort the given pairs in increasing order of the first (smaller) element: O(nlogn) time
2. find the longest increasing (leftPair.second < rightPair.first) subsequence of the second elements: 
DP1D_Quadratic: O(n^2) time, O(n) space
*/
class LongestChainOfPairs
{
public:
	LongestChainOfPairs(){}
	~LongestChainOfPairs(){}

	int Len_DP1D_Quadratic(std::vector<std::pair<int, int> > & v)
	{
		int N = v.size();
		std::sort(v.begin(), v.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.first != b.first ? a.first < b.first : a.second < b.second;
		});
		std::vector<int> dp(N, 1);//longest length at each index
		std::vector<int> prevIdx(N, -1);//previous index of LIS at each index
		int maxIncrCount = 1;
		int maxIncrIdx = 0;//the last index of the LIS
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (v[curStart].second < v[curEnd].first && dp[curStart] + 1 > dp[curEnd])
				{
					dp[curEnd] = dp[curStart] + 1;
					prevIdx[curEnd] = curStart;
				}
			}
			if (dp[curEnd] > maxIncrCount)
			{
				maxIncrCount = dp[curEnd];
				maxIncrIdx = curEnd;
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::vector<std::pair<int, int> > lis(maxIncrCount);
		int lisLen = maxIncrCount;
		while (lisLen-- > 0)
		{
			lis[lisLen] = v[maxIncrIdx];
			maxIncrIdx = prevIdx[maxIncrIdx];
		}
		std::cout << "LongestChainOfPairs DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxIncrCount << " (" << Debug::ToStr1D<int>()(lis) << ")" << std::endl;
		return maxIncrCount;
	}

	//equivalent to the Interval Scheduling Problem, see also MinRemovalForNonOverlapIntervals.h
	int UseIntervalScheduling(std::vector<std::vector<int>> & v)//O(nlogn) time
	{
		int N = v.size();
		std::sort(v.begin(), v.end(), [](const std::vector<int> & a, const std::vector<int> & b)->bool
		{
			return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
		});
		int count = 1;
		int pre = 0;
		for (int i = 1; i < N; ++i)
		{
			if (v[pre][1] < v[i][0])
			{
				++count;
				pre = i;
			}
		}
		return count;
	}
};
/*
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 1, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 1, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 1, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 1
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4
LongestChainOfPairs DP1D_Quadratic for "[1,63], [1,74], [8,66], [11,68], [13,74], [14,34], [17,46], [17,95], [18,63], [22,47], [28,84], [30,43], [42,90], [44,60], [52,54], [57,75], [58,72], [62,65], [64,70], [91,97]": 4 ([14,34], [52,54], [57,75], [91,97])
*/
#endif