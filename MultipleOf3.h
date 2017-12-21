#ifndef	MULTIPLE_OF_3_H
#define MULTIPLE_OF_3_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/write-an-efficient-method-to-check-if-a-number-is-multiple-of-3/
http://edusagar.com/articles/view/10/BitWise-Operators-interview-Questions
If sum of digits in a number is multiple of 3 then the number multiple of 3.

There is pattern in binary representation of the number that can be used to find if number is a multiple of 3.
If difference between count of odd set bits (bits set at odd positions) and even set bits is multiple of 3
, then is the number.

1=01, final diff count of even/odd set bits=1
2=10, final diff count of even/odd set bits=1
3=11, final diff count of even/odd set bits=0

4=100, final diff count of even/odd set bits=1
5=101, final diff count of even/odd set bits=2->1
6=110, final diff count of even/odd set bits=0

OddEvenBitCountDiff_Recur: O(logn) time
*/
class MultipleOf3
{
public:
	MultipleOf3(){}
	~MultipleOf3(){}

	bool OddEvenBitCountDiff_Recur(int n)
	{
		bool res = this->recur(n);
		std::cout << "MultipleOf3 OddEvenBitCountDiff_Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}

	bool recur(int n)
	{
		if (n < 0)
			n = -n;
		if (n == 0)
			return true;
		if (n == 1)
			return false;

		int oddCount = 0;
		int evenCount = 0;

		while (n != 0)
		{
			if (n & 1)
				++oddCount;
			n = n >> 1;

			if (n & 1)
				++evenCount;
			n = n >> 1;
		}

		int diff = std::abs(oddCount - evenCount);
		return this->recur(diff);
	}

};
/*
MultipleOf3 OddEvenBitCountDiff_Recur for "23": 0
*/
#endif