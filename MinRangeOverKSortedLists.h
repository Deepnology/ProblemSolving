#ifndef MIN_RANGE_OVER_K_SORTED_LISTS_H
#define MIN_RANGE_OVER_K_SORTED_LISTS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>//std::greater
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Smallest Range
Elements of programming interview, BST: Compute the closest entries in three sorted arrays
Let A, B, and C be sorted arrays of integers.
Define distance(i,j,k) = max(|A[i]-B[j]|, |B[j]-C[k]|, |C[k]-A[i]|).
Design an algorithm that takes three sorted arrays A, B, and C and returns a triple (i,j,k) such that distance(i,j,k) is minimum.
Your algorithm should run in O(nA + nB + nC) time.

Google
http://www.careercup.com/question?id=16759664
You have K lists of sorted integers.
Find the smallest range that includes at least one number from each of the K lists.
For example,
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]
The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.

MinHeap or BST:
Keep track of K elements with one element from begin of each list.
Also keep track of max and min of the K elements (use heap or set).
The range would be max - min.
Keep removing the min element from heap or BST
, and inserting the next right element from the same list of the min element
, until reaches the end of any list.

O(n*k*logk) time, O(k) space, where n is the min size of the k sorted lists

See also KwayMergeSort.h, MinPairDiff2SortedArrays.h
*/
class MinRangeOverKSortedLists
{
public:
	MinRangeOverKSortedLists(){}
	~MinRangeOverKSortedLists(){}

	//1. Use MinHeap
	struct CompGreater
	{
		bool operator()(const std::pair<int, std::pair<int, int>> & a, const std::pair<int, std::pair<int, int>> & b) const
		{
			return a.first != b.first ? a.first > b.first : a.second.first != b.second.first ? a.second.first < b.second.first : a.second.second < b.second.second;
		}
	};
	int Solve_MinHeap(const std::vector<std::vector<int>> & lists)
	{
		int K = lists.size();
		int curRangeMax = INT_MIN;//keeps track of the max element of current K elements
		int minRange = INT_MAX;
		int minRangeMax;
		int minRangeMin;
		std::vector<int> res;
		std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, CompGreater> minHeap;
		//first: val, second.first: the list index that val belongs to, second.second: the val's index in that list
		//minHeap: keeps track of the smallest element of current K elements
		for (int i = 0; i < K; ++i)
		{
			minHeap.push({ lists[i][0], {i, 0} });
			if (lists[i][0] > curRangeMax)
				curRangeMax = lists[i][0];

			res.push_back(lists[i][0]);
		}
		minRange = curRangeMax - minHeap.top().first;
		minRangeMax = curRangeMax;
		minRangeMin = minHeap.top().first;
		//now minHeap has K elements
		while (true)
		{
			auto top = minHeap.top();
			minHeap.pop();
			if (++top.second.second < (int)lists[top.second.first].size())//get the next element from list that the smallest element belongs if available
			{
				int next = lists[top.second.first][top.second.second];
				if (next > curRangeMax)
					curRangeMax = next;
				minHeap.push({ next, {top.second.first, top.second.second} });
				if (curRangeMax - minHeap.top().first < minRange)
				{
					minRange = curRangeMax - minHeap.top().first;
					minRangeMax = curRangeMax;
					minRangeMin = minHeap.top().first;

					res.clear();
					std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, CompGreater> copy(minHeap);
					while (!copy.empty())
					{
						res.push_back(copy.top().first);
						copy.pop();
					}
				}
			}
			else
				break;
		}
		Debug::Print2D<int>()(lists, false);
		std::cout << "MinRangeOverKSortedLists MinHeap for the above lists: " << minRange << " = [" << minRangeMin << "," << minRangeMax << "] from [" << Debug::ToStr1D<int>()(res) << "]" << std::endl;
		return minRange;
	}

	//2. Use SortedSet
	struct CompLess
	{
		bool operator()(const std::pair<int, std::pair<int, int>> & a, const std::pair<int, std::pair<int, int>> & b) const
		{
			return a.first != b.first ? a.first < b.first : a.second.first != b.second.first ? a.second.first < b.second.first : a.second.second < b.second.second;
		}
	};
	int Solve_SortedSet(const std::vector<std::vector<int> > & lists)
	{
		int K = lists.size();
		int minPairDiff = INT_MAX;
		std::vector<int> res;
		std::set<std::pair<int, std::pair<int, int>>, CompLess> sorted;
		//first: val, second.first: the list index that val belongs to, second.second: the val's index in that list
		//sorted: keeps track of the smallest and largest element of current K elements
		for (int i = 0; i < K; ++i)
		{
			sorted.insert({ lists[i][0], {i, 0} });
			res.push_back(lists[i][0]);
		}
		minPairDiff = sorted.crbegin()->first - sorted.cbegin()->first;

		//now sorted has K elements
		while (true)
		{
			auto front = *sorted.begin();
			sorted.erase(sorted.begin());
			if (++front.second.second < (int)lists[front.second.first].size())//get the next element from list that the smallest element belongs if available
			{
				int next = lists[front.second.first][front.second.second];
				sorted.insert({ next, {front.second.first, front.second.second} });
				if (sorted.crbegin()->first - sorted.cbegin()->first < minPairDiff)
				{
					minPairDiff = sorted.crbegin()->first - sorted.cbegin()->first;

					res.clear();
					for (auto & p : sorted)
						res.push_back(p.first);
				}
			}
			else
				break;
		}
		Debug::Print2D<int>()(lists, false);
		std::cout << "MinRangeOverKSortedLists SortedSet for the above lists: " << minPairDiff << " from [" << Debug::ToStr1D<int>()(res) << "]" << std::endl;
		return minPairDiff;
	}
};
/*
[rY][cX]
Row#0	= 4, 10, 15, 24, 26
Row#1	= 0, 9, 12, 20,
Row#2	= 5, 18, 22, 30,

MinRangeOverKSortedLists MinHeap for the above lists: 4 = [20,24] from [20, 22, 24]
[rY][cX]
Row#0	= 4, 10, 15, 24, 26
Row#1	= 0, 9, 12, 20,
Row#2	= 5, 18, 22, 30,

MinRangeOverKSortedLists SortedSet for the above lists: 4 from [20, 22, 24]
[rY][cX]
Row#0	= 3, 5, 7, 8, 12, 26, 27, 31
Row#1	= 9, 10, 15, 22, 24, 28,  ,
Row#2	= 16, 17, 18, 21, 23,  ,  ,

MinRangeOverKSortedLists MinHeap for the above lists: 3 = [23,26] from [23, 24, 26]
[rY][cX]
Row#0	= 3, 5, 7, 8, 12, 26, 27, 31
Row#1	= 9, 10, 15, 22, 24, 28,  ,
Row#2	= 16, 17, 18, 21, 23,  ,  ,

MinRangeOverKSortedLists SortedSet for the above lists: 3 from [23, 24, 26]
[rY][cX]
Row#0	= 1, 2, 3, 80,
Row#1	= 1, 2, 3, 90, 200
Row#2	= 1, 2, 3, 99, 300

MinRangeOverKSortedLists MinHeap for the above lists: 0 = [1,1] from [1, 1, 1]
[rY][cX]
Row#0	= 1, 2, 3, 80,
Row#1	= 1, 2, 3, 90, 200
Row#2	= 1, 2, 3, 99, 300

MinRangeOverKSortedLists SortedSet for the above lists: 0 from [1, 1, 1]
[rY][cX]
Row#0	= 1, 10, 15, 24, 26
Row#1	= 0, 9, 12, 18,
Row#2	= 2, 18, 22, 30,

MinRangeOverKSortedLists MinHeap for the above lists: 2 = [0,2] from [1, 0, 2]
[rY][cX]
Row#0	= 1, 10, 15, 24, 26
Row#1	= 0, 9, 12, 18,
Row#2	= 2, 18, 22, 30,

MinRangeOverKSortedLists SortedSet for the above lists: 2 from [1, 0, 2]
*/
/*
Leetcode: Maximum Distance in Arrays
Given m arrays, and each array is sorted in ascending order.
Now you can pick up two integers from two different arrays (each array picks one) and calculate the distance.
We define the distance between two integers a and b to be their absolute difference |a-b|.
Your task is to find the maximum distance.
Example 1:
Input:
[[1,2,3],
[4,5],
[1,2,3]]
Output: 4
Explanation:
One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
*/
class MaxRangeOverKSortedLists
{
public:
	MaxRangeOverKSortedLists() {}
	~MaxRangeOverKSortedLists() {}

	int Greedy(std::vector<std::vector<int>> & v)
	{
		int K = v.size();

		int left = v[0].front();
		int right = v[0].back();
		int res = INT_MIN;
		for (int i = 1; i < K; ++i)
		{
			res = std::max(res, std::max(right - v[i].front(), v[i].back() - left));//avoid getting two nums from same array
			left = std::min(left, v[i].front());
			right = std::max(right, v[i].back());
		}

		return res;
	}
};
/*

*/
#endif