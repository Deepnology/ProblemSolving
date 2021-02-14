#ifndef _SORT_DIAGONALS_IN_MATRIX_H
#define _SORT_DIAGONALS_IN_MATRIX_H
#include "Debug.h"
/*
Leetcode: Sort the Matrix Diagonally
Given a m * n matrix mat of integers, sort it diagonally in ascending order from the top-left to the bottom-right then return the sorted array.
Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
 */
class SortReverseDiagonalsInMatrix
{
public:
    std::vector<std::vector<int>> UseHashMap(std::vector<std::vector<int>>& mat)
    {
        //O(NMlogN) time
        std::unordered_map<int, std::priority_queue<int, std::vector<int>, std::greater<int>>> m;
        int N = mat.size();
        int M = mat[0].size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                m[i-j].push(mat[i][j]);
        std::vector<std::vector<int>> res(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                res[i][j] = m[i-j].top();
                m[i-j].pop();
            }
        return res;
    }
    std::vector<std::vector<int>> InPlaceBubbleSort(std::vector<std::vector<int>>& mat)
    {
        //bubble sort: O(N^3) time
        int N = mat.size();
        int M = mat[0].size();
        for (int k = N; k > 0; --k)
            for (int i = 0; i+1 < k; ++i)
                for (int j = 0; j+1 < M; ++j)
                    if (mat[i][j] > mat[i+1][j+1])
                        std::swap(mat[i][j],mat[i+1][j+1]);
        return mat;
    }
};
#endif
