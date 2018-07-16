#ifndef _FIND_3_POINTS_FORM_LARGEST_TRIANGLE_H
#define _FIND_3_POINTS_FORM_LARGEST_TRIANGLE_H
#include "Debug.h"
/*
Leetcode: Largest Triangle Area
You have a list of points in the plane.
Return the area of the largest triangle that can be formed by any 3 of the points.
Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation:
The five points are show in the figure below. The red triangle is the largest.
 */
class Find3PointsFormLargestTriangle
{
public:
    Find3PointsFormLargestTriangle(){}

    double BruteForce(const std::vector<std::vector<int>> & points)
    {
        int N = points.size();
        double res = 0;
        for (int i = 0; i < N-2; ++i)
            for (int j = i+1; j < N-1; ++j)
                for (int k = j+1; k < N; ++k)
                    res = std::max(res, TriangleArea(points[i][0],points[i][1],points[j][0],points[j][1],points[k][0],points[k][1]));

        std::cout << "Find3PointsFormLargestTriangle BruteForce for [" << Debug::ToStr1D<int>()(points) << "]: " << res << std::endl;
        return res;
    }
private:
    double TriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        return abs(double(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
    }
};
/*
Find3PointsFormLargestTriangle BruteForce for [[0,0], [0,1], [1,0], [0,2], [2,0]]: 2
 */
#endif
