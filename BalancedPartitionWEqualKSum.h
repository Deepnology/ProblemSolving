#ifndef BALANCED_PARTITION_W_EQUAL_K_SUM_H
#define BALANCED_PARTITION_W_EQUAL_K_SUM_H
#include "Debug.h"
/*
Leetcode: Partition to K Equal Sum Subsets
Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.
Example 1:
Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.

see also BalancedPartitionWEqual2Sum.h
*/
class BalancedPartitionWEqualKSum
{
public:
	BalancedPartitionWEqualKSum() {}

	bool DP1D(std::vector<int> & nums, int k)
	{
		int N = nums.size();
		if (N == 0) return false;
		if (k == 1) return true;
		int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
		if (totalSum % k != 0) return false;
		int sum = totalSum / k;
		int used = 0;//since N <= 16, can use a 32-bit int to record used indices
		std::sort(nums.begin(), nums.end(), std::greater<int>());// for acceleration only !!!
		std::vector<int> dp(1 << N, -1);//record all configurations
		return recurDP(nums, 0, sum, used, dp, 0, k);
	}
private:
	bool recurDP(const std::vector<int> & v, int curSum, int sum, int & used, std::vector<int> & dp, int curK, int k)
	{
		if (curK == k) return dp[used] = 1;//end of 2nd level of recursion
		if (curSum == sum)//end of 1st level of recursion
			return recurDP(v, 0, sum, used, dp, curK + 1, k);//reset curSum, advance curK

		if (dp[used] != -1) return dp[used];
		int N = v.size();
		for (int i = 0; i < N; ++i)
		{
			if (((used >> i) & 1) == 0 && v[i] + curSum <= sum)
			{
				used |= (1 << i);
				if (recurDP(v, curSum + v[i], sum, used, dp, curK, k))
					return true;
				dp[used] = 0;
				used ^= (1 << i);
			}
		}
		return dp[used] = 0;
	}

public:
	bool Greedy(std::vector<int> & nums, int k)
	{
		int N = nums.size();
		if (N == 0) return false;
		if (k == 1) return true;
		int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
		if (totalSum % k != 0) return false;
		int sum = totalSum / k;
		int used = 0;//since N <= 16, can use a 32-bit int to record used indices
		
		std::sort(nums.begin(), nums.end(), std::greater<int>());
		// this greedy approach must always use largest nums first !!!
		// otherwise, need to enumerate all permutations of nums
		while (k--)//greedy
		{
			if (!recur(nums, 0, 0, sum, used))
			{
				return false;
			}
		}
		return true;
	}
private:
	bool recur(const std::vector<int> & v, int cur, int curSum, int sum, int & used)//check if sum can be produced by a subset of v
	{
		int N = v.size();
		if (cur == N)
		{
			if (curSum == sum)
				return true;
			else
				return false;
		}
		if ((used >> cur) & 1)//skip cur (bc DFS will be called for k times)
			return recur(v, cur + 1, curSum, sum, used);

		//start from including the largest num first
		if (curSum + v[cur] <= sum)//include cur
		{
			used |= (1 << cur);
			if (recur(v, cur + 1, curSum + v[cur], sum, used))
				return true;
			used ^= (1 << cur);
		}

		if (recur(v, cur + 1, curSum, sum, used))//exclude cur
			return true;

		return false;
	}
};
#endif
