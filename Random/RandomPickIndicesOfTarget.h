#ifndef RANDOM_PICK_INDICES_OF_TARGET_H
#define RANDOM_PICK_INDICES_OF_TARGET_H
#include "Debug.h"
/*
Leetcode: Random Pick Index
Given an array of integers with possible duplicates, randomly output the index of a given target number.
You can assume that the given target number must exist in the array.

Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

Example:
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);
// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);
// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);
*/
class RandomPickIndicesOfTarget
{
	std::vector<int> copy;
public:
	RandomPickIndicesOfTarget(std::vector<int> nums) : copy(nums) {}

	int Pick(int target)
	{
		int N = copy.size();
		int count = 0;
		int res;
		for (int i = 0; i < N; ++i)
		{
			if (copy[i] != target)
				continue;
			++count;
			if (count == 1)
				res = i;
			else if (rand() % count == 0)
				res = i;
		}

		std::cout << "RandomPickIndicesOfTarget Pick for \"" << target << "\": " << res << std::endl;
		return res;
	}
};
/*
RandomPickIndicesOfTarget Pick for "3": 4
RandomPickIndicesOfTarget Pick for "1": 0
*/
#endif
