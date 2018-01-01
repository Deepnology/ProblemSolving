#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
/*
Stable O(nlogn) time sorting algorithm that requires extra space.
Efficient than QuickSort for sequential accessed data structures such as list, and for huge data from external storage.
Sort each pair of elements.
Then, sort every four elements by merging every two pairs.
Then, sort every eight elements, etc.
Category: Merge Sort
Divide and conquer
Best case: O(n) or O(nlogn)
Average case: O(nlogn)
Worst case: O(nlogn)
Worst case space: O(n)
Stability: Stable
*/
class MergeSort
{
public:
	MergeSort(){}
	~MergeSort(){}

public:
	void GO(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		int * tmp = new int[n];
		this->MergeSortRecur(A, 0, n - 1, tmp);
		delete[] tmp;
		tmp = 0;

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "MergeSort for \"" << before << "\" is: " << after << std::endl;
	}
private:
	void MergeSortRecur(int A[], int first, int last, int tmp[])
	{
		if (first >= last)
			return;

		int middle = first + (last - first) / 2;
		this->MergeSortRecur(A, first, middle, tmp);
		this->MergeSortRecur(A, middle + 1, last, tmp);

		/*post-order merge A[first]~A[middle] with A[middle+1]~A[last]*/
		for (int k = first; k <= last; ++k)
			tmp[k] = A[k];
		int i = first;
		int j = middle + 1;
		int k = first;
		while (i <= middle || j <= last)
			A[k++] = (j > last || (i <= middle && tmp[i] <= tmp[j])) ? tmp[i++] : tmp[j++];
	}

	/*
	with STL
	http://rosettacode.org/wiki/Sorting_algorithms/Merge_sort
	*/
public:
	void GO_STL(std::vector<int> && A)
	{
		std::string before = Debug::ToStr1D<int>()(A);
		this->MergeSortSTLRecur(A.begin(), A.end());
		std::cout << "MergeSort STL for \"" << before << "\": " << Debug::ToStr1D<int>()(A) << std::endl;
	}
private:
	void MergeSortSTLRecur(std::vector<int>::iterator first, std::vector<int>::iterator last)
	{
		if (last - first > 1)
		{
			std::vector<int>::iterator middle = first + (last - first) / 2;
			this->MergeSortSTLRecur(first, middle);
			this->MergeSortSTLRecur(middle, last);
			std::inplace_merge(first, middle, last, std::less<int>());
			/*
			std::inplace_merge:
			merge two consecutive ranges: [first,middle) and [middle,last),
			putting the result into the combined sorted range [first,last)
			*/
		}
	}
};
/*
MergeSort for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8" is: 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
MergeSort STL for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/

#endif

