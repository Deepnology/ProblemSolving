#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
more efficient than bubble sort
better than insertion sort in terms of number of writes
efficient for small arrays
offen used as part of more sophisticated algorithms
Find the smallest element using a linear scan and move it to the front.
Then, find the second smallest and move it, again doing linear scan.
Continue doing this until all the elements are in place.
Category: Selection Sort
Essentially an in-place comparison sort
Better than Bubble Sort
Best case: O(n^2)
Average case: O(n^2)
Worst case: O(n^2)
Stability: unstable
*/
class SelectionSort
{
public:
	SelectionSort(){}
	~SelectionSort(){}

	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		for (int i = 0; i < n; ++i)
		{
			//find the min element in [i,n-1] and move to current start i, without affecting already sorted elements in the front
			int min = i;
			for (int j = i; j < n; ++j)
			{
				if (A[j] < A[min])
					min = j;
			}
			std::swap(A[i], A[min]);
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SelectionSort for \"" << before << "\" is: " << after << std::endl;
	}

	void GO(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
		{
			std::iter_swap(i, std::min_element(i, v.end()));
		}
		std::string after = Debug::ToStr1D<int>()(v);
		std::cout << "SelectionSort wSTL for \"" << before << "\" is: " << after << std::endl;
	}
};
/*
SelectionSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
SelectionSort wSTL for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif