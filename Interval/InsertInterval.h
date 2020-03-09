#ifndef INSERT_INTERVAL_H
#define INSERT_INTERVAL_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Add a closed interval
Write a function which takes as input an array A of disjoint closed intervals with integer endpoints
, sorted by increasing order of left endpoint, and an interval I, and returns the union of I with the intervals in A
, expressed as a union of disjoint intervals.
Leetcode: Insert Interval
// Given a set of non-overlapping intervals, insert a new interval into the
// intervals (merge if necessary).
//
// You may assume that the intervals were initially sorted according to their
// start times.
//
// Example 1:
// Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
//
// Example 2:
// Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
// [1,2],[3,10],[12,16].
//
// This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
//
// Complexity:
// O(n)
*/
class InsertInterval
{
public:
	InsertInterval(){}
	~InsertInterval(){}
	std::vector<std::pair<int, int> > Insert(const std::vector<std::pair<int, int> > & intervals, std::pair<int, int> newInterval)
	{
		std::pair<int, int> before = newInterval;
		int N = intervals.size();
		int i = 0;
		std::vector<std::pair<int, int> > res;

		//inserts intervals appeared before newInterval
		while (i < N && newInterval.first > intervals[i].second)
			res.push_back(intervals[i++]);

		//merges intervals that overlap with newInterval
		while (i < N && newInterval.second >= intervals[i].first)
		{
			newInterval = { std::min(newInterval.first, intervals[i].first), std::max(newInterval.second, intervals[i].second) };
			++i;
		}
		res.push_back(newInterval);

		//inserts intervals appearing after newInterval
		res.insert(res.end(), intervals.begin() + i, intervals.end());

		std::cout << "InsertInterval for \"" << before.first << "," << before.second << "\" in \"" << Debug::ToStr1D<int>()(intervals) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	struct Interval
	{
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
		int start;
		int end;
	};
	std::vector<Interval> Insert(const std::vector<Interval> & intervals, Interval newInterval)
	{
		std::cout << "InsertInterval for \"" << "[" << newInterval.start << "," << newInterval.end << "] in \"" << this->IntervalVecToString(intervals) << "\": ";

		std::vector<Interval> res;
		bool done = false;
		for (Interval cur : intervals)
		{
			if (newInterval.end >= cur.start &&//newInterval's right side overlaps curInterval's left side
				newInterval.start <= cur.end)//curInterval's right side overlaps newInterval's left side
			{
				newInterval.start = std::min(newInterval.start, cur.start);
				newInterval.end = std::max(newInterval.end, cur.end);
			}
			else//curInterval has no overlap with newInterval
			{
				if (!done && newInterval.end < cur.start)//newInterval is on left side of curInterval
				{
					res.push_back(newInterval);
					done = true;
				}
				res.push_back(cur);
			}
		}
		if (!done)
			res.push_back(newInterval);//newInterval is on right side of last curInterval

		std::cout << this->IntervalVecToString(res) << std::endl;
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
InsertInterval for "5,19" in "[1,3], [4,6], [7,8], [12,14], [17,18], [20,24]": [1,3], [4,19], [20,24]
InsertInterval for "[5,19] in "[1,3],[4,6],[7,8],[12,14],[17,18],[20,24]": [1,3],[4,19],[20,24]
*/
#endif