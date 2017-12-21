/*Greedy*/
#ifndef	LONGEST_SUB_ARR_W_LESS_EQUAL_SUM_H
#define LONGEST_SUB_ARR_W_LESS_EQUAL_SUM_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Find the longest subarray whose sum <= k
Design an algorithm that takes as input an array A of n numbers and a key k, and returns a longest subarray of A for which the subarray sum is less than or equal to k.

Compute an array that stores the prefix sum of each element.
The sum of the elements in the subarray A[i : j] is prefixSum[j]-prefixSum[i-1].

Observation:
Suppose u < v and prefixSum[u] >= prefixSum[v], then u will never be the ending point of a solution.
The reason is that for any w <= u, A[w : v] is longer than A[w : u] and if A[w : u] satisfies the sum constraint, so must A[w : v].

Greedy w/ PrefixSums: O(n) time, O(n) space
BruteForce w/ prefixSum: O(n^2) time, O(n) space
BruteForce: O(n^3) time, O(1) space
see also LongestSubArrWEqualSum.h
*/
class LongestSubArrWLessEqualSum
{
public:
	LongestSubArrWLessEqualSum(){}
	~LongestSubArrWLessEqualSum(){}

	std::pair<int, int> Greedy_PrefixSums(const std::vector<int> & v, int sum)
	{
		int N = v.size();
		//1. compute the prefix sum array
		std::vector<int> prefixSum;
		std::partial_sum(v.cbegin(), v.cend(), std::back_inserter(prefixSum));

		std::pair<int, int> res(-1, -1);
		if (prefixSum.back() <= sum)
		{
			res = { 0, N - 1 };
		}
		else
		{
			//2. compute the min prefix sum array from right
			std::vector<int> minPrefixSum(N);
			minPrefixSum[N - 1] = prefixSum[N - 1];
			for (int i = N - 2; i >= 0; --i)
			{
				minPrefixSum[i] = std::min(prefixSum[i], minPrefixSum[i + 1]);
			}

			//3. greedy
			int left = 0;
			int right = 0;
			int maxLen = 0;
			while (left < N && right < N)
			{
				int curMinSum = left > 0 ? minPrefixSum[right] - prefixSum[left - 1] : minPrefixSum[right];
				if (curMinSum <= sum)//cur subarr sum is valid and can be increased more. since cur right point is the min prefix sum from right, advance right to increase subarr length and sum.
				{
					if (right - left + 1 > maxLen)
					{
						maxLen = right - left + 1;
						res = { left, right };
					}
					++right;
				}
				else//curMinSum > sum. cur subarr sum is too big. left point won't be valid for the remaining right points because cur right point is already the min prefix sum from right. advance left.
					++left;
			}

			//std::cout << "prefixSum:    " << Debug::ToStr1D<int>()(prefixSum) << std::endl;
			//std::cout << "minPrefixSum: " << Debug::ToStr1D<int>()(minPrefixSum) << std::endl;
		}

		std::string resStr = "N/A";
		if (res.first != -1 && res.second != -1)
		{
			resStr = Debug::ToStr1D<int>()(v, res.first, res.second);
			resStr += " (" + std::to_string(res.second - res.first + 1) + ")";
		}
		std::cout << "LongestSubArrWLessEqualSum Greedy_PrefixSums for \"" << sum << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": " << resStr << std::endl;
		return res;
	}

	std::pair<int, int> BruteForce_PrefixSums(const std::vector<int> & v, int sum)
	{
		int N = v.size();
		//1. compute the prefix sum array
		std::vector<int> prefixSum;
		std::partial_sum(v.cbegin(), v.cend(), std::back_inserter(prefixSum));

		std::pair<int, int> res(-1, -1);
		if (prefixSum.back() <= sum)
		{
			res = { 0, N - 1 };
		}
		else
		{
			//2. nested for loops to check sum of each subarray
			//, where subarray sum in [left,right] = prefixSum[right] - prefixSum[left-1]
			int maxLen = 0;
			for (int right = 0; right < N; ++right)
			{
				for (int left = 0; left <= right; ++left)
				{
					int curSum = left > 0 ? prefixSum[right] - prefixSum[left - 1] : prefixSum[right];
					if (curSum <= sum)
					{
						if (right - left + 1 > maxLen)
						{
							maxLen = right - left + 1;
							res = { left, right };
						}
					}
				}
			}
		}

		std::string resStr = "N/A";
		if (res.first != -1 && res.second != -1)
		{
			resStr = Debug::ToStr1D<int>()(v, res.first, res.second);
			resStr += " (" + std::to_string(res.second - res.first + 1) + ")";
		}
		std::cout << "LongestSubArrWLessEqualSum BruteForce_PrefixSums for \"" << sum << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": " << resStr << std::endl;
		return res;
	}
};
/*
LongestSubArrWLessEqualSum Greedy_PrefixSums for "184" from "431, -15, 639, 342, -14, 565, -924, 635, 167, -70": 342, -14, 565, -924 (4)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "184" from "431, -15, 639, 342, -14, 565, -924, 635, 167, -70": 342, -14, 565, -924 (4)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-1" from "0, -6, -15, 20, 17, 8, -6, -15, -11, -16": 0, -6, -15, 20, 17, 8, -6, -15, -11, -16 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-1" from "0, -6, -15, 20, 17, 8, -6, -15, -11, -16": 0, -6, -15, 20, 17, 8, -6, -15, -11, -16 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-21" from "-23, -7, -15, 30, -16, 11, 29, 23, 2, 0": -23, -7, -15, 30, -16 (5)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-21" from "-23, -7, -15, 30, -16, 11, 29, 23, 2, 0": -23, -7, -15, 30, -16 (5)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-14" from "-1, 16, -25, 4, -11, 27, -20, -29, 18, -18": -1, 16, -25, 4, -11, 27, -20, -29, 18, -18 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-14" from "-1, 16, -25, 4, -11, 27, -20, -29, 18, -18": -1, 16, -25, 4, -11, 27, -20, -29, 18, -18 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-29" from "7, -10, -3, -13, 2, 25, 15, -14, 14, -9": N/A
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-29" from "7, -10, -3, -13, 2, 25, 15, -14, 14, -9": N/A
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-14" from "6, 23, -14, 7, 5, -5, -2, 21, 29, -13": -14 (1)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-14" from "6, 23, -14, 7, 5, -5, -2, 21, 29, -13": -14 (1)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "7" from "-8, -11, -20, 14, 26, 6, 5, -4, 28, -2": -8, -11, -20, 14, 26, 6 (6)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "7" from "-8, -11, -20, 14, 26, 6, 5, -4, 28, -2": -8, -11, -20, 14, 26, 6 (6)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-19" from "7, -1, 19, -1, -22, -11, 12, -1, 20, -6": -1, -22, -11, 12, -1 (5)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-19" from "7, -1, 19, -1, -22, -11, 12, -1, 20, -6": -1, -22, -11, 12, -1 (5)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-1" from "-30, 18, 6, -26, 17, -18, 2, 18, 0, -27": -30, 18, 6, -26, 17, -18, 2, 18, 0, -27 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-1" from "-30, 18, 6, -26, 17, -18, 2, 18, 0, -27": -30, 18, 6, -26, 17, -18, 2, 18, 0, -27 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-15" from "-26, -18, -30, -10, 26, 20, 24, 18, -7, 15": -26, -18, -30, -10, 26, 20 (6)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-15" from "-26, -18, -30, -10, 26, 20, 24, 18, -7, 15": -26, -18, -30, -10, 26, 20 (6)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-28" from "-27, 6, 26, -24, 3, 21, 18, 1, -10, -30": 1, -10, -30 (3)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-28" from "-27, 6, 26, -24, 3, 21, 18, 1, -10, -30": 1, -10, -30 (3)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "10" from "-2, 22, 21, -15, 7, -3, 30, 26, -8, 16": 21, -15, 7, -3 (4)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "10" from "-2, 22, 21, -15, 7, -3, 30, 26, -8, 16": 21, -15, 7, -3 (4)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-11" from "-14, -8, -9, 24, -2, 23, 17, 1, -22, -9": 17, 1, -22, -9 (4)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-11" from "-14, -8, -9, 24, -2, 23, 17, 1, -22, -9": 17, 1, -22, -9 (4)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-11" from "28, -24, -3, -27, 9, 3, 29, -5, 28, 8": -24, -3, -27, 9, 3, 29, -5 (7)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-11" from "28, -24, -3, -27, 9, 3, 29, -5, 28, 8": -24, -3, -27, 9, 3, 29, -5 (7)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "8" from "-11, -15, -12, 3, -16, 1, -6, -27, 26, 23": -11, -15, -12, 3, -16, 1, -6, -27, 26, 23 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "8" from "-11, -15, -12, 3, -16, 1, -6, -27, 26, 23": -11, -15, -12, 3, -16, 1, -6, -27, 26, 23 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "5" from "3, -19, 25, 28, 8, -14, -5, -20, 9, 10": -19, 25, 28, 8, -14, -5, -20 (7)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "5" from "3, -19, 25, 28, 8, -14, -5, -20, 9, 10": -19, 25, 28, 8, -14, -5, -20 (7)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "10" from "-20, 26, 29, 24, 1, 28, 8, -15, 8, 18": 8, -15, 8 (3)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "10" from "-20, 26, 29, 24, 1, 28, 8, -15, 8, 18": 8, -15, 8 (3)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-26" from "3, -4, -23, 25, 14, -25, 6, -6, -20, -10": 3, -4, -23, 25, 14, -25, 6, -6, -20, -10 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-26" from "3, -4, -23, 25, 14, -25, 6, -6, -20, -10": 3, -4, -23, 25, 14, -25, 6, -6, -20, -10 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-14" from "-23, 11, -6, 8, -17, 17, -24, -26, 23, 20": -23, 11, -6, 8, -17, 17, -24, -26, 23, 20 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-14" from "-23, 11, -6, 8, -17, 17, -24, -26, 23, 20": -23, 11, -6, 8, -17, 17, -24, -26, 23, 20 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-17" from "-6, -29, 26, 6, -17, 10, -19, -9, -16, 25": -6, -29, 26, 6, -17, 10, -19, -9, -16, 25 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-17" from "-6, -29, 26, 6, -17, 10, -19, -9, -16, 25": -6, -29, 26, 6, -17, 10, -19, -9, -16, 25 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-24" from "25, 29, -18, -11, 28, 28, 19, 12, 1, 11": -18, -11 (2)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-24" from "25, 29, -18, -11, 28, 28, 19, 12, 1, 11": -18, -11 (2)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-21" from "-26, -14, 21, -3, 19, 14, -24, -14, -26, -30": -26, -14, 21, -3, 19, 14, -24, -14, -26, -30 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-21" from "-26, -14, 21, -3, 19, 14, -24, -14, -26, -30": -26, -14, 21, -3, 19, 14, -24, -14, -26, -30 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-5" from "22, 14, 22, -14, 6, 16, -16, -30, -21, 30": 14, 22, -14, 6, 16, -16, -30, -21 (8)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-5" from "22, 14, 22, -14, 6, 16, -16, -30, -21, 30": 14, 22, -14, 6, 16, -16, -30, -21 (8)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "2" from "25, -14, 28, 16, -3, -14, -28, 10, 21, 29": -14, 28, 16, -3, -14, -28, 10 (7)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "2" from "25, -14, 28, 16, -3, -14, -28, 10, 21, 29": -14, 28, 16, -3, -14, -28, 10 (7)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-12" from "0, -9, -26, -17, -28, -8, 11, 27, -7, -10": 0, -9, -26, -17, -28, -8, 11, 27, -7, -10 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-12" from "0, -9, -26, -17, -28, -8, 11, 27, -7, -10": 0, -9, -26, -17, -28, -8, 11, 27, -7, -10 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-17" from "3, -12, -26, 29, 12, -23, 14, 22, -21, 5": 3, -12, -26, 29, 12, -23 (6)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-17" from "3, -12, -26, 29, 12, -23, 14, 22, -21, 5": 3, -12, -26, 29, 12, -23 (6)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-6" from "20, -12, -22, -24, -16, 19, 30, 2, -28, -19": 20, -12, -22, -24, -16, 19, 30, 2, -28, -19 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-6" from "20, -12, -22, -24, -16, 19, 30, 2, -28, -19": 20, -12, -22, -24, -16, 19, 30, 2, -28, -19 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-11" from "-28, -23, -15, 20, -26, 8, -19, -24, 0, -30": -28, -23, -15, 20, -26, 8, -19, -24, 0, -30 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-11" from "-28, -23, -15, 20, -26, 8, -19, -24, 0, -30": -28, -23, -15, 20, -26, 8, -19, -24, 0, -30 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-16" from "-5, -20, -24, -6, -18, -3, 7, -11, 12, -8": -5, -20, -24, -6, -18, -3, 7, -11, 12, -8 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-16" from "-5, -20, -24, -6, -18, -3, 7, -11, 12, -8": -5, -20, -24, -6, -18, -3, 7, -11, 12, -8 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-12" from "28, -18, -3, -29, -11, -3, -7, 24, 5, -18": 28, -18, -3, -29, -11, -3, -7, 24, 5, -18 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-12" from "28, -18, -3, -29, -11, -3, -7, 24, 5, -18": 28, -18, -3, -29, -11, -3, -7, 24, 5, -18 (10)
LongestSubArrWLessEqualSum Greedy_PrefixSums for "-10" from "13, 8, 12, -25, 24, -16, -26, -13, 16, -26": 13, 8, 12, -25, 24, -16, -26, -13, 16, -26 (10)
LongestSubArrWLessEqualSum BruteForce_PrefixSums for "-10" from "13, 8, 12, -25, 24, -16, -26, -13, 16, -26": 13, 8, 12, -25, 24, -16, -26, -13, 16, -26 (10)
*/
#endif