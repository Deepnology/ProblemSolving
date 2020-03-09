#ifndef MIN_AND_MAX_IN_ARRAY_W_MIN_COMP_H
#define MIN_AND_MAX_IN_ARRAY_W_MIN_COMP_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Searching: Find the min and max simultaneously
                                                                                  _      _
Find the min and max elements from an array of n > 0 elements using no more than |  3n/2  | - 2 comparisons.

Find the min m and max M of the first two elements; this requires a single comparison.
Now process the remaining elements two at a time.
Let (x,y) be such a pair.
If min(x,y) < m, update m; if max(x,y) > M, update M.
This entails three comparisons for each pair.
If n is odd, the last update entails two comparisons, namely comparing the last element with m and M.

BruteForce approach: keep track of the min and max through out all elements, which results in n*2 comparisons.

O(n) time
*/
class MinAndMaxInArrayWMinComp
{
public:
	MinAndMaxInArrayWMinComp(){}
	~MinAndMaxInArrayWMinComp(){}

	std::pair<int, int> Iterate(const std::vector<int> & v)
	{
		int N = v.size();
		if (N <= 1)
			return{ v.front(), v.front() };

		/*
		std::minmax(a, b)
		returns a pair with the smallest of a and b as the first element, and the largest as second
		*/
		std::pair<int, int> minMax = std::minmax(v[0], v[1]);
		for (int i = 2; i + 1 < N; i += 2)//n/2 iterations
		{
			std::pair<int, int> p = std::minmax(v[i], v[i + 1]);//1 comparison
			minMax = { std::min(minMax.first, p.first), std::max(minMax.second, p.second) };//2 comparisons
		}

		if (N & 1)//odd numbers, need to compare the last element
		{
			minMax = { std::min(minMax.first, v.back()), std::max(minMax.second, v.back()) };
		}

		std::cout << "MinAndMaxInArrayWMinComp Iterate for \"" << Debug::ToStr1D<int>()(v) << "\": " << minMax.first << ", " << minMax.second << std::endl;
		return minMax;
	}
};
/*
MinAndMaxInArrayWMinComp Iterate for "41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61": 0, 81
*/
#endif