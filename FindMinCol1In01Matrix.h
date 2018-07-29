/*Facebook*/
#ifndef _FIND_MIN_COL_1_IN_01_MATRIX_H
#define _FIND_MIN_COL_1_IN_01_MATRIX_H
#include "Debug.h"
/*
Given a 2d matrix with only 0 and 1, where all 0s in each row come before 1s.
Find the row that contains max number of 1s, and return the leftmost column index of 1s in that row.
(Find a 1 that has min column index)
 */
class FindMinCol1In01Matrix
{
public:
    FindMinCol1In01Matrix(){}

    int LinearSearchFromUpperRightCorner(const std::vector<std::vector<int>> & v)//O(N+M) time
    {
        int N = v.size();
        int M = v[0].size();
        int i = 0;
        int j = M-1;
        while (i < N && j >= 0)
        {
            if (v[i][j] == 1)
                --j;
            else
                ++i;
        }
        Debug::Print2D<int>()(v, false);
        std::cout << "FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: " << j+1 << std::endl;
        return j+1;
    }
};
/*
[rY][cX]
Row#0	= 0, 0, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1
Row#3	= 0, 0, 0, 0, 0

FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: 1
[rY][cX]
Row#0	= 0, 0, 0, 0, 1
Row#1	= 0, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1
Row#3	= 1, 1, 1, 1, 1

FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: 0
 */
#endif
