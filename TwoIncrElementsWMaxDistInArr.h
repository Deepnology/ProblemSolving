#ifndef TWO_INCR_ELEMENTS_W_MAX_DIST_IN_ARR_H
#define TWO_INCR_ELEMENTS_W_MAX_DIST_IN_ARR_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
This problem can be solved in 4 different ways! brillant!
http://www.geeksforgeeks.org/given-an-array-arr-find-the-maximum-j-i-such-that-arrj-arri/
Google
http://www.careercup.com/question?id=11532811
Given an integer array v[].
Find [i, j] such that v[i] < v[j] and j-i is maximum.

BruteForce: O(n^2) time, O(1) space
Greedy: O(n) time, O(n) space
Recur: O(2^n) time, O(1) space
DP2D: O(n^2) time, O(n^2) space

See also BestTimeBuySellStock.h, ThreeIncrElementsInArray.h
*/
class TwoIncrElementsWMaxDistInArr
{
public:
	TwoIncrElementsWMaxDistInArr(){}
	~TwoIncrElementsWMaxDistInArr(){}

	//enumerate all possible pairs in v: O(n^2) time, O(1) space
	void BruteForce(const std::vector<int> & v)
	{
		int N = v.size();
		int maxDist = INT_MIN;
		int maxLeft = -1;
		int maxRight = -1;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (v[i] < v[j] && j - i > maxDist)
				{
					maxDist = j - i;
					maxLeft = i;
					maxRight = j;
				}
			}
		}

		std::string leftNum = maxLeft == -1 ? "N" : std::to_string(v[maxLeft]);
		std::string rightNum = maxRight == -1 ? "N" : std::to_string(v[maxRight]);
		std::cout << "TwoIncrElementsWMaxDistInArr BruteForce for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxDist << ", [" << leftNum << ", " << rightNum << "]" << std::endl;
	}

	//O(n) time, O(n) space
	void Greedy(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> leftMin(N);
		std::vector<int> rightMax(N);

		leftMin[0] = v[0];
		for (int i = 1; i < N; ++i)
		{
			leftMin[i] = std::min(v[i], leftMin[i - 1]);
		}

		rightMax[N - 1] = v[N - 1];
		for (int i = N - 2; i >= 0; --i)
		{
			rightMax[i] = std::max(v[i], rightMax[i + 1]);
		}

		//now both leftMin and rightMax are sorted in descending order
		//we want to find the pair, where first<second, with longest distance from the 2 sorted array
		//see also MinPairdiff2SortedArrays.h
		int maxDist = INT_MIN;
		int maxLeft = -1;
		int maxRight = -1;
		int i = 0;
		int j = 0;
		while (i < N && j < N)
		{
			if (leftMin[i] < rightMax[j])
			{
				if (j - i > maxDist)
				{
					maxDist = j - i;
					maxLeft = i;
					maxRight = j;
				}
				++j;
			}
			else
			{
				++i;
			}
		}

		std::cout << Debug::ToStr1D<int>()(leftMin) << std::endl;
		std::cout << Debug::ToStr1D<int>()(rightMax) << std::endl;
		std::string leftNum = maxLeft == -1 ? "N" : std::to_string(v[maxLeft]);
		std::string rightNum = maxRight == -1 ? "N" : std::to_string(v[maxRight]);
		std::cout << "TwoIncrElementsWMaxDistInArr Greedy for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxDist << ", [" << leftNum << ", " << rightNum << "]" << std::endl;
	}

	//O(2^n) time, O(1) space. see also CoinsInLine.h, MinRemovalOfEndInArrayUntil.h
	void Recur(const std::vector<int> & v)
	{
		int N = v.size();
		int res = this->recur(v, 0, N - 1);

		std::cout << "TwoIncrElementsWMaxDistInArr Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
	}
private:
	int recur(const std::vector<int> & v, int begin, int end)
	{
		if (end - begin == 1)
			return v[begin] < v[end] ? 1 : 0;

		if (v[begin] < v[end])
			return end - begin;

		int keepBegin = this->recur(v, begin, end - 1);
		int keepEnd = this->recur(v, begin + 1, end);
		return std::max(keepBegin, keepEnd);
	}

public:
	//O(n^2) time, O(n^2) space. see also CoinsInLine.h, MinRemovalOfEndInArrayUntil.h
	void DP2D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::vector<int>> dp(N, std::vector<int>(N));

		for (int len = 0; len < N; ++len)
		{
			for (int left = 0, right = len; right < N; ++left, ++right)
			{
				dp[left][right] = v[left] < v[right] ? 
					right - left :
					std::max(left + 1 < N ? dp[left + 1][right] : 0, right - 1 >= 0 ? dp[left][right - 1] : 0);
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "TwoIncrElementWMaxDistInArr DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << dp[0][N - 1] << std::endl;
	}
};
/*
TwoIncrElementsWMaxDistInArr BruteForce for "21, 20, 19, 18, 17, 16, 15, 13, 17, 18, 1, 2, 3, 14, 4, 5, 15, 6, 7, -1, 0, -1, -2, -3, -4": 9, [13, 15]
21, 20, 19, 18, 17, 16, 15, 13, 13, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -2, -3, -4
21, 20, 19, 18, 18, 18, 18, 18, 18, 18, 15, 15, 15, 15, 15, 15, 15, 7, 7, 0, 0, -1, -2, -3, -4
TwoIncrElementsWMaxDistInArr Greedy for "21, 20, 19, 18, 17, 16, 15, 13, 17, 18, 1, 2, 3, 14, 4, 5, 15, 6, 7, -1, 0, -1, -2, -3, -4": 9, [13, 15]
TwoIncrElementsWMaxDistInArr Recur for "21, 20, 19, 18, 17, 16, 15, 13, 17, 18, 1, 2, 3, 14, 4, 5, 15, 6, 7, -1, 0, -1, -2, -3, -4": 9
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 5, 5, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 5, 5, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#2	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 5, 5, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#3	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 5, 5, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 5, 5, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#5	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#6	= 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 4, 4, 4, 4, 4, 4, 4
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4
Row#15	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3
Row#16	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#17	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
Row#18	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1
Row#19	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1
Row#20	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#21	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#22	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#23	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#24	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

TwoIncrElementWMaxDistInArr DP2D for "21, 20, 19, 18, 17, 16, 15, 13, 17, 18, 1, 2, 3, 14, 4, 5, 15, 6, 7, -1, 0, -1, -2, -3, -4": 9
*/
#endif