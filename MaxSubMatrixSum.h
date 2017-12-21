#ifndef MAX_SUB_MATRIX_SUM_H
#define MAX_SUB_MATRIX_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Cracking the coding interview: Hard
http://www.geeksforgeeks.org/dynamic-programming-set-27-max-sum-rectangle-in-a-2d-matrix/
http://stackoverflow.com/questions/2643908/getting-the-submatrix-with-maximum-sum
Given a 2D array, find the max submatrix sum in it.

Brute Force: O(n^6) time
Kadane's Algorithm: O(n^3) time, O(n) space

See also MaxSubArraySum.h
*/
class MaxSubMatrixSum
{
public:
	MaxSubMatrixSum(){}
	~MaxSubMatrixSum(){}

	//enumerate all possible sub-matrix between rowUpper, rowBottom, colLeft, and colRight
	int BruteForce(const std::vector<std::vector<int> > & matrix)
	{
		int N = matrix.size();
		int M = matrix[0].size();
		int maxArea = INT_MIN;
		int maxTopRowY;
		int maxBottomRowY;
		int maxLeftColX;
		int maxRightColX;

		for (int rowUpper = 0; rowUpper < N - 1; ++rowUpper)
			for (int colLeft = 0; colLeft < M - 1; ++colLeft)
				for (int rowBottom = rowUpper + 1; rowBottom < N; ++rowBottom)
					for (int colRight = colLeft + 1; colRight < M; ++colRight)
					{
						int area = 0;
						for (int row = rowUpper; row <= rowBottom; ++row)
							for (int col = colLeft; col <= colRight; ++col)
								area += matrix[row][col];
						if (area > maxArea)
						{
							maxArea = area;
							maxTopRowY = rowUpper;
							maxBottomRowY = rowBottom;
							maxLeftColX = colLeft;
							maxRightColX = colRight;
						}
					}

		Debug::Print2D<int>()(matrix, false);
		std::cout << "MaxSubMatrixSum BruteForce, RowY[Top,Bottom], ColX[Left,Right]: " << maxArea << ", [" << maxTopRowY << "," << maxBottomRowY << "], [" << maxLeftColX << "," << maxRightColX << "]" << std::endl;
		return maxArea;
	}

	//enumerate all possible sub-matrix (with full row size) between topRowY and bottomRowY
	int UseKandane(const std::vector<std::vector<int> > & matrix)
	{
		int N = matrix.size();
		int M = matrix[0].size();
		int maxLeftColX;
		int maxRightColX;
		int maxTopRowY;
		int maxBottomRowY;
		int maxSum = INT_MIN;
		for (int topRowY = 0; topRowY < N; ++topRowY)
		{
			std::vector<int> subMatrixSum(M, 0);
			for (int bottomRowY = topRowY; bottomRowY < N; ++bottomRowY)
			{
				for (int col = 0; col < M; ++col)
				{
					subMatrixSum[col] += matrix[bottomRowY][col];
				}

				/*
				now the sub matrix sum in the range of row[topRowY, bottomRowY], col[0, M) has been added in the 1D array subMatrixSum
				we then need to find out 1D max sub array sum and leftColX and rightColX from subMatrixSum with Kadane's Algorithm
				*/
				int leftColX;
				int rightColX;
				int maxSubMatrixSum = this->MaxSubArraySum_DP_2Pass(subMatrixSum, leftColX, rightColX);
				if (maxSubMatrixSum > maxSum)
				{
					maxSum = maxSubMatrixSum;
					maxLeftColX = leftColX;
					maxRightColX = rightColX;
					maxTopRowY = topRowY;
					maxBottomRowY = bottomRowY;
				}
			}
		}

		Debug::Print2D<int>()(matrix, false);
		std::cout << "MaxSubMatrixSum, UseKadane, RowY[Top,Bottom], ColX[Left,Right]: " << maxSum << ", [" << maxTopRowY << "," << maxBottomRowY << "], [" << maxLeftColX << "," << maxRightColX << "]" << std::endl;
		return maxSum;
	}

private:
	/*Kadane's Algorithm*/
	int MaxSubArraySum_DP_2Pass(const std::vector<int> & v, int & begin, int & end)
	{
		int N = v.size();
		int sum = 0;
		int maxSum = INT_MIN;
		end = -1;
		int positiveBegin = 0;

		for (int i = 0; i < N; ++i)
		{
			sum += v[i];

			/*when sum is negative, we reset it and positiveBegin*/
			if (sum < 0)
			{
				sum = 0;
				positiveBegin = i + 1;
				continue;
			}

			/*we only update maxSum, begin, and end when sum is 0 or positive*/
			if (sum > maxSum)
			{
				maxSum = sum;
				begin = positiveBegin;
				end = i;
			}
		}

		/*
		special case when all elements are negative (sum never became positive or 0):
		just need find the max negative element
		*/
		if (end == -1)
		{
			maxSum = v[0];
			begin = end = 0;
			for (int i = 1; i < N; ++i)
			{
				if (v[i] > maxSum)
				{
					maxSum = v[i];
					begin = end = i;
				}
			}
		}

		return maxSum;
	}
};
/*
[rY][cX]
Row#0	= 1, 2, -1, -4, -20
Row#1	= -8, -3, 4, 2, 1
Row#2	= 3, 8, 10, 1, 3
Row#3	= -4, -1, 1, 7, -6

MaxSubMatrixSum BruteForce, RowY[Top,Bottom], ColX[Left,Right]: 29, [1,3], [1,3]
[rY][cX]
Row#0	= 1, 2, -1, -4, -20
Row#1	= -8, -3, 4, 2, 1
Row#2	= 3, 8, 10, 1, 3
Row#3	= -4, -1, 1, 7, -6

MaxSubMatrixSum, UseKadane, RowY[Top,Bottom], ColX[Left,Right]: 29, [1,3], [1,3]
*/
#endif