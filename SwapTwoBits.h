#ifndef SWAP_TWO_BITS_H
#define SWAP_TWO_BITS_H
#include <string>
#include <sstream>
#include <iostream>
/*
A collection of bit programming
Elements of programming interview, PrimitiveTypes: Swap bits

O(1) time
*/
class SwapTwoBits
{
public:
	SwapTwoBits(){}
	~SwapTwoBits(){}

	int Solve(int n, int idx1, int idx2)
	{
		int res;
		if (idx1 == idx2)
			res = n;
		else
		{
			int xor = ((n >> idx1) ^ (n >> idx2)) & 1;/*the xor of the two isolated-bit numbers. 1: different, 0: same*/
			res = n ^ (xor << idx1) ^ (xor << idx2);
			/*
			The irrelevant bits xor 0s will remain unchanged.
			The target bit xor 0 will remain unchanged.
			The target bit xor 1 will be flippped.
			*/
		}

		std::cout << "SwapTwoBits for \"" << idx1 << "-th\" and \"" << idx2 << "-th\" bits in \"" << n << "\": " << res << std::endl;
		return res;
	}

	int Solve2(int n, int idx1, int idx2)
	{
		int res = n;
		if (((n >> idx1) & 1) != ((n >> idx2) & 1))
		{
			/*
			when the idx1 bit is diff from the idx2 bit, i.e., one is 1 and the other is 0
			, flip the two bits individually by XOR with bit 1
			*/
			res ^= (1 << idx1) | (1 << idx2);
		}

		std::cout << "SwapTwoBits2 for \"" << idx1 << "-th\" and \"" << idx2 << "-th\" bits in \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
SwapTwoBits for "4-th" and "1-th" bits in "56": 42
SwapTwoBits2 for "4-th" and "1-th" bits in "56": 42
*/
#endif