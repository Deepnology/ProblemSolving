#ifndef LONGEST_SUB_ARR_W_EQUAL_ELEMENTS_H
#define LONGEST_SUB_ARR_W_EQUAL_ELEMENTS_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Top 20 coding problems
The Plateau Problem
Given an inetger array that may have duplicated elements.
A plateau is a subarray that contains all equal elements.
Find the longest plateau length, i.e., the longest subarray that contain all equal elements.

FromSortedArray: O(n) time, O(1) space
BruteForce (enumerate all subarrays and check if all elements are equal in each subarray): O(n^3) time, O(1) space
Iterate: O(n) time, O(1) space (similar to LISubstr.h)
*/
class LongestSubArrWEqualElements
{
public:
	int FromSortedArray(const std::vector<int> & sorted)
	{
		int N = sorted.size();
		int maxLen = 1;
		int end = 0;
		for (int i = 1; i < N; ++i)
		{
			if (sorted[i] == sorted[i - maxLen])
			{
				++maxLen;
				end = i;
			}
		}

		std::cout << "LongestSubArrWEqualElements FromSortedArray for \"" << Debug::ToStr1D<int>()(sorted) << "\": " << maxLen << ", [" << Debug::ToStr1D<int>()(sorted, end - maxLen + 1, end) << "]" << std::endl;
		return maxLen;
	}

	int Iterate(const std::vector<int> & v)//O(n) time
	{
		int N = v.size();
		int maxLen = 1;
		int end = 0;
		int i = 0;
		while (i < N)
		{
			int j = i + 1;
			while (j < N && v[i] == v[j])
				++j;

			int curLen = (j - 1) - i + 1;
			if (curLen > maxLen)
			{
				maxLen = curLen;
				end = j - 1;
			}
			i = j;
		}

		std::cout << "LongestSubArrWEqualElements Iterate for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << ", [" << Debug::ToStr1D<int>()(v, end - maxLen + 1, end) << "]" << std::endl;
		return maxLen;
	}
};
/*
LongestSubArrWEqualElements FromSortedArray for "1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8": 9, [7, 7, 7, 7, 7, 7, 7, 7, 7]
LongestSubArrWEqualElements FromSortedArray for "1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7": 8, [1, 1, 1, 1, 1, 1, 1, 1]
LongestSubArrWEqualElements Iterate for "2, 3, 3, 3, 1, 1, 1, 1, 1, 1, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 8, 8, 8, 8": 9, [7, 7, 7, 7, 7, 7, 7, 7, 7]
LongestSubArrWEqualElements Iterate for "1, 1, 1, 1, 1, 2, 1, 4, 5, 6, 7, 1, 1, 2, 3": 5, [1, 1, 1, 1, 1]
*/
#endif