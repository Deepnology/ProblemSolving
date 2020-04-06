#ifndef LONGEST_CONTINUOUS_BINARY_0S_H
#define LONGEST_CONTINUOUS_BINARY_0S_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
Google
http://www.careercup.com/question?id=4860021380743168
http://www.quora.com/Algorithms/How-can-we-find-the-longest-continuous-subsequence-of-0s-in-binary-representation-of-an-integer-in-O-log-n-time-complexity
http://ideone.com/unp7hD
Find the lenght of longest continuous 0s of the binary representation of a given integer.

Log32: O(logn) time, where n is the number of bits of the input number, which equals to 32 for an unsigned int (see quora)
Linear: O(n) time, where n is the number of bits of the input number, which equals to 32 for an unsigned int
*/
class LongestContinuousBinary0s
{
public:
	LongestContinuousBinary0s(){}
	~LongestContinuousBinary0s(){}

	int Solve_Log32Time(unsigned int n)
	{
		if (n == 0)
			return 8*sizeof(n);
		if (n == ~0)
			return 0;
		std::cout << "input:		" << KeyGenAux().UIntToBinStr(n) << std::endl;
		/*
		1. flip the rightmost digit of each continuous 0s segment from 0 to 1 by n |= n << 1
		Note that when n's rightmost digit is 0, n |= n << 1 won't flip the rightmost digit of the rightmost continuous 0s segment,
		so we flip the rightmost digit of the rightmost continuous 0s segment from 0 to 1 manually,
		and this won't affect the case when n's rightmost digit is 1
		*/
		
		int lo;
		int hi = 1;

		unsigned int state = n | n << hi | 1;

		std::cout << "flip " << hi << " 0s:	" << KeyGenAux().UIntToBinStr(state) << std::endl;

		if (state == ~0)
			return hi;

		/*
		2. then speed up by flipping 2, 4, 8, 16, 32 0s to the rightmost digit of each continuous 0s segment until n becomes all 1s
		*/

		while (true)
		{
			hi *= 2;
			unsigned int after = state | state << (hi / 2);//flip (hi/2) 0s to previous state
			std::cout << "flip " << hi << " 0s:	" << KeyGenAux().UIntToBinStr(after) << std::endl;
			if (after == ~0)
				break;
			state = after;
		}
		lo = hi / 2;
		int lo2 = lo;
		/*
		3. when n becomes all 1s, it means the longest continuous 0s segment has been filled with 1s
		the actual flip count of 0s must be some number in between one of these ranges: [1], (1,2], (2,4], (4,8], (8, 16], (16, 32]
		perform binary search in (lo, hi] to find out the flip count of 0s that makes n to be all 1s
		*/

		std::cout << "floor, ceil: " << lo << ", " << hi << std::endl;
		
		while (hi - lo > 1)
		{
			int mid = lo + (hi - lo) / 2;
			unsigned int after = state | state << (mid - lo2);//flip (mid-lo2) 0s to floor state
			std::cout << "flip " << mid << " 0s:	" << KeyGenAux().UIntToBinStr(after) << std::endl;
			if (after == ~0)//already all 1s => too much => next search left side
				hi = mid;
			else//not yet all 1s => not enough => next search right side
				lo = mid;
		}
		std::cout << "LongestContinuousBinary0s O(logn) for \"" << n << "\": " << hi << std::endl;
		return hi;
	}


	int Solve_Linear32Time(unsigned int n)
	{
		std::string before = KeyGenAux().UIntToBinStr(n);
		int maxLen = 0;
		int curLen = 0;
		while (n > 0)
		{
			if (n % 2 == 1)
				curLen = 0;
			else
				++curLen;

			if (curLen > maxLen)
				maxLen = curLen;

			n /= 2;
		}

		std::cout << "LongestContinuousBinary0s O(n) for \"" << before << "\": " << maxLen << std::endl;
		return maxLen;
	}
};
/*
input:		01101111000000010001110011000010
flip 1 0s:	11111111000000110011110111000111
flip 2 0s:	11111111000001110111111111001111
flip 4 0s:	11111111000111111111111111111111
flip 8 0s:	11111111111111111111111111111111
floor, ceil: 4, 8
flip 6 0s:	11111111011111111111111111111111
flip 7 0s:	11111111111111111111111111111111
LongestContinuousBinary0s O(logn) for "1862343874": 7
LongestContinuousBinary0s O(n) for "01101111000000010001110011000010": 7
*/
#endif