#ifndef _ROUND_TRIP_MAX_PICKUP_IN_2D_MATRIX_H
#define _ROUND_TRIP_MAX_PICKUP_IN_2D_MATRIX_H
#include "Debug.h"
/*
Leetcode: Cherry Pickup
In a N x N grid representing a field of cherries, each cell is one of three possible integers.
0 means the cell is empty, so you can pass through;
1 means the cell contains a cherry, that you can pick up and pass through;
-1 means the cell contains a thorn that blocks your way.
Your task is to collect maximum number of cherries possible by following the rules below:
Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
Example 1:
Input: grid =
[[0, 1, -1],
 [1, 0, -1],
 [1, 1,  1]]
Output: 5
Explanation:
The player started at (0, 0) and went down, down, right right to reach (2, 2).
4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
Then, the player went left, up, up, left to return home, picking up one more cherry.
The total number of cherries picked up is 5, and this is the maximum possible.
 */
class RoundTripMaxPickupIn2DMatrix
{
public:
    RoundTripMaxPickupIn2DMatrix(){}
    ~RoundTripMaxPickupIn2DMatrix(){}

    int DP3D(std::vector<std::vector<int>> && grid)
    {
        //(0,0) to (N-1,N-1) to (0,0) is equivalent to
        //simultaneous two paths (i,j) and (x,y) from (0,0) to (N-1,N-1)
        //with i+j = x+y which means total steps of each path are equal
        //dp[i][j][x][y] = max(dp[i-1][j][x-1][y],dp[i][j-1][x][y-1],dp[i-1][j][x][y-1],dp[i][j-1][x-1][y]) + grid[i][j] + (i==x ? 0 : grid[x][y])
        //O(N^3) time, O(N^3) space, which can be further optimized to O(N^2) space
        int N = grid.size();
        std::vector<std::vector<std::vector<int>>> dp(N, std::vector<std::vector<int>>(N, std::vector<int>(N, INT_MIN)));
        dp[0][0][0] = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == -1) continue;
                for (int x = i; x >= 0; --x)
                {
                    int y = i+j-x;
                    if (y >= N) break;
                    if (grid[x][y] == -1) continue;

                    if (i>0 && x>0) dp[i][j][x] = std::max(dp[i][j][x], dp[i-1][j][x-1]);//(i-1,j), (x-1,y)
                    if (j>0 && y>0) dp[i][j][x] = std::max(dp[i][j][x], dp[i][j-1][x]);//(i,j-1), (x,y-1)
                    if (i>0 && y>0) dp[i][j][x] = std::max(dp[i][j][x], dp[i-1][j][x]);//(i-1,j), (x,y-1)
                    if (j>0 && x>0) dp[i][j][x] = std::max(dp[i][j][x], dp[i][j-1][x-1]);//(i,j-1), (x-1,y)
                    if (dp[i][j][x] != INT_MIN)
                        dp[i][j][x] += grid[i][j] + (i==x ? 0 : grid[x][y]);
                }
            }

        int res = dp[N-1][N-1][N-1] == INT_MIN ? 0 : dp[N-1][N-1][N-1];

        Debug::Print2D<int>()(grid, false);
        std::cout << "RoundTripMaxPickupIn2DMatrix DP3D for above grid: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 0, 1, -1
Row#1	= 1, 0, -1
Row#2	= 1, 1, 1

RoundTripMaxPickupIn2DMatrix DP3D for above grid: 5
 */
#endif
