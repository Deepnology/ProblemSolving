#ifndef MULTIPLE_OF_9_H
#define MULTIPLE_OF_9_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/divisibility-9-using-bitwise-operators/
Given a number, write a function that returns true if n is divisible by 9, else false.

1. The simplest way to check for n's divisibility by 9 is to do n%9.

2. Another method is to sum the digits of n.
   If sum of digits is multiple of 9, then n is multiple of 9.

The above 2 methods are not bitwise operator based methods and require use of % and /.

The bitwise operators are generally faster than modulo and division operators.

*/
class MultipleOf9
{
public:
	MultipleOf9(){}
	~MultipleOf9(){}

	bool Bitwise_Recur(int n)
	{
		bool res = this->recur(n);
		std::cout << "MultipleOf9 Bitwise_Recur for \"" << n << "\": " << res << std::endl;
		return res;
	}
	bool recur(int n)
	{
		if (n == 0 || n == 9)
			return true;
		if (n < 9)
			return false;

		/*
		if n is greater than 9, then recur for [floor(n/9) - n%8]
		*/
		return this->recur((int)(n >> 3) - (int)(n & 7));
	}
};
/*
MultipleOf9 Bitwise_Recur for "37": 0
*/
#endif