#ifndef _COUNT_OUT_OF_INCR_ORDER_NUMS_IN_ARR_H
#define _COUNT_OUT_OF_INCR_ORDER_NUMS_IN_ARR_H
#include "Debug.h"
/*
Leetcode: Height Checker
Students are asked to stand in non-decreasing order of heights for an annual photo.
Return the minimum number of students not standing in the right positions.
 (This is the number of students that must move in order for all students to be standing in non-decreasing order of height.)
Example 1:
Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right positions.
Note:
1 <= heights.length <= 100
1 <= heights[i] <= 100
 */
class CountOutOfIncrOrderNumsInArr
{
public:
    int SortAndCompare(std::vector<int> && heights)
    {
        std::vector<int> copy(heights);
        std::sort(copy.begin(), copy.end());
        int res = 0;
        int N = heights.size();
        for (int i = 0; i < N; ++i)
            if (heights[i] != copy[i])
                ++res;
        return res;
    }
};
#endif
