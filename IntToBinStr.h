#ifndef _INT_TO_BIN_STR_H
#define _INT_TO_BIN_STR_H
#include <string>
#include <iostream>
#include <sstream>
#include "KeyGenAux.hpp"
/*
Convert an integer to binary string.
*/
class IntToBinStr//better (negative nums are represented as 2's complement)(same for IntToHexStr)
{
public:
	IntToBinStr() {}

	std::string Solve(int n)
	{
		if (n == 0) return "0";
		std::string res;
		for (int i = 0; i <= 31; ++i)//from lowest bit to highest bit
		{
			int cur = (n >> i);
			if (cur == 0) break;//early stop to skip extra leading 0s
			res = ((cur & 1) ? "1" : "0") + res;
		}

		std::cout << "IntToBinStr for \"" << n << "\": " << res << " (" << FullLength(n) << ")" << std::endl;
		return res;
	}

	std::string FullLength(int n)
	{
		if (n == 0) return "0";
		std::string res;
		for (int i = 0; i <= 31; ++i)//from lowest bit to highest bit
		{
			int cur = (n >> i);
			res = ((cur & 1) ? "1" : "0") + res;
		}
		return res;
	}
};
/*
IntToBinStr for "2147483647": 1111111111111111111111111111111 (01111111111111111111111111111111)
IntToBinStr for "2147483646": 1111111111111111111111111111110 (01111111111111111111111111111110)
IntToBinStr for "-2147483648": 10000000000000000000000000000000 (10000000000000000000000000000000)
IntToBinStr for "-2147483647": 10000000000000000000000000000001 (10000000000000000000000000000001)
IntToBinStr for "-3": 11111111111111111111111111111101 (11111111111111111111111111111101)
IntToBinStr for "3": 11 (00000000000000000000000000000011)
IntToBinStr for "-255": 11111111111111111111111100000001 (11111111111111111111111100000001)
IntToBinStr for "255": 11111111 (00000000000000000000000011111111)
IntToBinStr for "-4": 11111111111111111111111111111100 (11111111111111111111111111111100)
IntToBinStr for "4": 100 (00000000000000000000000000000100)
IntToBinStr for "-5": 11111111111111111111111111111011 (11111111111111111111111111111011)
IntToBinStr for "5": 101 (00000000000000000000000000000101)
*/
#endif
