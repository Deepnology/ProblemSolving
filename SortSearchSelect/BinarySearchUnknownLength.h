#ifndef BINARY_SEARCH_UNKNOWN_LENGTH_H
#define BINARY_SEARCH_UNKNOWN_LENGTH_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Searching: Search a sorted array of unknown length
Let A be a sorted array.
The length of A is not known in advance; access A[i] for i beyond the end of the array throws an exception.
Design an algorithm that takes A and a key k and returns an index i such that A[i] = k; return -1 if k doesn't appear in A.

The key idea is to simultaneously do a binary search for the end of the array as well as the key.
We examine A[2^p-1] in the p-th step till we hit an exception or an entry greater than or equal to k.
Then we do a conventional binary search for k in the range [2^(p-1), 2^p-2].

O(logn) time

See also KthSmallestElementUnknownLength.h

Leetcode: Search in a Sorted Array of Unknown Size
Given an integer array sorted in ascending order, write a function to search target in nums.
If target exists, then return its index, otherwise return -1.
However, the array size is unknown to you.
You may only access the array using an ArrayReader interface, where ArrayReader.get(k) returns the element of the array at index k (0-indexed).
You may assume all integers in the array are less than 10000, and if you access the array out of bounds, ArrayReader.get will return 2147483647.
Example 1:
Input: array = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4
Example 2:
Input: array = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
*/
class BinarySearchUnknownLength
{
public:
	BinarySearchUnknownLength(){}
	~BinarySearchUnknownLength(){}

	int Iterate(const std::vector<int> & v, int target)
	{
		//find a power such that v[2^(power-1)] <= target < v[2^(power)-1]
		int power = 0;
		int idx = -1;
		while (true)
		{
			try
			{
				int val = v.at((1 << power) - 1);//check every value at v[2^power-1]
				if (val == target)
				{
					idx = (1 << power) - 1;
					break;
				}
				else if (val > target)
				{
					break;
				}
			}
			catch (const std::exception &)
			{
				break;
			}
			++power;
		}

		if (idx == -1)
		{
			/*
			Now power has been determined, the target value's idx: 2^(power-1) <= idx < 2^power-1.
			Binary search between indices 2^(power-1) and 2^power-2, inclusive.
			*/
			int left = std::max(0, 1 << (power - 1));//power might be 0
			int right = (1 << power) - 2;//right might be out of boundary
			while (left <= right)//keep 1 entry between [left,right] inclusive
			{
				int mid = left + (right - left) / 2;//mid might be out of boundary
				try
				{
					int val = v.at(mid);
					if (val == target)
					{
						idx = mid;
						break;
					}
					else if (val > target)
						right = mid - 1;
					else
						left = mid + 1;
				}
				catch (const std::exception &)
				{
					right = mid - 1;//search the left part if mid is out of boundary
				}
			}
		}

		std::cout << "BinarySearchUnknownLength Iterate for \"" << target << "\" in \"" << Debug::ToStr1D<int>()(v) << "\": " << idx << std::endl;
		return idx;
	}

	struct ArrayReader
	{
		int get(int idx) const
		{
			return 0;
		}
	};
	int BinarySearch(const ArrayReader & reader, int target)
	{
		int right = 1;
		while (reader.get(right) < target)
			right <<= 1;
		int left = right >> 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (reader.get(mid) > target)
				right = mid - 1;
			else if (reader.get(mid) < target)
				left = mid + 1;
			else
				return mid;
		}
		return -1;
	}
};
/*
BinarySearchUnknownLength Iterate for "78" in "3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 78, 78, 81": 15
*/
#endif