#ifndef _UNIQUE_PATH_IN_TRIANGLE_H
#define _UNIQUE_PATH_IN_TRIANGLE_H
#include "Debug.h"
/*
Given a number triangle, where you can move down left or down right.
Start from the top, count number of unique paths to bottom numbers.

This is equivalent to Pascal Triangle.
The total number of unique paths is 2^N, where N is number of rows in the triangle.
 */
class UniquePathInTriangle
{
public:
    UniquePathInTriangle(){}

    int DP2D(int n)
    {
        std::vector<std::vector<int>> dp;
        for (int row = 0; row < n; ++row)
            dp.push_back(std::vector<int>(row+1, 0));
        dp[0][0] = 1;
        for (int row = 1; row < n; ++row)
            for (int col = 0; col <= row; ++col)
            {
                if (col == 0 || col == row)
                    dp[row][col] = 1;
                else
                    dp[row][col] = dp[row-1][col-1] + dp[row-1][col];
            }

        int res = 0;
        for (int col = 0; col < n; ++col)
            res += dp[n-1][col];

        Debug::Print2D<int>()(dp, false);
        std::cout << "UniquePathInTriangle DP2D for above triangle: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1

UniquePathInTriangle DP2D for above triangle: 1
[rY][cX]
Row#0	= 1,
Row#1	= 1, 1

UniquePathInTriangle DP2D for above triangle: 2
[rY][cX]
Row#0	= 1,  ,
Row#1	= 1, 1,
Row#2	= 1, 2, 1

UniquePathInTriangle DP2D for above triangle: 4
[rY][cX]
Row#0	= 1,  ,  ,
Row#1	= 1, 1,  ,
Row#2	= 1, 2, 1,
Row#3	= 1, 3, 3, 1

UniquePathInTriangle DP2D for above triangle: 8
[rY][cX]
Row#0	= 1,  ,  ,  ,
Row#1	= 1, 1,  ,  ,
Row#2	= 1, 2, 1,  ,
Row#3	= 1, 3, 3, 1,
Row#4	= 1, 4, 6, 4, 1

UniquePathInTriangle DP2D for above triangle: 16
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,
Row#3	= 1, 3, 3, 1,  ,
Row#4	= 1, 4, 6, 4, 1,
Row#5	= 1, 5, 10, 10, 5, 1

UniquePathInTriangle DP2D for above triangle: 32
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,  ,
Row#3	= 1, 3, 3, 1,  ,  ,
Row#4	= 1, 4, 6, 4, 1,  ,
Row#5	= 1, 5, 10, 10, 5, 1,
Row#6	= 1, 6, 15, 20, 15, 6, 1

UniquePathInTriangle DP2D for above triangle: 64
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,  ,  ,
Row#3	= 1, 3, 3, 1,  ,  ,  ,
Row#4	= 1, 4, 6, 4, 1,  ,  ,
Row#5	= 1, 5, 10, 10, 5, 1,  ,
Row#6	= 1, 6, 15, 20, 15, 6, 1,
Row#7	= 1, 7, 21, 35, 35, 21, 7, 1

UniquePathInTriangle DP2D for above triangle: 128
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,  ,  ,  ,
Row#1	= 1, 1,  ,  ,  ,  ,  ,  ,
Row#2	= 1, 2, 1,  ,  ,  ,  ,  ,
Row#3	= 1, 3, 3, 1,  ,  ,  ,  ,
Row#4	= 1, 4, 6, 4, 1,  ,  ,  ,
Row#5	= 1, 5, 10, 10, 5, 1,  ,  ,
Row#6	= 1, 6, 15, 20, 15, 6, 1,  ,
Row#7	= 1, 7, 21, 35, 35, 21, 7, 1,
Row#8	= 1, 8, 28, 56, 70, 56, 28, 8, 1

UniquePathInTriangle DP2D for above triangle: 256
 */
#endif
