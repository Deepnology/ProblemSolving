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

	/*
	Leetcode: Continuous Subarray sum
	Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2
	that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.
	Example 1:
	Input: [23, 2, 4, 6, 7],  k=6
	Output: True
	Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
	Example 2:
	Input: [23, 2, 6, 4, 7],  k=6
	Output: True
	Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
	*/
	bool ExistSubArrSum_MultipleOfK(std::vector<int> & v, int k)
	{
		bool res = existSubArrSum_MultipleOfK(v, k);
		std::cout << "SubArrayWGivenSum ExistSubArrSum_MultipleOfK for k=" << k << ", \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	bool existSubArrSum_MultipleOfK(std::vector<int> & v, int k)
	{
		//modified from LongestSubArrWEqualSum.h
		std::unordered_map<int, int> prefixSumMap;//<prefixSum%k, first occur idx>
		int prefixSum = 0;
		int N = v.size();
		for (int i = 0; i < N; ++i)
		{
			prefixSum += v[i];
			if (k != 0) prefixSum %= k;
			if (prefixSum == 0 && i >= 1)//cur prefixSum is a multiple of k
				return true;
			if (prefixSumMap.count(prefixSum))
			{
				if (i - prefixSumMap[prefixSum] > 1)//[prefixSumMap[prefixSum]+1,...,i] must contain at least 2 elements
					return true;
			}
			else
				prefixSumMap.insert({ prefixSum, i });
		}
		return false;
	}
};
/*
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

SubArrayWGivenSum ExistSubArrSum_MultipleOfK for k=6, "23, 2, 4, 6, 7": 1
SubArrayWGivenSum ExistSubArrSum_MultipleOfK for k=6, "23, 2, 6, 4, 7": 1
*/
#endif