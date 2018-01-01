#ifndef NUM_OF_BOOMERANGS_H
#define NUM_OF_BOOMERANGS_H
#include "Debug.h"
/*
Leetcode: Number of Boomerangs
Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
Find the number of boomerangs.
You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).
Example:
Input:
[[0,0],[1,0],[2,0]]
Output:
2
Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
*/
class NumOfBoomerangs
{
public:
	NumOfBoomerangs() {}

	int HashMap(const std::vector<std::pair<int, int>> & points)
	{
		int N = points.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			std::unordered_map<double, std::unordered_set<int>> distIdxList;//<dist, list of indices>
			for (int j = 0; j < N; ++j)
			{
				if (i == j) continue;
				int deltaX = points[j].first - points[i].first;
				int deltaY = points[j].second - points[i].second;
				double dist = sqrt(deltaX*deltaX + deltaY*deltaY);
				distIdxList[dist].insert(j);
			}
			for (const auto & p : distIdxList)
			{
				if (p.second.size() > 1)
					res += p.second.size()*(p.second.size() - 1);
			}
		}

		std::cout << "NumOfBoomerangs HashMap for \"" << Debug::ToStr1D<int>()(points) << "\": " << res << std::endl;
		return res;
	}
};
/*
NumOfBoomerangs HashMap for "[0,0], [1,0], [2,0]": 2
*/
#endif
