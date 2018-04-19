/*Facebook*/
#ifndef _LEAST_NUM_OF_INTERVALS_COVER_RANGE_H
#define _LEAST_NUM_OF_INTERVALS_COVER_RANGE_H
#include "Debug.h"
/*
https://discuss.leetcode.com/topic/244/find-least-number-of-intervals-from-a-that-can-fully-cover-b
Given a list of intervals A and one interval B, find the least
number of intervals from A that can fully cover B.
If cannot find any result, just return 0;
For example:
Given A=[[0,3],[3,4],[4,6],[2,7]] B=[0,6] return 2 since we can use [0,3] [2,7] to cover the B
Given A=[[0,3],[4,7]] B=[0,6] return 0 since we cannot find any interval combination from A to cover the B
 */
class LeastNumOfIntervalsCoverRange
{
public:
    LeastNumOfIntervalsCoverRange(){}

    int SortGreedy(std::vector<std::pair<int,int>> v, std::pair<int,int> tgt)
    {
        std::sort(v.begin(), v.end(), [](const std::pair<int,int> & a, const std::pair<int,int> & b)
        {
           return a.first != b.first ? a.first < b.first : a.second < b.second;
        });

        int N = v.size();
        int count = 0;
        int i = 0;
        int start = tgt.first;
        int end = tgt.first - 1;
        while (i < N)
        {
            if (v[i].first <= start)//just advance
            {
                end = std::max(end, v[i].second);
                ++i;
            }
            else//include one of prev interval, and also get max end from prev intervals
            {
                start = end;
                ++count;
                if (v[i].first > end //no overlap for intervals after
                    || end >= tgt.second) //already covered, no need more intervals
                    break;
            }
        }
        if (end < tgt.second)
            count = -1;

        std::cout << "LeastNumOfIntervalsCoverRange SortGreedy for [" << Debug::ToStr1D<int>()(v) << "], tgt=[" << Debug::ToStr1D<int>()(tgt) << "]: " << count << std::endl;
        return count;
    }
};
/*
LeastNumOfIntervalsCoverRange SortGreedy for [[0,3], [2,7], [3,4], [4,6]], tgt=[0, 6]: 2
LeastNumOfIntervalsCoverRange SortGreedy for [[0,3], [4,7]], tgt=[0, 6]: -1
LeastNumOfIntervalsCoverRange SortGreedy for [[0,3], [2,7], [3,4], [4,6]], tgt=[-1, 6]: -1
 */
#endif
