#ifndef HEATERS_H
#define HEATERS_H
#include "Debug.h"
/*
Leetcode: Heaters
Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.
Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.
So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.
Note:
Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
As long as a house is in the heaters' warm radius range, it can be warmed.
All the heaters follow your radius standard and the warm radius will the same.
Example 1:
Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
*/
class Heaters
{
public:
	Heaters() {}

	int MinRadius(const std::vector<int> & houses, std::vector<int> && heaters)
	{
		std::sort(heaters.begin(), heaters.end());
		int N = houses.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			auto ub = std::upper_bound(heaters.begin(), heaters.end(), houses[i]);
			int left = INT_MAX;//dist from left heater to house[i]
			int right = INT_MAX;//dist from right heater to house[i]
			if (ub != heaters.end())
				right = *ub - houses[i];
			if (ub != heaters.begin())
				left = houses[i] - *std::prev(ub);
			int minDist = std::min(left, right);
			res = std::max(res, minDist);
		}

		std::cout << "Heaters MinRadius for \"" << Debug::ToStr1D<int>()(houses) << "\", \"" << Debug::ToStr1D<int>()(heaters) << "\": " << res << std::endl;
		return res;
	}
};
/*
Heaters MinRadius for "1, 2, 3", "2": 1
Heaters MinRadius for "1, 2, 3, 4", "1, 4": 1
*/
#endif
