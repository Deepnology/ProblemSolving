#ifndef LONGEST_SUB_ARR_PREDICATE_H
#define LONGEST_SUB_ARR_PREDICATE_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Top 20 coding interview
Find the longest subarray that satisfies the predicate.

O(n) time, O(1) space
*/
class LongestSubArrPredicate
{
public:
	int Length(const std::vector<int> & v, const std::function<bool(const int &)> & f)
	{
		int N = v.size();
		int maxLen = 0;
		int maxEnd = 0;
		int validBegin = 0;
		for (int i = 0; i < N; ++i)
		{
			if (!f(v[i]))
			{
				validBegin = i + 1;
			}

			int curLen = i - validBegin + 1;
			if (curLen > maxLen)
			{
				maxLen = curLen;
				maxEnd = i;
			}
		}

		std::cout << "LongestSubArrPredicate for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << ", [" << Debug::ToStr1D<int>()(v, maxEnd - maxLen + 1, maxEnd) << "]" << std::endl;
		return maxLen;
	}
};
/*
LongestSubArrPredicate for "3, 5, 5, 7, 3, 0, 0, 9, 9, 0, 0, 0, 0, 0, 6, 4, 4, 3, 6, 8": 5, [0, 0, 0, 0, 0]
*/
#endif