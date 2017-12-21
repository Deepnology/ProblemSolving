#ifndef K_CLOSEST_ELEMENTS_IN_SORTED_ARR_H
#define K_CLOSEST_ELEMENTS_IN_SORTED_ARR_H
#include "Debug.h"
/*
Leetcode: Find K Closest Elements
Given a sorted array, two integers k and x, find the k closest elements to x in the array.
The result should also be sorted in ascending order.
If there is a tie, the smaller elements are always preferred.
Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]
Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]
Note:
The value k is positive and will always be smaller than the length of the sorted array.
Length of the given array is positive and will not exceed 10^4
Absolute value of elements in the array and x will not exceed 10^4
*/
class KClosestElementsInSortedArr
{
public:
	KClosestElementsInSortedArr() {}

	std::vector<int> BinarySearchLeftBoundary(std::vector<int> & arr, int k, int x)
	{
		int N = arr.size();
		int left = 0;
		int right = N - k - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (x - arr[mid] <= arr[mid + k] - x)//right too big: search left (when equal, search left)
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is lower bound
		return std::vector<int>({ arr.begin() + left, arr.begin() + left + k });
	}
};
#endif
