/*DP*/
#ifndef MAX_SUM_INCR_SUB_SEQ_H
#define MAX_SUM_INCR_SUB_SEQ_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-14-variations-of-lis/
http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/
variation of LIS
Given an array of n positive integers.
Write a program to find the sum of maximum sum subsequence of the given array such that integers in the subsequence are sorted in increasing order.

*/
class MaxSumIncrSubseq
{
public:
	MaxSumIncrSubseq(){}
	~MaxSumIncrSubseq(){}
	
	int DP1D_LowerBound(const std::vector<int> & x)
	{
		/*
		int N = x.size();
		if (N == 1)
			return 1;
		std::vector<int> dp(N, INT_MAX);
		std::vector<int> lis;
		for (int i = 0; i < N; ++i)
		{
			//1. insert x[i] to the first element which does not compare less than x[i] in dp
			std::vector<int>::iterator lb = std::lower_bound(dp.begin(), dp.end(), x[i]);

			if (lb != dp.begin() && *lb == INT_MAX)
				lis.push_back(*(lb - 1));//a. push "prev num of INT_MAX in dp when replacing an INT_MAX" to lis array

			*lb = x[i];//update *lb, which is INT_MAX or existing num, with x[i]
			std::cout << "dp: " << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		//2. the LIS length is the number of all elements before the first INT_MAX
		int res = std::lower_bound(dp.begin(), dp.end(), INT_MAX) - dp.begin();

		lis.push_back(dp[res - 1]);//b. push the last num in dp to lis array

		std::cout << "MaxSumIncrSubseq DP1D LowerBound O(nlogn) for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << " (" << Debug::ToStr1D<int>()(lis) << ")" << std::endl;
		return res;
		*/
		return 0;
	}
	
	int DP1D_Quadratic(const std::vector<int> & x)//O(n^2)
	{
		int N = x.size();
		std::vector<int> dp(N);
		dp[0] = x[0];
		int maxIncrSum = x[0];
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			dp[curEnd] = x[curEnd];
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (x[curEnd] > x[curStart])//end > cur
				{
					dp[curEnd] = std::max(dp[curEnd], dp[curStart] + x[curEnd]);
				}
			}
			maxIncrSum = std::max(dp[curEnd], maxIncrSum);
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::cout << "MaxSumIncrSubseq DP1D Quadratic O(n^2) for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrSum << std::endl;
		return maxIncrSum;
	}
};
/*
5, 110, 0, 0, 0, 0, 0
5, 110, 15, 0, 0, 0, 0
5, 110, 15, 30, 0, 0, 0
5, 110, 15, 30, 130, 0, 0
5, 110, 15, 30, 130, 50, 0
5, 110, 15, 30, 130, 50, 75
MaxSumIncrSubseq DP1D Quadratic O(n^2) for "5, 105, 10, 15, 100, 20, 25": 130
*/
#endif