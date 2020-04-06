#ifndef MAX_INCR_SUB_ARRAY_SUM_H
#define MAX_INCR_SUB_ARRAY_SUM_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5649094550749184
Given an array of integer pairs.
Find a sub-array such that the 1st element in the pairs are in increasing order and the sum of 2nd element of the pairs are maximum.

Kadane: O(n) time, O(1) space
*/
class MaxIncrSubArraySum
{
public:
	MaxIncrSubArraySum(){}
	~MaxIncrSubArraySum(){}
	
	int Kadane_2Pass(const std::vector<std::pair<int, int>> & v, int & begin, int & end)
	{
		int N = v.size();
		int sum = 0;
		int dpMax = INT_MIN;
		int tmpBegin = 0;
		end = -1;
		for (int i = 0; i < N; ++i)
		{
			/*if decreasing, reset*/
			if (i != 0 && v[i].first < v[i - 1].first)
			{
				sum = 0;
				tmpBegin = i;
			}
			/**/

			sum += v[i].second;
			if (sum < 0)
			{
				sum = 0;
				tmpBegin = i + 1;
				continue;
			}

			if (sum > dpMax)
			{
				dpMax = sum;
				begin = tmpBegin;
				end = i;
			}
		}

		if (end == -1)
		{
			dpMax = INT_MIN;
			begin = end = 0;
			for (int i = 0; i < N; ++i)
			{
				if (v[i].second > dpMax)
				{
					dpMax = v[i].second;
					begin = end = i;
				}
			}
		}

		std::cout << "MaxIncrSubArraySum Kadane_2Pass for \"" << Debug::ToStr1D<int>()(v) << "\": " << dpMax << " (" << Debug::ToStr1D<int>()(v, begin, end) << ")" << std::endl;
		return dpMax;
	}
};
/*
MaxIncrSubArraySum Kadane_2Pass for "[0,-3], [1,3], [4,-1], [6,4], [5,7], [6,-2], [7,4], [8,-2], [7,8], [9,-9], [10,8], [11,2], [12,-1]": 10 ([10,8], [11,2])
*/
#endif