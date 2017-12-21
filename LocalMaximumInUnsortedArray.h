#ifndef LOCAL_MAXIMUM_IN_UNSORTED_ARRAY_H
#define LOCAL_MAXIMUM_IN_UNSORTED_ARRAY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
/*
Leetcode: Find peak element
http://siddontang.gitbooks.io/leetcode-solution/content/array/find_peak_element.html
A peak element is an element that is greater than its neighbors.
Given an input array where "num[i] != num[i+1]", find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that "num[-1] = num[n] = INT_MIN".
For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

BinarySearch: O(logn) time, O(1) space
*/
class LocalMaximumInUnsortedArray
{
public:
	LocalMaximumInUnsortedArray(){}
	~LocalMaximumInUnsortedArray(){}

	int Strickly_Iterate(const std::vector<int> & v)
	{
		int N = v.size();
		if (N == 1)
			return 0;
		if (N == 2)
			return v[0] > v[1] ? 0 : 1;

		int left = 0;
		int right = N - 1;
		int res = -1;
		while (right - left > 1)//keep 3 entries in between [left,right] inclusive
		{
			int mid = left + (right - left) / 2;

			if (v[mid] > v[mid - 1] && v[mid] > v[mid + 1])
			{
				res = mid;
				break;
			}
			else if (v[mid] > v[mid - 1])//since we want to find local max, abandon left side which contain a smaller element
				left = mid;
			else
				right = mid;
		}
		if (res == -1)
		{
			res = v[left] > v[right] ? left : right;
		}

		std::cout << "LocalMaximumInUnsortedArray Strickly_Iterate for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}

	int Strickly_Recur(const std::vector<int> & v)
	{
		int res = this->index_Strickly_Recur(v, 0, v.size() - 1);
		std::cout << "LocalMaximumInUnsortedArray Strickly_Recur for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
private:
	int index_Strickly_Recur(const std::vector<int> & v, int left, int right)
	{
		if (right - left <= 1)//less than 3 entries between [left,right] inclusive
			return v[left] > v[right] ? left : right;
		int N = v.size();
		int mid = (left + right) / 2;

		if (v[mid] > v[mid - 1] && v[mid] > v[mid + 1])
			return mid;

		if (v[mid] > v[mid - 1])//since we want to find local max, abandon left side which contain a smaller element
			return this->index_Strickly_Recur(v, mid, right);
		else
			return this->index_Strickly_Recur(v, left, mid);
	}
};
/*
LocalMaximumInUnsortedArray Strickly_Iterate for "6, 5, 1, 4, 5, 7, 10, 1, 9, 1, 5, 7, 4, 8, 7, 10, 4, 10, 9, 9": 6
*/
#endif