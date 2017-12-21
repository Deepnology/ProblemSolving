#ifndef _KTH_SMALLEST_PAIR_SUM_2_SORTED_ARRAYS_H
#define _KTH_SMALLEST_PAIR_SUM_2_SORTED_ARRAYS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Find K Pairs with Smallest Sums
http://www.careercup.com/question?id=6335704
http://www.careercup.com/question?id=6332981908078592
http://www.careercup.com/question?id=6335704
Given 2 sorted array of numbers, a and b, with size of N and M where N > M.
Find Kth smallest pair sum a[i]+b[j].
This problem is equivalent to find the Kth smallest element in a sorted matrix (sorted rows and columns).
See also KthSmallestElementInSortedMatrix.h

1.
MinHeap and keep track of pairs' indicies in minHeap: O(K*logK) time, O(K) space
http://stackoverflow.com/questions/18557175/how-to-find-pair-with-kth-largest-sum
When you pop the current min, push its two larger neighbors to the minHeap, if they weren't processed already (need to mark the element that has been processed).
Count for K times.

2.
Selection in X + Y and matrices with sorted rows and columns: O(n) time
http://stackoverflow.com/questions/18557175/how-to-find-pair-with-kth-largest-sum

3.
http://stackoverflow.com/questions/19028613/kth-smallest-element-in-a-matrix-with-sorted-rows-and-columns
http://pastebin.com/kASWRHdA
The Frederickson and Johnson algorithm: O(n) time
*/
class KthSmallestPairSum2SortedArrays
{
public:
	KthSmallestPairSum2SortedArrays(){}
	~KthSmallestPairSum2SortedArrays(){}
	
	std::vector<std::pair<int, int>> MinHeap(const std::vector<int> & a, const std::vector<int> & b, int K)
	{
		int N = a.size();
		int M = b.size();
		std::vector<std::pair<int, int>> res;
		if (N == 0 || M == 0 || K <= 0)
			return res;
		if (K > N * M)
			K = N * M;

		std::priority_queue<std::pair<int, std::pair<int, int>> , std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> minHeap;
		//first: sum, second.first: aIdx, second.second: bIdx
		minHeap.push({ a[0] + b[0], { 0,0 } });

		std::unordered_set<int> pairsInHeap;//keep track of pairs' indicies in minHeap
		//hash value for pair(index1,index2): index1 * N + index2 (since N is the max number for both index1 and index2)
		pairsInHeap.insert(0 * N + 0);//(0, 0)

		for (int i = 0; i < K; ++i)//extract min from minHeap for K times, O(K*logK) time
		{
			auto curMin = minHeap.top();
			minHeap.pop();
			pairsInHeap.erase(curMin.second.first * N + curMin.second.second);

			res.push_back({ a[curMin.second.first], b[curMin.second.second] });

			if (curMin.second.first + 1 < N &&
				pairsInHeap.count((curMin.second.first + 1) * N + curMin.second.second) == 0)
			{
				minHeap.push({ a[curMin.second.first + 1] + b[curMin.second.second], { curMin.second.first + 1, curMin.second.second } });
				pairsInHeap.insert((curMin.second.first + 1) * N + curMin.second.second);
			}

			if (curMin.second.second + 1 < M &&
				pairsInHeap.count(curMin.second.first * N + (curMin.second.second + 1)) == 0)
			{
				minHeap.push({ a[curMin.second.first] + b[curMin.second.second + 1], { curMin.second.first, curMin.second.second + 1 } });
				pairsInHeap.insert(curMin.second.first * N + (curMin.second.second + 1));
			}
		}

		std::cout << Debug::ToStr1D<int>()(a) << std::endl;
		std::cout << Debug::ToStr1D<int>()(b) << std::endl;
		std::cout << "KthSmallestPairSum2SortedArrays MinHeap for above 2 arrays, K=\"" << K << "-th\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
2, 3, 5, 8, 13
4, 8, 12, 16
KthSmallestPairSum2SortedArrays MinHeap for above 2 arrays, K="20-th": [2,4], [3,4], [5,4], [2,8], [3,8], [8,4], [5,8], [2,12], [3,12], [8,8], [5,12], [13,4], [2,16], [3,16], [8,12], [5,16], [13,8], [8,16], [13,12], [13,16]
1, 7, 11
2, 4, 6
KthSmallestPairSum2SortedArrays MinHeap for above 2 arrays, K="3-th": [1,2], [1,4], [1,6]
1, 1, 2
1, 2, 3
KthSmallestPairSum2SortedArrays MinHeap for above 2 arrays, K="2-th": [1,1], [1,1]
1, 2
3
KthSmallestPairSum2SortedArrays MinHeap for above 2 arrays, K="2-th": [1,3], [2,3]
*/
#endif