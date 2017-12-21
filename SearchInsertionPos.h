#ifndef SEARCH_INSERTION_POS_H
#define SEARCH_INSERTION_POS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
https://github.com/anson627/leetcode/blob/master/SearchInsertPosition/SearchInsertPosition.cpp
// Given a sorted array and a target value, return the index if the target is
// found. If not, return the index where it would be if it were inserted in order.
//
// You may assume no duplicates in the array.
//
// Here are few examples.
// [1,3,5,6], 5 -> 2
// [1,3,5,6], 2 -> 1
// [1,3,5,6], 7 -> 4
// [1,3,5,6], 0 -> 0
//
// Complexity
// log(n) time (binary search, lower/upper bound)
*/
class SearchInsertionPos
{
public:
	SearchInsertionPos(){}
	~SearchInsertionPos(){}
	/*
	Normal lower bound:
	Returns an index of the first element in the range [first,last) which does not compare less than val (can compare both equal to or greater than val).
	Normal upper bound:
	Returns an index of the first element in the range [first,last) which compares ONLY greater than val.
	So we can do a lower bound to search the insertion position.
	*/
	int LowerBound(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size() - 1;
		while (left <= right)//keep 1 entry between [left,right] inclusive
		{
			int middle = (left + right) / 2;
			if (A[middle] >= val)
				right = middle - 1;
			else
				left = middle + 1;
		}
		//now left is the lower bound of val

		std::cout << "SearchInsertionPos for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\" is: " << left << std::endl;
		return left;
	}

};
/*
SearchInsertionPos for "7" in "3, 4, 5, 5, 5, 6, 7, 7, 7, 8, 8" is: 6
*/
#endif