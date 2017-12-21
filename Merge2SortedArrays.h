#ifndef MERGE_TWO_SORTED_ARRAYS_H
#define MERGE_TWO_SORTED_ARRAYS_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Implement mergesort in-place
https://github.com/anson627/leetcode/blob/master/MergeSortedArray/MergeSortedArray.cpp
Given two sorted integer arrays A and B, merge B into A as one sorted array.
Note:
You may assume that A has enough space to hold additional elements from B.
The number of elements initialized in A and B are m and n respectively.
Complexity:
O(m+n) time
*/
class Merge2SortedArrays
{
public:
	Merge2SortedArrays(){}
	~Merge2SortedArrays(){}

	/*
	large must have a larger array space than small
	but large's elements count is not necessarily larger than samll
	*/
	void Solve_InPlace(std::vector<int> & large, const std::vector<int> & small)
	{
		std::string before = Debug::ToStr1D<int>()(large);
		int N = large.size();
		int M = small.size();
		large.resize(N + M);

		/*merge large and small from the back*/
		int i = N - 1;
		int j = M - 1;
		for (int k = N + M - 1; k >= 0; --k)
		{
			large[k] = (j == -1 || (i >= 0 && large[i] > small[j])) ? large[i--] : small[j--];
		}
		
		std::cout << "Merge2SortedArray InPlace for \"" << before << "\", and \"" << Debug::ToStr1D<int>()(small) << "\": " << Debug::ToStr1D<int>()(large) << std::endl;
	}

	void Solve_InPlace2(std::vector<int> & large, const std::vector<int> & small)
	{
		std::string before = Debug::ToStr1D<int>()(large);
		int N = large.size();
		int M = small.size();
		large.resize(N + M);
		
		/*merge large and small from the back*/
		int i = N - 1;
		int j = M - 1;
		int k = N + M - 1;
		while (i >= 0 && j >= 0)
		{
			if (large[i] > small[j])
				large[k--] = large[i--];
			else
				large[k--] = small[j--];
		}
		/*
		now either large or small has been used up
		if there are remaining elements in small, we have to move them to large
		if there are remaining elements in large, we don't have to do anything bc they are already in the right place
		*/
		while (j >= 0)
			large[k--] = small[j--];

		std::cout << "Merge2SortedArray InPlace for \"" << before << "\", and \"" << Debug::ToStr1D<int>()(small) << "\": " << Debug::ToStr1D<int>()(large) << std::endl;
	}

	std::vector<int> Solve(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();
		std::vector<int> res(M + N);
		int i = 0;
		int j = 0;
		for (int k = 0; k < M + N; ++k)
		{
			res[k] = (j == N || (i < M && v1[i] < v2[j])) ? v1[i++] : v2[j++];
		}

		std::cout << "Merge2SortedArray for \"" << Debug::ToStr1D<int>()(v1) << "\", and \"" << Debug::ToStr1D<int>()(v2) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Solve2(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();
		std::vector<int> res(M + N);
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < M && j < N)
		{
			if (v1[i] < v2[j])
				res[k++] = v1[i++];
			else
				res[k++] = v2[j++];
		}
		while (i < M)
			res[k++] = v1[i++];
		while (i < N)
			res[k++] = v2[j++];

		std::cout << "Merge2SortedArray for \"" << Debug::ToStr1D<int>()(v1) << "\", and \"" << Debug::ToStr1D<int>()(v2) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
Merge2SortedArray InPlace for "1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23", and "2, 4, 6, 8, 10, 12, 14, 16": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 21, 23
Merge2SortedArray InPlace for "1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23", and "2, 4, 6, 8, 10, 12, 14, 16": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 21, 23
Merge2SortedArray for "1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23", and "2, 4, 6, 8, 10, 12, 14, 16": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 21, 23
Merge2SortedArray for "1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23", and "2, 4, 6, 8, 10, 12, 14, 16": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 21, 23
*/
#endif