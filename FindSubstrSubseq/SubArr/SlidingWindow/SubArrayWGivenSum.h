#ifndef SUB_ARRAY_W_GIVEN_SUM_H
#define SUB_ARRAY_W_GIVEN_SUM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/find-subarray-with-given-sum/
Given an unsorted array of nonnegative integers, find a continuous subarray which adds to a given number.
(Linear Slide Window method find subarray sum works for Non-negative nums only.
With Negative nums, the worst case becomes Quadratic. See also ShortestSubArrWGreaterSum.h)

SlideWindow: O(n) time, O(1) space
BruteForce_PrefixSums: O(n^2) time, O(n) space
BruteForce: O(n^3) time, O(1) space

See also ShortestSubArrWGreaterSum.h, LongestSubArrWEqualSum.h, LongestSubArrWLessEqualSum.h, RangeSumCount.h
*/
class SubArrayWGivenSum
{
public:
	SubArrayWGivenSum(){}
	~SubArrayWGivenSum(){}

	//linear sliding window method finding subArrSum works for non-negative num array only
	void SlideWindow_NonNegativeArr(const std::vector<int> & v, int val)
	{
		int N = v.size();
		int sum = 0;
		int left = 0;
		int right = 0;
		std::vector<std::pair<std::pair<int, int>, std::vector<int>>> res;
		for (; right < N; ++right)
		{
			//1. accumulate running sum
			sum += v[right];

			//2. advance left to keep a longest window where sum <= val
			while (sum - v[left] > val && left < right)
			{
				sum -= v[left];
				++left;
			}

			//3. find all subarrays between left and right, and ended at right
			int sum2 = sum;
			int left2 = left;
			if (sum2 == val)
				res.push_back({ { left2, right }, std::vector<int>(v.begin() + left2, v.begin() + right + 1) });
			while (sum2 - v[left2] == val && left2 < right)
			{
				sum2 -= v[left2];
				++left2;
				res.push_back({ { left2, right }, std::vector<int>(v.begin() + left2, v.begin() + right + 1) });
			}
		}
		
		std::cout << "SubArrayWGivenSum SlideWindow_NonNegativeArr for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(v) << "\":" << std::endl;
		Debug::Print2D<int>()(res);
	}
};
/*
SubArrayWGivenSum SlideWindow_NonNegativeArr for "0" from "0, 0, 0":
Row#0	= [0,0]: 0
Row#1	= [0,1]: 0, 0
Row#2	= [1,1]: 0
Row#3	= [0,2]: 0, 0, 0
Row#4	= [1,2]: 0, 0
Row#5	= [2,2]: 0

SubArrayWGivenSum SlideWindow_NonNegativeArr for "4" from "1, 2, 1, 0, 2, 1, 2, 0, 0, 1, 1, 2, 4":
Row#0	= [0,2]: 1, 2, 1
Row#1	= [0,3]: 1, 2, 1, 0
Row#2	= [2,5]: 1, 0, 2, 1
Row#3	= [5,9]: 1, 2, 0, 0, 1
Row#4	= [6,10]: 2, 0, 0, 1, 1
Row#5	= [7,11]: 0, 0, 1, 1, 2
Row#6	= [8,11]: 0, 1, 1, 2
Row#7	= [9,11]: 1, 1, 2
Row#8	= [12,12]: 4

SubArrayWGivenSum SlideWindow_NonNegativeArr for "4" from "1, 2, 1, -2, 0, 2, 1, 2, 0, 0, 1, -2, 1, 2, 4":
Row#0	= [0,2]: 1, 2, 1
Row#1	= [0,5]: 1, 2, 1, -2, 0, 2
Row#2	= [1,6]: 2, 1, -2, 0, 2, 1
Row#3	= [2,7]: 1, -2, 0, 2, 1, 2
Row#4	= [2,8]: 1, -2, 0, 2, 1, 2, 0
Row#5	= [2,9]: 1, -2, 0, 2, 1, 2, 0, 0
Row#6	= [3,10]: -2, 0, 2, 1, 2, 0, 0, 1
Row#7	= [2,12]: 1, -2, 0, 2, 1, 2, 0, 0, 1, -2, 1
Row#8	= [7,13]: 2, 0, 0, 1, -2, 1, 2
Row#9	= [14,14]: 4
*/
#endif