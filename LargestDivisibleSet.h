#ifndef LARGEST_DIVISIBLE_SET_H
#define LARGEST_DIVISIBLE_SET_H
#include "Debug.h"
/*
Leetcode: Largest Divisible Set
Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
If there are multiple solutions, return any subset is fine.

Example 1:
nums: [1,2,3]
Result: [1,2] (of course, [1,3] will also be ok)

Example 2:
nums: [1,2,4,8]
Result: [1,2,4,8]

For Si % Sj = 0, if Sj > Si, it must always be Si, so only Si >= Sj is meaningful to test Si % Sj.
Sort the array.
After sorting the array, this problem becomes similar to find the LIS.
But instead of testing increasing, we test v[end] % v[start] == 0 and dp[start] + 1 > dp[end], where dp[i] represents the length of longest %==0 sequence at i.
Also keep a prevIdx array to track the prev index of longest %==0 sequence at i.

*/
class LargestDivisibleSet
{
public:
	LargestDivisibleSet() {}
	~LargestDivisibleSet() {}

	std::vector<int> DP(std::vector<int> & nums)
	{
		std::sort(nums.begin(), nums.end());
		int N = nums.size();
		std::vector<int> dp(N, 1);
		std::vector<int> prevIdx(N, -1);

		for (int end = 1; end < N; ++end)
		{
			for (int start = 0; start < end; ++start)
			{
				if (nums[end] % nums[start] == 0 && dp[start] + 1 > dp[end])
				{
					dp[end] = dp[start] + 1;
					prevIdx[end] = start;
				}
			}
		}

		int maxLen = 0;
		int maxEnd = 0;
		for (int i = 0; i < N; ++i)
		{
			if (maxLen < dp[i])
			{
				maxLen = dp[i];
				maxEnd = i;
			}
		}
		std::vector<int> res(maxLen);
		while (maxLen-- > 0)
		{
			res[maxLen] = nums[maxEnd];
			maxEnd = prevIdx[maxEnd];
		}

		std::cout << "LargestDivisibleSet DP for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
LargestDivisibleSet DP for "1, 2, 3": 1, 2
LargestDivisibleSet DP for "1, 2, 4, 8": 1, 2, 4, 8
*/
#endif
