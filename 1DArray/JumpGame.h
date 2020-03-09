#ifndef JUMP_GAME_H
#define JUMP_GAME_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Check if a board game is winnable (CanJumpGreedy3)
http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/
Leetcode: Jump Game
// Given an array of non-negative integers, you are initially positioned at
// the first index of the array.
//
// Each element in the array represents your maximum jump length at that
// position.
//
// Determine if you are able to reach the last index.
//
// For example:
// A = [2,3,1,1,4], return true.
//
// A = [3,2,1,0,4], return false.
//
// Complexity
// Greedy: O(n)
// DP: O(n^2)

Leetcode: Jump Game II
// Given an array of non-negative integers, you are initially positioned at
// the first index of the array.
//
// Each element in the array represents your maximum jump length at that
// position.
//
// Your goal is to reach the last index in the minimum number of jumps.
//
// For example:
// Given array A = [2,3,1,1,4]
//
// The minimum number of jumps to reach the last index is 2. (Jump 1 step
// from index 0 to 1, then 3 steps to the last index.)
//
// Complexity
// Greedy: O(n)
// DP: O(n^2)
Greedy: choose the current best instead of overall best condition.
Always choose the farthest distance you can reach from all available positions.
*/
class JumpGame
{
public:
	JumpGame(){}
	~JumpGame(){}

	//O(n) time
	bool CanJump_Greedy(int A[], int n)
	{
		std::cout << "JumpGame CanJump_Greedy for \"" << Debug::ToStr1D<int>()(A, n) << "\": ";
		int curEnd = 0;
		for (int i = 0; i < n; ++i)
		{
			if (curEnd < i)
			{
				std::cout << false << std::endl;
				return false;
			}
			curEnd = std::max(curEnd, i + A[i]);
			if (curEnd >= n - 1)
			{
				std::cout << true << std::endl;
				return true;
			}
		}
		std::cout << false << std::endl;
		return false;
	}
	//O(n^2) time, time limit exceeded
	bool CanJump_DP(int A[], int n)
	{
		if (n <= 1)
			return true;
		std::cout << "JumpGame CanJump_DP for \"" << Debug::ToStr1D<int>()(A, n) << "\": ";
		std::vector<int> dp(n, 0);
		dp[0] = 1;//true
		for (int i = 1; i < n; ++i)
		{
			dp[i] = 0;//false
			for (int j = i - 1; j >= 0; --j)
			{
				if (dp[j] && j + A[j] >= i)
				{
					dp[i] = 1;//true
					break;
				}
			}
		}
		std::cout << dp[n - 1] << std::endl;
		return dp[n - 1] == 1 ? true : false;
	}

	//O(n) time
	int MinJumps_Greedy(int A[], int n)
	{
		int curEnd = 0;
		int preEnd = 0;
		int step = 0;
		for (int i = 0; i < n; ++i)
		{
			if (preEnd < i)
			{
				preEnd = curEnd;
				++step;
			}
			curEnd = std::max(curEnd, i + A[i]);
		}
		std::cout << "JumpGame MinJumps_Greedy for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << step << std::endl;
		return step;
	}
	//O(n^2) time, time limit exceeded
	int MinJumps_DP(int A[], int n)
	{
		std::vector<int> dp(n, 0);
		for (int i = 1; i < n; ++i)
		{
			dp[i] = n;
			for (int j = i - 1; j >= 0; --j)
			{
				if (j + A[j] >= i)
					dp[i] = std::min(1 + dp[j], dp[i]);
			}
		}
		std::cout << "JumpGame MinJumps_DP for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << dp[n - 1] << std::endl;
		return dp[n - 1];
	}
};
/*
JumpGame CanJump_Greedy for "1, 2, 3, 0, 3": 1
JumpGame CanJump_DP for "1, 2, 3, 0, 3": 1
JumpGame MinJumps_Greedy for "3, 2, 3, 0, 1, 3, 0, 1": 3
JumpGame MinJumps_DP for "3, 2, 3, 0, 1, 3, 0, 1": 3
*/
#endif

/*
https://leetcode.com/discuss/422/is-there-better-solution-for-jump-game-ii
http://suifengls.blogspot.tw/2013/09/jump-gameleetcode.html
http://suifengls.blogspot.tw/2013/09/jump-game-iileetcode.html
http://coding-exercise.blogspot.tw/2013/03/leetcode-jump-game.html
http://coding-exercise.blogspot.tw/2013/03/leetcode-jump-game-ii.html?view=sidebar
*/