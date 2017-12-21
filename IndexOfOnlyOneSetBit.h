#ifndef	INDEX_OF_ONLY_ONE_SET_BIT_H
#define INDEX_OF_ONLY_ONE_SET_BIT_H
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>
/*
Given an unsigned number with only one bit set.
Find the position of this bit.

If there is only one bit set, then the number must be a power of 2.
For identifying the position set we can AND the number with an appropriate bitmask.
*/
class IndexOfOnlyOneSetBit
{
public:
	IndexOfOnlyOneSetBit(){}
	~IndexOfOnlyOneSetBit(){}

	int Iterate(unsigned int n)
	{
		if ((n & (n - 1)) != 0)/*n is not a power of 2*/
			return -1;

		int idx = 0;
		while ((n & (1 << idx)) == 0)
		{
			++idx;
		}
		std::cout << "IndexOfOnlyOneSetBit Iterate for \"" << n << "\": " << idx << std::endl;
		return idx;
	}

	int Log(unsigned int n)
	{
		if ((n & (n - 1)) != 0)/*n is not a power of 2*/
			return -1;

		int res = (int)((log((double)n)) / log(2.0));

		std::cout << "IndexOfOnlyOneSetBit Log for \"" << n << "\": " << res << std::endl;
		return res;
	}

	//see also Divide2IntWoMulDivMod.h
	int BinarySearch(unsigned int n)
	{
		if ((n & (n - 1)) != 0)/*n is not a power of 2*/
			return -1;

		//find i such that 2^i <= n < 2^(i+1)
		int left = 0;
		int right = 31;
		while (right >= left)
		{
			int mid = (left + right) / 2;
			if ((1U << mid) >= n)
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is the lower bound
		std::cout << "IndexOfOnlyOneSetBit BinarySearch for \"" << n << "\": " << left << std::endl;
		return left;
	}
};
/*
IndexOfOnlyOneSetBit Iterate for "1024": 10
IndexOfOnlyOneSetBit Log for "1024": 10
IndexOfOnlyOneSetBit BinarySearch for "1": 0
IndexOfOnlyOneSetBit BinarySearch for "2": 1
IndexOfOnlyOneSetBit BinarySearch for "4": 2
IndexOfOnlyOneSetBit BinarySearch for "8": 3
IndexOfOnlyOneSetBit BinarySearch for "16": 4
IndexOfOnlyOneSetBit BinarySearch for "32": 5
IndexOfOnlyOneSetBit BinarySearch for "64": 6
IndexOfOnlyOneSetBit BinarySearch for "128": 7
IndexOfOnlyOneSetBit BinarySearch for "256": 8
IndexOfOnlyOneSetBit BinarySearch for "512": 9
IndexOfOnlyOneSetBit BinarySearch for "1024": 10
IndexOfOnlyOneSetBit BinarySearch for "2048": 11
IndexOfOnlyOneSetBit BinarySearch for "4096": 12
IndexOfOnlyOneSetBit BinarySearch for "8192": 13
IndexOfOnlyOneSetBit BinarySearch for "16384": 14
IndexOfOnlyOneSetBit BinarySearch for "32768": 15
IndexOfOnlyOneSetBit BinarySearch for "65536": 16
IndexOfOnlyOneSetBit BinarySearch for "131072": 17
IndexOfOnlyOneSetBit BinarySearch for "262144": 18
IndexOfOnlyOneSetBit BinarySearch for "524288": 19
IndexOfOnlyOneSetBit BinarySearch for "1048576": 20
IndexOfOnlyOneSetBit BinarySearch for "2097152": 21
IndexOfOnlyOneSetBit BinarySearch for "4194304": 22
IndexOfOnlyOneSetBit BinarySearch for "8388608": 23
IndexOfOnlyOneSetBit BinarySearch for "16777216": 24
IndexOfOnlyOneSetBit BinarySearch for "33554432": 25
IndexOfOnlyOneSetBit BinarySearch for "67108864": 26
IndexOfOnlyOneSetBit BinarySearch for "134217728": 27
IndexOfOnlyOneSetBit BinarySearch for "268435456": 28
IndexOfOnlyOneSetBit BinarySearch for "536870912": 29
IndexOfOnlyOneSetBit BinarySearch for "1073741824": 30
IndexOfOnlyOneSetBit BinarySearch for "2147483648": 31
*/
#endif