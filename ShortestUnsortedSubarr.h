#ifndef SHORTEST_UNSORTED_SUBARR_H
#define SHORTEST_UNSORTED_SUBARR_H
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
class ShortestUnsortedSubarr
{
public:
	ShortestUnsortedSubarr(){}
	~ShortestUnsortedSubarr(){}

	std::pair<int, int> Find(const std::vector<int> & A)
	{
		int N = A.size();
		
		//leftEnd: end of sorted subarray from begin
		int leftEnd = 0;
		while (leftEnd < N - 1 && A[leftEnd] <= A[leftEnd + 1])
			++leftEnd;

		if (leftEnd == N - 1)
		{
			std::cout << "ShortestUnsortedSubarr for \"" << Debug::ToStr1D<int>()(A) << "\": " << N << ", " << N << std::endl;
			return std::make_pair(N, N);
		}

		//rightBegin: begin of sorted subarray from end
		int rightBegin = N - 1;
		while (rightBegin > 0 && A[rightBegin - 1] <= A[rightBegin])
			--rightBegin;
		//now A[0]~A[leftEnd] and A[rightBegin]~A[N-1] are sorted

		int unsortedMin = A[leftEnd];//min value in A[leftEnd]~A[rightBegin]
		int unsortedMax = A[leftEnd];//max value in A[leftEnd]~A[rightBegin]
		for (int i = leftEnd + 1; i <= rightBegin; ++i)
		{
			if (A[i] > unsortedMax)
				unsortedMax = A[i];
			if (A[i] < unsortedMin)
				unsortedMin = A[i];
		}
		//std::cout << leftEnd << "," << rightBegin << "," << unsortedMax << "," << unsortedMin << std::endl;

		//shift leftEnd index to its left until A[i] <= unsortedMin
		int unsortedBegin = leftEnd;
		while (unsortedBegin > 0 && A[unsortedBegin - 1] > unsortedMin)
			--unsortedBegin;

		//shift rightBegin index to its right until A[i] >= unsortedMax
		int unsortedEnd = rightBegin;
		while (unsortedEnd < N - 1 && A[unsortedEnd + 1] < unsortedMax)
			++unsortedEnd;

		std::cout << "ShortestUnsortedSubarr for \"" << Debug::ToStr1D<int>()(A) << "\": " << unsortedBegin << ", " << unsortedEnd << std::endl;
		return std::make_pair(unsortedBegin, unsortedEnd);
	}
};
/*
ShortestUnsortedSubarr for "0, 1, 15, 25, 6, 7, 30, 40, 50": 2, 5
ShortestUnsortedSubarr for "1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19": 3, 9
ShortestUnsortedSubarr for "15, 17, 19, 8, 2, 30, 4, 24, 26, 29": 0, 9
*/
#endif