#ifndef _COUNT_CORNER_RECTANGLES_IN_2D_GRID_H
#define _COUNT_CORNER_RECTANGLES_IN_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Number of Corner Rectangles
Given a grid where each entry is only 0 or 1, find the number of corner rectangles.
A corner rectangle is 4 distinct 1s on the grid that form an axis-aligned rectangle.
Note that only the corners need to have the value 1.
Also, all four 1s used must be distinct.
Example 1:
Input: grid =
[[1, 0, 0, 1, 0],
 [0, 0, 1, 0, 1],
 [0, 0, 0, 1, 0],
 [1, 0, 1, 0, 1]]
Output: 1
Explanation: There is only one corner rectangle, with corners grid[1][2], grid[1][4], grid[3][2], grid[3][4].
 Example 2:
Input: grid =
[[1, 1, 1],
 [1, 1, 1],
 [1, 1, 1]]
Output: 9
Explanation: There are four 2x2 rectangles, four 2x3 and 3x2 rectangles, and one 3x3 rectangle.
 Example 3:
Input: grid =
[[1, 1, 1, 1]]
Output: 0
Explanation: Rectangles must have four distinct corners.
Note:
The number of rows and columns of grid will each be in the range [1, 200].
Each grid[i][j] will be either 0 or 1.
The number of 1s in the grid will be at most 6000.
 */
class CountCornerRectanglesIn2DGrid
{
public:
    CountCornerRectanglesIn2DGrid(){}

    int BruteForce(const std::vector<std::vector<int>> & grid) //O(N^4) time
    {
        int N = grid.size();
        int M = grid[0].size();
        int count = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (grid[i][j]) //upper left corner
                {
                    for (int ii = i + 1; ii < N; ++ii)
                        if (grid[ii][j]) //lower left corner
                        {
                            for (int jj = j + 1; jj < M; ++jj)
                                if (grid[i][jj]) //upper right corner
                                    count += grid[ii][jj]; //lower right corner
                        }
                }

        Debug::Print2D<int>()(grid, false);
        std::cout << "CountCornerRectanglesIn2DGrid BruteForce for above grid: " << count << std::endl;
        return count;
    }

    int Better(const std::vector<std::vector<int>> & grid) //O(N*M*numOfMax1sInARow) time complexity
    {
        int N = grid.size();
        int M = grid[0].size();
        std::vector<std::vector<int>> onesIdx(N, std::vector<int>());
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
            {
                if (grid[i][j])
                    onesIdx[i].push_back(j);
            }

        for (int i = 0; i < N; ++i)
        {
            for (int ii = i+1; ii < N; ++ii)
            {
                int j = 0; int M1 = onesIdx[i].size();
                int jj = 0; int M2 = onesIdx[ii].size();
                int count = 0; //count of pairs of one from onesIdx[i] and one from onesIdx[ii] whose values are same
                while (j < M1 && jj < M2)
                {
                    if (onesIdx[i][j] == onesIdx[ii][jj])
                    {
                        ++count;
                        ++j; ++jj;
                    }
                    else if (onesIdx[i][j] < onesIdx[ii][jj])
                        ++j;
                    else
                        ++jj;
                }
                res += count*(count-1)/2; // n!/(k!*(n-k)!), where k=2, equivalent to n*(n-1)/2
            }
        }

        Debug::Print2D<int>()(grid, false);
        std::cout << "CountCornerRectanglesIn2DGrid Better for above grid: " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 1, 0, 0, 1, 0
Row#1	= 0, 0, 1, 0, 1
Row#2	= 0, 0, 0, 1, 0
Row#3	= 1, 0, 1, 0, 1

CountCornerRectanglesIn2DGrid BruteForce for above grid: 1
[rY][cX]
Row#0	= 1, 0, 0, 1, 0
Row#1	= 0, 0, 1, 0, 1
Row#2	= 0, 0, 0, 1, 0
Row#3	= 1, 0, 1, 0, 1

CountCornerRectanglesIn2DGrid Better for above grid: 1
 */
#endif
