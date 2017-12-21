/*DP*/
#ifndef LIS_PAIRS_H
#define LIS_PAIRS_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Longest Increasing Subsequence of Pairs
Given a list of pairs of integers, find the length of the longest increasing subsequence of pairs, where adjacent pairs must satisfy
the constraint: leftPair.first < rightPair.first, leftPair.second < rightPair.second.
(both the first elements and the second elements in the pairs must be in increasing order, respectively)

DP1D_Quadratic: O(n^2) time, O(n) space
see also LongestIncreasingPairs.h, LongestChainOfPairs.h
*/
class LISPairs
{
public:
	LISPairs(){}
	~LISPairs(){}

	int Len_DP1D_Quadratic(const std::vector<std::pair<int, int> > & v)
	{
		int N = v.size();
		if (N == 0) return 0;

		std::vector<int> dp(N, 1);//longest length at each index
		std::vector<int> prevIdx(N, -1);//previous index of LIS at each index
		int maxIncrCount = 1;
		int maxIncrIdx = 0;//the last index of the LIS
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (v[curEnd].first > v[curStart].first && v[curEnd].second > v[curStart].second && dp[curStart] + 1 > dp[curEnd])//end > cur
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
		std::cout << "LISPairs Len_DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxIncrCount << " (" << Debug::ToStr1D<int>()(lis) << ")" << std::endl;
		return maxIncrCount;
	}
};
/*
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 3, 1, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 3, 5, 1, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 3, 5, 4, 1, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 3, 5, 4, 6, 1
1, 1, 2, 3, 3, 2, 2, 1, 3, 2, 4, 3, 5, 4, 6, 5
LISPairs Len_DP1D_Quadratic for "[3,3], [1,0], [5,4], [7,5], [6,7], [8,3], [2,5], [-5,-3], [4,6], [-4,-1], [5,7], [-3,0], [6,8], [-2,1], [7,9], [-1,3]": 6 ([1,0], [2,5], [4,6], [5,7], [6,8], [7,9])
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 3, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 3, 3, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 3, 3, 4, 1, 1, 1, 1
1, 1, 2, 3, 3, 3, 3, 4, 5, 1, 1, 1
1, 1, 2, 3, 3, 3, 3, 4, 5, 6, 1, 1
1, 1, 2, 3, 3, 3, 3, 4, 5, 6, 6, 1
1, 1, 2, 3, 3, 3, 3, 4, 5, 6, 6, 7
LISPairs Len_DP1D_Quadratic for "[1,2], [1,3], [2,3], [4,5], [4,6], [4,6], [4,7], [5,6], [6,7], [10,12], [10,32], [12,32]": 7 ([1,2], [2,3], [4,5], [5,6], [6,7], [10,12], [12,32])
*/
#endif