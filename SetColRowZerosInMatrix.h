#ifndef SET_COL_ROW_ZEROS_IN_MATRIX_H
#define SET_COL_ROW_ZEROS_IN_MATRIX_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Identify positions attacted by rooks
Leetcode: Set Matrix Zeros
// Given a m x n matrix, if an element is 0, set its entire row and column to
// 0. Do it in place.
//
// Follow up:
// Did you use extra space?
// A straight forward solution using O(mn) space is probably a bad idea.
// A simple improvement uses O(m + n) space, but still not the best solution.
// Could you devise a constant space solution?
//
// We can use the first row and first column to mark the columns and rows that should be all 0s.
// Before doing this, we have to first determine whether the first row and the first column should be all 0s or not.
//
// Complexity:
// O(m*n) time
*/
class SetColRowZerosInMatrix
{
public:
	SetColRowZerosInMatrix(){}
	~SetColRowZerosInMatrix(){}

	void SetZeros_LinearSpace(std::vector<std::vector<int> > & matrix)//[rowY][columnX]
	{
		std::cout << "SetColRowZerosInMatrix LinearSpace Before and After:" << std::endl;
		Debug::Print2D<int>()(matrix, false);

		int M = matrix.size();
		int N = matrix[0].size();
		std::vector<int> rowY(M, 1);//stores which row has to be set 0 entirely
		std::vector<int> colX(N, 1);//stores which column has to be set 0 entirely
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			for (int j = 0; j < N; ++j)//from left to right
				if (matrix[i][j] == 0)
					rowY[i] = colX[j] = 0;//update both
		}
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			for (int j = 0; j < N; ++j)//from left to right
				if (rowY[i] == 0 || colX[j] == 0)
					matrix[i][j] = 0;
		}

		Debug::Print2D<int>()(matrix, false);
	}

	void SetZeros_ConstantSpace(std::vector<std::vector<int> > & matrix)//[rowY][columnX]
	{
		std::cout << "SetColRowZerosInMatrix ConstantSpace Before and After:" << std::endl;
		Debug::Print2D<int>()(matrix, false);

		int M = matrix.size();
		int N = matrix[0].size();
		int firstCol = 1;
		for (int i = 0; i < M; ++i)//from top to bottom
		{
			if (matrix[i][0] == 0)
			{
				firstCol = 0;//need to set entire first col to be 0
				break;
			}
		}
		int firstRow = 1;
		for (int j = 0; j < N; ++j)
		{
			if (matrix[0][j] == 0)
			{
				firstRow = 0;//need to set entire first row to be 0
				break;
			}
		}

		for (int i = 1; i < M; ++i)//from top to bottom
		{
			for (int j = 1; j < N; ++j)//from left to right
				if (matrix[i][j] == 0)
					matrix[i][0] = matrix[0][j] = 0;//mark 0 at both first row and first col
		}
		for (int i = 1; i < M; ++i)//from top to bottom
		{
			for (int j = 1; j < N; ++j)//from left to right
				if (matrix[i][0] == 0 || matrix[0][j] == 0)//if first col or first row is 0
					matrix[i][j] = 0;
		}

		if (firstCol == 0)
		{
			for (int i = 0; i < M; ++i)
				matrix[i][0] = 0;//set entire first col to be 0
		}
		if (firstRow == 0)
		{
			for (int j = 0; j < N; ++j)
				matrix[0][j] = 0;//set entire first row to be 0
		}

		Debug::Print2D<int>()(matrix, false);
	}
};
/*
SetColRowZerosInMatrix LinearSpace Before and After:
[rY][cX]
Row#0	= 1, 0, 3, 7
Row#1	= 9, 0, 1, 2
Row#2	= 3, 8, 4, 5
Row#3	= 7, 8, 6, 9

[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 0, 0
Row#2	= 3, 0, 4, 5
Row#3	= 7, 0, 6, 9

SetColRowZerosInMatrix ConstantSpace Before and After:
[rY][cX]
Row#0	= 1, 0, 3, 7
Row#1	= 9, 0, 1, 2
Row#2	= 3, 8, 4, 5
Row#3	= 7, 8, 6, 9

[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 0, 0, 0, 0
Row#2	= 3, 0, 4, 5
Row#3	= 7, 0, 6, 9

*/
#endif