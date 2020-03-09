#ifndef MAX_RECTANGLE_H
#define MAX_RECTANGLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Find the maximum 2D subarray
http://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/
Leetcode: Maximum Rectangle
// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
// containing all ones and return its area.
//
// Complexity:
// largest rectangle in histogram O(n^2) time, O(n) space
// Brute Force: O(n^4) time, O(1) space

Special case: Find max square sub-matrix
Leetcode: Maximal Square
Given a 2D binary matrix filled with 0's and 1's, 
find the largest square containing all 1's and return its area.
For example, given the following matrix:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

DP2D: O(n^2) time, O(n^2) space
Input:
0 1 1 1 0 0 0
0 1 1 1 0 1 1
1 1 0 0 0 1 1
1 1 1 1 1 1 0
0 1 1 1 1 1 0
0 0 1 1 1 1 0
0 0 0 1 1 0 0
DP2D:
dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
0 1 1 1 0 0 0
0 1 2 2 0 1 1
1 1 0 0 0 1 2
1 2 1 1 1 1 0
0 1 2 2 2 2 0
0 0 1 2 3 3 0
0 0 0 1 2 0 0
Max square length = 3

see also RangeSumQueryWPrefixSums.h
*/
class MaxRectangle
{
public:
	MaxRectangle(){}
	~MaxRectangle(){}

	int Histogram(const std::vector<std::vector<char> > & matrix)//[rowY][columnX]
	{
		if (matrix.empty() || matrix[0].empty())
			return 0;
		int M = matrix.size();
		int N = matrix[0].size();
		std::vector<int> hs(N + 1, 0);
		std::stack<int> stk;
		int res = 0;
		for (int rowY = 0; rowY < M; ++rowY)//from top to bottom
		{
			//1. build histogram for the area between top row and current row
			for (int colX = 0; colX < N; ++colX)//from left to right
			{
				if (matrix[rowY][colX] == '0')
					hs[colX] = 0;
				else
					++hs[colX];
			}

			//2. compute max rectangle in histogram for the area between top row and current row (same as LargestRectHistogram.h)
			for (int colX = 0; colX <= N; ++colX)
			{
				while (!stk.empty() && hs[stk.top()] >= hs[colX])
				{
					int h = hs[stk.top()];
					stk.pop();
					int w = stk.empty() ? colX : (colX - stk.top() - 1);
					res = std::max(res, h*w);
				}
				if (colX != N)
					stk.push(colX);
			}
		}
		Debug::Print2D<char>()(matrix, false);
		std::cout << "MaxRectangle Histogram: " << res << std::endl;
		return res;
	}

	int BruteForce(const std::vector<std::vector<char> > & matrix)//[rowY][columnX]
	{
		if (matrix.empty() || matrix[0].empty())
			return 0;
		int M = matrix.size();
		int N = matrix[0].size();
		int res = 0;
		for (int rowY = 0; rowY < M; ++rowY)//from top to bottom
			for (int colX = 0; colX < N; ++colX)//from left to right
				if (matrix[rowY][colX] == '1')
				{
					int area = this->rectAreaAt(matrix, M, N, rowY, colX);
					if (area > res)
						res = area;
				}
		Debug::Print2D<char>()(matrix, false);
		std::cout << "MaxRectangle BruteForce: " << res << std::endl;
		return res;
	}
private:
	int rectAreaAt(const std::vector<std::vector<char> > & matrix, int M, int N, int rowY, int colX)//rectangle area at top left corner (rowY,colX)
	{
		int minLenX = INT_MAX;
		int maxArea = 0;
		for (int row = rowY; row < M && matrix[row][colX] == '1'; ++row)//from top to bottom
		{
			//compute length of consecutive 1's in current row, and keep track of the shortest length in each row
			int lenX = 0;
			while (colX + lenX < N && matrix[row][colX + lenX] == '1')//from left to right
				++lenX;
			if (lenX < minLenX)
				minLenX = lenX;
			int curArea = (row - rowY + 1) * minLenX;
			if (maxArea < curArea)
				maxArea = curArea;
		}
		return maxArea;
	}


public:
	/*special case: find square sub-matrix*/
	int DP2D_SquareSubmatrix(const std::vector<std::vector<char> > & matrix)
	{
		if (matrix.empty() || matrix[0].empty())
			return 0;
		int M = matrix.size();
		int N = matrix[0].size();

		//keep track of the max square sub-matrix border length of the upper left area of each pixel
		std::vector<std::vector<int> > dp(M, std::vector<int>(N));
		for (int rowY = 0; rowY < M; ++rowY)
			dp[rowY][0] = matrix[rowY][0] - '0';
		for (int colX = 0; colX < N; ++colX)
			dp[0][colX] = matrix[0][colX] - '0';
		for (int rowY = 1; rowY < M; ++rowY)
		{
			for (int colX = 1; colX < N; ++colX)
			{
				if (matrix[rowY][colX] == '1')
					dp[rowY][colX] = std::min(std::min(dp[rowY][colX - 1], dp[rowY - 1][colX]), dp[rowY - 1][colX - 1]) + 1;
				else
					dp[rowY][colX] = 0;
			}
		}

		/*now the max area is the max value in dp*/
		int len = dp[0][0];
		int rowY = 0;
		int colX = 0;
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (len < dp[i][j])
				{
					len = dp[i][j];
					rowY = i;
					colX = j;
				}
			}
		}
		Debug::Print2D<char>()(matrix, false);
		Debug::Print2D<int>()(dp, false);
		std::cout << "MaxRectangle DP2D_SquareSubmatrix: " << len << ", [" << rowY << "][" << colX << "]" << std::endl;
		return len;
	}
};
/*
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0
Row#1	= 0, 1, 1, 1, 0, 1, 1
Row#2	= 1, 1, 0, 0, 0, 1, 1
Row#3	= 1, 1, 1, 1, 1, 1, 0
Row#4	= 0, 1, 1, 1, 1, 1, 0
Row#5	= 0, 0, 1, 1, 1, 1, 0
Row#6	= 0, 0, 0, 1, 1, 0, 0

MaxRectangle Histogram: 12
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0
Row#1	= 0, 1, 1, 1, 0, 1, 1
Row#2	= 1, 1, 0, 0, 0, 1, 1
Row#3	= 1, 1, 1, 1, 1, 1, 0
Row#4	= 0, 1, 1, 1, 1, 1, 0
Row#5	= 0, 0, 1, 1, 1, 1, 0
Row#6	= 0, 0, 0, 1, 1, 0, 0

MaxRectangle BruteForce: 12
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0
Row#1	= 0, 1, 1, 1, 0, 1, 1
Row#2	= 1, 1, 0, 0, 0, 1, 1
Row#3	= 1, 1, 1, 1, 1, 1, 0
Row#4	= 0, 1, 1, 1, 1, 1, 0
Row#5	= 0, 0, 1, 1, 1, 1, 0
Row#6	= 0, 0, 0, 1, 1, 0, 0

[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0
Row#1	= 0, 1, 2, 2, 0, 1, 1
Row#2	= 1, 1, 0, 0, 0, 1, 2
Row#3	= 1, 2, 1, 1, 1, 1, 0
Row#4	= 0, 1, 2, 2, 2, 2, 0
Row#5	= 0, 0, 1, 2, 3, 3, 0
Row#6	= 0, 0, 0, 1, 2, 0, 0

MaxRectangle DP2D_SquareSubmatrix: 3, [5][4]
[rY][cX]
Row#0	= 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 1, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 1, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 1, 1, 1, 1, 1, 0, 0, 1, 0, 1
Row#5	= 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
Row#6	= 1, 0, 0, 1, 1, 0, 0, 1, 0, 1
Row#7	= 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
Row#9	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1

[rY][cX]
Row#0	= 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 1, 2, 2, 1, 1, 0, 0, 0, 0, 0
Row#2	= 1, 2, 3, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 1, 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 1, 1, 1, 1, 2, 0, 0, 1, 0, 1
Row#5	= 1, 0, 0, 1, 0, 0, 0, 1, 0, 1
Row#6	= 1, 0, 0, 1, 1, 0, 0, 1, 0, 1
Row#7	= 1, 1, 1, 1, 2, 1, 1, 1, 0, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
Row#9	= 0, 0, 0, 1, 1, 1, 1, 1, 1, 1

MaxRectangle DP2D_SquareSubmatrix: 3, [2][2]
*/
#endif