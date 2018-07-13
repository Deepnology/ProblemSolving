#ifndef _TRANSPOSE_MATRIX_H
#define _TRANSPOSE_MATRIX_H
#include "Debug.h"
/*
Leetcode: Transpose Matrix
Given a matrix A, return the transpose of A.
The transpose of a matrix is the matrix flipped over it's main diagonal, switching the row and column indices of the matrix.
Example 1:
Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Example 2:
Input: [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
 */
class TransposeMatrix
{
public:
    TransposeMatrix(){}

    std::vector<std::vector<int>> Solve(const std::vector<std::vector<int>>& A)
    {
        int N = A.size();
        int M = A[0].size();
        std::vector<std::vector<int>> res(M, std::vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                res[j][i] = A[i][j];
        return res;
    }
};
#endif
