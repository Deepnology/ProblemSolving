#ifndef INTERSECTION_OF_INTERVALS_H
#define INTERSECTION_OF_INTERVALS_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Meeting Rooms
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.
For example,
Given [[0, 30],[5, 10],[15, 20]], return false.
This problem is equivalent to check if there is any overlap.
Google
http://www.careercup.com/question?id=15519765
Given an array of disc radius.
Each disc at index i is centered at i with its radius coverage on its left side and right side of the 1D array, which forms an interval.
Count the total number of intersections between all the intervals (discs).
(If a left interval's end falls in the same index as a right interval's start, then these two intervals have an intersection.)

Algorithm
1. sort intervals by start index
2. for each interval from left, find "the rightmost interval whose start is covered by current interval's end" via binary search
   then intervals between current and the rightmost are intersections
O(nlogn) time, O(n) space


Leetcode: Meeting Rooms II
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
For example,
Given [[0, 30],[5, 10],[15, 20]], return 2.
This problem is equivalent to find the max number of overlapped intervals at a time.
Elements of programming interview, Sorting: Render a calendar (CountMaxAtATime)
Given a set of n events, where each event has a start time and an end time, how would you determine the max number of events that take place concurrently?
Variant:
Users 1,2,...,n share an internet connection.
User i uses Bi bandwidth from time Si to Ei inclusive.
What is the peak bandwidth usage?
(this is a weighted version of counting the max of a time problem)

Algorithm
1. sort all of the start and end points
2. for each point from left, increment the intersection count when it is a start, decrement when it is an end
   keep track of the max intersection count
O(nlogn) time, O(n) space
*/
class IntersectionOfIntervals
{
public:
	IntersectionOfIntervals(){}
	~IntersectionOfIntervals(){}

	int CountTotal(const std::vector<int> & circles)
	{
		int N = circles.size();
		std::vector<std::pair<int, int>> intervals(N);//first: start, second: end
		for (int i = 0; i < N; ++i)
		{
			intervals[i].first = i - circles[i];
			intervals[i].second = i + circles[i];
		}
		/*
		1. sort intervals by start index
		*/
		std::sort(intervals.begin(), intervals.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.first < b.first;
		});

		/*
		2. for each interval from left, find "the rightmost interval whose start is covered by current interval's end" via binary search
		   then intervals between current and the rightmost are intersections
		*/
		int countIntersection = 0;
		std::vector<std::pair<int, int>> intersections;
		for (int i = 0; i < N; ++i)
		{
			auto iter = std::upper_bound(intervals.begin(), intervals.end(), intervals[i].second, [](const int & a, const std::pair<int, int> & b)->bool
			{
				return a < b.first;
			});
			--iter;//now iter points to the last dup of intervals[i].second

			int idx = iter - intervals.begin();
			countIntersection += (idx - i);//add current interval intersections: include back, don't include front (don't include itself)
			std::cout << "[" << intervals[i].first << "," << intervals[i].second << "] has " << idx - i << " intersections:" << std::endl;

			for (int j = i + 1; j <= idx; ++j)
			{
				intersections.push_back(std::make_pair((intervals[i].second + intervals[i].first) / 2, (intervals[j].second + intervals[j].first) / 2));
				std::cout << "[" << intervals[i].first << "," << intervals[i].second << "] overlaps [" << intervals[j].first << "," << intervals[j].second << "]" << std::endl;
			}
		}
		std::cout << Debug::ToStr1D<int>()(intervals) << std::endl;
		std::cout << "IntersectionOfIntervals CountTotal for \"" << Debug::ToStr1D<int>()(circles) << "\": " << countIntersection << ", IndexPairs: " << Debug::ToStr1D<int>()(intersections) << std::endl;
		return countIntersection;
	}

	int CountMaxAtATime(const std::vector<std::pair<int, int>> & intervals)//connected interval boundary counts for 2, i.e. [start,end]
	{
		int N = intervals.size();
		
		std::vector<std::pair<int, bool>> endPoints;//first: start/end point of an interval, second: true/false for start/end
		for (int i = 0; i < N; ++i)
		{
			endPoints.push_back(std::make_pair(intervals[i].first, true));
			endPoints.push_back(std::make_pair(intervals[i].second, false));
		}
		//1. sort all of the start and end points
		std::sort(endPoints.begin(), endPoints.end(), [](const std::pair<int, bool> & a, const std::pair<int, bool> & b)->bool
		{
			return a.first != b.first ? a.first < b.first : (a.second && !b.second);//start points always come before end points for [start,end]
		});

		//2. for each point from left, increment the intersection count when it is a start, decrement when it is an end
		//   keep track of the max intersection count
		int maxCount = 0;
		int count = 0;
		for (int i = 0; i < 2 * N; ++i)//endPoints have 2N points
		{
			if (endPoints[i].second)//cur point is a start
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else//cur point is an end
			{
				--count;
			}
		}

		std::cout << Debug::ToStr1D<int, bool>()(endPoints) << std::endl;
		std::cout << "IntersectionOfIntervals CountMaxAtATime for \"" << Debug::ToStr1D<int>()(intervals) << "\": " << maxCount << std::endl;
		return maxCount;
	}

	//==================================================
	//==================================================

	int CountMaxAtATimeII(const std::vector<std::pair<int, int> > & intervals)//connected interval boundary counts for 1, i.e., [start,end), (Leetcode: Meeting Rooms II)
	{
		int N = intervals.size();

		std::vector<std::pair<int, bool>> endPoints;//first: start/end point of an interval, second: true/false for start/end
		for (int i = 0; i < N; ++i)
		{
			endPoints.push_back(std::make_pair(intervals[i].first, true));
			endPoints.push_back(std::make_pair(intervals[i].second, false));
		}
		//1. sort all of the start and end points
		std::sort(endPoints.begin(), endPoints.end(), [](const std::pair<int, bool> & a, const std::pair<int, bool> & b)->bool
		{
			return a.first != b.first ? a.first < b.first : (!a.second && b.second);//end points always come before start points for [start,end)
		});

		//2. for each point from left, increment the itersection count when it is a start, decrement when it is an end
		//   keep track of the max intersection count
		int maxCount = 0;
		int count = 0;
		for (int i = 0; i < 2 * N; ++i)//endPoints have 2N points
		{
			if (endPoints[i].second)//cur point is a start
			{
				++count;
				if (count > maxCount)
				{
					maxCount = count;
				}
			}
			else//cur point is an end
			{
				--count;
			}
		}

		std::cout << Debug::ToStr1D<int, bool>()(endPoints) << std::endl;
		std::cout << "IntersectionOfIntervals CountMaxAtATimeII for \"" << Debug::ToStr1D<int>()(intervals) << "\": " << maxCount << std::endl;
		return maxCount;
	}
	int CountMaxAtATimeII_Simple(const std::vector<std::pair<int, int>> & intervals)//connected interval boundary counts for 1, i.e., [start,end), (Leetcode: Meeting Rooms II)
	{
		std::map<int, int> balance;//<timeIdx, StartEndSum> where timeIdx is sorted in incr order
		for (auto & i : intervals)
		{
			balance[i.first] += 1;//increment at start
			balance[i.second] -= 1;//decrement at end
		}
		int count = 0;//numOvlpItvl
		int maxCount = 0;//maxNumOvlpItvl
		for (auto & i : balance)
		{
			count += i.second;
			maxCount = std::max(maxCount, count);
		}
		std::vector<std::pair<int,int>> maxItvls;//intervals with max overlapped intervals
		std::vector<std::pair<int,int>> intersections;//intervals with at least 2 overlapped intervals
		count = 0;
		for (auto itr = balance.begin(); itr != balance.end(); ++itr)
		{
			count += itr->second;
			std::cout << "TimeIdx:StartEndSum,NumOvlp   " << itr->first << ":" << itr->second << "," << count << std::endl;

			if (count == maxCount && (maxItvls.empty() || maxItvls.back().second != INT_MIN))
				maxItvls.push_back({itr->first, INT_MIN});
			else if (count < maxCount && !maxItvls.empty() && maxItvls.back().second == INT_MIN)
				maxItvls.back().second = itr->first;

			if (count >= 2 && (intersections.empty() || intersections.back().second != INT_MIN))
			    intersections.push_back({itr->first, INT_MIN});
			else if (count < 2 && !intersections.empty() && intersections.back().second == INT_MIN)
			    intersections.back().second = itr->first;
		}
		std::cout << "IntersectionOfIntervals CountMaxAtATimeII_Simple for \"" << Debug::ToStr1D<int>()(intervals) << "\": " << maxCount << ", At: " << Debug::ToStr1D<int>()(maxItvls) << ", Intersections: " << Debug::ToStr1D<int>()(intersections) << std::endl;
		return maxCount;
	}


	//Leetcode: Car Pooling
	bool CarPooling(std::vector<std::vector<int>> && trips, int capacity)
	{
		std::map<int,int> map;//<stop,numPassengers> where stop is sorted in incr order
		for(auto & v : trips)
		{
			map[v[1]] += v[0];
			map[v[2]] -= v[0];
		}
		for(auto & s : map)
		{
			capacity -= s.second;
			if (capacity < 0)
				return false;
		}
		return true;
	}
};
/*
-|---|---|---|---|---|---|---|---|---|---
-2  -1   0   1   2   3   4   5   6   7
 |---------------|
     |---------------|
	     |---------------|
		         |-------|
				 |---------------|
				     |---------------|
					         |-------|

[-2,2] has 4 intersections:
[-2,2] overlaps [-1,3]
[-2,2] overlaps [0,4]
[-2,2] overlaps [2,4]
[-2,2] overlaps [2,6]
[-1,3] has 4 intersections:
[-1,3] overlaps [0,4]
[-1,3] overlaps [2,4]
[-1,3] overlaps [2,6]
[-1,3] overlaps [3,7]
[0,4] has 3 intersections:
[0,4] overlaps [2,4]
[0,4] overlaps [2,6]
[0,4] overlaps [3,7]
[2,4] has 2 intersections:
[2,4] overlaps [2,6]
[2,4] overlaps [3,7]
[2,6] has 2 intersections:
[2,6] overlaps [3,7]
[2,6] overlaps [5,7]
[3,7] has 1 intersections:
[3,7] overlaps [5,7]
[5,7] has 0 intersections:
[-2,2], [-1,3], [0,4], [2,4], [2,6], [3,7], [5,7]
IntersectionOfIntervals CountTotal for "2, 2, 2, 1, 2, 2, 1": 16, IndexPairs: [0,1], [0,2], [0,3], [0,4], [1,2], [1,3], [1,4], [1,5], [2,3], [2,4], [2,5], [3,4], [3,5], [4,5], [4,6], [5,6]

-|---|---|---|---|---|---|---|---|---|---|---|---|---
-4  -3  -2  -1   0   1   2   3   4   5   6   7   8
 |---------------------------------------|
             |-------|
	             |---------------|
		         |-------------------------------|
				         |-------|
				                    ||

[-4,6] has 5 intersections:
[-4,6] overlaps [-1,1]
[-4,6] overlaps [0,4]
[-4,6] overlaps [0,8]
[-4,6] overlaps [2,4]
[-4,6] overlaps [5,5]
[-1,1] has 2 intersections:
[-1,1] overlaps [0,4]
[-1,1] overlaps [0,8]
[0,4] has 2 intersections:
[0,4] overlaps [0,8]
[0,4] overlaps [2,4]
[0,8] has 2 intersections:
[0,8] overlaps [2,4]
[0,8] overlaps [5,5]
[2,4] has 0 intersections:
[5,5] has 0 intersections:
[-4,6], [-1,1], [0,4], [0,8], [2,4], [5,5]
IntersectionOfIntervals CountTotal for "1, 5, 2, 1, 4, 0": 11, IndexPairs: [1,0], [1,2], [1,4], [1,3], [1,5], [0,2], [0,4], [2,4], [2,3], [4,3], [4,5]

-|---|---|---|---|---|---|---|---|---|---
-2  -1   0   1   2   3   4   5   6   7
 |---------------|
     |---------------|
	     |---------------|
		         |-------|
				 |---------------|
				     |---------------|
					         |-------|

[-2,1], [-1,1], [0,1], [2,1], [2,1], [2,0], [3,1], [3,0], [4,0], [4,0], [5,1], [6,0], [7,0], [7,0]
IntersectionOfIntervals CountMaxAtATime for "[-2,2], [-1,3], [0,4], [2,4], [2,6], [3,7], [5,7]": 5, At: [2,3]

-|---|---|---|---|---|---|---|---|---|---|---|---|---
-4  -3  -2  -1   0   1   2   3   4   5   6   7   8
 |---------------------------------------|
             |-------|
	             |---------------|
		         |-------------------------------|
				         |-------|
				                    ||

[-4,1], [-1,1], [0,1], [0,1], [1,0], [2,1], [4,0], [4,0], [5,1], [5,0], [6,0], [8,0]
IntersectionOfIntervals CountMaxAtATime for "[-4,6], [-1,1], [0,4], [0,8], [2,4], [5,5]": 4, At: [0,4]

[2,1], [10,1], [10,0], [19,0]
IntersectionOfIntervals CountMaxAtATime for "[10,19], [2,10]": 2, At: [10,10]

[-2,1], [-1,1], [0,1], [2,0], [2,1], [2,1], [3,0], [3,1], [4,0], [4,0], [5,1], [6,0], [7,0], [7,0]
IntersectionOfIntervals CountMaxAtATimeII for "[-2,2], [-1,3], [0,4], [2,4], [2,6], [3,7], [5,7]": 4
[-4,1], [-1,1], [0,1], [0,1], [1,0], [2,1], [4,0], [4,0], [5,0], [5,1], [6,0], [8,0]
IntersectionOfIntervals CountMaxAtATimeII for "[-4,6], [-1,1], [0,4], [0,8], [2,4], [5,5]": 4
[2,1], [10,0], [10,1], [19,0]
IntersectionOfIntervals CountMaxAtATimeII for "[10,19], [2,10]": 1


TimeIdx:StartEndSum,NumOvlp   -2:1,1
TimeIdx:StartEndSum,NumOvlp   -1:1,2
TimeIdx:StartEndSum,NumOvlp   0:1,3
TimeIdx:StartEndSum,NumOvlp   2:1,4
TimeIdx:StartEndSum,NumOvlp   3:0,4
TimeIdx:StartEndSum,NumOvlp   4:-2,2
TimeIdx:StartEndSum,NumOvlp   5:1,3
TimeIdx:StartEndSum,NumOvlp   6:-1,2
TimeIdx:StartEndSum,NumOvlp   7:-2,0
IntersectionOfIntervals CountMaxAtATimeII_Simple for "[-2,2], [-1,3], [0,4], [2,4], [2,6], [3,7], [5,7]": 4, At: [2,4], Intersections: [-1,7]
TimeIdx:StartEndSum,NumOvlp   -4:1,1
TimeIdx:StartEndSum,NumOvlp   -1:1,2
TimeIdx:StartEndSum,NumOvlp   0:2,4
TimeIdx:StartEndSum,NumOvlp   1:-1,3
TimeIdx:StartEndSum,NumOvlp   2:1,4
TimeIdx:StartEndSum,NumOvlp   4:-2,2
TimeIdx:StartEndSum,NumOvlp   5:0,2
TimeIdx:StartEndSum,NumOvlp   6:-1,1
TimeIdx:StartEndSum,NumOvlp   8:-1,0
IntersectionOfIntervals CountMaxAtATimeII_Simple for "[-4,6], [-1,1], [0,4], [0,8], [2,4], [5,5]": 4, At: [0,1], [2,4], Intersections: [-1,6]
TimeIdx:StartEndSum,NumOvlp   2:1,1
TimeIdx:StartEndSum,NumOvlp   10:0,1
TimeIdx:StartEndSum,NumOvlp   19:-1,0
IntersectionOfIntervals CountMaxAtATimeII_Simple for "[10,19], [2,10]": 1, At: [2,19], Intersections:
TimeIdx:StartEndSum,NumOvlp   1:1,1
TimeIdx:StartEndSum,NumOvlp   2:1,2
TimeIdx:StartEndSum,NumOvlp   6:-1,1
TimeIdx:StartEndSum,NumOvlp   9:1,2
TimeIdx:StartEndSum,NumOvlp   10:-1,1
TimeIdx:StartEndSum,NumOvlp   12:-1,0
TimeIdx:StartEndSum,NumOvlp   14:1,1
TimeIdx:StartEndSum,NumOvlp   16:0,1
TimeIdx:StartEndSum,NumOvlp   17:-1,0
IntersectionOfIntervals CountMaxAtATimeII_Simple for "[1,10], [2,6], [9,12], [14,16], [16,17]": 2, At: [2,6], [9,10], Intersections: [2,6], [9,10]
*/
#endif