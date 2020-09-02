#ifndef _PAINT_NX3_GRID_COMBINATIONS_H
#define _PAINT_NX3_GRID_COMBINATIONS_H
#include "Debug.h"
/*
Leetcode: Number of Ways to Paint N × 3 Grid
You have a grid of size n x 3 and you want to paint each cell of the grid with
 exactly one of the three colours: Red, Yellow or Green while making sure that
 no two adjacent cells have the same colour
 (i.e no two cells that share vertical or horizontal sides have the same colour).
You are given n the number of rows of the grid.
Return the number of ways you can paint this grid.
As the answer may grow large, the answer must be computed modulo 10^9 + 7.
 */
class PaintNx3GridCombinations
{
public:
    int DP(int totalRow)
    {
        long a121 = 6; //121, 131, 212, 232, 313, 323
        long a123 = 6; //123, 132, 213, 231, 312, 321
        long b121; //212, 213, 232, 312, 313 => 3 * a121 + 2 * a123
        long b123; //212, 231, 312, 232 => 2 * a121 + 2 * a123
        for (int i = 1; i < totalRow; ++i)
        {
            b121 = 3 * a121 + 2 * a123;
            b123 = 2 * a121 + 2 * a123;
            a121 = b121 % 1000000007;
            a123 = b123 % 1000000007;
        }
        return (a121 + a123) % 1000000007;
    }

    int DFS_DP(int totalRow)
    {
        std::vector<std::vector<std::vector<std::vector<int>>>> dp(totalRow+1, std::vector<std::vector<std::vector<int>>>(4, std::vector<std::vector<int>>(4, std::vector<int>(4, -1))));
        return DFS(0, totalRow, 0, 0, 0, dp);
    }
    int DFS(int cur, int totalRow, int prevA, int prevB, int prevC, std::vector<std::vector<std::vector<std::vector<int>>>> & dp)
    {
        if (cur == totalRow)
            return 1;
        if (dp[cur][prevA][prevB][prevC] != -1)
            return dp[cur][prevA][prevB][prevC];
        int res = 0;
        static std::vector<int> colors({1,2,3});
        for (auto & a : colors)
        {
            if (a == prevA) continue;
            for (auto & b : colors)
            {
                if (b == prevB || b == a) continue;
                for (auto & c : colors)
                {
                    if (c == prevC || c == b) continue;
                    res += DFS(cur+1, totalRow, a, b, c, dp);
                    res %= 1000000007;
                }
            }
        }
        return dp[cur][prevA][prevB][prevC] = res;//num of ways at curRow w/ prevRow's colors A, B, C
    }
};
#endif
