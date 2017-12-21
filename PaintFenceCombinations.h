#ifndef PAINT_FENCE_COMBINATIONS_H
#define PAINT_FENCE_COMBINATIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Paint Fence
There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.
Note:
n and k are non-negative integers.
*/
class PaintFenceCombinations
{
public:
	PaintFenceCombinations() {}
	~PaintFenceCombinations() {}

	int ConstSpace(int n, int k)
	{
		//res[0]: 0 post, 0 ways
		//res[1]: 1 post, k ways (can choose one from k colors)
		//res[2]: 2 posts, k*k ways (res[2] can be either same or diff from res[1])
		//res[3]: 3 posts, if res[1] and res[2] have same colors (k ways), res[3] must be diff so has k-1 ways; if res[1] and res[2] have diff colors (k*(k-1) ways), res[3] can have k ways.
		//=> res[3] = k*(k-1) + k*(k-1)*k = (k-1)*(k + k*k) = (k-1)*(res[1] + res[2])
		std::vector<int> res({ 0, k, k*k, 0 });
		if (n <= 2)
			return res[n];

		for (int i = 3; i <= n; ++i)
		{
			res[3] = (k - 1) * (res[1] + res[2]);
			res[1] = res[2];
			res[2] = res[3];
		}

		std::cout << "PaintFenceCombinations ConstSpace for \"n=" << n << ", k=" << k << "\": " << res[3] << std::endl;
		return res[3];
	}
};
/*
PaintFenceCombinations ConstSpace for "n=3, k=3": 24
*/
#endif
