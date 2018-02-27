#ifndef RESHAPE_MATRIX_H
#define RESHAPE_MATRIX_H
#include "Debug.h"
/*
Leetcode: Reshape Matrix
In MATLAB, there is a very useful function called 'reshape', which can reshape a matrix into a new one with different size but keep its original data.
You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column number of the wanted reshaped matrix, respectively.
The reshaped matrix need to be filled with all the elements of the original matrix in the same row-traversing order as they were.
If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.
Example 1:
Input:
nums =
[[1,2],
[3,4]]
r = 1, c = 4
Output:
[[1,2,3,4]]
Explanation:
The row-traversing of nums is [1,2,3,4].
The new reshaped matrix is a 1 * 4 matrix, fill it row by row by using the previous list.
Example 2:
Input:
nums =
[[1,2],
[3,4]]
r = 2, c = 4
Output:
[[1,2],
[3,4]]
Explanation:
There is no way to reshape a 2 * 2 matrix to a 2 * 4 matrix.
So output the original matrix.
*/
class ReshapeMatrix
{
public:
	ReshapeMatrix() {}
	std::vector<std::vector<int>> Reshape(const std::vector<std::vector<int>> & nums, int r, int c)
	{
		int N = nums.size();
		int M = nums[0].size();
		if (N*M != r*c) return nums;
		std::vector<std::vector<int>> res(r, std::vector<int>(c));
		for (int i = 0; i < N*M; ++i)
		{
			res[i/c][i%c] = nums[i/M][i%M];
		}
		Debug::Print2D<int>()(nums, false);
		std::cout << "ReshapeMatrix for above matrix to [r,c]=[" << r << "," << c << "]:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

	std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>> & nums)
	{
		int N = nums.size();
		int M = nums[0].size();
		std::vector<std::vector<int>> res(M, std::vector<int>(N));
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				res[j][i] = nums[i][j];

		Debug::Print2D<int>()(nums, false);
		std::cout << "ReshapeMatrix Transpose for above matrix:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;

	}
};
/*
[rY][cX]
Row#0	= 11, 12
Row#1	= 21, 22
Row#2	= 31, 32

ReshapeMatrix for above matrix to [r,c]=[2,3]:
[rY][cX]
Row#0	= 11, 12, 21
Row#1	= 22, 31, 32

[rY][cX]
Row#0	= 11, 12
Row#1	= 21, 22
Row#2	= 31, 32

ReshapeMatrix Transpose for above matrix:
[rY][cX]
Row#0	= 11, 21, 31
Row#1	= 12, 22, 32

*/
#endif
