#ifndef LEAST_POINTS_COVERING_ALL_INTERVALS_H
#define LEAST_POINTS_COVERING_ALL_INTERVALS_H
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "Debug.h"
/*
Leetcode: Minimum Number of Arrows to Burst Balloons
Elements of programming interview, Sorting: The interval covering problem
You are given a set of n tasks modeled as closed intervals [ai, bi], for i = 0,...,n-1.
Design an efficient algorithm for finding a minimum cardinality set of visit times that covers all the tasks.

2SortedSets: O(nlogn) time, O(n) space
1. sort all the intervals by their start points and end points to get two sorted sets
2. the leftmost point that covers intervals will be the end point of "interval with smallest end point" (front of endSorted set), record it
   remove "intervals that are coverred by the leftmost end point" (intervals whose start point <= the leftmost end point) from front of both endSorted and startSorted sets
3. repeat the above 2 steps until both the 2 sorted sets are empty
*/
class LeastPointsCoveringAllIntervals
{
public:
	LeastPointsCoveringAllIntervals(){}
	~LeastPointsCoveringAllIntervals(){}

	struct StartComp
	{
		bool operator()(const std::pair<int, int> * a, const std::pair<int, int> * b) const
		{
			return a->first != b->first ? a->first < b->first : a->second < b->second;
		}
	};
	struct EndComp
	{
		bool operator()(const std::pair<int, int> * a, const std::pair<int, int> * b) const
		{
			return a->second != b->second ? a->second < b->second : a->first < b->first;
		}
	};
	std::vector<int> TwoSortedSets(const std::vector<std::pair<int, int>> & v)
	{
		int N = v.size();
		std::set<const std::pair<int, int> *, StartComp> startSorted;
		std::set<const std::pair<int, int> *, EndComp> endSorted;
		//O(nlogn) time for insertion
		for (int i = 0; i < N; ++i)
		{
			startSorted.emplace(&v[i]);
			endSorted.emplace(&v[i]);
		}

		//O(n) time for deletion
		std::vector<int> res;
		while (!startSorted.empty() && !endSorted.empty())
		{
			//1. find the leftmost end point of any interval
			int smallestEnd = (*endSorted.cbegin())->second;
			res.emplace_back(smallestEnd);

			//2. remove intervals that are coverred by the leftmost end point (intervals whose start point <= the leftmost end point)
			auto iter = startSorted.cbegin();
			while (iter != startSorted.cend() && (*iter)->first <= smallestEnd)
			{
				endSorted.erase(*iter);//erase by value
				startSorted.erase(iter++);//erase by iter
			}
		}

		std::cout << "LeastPointsCoveringAllIntervals 2SortedSets for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	int Count_SortGreedy(std::vector<std::pair<int, int>> && v)
	{
		int N = v.size();
		std::sort(v.begin(), v.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.second == b.second ? a.first < b.first : a.second < b.second;
		});//sort intervals by end poins

		std::vector<int> res;
		int count = 0;
		int arrow = INT_MIN;
		for (int i = 0; i < N; ++i)
		{
			if (arrow != INT_MIN && v[i].first <= arrow)
				continue;//prev arrow already covers v[i]
			arrow = v[i].second;//always shot end point since it can cover the most intervals
			res.push_back(arrow);
			++count;
		}

		std::cout << "LeastPointsCoveringAllIntervals Count_SortGreedy for \"" << Debug::ToStr1D<int>()(v) << "\": " << count << " (" << Debug::ToStr1D<int>()(res) << ")" << std::endl;
		return count;
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

LeastPointsCoveringAllIntervals 2SortedSets for "[-2,2], [-1,3], [0,4], [2,4], [2,6], [5,7]": 2, 7
LeastPointsCoveringAllIntervals Count_SortGreedy for "[-2,2], [-1,3], [0,4], [2,4], [2,6], [5,7]": 2 (2, 7)

-|---|---|---|---|---|---|---|---|---|---|---|---|---
-4  -3  -2  -1   0   1   2   3   4   5   6   7   8
 |---------------------------------------|
             |-------|
	             |---------------|
		         |-------------------------------|
				         |-------|
				                    ||

LeastPointsCoveringAllIntervals 2SortedSets for "[-4,6], [-1,1], [0,4], [0,8], [2,4], [5,5]": 1, 4, 5
LeastPointsCoveringAllIntervals Count_SortGreedy for "[-1,1], [0,4], [2,4], [5,5], [-4,6], [0,8]": 3 (1, 4, 5)
*/
#endif