#ifndef MAX_SUM_OF_PAIR_MINS_H
#define MAX_SUM_OF_PAIR_MINS_H
#include "Debug.h"
/*
Leetcode: Array Partition I
Given an array of 2n integers, your task is to group these integers into n pairs of integer
, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.
Example 1:
Input: [1,4,3,2]
Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4.
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].

BruteForce: enumerate all permutations: O(n!) time
Sort: O(nlogn) time
*/
class MaxSumOfPairMins
{
public:
	MaxSumOfPairMins() {}

	int Sort(std::vector<int> && nums)
	{
		std::sort(nums.begin(), nums.end());
		int res = 0;
		int N = nums.size();
		for (int i = 0; i < N; i += 2)
			res += nums[i];

		std::cout << "MaxSumOfPairMins Sort for \"" << Debug::ToStr1D<int>()(nums) << "\": " << res << std::endl;
		return res;
	}
};
/*
MaxSumOfPairMins Sort for "1, 2, 3, 4": 4
*/
#endif
