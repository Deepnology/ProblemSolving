#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://rosettacode.org/wiki/Sorting_algorithms/Insertion_sort#C
Category: Insertion Sort
Relatively efficient for small lists and mostly-sorted lists
More efficient than most other quadratic sorting algorithms (bubble sort)
Often used as part of more sophisticated algorithms
Online: can sort a list as it receives it
Efficient for nearly sorted data set where each element is at most K away from its target position. O(nk)time
Best case: O(n)
Average case: O(n^2)
Worst case: O(n^2)
Stability: stable
*/
class InsertionSort
{
public:
	InsertionSort(){}
	~InsertionSort(){}

	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		for (int i = 1; i < n; ++i)
		{
			//insert A[i] into a sorted range [0,i-1] by right shifting all greater elements
			int tmp = A[i];
			int j;
			for (j = i; j > 0 && A[j - 1] > tmp; --j)
				A[j] = A[j - 1];
			A[j] = tmp;
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "InsertionSort for \"" << before << "\" is: " << after << std::endl;
	}

	/*
	Uses binary search via std::upper_bound() to find the insertion position in logarithmic time
	, then performs the insertion via std::rotate(), in linear time.
	*/
	void GO(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);

		for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
			std::rotate(std::upper_bound(v.begin(), i, *i), i, i + 1);

		std::string after = Debug::ToStr1D<int>()(v);
		std::cout << "InsertionSort wSTL for \"" << before << "\" is: " << after << std::endl;
	}
};
/*
InsertionSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
InsertionSort wSTL for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif