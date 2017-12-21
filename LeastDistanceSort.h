#ifndef LEAST_DISTANCE_SORT_H
#define LEAST_DISTANCE_SORT_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Implement a least-distance sort
Design a sorting algorithm that minimizes the total distance that items are moved.
1. apply indirect sort: assign increasing indices to each reference to the object and sort all references to the objects
2. sort the objects by permutation order indices generated from indirect sort

O(nlogn) time, O(n) space

See also IndirectSortTextLineLengthInFile.h, SortByPermutationOrder.h
*/
class LeastDistanceSort
{
public:
	LeastDistanceSort(){}
	~LeastDistanceSort(){}

	void IndirectAndPermute(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		std::vector<std::pair<const int*, int> > permutation;
		for (int i = 0; i < N; ++i)
			permutation.push_back(std::make_pair(&v[i], i + 1));
		std::sort(permutation.begin(), permutation.end(), [](const std::pair<const int *, int> & a, const std::pair<const int *, int> & b)->bool
		{
			return *(a.first) < *(b.first);
		});

		std::ostringstream oss;
		for (int i = 0; i < N; ++i)
		{
			oss << "[" << *(permutation[i].first) << "," << permutation[i].second << "]";
			if (i != N - 1)
				oss << ", ";
		}
		std::cout << oss.str() << std::endl;

		//sort v by permutation order: v[i] <- v[Idx[i]-1]
		/*when iterating over all values, keep those values on the left side of current index unchanged because they were already placed at the correct positions*/
		for (int i = 0; i < N; ++i)
		{
			/*
			case1: target index is on the right side of current index
			=> swap target value to current position
			*/
			if (permutation[i].second - 1 > i)
			{
				std::swap((v[i]), (v[permutation[i].second - 1]));
				continue;
			}

			/*
			case2: target index is current index
			=> current value already at correct position, just skip it
			*/
			if (permutation[i].second - 1 == i)
				continue;

			/*
			case3: target index is on left side of current index, which was already placed correctly and we don't want to change it
			=>	find the next index until it is greater than or equal to current index,
			which must be itself (equal) or on the right side (greater) of current index.
			then swap target value to current position
			*/
			int k = permutation[i].second - 1;
			while (k < i)
			{
				k = permutation[k].second - 1;
			}
			std::swap(v[k], v[i]);
		}

		std::cout << "LeastDistanceSort for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
[0,4], [5,11], [24,6], [27,14], [34,3], [41,1], [45,12], [58,8], [61,15], [62,9], [64,10], [67,2], [69,5], [78,7], [81,13]
LeastDistanceSort for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
*/
#endif