#ifndef SORT_NEARLY_SORTED_ARRAY_H
#define SORT_NEARLY_SORTED_ARRAY_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>//std::greater
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Heaps: Sort an almost-sorted array
http://www.geeksforgeeks.org/nearly-sorted-algorithm/
AKA sort K sorted array
Given an array of n elements, where each element is at most K away from its target position.
Sort the nearly sorted array.

The strategy is to always keep K+1 numbers in a minHeap.
As soon as we read a new number, we extract the min from the heap and write the output and then insert the new number.

MinHeap: O(nlogk) time, O(k) space.
InsertionSort: O(nk) time
*/
class SortNearlySortedArray
{
public:
	SortNearlySortedArray(){}
	~SortNearlySortedArray(){}

	void Solve_MinHeap(std::vector<int> && A, int K)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();
		std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;

		//1. init the minHeap with the first K+1 elements
		for (int i = 0; i <= K && i < N; ++i)
			minHeap.push(A[i]);

		//2. create the new array from begin
		for (int i = 0, j = K + 1; i < N; ++i, ++j)
		{
			A[i] = minHeap.top();
			minHeap.pop();

			if (j < N)
				minHeap.push(A[j]);
		}

		std::cout << "SortNearlySortedArray for \"" << K << "-away\" in \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}

	void Solve_InsertionSort(std::vector<int> && A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		int N = A.size();

		for (int i = 1; i < N; ++i)
		{
			//insert A[i] into a sorted range [0,i-1] by right shifting all greater elements
			//the inner loop will run at most K times
			int tmp = A[i];
			int j;
			for (j = i; j > 0 && A[j - 1] > tmp; --j)
				A[j] = A[j - 1];
			A[j] = tmp;
		}

		std::cout << "SortNearlySortedArray InsertionSort for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
};
/*
SortNearlySortedArray for "3-away" in "2, 6, 3, 12, 56, 8": 2, 3, 6, 8, 12, 56
SortNearlySortedArray InsertionSort for "2, 6, 3, 12, 56, 8": 2, 3, 6, 8, 12, 56
*/
#endif