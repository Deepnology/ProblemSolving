#ifndef FIND_RIGHT_INTERVAL_H
#define FIND_RIGHT_INTERVAL_H
#include "Debug.h"
/*
Leetcode: Find Right Interval
Given a set of intervals, for each of the interval i, check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i
, which can be called that j is on the "right" of i.
For any interval i, you need to store the minimum interval j's index, which means that the interval j has the minimum start point to build the "right" relationship for interval i.
If the interval j doesn't exist, store -1 for the interval i.
Finally, you need output the stored value of each interval as an array.
Note:
You may assume the interval's end point is always bigger than its start point.
You may assume none of these intervals have the same start point.
Example 1:
Input: [ [1,2] ]
Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.
Example 2:
Input: [ [3,4], [2,3], [1,2] ]
Output: [-1, 0, 1]
Explanation: There is no satisfied "right" interval for [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point;
For [1,2], the interval [2,3] has minimum-"right" start point.
Example 3:
Input: [ [1,4], [2,3], [3,4] ]
Output: [-1, 2, -1]
Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point.
*/
class FindRightInterval
{
public:
	FindRightInterval() {}
	struct Interval
	{
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};

	std::vector<int> Sort_BinarySearch(const std::vector<Interval> & intervals)
	{
		std::ostringstream oss;
		for (const auto & i : intervals)
			oss << "[" << i.start << "," << i.end << "],";

		std::map<int, int> startIdxMap;//<start, original idx> where starts are sorted in incr order
		int N = intervals.size();
		for (int i = 0; i < N; ++i)
			startIdxMap[intervals[i].start] = i;

		std::vector<int> res;
		for (const auto & cur : intervals)
		{
			auto itr = startIdxMap.lower_bound(cur.end);//search cur.end in between all starts
			if (itr == startIdxMap.end())
				res.push_back(-1);
			else
				res.push_back(itr->second);
		}

		std::cout << "FindRightInterval Sort_BinarySearch for \"" << oss.str() << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
FindRightInterval Sort_BinarySearch for "[1,2],": -1
FindRightInterval Sort_BinarySearch for "[3,4],[2,3],[1,2],": -1, 0, 1
FindRightInterval Sort_BinarySearch for "[1,4],[2,3],[3,4],": -1, 2, -1
*/
#endif
