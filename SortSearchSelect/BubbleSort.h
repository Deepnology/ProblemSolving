#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
/*
http://www.algorithmist.com/index.php/Bubble_sort.c
Start at the beginning of an array and swap the first two elements if the first is bigger than the second.
Go to the next pair, continuously making sweeps of the array until sorted.
Category: Exchange Sort
Best case: O(n)
Average case: O(n^2)
Worst case: O(n^2)
Stability: stable
*/
class BubbleSort
{
public:
	BubbleSort(){}
	~BubbleSort(){}

	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		for (int i = n - 1; i > 0; --i)
		{
			//find and move the max element in [0,i-1] to current end i, without affecting already sorted elements in the back
			for (int j = 1; j <= i; ++j)
			{
				if (A[j - 1] > A[j])
				{
					std::swap(A[j - 1], A[j]);
				}
			}
		}
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "BubbleSort for \"" << before << "\" is: " << after << std::endl;
	}
};
/*
BubbleSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif