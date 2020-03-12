#ifndef _COMBINATION_SUM_
#define _COMBINATION_SUM_
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
AKA SubsetSum
Elements of programming interview, DynamicProgramming:
Count the number of score combinations: NumOfWays_AllowRepeats_FromNoDupArray_DP1D, NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D
Count the number of steps in a board game: NumOfDistinctOrderWays_AllowRepeats_From1tok_DP1D
Test if a tie is possible: NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups
Leetcode: Combination Sum
Given a set of candidate numbers (C) and a targetSum number (T),
find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.
Note:
All numbers (including targetSum) will be positive integers.
Elements in a combination (a1, a2, ..., ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and targetSum 7,
A solution set is:
[7]
[2, 2, 3]

Leetcode: Combination Sum II
Given a collection of candidate numbers (C) and a targetSum number (T),
find all unique combinations in C where the candidate numbers sums to T.
Each number in C may only be used once in the combination.
Note:
All numbers (including targetSum) will be positive integers.
Elements in a combination (a1, a2, ..., ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and targetSum 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]

Leetcode: Combination Sum III (FindAllUnique_NoRepeats_FromDupArray_FixRecur/InExcludeRecur with one more constraint: K numbers, see also KSum.h)
Find all possible combinations of k numbers that add up to a number n,
given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
Example 1:
Input: k = 3, n = 7
Output:
[[1,2,4]]
Example 2:
Input: k = 3, n = 9
Output:
[[1,2,6], [1,3,5], [2,3,4]]

Leetcode: Combination Sum IV (NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D)
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.
Example:
nums = [1, 2, 3]
target = 4
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
Therefore the output is 7.
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

Lettcode: Coin Change II (NumOfWays_AllowRepeats_FromNoDupArray_DP1D)
You are given coins of different denominations and a total amount of money.
Write a function to compute the number of combinations that make up that amount.
You may assume that you have infinite number of each kind of coin.

Leetcode: Coin Change (Min Coin Problem)
You are given coins of different denominations and a total amount of money amount.
Write a function to compute the fewest number of coins that you need to make up that amount.
If that amount of money cannot be made up by any combination of the coins, return -1.
Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)
Example 2:
coins = [2], amount = 3
return -1.
Note:
You may assume that you have an infinite number of each kind of coin.

Greedy algorithm does not always give you minimum number of coins. 
Consider sum as 40, and coins as {1, 5, 10, 20, 25}.
Greedy algorithm will give:{25, 10, 5}. 
However the correct answer is {20, 20}. 
So dynamic programming is the way to solve this.

Leetcode: Partition Equal Subset Sum (special case of NumOfWays_NoRepeats_FromDupArray w/ targetSum==totalSum/2)
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
*/
class CombinationSum
{
public:
	CombinationSum(){}
	~CombinationSum(){}

	std::vector<std::vector<int>> FindAllUnique_AllowRepeats_FromNoDupArray_FixRecur(std::vector<int> && nums, int targetSum)//nums are all supposed to be unique
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int>> res;
		std::vector<int> path;
		this->FixRecur_AllowRepeats_FromNoDupArray(nums, targetSum, 0, path, res);//all possible ways to pick(combine) ANY COUNT of numbers from nums[0]~nums[N-1]

		std::cout << "CombinationSum FindAllUnique_AllowRepeats_FromNoDupArray_FixRecur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur_AllowRepeats_FromNoDupArray(std::vector<int> & nums, int targetSum, int start
		, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (targetSum == 0)//found a combination path
		{
			res.push_back(path);
			return;
		}

		int N = nums.size();
		for (int index = start; index < N; ++index)//next pick(combine) one number from nums[start]~nums[N-1]
		{
			if (nums[index] > targetSum)
				continue;

			path.push_back(nums[index]);
			this->FixRecur_AllowRepeats_FromNoDupArray(nums, targetSum - nums[index], index, path, res);//all possible ways to pick(combine) ANY COUNT of numbers from nums[index]~nums[N-1] (AllowRepeats: takes "index" instead of "index+1")
			path.pop_back();
		}
	}
public:
	std::vector<std::vector<int>> FindAllUnique_AllowRepeats_FromNoDupArray_InExcludeRecur(std::vector<int> && nums, int targetSum)//nums are all supposed to be unique
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int>> res;
		std::vector<int> path;
		this->InExcludeRecur_AllowRepeats_FromNoDupArray(nums, targetSum, 0, path, res);//all possible ways to pick(combine) ANY COUNT of numbers from nums[0]~nums[N-1]

		std::cout << "CombinationSum FindAllUnique_AllowRepeats_FromNoDupArray_InExcludeRecur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur_AllowRepeats_FromNoDupArray(std::vector<int> & nums, int targetSum, int start
		, std::vector<int> & path, std::vector<std::vector<int>> & res)
	{
		if (targetSum == 0)//found a combination path
		{
			res.push_back(path);
			return;
		}

		int N = nums.size();
		if (start == N)
			return;

		if (nums[start] <= targetSum)
		{
			//1. include current element
			path.push_back(nums[start]);
			this->InExcludeRecur_AllowRepeats_FromNoDupArray(nums, targetSum - nums[start], start, path, res);//(AllowRepeats: takes "start" instead of "start+1")
			path.pop_back();
		}
		//2. exclude current element
		this->InExcludeRecur_AllowRepeats_FromNoDupArray(nums, targetSum, start + 1, path, res);
	}

public:
	std::vector<std::vector<int>> FindAllUnique_NoRepeats_FromDupArray_FixRecur(std::vector<int> && nums, int targetSum)//nums might have duplicates
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int>> res;
		std::vector<int> path;
		this->FixRecur_NoRepeats_FromDupArray(nums, targetSum, 0, path, res);

		std::cout << "CombinationSum FindAllUnique_NoRepeats_FromDupArray_FixRecur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur_NoRepeats_FromDupArray(std::vector<int> & nums, int targetSum, int start
		, std::vector<int> & path, std::vector<std::vector<int>> & res)
	{
		if (targetSum == 0)
		{
			res.push_back(path);
			return;
		}

		int N = nums.size();
		for (int index = start; index < N; ++index)//next pick(combine) one number from nums[start]~nums[N-1]
		{
			if (index > start && nums[index] == nums[index - 1])
				continue;//skip duplicates because nums might have duplicates (nums was already sorted)

			if (nums[index] > targetSum)
				continue;

			path.push_back(nums[index]);
			this->FixRecur_NoRepeats_FromDupArray(nums, targetSum - nums[index], index + 1, path, res);//take index+1 to not allow repeats
			path.pop_back();
		}
	}
public:
	std::vector<std::vector<int>> FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur(std::vector<int> && nums, int targetSum)//nums might have duplicates
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int>> res;
		std::vector<int> path;
		this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum, 0, path, res);

		std::cout << "CombinationSum FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur_NoRepeats_FromDupArray(std::vector<int> & nums, int targetSum, int start
		, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (targetSum == 0)
		{
			res.push_back(path);
			return;
		}
		int N = nums.size();
		if (start == N)
			return;

		if (nums[start] <= targetSum)
		{
			//1. include current element
			path.push_back(nums[start]);
			this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum - nums[start], start + 1, path, res);//take start+1 to not allow repeats
			path.pop_back();
		}
		//2. exclude current element and all duplicates (See Subsets.h for another approach to skip duplicates)
		int stride = 1;
		while (start + stride < N && nums[start] == nums[start + stride])
			++stride;
		this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum, start + stride, path, res);
	}


	//Num Of Ways Problem
public:
	int NumOfWays_AllowRepeats_FromNoDupArray_Recur(std::vector<int> && nums, int targetSum)
	{
		std::sort(std::begin(nums), std::end(nums));
		int res = this->numOfWays_Recur_AllowRepeats_FromNoDupArray(nums, targetSum, 0);
		std::cout << "CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_Recur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << res << std::endl;
		return res;
	}
private:
	int numOfWays_Recur_AllowRepeats_FromNoDupArray(std::vector<int> & nums, int targetSum, int start)
	{
		if (targetSum == 0)
			return 1;

		int N = nums.size();
		int res = 0;
		for (int index = start; index < N; ++index)
		{
			if (nums[index] > targetSum)
				continue;

			res += this->numOfWays_Recur_AllowRepeats_FromNoDupArray(nums, targetSum - nums[index], index);
		}
		return res;
	}
public:
	int NumOfWays_NoRepeats_FromDupArray_Recur(std::vector<int> && nums, int targetSum)
	{
		std::sort(std::begin(nums), std::end(nums));
		int res = this->numOfWays_Recur_NoRepeats_FromDupArray(nums, targetSum, 0);
		std::cout << "CombinationSum NumOfWays_NoRepeats_FromDupArray_Recur for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\" are: " << res << std::endl;
		return res;
	}
private:
	int numOfWays_Recur_NoRepeats_FromDupArray(std::vector<int> & nums, int targetSum, int start)
	{
		if (targetSum == 0)
			return 1;

		int N = nums.size();
		int res = 0;
		for (int index = start; index < N; ++index)
		{
			if (index > start && nums[index] == nums[index - 1])
				continue;

			if (nums[index] > targetSum)
				continue;

			res += this->numOfWays_Recur_NoRepeats_FromDupArray(nums, targetSum - nums[index], index + 1);
		}
		return res;
	}

public:
	int NumOfWays_AllowRepeats_FromNoDupArray_DP2D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<int>> dp(targetSum + 1, std::vector<int>(N + 1, 0));
		/*
		dp[curSumY][curNumX]: count of ways for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curSumY == 0 && curNumX == 0)
					dp[curSumY][curNumX] = 1;
				else if (curSumY == 0)//(first row) sum is 0: we can always select nothing, so it's a valid one way
					dp[curSumY][curNumX] = 1;
				else if (curNumX == 0)//(first column) sum is not 0, but select nothing: impossible (no way)
					dp[curSumY][curNumX] = 0;

				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = dp[curSumY - nums[curNumX - 1]][curNumX]//include nums[curNumX-1] (curNumX for AllowRepeats, see also Knapsack.h)
						+ dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum][N] << std::endl;
		return dp[targetSum][N];
	}
	int NumOfWays_AllowRepeats_FromNoDupArray_DP1D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<int> dp(targetSum + 1, 0);
		/*
		dp[curSum]: count of ways for curSum in nums[0:N-1]
		when curSum == 0, the count of ways in nums[0:N-1] is 1
		*/
		dp[0] = 1;
		for (int curNum = 0; curNum < N; ++curNum)
		{
			for (int curSum = nums[curNum]; curSum <= targetSum; ++curSum)//incrementing
			{
				dp[curSum] += dp[curSum - nums[curNum]];
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum] << std::endl;
		return dp[targetSum];
	}
	int NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D(const std::vector<int> & nums, int targetSum)//Special, see also Permutations2.h for recursion, elements of programming interview
	{
		int N = nums.size();
		std::vector<int> dp(targetSum + 1, 0);
		/*
		dp[curSum]: count of DISTINCT ORDER (permutation) ways for curSum in nums[0:N-1]
		when curSum == 0, the count of DISTINCT ORDER (permutation) ways in nums[0:N-1] is 1
		*/
		dp[0] = 1;
		for (int curSum = 0; curSum <= targetSum; ++curSum)//reversed nested loop
		{
			for (int curNum = 0; curNum < N; ++curNum)
			{
				if (nums[curNum] <= curSum)
					dp[curSum] += dp[curSum - nums[curNum]];
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum] << std::endl;
		return dp[targetSum];
	}
	int NumOfDistinctOrderWays_AllowRepeats_From1tok_DP1D(int k, int targetSum)//need to understand, see also Permutations2.h for recursion, elements of programming interview
	{
		int res;
		if (targetSum <= 1)
			res = 1;
		else
		{
			std::vector<int> dp(k + 1, 0);
			dp[0] = dp[1] = 1;
			for (int curSum = 2; curSum <= targetSum; ++curSum)
			{
				dp[curSum % (k + 1)] = 0;
				for (int curNum = 1; curNum <= k && curSum - curNum >= 0; ++curNum)
				{
					dp[curSum % (k + 1)] += dp[(curSum - curNum) % (k + 1)];
				}
			}
			res = dp[targetSum % (k + 1)];
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		
		std::cout << "CombinationSum NumOfDistinctOrderWays_AllowRepeats_From1tok_DP1D for \"" << targetSum << "\" in \"1..." << k << "\": " << res << std::endl;
		return res;
	}

	int NumOfWays_NoRepeats_FromDupArray_DP2D(std::vector<int> && nums, int targetSum)
	{
		std::sort(nums.begin(), nums.end());//sort is only required to skip duplicated numbers
		int N = nums.size();
		std::vector<std::vector<int>> dp(targetSum + 1, std::vector<int>(N + 1, 0));
		/*
		dp[curSumY][curNumX]: count of ways for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curSumY == 0 && curNumX == 0)
					dp[curSumY][curNumX] = 1;
				else if (curSumY == 0)//(first row) sum is 0: we can always select nothing, so it's a valid one way
					dp[curSumY][curNumX] = 1;
				else if (curNumX == 0)//(first column) sum is not 0, but select nothing: impossible (no way)
					dp[curSumY][curNumX] = 0;

				/*
				nums[curNumX-1] is a duplicate of nums[curNumX-2]
				(if there is no duplicates in nums, we can skip this condition)
				*/
				else if (curNumX >= 2 && nums[curNumX - 1] == nums[curNumX - 2])
				{
					int dupBegin = curNumX - 1;
					while (dupBegin > 0 && nums[dupBegin] == nums[dupBegin - 1])
						--dupBegin;
					int dupCount = (curNumX - 1) - dupBegin + 1;
					
					int countIncludeThis = (curSumY - nums[curNumX - 1] * dupCount >= 0) ? dp[curSumY - nums[curNumX - 1] * dupCount][dupBegin] : 0;//include nums[curNumX-1]
					int countExcludeThis = dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
					dp[curSumY][curNumX] = countIncludeThis + countExcludeThis;
				}

				/*general case for current number num[curNumX-1]*/
				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = dp[curSumY - nums[curNumX - 1]][curNumX - 1]//include nums[curNumX-1] (curNumX-1 for NoRepeats, see also Knapsack.h)
						+ dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum][N] << std::endl;
		return dp[targetSum][N];
	}
	int NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<int>> dp(targetSum + 1, std::vector<int>(N + 1, 0));
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curSumY == 0 && curNumX == 0)
					dp[curSumY][curNumX] = 1;
				else if (curSumY == 0)//(first row) sum is 0: we can always select nothing, so it's a valid one way
					dp[curSumY][curNumX] = 1;
				else if (curNumX == 0)//(first column) sum is not 0, but select nothing: impossible (no way)
					dp[curSumY][curNumX] = 0;

				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = dp[curSumY - nums[curNumX - 1]][curNumX - 1]//include nums[curNumX-1] (curNumX-1 for NoRepeats, see also Knapsack.h)
						+ dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude nums[curNumX-1]
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum][N] << std::endl;
		return dp[targetSum][N];
	}
	int NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<int> dp(targetSum + 1, 0);
		/*
		dp[curSum]: count of ways for curSum in nums[0:N-1]
		when curSum == 0, the count of ways in nums[0:N-1] is 1
		*/
		dp[0] = 1;
		for (int curNum = 0; curNum < N; ++curNum)
		{
			for (int curSum = targetSum; curSum >= nums[curNum]; --curSum)//decrementing
			{
				dp[curSum] += dp[curSum - nums[curNum]];
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "CombinationSum NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum] << std::endl;
		return dp[targetSum];
	}
	int NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups(const std::vector<int> & nums, int targetSum)//not working now
	{
		int N = nums.size();
		std::vector<int> dp(targetSum + 1, 0);
		/*
		dp[curSum]: count of DISTINCT ORDER (permutation) ways for curSum in nums[0:N-1]
		when curSum == 0, the count of DISTINCT ORDER (permutation) ways in nums[0:N-1] is 1
		*/
		dp[0] = 1;
		for (int curSum = targetSum; curSum >= 0; --curSum)//reversed nested loop, decrementing
		{
			for (int curNum = 0; curNum < N; ++curNum)
			{
				if (nums[curNum] <= curSum)
					dp[curSum] += dp[curSum - nums[curNum]];
			}
		}
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "CombinationSum NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum] << std::endl;
		return dp[targetSum];
	}


	//Min Coins Problem
	int MinCoins_AllowRepeats_FromNoDupArray_DP2D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<long long>> dp(targetSum + 1, std::vector<long long>(N + 1, INT_MAX));
		/*
		dp[curSumY][curNumX]: min coins of nums for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curNumX == 0 && curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curNumX == 0)
					dp[curSumY][curNumX] = INT_MAX;
				else if (curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = std::min(1 + dp[curSumY - nums[curNumX - 1]][curNumX],//include this
						dp[curSumY][curNumX - 1]);//exclude this
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude this
				}
			}
		}
		Debug::Print2D<long long>()(dp, false);
		std::cout << "CombinationSum MinCoins_AllowRepeats_FromNoDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum][N] << std::endl;
		return (int)dp[targetSum][N];
	}
	int MinCoins_NoRepeats_FromDupArray_DP2D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<long long>> dp(targetSum + 1, std::vector<long long>(N + 1, INT_MAX));
		/*
		dp[curSumY][curNumX]: min coins of nums for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curNumX == 0 && curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curNumX == 0)
					dp[curSumY][curNumX] = INT_MAX;
				else if (curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = std::min(1 + dp[curSumY - nums[curNumX - 1]][curNumX - 1],//include this
						dp[curSumY][curNumX - 1]);//exclude this
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude this
				}
			}
		}
		Debug::Print2D<long long>()(dp, false);
		std::cout << "CombinationSum MinCoins_NoRepeats_FromDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[targetSum][N] << std::endl;
		return (int)dp[targetSum][N];
	}
	int MinCoins_AllowRepeats_FromNoDupArray_DP1D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<long long> dp(targetSum + 1, INT_MAX);
		dp[0] = 0;
		for (int idx = 0; idx < N; ++idx)
		{
			for (int sum = nums[idx]; sum <= targetSum; ++sum)//incrementing
			{
				dp[sum] = std::min(dp[sum - nums[idx]] + 1, dp[sum]);
			}
		}
		std::cout << Debug::ToStr1D<long long>()(dp) << std::endl;
		std::cout << "CombinationSum MinCoins_AllowRepeats_FromDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << (dp[targetSum] == INT_MAX ? -1 : dp[targetSum]) << std::endl;
		return (int)(dp[targetSum] == INT_MAX ? -1 : dp[targetSum]);
	}
	int MinCoins_NoRepeats_FromDupArray_DP1D(const std::vector<int> & nums, int targetSum)
	{
		int N = nums.size();
		std::vector<long long> dp(targetSum + 1, INT_MAX);
		dp[0] = 0;
		for (int idx = 0; idx < N; ++idx)
		{
			for (int sum = targetSum; sum >= nums[idx]; --sum)//decrementing
			{
				dp[sum] = std::min(dp[sum - nums[idx]] + 1, dp[sum]);
			}
		}
		std::cout << Debug::ToStr1D<long long>()(dp) << std::endl;
		std::cout << "CombinationSum MinCoins_NoRepeats_FromDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << (dp[targetSum] == INT_MAX ? -1 : dp[targetSum]) << std::endl;
		return (int)(dp[targetSum] == INT_MAX ? -1 : dp[targetSum]);
	}
	

	//Min Cost Problem
	int MinCost_AllowRepeats_FromNoDupArray_DP2D(const std::vector<int> & nums, const std::vector<int> & costs, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<long long>> dp(targetSum + 1, std::vector<long long>(N + 1, INT_MAX));
		/*
		dp[curSumY][curNumX]: min cost of nums for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curNumX == 0 && curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curNumX == 0)
					dp[curSumY][curNumX] = INT_MAX;
				else if (curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = std::min(costs[curNumX - 1] + dp[curSumY - nums[curNumX - 1]][curNumX],//include this
						dp[curSumY][curNumX - 1]);//exclude this
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude this
				}
			}
		}
		Debug::Print2D<long long>()(dp, false);
		std::cout << "CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\", \"" << Debug::ToStr1D<int>()(costs) << "\": " << dp[targetSum][N] << std::endl;
		return (int)dp[targetSum][N];
	}
	int MinCost_NoRepeats_FromDupArray_DP2D(const std::vector<int> & nums, const std::vector<int> & costs, int targetSum)
	{
		int N = nums.size();
		std::vector<std::vector<long long>> dp(targetSum + 1, std::vector<long long>(N + 1, INT_MAX));
		/*
		dp[curSumY][curNumX]: min cost of nums for curSumY in nums[0:curNumX-1]
		*/
		for (int curSumY = 0; curSumY <= targetSum; ++curSumY)
		{
			for (int curNumX = 0; curNumX <= N; ++curNumX)
			{
				if (curNumX == 0 && curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curNumX == 0)
					dp[curSumY][curNumX] = INT_MAX;
				else if (curSumY == 0)
					dp[curSumY][curNumX] = 0;
				else if (curSumY - nums[curNumX - 1] >= 0)
				{
					dp[curSumY][curNumX] = std::min(costs[curNumX - 1] + dp[curSumY - nums[curNumX - 1]][curNumX - 1],//include this
						dp[curSumY][curNumX - 1]);//exclude this
				}
				else
				{
					dp[curSumY][curNumX] = dp[curSumY][curNumX - 1];//exclude this
				}
			}
		}
		Debug::Print2D<long long>()(dp, false);
		std::cout << "CombinationSum MinCost_NoRepeats_FromDupArray_DP2D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\", \"" << Debug::ToStr1D<int>()(costs) << "\": " << dp[targetSum][N] << std::endl;
		return (int)dp[targetSum][N];
	}
	int MinCost_AllowRepeats_FromNoDupArray_DP1D(const std::vector<int> & nums, const std::vector<int> & costs, int targetSum)
	{
		int N = nums.size();
		std::vector<long long> dp(targetSum + 1, INT_MAX);
		dp[0] = 0;
		for (int idx = 0; idx < N; ++idx)
		{
			for (int sum = nums[idx]; sum <= targetSum; ++sum)//incrementing
			{
				dp[sum] = std::min(dp[sum - nums[idx]] + costs[idx], dp[sum]);
			}
		}
		std::cout << Debug::ToStr1D<long long>()(dp) << std::endl;
		std::cout << "CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\", \"" << Debug::ToStr1D<int>()(costs) << "\": " << dp[targetSum] << std::endl;
		return (int)dp[targetSum];
	}
	int MinCost_NoRepeats_FromDupArray_DP1D(const std::vector<int> & nums, const std::vector<int> & costs, int targetSum)
	{
		int N = nums.size();
		std::vector<long long> dp(targetSum + 1, INT_MAX);
		dp[0] = 0;
		for (int idx = 0; idx < N; ++idx)
		{
			for (int sum = targetSum; sum >= nums[idx]; --sum)//decrementing
			{
				dp[sum] = std::min(dp[sum - nums[idx]] + costs[idx], dp[sum]);
			}
		}
		std::cout << Debug::ToStr1D<long long>()(dp) << std::endl;
		std::cout << "CombinationSum MinCost_NoRepeats_FromDupArray_DP1D for \"" << targetSum << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\", \"" << Debug::ToStr1D<int>()(costs) << "\": " << dp[targetSum] << std::endl;
		return (int)dp[targetSum];
	}
};
/*
CombinationSum FindAllUnique_AllowRepeats_FromNoDupArray_FixRecur for "8" in "1, 2, 5, 6, 7, 8, 9, 10" are: [1,1,1,1,1,1,1,1], [1,1,1,1,1,1,2], [1,1,1,1,2,2], [1,1,1,5], [1,1,2,2,2], [1,1,6], [1,2,5], [1,7], [2,2,2,2], [2,6], [8]
CombinationSum FindAllUnique_AllowRepeats_FromNoDupArray_InExcludeRecur for "8" in "1, 2, 5, 6, 7, 8, 9, 10" are: [1,1,1,1,1,1,1,1], [1,1,1,1,1,1,2], [1,1,1,1,2,2], [1,1,1,5], [1,1,2,2,2], [1,1,6], [1,2,5], [1,7], [2,2,2,2], [2,6], [8]
CombinationSum FindAllUnique_NoRepeats_FromDupArray_FixRecur for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10" are: [1,1,6], [1,2,5], [1,7], [2,6], [8]
CombinationSum FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10" are: [1,1,6], [1,2,5], [1,7], [2,6], [8]
CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_Recur for "8" in "1, 2, 5, 6, 7, 8, 9, 10" are: 11
CombinationSum NumOfWays_NoRepeats_FromDupArray_Recur for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10" are: 5
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 1, 2, 2, 2, 2, 2, 2, 2
Row#3	= 0, 1, 2, 2, 2, 2, 2, 2, 2
Row#4	= 0, 1, 3, 3, 3, 3, 3, 3, 3
Row#5	= 0, 1, 3, 4, 4, 4, 4, 4, 4
Row#6	= 0, 1, 4, 5, 6, 6, 6, 6, 6
Row#7	= 0, 1, 4, 6, 7, 8, 8, 8, 8
Row#8	= 0, 1, 5, 7, 9, 10, 11, 11, 11

CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_DP2D for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 11
1, 1, 2, 2, 3, 4, 6, 8, 11
CombinationSum NumOfWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 11
1, 1, 1, 1, 1, 1, 1, 1, 1
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1": 1 ([1,1,1,1,1,1,1,1] = 8!/8! = 1)
1, 1, 2, 3, 5, 8, 13, 21, 34
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2": 34 ([1,1,1,1,1,1,2] = 7!/(6!*1!) = 7, [1,1,1,1,2,2] = 6!/(4!*2!) = 15, [1,1,2,2,2] = 5!/(2!*3!) = 10, [2,2,2,2] = 4!/4! = 1)
1, 1, 2, 3, 5, 9, 15, 26, 44
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5": 44 ([1,1,1,5] = 4!/(3!*1!) = 4, [1,2,5] = 3!/(1!*1!*1*) = 6)
1, 1, 2, 3, 5, 9, 16, 28, 49
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6": 49
1, 1, 2, 3, 5, 9, 16, 29, 51
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6, 7": 51
1, 1, 2, 3, 5, 9, 16, 29, 52
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6, 7, 8": 52
1, 1, 2, 3, 5, 9, 16, 29, 52
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6, 7, 8, 9": 52
1, 1, 2, 3, 5, 9, 16, 29, 52
CombinationSum NumOfDistinctOrderWays_AllowRepeats_FromNoDupArray_DP1D for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 52
3, 5, 2
CombinationSum NumOfDistinctOrderWays_AllowRepeats_From1tok_DP1D for "4" in "1...2": 5
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 2, 2, 2, 2, 2, 2, 2
Row#3	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#5	= 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#6	= 0, 0, 0, 0, 1, 2, 2, 2, 2, 2
Row#7	= 0, 0, 0, 0, 2, 3, 4, 4, 4, 4
Row#8	= 0, 0, 0, 0, 1, 3, 4, 5, 5, 5

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10": 5
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 2, 2, 2, 2, 2, 2, 2, 2
Row#2	= 0, 0, 1, 2, 2, 2, 2, 2, 2, 2
Row#3	= 0, 0, 0, 2, 2, 2, 2, 2, 2, 2
Row#4	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#5	= 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#6	= 0, 0, 0, 0, 2, 3, 3, 3, 3, 3
Row#7	= 0, 0, 0, 0, 2, 4, 5, 5, 5, 5
Row#8	= 0, 0, 0, 0, 2, 4, 6, 7, 7, 7

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10": 7
1, 2, 2, 2, 1, 1, 3, 5, 7
CombinationSum NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10": 7
1, 2, 1, 0, 0, 1, 1, 1, 1
CombinationSum NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 1, 2, 5, 6, 7, 8, 9, 10": 1
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#3	= 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#6	= 0, 0, 0, 1, 2, 2, 2, 2, 2
Row#7	= 0, 0, 0, 1, 2, 3, 3, 3, 3
Row#8	= 0, 0, 0, 1, 2, 3, 4, 4, 4

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 4
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#3	= 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 1, 1, 1, 1, 1, 1
Row#6	= 0, 0, 0, 1, 2, 2, 2, 2, 2
Row#7	= 0, 0, 0, 1, 2, 3, 3, 3, 3
Row#8	= 0, 0, 0, 1, 2, 3, 4, 4, 4

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 4
1, 1, 1, 1, 0, 1, 2, 3, 4
CombinationSum NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 4
1, 1, 1, 0, 0, 1, 1, 1, 1
CombinationSum NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 2, 5, 6, 7, 8, 9, 10": 1
===
CombinationSum FindAllUnique_NoRepeats_FromDupArray_FixRecur for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10" are: [1,1,2,2,2], [1,1,3,3], [1,1,6], [1,2,2,3], [1,2,5], [1,7], [2,3,3], [2,6], [3,5], [8]
CombinationSum FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10" are: [1,1,2,2,2], [1,1,3,3], [1,1,6], [1,2,2,3], [1,2,5], [1,7], [2,3,3], [2,6], [3,5], [8]
CombinationSum NumOfWays_NoRepeats_FromDupArray_Recur for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10" are: 10
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#3	= 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2
Row#4	= 0, 0, 0, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3
Row#5	= 0, 0, 0, 0, 1, 1, 3, 3, 4, 4, 4, 4, 4, 4
Row#6	= 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6
Row#7	= 0, 0, 0, 0, 0, 1, 3, 4, 6, 7, 8, 8, 8, 8
Row#8	= 0, 0, 0, 0, 0, 1, 2, 4, 6, 8, 9, 10, 10, 10

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10": 10
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#2	= 0, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4
Row#3	= 0, 0, 0, 2, 4, 6, 7, 8, 8, 8, 8, 8, 8, 8
Row#4	= 0, 0, 0, 1, 3, 6, 8, 10, 10, 10, 10, 10, 10, 10
Row#5	= 0, 0, 0, 0, 2, 6, 10, 14, 15, 15, 15, 15, 15, 15
Row#6	= 0, 0, 0, 0, 1, 4, 10, 17, 19, 20, 20, 20, 20, 20
Row#7	= 0, 0, 0, 0, 0, 2, 8, 16, 20, 22, 23, 23, 23, 23
Row#8	= 0, 0, 0, 0, 0, 1, 7, 17, 25, 29, 31, 32, 32, 32

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10": 32
1, 2, 4, 8, 10, 15, 20, 23, 32
CombinationSum NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10": 32
1, 2, 3, 2, 0, 1, 1, 1, 1
CombinationSum NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "8" in "1, 1, 2, 2, 2, 3, 3, 5, 6, 7, 8, 9, 10": 1
===
CombinationSum FindAllUnique_NoRepeats_FromDupArray_FixRecur for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10" are: [1,1,2,2,2,4], [1,1,2,2,3,3], [1,1,2,2,6], [1,1,2,3,5], [1,1,2,4,4], [1,1,2,8], [1,1,3,3,4], [1,1,3,7], [1,1,4,6], [1,1,10], [1,2,2,2,5], [1,2,2,3,4], [1,2,2,7], [1,2,3,3,3], [1,2,3,6], [1,2,4,5], [1,2,9], [1,3,3,5], [1,3,4,4], [1,3,8], [1,4,7], [1,5,6], [2,2,2,3,3], [2,2,2,6], [2,2,3,5], [2,2,4,4], [2,2,8], [2,3,3,4], [2,3,7], [2,4,6], [2,10], [3,3,3,3], [3,3,6], [3,4,5], [3,9], [4,4,4], [4,8], [5,7]
CombinationSum FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10" are: [1,1,2,2,2,4], [1,1,2,2,3,3], [1,1,2,2,6], [1,1,2,3,5], [1,1,2,4,4], [1,1,2,8], [1,1,3,3,4], [1,1,3,7], [1,1,4,6], [1,1,10], [1,2,2,2,5], [1,2,2,3,4], [1,2,2,7], [1,2,3,3,3], [1,2,3,6], [1,2,4,5], [1,2,9], [1,3,3,5], [1,3,4,4], [1,3,8], [1,4,7], [1,5,6], [2,2,2,3,3], [2,2,2,6], [2,2,3,5], [2,2,4,4], [2,2,8], [2,3,3,4], [2,3,7], [2,4,6], [2,10], [3,3,3,3], [3,3,6], [3,4,5], [3,9], [4,4,4], [4,8], [5,7]
CombinationSum NumOfWays_NoRepeats_FromDupArray_Recur for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10" are: 38
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#3	= 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#4	= 0, 0, 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4
Row#5	= 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5
Row#6	= 0, 0, 0, 0, 1, 2, 3, 4, 4, 4, 6, 6, 6, 7, 8, 8, 8, 8, 8
Row#7	= 0, 0, 0, 0, 0, 1, 3, 4, 4, 4, 6, 6, 6, 8, 9, 10, 10, 10, 10
Row#8	= 0, 0, 0, 0, 0, 1, 2, 4, 4, 4, 7, 8, 8, 10, 12, 13, 14, 14, 14
Row#9	= 0, 0, 0, 0, 0, 0, 2, 3, 4, 4, 7, 8, 8, 12, 14, 16, 17, 18, 18
Row#10	= 0, 0, 0, 0, 0, 0, 1, 3, 4, 4, 8, 10, 10, 14, 18, 20, 22, 23, 24
Row#11	= 0, 0, 0, 0, 0, 0, 1, 2, 4, 4, 8, 10, 10, 16, 21, 25, 27, 29, 30
Row#12	= 0, 0, 0, 0, 0, 0, 0, 2, 3, 4, 8, 11, 12, 18, 25, 30, 34, 36, 38

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10": 38
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#2	= 0, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
Row#3	= 0, 0, 0, 2, 4, 6, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
Row#4	= 0, 0, 0, 1, 3, 6, 8, 10, 12, 14, 15, 16, 17, 17, 17, 17, 17, 17, 17
Row#5	= 0, 0, 0, 0, 2, 6, 10, 14, 18, 22, 24, 26, 28, 29, 29, 29, 29, 29, 29
Row#6	= 0, 0, 0, 0, 1, 4, 10, 17, 25, 34, 38, 42, 46, 48, 49, 49, 49, 49, 49
Row#7	= 0, 0, 0, 0, 0, 2, 8, 16, 26, 38, 48, 58, 68, 72, 74, 75, 75, 75, 75
Row#8	= 0, 0, 0, 0, 0, 1, 7, 17, 31, 49, 63, 78, 94, 104, 108, 110, 111, 111, 111
Row#9	= 0, 0, 0, 0, 0, 0, 4, 14, 31, 56, 78, 102, 128, 145, 155, 159, 161, 162, 162
Row#10	= 0, 0, 0, 0, 0, 0, 2, 10, 26, 52, 86, 124, 166, 194, 211, 221, 225, 227, 228
Row#11	= 0, 0, 0, 0, 0, 0, 1, 8, 25, 56, 94, 142, 200, 246, 275, 292, 302, 306, 308
Row#12	= 0, 0, 0, 0, 0, 0, 0, 4, 18, 49, 98, 161, 239, 307, 355, 384, 401, 411, 415

CombinationSum NumOfWays_NoRepeats_FromDupArray_DP2D_DistinguishDups for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10": 415
1, 2, 4, 10, 17, 29, 49, 75, 111, 162, 228, 308, 415
CombinationSum NumOfWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10": 415
1, 2, 3, 4, 3, 1, 1, 1, 1, 1, 1, 0, 0
CombinationSum NumOfDistinctOrderWays_NoRepeats_FromDupArray_DP1D_DistinguishDups for "12" in "1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 10": 0
===
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 2147483647, 1, 1, 1, 1
Row#2	= 2147483647, 2147483647, 2, 2, 2, 2
Row#3	= 2147483647, 2147483647, 3, 3, 3, 3
Row#4	= 2147483647, 2147483647, 4, 4, 4, 4
Row#5	= 2147483647, 1, 1, 1, 1, 1
Row#6	= 2147483647, 2147483647, 2, 2, 2, 2
Row#7	= 2147483647, 2147483647, 3, 3, 3, 3
Row#8	= 2147483647, 2147483647, 4, 4, 4, 4
Row#9	= 2147483647, 2147483647, 5, 5, 5, 5
Row#10	= 2147483647, 2, 2, 2, 2, 1
Row#11	= 2147483647, 2147483647, 3, 3, 3, 2
Row#12	= 2147483647, 2147483647, 4, 4, 4, 3
Row#13	= 2147483647, 2147483647, 5, 5, 5, 4
Row#14	= 2147483647, 2147483647, 6, 6, 6, 5
Row#15	= 2147483647, 3, 3, 3, 3, 2
Row#16	= 2147483647, 2147483647, 4, 4, 4, 3
Row#17	= 2147483647, 2147483647, 5, 5, 5, 4
Row#18	= 2147483647, 2147483647, 6, 6, 6, 5
Row#19	= 2147483647, 2147483647, 7, 7, 7, 6
Row#20	= 2147483647, 4, 4, 4, 1, 1
Row#21	= 2147483647, 2147483647, 5, 5, 2, 2
Row#22	= 2147483647, 2147483647, 6, 6, 3, 3
Row#23	= 2147483647, 2147483647, 7, 7, 4, 4
Row#24	= 2147483647, 2147483647, 8, 8, 5, 5
Row#25	= 2147483647, 5, 5, 1, 1, 1
Row#26	= 2147483647, 2147483647, 6, 2, 2, 2
Row#27	= 2147483647, 2147483647, 7, 3, 3, 3
Row#28	= 2147483647, 2147483647, 8, 4, 4, 4
Row#29	= 2147483647, 2147483647, 9, 5, 5, 5
Row#30	= 2147483647, 6, 6, 2, 2, 2
Row#31	= 2147483647, 2147483647, 7, 3, 3, 3
Row#32	= 2147483647, 2147483647, 8, 4, 4, 4
Row#33	= 2147483647, 2147483647, 9, 5, 5, 5
Row#34	= 2147483647, 2147483647, 10, 6, 6, 6
Row#35	= 2147483647, 7, 7, 3, 3, 2
Row#36	= 2147483647, 2147483647, 8, 4, 4, 3
Row#37	= 2147483647, 2147483647, 9, 5, 5, 4
Row#38	= 2147483647, 2147483647, 10, 6, 6, 5
Row#39	= 2147483647, 2147483647, 11, 7, 7, 6
Row#40	= 2147483647, 8, 8, 4, 2, 2

CombinationSum MinCoins_AllowRepeats_FromNoDupArray_DP2D for "40" in "5, 1, 25, 20, 10": 2
0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 2
CombinationSum MinCoins_AllowRepeats_FromDupArray_DP1D for "40" in "5, 1, 25, 20, 10": 2
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 2147483647, 1, 1, 1, 1
Row#2	= 2147483647, 2147483647, 2, 2, 2, 2
Row#3	= 2147483647, 2147483647, 3, 3, 3, 3
Row#4	= 2147483647, 2147483647, 4, 4, 4, 4
Row#5	= 2147483647, 1, 1, 1, 1, 1
Row#6	= 2147483647, 2147483647, 2, 2, 2, 2
Row#7	= 2147483647, 2147483647, 3, 3, 3, 3
Row#8	= 2147483647, 2147483647, 4, 4, 4, 4
Row#9	= 2147483647, 2147483647, 5, 5, 5, 5
Row#10	= 2147483647, 2, 2, 2, 2, 1
Row#11	= 2147483647, 2147483647, 3, 3, 3, 2
Row#12	= 2147483647, 2147483647, 4, 4, 4, 3
Row#13	= 2147483647, 2147483647, 5, 5, 5, 4
Row#14	= 2147483647, 2147483647, 6, 6, 6, 5
Row#15	= 2147483647, 3, 3, 3, 3, 2
Row#16	= 2147483647, 2147483647, 4, 4, 4, 3
Row#17	= 2147483647, 2147483647, 5, 5, 5, 4
Row#18	= 2147483647, 2147483647, 6, 6, 6, 5
Row#19	= 2147483647, 2147483647, 7, 7, 7, 6
Row#20	= 2147483647, 4, 4, 4, 1, 1
Row#21	= 2147483647, 2147483647, 5, 5, 2, 2
Row#22	= 2147483647, 2147483647, 6, 6, 3, 3
Row#23	= 2147483647, 2147483647, 7, 7, 4, 4
Row#24	= 2147483647, 2147483647, 8, 8, 5, 5
Row#25	= 2147483647, 5, 5, 1, 1, 1
Row#26	= 2147483647, 2147483647, 6, 2, 2, 2
Row#27	= 2147483647, 2147483647, 7, 3, 3, 3
Row#28	= 2147483647, 2147483647, 8, 4, 4, 4
Row#29	= 2147483647, 2147483647, 9, 5, 5, 5
Row#30	= 2147483647, 6, 6, 2, 2, 2
Row#31	= 2147483647, 2147483647, 7, 3, 3, 3
Row#32	= 2147483647, 2147483647, 8, 4, 4, 4
Row#33	= 2147483647, 2147483647, 9, 5, 5, 5
Row#34	= 2147483647, 2147483647, 10, 6, 6, 6
Row#35	= 2147483647, 7, 7, 3, 3, 2
Row#36	= 2147483647, 2147483647, 8, 4, 4, 3
Row#37	= 2147483647, 2147483647, 9, 5, 5, 4
Row#38	= 2147483647, 2147483647, 10, 6, 6, 5
Row#39	= 2147483647, 2147483647, 11, 7, 7, 6
Row#40	= 2147483647, 8, 8, 4, 2, 2
Row#41	= 2147483647, 2147483647, 9, 5, 3, 3
Row#42	= 2147483647, 2147483647, 10, 6, 4, 4
Row#43	= 2147483647, 2147483647, 11, 7, 5, 5
Row#44	= 2147483647, 2147483647, 12, 8, 6, 6
Row#45	= 2147483647, 9, 9, 5, 2, 2
Row#46	= 2147483647, 2147483647, 10, 6, 3, 3
Row#47	= 2147483647, 2147483647, 11, 7, 4, 4
Row#48	= 2147483647, 2147483647, 12, 8, 5, 5
Row#49	= 2147483647, 2147483647, 13, 9, 6, 6
Row#50	= 2147483647, 10, 10, 2, 2, 2
Row#51	= 2147483647, 2147483647, 11, 3, 3, 3
Row#52	= 2147483647, 2147483647, 12, 4, 4, 4

CombinationSum MinCoins_AllowRepeats_FromNoDupArray_DP2D for "52" in "5, 1, 25, 20, 10": 4
0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 2, 3, 4
CombinationSum MinCoins_AllowRepeats_FromDupArray_DP1D for "52" in "5, 1, 25, 20, 10": 4
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2
Row#3	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#6	= 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 1, 1, 1, 1, 1
Row#11	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 2, 2, 2, 2, 2
Row#12	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#13	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#14	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#15	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2
Row#16	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3
Row#17	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#18	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#19	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#20	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1
Row#21	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2
Row#22	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#23	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#24	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#25	= 2147483647, 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#26	= 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#27	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#28	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#29	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#30	= 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#31	= 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3, 3, 3, 3, 3
Row#32	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#33	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#34	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#35	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 2, 2, 2, 2, 2
Row#36	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 3, 3, 3, 3, 3
Row#37	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#38	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#39	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#40	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 2

CombinationSum MinCoins_NoRepeats_FromDupArray_DP2D for "40" in "5, 1, 25, 25, 20, 5, 10, 10, 10, 1, 20": 2
0, 1, 2, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2
CombinationSum MinCoins_NoRepeats_FromDupArray_DP1D for "40" in "5, 1, 25, 25, 20, 5, 10, 10, 10, 1, 20": 2
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2
Row#3	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#6	= 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 1, 1, 1, 1, 1
Row#11	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 2, 2, 2, 2, 2
Row#12	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#13	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#14	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#15	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2
Row#16	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3
Row#17	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#18	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#19	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#20	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1
Row#21	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2
Row#22	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#23	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#24	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#25	= 2147483647, 2147483647, 2147483647, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#26	= 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#27	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3
Row#28	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#29	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#30	= 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#31	= 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3, 3, 3, 3, 3
Row#32	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#33	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#34	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#35	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 2, 2, 2, 2, 2
Row#36	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 3, 3, 3, 3, 3
Row#37	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#38	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#39	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#40	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 2
Row#41	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4, 4, 4, 3
Row#42	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 5, 4
Row#43	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#44	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#45	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2
Row#46	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3, 3, 3
Row#47	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4
Row#48	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#49	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#50	= 2147483647, 2147483647, 2147483647, 2147483647, 2, 2, 2, 2, 2, 2, 2, 2
Row#51	= 2147483647, 2147483647, 2147483647, 2147483647, 3, 3, 3, 3, 3, 3, 3, 3
Row#52	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4, 4

CombinationSum MinCoins_NoRepeats_FromDupArray_DP2D for "52" in "5, 1, 25, 25, 20, 5, 10, 10, 10, 1, 20": 4
0, 1, 2, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 1, 2, 3, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2, 3, 4, 2147483647, 2147483647, 2, 3, 4
CombinationSum MinCoins_NoRepeats_FromDupArray_DP1D for "52" in "5, 1, 25, 25, 20, 5, 10, 10, 10, 1, 20": 4
===
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 2147483647, 20, 20, 20
Row#2	= 2147483647, 40, 40, 40
Row#3	= 2147483647, 60, 60, 60
Row#4	= 2147483647, 80, 80, 80
Row#5	= 2147483647, 100, 100, 100
Row#6	= 2147483647, 120, 120, 120
Row#7	= 2147483647, 140, 125, 125
Row#8	= 2147483647, 160, 145, 145
Row#9	= 2147483647, 180, 165, 165
Row#10	= 2147483647, 200, 185, 185
Row#11	= 2147483647, 220, 205, 205
Row#12	= 2147483647, 240, 225, 225
Row#13	= 2147483647, 260, 245, 245
Row#14	= 2147483647, 280, 250, 250
Row#15	= 2147483647, 300, 270, 270
Row#16	= 2147483647, 320, 290, 290
Row#17	= 2147483647, 340, 310, 310
Row#18	= 2147483647, 360, 330, 330
Row#19	= 2147483647, 380, 350, 350
Row#20	= 2147483647, 400, 370, 370
Row#21	= 2147483647, 420, 375, 375
Row#22	= 2147483647, 440, 395, 395
Row#23	= 2147483647, 460, 415, 415
Row#24	= 2147483647, 480, 435, 435
Row#25	= 2147483647, 500, 455, 455
Row#26	= 2147483647, 520, 475, 475
Row#27	= 2147483647, 540, 495, 495
Row#28	= 2147483647, 560, 500, 500
Row#29	= 2147483647, 580, 520, 520
Row#30	= 2147483647, 600, 540, 510

CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP2D for "30" in "1, 7, 30", "20, 125, 510": 510
0, 20, 40, 60, 80, 100, 120, 125, 145, 165, 185, 205, 225, 245, 250, 270, 290, 310, 330, 350, 370, 375, 395, 415, 435, 455, 475, 495, 500, 520, 510
CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP1D for "30" in "1, 7, 30", "20, 125, 510": 510
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20
Row#2	= 2147483647, 2147483647, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40
Row#3	= 2147483647, 2147483647, 2147483647, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
Row#6	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 120, 120, 120, 120, 120, 120, 120, 120, 120
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 140, 140, 140, 125, 125, 125, 125, 125
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 160, 160, 145, 145, 145, 145, 145
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 180, 165, 165, 165, 165, 165
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 185, 185, 185, 185, 185
Row#11	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 205, 205, 205, 205, 205
Row#12	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 225, 225, 225, 225, 225
Row#13	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 245, 245, 245, 245, 245
Row#14	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 265, 250, 250, 250, 250
Row#15	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 285, 270, 270, 270, 270
Row#16	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 305, 290, 290, 290, 290
Row#17	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 310, 310, 310, 310
Row#18	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 330, 330, 330, 330
Row#19	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 350, 350, 350, 350
Row#20	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 370, 370, 370, 370
Row#21	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 390, 375, 375, 375
Row#22	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 410, 395, 395, 395
Row#23	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 430, 415, 415, 415
Row#24	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 435, 435, 435
Row#25	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 455, 455, 455
Row#26	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 475, 475, 475
Row#27	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 495, 495, 495
Row#28	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 515, 500, 500
Row#29	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 535, 520, 520
Row#30	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 555, 540, 510

CombinationSum MinCost_NoRepeats_FromDupArray_DP2D for "30" in "1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 30", "20, 20, 20, 20, 20, 20, 20, 20, 20, 125, 125, 125, 125, 510": 510
0, 20, 40, 60, 80, 100, 120, 125, 145, 165, 185, 205, 225, 245, 250, 270, 290, 310, 330, 350, 370, 375, 395, 415, 435, 455, 475, 495, 500, 520, 510
CombinationSum MinCost_NoRepeats_FromDupArray_DP1D for "30" in "1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 30", "20, 20, 20, 20, 20, 20, 20, 20, 20, 125, 125, 125, 125, 510": 510
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 178, 178, 178, 178, 178
Row#2	= 2147483647, 356, 356, 356, 356, 356
Row#3	= 2147483647, 534, 534, 534, 534, 534
Row#4	= 2147483647, 712, 712, 712, 712, 712
Row#5	= 2147483647, 890, 890, 890, 890, 890
Row#6	= 2147483647, 1068, 1068, 1068, 1068, 1068
Row#7	= 2147483647, 1246, 1236, 1236, 1236, 1236
Row#8	= 2147483647, 1424, 1414, 1414, 1414, 1414
Row#9	= 2147483647, 1602, 1592, 1592, 1592, 1592
Row#10	= 2147483647, 1780, 1770, 1770, 1770, 1770
Row#11	= 2147483647, 1958, 1948, 1948, 1948, 1948
Row#12	= 2147483647, 2136, 2126, 2126, 2126, 2126
Row#13	= 2147483647, 2314, 2304, 2304, 2304, 2304
Row#14	= 2147483647, 2492, 2472, 2472, 2472, 2472
Row#15	= 2147483647, 2670, 2650, 2650, 2650, 2650
Row#16	= 2147483647, 2848, 2828, 2828, 2828, 2828
Row#17	= 2147483647, 3026, 3006, 2995, 2995, 2995
Row#18	= 2147483647, 3204, 3184, 3173, 3173, 3173
Row#19	= 2147483647, 3382, 3362, 3351, 3351, 3351
Row#20	= 2147483647, 3560, 3540, 3529, 3529, 3529
Row#21	= 2147483647, 3738, 3708, 3707, 3707, 3707
Row#22	= 2147483647, 3916, 3886, 3885, 3885, 3885
Row#23	= 2147483647, 4094, 4064, 4063, 4063, 4063
Row#24	= 2147483647, 4272, 4242, 4231, 4231, 4231
Row#25	= 2147483647, 4450, 4420, 4409, 4409, 4409
Row#26	= 2147483647, 4628, 4598, 4587, 4587, 4587
Row#27	= 2147483647, 4806, 4776, 4765, 4765, 4765
Row#28	= 2147483647, 4984, 4944, 4943, 4943, 4943
Row#29	= 2147483647, 5162, 5122, 5121, 5121, 5121
Row#30	= 2147483647, 5340, 5300, 5299, 5299, 5299

CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP2D for "30" in "1, 7, 17, 27, 30", "178, 1236, 2995, 4790, 5330": 5299
0, 178, 356, 534, 712, 890, 1068, 1236, 1414, 1592, 1770, 1948, 2126, 2304, 2472, 2650, 2828, 2995, 3173, 3351, 3529, 3707, 3885, 4063, 4231, 4409, 4587, 4765, 4943, 5121, 5299
CombinationSum MinCost_AllowRepeats_FromNoDupArray_DP1D for "30" in "1, 7, 17, 27, 30", "178, 1236, 2995, 4790, 5330": 5299
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2147483647, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178
Row#2	= 2147483647, 2147483647, 356, 356, 356, 356, 356, 356, 356, 356, 356, 356, 356, 356, 356
Row#3	= 2147483647, 2147483647, 2147483647, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534, 534
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 712, 712, 712, 712, 712, 712, 712, 712, 712, 712, 712
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 890, 890, 890, 890, 890, 890, 890, 890, 890, 890
Row#6	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068, 1068
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1236, 1236, 1236, 1236, 1236, 1236, 1236, 1236
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1414, 1414, 1414, 1414, 1414, 1414, 1414, 1414
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1592, 1592, 1592, 1592, 1592, 1592, 1592, 1592
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1770, 1770, 1770, 1770, 1770, 1770, 1770, 1770
Row#11	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 1948, 1948, 1948, 1948, 1948, 1948, 1948, 1948
Row#12	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2126, 2126, 2126, 2126, 2126, 2126, 2126, 2126
Row#13	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2304, 2304, 2304, 2304, 2304, 2304, 2304, 2304
Row#14	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2472, 2472, 2472, 2472, 2472, 2472, 2472
Row#15	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2650, 2650, 2650, 2650, 2650, 2650, 2650
Row#16	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2828, 2828, 2828, 2828, 2828, 2828, 2828
Row#17	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3006, 3006, 3006, 2995, 2995, 2995, 2995
Row#18	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3184, 3184, 3184, 3173, 3173, 3173, 3173
Row#19	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3362, 3362, 3362, 3351, 3351, 3351, 3351
Row#20	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3540, 3540, 3540, 3529, 3529, 3529, 3529
Row#21	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3708, 3708, 3707, 3707, 3707, 3707
Row#22	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3886, 3886, 3885, 3885, 3885, 3885
Row#23	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4064, 4064, 4063, 4063, 4063, 4063
Row#24	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4242, 4242, 4231, 4231, 4231, 4231
Row#25	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4420, 4420, 4409, 4409, 4409, 4409
Row#26	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4598, 4598, 4587, 4587, 4587, 4587
Row#27	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4776, 4776, 4765, 4765, 4765, 4765
Row#28	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 4944, 4943, 4943, 4943, 4943
Row#29	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 5122, 5121, 5121, 5121, 5121
Row#30	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 5300, 5299, 5299, 5299, 5299

CombinationSum MinCost_NoRepeats_FromDupArray_DP2D for "30" in "1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 17, 17, 27, 30", "178, 178, 178, 178, 178, 178, 1236, 1236, 1236, 1236, 2995, 2995, 4790, 5330": 5299
0, 178, 356, 534, 712, 890, 1068, 1236, 1414, 1592, 1770, 1948, 2126, 2304, 2472, 2650, 2828, 2995, 3173, 3351, 3529, 3707, 3885, 4063, 4231, 4409, 4587, 4765, 4943, 5121, 5299
CombinationSum MinCost_NoRepeats_FromDupArray_DP1D for "30" in "1, 1, 1, 1, 1, 1, 7, 7, 7, 7, 17, 17, 27, 30", "178, 178, 178, 178, 178, 178, 1236, 1236, 1236, 1236, 2995, 2995, 4790, 5330": 5299
*/
#endif