#ifndef SHORTEST_SUBARR_TO_SORT_TO_MAKE_ARR_SORTED_H
#define SHORTEST_SUBARR_TO_SORT_TO_MAKE_ARR_SORTED_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
Leetcode: Shortest Unsorted Continuous Subarray
Cracking the coding interview: Moderate
http://www.geeksforgeeks.org/minimum-length-unsorted-subarray-sorting-which-makes-the-complete-array-sorted/
Given an unsorted array arr[0...n-1] of size n.
Find the minimum length subarray arr[s...e] such that sorting this subarray makes the whole array sorted.

Key idea:
need to find the min and max in the non-ascending-range
, and shift non-ascending-range-begin to left until smaller equal to min
, and shift non-ascending-range-end to right until greater equal to max
*/
class ShortestSubarrToSortToMakeArrSorted
{
public:
	std::pair<int, int> Find(const std::vector<int> & A)
	{
        int N = A.size();

        //left: end of sorted subarray from begin inclusive
        int left = 0;
        while (left < N-1 && A[left] <= A[left+1])
            ++left;
        if (left == N-1) return {0,N-1};

        //right: begin of sorted subarray from end inclusive
        int right = N-1;
        while (right > 0 && A[right-1] <= A[right])
            --right;
        //now A[0:left] and A[right:N-1] are sorted

        int minVal = INT_MAX;//min value in A[left:right]
        int maxVal = INT_MIN;//max value in A[left:right]
        for (int i = left; i <= right; ++i)
        {
            maxVal = std::max(maxVal,A[i]);
            minVal = std::min(minVal,A[i]);
        }
        //std::cout << left << "," << right << "," << maxVal << "," << minVal << std::endl;

        //shift left to its left until A[left] <= minVal
        while (left > 0 && A[left-1] > minVal)
            --left;

        //shift right to its right until maxVal <= A[right]
        while (right < N-1 && maxVal > A[right+1])
            ++right;
        //std::cout << left << "," << right << std::endl;

        std::cout << "ShortestSubarrToSortToMakeArrSorted for \"" << Debug::ToStr1D<int>()(A) << "\": " << left << ", " << right << std::endl;
		return std::make_pair(left, right);
	}
};
/*
ShortestSubarrToSortToMakeArrSorted for "0, 1, 15, 25, 6, 7, 30, 40, 50": 2, 5
ShortestSubarrToSortToMakeArrSorted for "1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19": 3, 9
ShortestSubarrToSortToMakeArrSorted for "15, 17, 19, 8, 2, 30, 4, 24, 26, 29": 0, 9
*/
#endif