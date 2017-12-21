#ifndef MIN_REMOVAL_FOR_NON_OVERLAP_INTERVALS_H
#define MIN_REMOVAL_FOR_NON_OVERLAP_INTERVALS_H
#include "Debug.h"
/*
Leetcode: Non-overlapping intervals
Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:
Input: [ [1,2], [1,2], [1,2] ]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:
Input: [ [1,2], [2,3] ]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

*/
class MinRemovalForNonOverlapIntervals
{
public:
	MinRemovalForNonOverlapIntervals() {}
	struct Interval
	{
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};
	int Greedy(std::vector<Interval> & intervals)
	{
		std::ostringstream oss;
		for (const auto & i : intervals)
			oss << "[" << i.start << "," << i.end << "],";

		int N = intervals.size();
		std::sort(intervals.begin(), intervals.end(), [](const Interval & a, const Interval & b)->bool
		{
			return a.start == b.start ? a.end < b.end : a.start < b.start;
		});//sort by start points !!!
		int count = 0;
		int pre = 0;
		for (int i = 1; i < N; ++i)
		{
			if (intervals[pre].end > intervals[i].start)
			{
				//now intervals[i] overlaps w/ interval[pre]: either itervals[pre] or intervals[i] needs to be removed
				++count;
				if (intervals[pre].end > intervals[i].end)//choose to remove intervals[pre] (which is longer) to keep min removal
					pre = i;
				//else: choose to remove intervals[i] (which is longer) to keep min removal
			}
			else
				pre = i;
		}

		std::cout << "MinRemovalForNonOverlapIntervals Greedy for \"" << oss.str() << "\": " << count << std::endl;
		return count;
	}

	//this problem is equivalent to: count max number of non-overlapping intervals (Interval Scheduling)
	int Greedy2(std::vector<Interval> & intervals)
	{
		std::ostringstream oss;
		for (const auto & i : intervals)
			oss << "[" << i.start << "," << i.end << "],";

		int N = intervals.size();
		if (N == 0) return 0;
		std::sort(intervals.begin(), intervals.end(), [](const Interval & a, const Interval & b)->bool
		{
			return a.end == b.end ? a.start < b.start : a.end < b.end;
		});//sort by end points !!!
		int count = 1;
		int pre = 0;
		for (int i = 1; i < N; ++i)
		{
			if (intervals[pre].end <= intervals[i].start)
			{
				//now intervals[i] doesn't overlap w/ interval[pre]: include intervals[i]
				++count;
				pre = i;
			}
			//else: intervals[i] overlaps w/ interval[pre]: doesn't include intervals[i]
		}
		//now count is: max number of non-overlapping intervals

		std::cout << "MinRemovalForNonOverlapIntervals Greedy2 for \"" << oss.str() << "\": " << N - count << std::endl;
		return N - count;
	}
};
/*
MinRemovalForNonOverlapIntervals Greedy for "[1,2],[2,3],[3,4],[1,3],": 1
MinRemovalForNonOverlapIntervals Greedy2 for "[1,2],[2,3],[3,4],[1,3],": 1
MinRemovalForNonOverlapIntervals Greedy for "[1,2],[1,2],[1,2],": 2
MinRemovalForNonOverlapIntervals Greedy2 for "[1,2],[1,2],[1,2],": 2
MinRemovalForNonOverlapIntervals Greedy for "[1,2],[2,3],": 0
MinRemovalForNonOverlapIntervals Greedy2 for "[1,2],[2,3],": 0
*/
#endif
