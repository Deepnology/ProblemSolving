#ifndef MIN_PAIR_DIFF_2_SORTED_ARRAYS_H
#define MIN_PAIR_DIFF_2_SORTED_ARRAYS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include "Debug.h"
/*
Amazon
https://sites.google.com/site/spaceofjameschen/annnocements/findminimumabsolutedifferencebtweentwonumbersin2arrays--amazon
Given 2 sorted arrays of integer.
Find a pair of integers, one from each array, such that the absolute difference between the 2 integers is minimum.

1. Modified Merge 2 Sorted Arrays
(Same for merging 2 sorted arrays with each element has an array label, then find the min diff between any two consecutive elements with different array labels)
O(m+n) time
See also TwoDifference.h, TwoClosestPoints.h

2. Modified Binary Search
O(nlogm) time
*/
class MinPairDiff2SortedArrays
{
public:
	MinPairDiff2SortedArrays(){}
	~MinPairDiff2SortedArrays(){}

	//1.1 Modified Merge 2 Sorted Arrays: O(m+n) time
	int ModifiedMerge2SortedArrays(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();
		int i = 0;
		int j = 0;
		int minDiff = INT_MAX;
		int n1;
		int n2;
		while (i < M && j < N)
		{
			if (std::abs(v1[i] - v2[j]) < minDiff)
			{
				minDiff = std::abs(v1[i] - v2[j]);
				n1 = v1[i];
				n2 = v2[j];
			}
			if (v1[i] == v2[j])
				break;
			else if (v1[i] < v2[j])
				++i;
			else
				++j;
		}
		std::cout << "MinPairDiff2SortedArrays ModifiedMerge2SortedArrays for \"" << Debug::ToStr1D<int>()(v1) << "\", and \"" << Debug::ToStr1D<int>()(v2) << "\": " << minDiff << ", [" << n1 << "," << n2 << "]" << std::endl;
		return minDiff;
	}

	//1.2 Modified Merge 2 Sorted Arrays: O(m+n) time
	int ModifiedMerge2SortedArrays2(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();
		int i = 0;
		int j = 0;
		int prevNum = 0;
		int prevArr = -1;
		int minDiff = INT_MAX;
		while (i < M && j < N)
		{
			if (v1[i] < v2[j])
			{
				if (prevArr == 2)
				{
					//std::cout << prevNum << "," << v1[i] << std::endl;
					int curDiff = std::abs(v1[i] - prevNum);
					if (curDiff < minDiff)
						minDiff = curDiff;
				}
				prevArr = 1;
				prevNum = v1[i];
				++i;
			}
			else
			{
				if (prevArr == 1)
				{
					//std::cout << prevNum << "," << v2[j] << std::endl;
					int curDiff = std::abs(v2[j] - prevNum);
					if (curDiff < minDiff)
						minDiff = curDiff;
				}
				prevArr = 2;
				prevNum = v2[j];
				++j;
			}
		}
		//now either v1 or v2 has been used up
		
		if (i < M)
		{
			if (prevArr == 2)
			{
				//std::cout << prevNum << "," << v1[i] << std::endl;
				int curDiff = std::abs(v1[i] - prevNum);//compare v1[i] with v2[N-1]
				if (curDiff < minDiff)
					minDiff = curDiff;
			}
			prevArr = 1;
			prevNum = v1[i];
			++i;
		}
		if (j < N)
		{
			if (prevArr == 1)
			{
				//std::cout << prevNum << "," << v2[j] << std::endl;
				int curDiff = std::abs(v2[j] - prevNum);//compare v2[j] with v1[M-1]
				if (curDiff < minDiff)
					minDiff = curDiff;
			}
			prevArr = 2;
			prevNum = v2[j];
			++j;
		}

		std::cout << "MinPairDiff2SortedArrays ModifiedMerge2SortedArrays2 for \"" << Debug::ToStr1D<int>()(v1) << "\", and \"" << Debug::ToStr1D<int>()(v2) << "\": " << minDiff << std::endl;
		return minDiff;
	}

	//2. Modified Binary Search: O(nlogm) time
	int ModifiedBinarySearch(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int N = v1.size();
		int M = v2.size();
		int minDiff = INT_MAX;
		//for each element in v1, binary search the closest element in v2, and keep track of the min diff
		for (int i = 0; i < N; ++i)
		{
			int curDiff;
			if (v1[i] <= v2[0])//out of range
				curDiff = v2[0] - v1[i];
			else if (v1[i] >= v2[M - 1])//out of range
				curDiff = v1[i] - v2[M - 1];
			else
				curDiff = std::abs(v1[i] - v2[this->modifiedBinarySearch(v2, v1[i])]);
			if (curDiff < minDiff)
				minDiff = curDiff;
		}
		std::cout << "MinPairDiff2SortedArrays ModifiedBinarySearch for \"" << Debug::ToStr1D<int>()(v1) << "\", and \"" << Debug::ToStr1D<int>()(v2) << "\": " << minDiff << std::endl;
		return minDiff;
	}
private:
	/*
	Modified Binary Search:
	if val found in array, return the corresponding index
	if val not found, return the CLOSEST INDEX of its floor val and ceil val
	*/
	int modifiedBinarySearch(const std::vector<int> & A, int val)
	{
		int left = 0;
		int right = A.size();
		while (right - left > 1)//keep 3 entries between [left,right] inclusive
		{
			int middle = left + (right - left) / 2;
			if (A[middle] <= val)
				left = middle;
			else
				right = middle;
		}
		//now right is the upper bound of val (the index of the leftmost element that compares greater than val)

		if (A[left] == val)//val found, left points to the last duplicate
		{
			return left;
		}
		else//val not found, [left,right] will be the [floor,ceil] index
		{
			if (std::abs(val - A[left]) <= std::abs(val - A[right]))
				return left;
			else
				return right;
		}
	}
};
/*
MinPairDiff2SortedArrays ModifiedMerge2SortedArrays for "-5, 7, 14, 23, 29, 38, 45, 54, 67, 78, 117", and "3, 18, 32, 40, 50, 62, 88, 97": 2, [38,40]
MinPairDiff2SortedArrays ModifiedMerge2SortedArrays2 for "-5, 7, 14, 23, 29, 38, 45, 54, 67, 78, 117", and "3, 18, 32, 40, 50, 62, 88, 97": 2
MinPairDiff2SortedArrays ModifiedBinarySearch for "-5, 7, 14, 23, 29, 38, 45, 54, 67, 78, 117", and "3, 18, 32, 40, 50, 62, 88, 97": 2
*/
#endif