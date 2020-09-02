#ifndef _MIN_STEPS_MOVE_VERT_HORI_DIAG_2D_GRID_H
#define _MIN_STEPS_MOVE_VERT_HORI_DIAG_2D_GRID_H
#include "Debug.h"
/*
Leetcode: Minimum Time Visiting All Points
On a plane there are n points with integer coordinates points[i] = [xi, yi].
Your task is to find the minimum time in seconds to visit all points.
You can move according to the next rules:
In one second always you can either move vertically, horizontally by one unit or diagonally (it means to move one unit vertically and one unit horizontally in one second).
You have to visit the points in the same order as they appear in the array.
 */
class MinStepsMoveVertHoriDiag2DGrid
{
public:
    int MoveInGivenArrayOrder(const std::vector<std::vector<int>> & points)
    {
        int res = 0;
        for (auto i = 0; i < points.size()-1; ++i)
            res += std::max(std::abs(points[i][0]-points[i+1][0]), std::abs(points[i][1]-points[i+1][1]));
        //between two points, we can choose to move horizontally, vertically, or diagonally
        //the min steps is to first move diagonally (both horizontally and vertically) until either x1=x2 or y1=y2, then move vertically or horizontally
        //which is equivalent to max(|x1-x2|, |y1-y2|)

        return res;
    }
};
#endif
