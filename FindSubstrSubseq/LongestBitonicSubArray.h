#ifndef LONGEST_BITONIC_SUB_ARRAY_H
#define LONGEST_BITONIC_SUB_ARRAY_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/maximum-length-bitonic-subarray/
Given an integer array.
A subarray A[i...j] is bitonic if there is a k with i <= k <= j such that
A[i] <= A[i + 1] ... <= A[k] >= A[k + 1] >= .. A[j - 1] >= A[j].

O(n) time, O(1) space
see LBSubArr.h
*/
class LongestBitonicSubArray
{
public:
	LongestBitonicSubArray(){}
	~LongestBitonicSubArray(){}

	int Len(const std::vector<int> & v)
	{
		int N = v.size();
		bool incr = v[0] <= v[1] ? true : false;
		int count = 1;
		int begin = 0;
		int maxLen = 1;
		int maxBegin;
		int maxEnd;

		for (int i = 0; i < N - 1; ++i)
		{
			if (v[i] == v[i + 1])
			{
				++count;//continue
			}
			else if (v[i] < v[i + 1])
			{
				if (incr)
					++count;//continue
				else
				{
					/*switch from decr to incr: reset*/
					incr = !incr;
					count = 2;
					begin = i;
				}
			}
			else
			{
				if (!incr)
					++count;//continue
				else
				{
					/*switch from incr to decr: continue*/
					incr = !incr;
					++count;
				}
			}

			if (count > maxLen)
			{
				maxLen = count;
				maxBegin = begin;
				maxEnd = i + 1;
			}
		}

		std::cout << "LongestBitonicSubArray for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << ", (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxLen;
	}
};
/*
LongestBitonicSubArray for "20, 4, 1, 2, 3, 4, 2, 10": 5, (1, 2, 3, 4, 2)
LongestBitonicSubArray for "9, 1, 3, 7, 4, 2, 5, 8, 10, 7, 6, 3, 5, 7, 1": 7, (2, 5, 8, 10, 7, 6, 3)
*/
#endif