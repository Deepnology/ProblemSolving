#ifndef PREVIOUS_PERMUTATION_H
#define PREVIOUS_PERMUTATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute the next permutation

For example:
input:  6,2,3,0,1,4,5
output: 6,2,1,5,4,3,0

See also NextPermutation.h
*/
class PreviousPermutation
{
public:
	PreviousPermutation(){}
	~PreviousPermutation(){}

	void InPlace(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		if (N < 2)
			return;

		int descendingEnd = N - 1;
		while (descendingEnd > 0 && !(v[descendingEnd - 1] > v[descendingEnd]))
			--descendingEnd;

		std::reverse(std::begin(v) + descendingEnd, std::end(v));

		if (descendingEnd > 0)
		{
			int pivot = descendingEnd - 1;

			//we want to find the upper bound in an descending order sorted array, the comparator should be "greater than" now
			int descendingUpperBound = std::upper_bound(v.begin() + descendingEnd, v.end(), v[pivot], std::greater<int>()) - v.begin();
			
			std::swap(v[pivot], v[descendingUpperBound]);
		}

		std::cout << "PreviousPermutation for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
PreviousPermutation for "6, 2, 3, 0, 1, 4, 5": 6, 2, 1, 5, 4, 3, 0
PreviousPermutation for "1, 3, 1": 1, 1, 3
PreviousPermutation for "1, 2, 3": 3, 2, 1
PreviousPermutation for "1, 3, 2": 1, 2, 3
*/
#endif