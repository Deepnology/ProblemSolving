#ifndef MIN_REMOVAL_OF_END_IN_ARRAY_UNTIL_H
#define MIN_REMOVAL_OF_END_IN_ARRAY_UNTIL_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/remove-minimum-elements-either-side-2min-max/
Given an unsorted array, remove minimum elements from either side such that 2*min becomes more than max.

Use O(n) time Min/Max function:
Recur: O(n * 2^n) time
DP2D: O(n^3) time, O(n^2) space

Use O(logn) time segment tree RMQ for Min/Max function:
Recur: O(logn * 2^n) time
DP2D: O(logn * n^2) time, O(n^2) space

Count_FindRemainingArray: O(n^2) time, O(1) space

See also CoinsInLine.h
*/
class MinRemovalOfEndInArrayUntil
{
public:
	MinRemovalOfEndInArrayUntil(){}
	~MinRemovalOfEndInArrayUntil(){}

	int Count_Recur(const std::vector<int> & v)
	{
		int N = v.size();
		int count = this->count_recur(v, 0, N - 1);
		std::cout << "MinRemovalOfEndInArrayUntil Count_Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << count << std::endl;
		return count;
	}
private:
	int count_recur(const std::vector<int> & v, int left, int right)
	{
		if (left >= right)
			return 0;

		int min = this->Min(v, left, right);
		int max = this->Max(v, left, right);
		
		if (2 * min > max)//already satisfied, no removal required
			return 0;
		int removeLeftEnd = this->count_recur(v, left + 1, right);
		int removeRightEnd = this->count_recur(v, left, right - 1);
		return std::min(removeLeftEnd, removeRightEnd) + 1;
	}
	int Min(const std::vector<int> & v, int left, int right)
	{
		int min = INT_MAX;
		for (int i = left; i <= right; ++i)
			if (v[i] < min)
				min = v[i];
		return min;
	}
	int Max(const std::vector<int> & v, int left, int right)
	{
		int max = INT_MIN;
		for (int i = left; i <= right; ++i)
			if (v[i] > max)
				max = v[i];
		return max;
	}

public:
	int Count_DP2D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N));
		for (int len = 0; len < N; ++len)
		{
			for (int left = 0, right = len; right < N; ++left, ++right)
			{
				int min = this->Min(v, left, right);
				int max = this->Max(v, left, right);

				dp[left][right] = (2 * min > max) ? 0 : std::min(
					left + 1 < N ? dp[left + 1][right] + 1 : 0,
					right - 1 >= 0 ? dp[left][right - 1] + 1 : 0);
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "MinRemovalOfEndInArrayUntil Count_DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}

	//brute force enumerate all possible (left,right) pairs
	int Count_Reversely(const std::vector<int> & v)
	{
		int N = v.size();
		int longestLeft = -1;
		int longestRight = 0;

		for (int left = 0; left < N; ++left)
		{
			int min = INT_MAX;
			int max = INT_MIN;
			for (int right = left; right < N; ++right)
			{
				if (v[right] > max)
					max = v[right];
				if (v[right] < min)
					min = v[right];

				if (2 * min <= max)
					break;//not satisfied

				if (right - left > longestRight - longestLeft ||
					longestLeft == -1)
				{
					longestLeft = left;
					longestRight = right;
				}
			}
		}

		int count;
		if (longestLeft == -1)
		{
			longestLeft = 0;
			count = N;
		}
		else
			count = N - (longestRight - longestLeft + 1);
		std::cout << "MinRemovalOfEndInArrayUntil Count_Reversely for \"" << Debug::ToStr1D<int>()(v) << "\": " << count << ", [" << Debug::ToStr1D<int>()(v, longestLeft, longestRight) << "]" << std::endl;
		return count;
	}
};
/*
MinRemovalOfEndInArrayUntil Count_Recur for "4, 5, 100, 9, 10, 11, 12, 15, 200": 4
[rY][cX]
Row#0	= 0, 0, 1, 2, 3, 3, 3, 3, 4
Row#1	= 0, 0, 1, 2, 2, 2, 2, 2, 3
Row#2	= 0, 0, 0, 1, 1, 1, 1, 1, 2
Row#3	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0

MinRemovalOfEndInArrayUntil Count_DP2D for "4, 5, 100, 9, 10, 11, 12, 15, 200": 4
MinRemovalOfEndInArrayUntil Count_Reversely for "4, 5, 100, 9, 10, 11, 12, 15, 200": 4, [9, 10, 11, 12, 15]
MinRemovalOfEndInArrayUntil Count_Recur for "9, 10, 11, 12, 15": 0
[rY][cX]
Row#0	= 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0

MinRemovalOfEndInArrayUntil Count_DP2D for "9, 10, 11, 12, 15": 0
MinRemovalOfEndInArrayUntil Count_Reversely for "9, 10, 11, 12, 15": 0, [9, 10, 11, 12, 15]
*/
#endif