#ifndef INTERPOLATION_SEARCH_H
#define INTERPOLATION_SEARCH_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <math.h>
#include "Debug.h"
/*
Interpolation Search on sorted array.


*/
class InterpolationSearch
{
public:
	int Index_UpperBound(const std::vector<int> & A, int val)
	{
		int N = A.size();
		if (val < A[0])
		{
			std::cout << "InterpolationSearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << 0 << ", Out Of Range On Left" << std::endl;
			return 0;
		}
		if (val > A[N - 1])
		{
			std::cout << "InterpolationSearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << N << ", Out Of Range On Right" << std::endl;
			return N;
		}
		int left = 0;
		int right = N - 1;
		while (right - left > 1)
		{
			int middle = left + (val - A[left]) * (right - left) / (A[right] - A[left]);
			//std::cout << left << ", " << right << " -> " << middle << std::endl;
			if (middle == left)//no advance
			{
				if (left < right - 1 && A[left + 1] < val)//can advance "left" to next right, just continue
				{
					//std::cout << "A" << std::endl;
					++left;
				}
				else//cannot advance "left" to next right, need to break
				{
					if (A[left] != val && left < right - 1 && A[left + 1] == val)//1. current "left" is not val but next right is
					{
						//std::cout << "B" << std::endl;
						++left;//advance "left"
						while (left < right - 1 && A[left] == A[left + 1])
							++left;//get the rightmost duplicate
					}
					else//2. current "left" is val or not
					{
						//std::cout << "C" << std::endl;
						while (left < right - 1 && A[left] == A[left + 1])
							++left;//get the rightmost duplicate
					}
					right = left + 1;
					break;
				}
			}
			else if (A[middle] <= val)
				left = middle;
			else
				right = middle;
		}

		//now right is the upper bound of val (the index of the leftmost element that compares greater than val)

		if (A[left] == val)//val found, left points to the last duplicate
		{
			if (left == N - 1)
				++right;
			std::cout << "InterpolationSearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", Found Last Dup: " << left << std::endl;
			return right;
		}
		else//val in range but not found, [left,right] will be the [floor,ceil] index
		{
			std::cout << "InterpolationSearch Index_UpperBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", [Floor,Ceil]: [" << left << "," << right << "]=[" << A[left] << "," << A[right] << "]" << std::endl;
			return right;
		}
	}
	int Index_LowerBound(const std::vector<int> & A, int val)
	{
		int N = A.size();
		if (val < A[0])
		{
			std::cout << "InterpolationSearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << 0 << ", Out Of Range On Left" << std::endl;
			return 0;
		}
		if (val > A[N - 1])
		{
			std::cout << "InterpolationSearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << N << ", Out Of Range On Right" << std::endl;
			return N;
		}
		int left = 0;
		int right = N - 1;
		while (right - left > 1)
		{
			int middle = left + (val - A[left]) * (right - left) / (A[right] - A[left]);
			//std::cout << left << ", " << right << " -> " << middle << std::endl;
			if (middle == left)//no advance
			{
				if (left < right - 1 && A[left + 1] < val)//can advance "left" to next right, just continue
				{
					//std::cout << "A" << std::endl;
					++left;
				}
				else//cannot advance "left" to next right, need to break
				{
					if (A[left] != val && left < right - 1 && A[left + 1] == val)//1. current "left" is not val but next right is
					{
						//std::cout << "B" << std::endl;
						++left;//advance "left"
						while (left < right - 1 && A[left] == A[left + 1])
							++left;//get the rightmost duplicate
					}
					else//2. current "left" is val or not
					{
						//std::cout << "C" << std::endl;
						while (left < right - 1 && A[left] == A[left + 1])
							++left;//get the rightmost duplicate
					}
					right = left + 1;
					break;
				}
			}
			else if (A[middle] <= val)
				left = middle;
			else
				right = middle;
		}

		//now right is the upper bound of val (the index of the leftmost element that compares greater than val)

		if (A[left] == val)//val found, left points to the last duplicate
		{
			while (left > 0 && A[left] == A[left - 1])
				--left;
			std::cout << "InterpolationSearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << left << ", Found First Dup: " << left << std::endl;
			return left;
		}
		else//val in range but not found, [left,right] will be the [floor,ceil] index
		{
			std::cout << "InterpolationSearch Index_LowerBound for \"" << val << "\" from \"" << Debug::ToStr1D<int>()(A) << "\": " << right << ", [Floor,Ceil]: [" << left << "," << right << "]=[" << A[left] << "," << A[right] << "]" << std::endl;
			return right;
		}
	}

public:
	int Index(const std::vector<int> & A, int val)
	{
		int N = A.size();
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			if (A[left] == A[right])
			{
				if (A[left] == val)
				{
					std::cout << "InterpolationSearch for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << left << std::endl;
					return left;
				}
				else
				{
					std::cout << "InterpolationSearch for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << -1 << std::endl;
					return -1;
				}
			}

			double dist = (val - A[left]) / (A[right] - A[left]);
			if (dist < 0 || dist > 1)
			{
				std::cout << "InterpolationSearch for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << -1 << std::endl;
				return -1;
			}

			int mid = (int)std::round
				(left + dist * (right - left));
			if (val < A[mid])
				right = mid - 1;
			else if (val > A[mid])
				left = mid + 1;
			else
			{
				std::cout << "InterpolationSearch for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << mid << std::endl;
				return mid;
			}
		}

		std::cout << "InterpolationSearch for \"" << val << "\" in \"" << Debug::ToStr1D<int>()(A) << "\": " << -1 << std::endl;
		return -1;
	}
};
/*
InterpolationSearch Index_UpperBound for "8" from "2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 18, 20, 22, 24": 4, Found Last Dup: 3
InterpolationSearch Index_LowerBound for "21" from "2, 4, 6, 8, 10, 12, 13, 14, 15, 16, 18, 20, 22, 24": 12, [Floor,Ceil]: [11,12]=[20,22]
*/
#endif