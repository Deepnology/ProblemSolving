#ifndef _COUNT_ENCLOSED_ISLANDS_IN_2D_GRID_H
#define _COUNT_ENCLOSED_ISLANDS_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Number of Closed Islands
Given a 2D grid consists of 0s (land) and 1s (water).
An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
Return the number of closed islands.
Leetcode: Number of Enclaves
Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)
A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.
Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.
Example 1:
Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation:
There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
Example 2:
Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation:
All 1s are either on the boundary or can reach the boundary.
 */
class CountEnclosedIslandsIn2DGrid
{
public:
    int DFS(std::vector<std::vector<int>>& grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        int count = 0;
        int totalArea = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] == 1)//land
                {
                    std::pair<bool,int> cur = recur(grid, i, j);
                    if (cur.first)
                    {
                        ++count;
                        totalArea += cur.second;
                    }
                }
        return count;
    }
    std::pair<bool,int> recur(std::vector<std::vector<int>> & grid, int i, int j)
    {
        int N = grid.size();
        int M = grid[0].size();
        if (i < 0 || i >= N || j < 0 || j >= M) return {false,0};
        if (grid[i][j] == 0)//water
            return {true,0};
        grid[i][j] = 0;//mark as water
        static std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
        std::pair<bool,int> res = {true,1};
        for (int d = 0; d < 4; ++d)
        {
            auto cur = recur(grid, i+dir[d][0], j+dir[d][1]);
            res.first &= cur.first;
            res.second += cur.second;
        }
        //all 4 directions must meet a water to qualify be surrounded by water
        return res;
    }
};
#endif
