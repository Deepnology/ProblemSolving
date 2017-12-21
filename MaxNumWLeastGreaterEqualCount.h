/*MUST*/
#ifndef MAX_NUM_W_LEAST_GREATER_EQUAL_COUNT_H
#define MAX_NUM_W_LEAST_GREATER_EQUAL_COUNT_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5094709806497792
Given an unsorted array of integers with size of N.
Find the maximum possible integer n from the array such that the array consists at least n values greater than or equal to n.
=> n is in between 0 to N, inclusive
=> n is actually an index of the array

QuickSelect: O(n) time, O(1) space
1. find mid of current range as pivot
2. move all greater elements than pivotVal to the left side (partition)
3. if greater equal elements' count >= pivotVal (pivot+1 >= pivotVal): res = max(res, pivotVal), next search left side
4. otherwise, next search right side

Sort: O(nlogn) time, O(1) space
1. sort input array in ascending order
2. iterate from the back, the 1st one valid element will be the max one
3. valid only if greater equal elements' count >= element (N-idx >= v[idx])

See also KthSmallestElement.h, HIndex.h
*/
class MaxNumWLeastGreaterEqualCount
{
public:
	MaxNumWLeastGreaterEqualCount(){}
	~MaxNumWLeastGreaterEqualCount(){}

	int QuickSelect(std::vector<int> v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		int res = -1;
		int lo = 0;
		int hi = N - 1;
		while (lo <= hi)
		{
			int mid = lo + (hi - lo) / 2;

			/*
			partition the array in the range [lo, hi] to move greater elements to left side
			also make sure the first element of the second group is the greatest element of the second group
			*/
			/*
			method 1. use std::partition
			*/
			int pivotVal = v[mid];
			int pivot = std::partition(v.begin() + lo, v.begin() + hi + 1, 
				[&](const int & a)
			{
				return a > pivotVal;//descending order, so that "idx+1" is the count of self and left side elements (greater equal elements' count)
			}) - v.begin();
			for (int i = pivot; i <= hi; ++i)
				if (!(v[pivot] > v[i]))
					std::swap(v[pivot], v[i]);

			/*
			method 2. use std::nth_element
			*/
			//std::nth_element(v.begin() + lo, v.begin() + mid, v.begin() + hi + 1,
			//	[](const int & a, const int & b)
			//{
			//	return a > b;//descending order
			//});
			//int pivot = mid;

			//now first group: v[lo]~v[pivot-1] >= v[pivot], and second group: v[pivot] > v[pivot]~v[hi]

			if (pivot + 1 >= v[pivot])//greater equal count >= v[i]
			{
				res = std::max(res, v[pivot]);
				hi = pivot - 1;
			}
			else
				lo = pivot + 1;
		}
		//std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		std::cout << "MaxNumWLeastGreaterEqualCount QuickSelect for \"" << before << "\": " << res << std::endl;
		return res;
	}
	int Sort(std::vector<int> v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::sort(v.begin(), v.end()
			, [](const int & a, const int & b)
		{
			return a < b;//ascending order, so that "N-idx" is the count of self and right side elements (greater equal elements' count)
		});
		//std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		int res = -1;
		for (int i = N - 1; i >= 0; --i)//from back: the 1st valid one will be the max one
			if (N - i >= v[i])//greater equal count >= v[i]
			{
				res = v[i];
				break;
			}

		std::cout << "MaxNumWLeastGreaterEqualCount Sort for \"" << before << "\": " << res << std::endl;
		return res;
	}

};
/*
MaxNumWLeastGreaterEqualCount QuickSelect for "1, 2, 3, 4": 2
MaxNumWLeastGreaterEqualCount QuickSelect for "900, 2, 901, 3, 1000": 3
MaxNumWLeastGreaterEqualCount QuickSelect for "900, 902, 901, 903, 1000": -1
MaxNumWLeastGreaterEqualCount Sort for "1, 2, 3, 4": 2
MaxNumWLeastGreaterEqualCount Sort for "900, 2, 901, 3, 1000": 3
MaxNumWLeastGreaterEqualCount Sort for "900, 902, 901, 903, 1000": -1
MaxNumWLeastGreaterEqualCount QuickSelect for "9, 5, 8, 1, 18, 15, 2, 4, 12, 9": 5
MaxNumWLeastGreaterEqualCount Sort for "9, 5, 8, 1, 18, 15, 2, 4, 12, 9": 5
*/
#endif