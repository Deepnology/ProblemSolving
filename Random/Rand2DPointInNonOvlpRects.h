#ifndef _RAND_2D_POINT_IN_NON_OVLP_RECTS_H
#define _RAND_2D_POINT_IN_NON_OVLP_RECTS_H
#include "Debug.h"
/*
Leetcode: Random Point in Non-Overlapping Rectangles
Given a list of non-overlapping axis-aligned rectangles rects, write a function pick which
 randomly and uniformily picks an integer point in the space covered by the rectangles.
Note:
An integer point is a point that has integer coordinates.
A point on the perimeter of a rectangle is included in the space covered by the rectangles.
ith rectangle = rects[i] = [x1,y1,x2,y2], where [x1, y1] are the integer coordinates of the bottom-left corner,
 and [x2, y2] are the integer coordinates of the top-right corner.
length and width of each rectangle does not exceed 2000.
1 <= rects.length <= 100
pick return a point as an array of integer coordinates [p_x, p_y]
pick is called at most 10000 times.
Example 1:
Input:
["Solution","pick","pick","pick"]
[[[[1,1,5,5]]],[],[],[]]
Output:
[null,[4,1],[4,1],[3,3]]
Example 2:
Input:
["Solution","pick","pick","pick","pick","pick"]
[[[[-2,-2,-1,-1],[1,0,3,0]]],[],[],[],[],[]]
Output:
[null,[-1,-2],[2,0],[-2,-1],[3,0],[-2,-2]]
 */
class Rand2DPointInNonOvlpRects
{
    std::map<int,std::vector<int>> prefixSumToRect;
    int totalArea;
public:
    Rand2DPointInNonOvlpRects(const std::vector<std::vector<int>> & rects)
    {
        int prefixSum = 0;
        for (auto & rect : rects)
        {
            prefixSum += (rect[2]-rect[0]+1) * (rect[3]-rect[1]+1);
            prefixSumToRect[prefixSum] = rect;
        }
        totalArea = prefixSum;
    }

    std::vector<int> Pick()
    {
        int r = rand() % totalArea + 1;
        auto lb = prefixSumToRect.lower_bound(r);//binary search in sorted prefixSums
        int x = lb->second[0] + rand() % (lb->second[2]-lb->second[0]+1);
        int y = lb->second[1] + rand() % (lb->second[3]-lb->second[1]+1);

        Debug::Print2D<int>()(prefixSumToRect);
        std::cout << "Rand2DPointInNonOvlpRects Pick: [" << x << "," << y << "]" << std::endl;
        return {x,y};
    }
};
/*
Row#0	= 4: -2, -2, -1, -1
Row#1	= 7: 1, 0, 3, 0

Rand2DPointInNonOvlpRects Pick: [3,0]
Row#0	= 4: -2, -2, -1, -1
Row#1	= 7: 1, 0, 3, 0

Rand2DPointInNonOvlpRects Pick: [-1,-2]
Row#0	= 4: -2, -2, -1, -1
Row#1	= 7: 1, 0, 3, 0

Rand2DPointInNonOvlpRects Pick: [-1,-2]
Row#0	= 4: -2, -2, -1, -1
Row#1	= 7: 1, 0, 3, 0

Rand2DPointInNonOvlpRects Pick: [1,0]
Row#0	= 4: -2, -2, -1, -1
Row#1	= 7: 1, 0, 3, 0

Rand2DPointInNonOvlpRects Pick: [2,0]
 */
#endif
