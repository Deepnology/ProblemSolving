/*Facebook*/
#ifndef _INTERSECTION_OF_LISTS_OF_INTERVALS_H
#define _INTERSECTION_OF_LISTS_OF_INTERVALS_H
#include "Debug.h"
/*
Given two lists of sorted intervals, find the intersection of intervals from the two lists.
https://stackoverflow.com/questions/40367461/intersection-of-two-lists-of-ranges-in-python
Example:
a = [[0, 2], [5, 10], [13, 23], [24, 25]]
b = [[1, 5], [8, 12], [15, 18], [20, 24]]
Expected output: [[1, 2], [5, 5], [8, 10], [15, 18], [20, 24]]
 */
class IntersectionOfListsOfIntervals
{
public:
    IntersectionOfListsOfIntervals(){}

    std::vector<std::pair<int,int>> Linear(const std::vector<std::pair<int,int>> & a, const std::vector<std::pair<int,int>> & b)
    {
        std::vector<std::pair<int,int>> res1;
        int N = a.size();
        int M = b.size();
        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (a[i].first <= b[j].second && b[j].first <= a[i].second)//intersection condition
            {
                int left = std::max(a[i].first, b[j].first);
                int right = std::min(a[i].second, b[j].second);
                res1.push_back({left, right});
            }
            if (a[i].second < b[j].second)
                ++i;
            else
                ++j;
        }

        //merge (this may be unecessary because [20,23],[24,24] doesn't necessarily mean [20,24]
        std::vector<std::pair<int,int>> res2;
        std::pair<int,int> pre = res1[0];
        int SIZE = res1.size();
        for (int i = 1; i < SIZE; ++i)
        {
            std::pair<int,int> cur = res1[i];
            if (pre.second >= cur.first || pre.second + 1 == cur.first)//overlapped
            {
                pre.first = std::min(pre.first, cur.first);
                pre.second = std::max(pre.second, cur.second);
            }
            else//non-overlapped
            {
                res2.push_back(pre);
                pre = cur;
            }
        }
        res2.push_back(pre);

        std::cout << Debug::ToStr1D<int>()(a) << std::endl;
        std::cout << Debug::ToStr1D<int>()(b) << std::endl;
        std::cout << Debug::ToStr1D<int>()(res1) << std::endl;
        std::cout << Debug::ToStr1D<int>()(res2) << std::endl;
        std::cout << "IntersectionOfListsOfIntervals Linear for above 4 arrays: input, input, res1, res2" << std::endl;
        return res2;
    };
};
/*
[0,2], [5,10], [13,23], [24,25]
[1,5], [8,12], [15,18], [20,24]
[1,2], [5,5], [8,10], [15,18], [20,23], [24,24]
[1,2], [5,5], [8,10], [15,18], [20,24]
IntersectionOfListsOfIntervals Linear for above 4 arrays: input, input, res1, res2
[1,2], [5,7]
[2,6]
[2,2], [5,6]
[2,2], [5,6]
IntersectionOfListsOfIntervals Linear for above 4 arrays: input, input, res1, res2
[3,8], [100,150]
[2,5], [7,10]
[3,5], [7,8]
[3,5], [7,8]
IntersectionOfListsOfIntervals Linear for above 4 arrays: input, input, res1, res2
[0,4], [7,12]
[1,3], [5,8], [9,11]
[1,3], [7,8], [9,11]
[1,3], [7,11]
IntersectionOfListsOfIntervals Linear for above 4 arrays: input, input, res1, res2
 */
#endif
