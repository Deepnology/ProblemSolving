#ifndef MEDIAN_2_SORTED_ARRAYS_H
#define MEDIAN_2_SORTED_ARRAYS_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
#include "KthSmallestElement2SortedArrays.h"
/*
https://github.com/anson627/leetcode/blob/master/MedianofTwoSortedArrays/MedianofTwoSortedArrays.cpp
There are two sorted arrays A and B of size m and n respectively. Find the
median of the two sorted arrays. The overall run time complexity should be
O(log (m+n)).

check also KthSmallestElement2SortedArrays.h
*/
class Median2SortedArrays
{
public:
	Median2SortedArrays(){}
	~Median2SortedArrays(){}

	//O((m+n)/2) time
	double Linear(const std::vector<int> & A, const std::vector<int> & B)
	{
		int M = A.size();
		int N = B.size();
		if (M == 0 && N == 0)
			return 0.0;

		std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::cout << Debug::ToStr1D<int>()(B) << std::endl;

		int i = 0;
		int j = 0;
		int preVal = -1;
		int curVal = -1;

		//the median of the 2 sorted array must be 0-based (m+n)/2-th (odd), or Avg((m+n)/2-1,(m+n)/2)-th (even) element when counting from the smallest element of the two sorted arrays
		//so just take (m+n)/2+1 elements in the increasing order from the two sorted arrays
		for (int indexOf2 = 0; indexOf2 <= (M + N) / 2; ++indexOf2)
		{
			preVal = curVal;//preVal is used for the even case

			//if B array is empty or (A array is non-empty and current A element is smaller)
			if (j == N || (i < M && A[i] < B[j]))
				curVal = A[i++];//take one element from A and save it to curVal, increment i
			else
				curVal = B[j++];//take one element from B and save it to curVal, increment j
		}

		if ((M + N) % 2 == 1)//odd
		{
			std::cout << "Median2SortedArray Linear (Middle): " << curVal << std::endl;
			return (double)curVal;
		}
		else//even
		{
			std::cout << "Median2SortedArray Linear (2 Middles' Avg): " << (preVal + curVal) / 2.0 << std::endl;
			return (preVal + curVal) / 2.0;
		}
	}

	//O(log(m+n)) time
	double Logarithmic(const std::vector<int> & A, const std::vector<int> & B)
	{
		int M = A.size();
		int N = B.size();
		if (M == 0 && N == 0)
			return 0.0;

		std::cout << Debug::ToStr1D<int>()(A) << std::endl;
		std::cout << Debug::ToStr1D<int>()(B) << std::endl;

		if ((M + N) % 2 == 1)//odd: median is 0-based (m+n)/2-th element
		{
			double r = (double)KthSmallestElement2SortedArrays().findRecur(A, 0, M - 1, B, 0, N - 1, (M + N) / 2);
			std::cout << "Median2SortedArray Logarithmic (Middle): " << r << std::endl;
			return r;
		}
		else//even: median is 0-based Avg((m+n)/2-1,(m+n)/2)-th element
		{
			double r = (KthSmallestElement2SortedArrays().findRecur(A, 0, M - 1, B, 0, N - 1, (M + N) / 2)
				+ KthSmallestElement2SortedArrays().findRecur(A, 0, M - 1, B, 0, N - 1, (M + N) / 2 - 1)
				) / 2.0;
			std::cout << "Median2SortedArray Logarithmic (2 Middles' Avg): " << r << std::endl;
			return r;
		}
	}
};
/*
1, 3, 5, 7, 9, 11
2, 4, 6, 8, 10, 12, 14, 16
Median2SortedArray Linear (2 Middles' Avg): 7.5
1, 3, 5, 7, 9, 11
2, 4, 6, 8, 10, 12, 14, 16
Median2SortedArray Logarithmic (2 Middles' Avg): 7.5
-1
-3, -2, 1, 3, 5, 6, 8, 8, 8, 10, 12
Median2SortedArray Linear (2 Middles' Avg): 5.5
-1
-3, -2, 1, 3, 5, 6, 8, 8, 8, 10, 12
Median2SortedArray Logarithmic (2 Middles' Avg): 5.5
*/
#endif