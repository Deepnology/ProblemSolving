#ifndef PLUS_MINUS_COMBINATION_SUM_H
#define PLUS_MINUS_COMBINATION_SUM_H
#include "Debug.h"
/*
Leetcode: Target Sum
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S.
Now you have 2 symbols + and -.
For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.
Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
Note:
1. The length of the given array is positive and will not exceed 20.
2. The sum of elements in the given array will not exceed 1000.
3. Your output answer is guaranteed to be fitted in a 32-bit integer.
*/
class PlusMinusCombinationSum
{
public:
	PlusMinusCombinationSum() {}

	int NumOfWaysRecur(const std::vector<int> & nums, int S)
	{
		int res = 0;
		recur(nums, 0, 0, S, res);
		std::cout << "PlusMinusCombinationSum NumOfWaysRecur for \"" << S << "\" from \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
private:
	void recur(const std::vector<int> & v, int i, int curSum, int sum, int & count)
	{
		int N = v.size();
		if (i == N)
		{
			if (curSum == sum)
				++count;
			return;
		}
		recur(v, i + 1, curSum + v[i], sum, count);
		recur(v, i + 1, curSum - v[i], sum, count);
	}
public:
	int NumOfWaysRecurDP(const std::vector<int> & nums, int S)
	{
		int N = nums.size();
		std::vector<std::unordered_map<int, int>> dp(N, std::unordered_map<int, int>());
		int res = recurDP(nums, 0, 0, S, dp);
		std::cout << "PlusMinusCombinationSum NumOfWaysRecurDP for \"" << S << "\" from \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
private:
	int recurDP(const std::vector<int> & v, int i, int curSum, int sum, std::vector<std::unordered_map<int, int>> & dp)
	{
		int N = v.size();
		if (i == N)
		{
			if (curSum == sum)
				return 1;
			else
				return 0;
		}
		if (dp[i].count(curSum)) return dp[i][curSum];
		int a = recurDP(v, i + 1, curSum + v[i], sum, dp);
		int b = recurDP(v, i + 1, curSum - v[i], sum, dp);
		return dp[i][curSum] = (a + b);
	}
public:
	int NumOfWaysDP2D(const std::vector<int> & nums, int S)
	{
		int N = nums.size();
		std::vector<std::unordered_map<int,int>> dp(N + 1, std::unordered_map<int,int>());
		dp[0][0] = 1;
		for (int i = 1; i <= N; ++i)
		{
			for (const auto & p : dp[i-1])
			{
				dp[i][p.first + nums[i-1]] += p.second;
				dp[i][p.first - nums[i-1]] += p.second;
			}
		}
		std::cout << "PlusMinusCombinationSum NumOfWaysDP2D for \"" << S << "\" from \"" << Debug::ToStr1D<int>()(nums) << "\": " << dp[N][S] << std::endl;
		return dp[N][S];
	}
};
/*
PlusMinusCombinationSum NumOfWaysRecur for "3" from "1, 1, 1, 1, 1": 5
PlusMinusCombinationSum NumOfWaysRecurDP for "3" from "1, 1, 1, 1, 1": 5
PlusMinusCombinationSum NumOfWaysDP2D for "3" from "1, 1, 1, 1, 1": 5
*/
#endif
