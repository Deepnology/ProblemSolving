#ifndef VALID_TRIANGLE_NUMBER_H
#define VALID_TRIANGLE_NUMBER_H
#include "Debug.h"
/*
Leetcode: Valid Triangle Number
Given an array consists of non-negative integers, your task is to count the number of triplets
chosen from the array that can make triangles if we take them as side lengths of a triangle.
Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are:
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
*/
class ValidTriangleNumber
{
public:
	ValidTriangleNumber() {}
	//similar to 3 sum
	int SortAndGreedy(std::vector<int> & nums)
	{
		int N = nums.size();
		if (N < 3) return 0;
		std::sort(nums.begin(), nums.end());
		int res = 0;
		for (int i = 2; i < N; ++i)
		{
			//now take nums[i] as the longest side
			int left = 0;
			int right = i - 1;
			while (left < right)
			{
				if (nums[left] + nums[right] > nums[i])//left,right,i can form a triangle
				{
					res += (right - left);//fix left, i
					--right;
				}
				else
					++left;
			}
		}
		return res;
	}
};
#endif
