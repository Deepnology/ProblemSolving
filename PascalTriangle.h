/*MEMO*/
#ifndef PASCAL_TRIANGLE_H
#define PASCAL_TRIANGLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute rows in Pascal's Triangle, Compute the n-th row of Pascal's Triangle using O(n) space
http://www.geeksforgeeks.org/pascal-triangle/
Leetcode: Pascal Triangle
// Given numRows, generate the first numRows of Pascal's triangle.
//
// For example, given numRows = 5,
// Return
//
// [
//      [1],	0
//     [1,1],	1
//    [1,2,1],	2
//   [1,3,3,1],	3
//  [1,4,6,4,1]	4
// ]
//
// Complexity:
// O(n^2)

a
b c
d e f

e = b + c

Leetcode: Pascal Triangle II
// Given an index k, return the kth row of the Pascal's triangle.
//
// For example, given k = 3,
// Return [1,3,3,1].
//
// Note:
// Could you optimize your algorithm to use only O(k) extra space?
//
// Complexity:
// O(n^2) time, O(n) space

See also BinomialCoefficient.h, Combinations.h
*/
class PascalTriangle
{
public:
	PascalTriangle(){}
	~PascalTriangle(){}

	std::vector<std::vector<int> > Generate(int numRows)
	{
		std::cout << "PascalTriangle for \"" << numRows << "\" rows:" << std::endl;

		std::vector<std::vector<int> > res;//[rowY][columnX]
		for (int row = 0; row < numRows; ++row)
		{
			res.push_back(std::vector<int>(row + 1, 1));//each row has (rowIndex+1) 1s
		}
		Debug::Print2D<int>()(res, false);

		for (int row = 2; row < numRows; ++row)//from the 3rd row to bottom row
		{
			for (int col = 1; col < row; ++col)//from the "one after the first element" to "one before the last element"
				res[row][col] = res[row - 1][col - 1] + res[row - 1][col];//sum of "upper left element" and "upper element"
		}
		Debug::Print2D<int>()(res, false);
		return res;
	}
	std::vector<std::vector<int> > Generate2(int numRows)
	{
		std::vector<std::vector<int> > res;
		for (int row = 0; row < numRows; ++row)
		{
			std::vector<int> curRow(row + 1, 1);
			for (int col = 1; col < row; ++col)
			{
				curRow[col] = res.back()[col - 1] + res.back()[col];
			}
			res.emplace_back(curRow);
		}
		std::cout << "PascalTriangle for \"" << numRows << "\" rows:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}


	std::vector<int> GetRow(int rowIndex)
	{
		std::vector<int> res(rowIndex + 1, 1);//init with (rowIndex+1) 1s which is the bottom row
		for (int row = 2; row <= rowIndex; ++row)//from the 3rd row to bottom row
		{
			for (int col = row - 1; col > 0; --col)//from "one before the last element" to "one after the first element": to avoid updating "upper left element"(previous one)
				res[col] += res[col - 1];//sum of "upper element"(self) and "upper left element"(previous one)

			std::cout << "row" << row << ": " << Debug::ToStr1D<int>()(res) << std::endl;
		}

		std::cout << "PascalTriangle for \"" << rowIndex << "\"-th row: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

};
/*
PascalTriangle for "6" rows:
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,
Row#2	= 1, 1, 1,  ,  ,
Row#3	= 1, 1, 1, 1,  ,
Row#4	= 1, 1, 1, 1, 1,
Row#5	= 1, 1, 1, 1, 1, 1

[rY][cX]
Row#0	= 1,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,
Row#3	= 1, 3, 3, 1,  ,
Row#4	= 1, 4, 6, 4, 1,
Row#5	= 1, 5, 10, 10, 5, 1

PascalTriangle for "6" rows:
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,
Row#3	= 1, 3, 3, 1,  ,
Row#4	= 1, 4, 6, 4, 1,
Row#5	= 1, 5, 10, 10, 5, 1

row2: 1, 2, 1, 1, 1, 1, 1
row3: 1, 3, 3, 1, 1, 1, 1
row4: 1, 4, 6, 4, 1, 1, 1
row5: 1, 5, 10, 10, 5, 1, 1
row6: 1, 6, 15, 20, 15, 6, 1
PascalTriangle for "6"-th row: 1, 6, 15, 20, 15, 6, 1
*/



#endif