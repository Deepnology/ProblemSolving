#ifndef _SHIFT_ALL_NUMS_IN_2D_GRID_H
#define _SHIFT_ALL_NUMS_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Shift 2D Grid
Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
In one shift operation:
Element at grid[i][j] moves to grid[i][j + 1].
Element at grid[i][n - 1] moves to grid[i + 1][0].
Element at grid[m - 1][n - 1] moves to grid[0][0].
Return the 2D grid after applying shift operation k times.
Example 1:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]
Example 2:
Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
Example 3:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]
 */
class ShiftAllNumsIn2DGrid
{
public:
    std::vector<std::vector<int>> Solve1(std::vector<std::vector<int>>& grid, int k)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<int>> res(N, std::vector<int>(M, 0));
        for (int i = 0; i < N*M; ++i)
        {
            int shift = (i+k)%(N*M); //index after shift in 1D
            res[shift/M][shift%M] = grid[i/M][i%M];
        }
        return res;
    }
    std::vector<std::vector<int>> Solve2(std::vector<std::vector<int>>& grid, int k)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<int>> res(N, std::vector<int>(M, 0));
        for (int i = 0; i < N*M; ++i)
        {
            int r = i/M;
            int c = i%M;
            int rr = (r+(c+k)/M)%N;
            int cc = (c+k)%M;
            res[rr][cc] = grid[r][c];
        }
        return res;
    }
};
#endif
