/*Greedy*DP*/
#ifndef LBS_H
#define LBS_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Longest Bitonic Subsequence
Elements of programming interview, DynamicProgramming: Find the longest nondecreasing subsequence, variant
http://www.geeksforgeeks.org/dynamic-programming-set-15-longest-bitonic-subsequence/
Given an array of integers, find the longest bitonic subsequence.
A sequence is bitonic if it is initially increasing then decreasing.

Define a sequence of numbers [a0,a1,a2,...,a(n-1)] to be bitonic if there exists k such that
ai < a(i+1), for 0 <= i < k and ai > a(i+1), for k <= i < n-1.

Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)

Input arr[] = {12, 11, 13, 5, 3, 1}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)

Input arr[] = {80, 60, 30, 40, 20, 10}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)

LenOfLBS[i] = LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1

Greedy_LowerBound: O(nlogn) time, O(n) space
DP1D_Quadratic: O(n^2) time, O(n) space

See also LIS.h
*/
class LBS
{
public:
	LBS(){}
	~LBS(){}

	int Len_Greedy_LowerBound(const std::vector<int> & v)
	{
		int N = v.size();

		/*1. compute LenOfLIS from left to right*/
		std::vector<int> LenOfLIS_Left(N);
		std::vector<int> dp;
		for (int i = 0; i < N; ++i)
		{
			std::vector<int>::iterator lb = std::lower_bound(dp.begin(), dp.end(), v[i]);
			if (lb == dp.end())
				dp.push_back(v[i]);
			else
				*lb = v[i];
			LenOfLIS_Left[i] = dp.size();
		}

		/*2. compute LenOfLIS from right to left*/
		std::vector<int> LenOfLIS_Right(N);
		std::vector<int> dp2;
		for (int i = N - 1; i >= 0; --i)
		{
			std::vector<int>::iterator lb = std::lower_bound(dp2.begin(), dp2.end(), v[i]);
			if (lb == dp2.end())
				dp2.push_back(v[i]);
			else
				*lb = v[i];
			LenOfLIS_Right[i] = dp2.size();
		}

		/*3. LenOfLBS[i] = LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1*/
		int maxLen = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			if (LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1 > maxLen)
				maxLen = LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1;
		}

		std::cout << Debug::ToStr1D<int>()(LenOfLIS_Left) << std::endl;
		std::cout << Debug::ToStr1D<int>()(LenOfLIS_Right) << std::endl;
		std::cout << "LBS Len_Greedy_LowerBound for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << std::endl;
		return maxLen;
	}

	int Len_DP1D_Quadratic(const std::vector<int> & v)
	{
		int N = v.size();

		/*1. compute LenOfLIS from left to right*/
		std::vector<int> LenOfLIS_Left(N, 1);
		std::vector<int> dp(N, 1);
		for (int end = 1; end < N; ++end)
		{
			for (int start = 0; start < end; ++start)
			{
				if (v[end] > v[start] && dp[start] + 1 > dp[end])
					dp[end] = dp[start] + 1;
			}
			LenOfLIS_Left[end] = std::max(LenOfLIS_Left[end - 1], dp[end]);
		}

		/*2. compute LenOfLIS from right to left*/
		std::vector<int> LenOfLIS_Right(N, 1);
		std::vector<int> dp2(N, 1);
		for (int end = N - 2; end >= 0; --end)
		{
			for (int start = N - 1; start > end; --start)
			{
				if (v[end] > v[start] && dp2[start] + 1 > dp2[end])
					dp2[end] = dp2[start] + 1;
			}
			LenOfLIS_Right[end] = std::max(LenOfLIS_Right[end + 1], dp2[end]);
		}

		/*3. LenOfLBS[i] = LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1*/
		int maxLen = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			if (LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1 > maxLen)
				maxLen = LenOfLIS_Left[i] + LenOfLIS_Right[i] - 1;
		}

		std::cout << Debug::ToStr1D<int>()(LenOfLIS_Left) << std::endl;
		std::cout << Debug::ToStr1D<int>()(LenOfLIS_Right) << std::endl;
		std::cout << "LBS Len_DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << std::endl;
		return maxLen;
	}
};
/*
1, 1, 2, 3, 3, 4, 4, 4
3, 3, 3, 3, 2, 2, 1, 1
LBS Len_Greedy_LowerBound for "3, 1, 5, 7, 6, 8, 2, 4": 5
1, 1, 2, 3, 3, 4, 4, 4
3, 3, 3, 3, 2, 2, 1, 1
LBS Len_DP1D_Quadratic for "3, 1, 5, 7, 6, 8, 2, 4": 5
1, 2, 2, 3, 3, 4, 4, 4
5, 5, 4, 4, 3, 3, 2, 1
LBS Len_Greedy_LowerBound for "1, 11, 2, 10, 4, 5, 2, 1": 6
1, 2, 2, 3, 3, 4, 4, 4
5, 5, 4, 4, 3, 3, 2, 1
LBS Len_DP1D_Quadratic for "1, 11, 2, 10, 4, 5, 2, 1": 6
1, 1, 2, 2, 2, 2
5, 4, 4, 3, 2, 1
LBS Len_Greedy_LowerBound for "12, 11, 13, 5, 3, 1": 5
1, 1, 2, 2, 2, 2
5, 4, 4, 3, 2, 1
LBS Len_DP1D_Quadratic for "12, 11, 13, 5, 3, 1": 5
1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6
5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 1, 1
LBS Len_Greedy_LowerBound for "0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15": 7
1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6
5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 1, 1
LBS Len_DP1D_Quadratic for "0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15": 7
*/
#endif