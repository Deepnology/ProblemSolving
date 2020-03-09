#ifndef MEDIAN_ELEMENT_H
#define MEDIAN_ELEMENT_H
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview
For an array with odd elements, the median element is the element located at index N/2 after sorting.
For an array with even elements, the median element is the avg of the 2 elements located at index N/2 and N/2 - 1 after sorting.

It's a general case of Kth smallest element (quick select) problem, where K is N/2 for even and the avg of N/2 and N/2 - 1 for odd array.
See also Partition.h, KthSmallestElement.h

O(n) time

used in FirstKClosestToMedian.h
*/
class MedianElement
{
public:
	MedianElement(){}
	~MedianElement(){}

	double Iterate_NthElement(std::vector<int> v, int begin, int end)
	{
		int N = end - begin + 1;
		int mid = begin + (N / 2);
		/*
		partition: use std::nth_element, which guarantees our mid is in the correct position of sorting the entire array,
		and none of the elements preceding nth are greater than it, and none of the elements following it are less
		*/
		std::nth_element(v.begin() + begin, v.begin() + mid, v.begin() + end + 1);

		if (N & 1)//odd count
			return v[mid];
		else//even count
		{
			int second = v[mid];
			/*
			partition: use std::nth_element, which guarantees our mid-1 is in the correct position of sorting the entire array,
			and none of the elements preceding nth are greater than it, and none of the elements following it are less
			*/
			std::nth_element(v.begin() + begin, v.begin() + mid - 1, v.begin() + end + 1);
			int first = v[mid - 1];
			return 0.5 * (first + second);
		}
	}

	double Iterate_NthElement(std::vector<int> v)
	{
		double res = this->Iterate_NthElement(v, 0, v.size() - 1);
		std::cout << "MedianElement Iterate_NthElement for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}

	double Iterate_QuickSelect(std::vector<int> v)
	{
		int N = v.size();

		double res;
		int rightMedian = this->QuickSelect(v, N / 2 + 1);//rightMedian's idx is N/2. Plus 1 to convert to 1-based idx.
		res = rightMedian;
		int leftMedian = 0;
		if ((N & 1) == 0)//even array
		{
			leftMedian = this->QuickSelect(v, N / 2);//leftMedian's idx is N/2-1. Plus 1 to convert to 1-based idx.
			res = 0.5 * (leftMedian + rightMedian);
		}

		std::cout << "MedianElement Iterate_QuickSelect for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}

	int QuickSelect(std::vector<int> v, int K)//K must be 1-based
	{
		int N = v.size();
		int lo = 0;
		int hi = N - 1;
		int res;
		
		while (lo <= hi)
		{
			int mid = (lo + hi) / 2;

			int pivotVal = v[mid];
			int pivot = std::partition(v.begin() + lo, v.begin() + hi + 1, [&](const int & a)
			{
				return a < pivotVal;
			}) - v.begin();
			for (int i = pivot; i <= hi; ++i)
				if (v[pivot] >= v[i])
					std::swap(v[pivot], v[i]);

			if (pivot - lo + 1 > K)
			{
				hi = pivot - 1;
			}
			else if (pivot - lo + 1 < K)
			{
				K -= (pivot - lo + 1);
				lo = pivot + 1;
			}
			else
			{
				res = v[pivot];
				break;
			}
		}

		return res;
	}
};
/*
MedianElement Iterate_NthElement for "34, 27, 78, 13, 49, 96, 9, 29, 96, 25, 37, 29, 78, 13, 69": 34
MedianElement Iterate_QuickSelect for "34, 27, 78, 13, 49, 96, 9, 29, 96, 25, 37, 29, 78, 13, 69": 34
MedianElement Iterate_NthElement for "40, 85, 63, 88, 7, 44, 81, 86, 94, 42, 55, 60, 20, 57, 16, 45": 56
MedianElement Iterate_QuickSelect for "40, 85, 63, 88, 7, 44, 81, 86, 94, 42, 55, 60, 20, 57, 16, 45": 56
MedianElement Iterate_NthElement for "9, 5, 33, 21, 55, 2, 23, 10, 14, 15, 25, 52, 13, 38, 98": 21
MedianElement Iterate_QuickSelect for "9, 5, 33, 21, 55, 2, 23, 10, 14, 15, 25, 52, 13, 38, 98": 21
MedianElement Iterate_NthElement for "61, 50, 81, 51, 62, 43, 86, 88, 91, 81, 9, 24, 44, 11, 88, 76": 61.5
MedianElement Iterate_QuickSelect for "61, 50, 81, 51, 62, 43, 86, 88, 91, 81, 9, 24, 44, 11, 88, 76": 61.5
MedianElement Iterate_NthElement for "98, 69, 73, 22, 20, 22, 79, 46, 7, 78, 67, 62, 79, 72, 8": 67
MedianElement Iterate_QuickSelect for "98, 69, 73, 22, 20, 22, 79, 46, 7, 78, 67, 62, 79, 72, 8": 67
MedianElement Iterate_NthElement for "5, 93, 93, 87, 52, 85, 48, 9, 98, 21, 7, 46, 65, 47, 99, 50": 51
MedianElement Iterate_QuickSelect for "5, 93, 93, 87, 52, 85, 48, 9, 98, 21, 7, 46, 65, 47, 99, 50": 51
MedianElement Iterate_NthElement for "48, 48, 46, 23, 92, 60, 36, 54, 81, 65, 46, 40, 17, 31, 96": 48
MedianElement Iterate_QuickSelect for "48, 48, 46, 23, 92, 60, 36, 54, 81, 65, 46, 40, 17, 31, 96": 48
MedianElement Iterate_NthElement for "93, 81, 57, 90, 22, 28, 66, 85, 14, 80, 11, 22, 55, 8, 12, 20": 41.5
MedianElement Iterate_QuickSelect for "93, 81, 57, 90, 22, 28, 66, 85, 14, 80, 11, 22, 55, 8, 12, 20": 41.5
MedianElement Iterate_NthElement for "27, 35, 87, 41, 94, 26, 69, 69, 22, 17, 71, 57, 97, 9, 83": 57
MedianElement Iterate_QuickSelect for "27, 35, 87, 41, 94, 26, 69, 69, 22, 17, 71, 57, 97, 9, 83": 57
MedianElement Iterate_NthElement for "98, 43, 92, 81, 34, 41, 61, 23, 87, 4, 23, 34, 94, 12, 65, 25": 42
MedianElement Iterate_QuickSelect for "98, 43, 92, 81, 34, 41, 61, 23, 87, 4, 23, 34, 94, 12, 65, 25": 42
*/
#endif