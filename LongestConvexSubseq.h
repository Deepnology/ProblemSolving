/*DP*/
#ifndef LONGEST_CONVEX_SUBSEQ_H
#define LONGEST_CONVEX_SUBSEQ_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Find the longest nondecreasing subsequence, variant
variation of LIS
http://stackoverflow.com/questions/20664920/longest-convex-subsequence-in-an-array
Define a sequence of numbers[a0, a1, a2, ..., a(n-1)] to be convex if ai < (a(i-1) + a(i+1)) / 2, for 1 <= i <= n-2.
Given an array of numbers A of length n, find a longest subsequence [i0, i1, i2, ..., i(k-1)] such that [A[i0], A[i1], A[i2], ..., A[i(k-1)]] is convex.

Convex property can be transformed to ai - a(i-1) < a(i+1) - ai.
Based on this property, enumerate all possible [start,end] pairs from the input array.
Sort all these pairs by their (end-start) values in ascending order.
For equal (end-start) values, sort by end index in descending order. (BECAUSE we don't want to miss updating any dp[end] from those equal-valued pairs)
For each pair in sorted order, dp[endIdx] = max(dp[endIdx], dp[startIdx]+1), where dp[i] is the length of longest convex subsequence in v[0]~v[i].
The length of the overall longest convex subsequence is the largest value in dp.

DP1D: O(n^2 * log(n^2)) time, O(n^2) space
*/
class LongestConvexSubseq
{
public:
	LongestConvexSubseq(){}
	~LongestConvexSubseq(){}
	typedef std::pair<std::pair<int, int>, std::pair<int, int> > ValIdxPair;
	//first.first: startVal, first.second: startIdx, second.first: endVal, second.second: endIdx

	int DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> dp(N, 1);//longest length at each index (only numbers >= 3 are meaningful)
		std::vector<int> prevIdx(N, -1);
		std::vector<ValIdxPair> p;

		//1. enumerate all the pairs, O(n^2) time
		for (int end = 1; end < N; ++end)
		{
			for (int start = 0; start < end; ++start)
				p.push_back({ { v[start], start }, { v[end], end } });
		}
		std::cout << "ValIdxPairs: " << Debug::ToStr1D<int>()(p) << std::endl;

		//2. sort all the pairs with pair's diffVal in ascending order, O(n^2 * log(n^2)) time
		std::sort(p.begin(), p.end(), [](const ValIdxPair & a, const ValIdxPair & b)->bool
		{
			int diffA = a.second.first - a.first.first;//a.endVal - a.startVal
			int diffB = b.second.first - b.first.first;//b.endVal - b.startVal
			return diffA == diffB ? a.second.second > b.second.second : diffA < diffB;
		});
		std::cout << "AfterSorted: " << Debug::ToStr1D<int>()(p) << std::endl;

		int maxLen = INT_MIN;
		int maxIdx = 0;

		//3. iterate through all pairs in ascending order of pair's diffVal, O(n^2) time
		for (const auto & pair : p)
		{
			if (dp[pair.first.second] + 1 > dp[pair.second.second])//dp[pair.startIdx] + 1 > dp[pair.endIdx]
			{
				dp[pair.second.second] = dp[pair.first.second] + 1;
				prevIdx[pair.second.second] = pair.first.second;
			}

			if (dp[pair.second.second] > maxLen)
			{
				maxLen = dp[pair.second.second];
				maxIdx = pair.second.second;
			}
			std::cout << "dp: " << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::vector<int> lcs(maxLen);
		int maxLen2 = maxLen;
		while (maxLen2-- > 0)
		{
			lcs[maxLen2] = v[maxIdx];
			maxIdx = prevIdx[maxIdx];
		}

		std::cout << "LongestConvexSubseq DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << " (" << Debug::ToStr1D<int>()(lcs) << ")" << std::endl;
		return maxLen;
	}
};
/*
ValIdxPairs: [(1,0),(2,1)], [(1,0),(-1,2)], [(2,1),(-1,2)], [(1,0),(0,3)], [(2,1),(0,3)], [(-1,2),(0,3)], [(1,0),(3,4)], [(2,1),(3,4)], [(-1,2),(3,4)], [(0,3),(3,4)], [(1,0),(8,5)], [(2,1),(8,5)], [(-1,2),(8,5)], [(0,3),(8,5)], [(3,4),(8,5)], [(1,0),(5,6)], [(2,1),(5,6)], [(-1,2),(5,6)], [(0,3),(5,6)], [(3,4),(5,6)], [(8,5),(5,6)]
AfterSorted: [(8,5),(5,6)], [(2,1),(-1,2)], [(2,1),(0,3)], [(1,0),(-1,2)], [(1,0),(0,3)], [(2,1),(3,4)], [(-1,2),(0,3)], [(1,0),(2,1)], [(3,4),(5,6)], [(1,0),(3,4)], [(2,1),(5,6)], [(0,3),(3,4)], [(1,0),(5,6)], [(-1,2),(3,4)], [(0,3),(5,6)], [(3,4),(8,5)], [(-1,2),(5,6)], [(2,1),(8,5)], [(1,0),(8,5)], [(0,3),(8,5)], [(-1,2),(8,5)]
dp: 1, 1, 1, 1, 1, 1, 2
dp: 1, 1, 2, 1, 1, 1, 2
dp: 1, 1, 2, 2, 1, 1, 2
dp: 1, 1, 2, 2, 1, 1, 2
dp: 1, 1, 2, 2, 1, 1, 2
dp: 1, 1, 2, 2, 2, 1, 2
dp: 1, 1, 2, 3, 2, 1, 2
dp: 1, 2, 2, 3, 2, 1, 2
dp: 1, 2, 2, 3, 2, 1, 3
dp: 1, 2, 2, 3, 2, 1, 3
dp: 1, 2, 2, 3, 2, 1, 3
dp: 1, 2, 2, 3, 4, 1, 3
dp: 1, 2, 2, 3, 4, 1, 3
dp: 1, 2, 2, 3, 4, 1, 3
dp: 1, 2, 2, 3, 4, 1, 4
dp: 1, 2, 2, 3, 4, 5, 4
dp: 1, 2, 2, 3, 4, 5, 4
dp: 1, 2, 2, 3, 4, 5, 4
dp: 1, 2, 2, 3, 4, 5, 4
dp: 1, 2, 2, 3, 4, 5, 4
dp: 1, 2, 2, 3, 4, 5, 4
LongestConvexSubseq DP1D for "1, 2, -1, 0, 3, 8, 5": 5 (2, -1, 0, 3, 8)
*/
#endif