/*MEMO*/
#ifndef UNIQUE_PATH_H
#define UNIQUE_PATH_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Count the number of ways to traverse a 2D array (DP_2D, DP_2D_wObstacle)
http://www.geeksforgeeks.org/print-all-possible-paths-from-top-left-to-bottom-right-of-a-mxn-matrix/
http://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/
Leetcode: Unique Paths
// A robot is located at the "top-left corner" of a m x n grid (marked 'Start'
// in the diagram below).
//
// The robot can only move either "down" or "right" at any point in time. The robot
// is trying to reach the bottom-right corner of the grid (marked 'Finish' in
// the diagram below).
//
// How many possible unique paths are there?
//
// Complexity:
// DP, O(m*n) time, O(1) space
// DP, O(m*n) time, O(n) space
// Math, O(n) time, O(1) space

Leetcode: Unique Paths II
// Follow up for "Unique Paths":
//
// Now consider if some obstacles are added to the grids. How many unique
// paths would there be?
//
// An obstacle and empty space is marked as 1 and 0 respectively in the grid.
//
// For example,
// There is one obstacle in the middle of a 3x3 grid as illustrated below.
//
// [
//  [0,0,0],
//  [0,1,0],
//  [0,0,0]
// ]
// The total number of unique paths is 2.
//
// Note: m and n will be at most 100.
//
// Complexity:
// DP, O(m*n) time, O(m*n) space
// DP, O(m*n) time, O(n) space
*/
class UniquePath
{
public:
	UniquePath(){}
	~UniquePath(){}

	//this is equivalent to find all permutations of {d, d, d, r, r} for 4x3 grid
	int FindAll_Recur(int m, int n)//Backtracking
	{
		std::vector<char> path;
		std::vector<std::vector<char> > res;
		int count = this->findAllRecur(0, 0, m - 1, n - 1, path, res);
		Debug::Print2D<char>()(res);
		std::cout << "UniquePath FindAll_Recur for \"" << m << "\" rows, \"" << n << "\" cols: " << count << std::endl;
		return count;
	}
private:
	int findAllRecur(int curRowY, int curColX, int m, int n, std::vector<char> & path, std::vector<std::vector<char> > & res)
	{
		if (curRowY > m || curColX > n)
			return 0;
		if (curRowY == m && curColX == n)
		{
			res.push_back(path);
			return 1;
		}
		path.push_back('d');
		int downCount = this->findAllRecur(curRowY + 1, curColX, m, n, path, res);
		path.pop_back();
		path.push_back('r');
		int rightCount = this->findAllRecur(curRowY, curColX + 1, m, n, path, res);
		path.pop_back();

		return downCount + rightCount;
	}
public:
	int DP2D_Recur(int m, int n)
	{
		std::vector<std::vector<int> > dp(m + 1, std::vector<int>(n + 1, -1));
		std::vector<char> path;
		std::vector<std::vector<char> > res;
		int count = this->dP2DRecur(0, 0, m - 1, n - 1, dp, path, res);
		Debug::Print2D<char>()(res);
		std::cout << "UniquePath DP2D_Recur for \"" << m << "\" rows, \"" << n << "\" cols: " << count << std::endl;
		return count;
	}
private:
	int dP2DRecur(int curRowY, int curColX, int m, int n, std::vector<std::vector<int> > & dp
		, std::vector<char> & path, std::vector<std::vector<char> > & res)
	{
		if (curRowY > m || curColX > n)
			return 0;
		if (curRowY == m && curColX == n)
		{
			res.push_back(path);
			return 1;
		}
		if (dp[curRowY + 1][curColX] == -1)
		{
			path.push_back('d');
			dp[curRowY + 1][curColX] = this->dP2DRecur(curRowY + 1, curColX, m, n, dp, path, res);
			path.pop_back();
		}
		if (dp[curRowY][curColX + 1] == -1)
		{
			path.push_back('r');
			dp[curRowY][curColX + 1] = this->dP2DRecur(curRowY, curColX + 1, m, n, dp, path, res);
			path.pop_back();
		}
		return dp[curRowY + 1][curColX] + dp[curRowY][curColX + 1];
	}

public:
	int DP_2D(int m, int n)//[rowY][columnX]
	{
		std::vector<std::vector<int> > dp(m, std::vector<int>(n, 0));
		dp[0][0] = 1;
		for (int rowY = 0; rowY < m; ++rowY) 
		{
			for (int colX = 0; colX < n; ++colX)
			{
				if (rowY == 0 || colX == 0)
					dp[rowY][colX] = 1;
					/*only one possible path for top row and leftmost column*/
				else
					dp[rowY][colX] = 
					dp[rowY - 1][colX] + dp[rowY][colX - 1];
					/*current = up in dp + left in dp*/
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "UniquePath DP_2D for \"" << m << "\" rows, \"" << n << "\" cols: " << dp[m - 1][n - 1] << std::endl;
		return dp[m - 1][n - 1];
	}

	int DP_1D(int m, int n)
	{
		std::vector<int> dp(n, 0);
		dp[0] = 1;
		for (int rowY = 0; rowY < m; ++rowY)
		{
			for (int colX = 1; colX < n; ++colX)
			{
				dp[colX] += dp[colX - 1];
				/*current = current in dp + left in dp*/
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		std::cout << "UniquePath DP_1D for \"" << m << "\" rows, \"" << n << "\" cols: " << dp[n - 1] << std::endl;
		return dp[n - 1];
	}

	/*
Permutation FromDupArray:
                                      n!
-----------------------------------------------------------------------------------
(dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!

   ((m-1) + (n-1))!
= ------------------
   (m-1)! * (n-1)!

   (m-1)!     m*(m+1)*...*(m+n-2)
= -------- * ---------------------
   (m-1)!           (n-1)!

   m*(m+1)*...*(m+n-2)
= ---------------------
         (n-1)!
	*/
	int Math(int m, int n)
	{
		long long res = 1;
		for (int i = 1; i < n; ++i)
		{
			res = res * (i + m - 1) / i;
		}
		std::cout << "UniquePath Math for \"" << m << "\" rows, \"" << n << "\" cols: " << (int)res << std::endl;
		return (int)res;
	}
	
	int DP_2D_wObstacle(const std::vector<std::vector<int> > & obstacleGrid)//[rowY][columnX]
	{
		if (obstacleGrid.empty() || obstacleGrid[0].empty())
			return 0;
		Debug::Print2D<int>()(obstacleGrid, false);

		int M = obstacleGrid.size();
		int N = obstacleGrid[0].size();
		std::vector<std::vector<int> > dp(M, std::vector<int>(N, 0));
		for (int rowY = 0; rowY < M; ++rowY)
		{
			for (int colX = 0; colX < N; ++colX)
			{
				if (obstacleGrid[rowY][colX])
					continue;//obstacle: can't form a path, leave it with 0
				if (rowY == 0 && colX == 0)
					dp[rowY][colX] = 1;
				else
					dp[rowY][colX] = 
					((rowY == 0) ? 0 : dp[rowY - 1][colX]) + 
					((colX == 0) ? 0 : dp[rowY][colX - 1]);
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "UniquePath DP_2D w/ Obstacle: " << dp[M - 1][N - 1] << std::endl;
		return dp[M - 1][N - 1];
	}

	int DP_1D_wObstacle(const std::vector<std::vector<int> > & obstacleGrid)//[rowY][columnX]
	{
		if (obstacleGrid.empty() || obstacleGrid[0].empty())
			return 0;
		Debug::Print2D<int>()(obstacleGrid, false);

		int M = obstacleGrid.size();
		int N = obstacleGrid[0].size();
		std::vector<int> dp(N, 0);
		dp[0] = 1;
		for (int rowY = 0; rowY < M; ++rowY)
		{
			for (int colX = 0; colX < N; ++colX)
			{
				if (obstacleGrid[rowY][colX])
					dp[colX] = 0;//obstacle: can't form a path, so the count is 0
				else if (colX > 0)
					dp[colX] += dp[colX - 1];
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}
		std::cout << "UniquePath DP_1D w/ Obstacle: " << dp[N - 1] << std::endl;
		return dp[N - 1];
	}


};
/*
[cX][rY]
Row#0	= d, d, d, d, d, d, r, r, r, r
Row#1	= d, d, d, r, r, r, d, d, d, r
Row#2	= d, r, r, d, d, r, d, d, r, d
Row#3	= r, d, r, d, r, d, d, r, d, d
Row#4	= r, r, d, r, d, d, r, d, d, d

UniquePath FindAll_Recur for "4" rows, "3" cols: 10
[cX][rY]
Row#0	= d
Row#1	= d
Row#2	= d
Row#3	= r
Row#4	= r

UniquePath DP2D_Recur for "4" rows, "3" cols: 10
[rY][cX]
Row#0	= 1, 1, 1
Row#1	= 1, 2, 3
Row#2	= 1, 3, 6
Row#3	= 1, 4, 10

UniquePath DP_2D for "4" rows, "3" cols: 10
1, 1, 1
1, 2, 3
1, 3, 6
1, 4, 10
UniquePath DP_1D for "4" rows, "3" cols: 10
UniquePath Math for "4" rows, "3" cols: 10
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 1, 0
Row#2	= 0, 0, 0, 0

[rY][cX]
Row#0	= 1, 1, 1, 1
Row#1	= 1, 2, 0, 1
Row#2	= 1, 3, 3, 4

UniquePath DP_2D w/ Obstacle: 4
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 1, 0
Row#2	= 0, 0, 0, 0

1, 1, 1, 1
1, 2, 0, 1
1, 3, 3, 4
UniquePath DP_1D w/ Obstacle: 4
*/
#endif