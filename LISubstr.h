#ifndef LISUBSTR_H
#define LISUBSTR_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Longest Continuous Increasing Subsequence
Elements of programming interview, Array: Compute the longest contiguous increasing subarray
http://java-fries.com/java/interview-programs/25-find-longest-increasing-sub-sequence-in-an-array-of-integers

BruteForce (enumerate all substr and check if each substr is incr): O(n^3) time
HeuristicSkip: O(n) time, O(1) space
(Skipping is a heuristic in that it does not improve the worst-case complexity
, but the best case complexity reduces to O(max(n/L, L)) time, where L is the length of the longest increasing subarray.)

see also LongestConsecutiveSeq.h
*/
class LISubstr
{
public:
	LISubstr(){}
	~LISubstr(){}

	int Len_HeuristicSkip(const std::vector<int> & x)
	{
		int N = x.size();
		int maxIncrCount = 1;//init value is 1
		int maxIncrSubStrBegin = 0;
		int maxIncrSubStrEnd = 0;
		int curBegin = 0;
		while (curBegin < N)
		{
			int curEnd = curBegin + maxIncrCount - 1;
			while (curEnd < N && curEnd > curBegin && x[curEnd - 1] < x[curEnd])
				--curEnd;
			if (curEnd != curBegin)
			{
				curBegin = curEnd;//skip x[curBegin]~x[curEnd - 1]
				continue;
			}
			
			curEnd = (curBegin + maxIncrCount - 1) + 1;
			while (curEnd < N && x[curEnd - 1] < x[curEnd])
				++curEnd;
			--curEnd;

			if (curEnd - curBegin + 1 > maxIncrCount)
			{
				maxIncrSubStrBegin = curBegin;
				maxIncrSubStrEnd = curEnd;
				maxIncrCount = curEnd - curBegin + 1;
			}
			curBegin = curEnd + 1;
		}

		std::vector<int> lisubstr(x.begin() + maxIncrSubStrBegin, x.begin() + maxIncrSubStrEnd + 1);
		std::cout << "LISubstr HeuristicSkip for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << ". (" << Debug::ToStr1D<int>()(lisubstr) << ")" << std::endl;
		return maxIncrCount;
	}

	int Len_Iterate(const std::vector<int> & x)//O(n) time
	{
		int N = x.size();
		int maxIncrCount = 1;
		int maxIncrSubStrBegin = 0;
		int maxIncrSubStrEnd = 0;
		int curBegin = 0;
		while (curBegin < N)
		{
			int curEnd = curBegin + 1;
			while (curEnd < N && x[curEnd - 1] < x[curEnd])
				++curEnd;
			--curEnd;

			if (curEnd - curBegin + 1 > maxIncrCount)
			{
				maxIncrSubStrBegin = curBegin;
				maxIncrSubStrEnd = curEnd;
				maxIncrCount = curEnd - curBegin + 1;
			}
			curBegin = curEnd + 1;
		}

		std::vector<int> lisubstr(x.begin() + maxIncrSubStrBegin, x.begin() + maxIncrSubStrEnd + 1);
		std::cout << "LISubstr Iterate for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << ". (" << Debug::ToStr1D<int>()(lisubstr) << ")" << std::endl;
		return maxIncrCount;
	}

	int Len_Iterate2(const std::vector<int> & num)//O(n) time
	{
		if (num.empty())
			return 0;
		
		int N = num.size();
		int maxIncrSubStrCount = 1;
		int curIncrSubStrCount = 1;

		int curIncrSubStrBegin = 0;
		int maxIncrSubStrBegin = 0;
		int maxIncrSubStrEnd = 0;
		for (int i = 1; i < N; ++i)
		{
			int diff = num[i] - num[i - 1];
			if (diff > 0)//this element is a consecutive of previous one
			{
				++curIncrSubStrCount;
				if (curIncrSubStrCount > maxIncrSubStrCount)
				{
					maxIncrSubStrCount = curIncrSubStrCount;
					maxIncrSubStrBegin = curIncrSubStrBegin;
					maxIncrSubStrEnd = i;
				}
			}
			else
			{
				curIncrSubStrCount = 1;//reset
				curIncrSubStrBegin = i;//reset
			}
		}
		std::vector<int> lisubstr(num.begin() + maxIncrSubStrBegin, num.begin() + maxIncrSubStrEnd + 1);
		std::cout << "LISubstr Iterate2 for \"" << Debug::ToStr1D<int>()(num) << "\": " << maxIncrSubStrCount << " (" << Debug::ToStr1D<int>()(lisubstr) << ")" << std::endl;
		return maxIncrSubStrCount;
	}
};
/*
LISubstr HeuristicSkip for "2, 3, -1, -3, 6, 8, 9, 10, 5, 6, 7": 5. (-3, 6, 8, 9, 10)
LISubstr Iterate for "2, 3, -1, -3, 6, 8, 9, 10, 5, 6, 7": 5. (-3, 6, 8, 9, 10)
LISubstr Iterate2 for "2, 3, -1, -3, 6, 8, 9, 10, 5, 6, 7": 5 (-3, 6, 8, 9, 10)
*/
#endif