#ifndef VIEW_FROM_ABOVE_INTERVALS_H
#define VIEW_FROM_ABOVE_INTERVALS_H
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, BST: Compute the view from above
This is a simplified version of a problem that often comes up in computer graphics.
You are given a set of line segments.
Each segment consists of a closed interval of a start and end point, a height, and a color.
When viewed from above, the color at point x on the x-axis is the color of the highest segment that includes x.
No two segments whose intervals overlap have the same height.
(this enables us to use the height as the key for the sorted map)

SortedEndPoints: O(nlogn) time, O(n) space

See also DrawSkylineOfBuildings.h
*/
class ViewFromAboveIntervals
{
public:
	ViewFromAboveIntervals(){}
	~ViewFromAboveIntervals(){}
	typedef std::pair<std::pair<int, int>, std::pair<int, int> > Interval;//first.first: start, first.second: end, second.first: height, second.second: color
	
	std::vector<std::pair<std::pair<int, int>, int> > SortedEndPoints(const std::vector<Interval> & v)
	{
		int N = v.size();
		std::vector<std::pair<std::pair<int, int>, int> > res;

		//1. sort all the end-points by their indices
		std::vector<std::pair<bool, const Interval*> > endPoints;//first: true for start, false for end, second: pointer to Interval in v
		for (int i = 0; i < N; ++i)
		{
			endPoints.emplace_back(true, &v[i]);
			endPoints.emplace_back(false, &v[i]);
		}

#define GetPointVal(x) (x.first ? x.second->first.first : x.second->first.second)//if a start, return start index; else, return end index

		std::sort(endPoints.begin(), endPoints.end(), [](const std::pair<bool, const Interval*> & a, const std::pair<bool, const Interval*> & b)->bool
		{
			return GetPointVal(a) < GetPointVal(b);
		});

		//2. keep track of curTopInterval:
		//extend curTopInterval to curPoint when curTopInterval's height and color are same as prev highest interval
		//otherwise, record curTopInterval that ends at prevPoint, and update curTopInterval with {prevPoint, curPoint, prev highest interval's height and color}
		//before adding or removing the interval associated with curPoint
		int prevPoint = -1;
		std::map<int, const Interval*> prevSortedIntervals;//sorted by height
		int curTopIntervalStart = -1;
		int curTopIntervalEnd = -1;
		int curTopIntervalHeight = -1;
		int curTopIntervalColor = -1;
		for (const auto & curPoint : endPoints)
		{
			//1. before arriving curPoint
			//conditions to update curTopInterval: meet a new (diff) point
			if (!prevSortedIntervals.empty() && prevPoint != GetPointVal(curPoint))
			{
				if (curTopIntervalStart == -1)//met the first start point
				{
					curTopIntervalStart = prevPoint;
					curTopIntervalEnd = GetPointVal(curPoint);
					curTopIntervalHeight = prevSortedIntervals.crbegin()->second->second.first;//the max height
					curTopIntervalColor = prevSortedIntervals.crbegin()->second->second.second;//color of the max height
				}
				else
				{
					//same max height && same color
					if (curTopIntervalHeight == prevSortedIntervals.crbegin()->second->second.first && curTopIntervalColor == prevSortedIntervals.crbegin()->second->second.second)
					{
						curTopIntervalEnd = GetPointVal(curPoint);//extend curTopInterval
					}
					else
					{
						//now curTopInterval should end at prevPoint, record it (record when meets a new TOP interval)
						res.push_back({ { curTopIntervalStart, curTopIntervalEnd }, curTopIntervalColor });

						//update curTopInterval
						curTopIntervalStart = prevPoint;
						curTopIntervalEnd = GetPointVal(curPoint);
						curTopIntervalHeight = prevSortedIntervals.crbegin()->second->second.first;
						curTopIntervalColor = prevSortedIntervals.crbegin()->second->second.second;
					}
				}
			}

			//2. arrive curPoint
			if (curPoint.first)
				prevSortedIntervals.emplace(curPoint.second->second.first, curPoint.second);//add interval (height, pointer) pair when curPoint is a start
			else
				prevSortedIntervals.erase(curPoint.second->second.first);//remove interval (height, pointer) pair when curPoint is an end
			prevPoint = GetPointVal(curPoint);
		}

		//(record the last TOP interval)
		if (curTopIntervalStart != -1)//found at least one interval
		{
			res.push_back({ { curTopIntervalStart, curTopIntervalEnd }, curTopIntervalColor });
		}

		std::cout << "ViewFromAboveIntervals SortedEndPoints for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	
};
/*
ViewFromAboveIntervals SortedEndPoints for "[(0,4),(1,101)], [(5,7),(1,102)], [(9,18),(1,103)], [(2,7),(2,104)], [(8,9),(2,105)], [(12,15),(2,106)], [(1,3),(3,107)], [(6,10),(3,108)], [(11,13),(3,109)], [(14,15),(3,120)], [(16,17),(3,121)], [(4,5),(4,122)], [(19,20),(4,123)]": [(0,1),101], [(1,3),107], [(3,4),104], [(4,5),122], [(5,6),104], [(6,10),108], [(10,11),103], [(11,13),109], [(13,14),106], [(14,15),120], [(15,16),103], [(16,17),121], [(17,18),103], [(19,20),123]
*/
#endif