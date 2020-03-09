#ifndef SUBSET_SUM_PROBLEM_H
#define SUBSET_SUM_PROBLEM_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/
Given a set of non-negative integers, and a value targetSum.
Determine if there is a subset of the given set with sum equal to given targetSum.

Recur: exponential time
DP2D: O(targetSum * n) time, O(targetSum * n) space
*/
class SubsetSumProblem
{
public:
	SubsetSumProblem(){}
	~SubsetSumProblem(){}

	bool Recur(const std::vector<int> & v, int targetSum)
	{
		bool res = this->inexclude_recur(v, targetSum, 0);
		std::cout << "SubsetSumProblem Recur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	bool inexclude_recur(const std::vector<int> & v, int targetSum, int start)
	{
		if (targetSum == 0)
			return true;
		int N = v.size();
		if (start == N)
			return false;

		bool include = false;
		bool exclude = false;
		if (v[start] <= targetSum)
		{
			include = this->inexclude_recur(v, targetSum - v[start], start + 1);
		}
		exclude = this->inexclude_recur(v, targetSum, start + 1);
		return include || exclude;
	}

public:
	//see also CombinationSum.h: NumOfWays_NoRepeats_FromDupArray_DP2D, CombinationPrimeSum1toN.h
	bool DP2D(const std::vector<int> & v, int targetSum)
	{
		int N = v.size();
		std::vector<std::vector<int> > dp(targetSum + 1, std::vector<int>(N + 1, 0));

		for (int sum = 0; sum <= targetSum; ++sum)
		{
			for (int idx = 0; idx <= N; ++idx)
			{
				if (sum == 0)
					dp[sum][idx] = 1;
				else if (idx == 0)
					dp[sum][idx] = 0;

				else
				{
					int include = 0;
					int exclude = dp[sum][idx - 1];
					if (v[idx - 1] <= sum)
						include = dp[sum - v[idx - 1]][idx - 1];
					dp[sum][idx] = (include || exclude) ? 1 : 0;
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "SubsetSumProblem DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[targetSum][N] << std::endl;
		return dp[targetSum][N] == 1 ? true : false;
	}
};
/*
SubsetSumProblem Recur for "8" in "10, 1, 2, 7, 6, 5, 9, 8": 1
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#3	= 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 1, 1, 1
Row#6	= 0, 0, 0, 0, 0, 1, 1, 1, 1
Row#7	= 0, 0, 0, 0, 1, 1, 1, 1, 1
Row#8	= 0, 0, 0, 0, 1, 1, 1, 1, 1

SubsetSumProblem DP2D for "8" in "10, 1, 2, 7, 6, 5, 9, 8": 1
*/
#endif