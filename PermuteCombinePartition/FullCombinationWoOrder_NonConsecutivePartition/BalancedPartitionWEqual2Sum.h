#ifndef BALANCED_PARTITION_W_EQUAL_2_SUM_H
#define BALANCED_PARTITION_W_EQUAL_2_SUM_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=6579701673885696
http://www.geeksforgeeks.org/dynamic-programming-set-18-partition-problem/
http://en.wikipedia.org/wiki/Partition_problem

Determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is same

This is equivalent to find if there exists a subset with targetSum of totalSum/2.
See also CombinationSum.h to find all subsets that have a targetSum of totalSum/2.

1. Recursion: O(2^n) time
2. DP2D: pseudo-polynomial O(n * sum) time
3. This problem can be solved as a special case of BalancedPartitionWMin2SumDiff.h: check if the min 2 sum diff of 2 partitions is equal to 0. O(n * sum) time
*/
class BalancedPartitionWEqual2Sum
{
public:
	BalancedPartitionWEqual2Sum(){}
	~BalancedPartitionWEqual2Sum(){}

	bool Recur(const std::vector<int> & v)
	{
		int N = v.size();
		int totalSum = 0;
		for (int i = 0; i < N; ++i)
			totalSum += v[i];
		bool res;
		std::vector<int> path;
		std::vector<int> result;
		if (totalSum % 2 != 0)//if cumuSum is odd, there cannot be 2 subsets with equal sum
			res = false;
		else
			res = this->recur(v, 0, totalSum / 2, path, result);

		std::cout << "BalancedPartitionWEqual2Sum Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << ", OneSet: " << Debug::ToStr1D<int>()(result) << std::endl;
		return res;
	}
	bool recur(const std::vector<int> & v, int cur, int sum, std::vector<int> & path, std::vector<int> & result)
	{
		int N = v.size();
		if (sum == 0)
		{
			result = path;
			return true;
		}
		if (cur == N)//sum != 0
			return false;
		
		bool exclude = this->recur(v, cur + 1, sum, path, result);//exclude cur element
		bool include = false;
		if (v[cur] <= sum)
		{
			path.push_back(v[cur]);
			include = this->recur(v, cur + 1, sum - v[cur], path, result);//include cur element
			path.pop_back();
		}
		
		return exclude || include;
	}

	bool DP2D(const std::vector<int> & v)
	{
		int N = v.size();
		int totalSum = 0;
		for (int i = 0; i < N; ++i)
			totalSum += v[i];
		bool res;
		if (totalSum % 2 != 0)//if cumuSum is odd, there cannot be 2 subsets with equal sum
		{
			res = false;
		}
		else
		{
			/*this part is similiar to CombinationSum::NumOfWays_NoRepeats_DP2D()*/
			std::vector<std::vector<int> > dp(totalSum / 2 + 1, std::vector<int>(N + 1));

			/*init top row as true*/
			for (int i = 0; i <= N; ++i)
				dp[0][i] = 1;
			/*init leftmost col as false, except dp[0][0]*/
			for (int i = 1; i <= totalSum / 2; ++i)
				dp[i][0] = 0;

			for (int sum = 1; sum <= totalSum / 2; ++sum)
			{
				for (int i = 1; i <= N; ++i)
				{
					/*
					dp[sum][i] = true if a subset of {v[0],v[1],...,v[i-1]} has sum equal to sum
					, otherwise, false
					*/
					int includeCurNum = sum >= v[i - 1] ? dp[sum - v[i - 1]][i - 1] : 0;
					int excludeCurNum = dp[sum][i - 1];
					dp[sum][i] = includeCurNum | excludeCurNum;
				}
			}
			res = dp[totalSum / 2][N] == 1 ? true : false;
			Debug::Print2D<int>()(dp, false);
		}
		
		std::cout << "BalancedPartitionWEqual2Sum DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
};
/*
BalancedPartitionWEqual2Sum Recur for "3, 1, 5, 9, 12": 1, OneSet: 3, 12
BalancedPartitionWEqual2Sum Recur for "1, 5, 11, 5": 1, OneSet: 1, 5, 5
BalancedPartitionWEqual2Sum Recur for "1, 5, 3": 0, OneSet:
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1
Row#1	= 0, 0, 1, 1, 1, 1
Row#2	= 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 1, 1, 1
Row#4	= 0, 0, 1, 1, 1, 1
Row#5	= 0, 0, 0, 1, 1, 1
Row#6	= 0, 0, 0, 1, 1, 1
Row#7	= 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 1, 1, 1
Row#9	= 0, 0, 0, 1, 1, 1
Row#10	= 0, 0, 0, 0, 1, 1
Row#11	= 0, 0, 0, 0, 0, 0
Row#12	= 0, 0, 0, 0, 1, 1
Row#13	= 0, 0, 0, 0, 1, 1
Row#14	= 0, 0, 0, 0, 1, 1
Row#15	= 0, 0, 0, 0, 1, 1

BalancedPartitionWEqual2Sum DP2D for "3, 1, 5, 9, 12": 1
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1
Row#2	= 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0
Row#5	= 0, 0, 1, 1, 1
Row#6	= 0, 0, 1, 1, 1
Row#7	= 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 1
Row#11	= 0, 0, 0, 1, 1

BalancedPartitionWEqual2Sum DP2D for "1, 5, 11, 5": 1
BalancedPartitionWEqual2Sum DP2D for "1, 5, 3": 0
*/
#endif