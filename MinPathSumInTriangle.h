/*MEMO*/
#ifndef MIN_PATH_SUM_IN_TRIANGLE_H
#define MIN_PATH_SUM_IN_TRIANGLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Find the max weight path in a triangle
Leetcode: Triangle
// Given a triangle, find the minimum path sum from top to bottom. Each step
// you may move to adjacent numbers on the row below.
//
// For example, given the following triangle
// [
//     [2],
//    [3,4],
//   [6,5,7],
//  [4,1,8,3]
//             ]
// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
//
// Note:
// Bonus point if you are able to do this using only O(n) extra space, where
// n is the total number of rows in the triangle.
//
// Complexity:
// DP, O(n^2) time, O(n^2) space
// Squeeze Memory, O(n^2) time, O(n) space

2
3,4
6,5,7
4,1,8,7

Analysis:
This problem is more likely to be a (dynamic programming) DP problem,
where a[rowY][colX] = a[rowY][colX] + min(a[rowY-1][colX], a[rowY-1][colX-1]).
Note that in this problem, "adjacent" of a[rowY][colX] means a[rowY-1][colX] (up) and a[rowY-1][colX-1] (up left), if available(not out of bound)
, while a[rowY-1][colX+1] is not "adjacent" element.

top down: current's down and down right
bottom up: current's up and up left
*/
class MinPathSumInTriangle
{
public:
	MinPathSumInTriangle(){}
	~MinPathSumInTriangle(){}

	int DP_2D(const std::vector<std::vector<int> > & triangle)//[rowY][columnX]
	{
		Debug::Print2D<int>()(triangle, false);
		int N = triangle.size();
		std::vector<std::vector<int> > dp;
		for (int rowY = 0; rowY < N; rowY++)
			dp.push_back(std::vector<int>(rowY + 1, 0));//a "triangle" dp table

		for (int rowY = N - 1; rowY >= 0; --rowY)//for each row (bottom up)
		{
			for (int colX = 0; colX <= rowY; ++colX)//for each col (left to right) (each row has rowY+1 elements)
			{
				if (rowY == N - 1)
					dp[rowY][colX] = triangle[rowY][colX];
				else
					dp[rowY][colX] = 
					std::min(dp[rowY + 1][colX], dp[rowY + 1][colX + 1]) + triangle[rowY][colX];
					/*current = min of (down, down right) in dp + current in triangle*/
			}
			Debug::Print2D<int>()(dp, false);
		}
		std::cout << "MinPathSumInTriangle DP_2D: " << dp[0][0] << std::endl;
		return dp[0][0];
	}

	int DP_1D(const std::vector<std::vector<int> > & triangle)//[rowY][columnX]
	{
		if (triangle.empty())
			return 0;
		Debug::Print2D<int>()(triangle, false);
		int N = triangle.size();
		std::vector<int> dp(N, 0);
		for (int rowY = N - 1; rowY >= 0; --rowY)//for each row (bottom up)
		{
			for (int colX = 0; colX <= rowY; ++colX)//for each col (left to right) (each row has rowY+1 elements)
			{
				if (rowY == N - 1)
					dp[colX] = triangle[rowY][colX];
				else
					dp[colX] = 
					std::min(dp[colX], dp[colX + 1]) + triangle[rowY][colX];
					/*current = min of (current, current right) in dp + current in triangle*/
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		std::cout << "MinPathSumInTriangle DP_1D: " << dp[0] << std::endl;
		return dp[0];
	}


};
/*
[rY][cX]
Row#0	= 2,  ,  ,
Row#1	= 3, 4,  ,
Row#2	= 6, 5, 7,
Row#3	= 4, 1, 8, 3

[rY][cX]
Row#0	= 0,  ,  ,
Row#1	= 0, 0,  ,
Row#2	= 0, 0, 0,
Row#3	= 4, 1, 8, 3

[rY][cX]
Row#0	= 0,  ,  ,
Row#1	= 0, 0,  ,
Row#2	= 7, 6, 10,
Row#3	= 4, 1, 8, 3

[rY][cX]
Row#0	= 0,  ,  ,
Row#1	= 9, 10,  ,
Row#2	= 7, 6, 10,
Row#3	= 4, 1, 8, 3

[rY][cX]
Row#0	= 11,  ,  ,
Row#1	= 9, 10,  ,
Row#2	= 7, 6, 10,
Row#3	= 4, 1, 8, 3

MinPathSumInTriangle DP_2D: 11
[rY][cX]
Row#0	= 2,  ,  ,
Row#1	= 3, 4,  ,
Row#2	= 6, 5, 7,
Row#3	= 4, 1, 8, 3

4, 1, 8, 3
7, 6, 10, 3
9, 10, 10, 3
11, 10, 10, 3
MinPathSumInTriangle DP_1D: 11
*/
#endif