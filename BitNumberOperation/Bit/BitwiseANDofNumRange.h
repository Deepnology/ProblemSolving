#ifndef BITWISE_AND_OF_NUM_RANGE_H
#define BITWISE_AND_OF_NUM_RANGE_H
#include <iostream>
#include <string>
#include "Debug.h"
/*
Leetcode: Bitwise AND of Numbers Range
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
For example, given the range [5, 7], you should return 4.

[26, 30]
00011010¡@¡@00011011¡@¡@00011100¡@¡@00011101¡@¡@00011110
Bitwise AND of all nums in range [26, 30] is 00011000.
The common left bits will be kept, and all the rest bits will be 0s.
*/
class BitwiseANDofNumRange
{
public:
	BitwiseANDofNumRange(){}
	~BitwiseANDofNumRange(){}

	int Solve(int m, int n)
	{
		int mask = INT_MAX;//all 1s

		//find the longest common left bits in m and n
		//these common left bits will be kept after bitwise AND (and all the rest bits will be 0s)
		while ((m & mask) != (n & mask))
		{
			mask <<= 1;
		}
		int res = m & mask;

		std::cout << "BitwiseANDofNumRange for \"" << m << "\", \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Solve2(int m, int n)
	{
		int mm = m, nn = n;

		//right shift both m and n until they are equal. keep track of count
		int count = 0;
		while (m != n)
		{
			m >>= 1;
			n >>= 1;
			++count;
		}
		int res = m << count;//insert count of 0s to the right
		std::cout << "BitwiseANDofNumRange2 for \"" << mm << "\", \"" << nn << "\": " << res << std::endl;

		return res;
	}

	//O(n) time
	//n & (n-1): set the rightmost set-bit to 0
	int Solve_Linear(int m, int n)
	{
		while (m < n)
		{
			n = n & (n - 1);
		}
		int res = m & n;

		std::cout << "BitwiseANDofNumRange Linear for \"" << m << " and " << n << "\": " << res << std::endl;
		return res;
	}
};
/*
BitwiseANDofNumRange for "26", "30": 24
BitwiseANDofNumRange2 for "26", "30": 24
BitwiseANDofNumRange Linear for "26 and 24": 24
*/
#endif