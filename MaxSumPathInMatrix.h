#ifndef PROBLEMSOLVING_MAX_SUM_PATH_IN_MATRIX_H
#define PROBLEMSOLVING_MAX_SUM_PATH_IN_MATRIX_H
#include "Debug.h"
/*
Leetcode: Path with Maximum Gold
In a gold mine grid of size m * n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
Return the maximum amount of gold you can collect under the conditions:
Every time you are located in a cell you will collect all the gold in that cell.
From your position you can walk one step to the left, right, up or down.
You can't visit the same cell more than once.
Never visit a cell with 0 gold.
You can start and stop collecting gold from any position in the grid that has some gold.
Example 1:
Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.
Example 2:
Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.
Constraints:
1 <= grid.length, grid[i].length <= 15
0 <= grid[i][j] <= 100
There are at most 25 cells containing gold.

see also LongestIncrAdjConsecuNumSeqInMatrix.h
 */
class MaxSumPathInMatrix
{
public:
    int DFS(std::vector<std::vector<int>> && grid)
    {
        //O(k * 3^k) time, O(k) space, where k is number of cells w/ gold
        int N = grid.size();
        int M = grid[0].size();
        //std::vector<std::vector<int>> memo(N,std::vector<int>(M,-1));
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] != 0)
                    res = std::max(res, recur(grid, i, j));

        //Debug::Print2D<int>()(memo, false);
        Debug::Print2D<int>()(grid, false);
        std::cout << "MaxSumPathInMatrix DFS for above matrix: " << res << std::endl;
        return res;
    }
    /*
    //memo is not working for this question, bc the max sum at each cell depends on the path taken to reach there, so it's not a constant value
    int recur(std::vector<std::vector<int>> & grid, int i, int j, std::vector<std::vector<int>> & memo)
    {
        int N = grid.size(); int M = grid[0].size();
        if (memo[i][j] != -1) return memo[i][j];
        std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
        int maxC = 0;
        for (int d = 0; d < 4; ++d)
        {
            int ii = i + dir[d][0];
            int jj = j + dir[d][1];
            if (ii>=0 && ii<N && jj>=0 && jj<M && grid[ii][jj] > 0)
            {
                grid[i][j] = -grid[i][j];
                maxC = std::max(maxC, recur(grid,ii,jj,memo));
                grid[i][j] = -grid[i][j];
            }
        }
        return memo[i][j] = maxC + grid[i][j];
    }
    */

    int recur(std::vector<std::vector<int>> & grid, int i, int j)
    {
        int N = grid.size(); int M = grid[0].size();
        std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
        int maxC = 0;
        for (int d = 0; d < 4; ++d)
        {
            int ii = i + dir[d][0];
            int jj = j + dir[d][1];
            if (ii>=0 && ii<N && jj>=0 && jj<M && grid[ii][jj]>0)
            {
                grid[i][j] = -grid[i][j];
                maxC = std::max(maxC, recur(grid,ii,jj));
                grid[i][j] = -grid[i][j];
            }
        }
        return maxC + grid[i][j];
    }

};
/*
[rY][cX]
Row#0	= 0, 6, 0
Row#1	= 5, 8, 7
Row#2	= 0, 9, 0

MaxSumPathInMatrix DFS for above matrix: 24
 */
#endif
