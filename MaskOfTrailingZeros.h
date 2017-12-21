#ifndef MASK_OF_TRAILING_ZEROS_H
#define MASK_OF_TRAILING_ZEROS_H
#include <string>
#include <sstream>
#include <iostream>
/*
The mask of trailing zeros is an integer with corresponding trailing 1s.
We can first isolate the rightmost set bit (n & -n), then subtract it by 1.

See also IsolateRightmostSetBit.h
*/
class MaskOfTrailingZeros
{
public:
	MaskOfTrailingZeros(){}
	~MaskOfTrailingZeros(){}

	int Solve(int n)
	{
		int res = (n & -n) - 1;
		std::cout << "MaskOfTrailingZeros for \"" << n << "\": " << res << std::endl;
		return res;
	}
};
/*
MaskOfTrailingZeros for "56": 7
*/
#endif