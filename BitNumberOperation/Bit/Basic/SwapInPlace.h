#ifndef SWAP_IN_PLACE_H
#define SWAP_IN_PLACE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Cracking the coding interview: Moderate
*/
class SwapInPlace
{
public:
	SwapInPlace(){}
	~SwapInPlace(){}

	void XOR(int a, int b)
	{
		std::cout << "SwapInPlace XOR for \"" << a << "\", \"" << b << "\": ";
		a ^= b;
		b ^= a;//b^(a^b)=a
		a ^= b;//(a^b)^a=b
		std::cout << a << ", " << b << std::endl;
	}
	void ElementaryArithmetic(int a, int b)
	{
		std::cout << "SwapInPlace ElementaryArithmetic for \"" << a << "\", \"" << b << "\": ";
		a -= b;
		b += a;//b+(a-b)=a
		a -= b;//(a-b)-a=-b
		a = -a;
		std::cout << a << ", " << b << std::endl;
	}
};
/*
SwapInPlace XOR for "117", "2437": 2437, 117
SwapInPlace ElementaryArithmetic for "117", "2437": 2437, 117
*/
#endif