#ifndef SUB_ARR_W_LESS_EQUAL_MIN_MAX_DIFF_H
#define SUB_ARR_W_LESS_EQUAL_MIN_MAX_DIFF_H
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5090693043191808
Given an unsorted integer array.
Find all subarrays that the difference between the maximum value and the minimum value in the subarray is <= K.

Slide Window with 2 max/min sorted queues: O(n) time

See also QueueWithMin.h, AllStockSpans.h, MaxBandwidthOverWindowTimeInterval.h
*/
class SubArrWLessEqualMinMaxDiff
{
public:
	SubArrWLessEqualMinMaxDiff(){}
	~SubArrWLessEqualMinMaxDiff(){}

	//std::vector<std::pair<int, int>> SlideWindow_Better(const std::vector<int> & v, int K)
	//{
	//	int N = v.size();
	//	std::vector<std::pair<int, int>> res;//first: left index, second: right index
	//	std::list<std::pair<int, int>> sortedQueMin;//first: value, second: index
	//	std::list<std::pair<int, int>> sortedQueMax;//first: value, second: index
	//	/*
	//	sortedQueMin: ascending order of some elements in window with their relative orders (sorted queue)
	//	sortedQueMax: descending order of some elements in window with their relative orders (sorted queue)
	//	*/
	//	
	//	int left = 0;
	//	for (int right = 0; right < N; ++right)
	//	{
	//		while (!sortedQueMax.empty() && sortedQueMax.back().first <= v[right])
	//			sortedQueMax.pop_back();
	//		sortedQueMax.push_back({ v[right],right });

	//		while (!sortedQueMin.empty() && sortedQueMin.back().first >= v[right])
	//			sortedQueMin.pop_back();
	//		sortedQueMin.push_back({ v[right], right });



	//		/*expand the window right as rightmost as possible, as long as it is valid (max-min <= K)*/
	//		while (right < N)
	//		{
	//			while (!sortedQueMax.empty() && sortedQueMax.back().first <= v[right])
	//				sortedQueMax.pop_back();
	//			sortedQueMax.push_back({ v[right], right });

	//			while (!sortedQueMin.empty() && sortedQueMin.back().first >= v[right])
	//				sortedQueMin.pop_back();
	//			sortedQueMin.push_back({ v[right], right });

	//			if (sortedQueMax.front().first - sortedQueMin.front().first > K)
	//				break;
	//			++right;
	//		}

	//		/*now [left,right) is a longest valid window for index at left*/
	//		for (int i = left; i < right; ++i)
	//			res.push_back({ left, i });

	//		/*drop left before advancing*/
	//		if (!sortedQueMax.empty() && sortedQueMax.front().second == left)
	//			sortedQueMax.pop_front();
	//		if (!sortedQueMin.empty() && sortedQueMin.front().second == left)
	//			sortedQueMin.pop_front();
	//	}

	//	std::cout << "SubArrWLessEqualMinMaxDiff SlideWindow for \"" << K << " from \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
	//	return res;
	//}

	std::vector<std::pair<int, int>> SlideWindow(const std::vector<int> & v, int K)
	{
		int N = v.size();
		std::vector<std::pair<int, int>> res;//first: left index, second: right index
		std::list<std::pair<int, int>> sortedQueMin;//first: value, second: index
		std::list<std::pair<int, int>> sortedQueMax;//first: value, second: index
		/*
		sortedQueMin: ascending order of some elements in window with their relative orders (sorted queue)
		sortedQueMax: descending order of some elements in window with their relative orders (sorted queue)
		*/
		/*for each left, keep longest valid window right*/
		int right = 0;
		for (int left = 0; left < N; ++left)
		{
			/*expand the window right as rightmost as possible, as long as it is valid (max-min <= K)*/
			while (right < N)
			{
				while (!sortedQueMax.empty() && sortedQueMax.back().first <= v[right])
					sortedQueMax.pop_back();
				sortedQueMax.push_back({ v[right], right });

				while (!sortedQueMin.empty() && sortedQueMin.back().first >= v[right])
					sortedQueMin.pop_back();
				sortedQueMin.push_back({ v[right], right });

				if (sortedQueMax.front().first - sortedQueMin.front().first > K)
					break;
				++right;
			}

			/*now [left,right) is a longest valid window for index at left*/
			for (int i = left; i < right; ++i)
				res.push_back({ left, i });

			/*drop left before advancing*/
			if (!sortedQueMax.empty() && sortedQueMax.front().second == left)
				sortedQueMax.pop_front();
			if (!sortedQueMin.empty() && sortedQueMin.front().second == left)
				sortedQueMin.pop_front();
		}

		std::cout << "SubArrWLessEqualMinMaxDiff SlideWindow for \"" << K << " from \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
SubArrWLessEqualMinMaxDiff SlideWindow for "2 from "3, 5, 7, 6, 3": [0,0], [0,1], [1,1], [1,2], [1,3], [2,2], [2,3], [3,3], [4,4]
SubArrWLessEqualMinMaxDiff SlideWindow for "2 from "4, 1, 6, 0, 5, 3, 2, 7, 6, 3, 9, 2, 4": [0,0], [1,1], [2,2], [3,3], [4,4], [4,5], [5,5], [5,6], [6,6], [7,7], [7,8], [8,8], [9,9], [10,10], [11,11], [11,12], [12,12]
*/
#endif