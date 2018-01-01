#ifndef PERFECT_RECTANGLE_H
#define PERFECT_RECTANGLE_H
#include "Debug.h"
/*
Leetcode: Perfect Rectangle
Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.
Each rectangle is represented as a bottom-left point and a top-right point.
For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).
*/
class PerfectRectangle
{
public:
	PerfectRectangle() {}

	bool IsRectangleCover(const std::vector<std::vector<int>> & rectangles)
	{
		bool res = UseHashMap(rectangles);
		Debug::Print2D<int>()(rectangles, false);
		std::cout << "PerfectRectangle UseHashMap for the above bottom-left and top-right points: " << res << std::endl;
		return res;
	}

	bool UseHashMap(const std::vector<std::vector<int>> & rectangles)
	{
		//1. sum of all areas of sub-rectangles must be equal to area of large rectangle
		//2. the 4 points at corners of large rectange must occur exactly once
		//all other points must occur even times
		int N = rectangles.size();
		if (N == 0) return false;
		int blx = INT_MAX;
		int bly = INT_MAX;
		int urx = INT_MIN;
		int ury = INT_MIN;
		int area = 0;
		std::unordered_map<std::string, int> count;
		for (int i = 0; i < N; ++i)
		{
			blx = std::min(blx, rectangles[i][0]);
			bly = std::min(bly, rectangles[i][1]);
			urx = std::max(urx, rectangles[i][2]);
			ury = std::max(ury, rectangles[i][3]);
			area += (rectangles[i][2] - rectangles[i][0])*(rectangles[i][3] - rectangles[i][1]);
			++count[(std::to_string(rectangles[i][0]) + "," + std::to_string(rectangles[i][1]))];
			++count[(std::to_string(rectangles[i][2]) + "," + std::to_string(rectangles[i][3]))];
			++count[(std::to_string(rectangles[i][0]) + "," + std::to_string(rectangles[i][3]))];
			++count[(std::to_string(rectangles[i][2]) + "," + std::to_string(rectangles[i][1]))];
		}
		
		if (area != (urx - blx)*(ury - bly))
			return false;
		if (count.count(std::to_string(blx) + "," + std::to_string(bly)) == 0 || count[std::to_string(blx) + "," + std::to_string(bly)] != 1 ||
			count.count(std::to_string(urx) + "," + std::to_string(ury)) == 0 || count[std::to_string(urx) + "," + std::to_string(ury)] != 1 ||
			count.count(std::to_string(blx) + "," + std::to_string(ury)) == 0 || count[std::to_string(blx) + "," + std::to_string(ury)] != 1 ||
			count.count(std::to_string(urx) + "," + std::to_string(bly)) == 0 || count[std::to_string(urx) + "," + std::to_string(bly)] != 1)
			return false;
		int odd = 0;
		for (const auto & p : count)
			if (p.second & 1)
				++odd;
		if (odd != 4) return false;
		return true;
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 3, 3
Row#1	= 3, 1, 4, 2
Row#2	= 3, 2, 4, 4
Row#3	= 1, 3, 2, 4
Row#4	= 2, 3, 3, 4

PerfectRectangle UseHashMap for the above bottom-left and top-right points: 1
*/
#endif
