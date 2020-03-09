/*MEMO*/
#ifndef SPIRAL_MATRIX_H
#define SPIRAL_MATRIX_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Print a 2D array in spiral order
Leetcode: Spiral Matrix
// Given a matrix of m x n elements (m rows, n columns), return all elements
// of the matrix in spiral order.
//
// For example,
// Given the following matrix:
//
// [
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
// ]
// You should return [1,2,3,6,9,8,7,4,5].
//
// Complexity:
// O(m*n)

Leetcode: Spiral Matrix II
Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.
For example,
Given n = 3,
You should return the following matrix:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]

Leetcode: Spiral Matrix III
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.
Here, the north-west corner of the grid is at the first row and column, and the south-east corner of the grid is at the last row and column.
Now, we walk in a clockwise spiral shape to visit every position in this grid.
Whenever we would move outside the boundary of the grid, we continue our walk outside the grid (but may return to the grid boundary later.)
Eventually, we reach all R * C spaces of the grid.
Return a list of coordinates representing the positions of the grid in the order they were visited.
Example 1:
Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]
Example 2:
Input: R = 5, C = 6, r0 = 1, c0 = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
*/
class SpiralMatrix
{
public:
	SpiralMatrix(){}
	~SpiralMatrix(){}

	std::vector<int> Iterate(const std::vector<std::vector<int> > & matrix)//[rowY][columnX]
	{
		std::vector<int> res;
		if (matrix.empty() || matrix[0].empty())
			return res;
		int M = matrix.size();
		int N = matrix[0].size();
		/*
		for each circle from outter to inner. starting point martrix[diag][diag] advances in diagonal direction.
		diag: diagonal index (circle from outter to inner)
		*/
		for (int diag = 0, rowCount = M, colCount = N; rowCount > 0 && colCount > 0; ++diag, rowCount -= 2, colCount -= 2)
		{
			int row = 0;
			int col = 0;
			if (rowCount == 1)//when M is odd and one row left => middle row
			{
				for (; col < colCount; ++col)//go right in middle row
					res.push_back(matrix[diag + row][diag + col]);
				break;
			}
			if (colCount == 1)//when N is odd and one column left => middle column
			{
				for (; row < rowCount; ++row)//go down in middle column
					res.push_back(matrix[diag + row][diag + col]);
				break;
			}

			for (; col < colCount - 1; ++col)//1. go right in top row, stop before the last one
				res.push_back(matrix[diag + row][diag + col]);
			for (; row < rowCount - 1; ++row)//2. go down in rightmost column, stop before the last one
				res.push_back(matrix[diag + row][diag + col]);
			for (; col > 0; --col)//3. go left in bottom row, stop before the last one
				res.push_back(matrix[diag + row][diag + col]);
			for (; row > 0; --row)//4. go up in leftmost column, stop before the last one
				res.push_back(matrix[diag + row][diag + col]);
		}
		
		Debug::Print2D<int>()(matrix, false);
		std::cout << "SpiralMatrix Iterate is: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Recur(const std::vector<std::vector<int> > & matrix)//[rowY][columnX]
	{
		int M = matrix.size();
		int N = matrix[0].size();
		std::vector<int> res;
		this->recur(matrix, M, N, 0, res);
		Debug::Print2D<int>()(matrix, false);
		std::cout << "SpiralMatrix Recur is: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::vector < std::vector<int> > & matrix
		, int rowCount, int colCount, int diag, std::vector<int> & res)
	{
		if (rowCount <= 0 || colCount <= 0)
			return;
		int row = 0;
		int col = 0;
		if (rowCount == 1)
		{
			for (; col < colCount; ++col)
				res.push_back(matrix[diag + row][diag + col]);
			return;
		}
		if (colCount == 1)
		{
			for (; row < rowCount; ++row)
				res.push_back(matrix[diag + row][diag + col]);
			return;
		}

		for (; col < colCount - 1; ++col)
			res.push_back(matrix[diag + row][diag + col]);
		for (; row < rowCount - 1; ++row)
			res.push_back(matrix[diag + row][diag + col]);
		for (; col > 0; --col)
			res.push_back(matrix[diag + row][diag + col]);
		for (; row > 0; --row)
			res.push_back(matrix[diag + row][diag + col]);

		this->recur(matrix, rowCount - 2, colCount - 2, diag + 1, res);
	}

public:
	std::vector<std::vector<int> > Generate(int n)
	{
		std::vector<std::vector<int> > res(n, std::vector<int>(n));
		int count = 0;
		for (int diag = 0, rowCount = n, colCount = n; rowCount > 0 && colCount > 0; ++diag, rowCount -= 2, colCount -= 2)
		{
			int row = 0;
			int col = 0;
			if (rowCount == 1)
			{
				for (; col < colCount; ++col)//final row: left to right
					res[diag + row][diag + col] = ++count;
				break;
			}
			if (colCount == 1)
			{
				for (; row < rowCount; ++row)//final col: top to bottom
					res[diag + row][diag + col] = ++count;
				break;
			}

			for (; col < colCount - 1; ++col)//1. top row: left to right (leave the last col for step 2)
				res[diag + row][diag + col] = ++count;
			for (; row < rowCount - 1; ++row)//2. right col: top to bottom (leave the last row for step 3)
				res[diag + row][diag + col] = ++count;
			for (; col > 0; --col)//3. bottom row: right to left (leave the last col for step 4)
				res[diag + row][diag + col] = ++count;
			for (; row > 0; --row)//4. left col: bottom to top
				res[diag + row][diag + col] = ++count;
		}

		std::cout << "SpiralMatrix Generate for \"" << n << "x" << n << "\": " << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

public:
	//Spiral Matrix III
	std::vector<std::vector<int>> Clockwise_RDLU_Path(int R, int C, int r0, int c0)
	{
		std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});//right,down,left,up
		std::vector<std::vector<int>> res;
		res.push_back({r0,c0});
		int d = 0;
		int len = 0;
		while (res.size() < R*C)
		{
			if (d == 0 || d == 2) ++len;//when moving right or left
			int move = len;
			while (move-- > 0)
			{
				r0 += dir[d][0];
				c0 += dir[d][1];
				if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C)
					res.push_back({r0,c0});
			}
			d = (d+1)%4;
		}

		std::cout << "SpiralMatrix Clockwise_RDLU_Path in [" << R << "," << C << "] starting at [" << r0 << "," << c0 << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45

SpiralMatrix Iterate is: 11, 12, 13, 14, 15, 25, 35, 45, 44, 43, 42, 41, 31, 21, 22, 23, 24, 34, 33, 32
[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45

SpiralMatrix Recur is: 11, 12, 13, 14, 15, 25, 35, 45, 44, 43, 42, 41, 31, 21, 22, 23, 24, 34, 33, 32
[rY][cX]
Row#0	= 11, 12, 13, 14
Row#1	= 21, 22, 23, 24
Row#2	= 31, 32, 33, 34
Row#3	= 41, 42, 43, 44
Row#4	= 51, 52, 53, 54

SpiralMatrix Iterate is: 11, 12, 13, 14, 24, 34, 44, 54, 53, 52, 51, 41, 31, 21, 22, 23, 33, 43, 42, 32
[rY][cX]
Row#0	= 11, 12, 13, 14
Row#1	= 21, 22, 23, 24
Row#2	= 31, 32, 33, 34
Row#3	= 41, 42, 43, 44
Row#4	= 51, 52, 53, 54

SpiralMatrix Recur is: 11, 12, 13, 14, 24, 34, 44, 54, 53, 52, 51, 41, 31, 21, 22, 23, 33, 43, 42, 32
SpiralMatrix Generate for "5x5":
[rY][cX]
Row#0	= 1, 2, 3, 4, 5
Row#1	= 16, 17, 18, 19, 6
Row#2	= 15, 24, 25, 20, 7
Row#3	= 14, 23, 22, 21, 8
Row#4	= 13, 12, 11, 10, 9

SpiralMatrix Clockwise_RDLU_Path in [1,4] starting at [3,3]: [0,0], [0,1], [0,2], [0,3]
*/
#endif