#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
http://rosettacode.org/wiki/Sorting_algorithms/Counting_sort#C

O(n+range) time, O(range) space
*/
class CountingSort
{
public:
	CountingSort(){}
	~CountingSort(){}

	void GO(int A[], int n, int min, int max)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		int range = max - min + 1;
		std::vector<int> count(range, 0);
		for (int i = 0; i < n; ++i)
			++count[A[i] - min];

		int index = 0;
		for (int num = min; num <= max; ++num)
		{
			while (count[num - min] != 0)//push_back A[] with same numbers
			{
				A[index] = num;
				++index;
				--count[num - min];
			}
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "CountingSort for \"" << before << "\" is: " << after << std::endl;
	}
};
/*
CountingSort for "41, 67, 34, 3, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27, 61" is: 3, 5, 24, 27, 34, 41, 45, 58, 61, 62, 64, 67, 69, 78, 81
*/
#endif