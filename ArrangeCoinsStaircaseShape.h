#ifndef ARRANGE_COINS_STAIRCASE_SHAPE_H
#define ARRANGE_COINS_STAIRCASE_SHAPE_H
#include "Debug.h"
/*
Leetcode: Arranging Coins
You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.
Given n, find the total number of full staircase rows that can be formed.
n is a non-negative integer and fits within the range of a 32-bit signed integer.
Example 1:
n = 5
The coins can form the following rows:
@
@@
@@
Because the 3rd row is incomplete, we return 2.
Example 2:
n = 8
The coins can form the following rows:
@
@@
@@@
@@
Because the 4th row is incomplete, we return 3.
*/
class ArrangeCoinsStaircaseShape
{
public:
	ArrangeCoinsStaircaseShape() {}

	int BinarySearch(int n)
	{
		//sum of arithmetic progression in [1:n] = (1+n)*n/2
		//find the max num k that (1+k)*k/2 <= n
		//find the upper bound-1
		long long N = n;
		long long left = 1;
		long long right = n;
		while (left <= right)
		{
			long long mid = (left + right) / 2;
			if ((1 + mid)*mid <= 2 * N)
				left = mid + 1;
			else
				right = mid - 1;
		}

		std::cout << "ArrangeCoinsStaircaseShape BinarySearch for \"" << n << "\": " << left - 1 << std::endl;
		return (int)(left - 1);
	}
};
/*
ArrangeCoinsStaircaseShape BinarySearch for "5": 2
ArrangeCoinsStaircaseShape BinarySearch for "8": 3
*/
#endif
