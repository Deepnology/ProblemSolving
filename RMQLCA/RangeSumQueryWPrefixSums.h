#ifndef	RANGE_SUM_QUERY_W_PREFIX_SUMS_H
#define RANGE_SUM_QUERY_W_PREFIX_SUMS_H
#include <iostream>
#include <vector>
#include "Debug.h"
/*
Leetcode: Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive.
Keep a 1D array prefixSums.
Subarray sum [i,j] inclusive = prefixSums[j] - (i == 0 ? 0 : prefixSums[i-1]).

Leetcode: Range Sum Query 2D - Immutable
Given a 2D integer matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 <= row2 and col1 <= col2.

Leetcode: Range Sum Query 1D - Mutable
The update(i, val) function modifies nums by updating the element at index i to val
Given nums = [1, 3, 5]
sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.

Leetcode: Range Sum Query 2D - Mutable
sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
Hide Tags Segment Tree Binary Indexed Tree
Hide Similar Problems (M) Range Sum Query 2D - Immutable (M) Range Sum Query - Mutable

See also MaxSubMatrixSumNoGreaterThanK.h, MaxRectangle.h
*/
class RangeSumQueryWPrefixSums2D
{
	std::vector<std::vector<int>> prefixSums;
public:
	explicit RangeSumQueryWPrefixSums2D(const std::vector<std::vector<int>> & matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return;
		int N = matrix.size();
		int M = matrix[0].size();
		std::vector<std::vector<int>>(N, std::vector<int>(M, 0)).swap(prefixSums);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				//prefixSums[i][j] = matrix[i][j] + prefixSums[i-1][j] + prefixSums[i][j-1] - prefixSums[i-1][j-1]
				prefixSums[i][j] = matrix[i][j] + (i == 0 ? 0 : prefixSums[i - 1][j]) + (j == 0 ? 0 : prefixSums[i][j - 1]) - (i == 0 || j == 0 ? 0 : prefixSums[i - 1][j - 1]);
			}
		}
		Debug::Print2D<int>()(matrix, false);
		std::cout << "RangeSumQueryWPrefixSums2D prefixSums for above matrix:" << std::endl;
		Debug::Print2D<int>()(prefixSums, false);
	}
	~RangeSumQueryWPrefixSums2D() {}

	int sumRegion(int row1, int col1, int row2, int col2)
	{
		//submatrix sum between [row1,col1], [row2,col2] inclusive is
		//prefixSums[row2][col2] - prefixSums[row1-1][col2] - prefixSums[row2][col1-1] + prefixSums[row1-1][col1-1]
		int res = prefixSums[row2][col2] - (row1 == 0 ? 0 : prefixSums[row1 - 1][col2]) - (col1 == 0 ? 0 : prefixSums[row2][col1 - 1]) + (row1 == 0 || col1 == 0 ? 0 : prefixSums[row1 - 1][col1 - 1]);
		std::cout << "RangeSumQueryWPrefixSum2D Query \"(" << row1 << ", " << col1 << "), (" << row2 << ", " << col2 << ")\": " << res << std::endl;
		return res;
	}
};
class RangeSumQueryWPrefixSums2DMutable
{
	std::vector<std::vector<int>> rowPrefixSums;
public:
	explicit RangeSumQueryWPrefixSums2DMutable(const std::vector<std::vector<int>> & matrix) 
	{
		int N = matrix.size();
		int M = matrix[0].size();
		rowPrefixSums.resize(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				//rowPrefixSums[i][j] = matrix[i][j] + rowPrefixSums[i][j-1]
				rowPrefixSums[i][j] = matrix[i][j] + (j == 0 ? 0 : rowPrefixSums[i][j - 1]);
			}
		}
		Debug::Print2D<int>()(matrix, false);
		std::cout << "RangeSumQueryWPrefixSums2DMutable rowPrefixSums for above matrix:" << std::endl;
		Debug::Print2D<int>()(rowPrefixSums, false);
	}
	RangeSumQueryWPrefixSums2DMutable() {}

	void update(int row, int col, int val)
	{
		int oldVal = rowPrefixSums[row][col] - (col == 0 ? 0 : rowPrefixSums[row][col - 1]);
		int diff = val - oldVal;
		int N = rowPrefixSums.size();
		int M = rowPrefixSums[0].size();
		for (int j = col; j < M; ++j)
		{
			//rowPrefixSums[row][col~M-1] += (val - (rowPrefixSums[row][col]-rowPrefixSums[row][col-1]))
			rowPrefixSums[row][j] += diff;
		}

		std::cout << "RangeSumQueryWPrefixSums2DMutable rowPrefixSums for updating \"(" << row << ", " << col << ")\" with \"" << val << "\":" << std::endl;
		Debug::Print2D<int>()(rowPrefixSums, false);
	}

	int sumRegion(int row1, int col1, int row2, int col2)
	{
		int res = 0;
		for (int i = row1; i <= row2; ++i)
		{
			//res += (rowPrefixSums[row1~row2][col2] - rowPrefixSums[row1~row2][col1-1])
			res += rowPrefixSums[i][col2] - (col1 == 0 ? 0 : rowPrefixSums[i][col1 - 1]);
		}

		std::cout << "RangeSumQueryWPrefixSum2DMutable Query \"(" << row1 << ", " << col1 << "), (" << row2 << ", " << col2 << ")\": " << res << std::endl;
		return res;
	}
};

class RangeSumQueryWPrefixSums1DMutable
{
	std::vector<int> prefixSums;
public:
	explicit RangeSumQueryWPrefixSums1DMutable(const std::vector<int> & v) 
	{
		int N = v.size();
		prefixSums.resize(N, 0);
		for (int i = 0; i < N; ++i)
			prefixSums[i] = v[i] + (i == 0 ? 0 : prefixSums[i - 1]);

		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		std::cout << "RangeSumQueryWPrefixSums1DMutable prefixSums for the above array: " << std::endl;
		std::cout << Debug::ToStr1D<int>()(prefixSums) << std::endl;
	}
	~RangeSumQueryWPrefixSums1DMutable() {}

	void update(int i, int val)
	{
		int N = prefixSums.size();
		int oldVal = prefixSums[i] - (i == 0 ? 0 : prefixSums[i - 1]);
		int diff = val - oldVal;
		for (int col = i; col < N; ++col)
		{
			//prefixSums[i~N-1] += (prefixSums[i]-prefixSums[i-1])
			prefixSums[col] += diff;
		}

		std::cout << "RangeSumQueryWPrefixSums1DMutable prefixSums for updating \"" << i << "\" with \"" << val << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(prefixSums) << std::endl;
	}

	int sumRange(int i, int j)
	{
		int res = prefixSums[j] - (i == 0 ? 0 : prefixSums[i - 1]);

		std::cout << "RangeSumQueryWPrefixSums1DMutable Query \"[" << i << ", " << j << "]\": " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 3, 0, 1, 4, 2
Row#1	= 5, 6, 3, 2, 1
Row#2	= 1, 2, 0, 1, 5
Row#3	= 4, 1, 0, 1, 7
Row#4	= 1, 0, 3, 0, 5

RangeSumQueryWPrefixSums2D prefixSums for above matrix:
[rY][cX]
Row#0	= 3, 3, 4, 8, 10
Row#1	= 8, 14, 18, 24, 27
Row#2	= 9, 17, 21, 28, 36
Row#3	= 13, 22, 26, 34, 49
Row#4	= 14, 23, 30, 38, 58

RangeSumQueryWPrefixSum2D Query "(2, 1), (4, 3)": 8
RangeSumQueryWPrefixSum2D Query "(1, 1), (2, 2)": 11
RangeSumQueryWPrefixSum2D Query "(1, 2), (2, 4)": 12
[rY][cX]
Row#0	= 3, 0, 1, 4, 2
Row#1	= 5, 6, 3, 2, 1
Row#2	= 1, 2, 0, 1, 5
Row#3	= 4, 1, 0, 1, 7
Row#4	= 1, 0, 3, 0, 5

RangeSumQueryWPrefixSums2DMutable rowPrefixSums for above matrix:
[rY][cX]
Row#0	= 3, 3, 4, 8, 10
Row#1	= 5, 11, 14, 16, 17
Row#2	= 1, 3, 3, 4, 9
Row#3	= 4, 5, 5, 6, 13
Row#4	= 1, 1, 4, 4, 9

RangeSumQueryWPrefixSum2DMutable Query "(2, 1), (4, 3)": 8
RangeSumQueryWPrefixSums2DMutable rowPrefixSums for updating "(3, 2)" with "2":
[rY][cX]
Row#0	= 3, 3, 4, 8, 10
Row#1	= 5, 11, 14, 16, 17
Row#2	= 1, 3, 3, 4, 9
Row#3	= 4, 5, 7, 8, 15
Row#4	= 1, 1, 4, 4, 9

RangeSumQueryWPrefixSum2DMutable Query "(2, 1), (4, 3)": 10
RangeSumQueryWPrefixSums2DMutable rowPrefixSums for updating "(2, 3)" with "7":
[rY][cX]
Row#0	= 3, 3, 4, 8, 10
Row#1	= 5, 11, 14, 16, 17
Row#2	= 1, 3, 3, 10, 15
Row#3	= 4, 5, 7, 8, 15
Row#4	= 1, 1, 4, 4, 9

RangeSumQueryWPrefixSum2DMutable Query "(2, 1), (4, 3)": 16
1, 3, 5
RangeSumQueryWPrefixSums1DMutable prefixSums for the above array:
1, 4, 9
RangeSumQueryWPrefixSums1DMutable Query "[0, 2]": 9
RangeSumQueryWPrefixSums1DMutable prefixSums for updating "1" with "2":
1, 3, 8
RangeSumQueryWPrefixSums1DMutable Query "[0, 2]": 8
*/
/*
Leetcode: Matrix Block Sum
Given a m * n matrix mat and an integer K, return a matrix answer where each answer[i][j]
 is the sum of all elements mat[r][c] for i - K <= r <= i + K, j - K <= c <= j + K, and (r, c) is a valid position in the matrix.
Example 1:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]
Example 2:
Input: mat = [[1,2,3],[4,5,6],[7,8,9]], K = 2
Output: [[45,45,45],[45,45,45],[45,45,45]]
Constraints:
m == mat.length
n == mat[i].length
1 <= m, n, K <= 100
1 <= mat[i][j] <= 100
 */
class MatrixBlockSum
{
public:
    std::vector<std::vector<int>> UsePrefixSums(std::vector<std::vector<int>>& matrix, int K)
    {
        int N = matrix.size();
        int M = matrix[0].size();
        std::vector<std::vector<int>> prefixSums(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                //prefixSums[i][j] = matrix[i][j] + prefixSums[i-1][j] + prefixSums[i][j-1] - prefixSums[i-1][j-1]
                prefixSums[i][j] = matrix[i][j] + (i == 0 ? 0 : prefixSums[i - 1][j]) + (j == 0 ? 0 : prefixSums[i][j - 1]) - (i == 0 || j == 0 ? 0 : prefixSums[i - 1][j - 1]);
            }
        std::vector<std::vector<int>> res(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                int row2 = i+K>=N?N-1:i+K;
                int col2 = j+K>=M?M-1:j+K;
                int row1 = i-K<0?0:i-K;
                int col1 = j-K<0?0:j-K;
                res[i][j] = prefixSums[row2][col2] - (row1 == 0 ? 0 : prefixSums[row1 - 1][col2]) - (col1 == 0 ? 0 : prefixSums[row2][col1 - 1]) + (row1 == 0 || col1 == 0 ? 0 : prefixSums[row1 - 1][col1 - 1]);
            }
        return res;
    }
};
#endif
