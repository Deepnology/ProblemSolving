#ifndef SEARCH_IN_ROTATED_SORTED_ARRAY_H
#define SEARCH_IN_ROTATED_SORTED_ARRAY_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a cyclically sorted array
Design an O(logn) algorithm for finding the position of the smallest element in a cyclically sorted array.
Variant: Design an O(logn) algorithm for finding the position of an element k in a cyclically sorted array.
1.1
https://github.com/anson627/leetcode/blob/master/SearchinRotatedSortedArray/SearchinRotatedSortedArray.cpp
// Search in Rotated Sorted Array
// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
//
// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
//
// You are given a target value to search. If found in the array return its
// index, otherwise return -1.
//
// You may assume no duplicate exists in the array.
//
// Complexity
// O(log(n)) time

1.2
https://github.com/anson627/leetcode/blob/master/SearchinRotatedSortedArrayII/SearchinRotatedSortedArrayII.cpp
// Follow up for "Search in Rotated Sorted Array":
// What if duplicates are allowed?
//
// Would this affect the run-time complexity? How and why?
//
// Write a function to determine if a given target is in the array.
//
// Complexity:
// Worse case O(n) time

2.1 Leetcode: Find minimum in rotated sorted array, where the array doesn't have duplicate
http://tech-wonderland.net/blog/leetcode-find-minimum-in-rotated-sorted-array-binary-search-tricky-boundary-issue.html
O(log(n)) time
2.2 Leetcode: Find minimum in rotated sorted array, where the array might have duplicates
http://tech-wonderland.net/blog/leetcode-find-minimum-in-rotated-sorted-array-ii-worst-case-analysis.html
O(log(n)) time, O(n) time in worst case

See also BinarySearchFixedPoint.h
*/
class SearchInRotatedSortedArray
{
public:
	SearchInRotatedSortedArray(){}
	~SearchInRotatedSortedArray(){}

	//1. Find target: keep 1 entry between [left,right] inclusive
	//1.1 NoDup Iterate
	int Index_NoDup_Iterate(const std::vector<int> & A, int target)
	{
		int left = 0;
		int right = A.size() - 1;
		int res = -1;
		while (left <= right)
		{
			int middle = (left + right) / 2;//for even: left of mid pair (this is why comparing v[mid] with v[right])
			//std::cout << left << "," << right << " -> " << middle << std::endl;
			if (A[middle] == target)
			{
				res = middle;
				break;
			}
			else if (A[middle] > A[right])//left side is in non-descending order, head/tail pair is on the right side
			{
				if (A[left] <= target && target < A[middle])
					right = middle - 1;
				else
					left = middle + 1;
			}
			else//A[middle] < A[right], right side is in non-descending order, head/tail pair is on the left side
			{
				if (A[middle] < target && target <= A[right])
					left = middle + 1;
				else
					right = middle - 1;
			}
		}

		std::cout << "SearchInRotatedSortedArray Index_NoDup_Iterate for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}

	//1.2.a AllowDup Iterate
	int Index_AllowDup_Iterate(const std::vector<int> & A, int target)
	{
		int left = 0;
		int right = A.size() - 1;
		int res = -1;
		while (left <= right)
		{
			int middle = (left + right) / 2;
			//std::cout << left << "," << right << " -> " << middle << std::endl;
			if (A[middle] == target)
			{
				res = middle;
				break;
			}
			else if (A[middle] > A[right])//left side is in non-descending order, head/tail pair is on the right side
			{
				if (A[left] <= target && target < A[middle])
					right = middle - 1;
				else
					left = middle + 1;
			}
			else if (A[middle] < A[right])//right side is in non-descending order, head/tail pair is on the left side
			{
				if (A[middle] < target && target <= A[right])
					left = middle + 1;
				else
					right = middle - 1;
			}
			else//can't tell which side is in non-descending order
			{
				if (A[middle] == A[left])
					++left;
				if (A[middle] == A[right])
					--right;
			}
		}

		std::cout << "SearchInRotatedSortedArray Index_AllowDup_Iterate for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << res << std::endl;
		return res;
	}

	//1.2.b AllowDup Recur
	int Index_AllowDup_Recur(const std::vector<int> & v, int target)
	{
		int res = this->index_AllowDup_Recur(v, target, 0, v.size() - 1);
		std::cout << "SearchInRotatedSortedArray Index_AllowDup_Recur for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	int index_AllowDup_Recur(const std::vector<int> & v, const int & target, int left, int right)
	{
		if (left > right)
			return -1;
		if (left == right)
		{
			if (v[left] == target)
				return left;
			else
				return -1;
		}

		//now left < right

		int middle = (left + right) / 2;
		if (v[middle] == target)
			return middle;
		if (v[middle] > v[right])//left side is in non-descending order, head/tail pair is on the right side
		{
			if (v[left] <= target && target < v[middle])
				return this->index_AllowDup_Recur(v, target, left, middle - 1);
			else
				return this->index_AllowDup_Recur(v, target, middle + 1, right);
		}
		else if (v[middle] < v[right])//right side is in non-descending order, head/tail pair is on the left side
		{
			if (v[middle] < target && target <= v[right])
				return this->index_AllowDup_Recur(v, target, middle + 1, right);
			else
				return this->index_AllowDup_Recur(v, target, left, middle - 1);
		}
		else//can't tell which side is in non-descending order
		{
			if (v[middle] == v[left])
				++left;
			if (v[middle] == v[right])
				--right;
			return this->index_AllowDup_Recur(v, target, left, right);
		}
	}

public:
	//2. Find min: keep 3 entries between [left,right] inclusive
	//2.1 NoDup Iterate
	int Min_NoDup_Iterate(const std::vector<int> & v)
	{
		int left = 0;
		int right = v.size() - 1;
		int head = -1;

		while (left < right - 1)//keep 3 entries between [left,right] inclusive
		{
			if (v[left] < v[right])//base condition: current range doesn't have head/tail pair
			{
				head = left;
				break;
			}

			int mid = (left + right) / 2;
			if (v[mid] > v[right])//head/tail pair is in the right side
				left = mid;
			else//head/tail pair is in the left side
				right = mid;
		}

		if (head == -1)
		{
			if (left == right)
				head = left;
			else if (left == right - 1)
				head = v[left] < v[right] ? left : right;
		}

		std::cout << "SearchInRotatedSortedArray Min_NoDup_Iterate for \"" << Debug::ToStr1D<int>()(v) << "\": " << head << std::endl;
		return head;
	}

public:
	//2.2.a AllowDup Iterate
	int Min_AllowDup_Iterate(const std::vector<int> & v)
	{
		int left = 0;
		int right = v.size() - 1;
		int head = -1;

		while (left < right - 1)//keep 3 entries between [left,right] inclusive
		{
			if (v[left] < v[right])//base condition: current range doesn't have head/tail pair
			{
				head = left;
				break;
			}

			int mid = (left + right) / 2;
			if (v[mid] > v[right])//head/tail pair is in the right side
				left = mid;
			else if (v[mid] < v[right])//head/tail pair is in the left side
				right = mid;
			else//v[mid]==v[right], can't tell head/tail pair is in the left or right side
			{
				--right;
				if (v[mid] == v[left])
					++left;
			}
		}

		if (head == -1)
		{
			if (left == right)
				head = left;
			else if (left == right - 1)
				head = v[left] < v[right] ? left : right;
		}

		std::cout << "SearchInRotatedSortedArray Min_AllowDup_Iterate for \"" << Debug::ToStr1D<int>()(v) << "\": " << head << std::endl;
		return head;
	}

public:
	//2.2.b AllowDup Recur
	int Min_AllowDup_Recur(const std::vector<int> & v)
	{
		int head = this->min_AllowDup_Recur(v, 0, v.size() - 1);
		std::cout << "SearchInRotatedSortedArray Min_AllowDup_Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << head << std::endl;
		return head;
	}
private:
	int min_AllowDup_Recur(const std::vector<int> & v, int left, int right)
	{
		if (left == right)//base condition: only one element in the range
			return left;
		if (left == right - 1)//condition1: found head/tail pair
			return v[left] < v[right] ? left : right;
		if (v[left] < v[right])//condition2: current range doesn't have head/tail pair
			return left;

		//now left < right - 1

		int middle = (left + right) / 2;
		if (v[middle] > v[right])//head/tail pair must be in the right side
			return this->min_AllowDup_Recur(v, middle, right);
		else if (v[middle] < v[right])//head/tail pair must be in the left side
			return this->min_AllowDup_Recur(v, left, middle);
		else//v[middle] == v[right], we can't tell head/tail pair is in right side or left side
		{
			--right;
			if (v[middle] == v[left])
				++left;
			
			return this->min_AllowDup_Recur(v, left, right);
		}
	}
};
/*
SearchInRotatedSortedArray Index_NoDup_Iterate for "0" in "4, 5, 6, 7, 0, 1, 2": 4
SearchInRotatedSortedArray Index_NoDup_Iterate for "1" in "4, 5, 6, 7, 0, 1, 2": 5
SearchInRotatedSortedArray Index_NoDup_Iterate for "2" in "4, 5, 6, 7, 0, 1, 2": 6
SearchInRotatedSortedArray Index_NoDup_Iterate for "3" in "4, 5, 6, 7, 0, 1, 2": -1
SearchInRotatedSortedArray Index_NoDup_Iterate for "4" in "4, 5, 6, 7, 0, 1, 2": 0
SearchInRotatedSortedArray Index_NoDup_Iterate for "5" in "4, 5, 6, 7, 0, 1, 2": 1
SearchInRotatedSortedArray Index_NoDup_Iterate for "6" in "4, 5, 6, 7, 0, 1, 2": 2
SearchInRotatedSortedArray Index_NoDup_Iterate for "7" in "4, 5, 6, 7, 0, 1, 2": 3
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "4, 5, 6, 7, 0, 1, 2": 5
SearchInRotatedSortedArray Index_AllowDup_Iterate for "5" in "1, 1, 5, 0, 0, 1, 1": 2
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "1, 1, 5, 0, 0, 1, 1": 5
SearchInRotatedSortedArray Index_AllowDup_Iterate for "0" in "1, 1, 5, 0, 0, 1, 1": 3
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "1, 1, 5, 1, 1, 1, 1": 3
SearchInRotatedSortedArray Index_AllowDup_Iterate for "5" in "1, 1, 5, 1, 1, 1, 1": 2
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "1, 1, 1, 1, 1, 1, 1": 3
SearchInRotatedSortedArray Index_AllowDup_Iterate for "3" in "67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81, 3, 67": 15
SearchInRotatedSortedArray Index_AllowDup_Iterate for "67" in "67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81, 3, 67": 8
SearchInRotatedSortedArray Index_AllowDup_Iterate for "78" in "67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81, 3, 67": 12
SearchInRotatedSortedArray Index_AllowDup_Iterate for "79" in "67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 69, 78, 78, 78, 81, 3, 67": -1
SearchInRotatedSortedArray Index_AllowDup_Iterate for "3" in "67, 69, 78, 78, 78, 81, 3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67": 6
SearchInRotatedSortedArray Index_AllowDup_Iterate for "67" in "67, 69, 78, 78, 78, 81, 3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67": 8
SearchInRotatedSortedArray Index_AllowDup_Iterate for "78" in "67, 69, 78, 78, 78, 81, 3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67": 3
SearchInRotatedSortedArray Index_AllowDup_Iterate for "79" in "67, 69, 78, 78, 78, 81, 3, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67": -1
SearchInRotatedSortedArray Index_AllowDup_Iterate for "62" in "62, 64, 67, 69, 78, 78, 78, 81, 3, 5, 24, 27, 34, 41, 45, 58, 61": 0
SearchInRotatedSortedArray Index_AllowDup_Iterate for "61" in "62, 64, 67, 69, 78, 78, 78, 81, 3, 5, 24, 27, 34, 41, 45, 58, 61": 16
SearchInRotatedSortedArray Index_AllowDup_Iterate for "78" in "62, 64, 67, 69, 78, 78, 78, 81, 3, 5, 24, 27, 34, 41, 45, 58, 61": 5
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2": 11
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "2, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2": 11
SearchInRotatedSortedArray Index_AllowDup_Iterate for "2" in "2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2": 13
SearchInRotatedSortedArray Index_AllowDup_Iterate for "0" in "1, 1, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0": 11
SearchInRotatedSortedArray Index_AllowDup_Iterate for "3" in "1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 1": -1
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1": 11
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1": 13
SearchInRotatedSortedArray Index_AllowDup_Iterate for "0" in "2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2": 7
SearchInRotatedSortedArray Index_AllowDup_Iterate for "1" in "2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1": 7
SearchInRotatedSortedArray Index_AllowDup_Iterate for "3" in "1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1": -1
SearchInRotatedSortedArray Min_NoDup_Iterate for "4, 5, 6, 7, 0, 1, 2": 4
SearchInRotatedSortedArray Min_AllowDup_Iterate for "1, 1, 5, 0, 0, 0, 1": 3
SearchInRotatedSortedArray Min_AllowDup_Iterate for "1, 1, 5, 1, 1, 1, 1": 3
SearchInRotatedSortedArray Min_AllowDup_Iterate for "1, 1, 1, 1, 1, 1, 1": 3
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2": 1
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2": 4
SearchInRotatedSortedArray Min_AllowDup_Iterate for "1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1": 6
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2": 1
SearchInRotatedSortedArray Min_AllowDup_Iterate for "1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 1, 1": 7
SearchInRotatedSortedArray Min_AllowDup_Iterate for "0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2": 0
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2": 1
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2": 4
SearchInRotatedSortedArray Min_AllowDup_Iterate for "0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 0, 0, 0": 12
SearchInRotatedSortedArray Min_AllowDup_Iterate for "2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1": 5
*/
#endif