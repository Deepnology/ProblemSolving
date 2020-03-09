#ifndef SADDLEBACK_SEARCH_SORTED_MATRIX_H
#define SADDLEBACK_SEARCH_SORTED_MATRIX_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
This is the upper right linear search in 2D sorted matrix.
The 2d matrix is sorted in row-wise and column-wise in non-descending order.
The first integer of each row is NOT necessarily greater than the last integer of the previous row.

O(m+n) time

See also Search2dSortedMatrix.h
*/
class SaddlebackSearchSortedMatrix
{
public:
	SaddlebackSearchSortedMatrix(){}
	~SaddlebackSearchSortedMatrix(){}

	/*first found must be the upper RIGHT corner occurrence*/
	bool FirstFound(const std::vector<std::vector<int> > & m, int tgt, int & rowY, int & colX)
	{
		int M = m.size();
		int N = m[0].size();
		rowY = 0;
		colX = N - 1;
		while (rowY < M && colX >= 0)
		{
			if (m[rowY][colX] < tgt)
				++rowY;
			else if (m[rowY][colX] > tgt)
				--colX;
			else
				break;
		}

		Debug::Print2D<int>()(m, false);
		std::ostringstream oss;
		if (rowY == M || colX == -1)
			oss << "N";
		else
			oss << "[" << rowY << "," << colX << "]";
		std::cout << "SaddlebackSearchSortedMatrix FirstFound for \"" << tgt << "\": " << oss.str() << std::endl;
		return rowY != M && colX != -1;
	}

	/*first occurrence must be the upper LEFT corner occurrence*/
	bool FirstOccurrence(const std::vector<std::vector<int> > & m, int tgt, int & rowY, int & colX)
	{
		int M = m.size();
		int N = m[0].size();
		rowY = 0;
		colX = N - 1;
		while (rowY < M && colX >= 0)
		{
			if (m[rowY][colX] < tgt)
				++rowY;
			else if (m[rowY][colX] > tgt)
				--colX;
			else
				break;
		}
		if (rowY != M && colX != -1)
		{
			/*go to the leftmost element in current row*/
			while (m[rowY][colX] == tgt)
				--colX;
			++colX;
		}

		Debug::Print2D<int>()(m, false);
		std::ostringstream oss;
		if (rowY == M || colX == -1)
			oss << "N";
		else
			oss << "[" << rowY << "," << colX << "]";
		std::cout << "SaddlebackSearchSortedMatrix FirstOccurrence for \"" << tgt << "\": " << oss.str() << std::endl;
		return rowY != M && colX != -1;
	}

	std::vector<std::pair<int, int> > AllOccurrences(const std::vector<std::vector<int> > & m, int tgt)
	{
		int M = m.size();
		int N = m[0].size();
		std::vector<std::pair<int, int> > res;
		int rowY = 0;
		int colX = N - 1;
		while (rowY < M && colX >= 0)
		{
			if (m[rowY][colX] < tgt)
				++rowY;
			else if (m[rowY][colX] > tgt)
				--colX;
			else
			{
				int col = colX;
				while (col >= 0 && m[rowY][col] == tgt)
					res.push_back(std::make_pair(rowY, col--));/*append all occurrences to the left in current row*/
				++rowY;/*advance rowY while keeping colX*/
			}
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "SaddlebackSearchSortedMatrix AllOccurrences for \"" << tgt << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	int Count(const std::vector<std::vector<int> > & m, int tgt)
	{
		int M = m.size();
		int N = m[0].size();
		int count = 0;
		int rowY = 0;
		int colX = N - 1;
		while (rowY < M && colX >= 0)
		{
			if (m[rowY][colX] < tgt)
				++rowY;
			else if (m[rowY][colX] > tgt)
				--colX;
			else
			{
				int col = colX;
				while (col >= 0 && m[rowY][col] == tgt)
				{
					++count;/*accumulate all occurrences to the left in current row*/
					--col;
				}
				++rowY;/*advance rowY while keeping colX*/
			}
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "SaddlebackSearchSortedMatrix Count for \"" << tgt << "\": " << count << std::endl;
		return count;
	}
};
/*
[rY][cX]
Row#0	= 2, 2, 3, 5
Row#1	= 3, 4, 6, 6
Row#2	= 3, 5, 6, 6
Row#3	= 3, 6, 6, 9

SaddlebackSearchSortedMatrix FirstFound for "6": [1,3]
[rY][cX]
Row#0	= 2, 2, 3, 5
Row#1	= 3, 4, 6, 6
Row#2	= 3, 5, 6, 6
Row#3	= 3, 6, 6, 9

SaddlebackSearchSortedMatrix FirstOccurrence for "6": [1,2]
[rY][cX]
Row#0	= 2, 2, 3, 5
Row#1	= 3, 4, 6, 6
Row#2	= 3, 5, 6, 6
Row#3	= 3, 6, 6, 9

SaddlebackSearchSortedMatrix AllOccurrences for "6": [1,3], [1,2], [2,3], [2,2], [3,2], [3,1]
[rY][cX]
Row#0	= 2, 2, 3, 5
Row#1	= 3, 4, 6, 6
Row#2	= 3, 5, 6, 6
Row#3	= 3, 6, 6, 9

SaddlebackSearchSortedMatrix Count for "6": 6
*/
#endif