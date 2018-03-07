#ifndef _LARGEST_PLUS_SIGN_IN_2D_GRID_H
#define _LARGEST_PLUS_SIGN_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Largest Plus Sign
In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0.
What is the largest axis-aligned plus sign of 1s contained in the grid?
Return the order of the plus sign.
If there is none, return 0.
An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, down, left, and right, and made of 1s.
This is demonstrated in the diagrams below.
Note that there could be 0s or 1s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1s.
Examples of Axis-Aligned Plus Signs of Order k:
Order 1:
000
010
000
Order 2:
00000
00100
01110
00100
00000
Order 3:
0000000
0001000
0001000
0111110
0001000
0001000
0000000
Example 1:
Input: N = 5, mines = [[4, 2]]
Output: 2
Explanation:
11111
11111
11111
11111
11011
In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.
Example 2:
Input: N = 2, mines = []
Output: 1
Explanation:
There is no plus sign of order 2, but there is of order 1.
Example 3:
Input: N = 1, mines = [[0, 0]]
Output: 0
Explanation:
There is no plus sign, so return 0.
 */
class LargestPlusSignIn2DGrid
{
public:
    LargestPlusSignIn2DGrid(){}

    int BruteForce(int N, const std::vector<std::vector<int>> & mines) //O(N^3) time
    {
        std::vector<std::vector<int>> grid(N, std::vector<int>(N, 1));
        for (auto & v : mines)
            grid[v[0]][v[1]] = 0;
        int res = 0;
        std::vector<std::vector<int>> dir({{-1,0},{1,0},{0,-1},{0,1}});
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 1)
                {
                    int curPlusLen = N;
                    for (int d = 0; d < 4; ++d)
                    {
                        int len = 1;
                        int ii = i; int jj = j;
                        while (ii+dir[d][0] >= 0 && ii+dir[d][0] < N && jj+dir[d][1] >= 0 && jj+dir[d][1] < N &&
                              grid[ii+dir[d][0]][jj+dir[d][1]] == 1)
                        {
                            ii += dir[d][0];
                            jj += dir[d][1];
                            ++len;
                        }
                        curPlusLen = std::min(curPlusLen, len);
                    }
                    res = std::max(res, curPlusLen);
                }
            }

        Debug::Print2D<int>()(grid, false);
        std::cout << "LargestPlusSignIn2DGrid BruteForce for above grid: " << res << std::endl;
        return res;
    }

    int DP2D(int N, const std::vector<std::vector<int>> & mines) //O(N^2) time, O(N^2) space
    {
        std::vector<std::vector<int>> grid(N, std::vector<int>(N, 1));
        for (auto & v : mines)
            grid[v[0]][v[1]] = 0;
        std::vector<std::vector<std::vector<int>>> dp(N, std::vector<std::vector<int>>(N, std::vector<int>(4, 0)));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                dp[i][j][0] = grid[i][j]==0? 0:grid[i][j] + (i-1>=0 ? dp[i-1][j][0]:0); //up
                dp[i][j][1] = grid[i][j]==0? 0:grid[i][j] + (j-1>=0 ? dp[i][j-1][1]:0); //left
            }
        for (int i = N-1; i >= 0; --i)
            for (int j = N-1; j >= 0; --j)
            {
                dp[i][j][2] = grid[i][j]==0 ? 0:grid[i][j] + (i+1<N ? dp[i+1][j][2]:0); //down
                dp[i][j][3] = grid[i][j]==0 ? 0:grid[i][j] + (j+1<N ? dp[i][j+1][3]:0); //right
            }
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
            {
                int curMin = N;
                for (int k = 0; k < 4; ++k)
                    curMin = std::min(curMin, dp[i][j][k]);
                res = std::max(res, curMin);
            }

        Debug::Print2D<int>()(grid, false);
        std::cout << "LargestPlusSignIn2DGrid DP2D for above grid: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 1, 1, 1, 1, 1
Row#2	= 1, 1, 1, 1, 1
Row#3	= 1, 1, 1, 1, 1
Row#4	= 1, 1, 0, 1, 1

LargestPlusSignIn2DGrid BruteForce for above grid: 2
[rY][cX]
Row#0	= 1, 1, 1, 1, 1
Row#1	= 1, 1, 1, 1, 1
Row#2	= 1, 1, 1, 1, 1
Row#3	= 1, 1, 1, 1, 1
Row#4	= 1, 1, 0, 1, 1

LargestPlusSignIn2DGrid DP2D for above grid: 2
 */
#endif
