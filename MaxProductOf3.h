#ifndef _MAX_PRODUCT_OF_3_H
#define _MAX_PRODUCT_OF_3_H
#include <iostream>
#include <string>
#include <sstream>
#include "Debug.h"
/*
Leetcode: Maximum Product of Three
Elements of programming interview, Array: Compute the maximum product of all but one entries
Given an array of integers (can be both +ve or -ve), find the three integers which multiply to give the largest product.
Find the 3 maximum elements and 2 minimum elements, max will be max(max1*max2*max3,max1*min1*min2).

See also MultiplicationOfNums.h, MaxSubArrayProduct.h
*/
class MaxProductOf3
{
public:
	MaxProductOf3(){}
	~MaxProductOf3(){}

	//O(n) time, O(1) space
	int OneScan(int A[], int n)
	{
		std::vector<int> max3(3, INT_MIN);
		std::vector<int> min2(2, INT_MAX);
 
		for(int i = 0; i < n; ++i)
		{
			/*find two smallest numbers*/
			if (A[i] < min2[0])//A[i] < smallest
			{
				min2[1] = min2[0];
				min2[0] = A[i];
			}
			else if (A[i] < min2[1])//A[i] < 2nd smallest
			{
				min2[1] = A[i];
			}
			
			/*find three largest numbers*/
			if (A[i] > max3[0])//A[i] > largest
			{
				max3[2] = max3[1];
				max3[1] = max3[0];
				max3[0] = A[i];
			}
			else if (A[i] > max3[1])//A[i] > 2nd largest
			{
				max3[2] = max3[1];
				max3[1] = A[i];
			}
			else if (A[i] > max3[2])//A[i] > 3rd largest
			{
				max3[2] = A[i];
			}
		}
		int res = std::max(max3[0] * max3[1] * max3[2], max3[0] * min2[0] * min2[1]);
		std::cout << "MaxProductOf3 OneScan for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << res << ". max(" << max3[0] << "*" << max3[1] << "*" << max3[2] << ", " << max3[0] << "*" << min2[0] << "*" << min2[1] << ")" << std::endl;
		return res;
	}

	//O(nlongn) time, O(1) space
	int Sort(int A[], int n)
	{
		std::sort(A, A + n);
		int res = std::max(A[n - 1] * A[n - 2] * A[n - 3], A[n - 1] * A[0] * A[1]);
		std::cout << "MaxProductOf3 Sort for \"" << Debug::ToStr1D<int>()(A, n) << "\": " << res << ". max(" << A[n - 1] << "*" << A[n - 2] << "*" << A[n - 3] << ", " << A[n - 1] << "*" << A[0] << "*" << A[1] << ")" << std::endl;
		return res;
	}
};
/*
MaxProductOf3 OneScan for "-6, -1, 2, -5, -4, -3, 7, 3, 1, 2": 210. max(7*3*2, 7*-6*-5)
MaxProductOf3 OneScan for "-6, -1, -2, -5, -4, -3, -7, -10, -8, -9": -6. max(-1*-2*-3, -1*-10*-9)
MaxProductOf3 Sort for "-6, -5, -4, -3, -1, 1, 2, 2, 3, 7": 210. max(7*3*2, 7*-6*-5)
MaxProductOf3 Sort for "-10, -9, -8, -7, -6, -5, -4, -3, -2, -1": -6. max(-1*-2*-3, -1*-10*-9)
*/
#endif


