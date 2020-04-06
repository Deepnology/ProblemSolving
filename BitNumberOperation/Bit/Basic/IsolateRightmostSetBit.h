#ifndef ISOLATE_RIGHTMOST_SET_BIT_H
#define ISOLATE_RIGHTMOST_SET_BIT_H
#include <string>
#include <sstream>
#include <iostream>
/*
Given an integer.
Flip all the set bits except the rightmost one.

For example, n = 01001100.
Compute -n as two's complement: ~n + 1 = 10110011 + 1 = 10110100.
Therefore, (n & -n) isolates the rightmost set bit.

See also MaskOfTrailingZeros.h
*/
class IsolateRightmostSetBit
{
public:
	IsolateRightmostSetBit(){}
	~IsolateRightmostSetBit(){}

	int Solve(int n)
	{
		int res = n & -n;
		std::cout << "IsolateRightmostSetBit for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Solve2(int n)
	{
		int res = n & (~n + 1);
		std::cout << "IsolateRightmostSetBit2 for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Solve3(int n)
	{
		int res = n & ~(n - 1);
		std::cout << "IsolateRightmostSetBit3 for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Solve4(int n)
	{
		int res = n & (n^(n - 1));
		std::cout << "IsolateRightmostSetBit4 for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
IsolateRightmostSetBit for "56": 8
IsolateRightmostSetBit2 for "56": 8
IsolateRightmostSetBit3 for "56": 8
IsolateRightmostSetBit4 for "56": 8
*/
#endif