#ifndef DATA_STREAM_AS_DISJOINT_INTERVALS_H
#define DATA_STREAM_AS_DISJOINT_INTERVALS_H
#include "Debug.h"
/*
Leetcode: Data Stream As Disjoint Intervals
Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.
For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:
[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

Use a set to keep a sorted array of intervals by their start vals.
When adding a new val, find the upper bound of the set which gives you the first interval whose start>val.
Its prev interval whose start must be <= val, so if prev interval whose end is one less than val or greater, merge val starting from prev interval.
Keep merging next intervals as long as current end is one less than or greater than next interval's start.

*/
class DataStreamAsDisjointIntervals
{
public:
	DataStreamAsDisjointIntervals() {}
	~DataStreamAsDisjointIntervals() {}

	struct Interval
	{
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};
	void addNum(int val)
	{
		Interval v(val, val);
		int start = val;
		int end = val;
		auto itr = sorted.upper_bound(v);
		//now itr points to to the first interval whose start > val
		//prev(itr) interval whose start must be <= val
		//if prev(itr) interval whose end is one less than val or greater, merge val starting from prev(itr)
		if (itr != sorted.begin() && std::prev(itr)->end + 1 >= val)
		{
			--itr;
		}

		//now merge val starting from itr based on current end is one less than or greater than next interval's start
		while (itr != sorted.end() && end + 1 >= itr->start)
		{
			start = std::min(start, itr->start);
			end = std::max(end, itr->end);
			itr = sorted.erase(itr);//returns an itr pointing to the next interval after removal
		}

		//insert the new interval
		sorted.insert(itr, Interval(start, end));

		std::cout << "DataStreamAsDisjointIntervals addNum: " << val << std::endl;
	}

	std::vector<Interval> getIntervals()
	{
		std::vector<Interval> res(sorted.cbegin(), sorted.cend());

		std::cout << "DataStreamAsDisjointIntervals getIntervals: " << this->IntervalVecToString(res) << std::endl;
		return res;
	}

private:
	struct LessThan
	{
		bool operator()(const Interval & a, const Interval & b) const
		{
			return a.start < b.start;
		}
	};
	std::set<Interval, LessThan> sorted;



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
DataStreamAsDisjointIntervals addNum: 1
DataStreamAsDisjointIntervals getIntervals: [1,1]
DataStreamAsDisjointIntervals addNum: 3
DataStreamAsDisjointIntervals getIntervals: [1,1],[3,3]
DataStreamAsDisjointIntervals addNum: 7
DataStreamAsDisjointIntervals getIntervals: [1,1],[3,3],[7,7]
DataStreamAsDisjointIntervals addNum: 2
DataStreamAsDisjointIntervals getIntervals: [1,3],[7,7]
DataStreamAsDisjointIntervals addNum: 6
DataStreamAsDisjointIntervals getIntervals: [1,3],[6,7]
*/
#endif
