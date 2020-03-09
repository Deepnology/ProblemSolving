#ifndef SORT_K_INCR_DECR_ARRAY_H
#define SORT_K_INCR_DECR_ARRAY_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>//std::greater
#include <algorithm>
#include "Debug.h"
#include "../SortSearchSelect/KwayMergeSort.h"
/*
Elements of programming interview, Heaps: Sort a k-increasing-decreasing array
An array A of n integers is said to be k-increasing-decreasing if elements repeatedly increase up to a certain index after which they decrease
, then again increase, a total of k times.

A 4-increasing-decreasing array:
57, 131, 493, 294, 221, 339, 418, 452, 442, 190
----------|---------|--------------|-----------
  1-incr    2-decr      3-incr         4-decr

Design an efficient algorithm for sorting a k-increasing-decreasing array.
You are given another array of the same size that the result should be written to, and you can use O(k) additional storage.

The first thing to note is that any array can be decomposed into a sequence of increasing and decreasing subarrays.
If k is comparable to n, then the problem is equivalent to the general sorting problem.
If k is substantially smaller than n, we could first reverse the order of the decreasing subarrays.
Now we can use the KwayMergeSort technique to sort the array in O(nlogk) time and O(k) space.

See also KwayMergeSort.h
*/
class SortKIncrDecrArray
{
public:
	SortKIncrDecrArray(){}
	~SortKIncrDecrArray(){}

	std::vector<int> UseKwayMergeSort(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::vector<int> > subarrs;
		bool isIncr = true;//initial value deosn't affect the final result
		//it only affects whether the first element is put in a subarr alone or is put together with other elements in a subarr

		//1. build k subarrays
		int begin = 0;
		for (int i = 1; i < N; ++i)
		{
			if ((v[i - 1] < v[i] && !isIncr) || //v[i-1] is end of current decr subarr, and v[i] is begin of next incr subarr
				(v[i - 1] >= v[i] && isIncr))//v[i-1] is end of current incr subarr, and v[i] is begin of next decr subarr
			{
				if (isIncr)
					subarrs.emplace_back(v.cbegin() + begin, v.cbegin() + i);//create a subarr [begin, begin+i)
				else
					subarrs.emplace_back(v.crbegin() + N - i, v.crbegin() + N - begin);//create a subarr [begin, begin+i) in reverse order

				begin = i;
				isIncr = !isIncr;
			}
		}
		if (begin < N)
		{
			if (isIncr)
				subarrs.emplace_back(v.cbegin() + begin, v.cend());//create a subarr [begin, v.end())
			else
				subarrs.emplace_back(v.crbegin(), v.crbegin() + N - begin);//create a subarr [begin, v.end()) in reverse order
		}

		std::cout << "SortKIncrDecrArray UseKwayMergeSort for \"" << Debug::ToStr1D<int>()(v) << "\":" << std::endl;

		//2. apply k way merge sort
		std::vector<int> res = KwayMergeSort().Solve_MinHeap(subarrs);
		return res;
	}
};
/*
SortKIncrDecrArray UseKwayMergeSort for "57, 131, 493, 294, 221, 339, 418, 452, 442, 190":
[rY][cX]
Row#0	= 57, 131, 493
Row#1	= 221, 294,
Row#2	= 339, 418, 452
Row#3	= 190, 442,

KwayMergeSort for the above lists: 57, 131, 190, 221, 294, 339, 418, 442, 452, 493
SortKIncrDecrArray UseKwayMergeSort for "2, 3, 4, 6, 8, 7, 7, 5, 4, 1, 0, 11, 13, 17, 18, 16, 14, 12, 10, 19":
[rY][cX]
Row#0	= 2, 3, 4, 6, 8,
Row#1	= 0, 1, 4, 5, 7, 7
Row#2	= 11, 13, 17, 18,  ,
Row#3	= 10, 12, 14, 16,  ,
Row#4	= 19,  ,  ,  ,  ,

KwayMergeSort for the above lists: 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 10, 11, 12, 13, 14, 16, 17, 18, 19
*/
#endif