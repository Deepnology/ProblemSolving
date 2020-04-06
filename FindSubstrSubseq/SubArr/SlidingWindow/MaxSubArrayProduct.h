#ifndef MAX_SUB_ARRAY_PRODUCT_H
#define MAX_SUB_ARRAY_PRODUCT_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Maximum Product Subarray
http://www.geeksforgeeks.org/maximum-product-subarray/
Given an array that contains both positive and negative integers.
Find the maximum product of contiguous subarray.
O(n) time, O(1) space

See also MaxProductOf3.h, MultiplicationOfNums.h
*/
class MaxSubArrayProduct
{
public:
	MaxSubArrayProduct(){}
	~MaxSubArrayProduct(){}

	int DP(const std::vector<int> & A)
	{
		int N = A.size();
		int maxProduct = A[0];
		int curMaxProduct = A[0];
		int curMinProduct = A[0];

		for (int i = 1; i < N; ++i)
		{
			int prevMaxProduct = curMaxProduct;
			int prevMinProduct = curMinProduct;
			curMaxProduct = std::max(std::max(prevMaxProduct * A[i], prevMinProduct * A[i]), A[i]);
			curMinProduct = std::min(std::min(prevMaxProduct * A[i], prevMinProduct * A[i]), A[i]);
			maxProduct = std::max(maxProduct, curMaxProduct);
		}
		std::cout << "MaxSubArrayProduct DP for \"" << Debug::ToStr1D<int>()(A) << "\": " << maxProduct << std::endl;
		return maxProduct;
	}

	int DP_2Scans(const std::vector<int> & A, int & begin, int & end)
	{
		int N = A.size();
		int curSubarrProduct = 1;
		int maxProduct = INT_MIN;
		int tmpBegin = 0;
		end = 0;
		std::vector<int> dpLeftToRight(N);//for debugging only
		std::vector<int> dpRightToLeft(N);//for debugging only
		//accumulated product from left to right
		for (int i = 0; i < N; ++i)
		{
			dpLeftToRight[i] = curSubarrProduct * A[i];//for debugging only

			if (curSubarrProduct * A[i] > maxProduct)
			{
				maxProduct = curSubarrProduct * A[i];
				begin = tmpBegin;
				end = i;
			}
			if (A[i] != 0)
				curSubarrProduct *= A[i];
			else
			{
				curSubarrProduct = 1;//reset
				tmpBegin = i + 1;//reset
			}
		}
		//accumulated product from right to left
		curSubarrProduct = 1;
		tmpBegin = N - 1;
		for (int i = N - 1; i >= 0; --i)
		{
			dpRightToLeft[i] = curSubarrProduct * A[i];//for debugging only

			if (curSubarrProduct * A[i] > maxProduct)
			{
				maxProduct = curSubarrProduct * A[i];
				begin = tmpBegin;
				end = i;
			}
			if (A[i] != 0)
				curSubarrProduct *= A[i];
			else
			{
				curSubarrProduct = 1;//reset
				tmpBegin = i - 1;//reset
			}
		}

		if (maxProduct == 0)//special cases: all non-zero numbers are individual negative isolated by 0(s) OR all 0(s)
			for (int i = 0; i < N; ++i)
				if (A[i] == 0)
				{
					begin = i;
					end = i;
					break;
				}

		if (begin > end)
			std::swap(begin, end);

		std::cout << "DP LeftToRight: " << Debug::ToStr1D<int>()(dpLeftToRight) << std::endl;
		std::cout << "DP RightToLeft: " << Debug::ToStr1D<int>()(dpRightToLeft) << std::endl;
		std::cout << "MaxSubArrayProduct DP_2Scans for \"" << Debug::ToStr1D<int>()(A) << "\": " << maxProduct << " in [" << begin << "," << end << "]" << std::endl;
		return maxProduct;
	}
};
/*
MaxSubArrayProduct DP for "0, 0, 0": 0
DP LeftToRight: 0, 0, 0
DP RightToLeft: 0, 0, 0
MaxSubArrayProduct DP_2Scans for "0, 0, 0": 0 in [0,0]
MaxSubArrayProduct DP for "0, -1": 0
DP LeftToRight: 0, -1
DP RightToLeft: 0, -1
MaxSubArrayProduct DP_2Scans for "0, -1": 0 in [0,0]
MaxSubArrayProduct DP for "-1, 0": 0
DP LeftToRight: -1, 0
DP RightToLeft: -1, 0
MaxSubArrayProduct DP_2Scans for "-1, 0": 0 in [1,1]
MaxSubArrayProduct DP for "0, -2, 0": 0
DP LeftToRight: 0, -2, 0
DP RightToLeft: 0, -2, 0
MaxSubArrayProduct DP_2Scans for "0, -2, 0": 0 in [0,0]
MaxSubArrayProduct DP for "-1, 0, -2": 0
DP LeftToRight: -1, 0, -2
DP RightToLeft: -1, 0, -2
MaxSubArrayProduct DP_2Scans for "-1, 0, -2": 0 in [1,1]
MaxSubArrayProduct DP for "2, -7, 0, 2, 3, 8, -6, 5": 48
DP LeftToRight: 2, -14, 0, 2, 6, 48, -288, -1440
DP RightToLeft: -14, -7, 0, -1440, -720, -240, -30, 5
MaxSubArrayProduct DP_2Scans for "2, -7, 0, 2, 3, 8, -6, 5": 48 in [3,5]
MaxSubArrayProduct DP for "2, -7, 0, 2, 3, 8, -6, 5, -1": 1440
DP LeftToRight: 2, -14, 0, 2, 6, 48, -288, -1440, 1440
DP RightToLeft: -14, -7, 0, 1440, 720, 240, 30, -5, -1
MaxSubArrayProduct DP_2Scans for "2, -7, 0, 2, 3, 8, -6, 5, -1": 1440 in [3,8]
MaxSubArrayProduct DP for "0, -5, 9, -8, -9, 8, 0, -7, 9, -2, 1, -1, -8, -1, 1": 5184
DP LeftToRight: 0, -5, -45, 360, -3240, -25920, 0, -7, -63, 126, 126, -126, 1008, -1008, -1008
DP RightToLeft: 0, -25920, 5184, 576, -72, 8, 0, -1008, 144, 16, -8, -8, 8, -1, 1
MaxSubArrayProduct DP_2Scans for "0, -5, 9, -8, -9, 8, 0, -7, 9, -2, 1, -1, -8, -1, 1": 5184 in [2,5]
*/
#endif