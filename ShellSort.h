#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
http://rosettacode.org/wiki/Sorting_algorithms/Shell_sort#C
Category: Insertion Sort
It improves upon Bubble Sort and Insertion Sort by moving out of order elements more than one position at a time.
It compares elements separated by a gap of several positions. 
This lets an element take "bigger steps" toward its expected position.
Multiple passes over the data are taken with smaller and smaller gap sizes. 
The last step of Shell Sort is a plain Insertion Sort, but by then, the array of data is guaranteed to be almost sorted.
Best case: O(n)
Average case: depends on gap sequence
Worst case: O(n^2) or O(nlog^2n) depending on gap sequence
Stability: unstable
*/
class ShellSort
{
public:
	ShellSort(){}
	~ShellSort(){}

	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		for (int gap = n; (gap /= 2) != 0;)//one more extra outer loop than Insertion Sort
		{
			for (int i = gap; i < n; ++i)
			{
				//insert A[i] into a sorted range [gap,i-gap] by right shifting all greater elements a gap
				int tmp = A[i];
				int j;
				for (j = i; j >= gap && A[j - gap] > tmp; j -= gap)
					A[j] = A[j - gap];
				A[j] = tmp;
			}
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "ShellSort for \"" << before << "\" is: " << after << std::endl;
	}
};
/*
ShellSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif