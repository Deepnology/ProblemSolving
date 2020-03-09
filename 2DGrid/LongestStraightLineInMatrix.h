#ifndef LONGEST_STRAIGHT_LINE_IN_MATRIX_H
#define LONGEST_STRAIGHT_LINE_IN_MATRIX_H
#include "Debug.h"
/*
Leetcode: Longest Line Of Consecutive One in Matrix
Given a 01 matrix M, find the longest line of consecutive one in the matrix.
The line could be horizontal, vertical, diagonal or anti-diagonal.
Example:
Input:
[[0,1,1,0],
[0,1,1,0],
[0,0,0,1]]
Output: 3
*/
class LongestStraightLineInMatrix
{
public:
	LongestStraightLineInMatrix() {}

	int BruteForce(std::vector<std::vector<int>> & m)
	{
        int N = m.size();
        if (N == 0) return 0;
        int M = m[0].size();
        if (M == 0) return 0;
        int res = 0;
        std::vector<std::vector<int>> dir{{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{1,1},{-1,1},{1,-1}};
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (m[i][j] == 1)
                {
                    for (int d = 0; d < 8; ++d)
                    {
                        int curLen = 1;
                        int ii = i + dir[d][0];
                        int jj = j + dir[d][1];
                        while (ii >= 0 && ii < N && jj >= 0 && jj < M && m[ii][jj] == 1)
                        {
                            ++curLen;
                            ii += dir[d][0];
                            jj += dir[d][1];
                        }
                        res = std::max(res, curLen);
                    }
                }
            }
        }
		return res;
	}

	int DP3D(std::vector<std::vector<int>> & m)
    {
        int N = m.size();
        if (N == 0) return 0;
        int M = m[0].size();
        if (M == 0) return 0;
        int res = 0;
        std::vector<std::vector<int>> dir{{-1,0},{0,-1},{-1,-1},{-1,1}};
        std::vector<std::vector<std::vector<int>>> dp(N, std::vector<std::vector<int>>(M, std::vector<int>(4, 0)));
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                if (m[i][j] == 1)
                {
                    for (int d = 0; d < 4; ++d)
                    {
                        dp[i][j][d] = 1;
                        int ii = i + dir[d][0];
                        int jj = j + dir[d][1];
                        if (ii >= 0 && ii < N && jj >= 0 && jj < M)
                        {
                            dp[i][j][d] += dp[ii][jj][d];
                        }
                        res = std::max(res, dp[i][j][d]);
                    }
                }
            }
        }
        return res;
    }
};
#endif
