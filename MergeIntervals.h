#ifndef MERGE_INTERVALS_H
#define MERGE_INTERVALS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Compute the union of intervals (Merge_OpenClosedPoints)
In this problem, we consider sets of intervals with integer endpoints; the intervals may be open or closed at either end.
We want to compute the union of the intervals in such sets.
Leetcode: Merge Intervals
// Given a collection of intervals, merge all overlapping intervals.
//
// For example,
// Given [1,3],[2,6],[8,10],[15,18],
// return [1,6],[8,10],[15,18].
//
// Complexity:
// O(nlog(n))
*/
class MergeIntervals
{
public:
	MergeIntervals(){}
	~MergeIntervals(){}
	struct Interval
	{
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
		int start;
		int end;
	};
	std::vector<Interval> Merge(std::vector<Interval> & intervals)
	{
		std::cout << "MergeIntervals for \"" << this->IntervalVecToString(intervals) << "\": ";
		std::vector<Interval> res;
		if (intervals.empty())
			return res;
		std::sort(std::begin(intervals), std::end(intervals)
			, [](const Interval & a, const Interval & b)->bool
		{
			return a.start < b.start;
		});

		Interval pre = intervals[0];
		for (int i = 1; i < (int)intervals.size(); ++i)
		{
			Interval cur = intervals[i];
			if (pre.end >= cur.start)//pre's right side overlaps cur's left side
			{
				pre.start = std::min(pre.start, cur.start);
				pre.end = std::max(pre.end, cur.end);
			}
			else//no overlap between pre and cur
			{
				res.push_back(pre);
				pre = cur;
			}
		}
		res.push_back(pre);

		std::cout << this->IntervalVecToString(res) << std::endl;
		return res;
	}

	//both start and end points of an interval have a bool field to indicate that point is included (closed) or excluded (open)
	std::vector<std::pair<std::pair<int, bool>, std::pair<int, bool> > > Merge_OpenClosedPoints(std::vector<std::pair<std::pair<int, bool>, std::pair<int, bool> > > & intervals)
	{
		//first.first: start point value, first.second: start point is closed (true) or not (false)
		//second.first: end point value, second.second: end point is closed(true) or not (false)
		int N = intervals.size();
		std::vector<std::pair<std::pair<int, bool>, std::pair<int, bool> > > res;
		if (intervals.empty())
			return res;

		//sort start points in non-descending order
		std::sort(intervals.begin(), intervals.end(), [](const std::pair<std::pair<int, bool>, std::pair<int, bool> > & a, const std::pair<std::pair<int, bool>, std::pair<int, bool> > & b)->bool
		{
			return a.first.first != b.first.first ? a.first.first < b.first.first : (a.first.second && !b.first.second);//closed point always comes first
		});
		std::pair<std::pair<int, bool>, std::pair<int, bool> > pre = intervals[0];
		for (int i = 1; i < N; ++i)
		{
			if (pre.second.first > intervals[i].first.first || (pre.second.first == intervals[i].first.first && (pre.second.second || intervals[i].first.second)))
			{
				if (pre.second.first < intervals[i].second.first || (pre.second.first == intervals[i].second.first && intervals[i].second.second))//pre's end point will stop in current interval
					pre.second = intervals[i].second;//update pre's end point to current interval's end point
			}
			else
			{
				res.push_back(pre);
				pre = intervals[i];
			}
		}
		res.push_back(pre);

		std::cout << "MergeIntervals Merge_OpenClosedPoints for \"" << Debug::ToStr1D<int, bool>()(intervals) << "\": " << Debug::ToStr1D<int, bool>()(res) << std::endl;
		return res;
	}

private:
	std::string IntervalVecToString(const std::vector<Interval> & intervals)
	{
		std::ostringstream oss;
		for (int i = 0; i < (int)intervals.size(); ++i)
		{
			oss << "[" << intervals[i].start << "," << intervals[i].end << "]";
			if (i != (int)intervals.size() - 1)
				oss << ",";
		}
		return oss.str();
	}
};
/*
MergeIntervals for "[9,11],[5,7],[4,6],[1,2],[7,8],[3,5]": [1,2],[3,8],[9,11]
MergeIntervals Merge_OpenClosedPoints for "[(0,0),(3,0)], [(1,1),(1,1)], [(2,1),(4,1)], [(3,1),(4,0)], [(5,1),(7,0)], [(7,1),(8,0)], [(8,1),(11,0)], [(9,0),(11,1)], [(12,1),(14,1)], [(12,0),(16,1)], [(13,0),(15,0)], [(16,0),(17,0)]": [(0,0),(4,1)], [(5,1),(11,1)], [(12,1),(17,0)]
*/
#endif