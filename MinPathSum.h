#ifndef MIN_PATH_SUM_H
#define MIN_PATH_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Plan a fishing trip
http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
Leetcode: Minimum Path Sum
// Given a m x n grid filled with non-negative numbers, find a path from "top
// left" to "bottom right" which minimizes the sum of all numbers along its path.
//
// Note: You can only move either "down" or "right" at any point in time.
//
// Complexity:
// DP, O(m*n) time, O(m*n) space
// DP, O(m*n) time, O(n) space
*/
class MinPathSum
{
public:
	MinPathSum(){}
	~MinPathSum(){}

	int DP_2D(const std::vector<std::vector<int> > & grid)//[rowY][columnX]
	{
		if (grid.empty() || grid[0].empty())
			return 0;
		Debug::Print2D<int>()(grid, false);
		int M = grid.size();
		int N = grid[0].size();
		std::vector<std::vector<int> > dp(M, std::vector<int>(N, 0));
		for (int rowY = 0; rowY < M; ++rowY)
		{
			for (int colX = 0; colX < N; ++colX)
			{
				if (rowY == 0 && colX == 0)//the top left corner element
					dp[rowY][colX] = grid[rowY][colX];
					/*current = current in grid*/
				else if (rowY == 0)//top row
					dp[rowY][colX] = dp[rowY][colX - 1] + grid[rowY][colX];
					/*current = left in dp + current in grid*/
				else if (colX == 0)//first element of each row
					dp[rowY][colX] = dp[rowY - 1][colX] + grid[rowY][colX];
					/*current = up in dp + current in grid*/
				else
					dp[rowY][colX] = 
					std::min(dp[rowY - 1][colX], dp[rowY][colX - 1]) + grid[rowY][colX];
					/*current = min of (up, left) in dp + current in grid*/
			}
			
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "MinPathSum DP_2D: " << dp[M - 1][N - 1] << std::endl;
		return dp[M - 1][N - 1];
	}

	int DP_1D(const std::vector<std::vector<int> > & grid)//[rowY][columnX]
	{
		if (grid.empty() || grid[0].empty())
			return 0;
		Debug::Print2D<int>()(grid, false);
		int M = grid.size();
		int N = grid[0].size();
		std::vector<int> dp(N, 0);
		for (int rowY = 0; rowY < M; ++rowY)//for each row (top down)
		{
			for (int colX = 0; colX < N; ++colX)//for each col (left to right)
			{
				if (colX == 0)//first element of each row
					dp[colX] += grid[rowY][colX];
					/*current = current in dp + current in grid*/
				else if (rowY == 0)//top row
					dp[colX] = dp[colX - 1] + grid[rowY][colX];
					/*current = left in dp + current in grid*/
				else
					dp[colX] = 
					std::min(dp[colX], dp[colX - 1]) + grid[rowY][colX];
					/*current = min of (current, left) in dp + current in grid*/
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		std::cout << "MinPathSum DP_1D: " << dp[N - 1] << std::endl;
		return dp[N - 1];
	}

};
/*
[rY][cX]
Row#0	= 1, 7, 3, 7
Row#1	= 9, 6, 1, 2
Row#2	= 3, 8, 4, 5

[rY][cX]
Row#0	= 1, 8, 11, 18
Row#1	= 10, 14, 12, 14
Row#2	= 13, 21, 16, 19

MinPathSum DP_2D: 19
[rY][cX]
Row#0	= 1, 7, 3, 7
Row#1	= 9, 6, 1, 2
Row#2	= 3, 8, 4, 5

1, 8, 11, 18
10, 14, 12, 14
13, 21, 16, 19
MinPathSum DP_1D: 19
*/
#endif