#ifndef _REMOVE_FULLY_COVERED_INTERVALS_H
#define _REMOVE_FULLY_COVERED_INTERVALS_H
#include "Debug.h"
/*
Leetcode: Remove Covered Intervals
Given a list of intervals, remove all intervals that are covered by another interval in the list.
Interval [a,b) is covered by interval [c,d) if and only if c <= a and b <= d.
After doing so, return the number of remaining intervals.
Example 1:
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
Example 2:
Input: intervals = [[1,4],[2,3]]
Output: 1
Example 3:
Input: intervals = [[0,10],[5,12]]
Output: 2
Example 4:
Input: intervals = [[3,10],[4,10],[5,11]]
Output: 2
Example 5:
Input: intervals = [[1,2],[1,4],[3,4]]
Output: 1
 */
class RemoveFullyCoveredIntervals
{
public:
    int Solve(std::vector<std::vector<int>> & intervals)
    {
        int N = intervals.size();
        if (N == 0) return 0;
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int> & a, const std::vector<int> & b)->bool
        {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });//sort by begin points in incr order and end points in decr order !!!
        int count = 0;//num of covered intervals
        int maxEnd = intervals[0][1];
        for (int i = 1; i < N; ++i)
        {
            if (intervals[i][1] <= maxEnd)
            {
                ++count;
            }
            maxEnd = std::max(maxEnd, intervals[i][1]);
        }
        return N-count;
    }
};
#endif
