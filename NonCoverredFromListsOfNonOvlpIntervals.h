#ifndef _NON_COVERRED_FROM_LISTS_OF_NON_OVLP_INTERVALS_H
#define _NON_COVERRED_FROM_LISTS_OF_NON_OVLP_INTERVALS_H
#include "Debug.h"
/*
Leetcode: Employee Free Time
We are given a list schedule of employees, which represents the working time for each employee.
Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.
Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.
Example 1:
Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation:
There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:
Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]
(Even though we are representing Intervals in the form [x, y], the objects inside are Intervals, not lists or arrays.
For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined.)
Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.
Note:
schedule and schedule[i] are lists with lengths in range [1, 50].
0 <= schedule[i].start < schedule[i].end <= 10^8.
 */
class NonCoverredFromListsOfNonOvlpIntervals
{
public:
    struct Interval
    {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}

        operator std::pair<int,int>() const
        {
            return std::pair<int,int>({start, end});
        };
    };
    NonCoverredFromListsOfNonOvlpIntervals(){}

    std::vector<Interval> MergeAndFind(const std::vector<std::vector<Interval>> & schedule)
    {
        std::vector<Interval> res;
        if (schedule.empty()) return res;

        std::vector<Interval> all;
        for (int i = 0; i < schedule.size(); ++i)
            for (int j = 0; j < schedule[i].size(); ++j)
                all.push_back(schedule[i][j]);

        std::vector<Interval> merged = SortAndMerge(all);

        int N = merged.size();
        for (int i = 1; i < N; ++i)
            res.push_back({merged[i-1].end, merged[i].start});

        //Debug::Print2D<int, int>()(static_cast<const std::vector<std::vector<std::pair<int,int>>>>(schedule), false);
        //std::cout << "NonCoveredFromListsOfNonOvlpIntervals MergeAndFind for above lists: " << Debug::ToStr1D<int, int>()(static_cast<std::vector<std::pair<int,int>>>(res)) << std::endl;
        return res;
    }
private:
    std::vector<Interval> SortAndMerge(std::vector<Interval> & all)
    {
        std::sort(all.begin(), all.end(), [](const Interval & a, const Interval & b)
        {
            return a.start != b.start ? a.start < b.start : a.end < b.end;
        });
        std::vector<Interval> merged;
        Interval pre = all[0];
        int N = all.size();
        for (int i = 1; i < N; ++i)
        {
            Interval cur = all[i];
            if (pre.end >= cur.start)//pre's right side overlaps cur's left side
            {
                pre.start = std::min(pre.start, cur.start);
                pre.end = std::max(pre.end, cur.end);
            }
            else//no overlap between pre and cur
            {
                merged.push_back(pre);
                pre = cur;
            }
        }
        merged.push_back(pre);
        return merged;
    }
};
#endif
