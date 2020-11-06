#ifndef _MAX_DIST_OF_WATER_TO_LAND_IN_MATRIX_H
#define _MAX_DIST_OF_WATER_TO_LAND_IN_MATRIX_H
#include "Debug.h"
/*
Leetcode: As Far From Land As Possible
Given an N x N grid containing only values 0 and 1, where 0 represents water and 1 represents land
 , find a water cell such that its distance to the nearest land cell is maximized and return the distance.
The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
If no land or water exists in the grid, return -1.
Example 1:
Input: [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation:
The cell (1, 1) is as far as possible from all the land with distance 2.
 */
class MaxDistOfWaterToLandInMatrix
{
public:
    int BFS(std::vector<std::vector<int>> & grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::queue<std::vector<int>> que;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] == 1)//land
                    que.push({i,j});
        if (que.size()==0 || que.size()==N*M) return -1;
        int dist = 0;
        std::vector<std::vector<int>> dir({{0,1},{0,-1},{1,0},{-1,0}});
        while (!que.empty())
        {
            int count = que.size();
            while (count-->0)
            {
                auto v = que.front(); que.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int i = v[0]+dir[d][0];
                    int j = v[1]+dir[d][1];
                    if (i>=0&&i<N&&j>=0&&j<M&&grid[i][j]==0)//water
                    {
                        grid[i][j]=-1;
                        que.push({i,j});
                    }
                }
            }
            ++dist;
        }
        return dist-1;
    }
};
#endif
