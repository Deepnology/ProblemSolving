#ifndef K_WAY_MERGE_SORT_H
#define K_WAY_MERGE_SORT_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>//std::greater
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Heaps: Merge sorted files
http://www.geeksforgeeks.org/merge-k-sorted-arrays/
http://www.careercup.com/question?id=22355666
http://stackoverflow.com/questions/11026219/why-is-k-way-merge-onk2

Given k sorted arrays with each size of n.
Merge the k sorted arrays.

1. use the merge routine: merge the first 2 arrays, then merge the 3rd array with the output of the merged first two arrays
, then merge the 4th array with the output of the merged first 3 arrays, and so on.
O(n*k^2) time
Complexity Analysis:
The first merge takes 2n, the second takes 3n, the third 4n...
We are given a summation of 2n + 3n + 4n + 5n + 6n +...+ kn = n * (2 + 3 + 4 + ... + k)
which is equal to n * (k * (k+1)/2 - 1)
which means O(n*k^2) time

2. Use MinHeap: O(n*k*logk) time, O(k) space
We need to go through n*k elements where each element involves an insertion of MinHeap with size K, which takes O(logk) time

see also MinRangeOverKSortedLists.h
*/
class KwayMergeSort
{
public:
	KwayMergeSort(){}
	~KwayMergeSort(){}

	struct CompGreater
	{
		bool operator()(const std::pair<int, std::pair<int, int> > & a, const std::pair<int, std::pair<int, int> > & b)
		{
			return a.first > b.first;
		}
	};

	std::vector<int> Solve_MinHeap(const std::vector<std::vector<int> > & lists)
	{
		int K = lists.size();//K sorted arrays
		std::vector<int> res;

		//first: val, second.first: the list index that val belongs to, second.second: the val's index in that list
		std::priority_queue<std::pair<int, std::pair<int, int> >, std::vector<std::pair<int, std::pair<int, int> > >, CompGreater> minHeap;
		//minHeap: keeps track of the smallest element of current K elements

		//init minHeap with the 1st element of each array
		for (int i = 0; i < K; ++i)
		{
			minHeap.push(std::make_pair(lists[i][0], std::make_pair(i, 0)));
		}

		while (!minHeap.empty())
		{
			auto top = minHeap.top();
			minHeap.pop();
			res.push_back(top.first);
			++top.second.second;
			if (top.second.second < (int)lists[top.second.first].size())
			{
				top.first = lists[top.second.first][top.second.second];
				minHeap.push(top);
			}
		}

		Debug::Print2D<int>()(lists, false);
		std::cout << "KwayMergeSort for the above lists: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 4, 10, 15, 24, 26
Row#1	= 0, 9, 12, 20, 32
Row#2	= 5, 18, 22, 30, 42

KwayMergeSort for the above lists: 0, 4, 5, 9, 10, 12, 15, 18, 20, 22, 24, 26, 30, 32, 42
[rY][cX]
Row#0	= 3, 5, 7, 8, 12, 26, 27, 31
Row#1	= 9, 10, 15, 22, 24, 28, 34, 43
Row#2	= 16, 17, 18, 21, 23, 32, 38, 47

KwayMergeSort for the above lists: 3, 5, 7, 8, 9, 10, 12, 15, 16, 17, 18, 21, 22, 23, 24, 26, 27, 28, 31, 32, 34, 38, 43, 47
[rY][cX]
Row#0	= 1, 2, 3, 80, 88
Row#1	= 1, 2, 3, 90, 200
Row#2	= 1, 2, 3, 99, 300

KwayMergeSort for the above lists: 1, 1, 1, 2, 2, 2, 3, 3, 3, 80, 88, 90, 99, 200, 300
[rY][cX]
Row#0	= 1, 10, 15, 24, 26
Row#1	= 0, 9, 12, 18, 31
Row#2	= 2, 18, 22, 30, 41

KwayMergeSort for the above lists: 0, 1, 2, 9, 10, 12, 15, 18, 18, 22, 24, 26, 30, 31, 41
*/
#endif