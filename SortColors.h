#ifndef SORT_COLORS_H
#define SORT_COLORS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
https://github.com/anson627/leetcode/blob/master/SortColors/SortColors.cpp
http://www.csse.monash.edu.au/~lloyd/tildeAlgDS/Sort/Flag/
http://coding-exercise.blogspot.tw/2013/03/leetcode-sort-colors.html
http://yucoding.blogspot.tw/2013/05/leetcode-questions-99-sort-colors.html
// Given an array with n objects colored red, white or blue, sort them so that
// objects of the same color are adjacent, with the colors in the order red,
// white and blue.
//
// Here, we will use the integers 0, 1, and 2 to represent the color red,
// white, and blue respectively.
//
// Note:
// You are not suppose to use the library's sort function for this problem.
//
// Follow up:
// A rather straight forward solution is a two-pass algorithm using counting
// sort.
// First, iterate the array counting number of 0's, 1's, and 2's, then
// overwrite array with total number of 0's, then 1's and followed by 2's.
//
// Could you come up with an one-pass algorithm using only constant space?
//
// Three Way Partition, O(n) time, O(1) space
// Counting Sort, O(n) time, o(1) space
//
// Insertion Sort, O(n^2) time, O(n*k) if array is already k sorted
// Quick Sort, O(nlog(n)) average, O(n^2) worse
// Merge Sort, O(nlog(n)) time, O(n) space
// Heap Sort, O(nlog(n)) time, O(1) space
*/
class SortColors
{
public:
	SortColors(){}
	~SortColors(){}

	void ThreeWayPartition(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		int curFrontCount = 0;
		int curBackCount = n - 1;
		int i = 0;
		while (i <= curBackCount)
		{
			if (A[i] == 0)
			{
				std::swap(A[curFrontCount++], A[i++]);
			}
			else if (A[i] == 1)
			{
				++i;
			}
			else
			{
				std::swap(A[curBackCount--], A[i]);
			}
		}
		std::cout << "SortColors ThreeWayPartition for \"" << before << "\": " << Debug::ToStr1D<int>()(A, n) << std::endl;
	}

	void CountingSort1(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		int tmp[3] = { 0 };
		for (int i = 0; i < n; ++i)
			++tmp[A[i]];
		int i = 0;
		for (int j = 0; j < 3; ++j)
		while (tmp[j]--)
			A[i++] = j;

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Counting1 for \"" << before << "\": " << after << std::endl;
	}

	void CountingSort2(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		int zero = -1;
		int one = -1;
		int two = -1;
		for (int i = 0; i < n; ++i)
		{
			if (A[i] == 0)
			{
				A[++two] = 2;
				A[++one] = 1;
				A[++zero] = 0;
			}
			else if (A[i] == 1)
			{
				A[++two] = 2;
				A[++one] = 1;
			}
			else
			{
				A[++two] = 2;
			}
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Counting2 for \"" << before << "\": " << after << std::endl;
	}

	void InsertionSort(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		for (int i = 0; i < n; ++i)
		{
			int tmp = A[i];
			int j = i;
			for (; j > 0 && A[j - 1] > tmp; --j)
				A[j] = A[j - 1];
			A[j] = tmp;
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Insertion for \"" << before << "\": " << after << std::endl;
	}

	void QuickSort(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		this->QuickSortRecur(A, 0, n - 1);

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Quick for \"" << before << "\": " << after << std::endl;
	}
private:
	void QuickSortRecur(int A[], int first, int last)
	{
		if (first >= last)
			return;

		std::swap(A[first], A[first + std::rand() % (last - first + 1)]);
		int i = first;
		int j = last + 1;
		while (true)
		{
			do 
			{
				++i;
			} while (i <= last && A[i] < A[first]);
			do
			{
				--j;
			} while (j >= first && A[j] > A[first]);
			if (i > j)
				break;
			std::swap(A[i], A[j]);

		}
		std::swap(A[first], A[j]);
		this->QuickSortRecur(A, first, j - 1);
		this->QuickSortRecur(A, j + 1, last);
	}

public:
	void MergeSort(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);

		int * tmp = new int[n];
		this->MergeSortRecur(A, 0, n - 1, tmp);
		delete[] tmp;
		tmp = 0;

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Merge for \"" << before << "\": " << after << std::endl;
	}
private:
	void MergeSortRecur(int A[], int first, int last, int tmp[])
	{
		if (first >= last)
			return;
		int middle = first + (last - first) / 2;
		this->MergeSortRecur(A, first, middle, tmp);
		this->MergeSortRecur(A, middle + 1, last, tmp);

		/*merge A[first]~A[middle] with A[middle+1]~A[last]*/
		for (int k = first; k <= last; ++k)
			tmp[k] = A[k];
		int i = first;
		int j = middle + 1;
		int k = first;
		while (i <= middle || j <= last)
			A[k++] = (j > last || (i <= middle && tmp[i] <= tmp[j])) ? tmp[i++] : tmp[j++];
	}

public:
	void HeapSort(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		
		for (int i = 2; i <= n; ++i)
		{
			for (int j = i, p; (p = j / 2) > 0; j = p)
			{
				if (A[p - 1] >= A[j - 1])
					break;
				std::swap(A[p - 1], A[j - 1]);
			}
		}
		for (int i = n; i >= 2; --i)
		{
			std::swap(A[0], A[i - 1]);
			for (int j = 1, c; (c = 2 * j) < i; j = c)
			{
				if (c + 1 < i && A[c] > A[c - 1])
					c += 1;
				if (A[j - 1]> A[c - 1])
					break;
				std::swap(A[j - 1], A[c - 1]);
			}
		}

		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "SortColors Heap for \"" << before << "\": " << after << std::endl;
	}

};
/*
SortColors ThreeWayPartition for "0, 2, 0, 1, 2, 1, 1, 2, 2, 0, 1, 0, 2": 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2
SortColors Counting1 for "0, 2, 0, 1, 2, 1, 1, 2, 2, 0, 1, 0, 2": 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2
SortColors Counting2 for "0, 2, 0, 1, 2, 1, 1, 2, 2, 0, 1, 0, 2": 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2
SortColors Insertion for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
SortColors Quick for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
SortColors Merge for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
SortColors Heap for "7, 4, 3, 8, 2, 7, 1, 9, 6, 7, 5, 4, 8": 1, 2, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9
*/
#endif