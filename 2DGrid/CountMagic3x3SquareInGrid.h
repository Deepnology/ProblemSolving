#ifndef _COUNT_MAGIC_3X3_SQUARE_IN_GRID_H
#define _COUNT_MAGIC_3X3_SQUARE_IN_GRID_H
#include "Debug.h"
/*
Leetcode: Magic Squares In Grid
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.
Given an grid of integers, how many 3 x 3 "magic square" subgrids are there?  (Each subgrid is contiguous).
Example 1:
Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation:
The following subgrid is a 3 x 3 magic square:
438
951
276
while this one is not:
384
519
762
In total, there is only one magic square inside the given grid.
 */
class CountMagic3x3SquareInGrid
{
public:
    CountMagic3x3SquareInGrid(){}
    ~CountMagic3x3SquareInGrid(){}

    int BruteForce(std::vector<std::vector<int>> && grid)
    {
        int N = grid.size();
        int M = grid[0].size();
        int res = 0;
        for (int i = 0; i < N-2; ++i)
            for (int j = 0; j < M-2; ++j)
                if (IsMagic3x3(grid, i, j))
                    ++res;

        Debug::Print2D<int>()(grid, false);
        std::cout << "CountMagic3x3SquareInGrid BruteForce for above grid: " << res << std::endl;
        return res;
    }
    bool IsMagic3x3(const std::vector<std::vector<int>> & grid, int row, int col)
    {
        std::vector<int> visit(10, 0);//check 1:9
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[row+i][col+j] < 1 || grid[row+i][col+j] > 9 || visit[grid[row+i][col+j]])
                    return false;
                else
                    visit[grid[row+i][col+j]] = 1;
        int sumD1 = grid[row][col] + grid[row+1][col+1] + grid[row+2][col+2];
        int sumD2 = grid[row][col+2] + grid[row+1][col+1] + grid[row+2][col];
        if (sumD1 != sumD2) return false;
        for (int i = 0; i < 3; ++i)
        {
            int sum = 0;
            for (int j = 0; j < 3; ++j)
                sum += grid[row+i][col+j];
            if (sum != sumD1) return false;
        }
        for (int j = 0; j < 3; ++j)
        {
            int sum = 0;
            for (int i = 0; i < 3; ++i)
                sum += grid[row+i][col+j];
            if (sum != sumD1) return false;
        }
        return true;
    }
};
/*
[rY][cX]
Row#0	= 4, 3, 8, 4
Row#1	= 9, 5, 1, 9
Row#2	= 2, 7, 6, 2

CountMagic3x3SquareInGrid BruteForce for above grid: 1
 */
#endif
