#ifndef MODIFY_1_ELEMENT_TO_NON_DECR_ARR_H
#define MODIFY_1_ELEMENT_TO_NON_DECR_ARR_H
#include "Debug.h"
/*
Leetcode: Non-decreasing array
Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.
We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).
Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first
4
to
1
to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
*/
class Modify1ElementToNonDecrArr
{
public:
	Modify1ElementToNonDecrArr() {}

	bool CheckPossibility(std::vector<int>& nums)
	{
		int N = nums.size();
		int count = 0;
		for (int i = 1; i < N; ++i)
		{
			if (nums[i - 1] > nums[i])
			{
				if (count++) return false;
				//now we are sure nums[i-2] < nums[i-1]
				if (i - 2 < 0 || nums[i - 2] <= nums[i])
					nums[i - 1] = nums[i];//replace nums[i-1] with nums[i]
				else
					nums[i] = nums[i - 1];//replace nums[i] with nums[i-1]
			}
		}
		return true;
	}
};
#endif
