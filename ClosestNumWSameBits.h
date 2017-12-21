/*MUST*/
#ifndef CLOSEST_NUM_W_SAME_BITS_H
#define CLOSEST_NUM_W_SAME_BITS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, PrimitiveTypes: Find a closest integer with the same weight

Write a function which takes as input an unsigned 64-bit integer x and returns y != x such that y has the same weight as x, and the difference of x and y is as small as possible.
You can assume x is not 0, or all 1s, i.e., 2^64 - 1.

O(n) time, where n is the number of bits.

See also NextPrevNumWSameBits.h
*/
class ClosestNumWSameBits
{
public:
	ClosestNumWSameBits(){}
	~ClosestNumWSameBits(){}

	unsigned long long Solve(unsigned long long n)
	{
		unsigned long long res = n;
		for (int i = 0; i < 63; ++i)
		{
			//swap the first 2 consecutive bits that diff from right
			if (((res >> i) & 1) ^ ((res >> (i + 1)) & 1))
			{
				res ^= (1UL << i) | (1UL << (i + 1));
				break;
			}
		}

		if (res == n)
			std::cout << "ClosestNumWSameBits for \"" << n << "\": invalid input of all 0s or all 1s, " << n << std::endl;
		else
			std::cout << "ClosestNumWSameBits for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
NextPrevNumWSameBits GetNext for "00000000000000000011011001111100(13948)": 00000000000000000011011010001111(13967)
NextPrevNumWSameBits GetPrev for "00000000000000000011011001111100(13948)": 00000000000000000011011001111010(13946)
NextPrevNumWSameBits GetNext for "00000000000000000010011110000011(10115)": 00000000000000000010011110000101(10117)
NextPrevNumWSameBits GetPrev for "00000000000000000010011110000011(10115)": 00000000000000000010011101110000(10096)
ClosestNumWSameBits for "13948": 13946
ClosestNumWSameBits for "10115": 10117
*/
#endif