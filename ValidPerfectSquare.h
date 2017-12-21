#ifndef VALID_PERFECT_SQUARE_H
#define VALID_PERFECT_SQUARE_H
#include <iostream>
#include <string>
#include <math.h>
/*
Leetcode: Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.
Note: Do not use any built-in library function such as sqrt.

see also Sqrtx.h, IndexOfOnlyOneSetBit.h, Divide2IntWoMulDivMod.h
*/
class ValidPerfectSquare
{
public:
	ValidPerfectSquare() {}
	~ValidPerfectSquare() {}

	bool BinarySearch(int n)
	{
		long long left = 1;
		//long long right = n;//also works, but slower
		long long right = (n >> 1) + 1;//n/2+1
		//find the lower bound
		while (left <= right)
		{
			long long mid = left + ((right - left) >> 1);//left+(right-left)/2
			long long square = mid * mid;
			if (square >= n)
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is the lower bound
		bool res = (left*left == n);
		std::cout << "ValidPerfectSquare BinarySearch for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
ValidPerfectSquare BinarySearch for "60652962": 0
ValidPerfectSquare BinarySearch for "60652944": 1
*/
#endif
