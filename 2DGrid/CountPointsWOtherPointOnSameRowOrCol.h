#ifndef _COUNT_POINTS_W_OTHER_POINT_ON_SAME_ROW_OR_COL_H
#define _COUNT_POINTS_W_OTHER_POINT_ON_SAME_ROW_OR_COL_H
#include "Debug.h"
/*
Leetcode: Count Servers that Communicate
You are given a map of a server center, represented as a m * n integer matrix grid
 , where 1 means that on that cell there is a server and 0 means that it is no server.
 Two servers are said to communicate if they are on the same row or on the same column.
Return the number of servers that communicate with any other server.
 */
class CountPointsWOtherPointOnSameRowOrCol
{
public:
    int Solve(std::vector<std::vector<int>> & grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<int> rowCount(N, 0);
        std::vector<int> colCount(M, 0);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j])
                {
                    ++rowCount[i];
                    ++colCount[j];
                }
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j] && (rowCount[i]>=2 || colCount[j]>=2))
                    ++res;//now grid[i][j] can communicate with at least 1 other server
        return res;
    }
};
#endif
