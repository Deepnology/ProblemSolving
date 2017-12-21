/*DP*/
#ifndef LONGEST_WEAKLY_ALTERNATING_SUBSEQ_H
#define LONGEST_WEAKLY_ALTERNATING_SUBSEQ_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Find the longest nondecreasing subsequence, variant
variation of LIS
Define a sequence of numbers[a0, a1, a2, ..., a(n-1)] to be weakly alternating if no three consecutive terms in the sequence are increasing or decreasing.
Given an array of numbers A of length n, find a longest subsequence [i0, i1, i2, ..., i(k-1)] such that [A[i0], A[i1], A[i2], ..., A[i(k-1)]] is weakly alternating.

DP1D: O(n^2) time, O(n) space
*/
class LongestWeaklyAlternatingSubseq
{
public:
	LongestWeaklyAlternatingSubseq(){}
	~LongestWeaklyAlternatingSubseq(){}

	int DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> dp(N, 1);//longest length at each index
		std::vector<int> incr(N, 1);//length of consecutive incr sequence ending at each index
		std::vector<int> decr(N, 1);//length of consecutive decr sequence ending at each index
		int maxWAltCount = 1;
		int maxWAltIdx;//the last index of the LAS
		std::vector<int> prevIdx(N, -1);//previous index of LAS at each index
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (v[curStart] > v[curEnd] && decr[curStart] < 2 && dp[curStart] + 1 > dp[curEnd])//count in curStart as prev decr element to curEnd
				{
					dp[curEnd] = dp[curStart] + 1;
					decr[curEnd] = decr[curStart] + 1;
					incr[curEnd] = 1;//reset
					prevIdx[curEnd] = curStart;
				}
				else if (v[curStart] < v[curEnd] && incr[curStart] < 2 && dp[curStart] + 1 > dp[curEnd])//count in curStart as prev incr element to curEnd
				{
					dp[curEnd] = dp[curStart] + 1;
					incr[curEnd] = incr[curStart] + 1;
					decr[curEnd] = 1;//reset
					prevIdx[curEnd] = curStart;
				}
				else if (v[curStart] == v[curEnd] && dp[curStart] + 1 > dp[curEnd])
				{
					dp[curEnd] = dp[curStart] + 1;
					decr[curEnd] = 1;//reset
					incr[curEnd] = 1;//reset
					prevIdx[curEnd] = curStart;
				}
			}

			if (dp[curEnd] > maxWAltCount)
			{
				maxWAltCount = dp[curEnd];
				maxWAltIdx = curEnd;
			}

			std::cout << "dp:   " << Debug::ToStr1D<int>()(dp) << std::endl;
			std::cout << "incr: " << Debug::ToStr1D<int>()(incr) << std::endl;
			std::cout << "decr: " << Debug::ToStr1D<int>()(decr) << std::endl;
		}

		std::vector<int> lwas(maxWAltCount);
		int lwasLen = maxWAltCount;
		while (lwasLen-- > 0)
		{
			lwas[lwasLen] = v[maxWAltIdx];
			maxWAltIdx = prevIdx[maxWAltIdx];
		}
		std::cout << "LongestWeaklyAlternatingSubseq DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxWAltCount << " (" << Debug::ToStr1D<int>()(lwas) << ")" << std::endl;
		return maxWAltCount;
	}
};
/*
dp:   1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 1, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 1, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 9, 1, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 1, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 9, 9, 1
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1
dp:   1, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 9, 9, 10
incr: 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 1
decr: 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2
LongestWeaklyAlternatingSubseq DP1D for "1, 3, 2, 1, 5, 7, 6, 5, 4, 3, 2, 7, 8, 9, 2, 3, 4, 0": 10 (1, 3, 2, 5, 5, 4, 7, 2, 3, 0)
dp:   1, 2, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1
decr: 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 1, 1, 1
decr: 1, 1, 2, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 1, 1, 1
incr: 1, 2, 1, 2, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 1
decr: 1, 1, 2, 1, 2, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 1
incr: 1, 2, 1, 2, 1, 2, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1
dp:   1, 2, 3, 4, 5, 6, 7, 7
incr: 1, 2, 1, 2, 1, 2, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 2
LongestWeaklyAlternatingSubseq DP1D for "1, 11, 2, 10, 4, 5, 2, 1": 7 (1, 11, 2, 10, 4, 5, 2)
dp:   1, 2, 1, 1, 1, 1
incr: 1, 1, 1, 1, 1, 1
decr: 1, 2, 1, 1, 1, 1
dp:   1, 2, 3, 1, 1, 1
incr: 1, 1, 2, 1, 1, 1
decr: 1, 2, 1, 1, 1, 1
dp:   1, 2, 3, 4, 1, 1
incr: 1, 1, 2, 1, 1, 1
decr: 1, 2, 1, 2, 1, 1
dp:   1, 2, 3, 4, 4, 1
incr: 1, 1, 2, 1, 1, 1
decr: 1, 2, 1, 2, 2, 1
dp:   1, 2, 3, 4, 4, 4
incr: 1, 1, 2, 1, 1, 1
decr: 1, 2, 1, 2, 2, 2
LongestWeaklyAlternatingSubseq DP1D for "12, 11, 13, 5, 3, 1": 4 (12, 11, 13, 5)
dp:   1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 1, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 1, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
dp:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
incr: 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2
decr: 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1
LongestWeaklyAlternatingSubseq DP1D for "0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15": 16 (0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15)
*/
#endif