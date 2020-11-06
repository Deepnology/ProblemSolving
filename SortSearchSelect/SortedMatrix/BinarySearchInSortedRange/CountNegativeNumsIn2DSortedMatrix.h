#ifndef _COUNT_NEGATIVE_NUMS_IN_2D_SORTED_MATRIX_H
#define _COUNT_NEGATIVE_NUMS_IN_2D_SORTED_MATRIX_H
#include "Debug.h"
/*
Leetcode: Count Negative Numbers in a Sorted Matrix
Given a m * n matrix grid which is sorted in non-increasing order both row-wise and column-wise.
Return the number of negative numbers in grid.
Example 1:
Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.
Example 2:
Input: grid = [[3,2],[1,0]]
Output: 0
Example 3:
Input: grid = [[1,-1],[-1,-1]]
Output: 3
Example 4:
Input: grid = [[-1]]
Output: 1
 */
class CountNegativeNumsIn2DSortedMatrix
{
public:
    int BinarySearch(std::vector<std::vector<int>>& grid)
    {
        //O(NlogM) time
        int N = grid.size(); int M = grid[0].size();
        int res = 0;
        for (int i = 0; i < N; ++i)
            res += (std::upper_bound(grid[i].rbegin(), grid[i].rend(), -1) - grid[i].rbegin());
        return res;
    }
    int UpperRightLinearSearch(std::vector<std::vector<int>>& grid)
    {
        //O(N+M) time
        int N = grid.size(); int M = grid[0].size();
        int res = 0;
        int row = 0; int col = M-1;
        while (row < N)
        {
            while (col >= 0 && grid[row][col] < 0)
                --col;
            res += M-col-1;//exclude both ends
            ++row;
        }
        return res;
    }
};
#endif
