#ifndef LINE_REFLECTION_H
#define LINE_REFLECTION_H
#include "Debug.h"
/*
Leetcode: Line Reflection
Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given set of points.
Example 1:
Given points = [[1,1],[-1,1]], return true.
Example 2:
Given points = [[1,1],[-1,-1]], return false.
Follow up:
Could you do better than O(n2)?
Hint:
1. Find the smallest and largest x-value for all points.
2. If there is a line then it should be at y = (minX + maxX) / 2.
3. For each point, make sure that it has a reflected point in the opposite side.
*/
class LineReflection
{
public:
	LineReflection() {}
	~LineReflection() {}

	bool isReflected(const std::vector<std::pair<int, int>> & points)
	{
		int N = points.size();
		int maxX = INT_MIN;
		int minX = INT_MAX;
		std::unordered_map<int, std::unordered_set<int>> xToYs;
		for (int i = 0; i < N; ++i)
		{
			maxX = std::max(maxX, points[i].first);
			minX = std::min(minX, points[i].first);
			xToYs[points[i].first].insert(points[i].second);
		}

		double midX = (double)(maxX + minX) / 2;
		bool res = true;
		for (int i = 0; i < N; ++i)
		{
			//(oppositeX + points[i].first) / 2 = midX
			//oppositeX = 2*midX - points[i].first
			int oppositeX = int(2 * midX - (double)points[i].first);
			if (!xToYs.count(oppositeX) || !xToYs[oppositeX].count(points[i].second))//if oppositeX doesn't exist OR oppositeY doesn't exist
			{
				res = false;
				break;
			}
		}

		std::cout << "LineReflection isReflected for \"" << Debug::ToStr1D<int>()(points) << "\": " << res << std::endl;
		return res;
	}
};
/*
LineReflection isReflected for "[1,1], [-1,1]": 1
LineReflection isReflected for "[1,1], [-1,-1]": 0
*/
#endif
