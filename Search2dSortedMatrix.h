#ifndef SEARCH_2D_SORTED_MATRIX_H
#define SEARCH_2D_SORTED_MATRIX_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search in a 2D sorted array
http://leetcode.com/2010/10/searching-2d-sorted-matrix.html
http://leetcode.com/2010/10/searching-2d-sorted-matrix-part-ii.html
http://leetcode.com/2010/10/searching-2d-sorted-matrix-part-iii.html
https://github.com/anson627/leetcode/blob/master/Searcha2DMatrix/Searcha2DMatrix.cpp
// Write an efficient algorithm that searches for a value in an m x n matrix.
// This matrix has the following properties:
//
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.
// For example,
//
// Consider the following matrix:
//
// [
//  [1,   3,  5,  7],
//  [10, 11, 16, 20],
//  [23, 30, 34, 50]
// ]
// Given target = 3, return true.
//
// Complexity:
// Upper Right Linear Search: O(m+n) time, see also SaddlebackSearchSortedMatrix.h
// 2D Quad Search: O(3^log(max(m,n))) = O(max(m,n)^log3) = O(max(m,n)^1.58) time
// 1D Binary Search: O(log(m*n)) time
// 2D Binary Search: O(max(m,n)*log(max(m,n))) time

See also RMQ2DSegmentTree2D.h
*/
class Search2dSortedMatrix
{
public:
	Search2dSortedMatrix(){}
	~Search2dSortedMatrix(){}

	bool UpperRightLinearSearch(const std::vector<std::vector<int> > & matrix, int target)//[rowY][columnX]
	{
		Debug::Print2D<int>()(matrix, false);

		int M = matrix.size();
		int N = matrix[0].size();
		int i = 0;
		int j = N - 1;
		while (i < M && j >= 0)//[i][j] starting from the top right corner
		{
			if (matrix[i][j] == target)
			{
				std::cout << "Search2dSortedMatrix UpperRightLinearSearch Found \"" << target << "\" at [" << i << "][" << j << "]" << std::endl;
				return true;
			}
			/*
			compare the rightmost element of each row with the target from top to bottom
			once found a rightmost element of a row that is greater than or equal to target
			=> the target must be in that row
			then check one by one from right to left in that row if found a match
			*/
			else if (matrix[i][j] < target)
				++i;
			else
				--j;
		}

		std::cout << "Search2dSortedMatrix UpperRightLinearSearch Found \"" << target << "\": 0" << std::endl;
		return false;
	}

public:
	bool TwoDQuadSearchRecur(const std::vector<std::vector<int> > & matrix, int target)//[rowY][columnX]
	{
		if (matrix.empty() || matrix[0].empty())
			return false;
		int M = matrix.size();
		int N = matrix[0].size();

		bool res = this->twoDQuadSearchRecur(matrix, target, -1, M, -1, N);
		bool res2 = this->twoDQuadSearchRecur2(matrix, target, 0, M - 1, 0, N - 1);//better
		Debug::Print2D<int>()(matrix, false);
		std::cout << "Search2dSortedMatrix 2DQuadSearchRecur Found \"" << target << "\": " << res << ", " << res2 << std::endl;
		return res;
	}
private:
	bool twoDQuadSearchRecur(const std::vector<std::vector<int> > & matrix, int target
		, int upper, int lower, int left, int right)
	{
		int M = matrix.size();
		int N = matrix[0].size();
		if (right - left <= 1 && lower - upper <= 1)
		{
			if (right == N || lower == M)
				return false;
			else if (matrix[lower][right] == target)
			{
				std::cout << "Found [" << lower << "," << right << "]: " << matrix[lower][right] << std::endl;
				return true;
			}
			else
				return false;
		}
		int midRow = (upper + lower) / 2;
		int midCol = (left + right) / 2;
		if (matrix[midRow][midCol] >= target)//eliminate lower right quad
		{
			return this->twoDQuadSearchRecur(matrix, target, upper, midRow, left, midCol) ||//upper left quad
				this->twoDQuadSearchRecur(matrix, target, upper, midRow, midCol, right) ||//upper right quad
				this->twoDQuadSearchRecur(matrix, target, midRow, lower, left, midCol);//lower left quad
		}
		else//elimiate upper left quad
		{
			return this->twoDQuadSearchRecur(matrix, target, midRow, lower, midCol, right) ||//lower right quad
				this->twoDQuadSearchRecur(matrix, target, upper, midRow, midCol, right) ||//upper right quad
				this->twoDQuadSearchRecur(matrix, target, midRow, lower, left, midCol);//lower left quad
		}
	}
	bool twoDQuadSearchRecur2(const std::vector<std::vector<int> > & matrix, int target
		, int upper, int lower, int left, int right)
	{
		int M = matrix.size();
		int N = matrix[0].size();
		if (upper > lower || left > right)
			return false;
		if (target < matrix[upper][left] || target > matrix[lower][right])
			return false;

		int midRow = upper + (lower - upper) / 2;
		int midCol = left + (right - left) / 2;
		if (matrix[midRow][midCol] == target)
			return true;
		if (matrix[midRow][midCol] > target)//eliminate lower right quad
		{
			return this->twoDQuadSearchRecur2(matrix, target, upper, midRow, left, midCol) ||//upper left quad. including: curRow, curCol
				this->twoDQuadSearchRecur2(matrix, target, upper, midRow, midCol + 1, right) ||//upper right quad. including: curRow
				this->twoDQuadSearchRecur2(matrix, target, midRow + 1, lower, left, midCol);//lower left quad. including: curCol
		}
		else//elimiate upper left quad
		{
			return this->twoDQuadSearchRecur2(matrix, target, midRow, lower, midCol + 1, right) ||//lower right quad. including: curRow
				this->twoDQuadSearchRecur2(matrix, target, upper, midRow + 1, midCol + 1, right) ||//upper right quad. including: 
				this->twoDQuadSearchRecur2(matrix, target, midRow + 1, lower, left, midCol);//lower left quad. including: curCol
		}
	}

public:
	//only this approach is not working for 2d matrix where the first integer of each row is NOT necessarily greater than the last integer of the previous row.
	bool OneDBinarySearch(const std::vector<std::vector<int> > & matrix, int target)//[rowY][columnX]
	{
		Debug::Print2D<int>()(matrix, false);

		int M = matrix.size();
		int N = matrix[0].size();//row size
		int left = 0;
		int right = M*N - 1;
		while (left <= right)
		{
			int middle = left + (right - left) / 2;
			/*
			middle / N = rowY index
			middle % N = columnX index
			*/
			if (matrix[middle / N][middle % N] >= target)
				right = middle - 1;
			else
				left = middle + 1;
		}
		//now left is the lower bound
		bool res = (left <= (M*N-1) && matrix[left / N][left % N] == target);

		std::cout << "Search2dSortedMatrix 1DBinarySearch Found \"" << target << "\": " << res << std::endl;
		return res;
	}

public:
	bool TwoDBinarySearchRecur(const std::vector<std::vector<int> > & matrix, int target)//[rowY][columnX]
	{
		if (matrix.empty() || matrix[0].empty())
			return false;
		int M = matrix.size();
		int N = matrix[0].size();
		bool res = this->binarySearchRowRecur(matrix, target, 0, M - 1, 0, N - 1);

		Debug::Print2D<int>()(matrix, false);
		std::cout << "Search2dSortedMatrix 2DBinarySearchRecur Found \"" << target << "\": " << res << std::endl;
		return res;
	}
private:
	bool binarySearchRowRecur(const std::vector<std::vector<int>> & matrix, int target, int upper, int lower, int left, int right)
	{
		if (upper > lower)
			return false;
		int midRow = (upper + lower) / 2;
		if (this->binarySearchColRecur(matrix, target, midRow, left, right))
			return true;

		//now need to binary search both sides!!!
		if (this->binarySearchRowRecur(matrix, target, upper, midRow - 1, left, right))
			return true;
		return this->binarySearchRowRecur(matrix, target, midRow + 1, lower, left, right);
	}
	bool binarySearchColRecur(const std::vector<std::vector<int>> & matrix, int target, int row, int left, int right)
	{
		if (left > right)
			return false;
		int midCol = (left + right) / 2;
		if (matrix[row][midCol] == target)
		{
			std::cout << "Search2dSortedMatrix 2DBinarySearchRecur Found target at [" << row << "][" << midCol << "]" << std::endl;
			return true;
		}
		else if (matrix[row][midCol] > target)
			return this->binarySearchColRecur(matrix, target, row, left, midCol - 1);
		else
			return this->binarySearchColRecur(matrix, target, row, midCol + 1, right);
	}

public:
	bool TwoDBinarySearchRecur2(const std::vector<std::vector<int> > & matrix, int target)//[rowY][columnX]
	{
		if (matrix.empty() || matrix[0].empty())
			return false;
		int M = matrix.size();
		int N = matrix[0].size();
		bool res = this->twoDBinarySearchRecur(matrix, target, 0, M - 1, 0, N - 1);

		Debug::Print2D<int>()(matrix, false);
		std::cout << "Search2dSortedMatrix 2DBinarySearchRecur2 Found \"" << target << "\": " << res << std::endl;
		return res;
	}
private:
	bool twoDBinarySearchRecur(const std::vector<std::vector<int> > & matrix, int target
		, int upper, int lower, int left, int right)
	{
		if (upper > lower || left > right)
			return false;
		
		int curCol = left + (right - left) / 2;
		int curRow;
		//for (curRow = upper; curRow <= lower; ++curRow)
		//{
		//	if (matrix[curRow][curCol] == target)
		//	{
		//		std::cout << "Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [" << curRow << "][" << curCol << "]" << std::endl;
		//		return true;
		//	}
		//	else if (matrix[curRow][curCol] > target)
		//		break;
		//}
		curRow = this->rowLowerBound(matrix, curCol, target, upper, lower);
		if (curRow <= lower && matrix[curRow][curCol] == target)
		{
			std::cout << "Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [" << curRow << "][" << curCol << "]" << std::endl;
			return true;
		}
		
		/*
		now we can make sure that:
		1. all elements in the upper left quad ended at [curRow-1][curCol] are smaller than target
		2. all elements in the lower right quad starting at [curRow+1][curCol+1] are greater than target
		3. all elements in the current column below [curRow][curCol], including itself, are greater than target
		4. all elements in the current row after [curRow][curCol], including itself, are greater than target
		The 2 remaining regions we want to search for next are:
		1. the lower left quad [curRow~lower][left~curCol-1]
		2. the upper right quad [upper~curRow-1][curCol+1~right]
		*/
		return this->twoDBinarySearchRecur(matrix, target, curRow, lower, left, curCol - 1) ||//lower left quad. including: curRow
			this->twoDBinarySearchRecur(matrix, target, upper, curRow - 1, curCol + 1, right);//upper right quad. including:
	}
	int rowLowerBound(const std::vector<std::vector<int> > & matrix, int col, int target, int upper, int lower)
	{
		upper -= 1;
		lower += 1;
		while (lower - upper > 1)
		{
			int mid = upper + (lower - upper) / 2;
			if (matrix[mid][col] >= target)
				lower = mid;
			else
				upper = mid;
		}
		return lower;
	}
};
#endif
/*
twoDQuadSearchRecur2:

matrix[curRow][curCol] > target
eliminate "lower right quad excluding curRow & curCol":
 _____________   ____________
|        l    |l|            |
|        l    |l|            |
|        l    |l|            |
=========#====+#+============+
|        l    |l|            |
|________l____|l|____________|
=========#=====#==============
+--------l----+l
|        l    |l
|		 l    |l
|		 l    |l
|________l____|l

matrix[curRow][curCol] < target
eliminate "upper left quad including curRow & curCol":
                 ____________
         l     l|            |
         l     l|            |
         l     l|____________|
=========#=====#==============
         l     l+------------+
         l     l|            |
=========#=====#+============+
+--------l----+l|            |
|        l    |l|            |
|		 l    |l|            |
|		 l    |l|            |
|________l____|l|____________|


twoDBinarySearchRecur:

matrix[curRow][curCol] > target
eliminate "upper left quad including curCol" & "lower right quad including curRow & curCol":
                 ____________
         l     l|            |
         l     l|            |
         l     l|____________|
=========#=====#==============
+-------+l     l
|       |l     l
+=======+#=====#==============
|       |l     l
|       |l     l
|		|l     l
|		|l     l
|_______|l     l
*/

/*
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67

Search2dSortedMatrix UpperRightLinearSearch Found "44" at [3][3]
Found [3,6]: 47
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67

Search2dSortedMatrix 2DQuadSearchRecur Found "47": 1, 1
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67

Search2dSortedMatrix 1DBinarySearch Found "33": 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [5][6]
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67

Search2dSortedMatrix 2DBinarySearchRecur Found "67": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [3][6]
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16, 17
Row#1	= 21, 22, 23, 24, 25, 26, 27
Row#2	= 31, 32, 33, 34, 35, 36, 37
Row#3	= 41, 42, 43, 44, 45, 46, 47
Row#4	= 51, 52, 53, 54, 55, 56, 57
Row#5	= 61, 62, 63, 64, 65, 66, 67

Search2dSortedMatrix 2DBinarySearchRecur2 Found "47": 1


//2d matrix where the first integer of each row is NOT necessarily greater than the last integer of the previous row. (only OneDBinarySearch is not working)
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "9" at [2][2]
Found [2,2]: 9
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "9": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [2][2]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "9": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [2][2]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "9": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "9": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "17" at [3][3]
Found [3,3]: 17
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "17": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [3][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "17": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [3][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "17": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "17": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "16" at [2][3]
Found [2,3]: 16
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "16": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [2][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "16": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [2][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "16": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "16": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "21" at [4][1]
Found [4,1]: 21
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "21": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [4][1]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "21": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [4][1]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "21": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "21": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "30" at [4][4]
Found [4,4]: 30
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "30": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [4][4]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "30": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [4][4]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "30": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "30": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "31": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "31": 0, 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "31": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "31": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "31": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "17" at [3][3]
Found [3,3]: 17
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "17": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [3][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "17": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [3][3]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "17": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "17": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "10" at [3][0]
Found [3,0]: 10
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "10": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [3][0]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "10": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [3][0]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "10": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "10": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "20": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "20": 0, 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "20": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "20": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "20": 0
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix UpperRightLinearSearch Found "14" at [3][2]
Found [3,2]: 14
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DQuadSearchRecur Found "14": 1, 1
Search2dSortedMatrix 2DBinarySearchRecur Found target at [3][2]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur Found "14": 1
Search2dSortedMatrix 2DBinarySearchRecur2 Found target at [3][2]
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 2DBinarySearchRecur2 Found "14": 1
[rY][cX]
Row#0	= 1, 4, 7, 11, 15
Row#1	= 2, 5, 8, 12, 19
Row#2	= 3, 6, 9, 16, 22
Row#3	= 10, 13, 14, 17, 24
Row#4	= 18, 21, 23, 26, 30

Search2dSortedMatrix 1DBinarySearch Found "14": 1
*/