#ifndef MULTI_DUP_IN_IDX_SEQ_ARRAY_H
#define MULTI_DUP_IN_IDX_SEQ_ARRAY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Leetcode: find all duplicates in an array
http://www.geeksforgeeks.org/find-duplicates-in-on-time-and-constant-extra-space/
Given an array of size n.
All elements of the array are in range 0~(n-1), with any of these numbers appearing any number of times.
Find all the duplicates.

Leetcode: find all numbers disappeared in an array
Given an array of integers where 1 <= a[i] <= n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[5,6]

1. MarkNegative: O(n) time, O(1) space

2. BruteForce: O(n^2) time, O(1) space
enumerate all possible pairs in the array
std::vector<int> res;
for (i = 0; i < N; ++i)
	for (j = i; j < N; ++j)
		if (A[i] == A[j])
			res.push_back(A[i]);
return res;

3. CountArray: O(n) time, O(n) space
std::vector<int> countArray(N, 0);
for (i = 0; i < N; ++i)
	++countArray[A[i]];
for (i = 0; i < N; ++i)
	if (countArray[i])
		res.push_back(i);
return res;
*/
class MultiDupInIdxSeqArray
{
public:
	MultiDupInIdxSeqArray(){}
	~MultiDupInIdxSeqArray(){}

	std::vector<int> FindAllDup_MarkNegative(std::vector<int> A)//A is in [0:n-1]
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		std::vector<int> res;

		for (int i = 0; i < N; ++i)
		{
			if (A[std::abs(A[i])] >= 0)//first visit
				A[std::abs(A[i])] = -A[std::abs(A[i])];
			else//negative means non-first visit
				res.push_back(std::abs(A[i]));
		}

		std::cout << "MultiDupInIdxSeqArray FindAllDup_MarkNegative for \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindAllMissing_MarkNegative(std::vector<int> A)//A is in [1:n]
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		std::vector<int> res;

		for (int i = 0; i < N; ++i)
		{
			if (A[std::abs(A[i]) - 1] > 0)//first visit
				A[std::abs(A[i]) - 1] = -A[std::abs(A[i]) - 1];
		}
		for (int i = 0; i < N; ++i)
		{
			if (A[i] > 0)//positive means its idx was never visited
				res.push_back(i + 1);
		}

		std::cout << "MultiDupInIdxSeqArray FindAllMissing_MarkNegative for \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
MultiDupInIdxSeqArray FindAllDup_MarkNegative for "1, 2, 3, 1, 3, 6, 6": 1, 3, 6
MultiDupInIdxSeqArray FindAllMissing_MarkNegative for "4, 3, 2, 7, 8, 2, 3, 1": 5, 6
*/
#endif