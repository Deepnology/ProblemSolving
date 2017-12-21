#ifndef REARRANGE_TO_WAVE_ARRAY_H
#define REARRANGE_TO_WAVE_ARRAY_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Wiggle Sort
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

Leetcode: Wiggle Sort II
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6].
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.
Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

Sort the array (or 3way partition the array with median element)
Let left points to end of 1st half, right points to end of 2nd half
Build a new array with interleaving left-- and right--
*/
class RearrangeToWaveArray
{
public:
	RearrangeToWaveArray(){}
	~RearrangeToWaveArray(){}

	//I.
	void WiggleSort(std::vector<int> & v)
	{
		int N = v.size();
		std::string before = Debug::ToStr1D<int>()(v);
		for (int i = 0; i < N - 1; ++i)
		{
			if (i % 2 == 0)//even
			{
				if (v[i] > v[i + 1])
					std::swap(v[i], v[i + 1]);
			}
			else//odd
			{
				if (v[i] < v[i + 1])
					std::swap(v[i], v[i + 1]);
			}
		}
		/*
		we don't need to check backwards. 
		it is satisfied automatically.
		*/
		std::cout << "RearrangeToWaveArray WiggleSort for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}

	//II.
	void WiggleSortII(std::vector<int> & nums)
	{
		std::string original = Debug::ToStr1D<int>()(nums);
		int N = nums.size();
		if (N <= 1) return;

		//1. find the end element of the 1st half (left of middle pair for even N, or left of middle for odd N)
		int midEvenOddLeft = (N - 1) / 2;//now mid points to the left of middle pair for even N, or the left of middle for odd N
		std::nth_element(nums.begin(), nums.begin() + midEvenOddLeft, nums.end());
		int pivotVal = nums[midEvenOddLeft];

		//2. 3way partition to move less elements in the front, equal elements in middle, greater elements in the back
		int curFrontCount = 0;
		int curBackCount = N - 1;
		int i = 0;
		while (i <= curBackCount)
		{
			if (nums[i] < pivotVal)
			{
				std::swap(nums[curFrontCount++], nums[i++]);
			}
			else if (nums[i] == pivotVal)
			{
				++i;
			}
			else
			{
				std::swap(nums[curBackCount--], nums[i]);
			}
		}

		//3. let left points to end of 1st half, right points to end of 2nd half
		//build a new array with interleaving left-- and right--
		std::vector<int> res(N);
		int left = (N - 1) / 2;
		int right = N - 1;
		for (int i = 0; i < N; ++i)
		{
			if (i % 2 == 0)//even
			{
				res[i] = nums[left--];
			}
			else
			{
				res[i] = nums[right--];
			}
		}
		res.swap(nums);

		std::cout << "RearrangeToWaveArray WiggleSortII for \"" << original << "\": " << Debug::ToStr1D<int>()(nums) << std::endl;
	}
};
/*
RearrangeToWaveArray WiggleSort for "8, 17, 3, 7, 14, 13, 5, 9, 12, 15, 2": 8, 17, 3, 14, 7, 13, 5, 12, 9, 15, 2
RearrangeToWaveArray WiggleSort for "3, 5, 2, 1, 6, 4": 3, 5, 1, 6, 2, 4
RearrangeToWaveArray WiggleSort for "1, 5, 1, 1, 6, 4": 1, 5, 1, 6, 1, 4
RearrangeToWaveArray WiggleSort for "1, 3, 2, 2, 3, 1": 1, 3, 2, 3, 1, 2
RearrangeToWaveArray WiggleSortII for "8, 17, 3, 7, 14, 13, 5, 9, 12, 15, 2": 9, 12, 8, 17, 7, 15, 5, 14, 3, 13, 2
RearrangeToWaveArray WiggleSortII for "3, 5, 2, 1, 6, 4": 3, 4, 2, 6, 1, 5
RearrangeToWaveArray WiggleSortII for "1, 5, 1, 1, 6, 4": 1, 4, 1, 6, 1, 5
RearrangeToWaveArray WiggleSortII for "1, 3, 2, 2, 3, 1": 2, 3, 1, 3, 1, 2
*/
#endif