#ifndef SEARCH_FOR_RANGE_H
#define SEARCH_FOR_RANGE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/count-number-of-occurrences-in-a-sorted-array/
https://github.com/anson627/leetcode/blob/master/SearchforaRange/SearchforaRange.cpp
// Given a sorted array of integers, find the starting and ending position of
// a given target value.
//
// Your algorithm's runtime complexity must be in the order of O(log n).
//
// If the target is not found in the array, return [-1, -1].
//
// For example,
// Given [5, 7, 7, 8, 8, 10] and target value 8,
// return [3, 4].

1.
template <class ForwardIterator, class T>
ForwardIterator std::lower_bound(ForwardIterator first, ForwardIterator last, const T& val);

Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
The elements in the range shall already be sorted according to this same criterion (operator<), or at least partitioned with respect to val.
The function optimizes the number of comparisons performed by comparing non-consecutive elements of the sorted range, which is specially efficient for random-access iterators.
Unlike upper_bound, the value pointed by the iterator returned by this function may also be equivalent to val, and not only greater.

2.
template <class ForwardIterator, class T>
ForwardIterator std::upper_bound(ForwardIterator first, ForwardIterator last, const T& val);

Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
The elements in the range shall already be sorted according to this same criterion (operator<), or at least partitioned with respect to val.
The function optimizes the number of comparisons performed by comparing non-consecutive elements of the sorted range, which is specially efficient for random-access iterators.
Unlike lower_bound, the value pointed by the iterator returned by this function cannot be equivalent to val, only greater.
*/
class SearchForRange
{
public:
	SearchForRange(){}
	~SearchForRange(){}


	std::vector<int> LowerBoundUpperBound_STL(const std::vector<int> & nums, int target)
	{
		auto lb = std::lower_bound(nums.begin(), nums.end(), target);
		std::vector<int> res(2, -1);
		if (lb != nums.end() && *lb == target)//found at least one target
		{
			res[0] = lb - nums.begin();//first target index: lower bound
			auto ub = std::upper_bound(nums.begin(), nums.end(), target);
			res[1] = (--ub) - nums.begin();//last target index: upper bound - 1
		}

		std::cout << "SearchForRange LowerBoundUpperBound_STL for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(nums) << "\": " << res[0] << ", " << res[1] << std::endl;
		return res;
	}


};
/*
SearchForRange LowerBoundUpperBound_STL for "7" in "3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 8": 6, 8
*/
#endif