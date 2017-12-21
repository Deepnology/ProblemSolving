#ifndef SWAP_ODD_EVEN_BITS_H
#define SWAP_ODD_EVEN_BITS_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
#include "KeyGenAux.hpp"
/*
http://www.geeksforgeeks.org/swap-all-odd-and-even-bits/
Cracking the coding interview 5.6
Mask all odd bits with 10101010 (0xaa) then shift them right
Mask all even bits with 01010101 (0x55) then shift them left
Then add the two integers
*/
class SwapOddEvenBits
{
public:
	SwapOddEvenBits(){}
	~SwapOddEvenBits(){}

	int Solve(int num)
	{
		int res = ((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1);
		std::cout << "SwapOddEvenBits for \"" << KeyGenAux().UIntToBinStr(num) << "\": " << KeyGenAux().UIntToBinStr(res) << std::endl;
		return res;
	}
};
/*
SwapOddEvenBits for "00000000000000001001011101000001": 00000000000000000110101110000010
*/
#endif