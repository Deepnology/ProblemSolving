#ifndef CLOSEST_SUB_ARRAY_SUM_H
#define CLOSEST_SUB_ARRAY_SUM_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
I. Find a subarray whose sum is closest to 0.
(Note: subarray sum is equal to prefixSum[right]-prefixSum[left-1])

SortedPrefixSums_Greedy
1. prepare (prefix sum, index) pair array
2. sort it by prefix sum in ascending order
3. compare all individual prefix sums and adjacent pairs
(bc adjacent pairs in the sorted prefixSum array have smallest abs difference)
O(nlogn) time, O(n) space


II. Find a subarray whose sum is closest to k.
(Note: subarray sum is equal to prefixSum[right]-prefixSum[left-1])

SortedPrefixSums_Greedy 
1. prepare (prefix sum, index) pair array
2. sort it by prefix sum in ascending order
3. use two pointers to first and second, get min(abs(prefixSum[first].first), abs(prefixSum[second].first), abs(prefixSum[first].first-prefixSum[second].first)), compare it to k, if equal, break, else if greater, advance first ptr, else, advance second ptr
(see also TwoDifference.h)
O(nlogn) time

BruteForce
1. prepare (prefix sum, index) pair array
2. enumerate and compare all individual prefix sums and every two entries in the (prefix sum, index) pair array
O(n^2) time, O(n) space


BruteForce (enumerate all subarrays and sum up all elements in each subarray): O(n^3) time, O(1) space

see also RangeSumCount.h, MaxSubMatrixSumNoGreaterThanK.h (SortedPrefixSums)
*/
class ClosestSubArraySum
{
public:
	ClosestSubArraySum(){}
	~ClosestSubArraySum(){}

	int Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr(const std::vector<int> & v)
	{
		int N = v.size();
		/*1. prepare (prefix sum, index) pair array*/
		std::vector<std::pair<int, int> > prefixSum(N);//first: value, second: index
		prefixSum[0].first = v[0];
		prefixSum[0].second = 0;
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i].first = prefixSum[i - 1].first + v[i];
			prefixSum[i].second = i;
		}

		/*2. sort by prefix sum in ascending order*/
		std::sort(prefixSum.begin(), prefixSum.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.first < b.first;
		});

		int absMinSum = INT_MAX;
		int left;
		int right;
		for (int i = 0; i < N; ++i)
		{
			/*3.1 compare individual prefix sum starting from begin of array*/
			if (std::abs(prefixSum[i].first) < absMinSum)
			{
				absMinSum = std::abs(prefixSum[i].first);
				left = 0;
				right = prefixSum[i].second;
			}
			/*3.2 compare adjacent pairs*/
			if (i < N - 1 && std::abs(prefixSum[i + 1].first - prefixSum[i].first) < absMinSum)
			{
				absMinSum = std::abs(prefixSum[i + 1].first - prefixSum[i].first);
				left = (prefixSum[i + 1].second < prefixSum[i].second ? prefixSum[i + 1].second : prefixSum[i].second) + 1;
				right = prefixSum[i + 1].second > prefixSum[i].second ? prefixSum[i + 1].second : prefixSum[i].second;
			}
		}

		std::cout << Debug::ToStr1D<int>()(prefixSum) << std::endl;
		std::cout << "ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for \"" << Debug::ToStr1D<int>()(v) << "\": " << absMinSum << ", [" << Debug::ToStr1D<int>()(v, left, right) << "]" << std::endl;
		return absMinSum;
	}

	int K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy(const std::vector<int> & v, int k)
	{
		int N = v.size();
		/*1. prepare (prefix sum, index) pair array*/
		std::vector<std::pair<int, int> > prefixSum(N);//first: value, second: index
		prefixSum[0].first = v[0];
		prefixSum[0].second = 0;
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i].first = prefixSum[i - 1].first + v[i];
			prefixSum[i].second = i;
		}

		/*2. sort by prefix sum in ascending order*/
		std::sort(prefixSum.begin(), prefixSum.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.first < b.first;
		});

		/*3. Greedy find closest 2 diff*/
		int absMinDist = INT_MAX;
		int left = 0;
		int right = 1;
		int resLeft;
		int resRight;
		while (right < N)
		{
			int absDiff = std::min(std::abs(prefixSum[left].first), std::min(std::abs(prefixSum[right].first), std::abs(prefixSum[left].first - prefixSum[right].first)));
			if (absDiff < absMinDist)
			{
				absMinDist = absDiff;

				//get resLeft and resRight ...
				if (std::abs(prefixSum[left].first) < std::abs(prefixSum[right].first) && std::abs(prefixSum[left].first) < std::abs(prefixSum[left].first - prefixSum[right].first))
				{ resLeft = 0; resRight = prefixSum[left].second; }
				else if (std::abs(prefixSum[right].first) < std::abs(prefixSum[left].first) && std::abs(prefixSum[right].first) < std::abs(prefixSum[left].first - prefixSum[right].first))
				{ resLeft = 0; resRight = prefixSum[right].second; }
				else
				{ resLeft = (prefixSum[left].second < prefixSum[right].second ? prefixSum[left].second : prefixSum[right].second) + 1; resRight = prefixSum[left].second < prefixSum[right].second ? prefixSum[right].second : prefixSum[left].second; }
			}
			if (absDiff == k)
			{
				break;
			}
			else if (absDiff > k)
			{
				++left;
				if (left == right)
					++right;
			}
			else
				++right;
		}

		std::cout << Debug::ToStr1D<int>()(prefixSum) << std::endl;
		std::cout << "ClosestSubArraySum K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy for \"" << k << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << absMinDist << ", [" << Debug::ToStr1D<int>()(v, resLeft, resRight) << "]" << std::endl;
		return absMinDist;
	}
	int K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce(const std::vector<int> & v, int k)
	{
		int N = v.size();
		/*1. prepare (prefix sum, index) pair array*/
		std::vector<std::pair<int, int> > prefixSum(N);//first: value, second: index
		prefixSum[0].first = v[0];
		prefixSum[0].second = 0;
		for (int i = 1; i < N; ++i)
		{
			prefixSum[i].first = prefixSum[i - 1].first + v[i];
			prefixSum[i].second = i;
		}

		/*2. enumerate and compare every two entries in the prefix sum array*/
		int absMinDist = INT_MAX;
		int left;
		int right;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i; j < N; ++j)
			{
				if (i == j)
				{
					if (std::abs(prefixSum[i].first - k) < absMinDist)
					{
						absMinDist = std::abs(prefixSum[i].first - k);
						left = 0;
						right = prefixSum[i].second;
					}
				}
				else
				{
					if (std::abs((prefixSum[j].first - prefixSum[i].first) - k) < absMinDist)
					{
						absMinDist = std::abs(prefixSum[j].first - prefixSum[i].first - k);
						left = i + 1;
						right = j;
					}
				}
			}
		}

		std::cout << Debug::ToStr1D<int>()(prefixSum) << std::endl;
		std::cout << "ClosestSubArraySum K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce for \"" << k << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << absMinDist << ", [" << Debug::ToStr1D<int>()(v, left, right) << "]" << std::endl;
		return absMinDist;
	}
};
/*
[4,4], [5,1], [7,2], [8,0], [8,3], [9,6], [14,5]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "8, -3, 2, 1, -4, 10, -5": 0, [-3, 2, 1]
[-11,4], [-3,0], [-3,3], [-1,1], [-1,5], [3,2], [10,6]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "-3, 2, 4, -6, -8, 10, 11": 0, [2, 4, -6]
[8,1], [10,0], [15,2]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "10, -2, 7": 2, [-2]
[-7,2], [0,4], [1,0], [3,3], [8,1]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "1, 7, -15, 10, -3": 0, [1, 7, -15, 10, -3]
[-7,2], [-2,4], [1,0], [3,3], [8,1]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "1, 7, -15, 10, -5": 1, [1]
[-1,2], [3,0], [7,4], [9,3], [14,1]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "3, 11, -15, 10, -2": 1, [3, 11, -15]
[-9,2], [-5,4], [-3,3], [3,0], [10,1]
ClosestSubArraySum Zero_MinAbsDiffOfAdjPairs_SortedPrefixSumArr for "3, 7, -19, 6, -2": 2, [-2]
[-7,2], [0,4], [1,0], [3,3], [8,1]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy for "0" in "1, 7, -15, 10, -3": 0, [1, 7, -15, 10, -3]
[-7,2], [-2,4], [1,0], [3,3], [8,1]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy for "0" in "1, 7, -15, 10, -5": 1, [1]
[-1,2], [3,0], [7,4], [9,3], [14,1]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy for "0" in "3, 11, -15, 10, -2": 1, [3, 11, -15]
[-9,2], [-5,4], [-3,3], [3,0], [10,1]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_SortedPrefixSumArr_Greedy for "0" in "3, 7, -19, 6, -2": 2, [-2]
[1,0], [8,1], [-7,2], [3,3], [0,4]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce for "0" in "1, 7, -15, 10, -3": 0, [1, 7, -15, 10, -3]
[1,0], [8,1], [-7,2], [3,3], [-2,4]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce for "0" in "1, 7, -15, 10, -5": 1, [1]
[3,0], [14,1], [-1,2], [9,3], [7,4]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce for "0" in "3, 11, -15, 10, -2": 1, [3, 11, -15]
[3,0], [10,1], [-9,2], [-3,3], [-5,4]
ClosestSubArraySum K_MinAbsDiffOfAllPairs_PrefixSumArr_BruteForce for "0" in "3, 7, -19, 6, -2": 2, [-2]
*/
#endif