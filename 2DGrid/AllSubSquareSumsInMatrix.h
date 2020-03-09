#ifndef ALL_SUB_SQUARE_SUMS_IN_MATRIX_H
#define ALL_SUB_SQUARE_SUMS_IN_MATRIX_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/given-n-x-n-square-matrix-find-sum-sub-squares-size-k-x-k/
Given an n x n square matrix, compute all sub-square sums of size k x k where k is smaller than or equal to n.

Naive: O(k^2 * n^2) time, O(1) space
Preprocess: O(n^2) time, O(n^2) space
*/
class AllSubSquareSumsInMatrix
{
public:
	AllSubSquareSumsInMatrix(){}
	~AllSubSquareSumsInMatrix(){}

	void FindAll_Preprocess(const std::vector<std::vector<int> > & matrix, int K)
	{
		int N = matrix.size();
		std::vector<std::vector<int> > colLowerKSum(N, std::vector<int>(N));//the K pixels' sum below each pixel in the same column. colLowerKSum[rowY][colX] = sum of matrix[rowY][colX]~matrix[rowY+K-1][colX]
		std::vector<std::vector<int> > res;
		for (int col = 0; col < N; ++col)
		{
			//1. compute the 1st lower K pixels' sum below the top pixel in current column
			int sum = 0;
			for (int row = 0; row < K; ++row)
				sum += matrix[row][col];
			colLowerKSum[0][col] = sum;

			//2. compute other lower K pixels' sums for other pixels in the same column
			for (int row = 1; row < N - K + 1; ++row)
			{
				sum += (matrix[row + K - 1][col] - matrix[row - 1][col]);
				colLowerKSum[row][col] = sum;
			}
		}

		for (int row = 0; row < N - K + 1; ++row)
		{
			res.push_back(std::vector<int>());

			//1. compute the 1st right K pixels' sum of the leftmost pixel in current row
			int sum = 0;
			for (int col = 0; col < K; ++col)
				sum += colLowerKSum[row][col];

			res.back().push_back(sum);

			//2. compute other right K pixels' sum for other pixels in the same row
			for (int col = 1; col < N - K + 1; ++col)
			{
				sum += (colLowerKSum[row][col + K - 1] - colLowerKSum[row][col - 1]);
				res.back().push_back(sum);
			}
		}

		Debug::Print2D<int>()(matrix, false);
		Debug::Print2D<int>()(colLowerKSum, false);
		std::cout << "AllSubSquareSumsInMatrix FindAll_Preprocess for \"" << K << "x" << K << "\":" << std::endl;
		Debug::Print2D<int>()(res, false);
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 2, 2, 2, 2, 2
Row#2	= 3, 3, 3, 3, 3
Row#3	= 4, 4, 4, 4, 4
Row#4	= 5, 5, 5, 5, 5

[rY][cX]
Row#0	= 6, 6, 6, 6, 6
Row#1	= 9, 9, 9, 9, 9
Row#2	= 12, 12, 12, 12, 12
Row#3	= 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0

AllSubSquareSumsInMatrix FindAll_Preprocess for "3x3":
[rY][cX]
Row#0	= 18, 18, 18
Row#1	= 27, 27, 27
Row#2	= 36, 36, 36
*/
#endif