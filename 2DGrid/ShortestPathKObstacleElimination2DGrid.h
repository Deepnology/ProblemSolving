#ifndef _SHORTEST_PATH_K_OBSTACLE_ELIMINATION_2D_GRID_H
#define _SHORTEST_PATH_K_OBSTACLE_ELIMINATION_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Shortest Path in a Grid with Obstacles Elimination
Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.
Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles.
 If it is not possible to find such walk return -1.
Example 1:
Input:
grid =
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]],
k = 1
Output: 6
Explanation:
The shortest path without eliminating any obstacle is 10.
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
Example 2:
Input:
grid =
[[0,1,1],
 [1,1,1],
 [1,0,0]],
k = 1
Output: -1
Explanation:
We need to eliminate at least two obstacles to find such a walk.
Constraints:
grid.length == m
grid[0].length == n
1 <= m, n <= 40
1 <= k <= m*n
grid[i][j] == 0 or 1
grid[0][0] == grid[m-1][n-1] == 0
 */
class ShortestPathKObstacleElimination2DGrid
{
public:
    int BFS(std::vector<std::vector<int>>& grid, int k)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<std::vector<int>>> visit(N, std::vector<std::vector<int>>(M, std::vector<int>(N*M, 0)));
        //visit[i][j][k]: grid[i][j][eliminationCount]
        std::queue<std::vector<int>> que;//<row,col,eliminationCount>
        int dist = 0;
        que.push({0,0,0});
        while (!que.empty())
        {
            int count = que.size();
            while (count-- > 0)
            {
                std::vector<int> cur = que.front();
                que.pop();
                if (cur[0]==N-1 && cur[1]==M-1)
                    return dist;
                std::vector<std::vector<int>> dir({{1,0},{-1,0},{0,1},{0,-1}});
                for (int d = 0; d < 4; ++d)
                {
                    int nxtR = cur[0]+dir[d][0];
                    int nxtC = cur[1]+dir[d][1];
                    if (nxtR>=0 && nxtR<N && nxtC>=0 && nxtC<M)
                    {
                        int nxtK = cur[2] + grid[nxtR][nxtC];
                        if (nxtK <= k && !visit[nxtR][nxtC][nxtK])
                        {
                            visit[nxtR][nxtC][nxtK] = 1;
                            que.push({nxtR,nxtC,nxtK});
                        }
                    }
                }
            }
            ++dist;
        }
        return -1;
    }
};
#endif
