#ifndef MEDIAN_OF_MEDIANS_H
#define MEDIAN_OF_MEDIANS_H
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
http://himangi774.blogspot.tw/2013/09/median-of-medians.html
O(n)
*/
/*
median:
1. first + len / 2
=> odd numbers: center
=> even numbers: center's right
2. (first + last) / 2
=> odd numbers: center
=> even numbers: center's left
*/
class MedianOfMedians
{
public:
	MedianOfMedians(){}
	~MedianOfMedians(){}

	/*the order of elements in A will be changed*/
	int GetIndex_InPlaceRecur(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		int index = this->GetIndex_InPlaceRecur(A, 0, n - 1);
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "MedianOfMedians GetIndex_InPlaceRecur before and after: " << index << std::endl;
		std::cout << before << std::endl;
		std::cout << after << std::endl;
		return index;
	}

	int GetIndex_InPlaceRecur(int A[], int first, int last)
	{
		int len = last - first + 1;
		
		if (len <= 5)
		{
			std::sort(A + first, A + last + 1);
			int median = first + len / 2;
			return median;
		}

		for (int i = 0; i <= len / 5; ++i)
		{
			int subFirst = 5 * i;
			int subLast;
			
			if (i < len / 5)
			{
				subLast = subFirst + 4;
			}
			else//i == len/5
			{
				if (len % 5 == 0)//remaining == 0
					continue;//skip
				subLast = subFirst + (len % 5 - 1);//subFirst + 0~3
			}

			int subMedian = this->GetIndex_InPlaceRecur(A, subFirst, subLast);//length of [subFirst,subLast] is always <= 5: recur will always return in the (len <= 5) case
			std::swap(A[first + i], A[subMedian]);//move a list of subMedian at indices starting from first
		}
		//now:
		//A[first]~A[len/5-1] (no remainings) or A[first]~A[len/5] (with remainings) is a list of subMedians
		//std::cout << "=> " << Debug::ToStr1D<int>()(A, first, len % 5 == 0 ? first + len / 5 - 1 : first + len / 5) << std::endl;
		return this->GetIndex_InPlaceRecur(A, first, len % 5 == 0 ? first + len / 5 - 1 : first + len / 5);
	}

	/*the order of elements in A will not be changed*/
	int GetValue_Recur(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		int value = this->GetValue_Recur(A, 0, n - 1);
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "MedianOfMedians GetValue_Recur before and after: " << value << std::endl;
		std::cout << before << std::endl;
		std::cout << after << std::endl;
		return value;
	}

	int GetValue_Recur(int A[], int first, int last)
	{
		int len = last - first + 1;
		
		if (len <= 5)
		{
			std::vector<int> copy(A + first, A + last + 1);
			std::sort(copy.begin(), copy.end());
			return copy[0 + (len - 0) / 2];//now return value instead of index
		}

		std::vector<int> subMedianVals;
		for (int i = 0; i <= len / 5; ++i)
		{
			int subFirst = 5 * i;
			int subLast;

			if (i < len / 5)
			{
				subLast = subFirst + 4;
			}
			else//i == len/5
			{
				if (len % 5 == 0)//remaining == 0
					continue;//skip
				subLast = subFirst + (len % 5 - 1);//subFirst + 0~3
			}

			int subMedianVal = this->GetValue_Recur(A, subFirst, subLast);
			subMedianVals.push_back(subMedianVal);
		}

		return this->GetValue_Recur(&subMedianVals[0], 0, subMedianVals.size() - 1);
	}
};
/*
MedianOfMedians GetIndex_InPlaceRecur before and after: 1
40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
8, 28, 18, 33, 38, 3, 23, 13, 34, 35, 26, 27, 36, 29, 30, 21, 22, 39, 24, 25, 16, 17, 40, 19, 20, 11, 12, 31, 14, 15, 6, 7, 32, 9, 10, 1, 2, 37, 4, 5
MedianOfMedians GetValue_Recur before and after: 28
40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
*/
#endif