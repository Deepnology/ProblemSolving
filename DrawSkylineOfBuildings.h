#ifndef DRAW_SKYLINE_OF_BUILDINGS_H
#define DRAW_SKYLINE_OF_BUILDINGS_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: The Skyline Problem
Input: a vector of buildings, where each building is represented as <start, end, height>, and is sorted by start points in ascending order
Output: a vector of highest corner points, which is represented as <point, height>

Elements of programming interview, Recursion: Draw the skyline
A number of buildings are visible from a point.
Each building is a rectangle, and the bottom of each building lies on a fixed line.
A building is specified using its left and right coordinates, and its height.
One building may partly obstruct another.
The skyline is the list of coordinates and corresponding heights of what is visible.


                      -------
         ---------    |     |
         |       |    |     |
   ------+---- --+----+-----+------
   |     |   | | |    |     |     |
   |     | --+-+-+--  |     |  ---+------
   |     | | | | | |  |     |  |  |     |
 --+---- | | | | | |  |  ---+--+--+-----+---
 | |   | | | | | | |  |  |  |  |  |     |  |
-0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15-16-17-18-19


                      -------
         ---------    |     |
         |       |    |     |
   ------+       +----+     +------
   |                              |
   |                              +------
   |                                    |
 --+                                    +---
 |                                         |
-0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15-16-17-18-19

Design an efficient algorithm for computing the skyline.

BruteForce: O(n^2) time
UseBST: O(nlogn) time, O(n) space
ModifiedMergeSort: O(nlogn) time

See also ViewFromAboveIntervals.h
*/
class DrawSkylineOfBuildings
{
public:
	DrawSkylineOfBuildings(){}
	~DrawSkylineOfBuildings(){}

	//buildings: a vector of <start,end,height> tuples
	std::vector<std::pair<int, int>> UseBST(const std::vector<std::vector<int>> & buildings)//buildings are sorted by start point in ascending order
	{
		std::map<int, std::vector<std::pair<int, bool>>> pointToHeights;//first: point, second: a list of <height, isStart> pairs
		for (const auto & b : buildings)
		{
			pointToHeights[b[0]].push_back({ b[2], true });// <start,<height,true>>
			pointToHeights[b[1]].push_back({ b[2], false });// <end,<height,false>>
		}

		std::vector<std::pair<int, int>> res;//first: point, second: height
		std::map<int, int> curHeightToCount;//all heights' count in range
		int curHeightMax = 0;

		//enumerate all points in ascending order
		for (const auto & p : pointToHeights)
		{
			const auto & point = p.first;
			const auto & heights = p.second;
			for (const auto & h : heights)
			{
				if (h.second)//cur height point is start
					++curHeightToCount[h.first];
				else//cur height point is end
				{
					--curHeightToCount[h.first];
					if (curHeightToCount[h.first] == 0)
						curHeightToCount.erase(h.first);
				}
			}

			if (curHeightToCount.empty() || curHeightMax != curHeightToCount.crbegin()->first)
			{
				curHeightMax = curHeightToCount.empty() ? 0 : curHeightToCount.crbegin()->first;
				res.push_back({ point, curHeightMax });
			}
		}

		std::cout << "DrawSkylineBuildings UseBST for \"" << Debug::ToStr1D<int>()(buildings) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


public:
	typedef std::pair<std::pair<int, int>, int> building;//first.first: begin idx, first.second: end idx, second: height
	std::vector<building> Recur(std::vector<building> & v)
	{
		//sort by begin idx and end idx
		std::sort(v.begin(), v.end(), [](const building & a, const building & b)->bool
		{
			return a.first.first != b.first.first ? a.first.first < b.first.first : a.first.second < b.first.second;
		});
		std::vector<building> res = this->recur(v, 0, v.size() - 1);
		std::cout << "DrawSkylineOfBuildings Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::vector<building> recur(const std::vector<building> & v, int start, int end)
	{
		if (start == end)
			return{ v[start] };

		int mid = (start + end) / 2;
		std::vector<building> left = this->recur(v, start, mid);
		std::vector<building> right = this->recur(v, mid + 1, end);
		return this->mergeSkylines(left, right);
	}

	std::vector<building> mergeSkylines(std::vector<building> & left, std::vector<building> & right)
	{
		std::vector<building> merged;
		int i = 0;
		int j = 0;
		int L = left.size();
		int R = right.size();
		while (i < L && j < R)//since both left and right are sorted, we can merge them accordingly
		{
			if (left[i].first.second < right[j].first.first)//left[i].end < right[j].start: no intersection
			{
				merged.emplace_back(left[i++]);
			}
			else if (left[i].first.first > right[j].first.second)//left[i].start > right[j].end: no intersection
			{
				merged.emplace_back(right[j++]);
			}
			else if (left[i].first.first <= right[i].first.first)//left[i].start <= right[i].start: has intersection, left is on left side of right
			{
				this->mergeIntersectSkylines(merged, left[i], i, right[j], j);
			}
			else//left[i].start > right[i].start: has intersection, left is on right side of right
			{
				this->mergeIntersectSkylines(merged, right[j], j, left[i], i);
			}
		}
		//now either i has reached L or j has reached R
		while (i < L)
			merged.emplace_back(left[i++]);
		while (j < R)
			merged.emplace_back(right[j++]);

		return merged;
	}

	//this function is the most tricky part
	void mergeIntersectSkylines(std::vector<building> & merged, building & L, int & idxL, building & R, int & idxR)//assume L.start <= R.start: L is on left side of R
	{
		if (L.first.second <= R.first.second)//L.end <= R.end: L doesn't cover R's right side
		{
			if (L.second > R.second)//L.height > R.height
			{
				if (L.first.second != R.first.second)//L.end != R.end: L doesn't cover R completely, add L, advance idxL, shrink R.start to L.end
				{
					merged.push_back(L);
					++idxL;
					R.first.first = L.first.second;
				}
				else//L covers R completely: advance idxR
					++idxR;
			}
			else if (L.second == R.second)//same height: extend R.start to L.end, advance idxL
			{
				R.first.first = L.first.first;
				++idxL;
			}
			else//L.height < R.height: add the lower segment from L.start to R.start, advance idxL
			{
				if (L.first.first != R.first.first)
					merged.push_back({ { L.first.first, R.first.first }, L.second });
				++idxL;
			}
		}
		else//L.end > R.end: L covers R's right side
		{
			if (L.second >= R.second)//L.height >= R.height: advance idxR
			{
				++idxR;
			}
			else//L.height < R.height: add the lower segment from L.start to R.start, move L.start to R.end (because L is longer), add R, advance idxR
			{
				if (L.first.first != R.first.first)
					merged.push_back({ { L.first.first, R.first.first }, L.second });

				L.first.first = R.first.second;
				merged.push_back(R);
				++idxR;
			}
		}
	}

};
/*
DrawSkylineBuildings UseBST for "[2,9,10], [3,7,15], [5,12,12], [15,20,10], [19,24,8]": [2,10], [3,15], [7,12], [12,0], [15,10], [20,8], [24,0]
DrawSkylineBuildings UseBST for "[0,5,2], [3,7,1], [10,14,3], [12,16,2]": [0,2], [5,1], [7,0], [10,3], [14,2], [16,0]
DrawSkylineBuildings UseBST for "[11,17,1], [13,16,2], [10,12,5], [5,9,2], [0,3,1], [4,8,4], [7,14,3], [1,6,3]": [0,1], [1,3], [4,4], [8,3], [10,5], [12,3], [14,2], [16,1], [17,0]
DrawSkylineOfBuildings Recur for "[(0,3),1], [(1,6),3], [(4,8),4], [(5,9),2], [(7,14),3], [(10,12),5], [(11,17),1], [(13,16),2]": [(0,1),1], [(1,4),3], [(4,8),4], [(8,10),3], [(10,12),5], [(12,14),3], [(14,16),2], [(16,17),1]
*/
#endif