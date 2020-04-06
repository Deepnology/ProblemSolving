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
class MaxProductOfK
{
public:
    MaxProductOfK(){}

    int SortGreedy(std::vector<int> && v, int k)
    {
        std::sort(v.begin(), v.end());
        int N = v.size();
        int res = 1;
        int left = 0;
        int right = N-1;
        int count = k;
        while (count > 0)
        {
            if (count % 2 == 1)//odd
            {
                res *= v[right--];
                --count;
            }
            else//even
            {
                if (v[left]*v[left+1] > v[right-1]*v[right])
                {
                    res *= v[left++];
                    res *= v[left++];
                }
                else
                {
                    res *= v[right--];
                    res *= v[right--];
                }
                count -= 2;
            }
        }

        std::cout << "MaxProductOfK SortGreedy for k=" << k << ", from [" << Debug::ToStr1D<int>()(v) << "]: " << res << std::endl;
        return res;
    }
};
/*
MaxProductOf3 OneScan for "-6, -1, 2, -5, -4, -3, 7, 3, 1, 2": 210. max(7*3*2, 7*-6*-5)
MaxProductOf3 OneScan for "-6, -1, -2, -5, -4, -3, -7, -10, -8, -9": -6. max(-1*-2*-3, -1*-10*-9)
MaxProductOf3 Sort for "-6, -5, -4, -3, -1, 1, 2, 2, 3, 7": 210. max(7*3*2, 7*-6*-5)
MaxProductOf3 Sort for "-10, -9, -8, -7, -6, -5, -4, -3, -2, -1": -6. max(-1*-2*-3, -1*-10*-9)

MaxProductOfK SortGreedy for k=5, from [-7, -7, -4, -3, -3, -2, -1, 7]: 4116
MaxProductOfK SortGreedy for k=1, from [-9, -9, -7, -5, -2, 0, 5, 6]: 6
MaxProductOfK SortGreedy for k=7, from [-8, -5, -4, -3, -3, 1, 1, 2]: 960
MaxProductOfK SortGreedy for k=3, from [-7, -6, -3, -2, 1, 5, 8, 8]: 336
MaxProductOfK SortGreedy for k=1, from [-8, -7, -4, 0, 1, 1, 3, 8]: 8
MaxProductOfK SortGreedy for k=5, from [-9, -5, -2, 3, 3, 4, 6, 9]: 9720
MaxProductOfK SortGreedy for k=4, from [-6, -6, -2, 0, 3, 4, 8, 8]: 2304
MaxProductOfK SortGreedy for k=2, from [-7, -5, -3, -3, 1, 2, 6, 8]: 48
MaxProductOfK SortGreedy for k=5, from [-9, -6, -6, -4, 0, 2, 4, 6]: 7776
MaxProductOfK SortGreedy for k=1, from [-7, -4, -4, -2, 0, 0, 2, 4]: 4
MaxProductOfK SortGreedy for k=6, from [-9, -1, 3, 4, 7, 7, 8, 9]: 42336
MaxProductOfK SortGreedy for k=2, from [-9, -8, -7, -1, 0, 4, 7, 9]: 72
MaxProductOfK SortGreedy for k=4, from [-8, -6, -6, -2, 1, 3, 8, 9]: 3456
MaxProductOfK SortGreedy for k=1, from [-7, -5, -5, -4, -2, 0, 3, 4]: 4
MaxProductOfK SortGreedy for k=6, from [-9, -5, -5, -3, -1, 3, 5, 8]: 27000
MaxProductOfK SortGreedy for k=3, from [-7, -6, -3, 0, 0, 0, 7, 8]: 336
MaxProductOfK SortGreedy for k=6, from [-7, -4, -3, 1, 2, 4, 4, 9]: 8064
MaxProductOfK SortGreedy for k=4, from [-6, -3, -2, -2, 1, 3, 6, 9]: 972
MaxProductOfK SortGreedy for k=1, from [-8, -5, -3, -2, 0, 6, 7, 9]: 9
MaxProductOfK SortGreedy for k=2, from [-9, -9, -6, -4, -1, 1, 7, 8]: 81
MaxProductOfK SortGreedy for k=4, from [-4, -2, 3, 3, 5, 5, 7, 8]: 1400
MaxProductOfK SortGreedy for k=4, from [-1, -1, 0, 0, 1, 8, 8, 8]: 512
MaxProductOfK SortGreedy for k=3, from [-8, -6, -3, -2, 2, 3, 5, 8]: 384
MaxProductOfK SortGreedy for k=5, from [-9, -9, -4, -2, -2, 4, 6, 6]: 11664
MaxProductOfK SortGreedy for k=5, from [-8, 1, 1, 3, 4, 6, 7, 8]: 4032
MaxProductOfK SortGreedy for k=7, from [-8, -8, -6, -5, -3, 2, 8, 9]: 276480
MaxProductOfK SortGreedy for k=3, from [-9, -4, -3, -2, 0, 2, 5, 6]: 216
MaxProductOfK SortGreedy for k=4, from [-6, 1, 1, 2, 2, 6, 9, 9]: 972
MaxProductOfK SortGreedy for k=5, from [-9, -7, -6, -4, 1, 2, 7, 9]: 13608
MaxProductOfK SortGreedy for k=3, from [-4, -3, -2, -1, 0, 2, 3, 6]: 72
*/
#endif


