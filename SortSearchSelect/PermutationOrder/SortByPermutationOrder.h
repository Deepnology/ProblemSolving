#ifndef SORT_BY_PERMUTATION_ORDER_H
#define SORT_BY_PERMUTATION_ORDER_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=4669539153346560
Given an array of integers with arbitrary order.
Given another array of integers ranging from 1 to N in arbitrary order, which is a permutation of 1,2,...,N.
For each position in the first array, move the element associated with the index in the second array to the current position.
v[i] <- v[Idx[i]-1]

2 steps:
1. Quick sort: O(nlogn) time
2. Perform in-place swaps: O(n) time
=> O(nlogn) time in total

See also ApplyPermutationOrder.h, LeastDistanceSort.h
*/
class SortByPermutationOrder
{
public:
	SortByPermutationOrder(){}
	~SortByPermutationOrder(){}

	void InPlace_2Pass(std::vector<int> && v, std::vector<int> Idx)
	{
		std::string before1 = Debug::ToStr1D<int>()(v);
		std::string before2 = Debug::ToStr1D<int>()(Idx);
		int N = v.size();
		std::sort(v.begin(), v.end(), std::less<int>());//ascending order
		//std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		for (int i = 0; i < N; ++i)
			Idx[i] = v[Idx[i] - 1];
		for (int i = 0; i < N; ++i)
			v[i] = Idx[i];
		std::cout << "SortByPermutationOrder 2Pass for \"" << before1 << "\" with order \"" << before2 << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
	}

	void InPlace_Swap(std::vector<int> && v, std::vector<int> Idx)
	{
		std::string before1 = Debug::ToStr1D<int>()(v);
		std::string before2 = Debug::ToStr1D<int>()(Idx);
		int N = v.size();
		std::sort(v.begin(), v.end(), std::less<int>());//ascending order
		//std::cout << Debug::ToStr1D<int>()(v) << std::endl;

		/*when iterating over all values, keep those values on the left side of current index unchanged because they were already placed at the correct positions*/
		for (int i = 0; i < N; ++i)
		{
			/*
			case1: target index is on the right side of current index
			=> swap target value to current position
			*/
			if (Idx[i] - 1 > i)
			{
				std::swap((v[i]), (v[Idx[i] - 1]));
				continue;
			}

			/*
			case2: target index is current index
			=> current value already at correct position, just skip it
			*/
			if (Idx[i] - 1 == i)
				continue;

			/*
			case3: target index is on left side of current index, which was already placed with correct value and we don't want to change it
			=>	find the next index until it is greater than or equal to current index,
				which must be itself (equal) or on the right side (greater) of current index.
				then swap target value to current position
			*/
			int k = Idx[i] - 1;
			while (k < i)
			{
				k = Idx[k] - 1;
			}
			std::swap(v[k], v[i]);
		}
		
		std::cout << "SortByPermutationOrder Swap for \"" << before1 << "\" with order \"" << before2 << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
SortByPermutationOrder 2Pass for "17, 5, 1, 9" with order "3, 2, 4, 1":
9, 5, 17, 1
SortByPermutationOrder Swap for "17, 5, 1, 9" with order "3, 2, 4, 1":
9, 5, 17, 1
SortByPermutationOrder 2Pass for "5, 12, 14, 27, 3, 2, 13, 17, 7, 21" with order "3, 6, 2, 9, 7, 1, 4, 8, 5, 10":
5, 13, 3, 21, 14, 2, 7, 17, 12, 27
SortByPermutationOrder Swap for "5, 12, 14, 27, 3, 2, 13, 17, 7, 21" with order "3, 6, 2, 9, 7, 1, 4, 8, 5, 10":
5, 13, 3, 21, 14, 2, 7, 17, 12, 27
SortByPermutationOrder 2Pass for "10, 20, 30, 40" with order "3, 1, 2, 4":
30, 10, 20, 40
SortByPermutationOrder Swap for "10, 20, 30, 40" with order "3, 1, 2, 4":
30, 10, 20, 40
SortByPermutationOrder Swap for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10" with order "10, 1, 3, 2, 6, 5, 8, 9, 4, 7":
10, 1, 3, 2, 6, 5, 8, 9, 4, 7
SortByPermutationOrder 2Pass for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10" with order "10, 1, 3, 2, 6, 5, 8, 9, 4, 7":
10, 1, 3, 2, 6, 5, 8, 9, 4, 7
*/
#endif