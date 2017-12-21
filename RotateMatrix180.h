/*MEMO*/
#ifndef ROTATE_MATRIX_180_H
#define ROTATE_MATRIX_180_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
https://sites.google.com/site/spaceofjameschen/home/array/is-the-rotated-matrix-same-google
http://www.careercup.com/question?id=19503663
Google
Given a 2D rectangular matrix of boolean values.
Determine if the matrix is the same when rotated 180 degrees.

11 12 13 14 15
21 22 23 24 25
31 32 33 32 31
25 24 23 22 21
15 14 13 12 11

11 12 13 14 15
21 22 23 24 25
31 32 33 34 35
35 34 33 32 31
25 24 23 22 21
15 14 13 12 11
*/
class RotateMatrix180
{
public:
	RotateMatrix180(){}
	~RotateMatrix180(){}

	bool IsSame(const std::vector<std::vector<int> > & matrix)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();
		bool res = true;
		for (int i = 0; i < (rows + 1) / 2; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (matrix[i][j] != matrix[rows - 1 - i][cols - 1 - j])
				{
					res = false;
					break;
				}
			}
			if (!res)
				break;
		}
		Debug::Print2D<int>()(matrix, false);
		std::cout << "RotateMatrix180 IsSame: " << res << std::endl;
		return res;
	}

	void Rotate(std::vector<std::vector<int> > & matrix)
	{
		std::cout << "RotateMatrix180 Rotate Before and After: " << std::endl;
		Debug::Print2D<int>()(matrix, false);
		int N = matrix.size();
		int M = matrix[0].size();
		for (int i = 0; i < (N + 1) / 2; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				std::swap(matrix[i][j], matrix[N - 1 - i][M - 1 - j]);
			}
		}
		Debug::Print2D<int>()(matrix, false);
	}
};
/*
RotateMatrix180 Rotate Before and After:
[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45
Row#4	= 51, 52, 53, 54, 55
Row#5	= 61, 62, 63, 64, 65

[rY][cX]
Row#0	= 65, 64, 63, 62, 61
Row#1	= 55, 54, 53, 52, 51
Row#2	= 45, 44, 43, 42, 41
Row#3	= 35, 34, 33, 32, 31
Row#4	= 25, 24, 23, 22, 21
Row#5	= 15, 14, 13, 12, 11

[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 32, 31
Row#3	= 25, 24, 23, 22, 21
Row#4	= 15, 14, 13, 12, 11

RotateMatrix180 IsSame: 1
*/
#endif