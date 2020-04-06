#ifndef X_POW_Y_MOD_Z_H
#define X_POW_Y_MOD_Z_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Debug.h"
/*
http://www.careercup.com/question?id=22767685
https://sites.google.com/site/spaceofjameschen/annnocements/calculatexyzwithoutpow--google
Calculate (x^y)%z without pow()

use binary weighted power computation method
*/
class XpowYmodZ
{
public:
	XpowYmodZ(){}
	~XpowYmodZ(){}

	//O(logy) time, see also Pow.h
	int BinaryIterate(int x, int y, int z)
	{
		int base = x;
		int res = 1;
		for (int i = abs(y); i > 0; i /= 2)/*i >>= 1*/
		{
			if (i % 2 == 1)/*i & 1 == 1*/
				res = (res * base) % z;

			base = (base * base) % z;
		}

		if (y < 0)
			res = 1 / res;

		std::cout << "XpowYmodZ BinaryIterate for \"" << x << " pow " << y << " mod " << z << "\": " << res << std::endl;
		return res;
	}

	//O(y) time
	int Iterate(int x, int y, int z)
	{
		int res = 1;
		for (int i = 0; i < abs(y); ++i)
		{
			res = (res * x) % z;
		}

		if (y < 0)
			res = 1 / res;

		std::cout << "XpowYmodZ Iterate for \"" << x << " pow " << y << " mod " << z << "\": " << res << std::endl;
		return res;
	}

	//O(y) time
	int Recur(int x, int y, int z)
	{
		int res = this->recur(x, abs(y), z);

		if (y < 0)
			res = 1 / res;

		std::cout << "XpowYmodZ Recur for \"" << x << " pow " << y << " mod " << z << "\": " << res << std::endl;
		return res;
	}
	int recur(int x, int y, int z)
	{
		if (y == 1)
			return x % z;

		return this->recur(x, y - 1, z) * (x % z) % z;
	}
};
/*
XpowYmodZ BinaryIterate for "7 pow 1 mod 5": 2
XpowYmodZ Iterate for "7 pow 1 mod 5": 2
XpowYmodZ Recur for "7 pow 1 mod 5": 2
XpowYmodZ BinaryIterate for "7 pow 2 mod 5": 4
XpowYmodZ Iterate for "7 pow 2 mod 5": 4
XpowYmodZ Recur for "7 pow 2 mod 5": 4
XpowYmodZ BinaryIterate for "7 pow 3 mod 5": 3
XpowYmodZ Iterate for "7 pow 3 mod 5": 3
XpowYmodZ Recur for "7 pow 3 mod 5": 3
XpowYmodZ BinaryIterate for "7 pow 4 mod 5": 1
XpowYmodZ Iterate for "7 pow 4 mod 5": 1
XpowYmodZ Recur for "7 pow 4 mod 5": 1
XpowYmodZ BinaryIterate for "7 pow 5 mod 5": 2
XpowYmodZ Iterate for "7 pow 5 mod 5": 2
XpowYmodZ Recur for "7 pow 5 mod 5": 2
*/
#endif