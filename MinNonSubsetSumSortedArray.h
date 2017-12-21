#ifndef MIN_NON_SUBSET_SUM_SORTED_ARRAY_H
#define MIN_NON_SUBSET_SUM_SORTED_ARRAY_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Compute the Smallest Nonconstructible Change
Write a function which takes an array A of positive integer and returns the smallest k such that k is not equal to the sum of a subset of elements of A.
Need to sort it in the first place.

http://www.geeksforgeeks.org/find-smallest-value-represented-sum-subset-given-array/
Given a sorted array (in non-decreasing order) of positive integers.
Find the smallest positive integer value that cannot be represented as sum of elements of any subset of given set.

Solution:
Compute the prefix sum by accumulating the elements in sorted A from the smallest until meeting an element that is greater than the prefix sum plus one.
The answer will be the prefix sum plus one.

O(n) time, O(1) space

see also PatchingArray.h
*/
class MinNonSubsetSumSortedArray
{
public:
	MinNonSubsetSumSortedArray(){}
	~MinNonSubsetSumSortedArray(){}

	int Find(const std::vector<int> & v)
	{
		int N = v.size();
		int res = 1;
		for (int i = 0; i < N && v[i] <= res; ++i)
			res += v[i];

		std::cout << "MinNonSubsetSumSortedArray for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}

	int Find2(const std::vector<int> & v)
	{
		int N = v.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			if (v[i] > res + 1)
				break;
			res += v[i];
		}
		res += 1;

		std::cout << "MinNonSubsetSumSortedArray for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
};
/*
MinNonSubsetSumSortedArray for "1, 1, 3, 4": 10
MinNonSubsetSumSortedArray for "1, 1, 3, 4": 10
MinNonSubsetSumSortedArray for "1, 2, 5, 10": 4
MinNonSubsetSumSortedArray for "1, 2, 5, 10": 4
*/
#endif