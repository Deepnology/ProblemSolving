#ifndef FIRST_K_CLOSEST_TO_MEDIAN_ELEMENTS_H
#define FIRST_K_CLOSEST_TO_MEDIAN_ELEMENTS_H
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <functional>
#include "Debug.h"
#include "MedianElement.h"
/*
Elements of programming interview, Heaps: Find K elements closest to the median
Given an integer array. Compute the first K elements that are closest to the median of the array.

BruteForce_MaxHeap: O(nlogk) time, O(k) space

First find the median value of the array.
Keep a maxHeap of size K where the order is maintained by difference of the absolute value of median and each element in the array.
Loop through the array and push each element to the maxHeap.
After the loop, the elements in the maxHeap will be the result.

ModifiedSelection: O(n) time, O(1) space

First find the median value of the array.
Then apply the modified selection algorithm to the array.
In the selection algorithm, we want to find the Kth smallest element in the array
, and we also repeatedly rearrange a shrinking part of the array such that samller elements are moved to the left side and increment the count of left side elements toward K.
In the final result, all the elements precede the Kth element are smaller than it.
The modified selection algorithm is to repeatedly rearrange a shrinking part of the array with a comparator of abs difference between underlying element and median.
In the final result, the first K elements in the array will be the K closest elements to the median.
*/
class FirstKClosestToMedianElements
{
public:
	FirstKClosestToMedianElements(){}
	~FirstKClosestToMedianElements(){}
	struct SmallerThanComp
	{
		bool operator()(const std::pair<double, int> & a, const std::pair<double, int> & b)
		{
			return a.first < b.first;
		}
	};
	std::vector<int> BruteForce_MaxHeap(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		/*1. find the median, O(n) time*/
		double median = MedianElement().Iterate_NthElement(v, 0, N - 1);

		/*2. Keep a maxHeap of size K where the order is maintained by difference of the absolute value of median and each element in the array*/
		std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, SmallerThanComp> maxHeap;
		for (int i = 0; i < N; ++i)
		{
			if ((int)maxHeap.size() < K)
			{
				maxHeap.push(std::make_pair(std::fabs(v[i] - median), v[i]));
			}
			else if (std::fabs(v[i] - median) < maxHeap.top().first)//maxHeap.size() >= K && abs(cur - median) < maxHeap.top().first
			{
				maxHeap.pop();
				maxHeap.push(std::make_pair(std::fabs(v[i] - median), v[i]));
			}
		}

		std::vector<int> res;
		while (!maxHeap.empty())
		{
			res.push_back(maxHeap.top().second);
			maxHeap.pop();
		}

		std::cout << "FirstKClosestToMedian BruteForce_MaxHeap for \"" << K << "\" in \"" << before << "\": (" << median << "), " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> ModifiedSelection(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		int count = K;
		/*1. find the median, O(n) time*/
		double median = MedianElement().Iterate_NthElement(v, 0, N - 1);

		/*2. run the modified selection algorithm with a comparator of difference of abs of each element and the median*/
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			std::nth_element(v.begin() + left, v.begin() + mid, v.begin() + right + 1, [&](const int & a, const int & b)->bool
			{
				return std::fabs(a - median) < std::fabs(b - median);
			});
			int pivot = mid;
			if (count < pivot - left + 1)
				right = pivot - 1;
			else if (count > pivot - left + 1)
			{
				count -= (pivot - left + 1);
				left = pivot + 1;
			}
			else
				break;
		}

		std::vector<int> res;
		for (int i = 0; i < K; ++i)
			res.push_back(v[i]);
		std::cout << "FirstKClosestToMedian ModifiedSelection for \"" << K << "\" in \"" << before << "\": (" << median << "), " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> ModifiedSelection2(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		int count = K;
		/*1. find the median, O(n) time*/
		double median = MedianElement().Iterate_NthElement(v, 0, N - 1);

		/*2. run the modified selection algorithm with a comparator of difference of abs of each element and the median*/
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			int pivotVal = v[mid];
			int pivot = std::partition(v.begin() + left, v.begin() + right + 1, [&](const int & a)->bool
			{
				return std::fabs(a - median) < std::fabs(pivotVal - median);
			}) - v.begin();
			for (int i = pivot; i < right; ++i)
				if (!(std::fabs(v[pivot] - median) < std::fabs(v[i] - median)))
					std::swap(v[pivot], v[i]);

			if (count < pivot - left + 1)
				right = pivot - 1;
			else if (count > pivot - left + 1)
			{
				count -= (pivot - left + 1);
				left = pivot + 1;
			}
			else
				break;
		}

		std::vector<int> res;
		for (int i = 0; i < K; ++i)
			res.push_back(v[i]);
		std::cout << "FirstKClosestToMedian ModifiedSelection2 for \"" << K << "\" in \"" << before << "\": (" << median << "), " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> STL_Nth_Element(std::vector<int> v, int K)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		double median = MedianElement().Iterate_NthElement(v, 0, N - 1);

		std::nth_element(v.begin(), v.begin() + (K - 1), v.end(), [&](const int & a, const int & b)->bool
		{
			return std::fabs(a - median) < std::fabs(b - median);
		});

		std::vector<int> res;
		for (int i = 0; i < K; ++i)
			res.push_back(v[i]);

		std::cout << "FirstKClosestToMedian STL_Nth_Element for \"" << K << "\" in \"" << before << "\": (" << median << "), " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
FirstKClosestToMedian BruteForce_MaxHeap for "10" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 4, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": (56.5), 37, 74, 72, 48, 65, 63, 60, 53, 54, 59
FirstKClosestToMedian ModifiedSelection for "10" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 4, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": (56.5), 54, 59, 53, 60, 63, 65, 48, 72, 74, 37
FirstKClosestToMedian ModifiedSelection2 for "10" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 4, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": (56.5), 54, 59, 60, 65, 72, 48, 63, 53, 74, 37
FirstKClosestToMedian STL_Nth_Element for "10" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 4, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": (56.5), 54, 59, 53, 60, 63, 65, 48, 72, 74, 37
*/
#endif