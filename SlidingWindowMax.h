#ifndef SLIDING_WINDOW_MAX_H
#define SLIDING_WINDOW_MAX_H
#include <vector>
#include <iostream>
#include <string>
#include <deque>
#include "Debug.h"
/*
Leetcode: Sliding Window Maximum

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window.
Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

SortedQueue: O(n) time, O(n) space
*/
class SlidingWindowMax
{
public:
	SlidingWindowMax() {}
	~SlidingWindowMax() {}

	std::vector<int> SortedQueue(const std::vector<int> & nums, int k)
	{
		std::vector<int> res;
		std::deque<std::pair<int, int>> sortedQue;//first: val in descending order, second: index

		int N = nums.size();
		for (int i = 0; i < N; ++i)
		{

			while (!sortedQue.empty() && sortedQue.back().first < nums[i])
			{
				sortedQue.pop_back();
			}

			sortedQue.push_back({ nums[i], i });

			if (i >= k - 1)
			{
				while (!sortedQue.empty() && i - sortedQue.front().second + 1 > k)
				{
					sortedQue.pop_front();
				}
				res.push_back(sortedQue.front().first);
			}
		}

		std::cout << "SlidingWindowMax SortedQueue for WinLen=\"" << k << "\", \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
SlidingWindowMax SortedQueue for WinLen="3", "1, 3, -1, -3, 5, 3, 6, 7": 3, 3, 5, 5, 6, 7
*/
#endif
