#ifndef _DETERMINE_IF_POINT_LIE_INSIDE_TRIANGLE_H
#define _DETERMINE_IF_POINT_LIE_INSIDE_TRIANGLE_H
#include "Debug.h"
/*
https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
 */
class DetermineIfPointLieInsideTriangle
{
public:
    DetermineIfPointLieInsideTriangle(){}

    bool CheckAreaSum(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
    {
        double T = TriangleArea(x1, y1, x2, y2, x3, y3);
        double t1 = TriangleArea(x, y, x1, y1, x2, y2);
        double t2 = TriangleArea(x, y, x2, y2, x3, y3);
        double t3 = TriangleArea(x, y, x3, y3, x1, y1);
        bool res = T == (t1+t2+t3);
        std::cout << "DetermineIfPointLieInsideTriangle CheckAreaSum for [" << x << "," << y << "], [(" << x1 << "," << y1 << "),(" << x2 << "," << y2 << "),(" << x3 << "," << y3 << ")]: " << res << std::endl;
        return res;
    }
    double TriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        return abs(double(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
    }
};
/*
DetermineIfPointLieInsideTriangle CheckAreaSum for [10,15], [(0,0),(20,0),(10,30)]: 1
 */
#endif
