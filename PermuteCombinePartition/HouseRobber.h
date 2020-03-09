#ifndef HOUSE_ROBBER_H
#define HOUSE_ROBBER_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
Leetcode: House Robber
http://www.cnblogs.com/grandyang/p/4383632.html
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed
, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected 
and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given a list of non-negative integers representing the amount of money of each house
, determine the maximum amount of money you can rob tonight without alerting the police.

Leetcode: House Robber II
After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention.
This time, all houses at this place are arranged in a circle.
That means the first house is the neighbor of the last one.
Meanwhile, the security system for these houses remain the same as for those in the previous street.
Given a list of non-negative integers representing the amount of money of each house
, determine the maximum amount of money you can rob tonight without alerting the police.
*/
class HouseRobber
{
public:
	HouseRobber(){}
	~HouseRobber(){}

	int DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		if (N == 0)
			return 0;
		if (N == 1)
			return v[0];

		std::vector<int> dp(N);
		dp[0] = v[0];
		dp[1] = std::max(v[0], v[1]);
		for (int i = 2; i < N; ++i)
		{
			dp[i] = std::max(v[i] + dp[i - 2], dp[i - 1]);
		}

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "HouseRobber DP1D for \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[N - 1] << std::endl;
		return dp[N - 1];
	}

	int ConstSpace(const std::vector<int> & v)
	{
		int N = v.size();

		int even = 0;
		int odd = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i % 2 == 0)
			{
				even += v[i];
				even = std::max(even, odd);
			}
			else
			{
				odd += v[i];
				odd = std::max(even, odd);
			}
		}

		std::cout << "HouseRobber ConstSpace for \"" << Debug::ToStr1D<int>()(v) << "\": max of [even,odd]=[" << even << "," << odd << "]" << std::endl;
		return std::max(even, odd);
	}

	int Circular_DP1D(const std::vector<int> & nums)
	{
		int N = nums.size();
		if (N == 0)
			return 0;
		if (N == 1)
			return nums[0];
		if (N == 2)
			return std::max(nums[0], nums[1]);

		//include the first element, not include the last element
		std::vector<int> dp1(N - 1);
		dp1[0] = nums[0];
		dp1[1] = std::max(nums[0], nums[1]);
		for (int i = 2; i < N - 1; ++i)
		{
			dp1[i] = std::max(dp1[i - 2] + nums[i], dp1[i - 1]);
		}

		//not include the first element, include the last element
		std::vector<int> dp2(N - 1);
		dp2[0] = nums[1];
		dp2[1] = std::max(nums[1], nums[2]);
		for (int i = 2; i < N - 1; ++i)
		{
			dp2[i] = std::max(dp2[i - 2] + nums[i + 1], dp2[i - 1]);
		}

		std::cout << Debug::ToStr1D<int>()(dp1) << std::endl;
		std::cout << Debug::ToStr1D<int>()(dp2) << std::endl;
		std::cout << "HouseRobber Circular_DP1D for \"" << Debug::ToStr1D<int>()(nums) << "\": " << std::max(dp1[N - 2], dp2[N - 2]) << std::endl;
		return std::max(dp1[N - 2], dp2[N - 2]);
	}
};
/*
9, 15, 32, 35, 46, 46, 64, 74, 74, 88, 88, 117, 117, 133, 147
HouseRobber DP1D for "9, 15, 23, 20, 14, 3, 18, 28, 7, 14, 8, 29, 9, 16, 30": 147
HouseRobber ConstSpace for "9, 15, 23, 20, 14, 3, 18, 28, 7, 14, 8, 29, 9, 16, 30": max of [even,odd]=[147,133]
2, 7, 11, 11
7, 9, 10, 10
HouseRobber Circular_DP1D for "2, 7, 9, 3, 1": 11
*/
#endif