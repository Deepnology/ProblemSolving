#ifndef SORT_1toN_AVG_OUTSIDE_2_NUMS_H
#define SORT_1toN_AVG_OUTSIDE_2_NUMS_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
http://www.careercup.com/question?id=11534829
Given an array containing integers from 1 to N in ascending order.
Rearrange the array such that average of any two numbers (if present) falls outside the two numbers.
If the average of two numbers is not an integer, we can assume that they do not have an average.

Recursively partition the array into two halves where the first half is composed of even indexed numbers (odd nums for 1st partition)
and the second half is composed of odd indexed numbers (even nums for the 1st partition).

Base case:
1 2: 1 2
1 2 3: 1 3 2
1 2 3 4: 1 3 2 4
1 2 3 4 5: 1 5 3 2 4 (1 2 3 4 5 -> 1 3 5 2 4 -> 1 5 3 2 4)
Recursively group even indexed numbers and odd indexed numbers for current level

Similiar to the process of QuickSort, except the way of partition.

use QuickSort method: O(nlogn) time, O(n) space
*/
class Sort1toNAvgOutside2Nums
{
public:
	Sort1toNAvgOutside2Nums(){}
	~Sort1toNAvgOutside2Nums(){}

	void QuickSort(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::vector<int> tmp(N);
		this->recur(v, tmp, 0, N - 1);

		std::cout << "Sort1toNAvgOutside2Nums QuickSort for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
private:
	void recur(std::vector<int> & v, std::vector<int> & tmp, int left, int right)
	{
		if (left >= right)
			return;
		for (int i = left; i <= right; ++i)
			tmp[i] = v[i];

		int mid = (left + right) / 2;
		int even = left;
		int odd = mid + 1;
		for (int i = left; i <= right; ++i)
		{
			if ((i - left) % 2 == 0)
				v[even++] = tmp[i];
			else
				v[odd++] = tmp[i];
		}
		std::cout << Debug::ToStr1D<int>()(v, left, right) << std::endl;

		this->recur(v, tmp, left, mid);
		this->recur(v, tmp, mid + 1, right);
	}
};
/*
1, 3, 2
1, 3
Sort1toNAvgOutside2Nums QuickSort for "1, 2, 3": 1, 3, 2
1, 3, 2, 4
1, 3
2, 4
Sort1toNAvgOutside2Nums QuickSort for "1, 2, 3, 4": 1, 3, 2, 4
1, 3, 5, 2, 4
1, 5, 3
1, 5
2, 4
Sort1toNAvgOutside2Nums QuickSort for "1, 2, 3, 4, 5": 1, 5, 3, 2, 4
1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10, 12
1, 5, 9, 3, 7, 11
1, 9, 5
1, 9
3, 11, 7
3, 11
2, 6, 10, 4, 8, 12
2, 10, 6
2, 10
4, 12, 8
4, 12
Sort1toNAvgOutside2Nums QuickSort for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12": 1, 9, 5, 3, 11, 7, 2, 10, 6, 4, 12, 8
1, 3, 5, 7, 9, 11, 13, 2, 4, 6, 8, 10, 12
1, 5, 9, 13, 3, 7, 11
1, 9, 5, 13
1, 9
5, 13
3, 11, 7
3, 11
2, 6, 10, 4, 8, 12
2, 10, 6
2, 10
4, 12, 8
4, 12
Sort1toNAvgOutside2Nums QuickSort for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13": 1, 9, 5, 13, 3, 11, 7, 2, 10, 6, 4, 12, 8
*/
#endif