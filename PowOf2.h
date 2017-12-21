#ifndef POW_OF_2_H
#define POW_OF_2_H
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
/*
Leetcode: Power of Two
Cracking the coding interview 5.4
Check if integer n is a power of 2: 
n & (n - 1) != 0: n is NOT a power of 2
n & (n - 1) == 0: n is a power of 2

n & (n - 1): flip the lowest set bit to 0
n			1101011000
n-1			1101010111
n&(n-1)		1101010000

See also DiffBitsBtw2Int.h
*/
class PowOf2
{
public:
	PowOf2(){}
	~PowOf2(){}

	bool Valid(int n)
	{
		bool res;

		if (n == 0)
			res = false;
		else
			res = (n & (n - 1)) == 0 ? true : false;

		std::cout << "PowOf2 Valid for \"" << n << "\": " << res << std::endl;
		return res;
	}

	int TwoToThePowerOfN(int N)
	{
		int res = 1 << N;
		std::cout << "PowOf2 2 To The Power Of \"" << N << "\": " << res << std::endl;
		return res;
	}
};
/*
PowOf2 Valid for "32": 1
PowOf2 Valid for "37": 0
PowOf2 2 To The Power Of "0": 1
PowOf2 2 To The Power Of "1": 2
PowOf2 2 To The Power Of "7": 128
PowOf2 2 To The Power Of "10": 1024
*/
#endif