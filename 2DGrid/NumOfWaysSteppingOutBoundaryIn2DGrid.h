#ifndef _NUM_OF_WAYS_STEPPING_OUT_BOUNDARY_IN_2D_GRID_H
#define _NUM_OF_WAYS_STEPPING_OUT_BOUNDARY_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Out of Boundary Paths
There is an m by n grid with a ball.
Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right).
 However, you can at most move N times.
 Find out the number of paths to move the ball out of grid boundary.
 The answer may be very large, return it after mod 109 + 7.
Example 1:
Input: m = 2, n = 2, N = 2, i = 0, j = 0
Output: 6
 */
class NumOfWaysSteppingOutBoundaryIn2DGrid
{
public:
    int DP3D(int m, int n, int N, int i, int j)
    {
        std::vector<std::vector<std::vector<int>>> dp(m, std::vector<std::vector<int>>(n, std::vector<int>(N+1, 0)));
        std::vector<std::vector<int>> dir({{0,1},{0,-1},{1,0},{-1,0}});
        for (int step = 1; step <= N; ++step)
            for (int r = 0; r < m; ++r)
                for (int c = 0; c < n; ++c)
                    for (int d = 0; d < 4; ++d)
                    {
                        int rr = r + dir[d][0];
                        int cc = c + dir[d][1];
                        dp[r][c][step] += (rr<0||rr>=m||cc<0||cc>=n)?1:dp[rr][cc][step-1];
                        dp[r][c][step] %= 1000000007;
                    }
        return dp[i][j][N];
    }

    int DFS(int m, int n, int N, int i, int j)
    {
        std::vector<std::vector<std::vector<int>>> memo(m, std::vector<std::vector<int>>(n, std::vector<int>(N+1, -1)));
        return recur(m, n, N, i, j, memo);
    }
    int recur(int N, int M, int steps, int i, int j, std::vector<std::vector<std::vector<int>>> & memo)
    {
        if (i<0||i>=N||j<0||j>=M) return 1;
        if (steps == 0) return 0;
        if (memo[i][j][steps] != -1) return memo[i][j][steps];
        std::vector<std::vector<int>> dir({{0,1},{0,-1},{1,0},{-1,0}});
        int count = 0;
        for (int d = 0; d < 4; ++d)
        {
            count += recur(N, M, steps-1, i+dir[d][0], j+dir[d][1], memo);
            count %= 1000000007;
        }
        return memo[i][j][steps] = count;
    }
};
#endif
