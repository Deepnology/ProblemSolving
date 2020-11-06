#ifndef _COLORING_BORDER_OF_CONNECTED_COMPONENT_IN_2D_GRID_H
#define _COLORING_BORDER_OF_CONNECTED_COMPONENT_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Coloring A Border
Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.
Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.
The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).
Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.
Example 1:
Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
Output: [[3, 3], [3, 2]]
 */
class ColoringBorderOfConnectedComponentIn2dGrid
{
public:
    std::vector<std::vector<int>> DFS(std::vector<std::vector<int>>& grid, int r0, int c0, int color)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
        recur(grid, r0, c0, color, visit);
        return grid;
    }
private:
    void recur(std::vector<std::vector<int>> & grid, int r, int c, int tgtColor, std::vector<std::vector<int>> & visit)
    {
        int N = grid.size();
        int M = grid[0].size();
        visit[r][c] = 1;
        bool isBoundary = false;
        bool isBorder = false;
        std::vector<std::vector<int>> dir({{0,1},{0,-1},{1,0},{-1,0}});
        for (int d = 0; d < 4; ++d)
        {
            int rr = r + dir[d][0];
            int cc = c + dir[d][1];
            if (rr>=0 && rr<N && cc>=0 && cc<M)
            {
                if (!visit[rr][cc])
                {
                    if (grid[rr][cc] == grid[r][c])
                        recur(grid, rr, cc, tgtColor, visit);
                    else
                        isBorder = true;
                }
            }
            else
                isBoundary = true;
        }
        if (isBoundary || isBorder)
            grid[r][c] = tgtColor;
    }
};
#endif
