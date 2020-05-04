/*MUST*/
#ifndef	WEIGHTED_MEDIAN_ELEMENT_H
#define WEIGHTED_MEDIAN_ELEMENT_H
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.csee.umbc.edu/~kalpakis/Courses/441-sp03/hws/hw4-sol.pdf
http://stackoverflow.com/questions/9794558/weighted-median-computation
Elements of programming interview, Searching: Compute the optinum mailbox placement
A total of n apartment buildings are coming up on a new street.
The postal service wants to place a single mailbox on the street.
Their objective is to minimize the total distance that residents have to walk to collect their mail each day.
Building i has Ri residents, and is at distance Di from the beginning of the street.
Device an algorithm that computes a distance m from the beginning of the street for the mailbox that minimizes the total distance, that residents travel to get to the mailbox
                       n-1
, i.e., minimizes Sigma    Ri * |Di - m|.
                       i=0
The goal is to find the weighted median of Ri * Di, where i is from 0 to n-1.
(Geometric Median, Facility Location Problem, Weber Problem)

UseSort: O(nlogn) time
UseSelect: O(n) time

1. calculate total weight sum
2. find mid of current range, move elements whose distance from begin < mid's distance from begin to left side, update pivot to mid's idx after rearrange (partition)
3. accumulate both left and right side weight sum exclude pivot's weight
4. if left weight sum > total weight sum/2: left weight sum is too large, next search left side (remember to keep accumulated right weight sum by adding it to the pivot-1's weight)
   if right weight sum > total weight sum/2: right weight sum is too large, next search right side (remember to keep accumulated left weight sum by adding it to the pivot+1's weight)
   if both left and right weight sum are less equal than total weight sum/2, we found median at pivot
*/
class WeightedMedianElement
{
public:
	WeightedMedianElement(){}
	~WeightedMedianElement(){}

	std::pair<double, int> UseSort(std::vector<std::pair<double, int> > v)//first: weight (num of resident), second: value (distance from begin)
	{
		std::string before = Debug::ToStr1D<double, int>()(v);
		int N = v.size();
		std::sort(v.begin(), v.end(), [](const std::pair<double, int> & a, const std::pair<double, int> & b)->bool
		{
			return a.second < b.second;
		});
		double weightSum = 0;
		for (const auto & p : v)
		{
			weightSum += p.first;
		}
		
		int idx = 0;
		double sum = weightSum - v[0].first;
		while (sum > weightSum / 2 && idx < N - 1)
		{
			++idx;
			sum -= v[idx].first;
		}
		
		std::cout << "WeightedMedianElement UseSort for \"" << before << "\": [" << v[idx].first << "," << v[idx].second << "]" << std::endl;
		return v[idx];
	}

	std::pair<double, int> UseSelect(std::vector<std::pair<double, int> > v)//first: weight (num of resident), second: value (distance from begin)
	{
		std::string before = Debug::ToStr1D<double, int>()(v);
		int N = v.size();

		double weightSum = 0;
		for (const auto & p : v)
		{
			weightSum += p.first;
		}
		int idx = 0;
		int lo = 0;
		int hi = N - 1;
		
		while (lo <= hi)
		{
			int mid = (lo + hi) / 2;
			std::nth_element(v.begin() + lo, v.begin() + mid, v.begin() + hi + 1, [](const std::pair<double, int> & a, const std::pair<double, int> & b)
			{
				return a.second < b.second;
			});
			//std::cout << Debug::ToStr1D<double, int>()(v) << std::endl;

			double wSumL = 0;//left weight sum exclude mid
			double wSumR = 0;//right weight sum exclude mid

			for (int i = lo; i < mid; ++i)
				wSumL += v[i].first;
			
			for (int i = mid + 1; i <= hi; ++i)
				wSumR += v[i].first;

			if (weightSum / 2 < wSumL)//left weight sum is too much: next search left side
			{
				hi = mid - 1;
				v[hi].first += (wSumR + v[mid].first);//when searching left side, we want to keep right weight sum
			}
			else if (weightSum / 2 < wSumR)//right weight sum is too much: next search right
			{
				lo = mid + 1;
				v[lo].first += (wSumL + v[mid].first);//when searching right side, we want to keep left weight sum
			}
			else//weightSum/2 >= wSumL && weightSum/2 >= wSumR
			{
				idx = mid;
				break;
			}
		}

		std::cout << "WeightedMedianElement UseSelect for \"" << before << "\": [" << v[idx].first << "," << v[idx].second << "]" << std::endl;
		return v[idx];
	}

	std::pair<double, int> UseSelect2(std::vector<std::pair<double, int> > v)//first: weight (num of resident), second: value (distance from begin)
	{
		std::string before = Debug::ToStr1D<double, int>()(v);
		int N = v.size();

		double weightSum = 0;
		for (const auto & p : v)
		{
			weightSum += p.first;
		}
		int idx = 0;
		int lo = 0;
		int hi = N - 1;

		while (lo <= hi)
		{
			int mid = (lo + hi) / 2;
			int pivotVal = v[mid].second;//pivotVal: distance from begin of mid element
			int pivot = std::partition(v.begin() + lo, v.begin() + hi + 1, [&](const std::pair<double, int> & a)
			{
				return a.second < pivotVal;
			}) - v.begin();
			for (int i = pivot; i <= hi; ++i)
				if (!(v[pivot] < v[i]))
					std::swap(v[i], v[pivot]);
			//std::cout << Debug::ToStr1D<double, int>()(v) << std::endl;

			double wSumL = 0;//left weight sum exclude mid
			double wSumR = 0;//right weight sum exclude mid

			for (int i = lo; i < pivot; ++i)
				wSumL += v[i].first;

			for (int i = pivot + 1; i <= hi; ++i)
				wSumR += v[i].first;

			if (weightSum / 2 < wSumL)//left weight sum is too much: next search left side
			{
				hi = pivot - 1;
				v[hi].first += (wSumR + v[pivot].first);//when searching left side, we want to keep right weight sum
			}
			else if (weightSum / 2 < wSumR)//right weight sum is too much: next search right
			{
				lo = pivot + 1;
				v[lo].first += (wSumL + v[pivot].first);//when searching right side, we want to keep left weight sum
			}
			else//weightSum/2 >= wSumL && weightSum/2 >= wSumR
			{
				idx = pivot;
				break;
			}
		}

		std::cout << "WeightedMedianElement UseSelect2 for \"" << before << "\": [" << v[idx].first << "," << v[idx].second << "]" << std::endl;
		return v[idx];
	}
};
/*
WeightedMedianElement UseSort for "[2,0], [5,1], [1,2], [4,3], [6,4], [2,5], [9,6], [1,7], [8,8], [13,9], [7,10], [10,11], [17,12], [13,13], [8,14], [12,15]": [10,11]
WeightedMedianElement UseSelect for "[13,13], [1,2], [7,10], [9,6], [10,11], [12,15], [17,12], [13,9], [8,14], [2,0], [6,4], [2,5], [1,7], [5,1], [4,3], [8,8]": [10,11]
WeightedMedianElement UseSelect2 for "[13,13], [1,2], [7,10], [9,6], [10,11], [12,15], [17,12], [13,9], [8,14], [2,0], [6,4], [2,5], [1,7], [5,1], [4,3], [8,8]": [118,11]
WeightedMedianElement UseSort for "[27,0], [18,1], [13,2], [7,3], [6,4], [2,5], [6,6], [1,7], [8,8], [3,9], [4,10], [3,11], [4,12], [2,13], [3,14], [2,15]": [13,2]
WeightedMedianElement UseSelect for "[2,13], [13,2], [4,10], [6,6], [3,11], [2,15], [4,12], [3,9], [3,14], [27,0], [6,4], [2,5], [1,7], [18,1], [7,3], [8,8]": [109,2]
WeightedMedianElement UseSelect2 for "[2,13], [13,2], [4,10], [6,6], [3,11], [2,15], [4,12], [3,9], [3,14], [27,0], [6,4], [2,5], [1,7], [18,1], [7,3], [8,8]": [91,2]
*/
#endif