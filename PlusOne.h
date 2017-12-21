#ifndef PLUS_ONE_H
#define PLUS_ONE_H
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
Elements of programming interview, Array: Increment a big integer
Leetcode: Plus One
// Given a number represented as an array of digits, plus one to the number.
// 
// Complexity:
// O(n)
*/
class PlusOne
{
public:
	PlusOne(){}
	~PlusOne(){}

	void NonNegative(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);

		int N = v.size();
		int carry = 1;
		for (int i = N - 1; i >= 0; --i)
		{
			v[i] += carry;
			carry = v[i] / 10;
			v[i] = v[i] % 10;
		}
		if (carry)
		{
			v.insert(v.begin(), 1);
		}

		std::cout << "PlusOne NonNegative for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
PlusOne NonNegative for "2, 3, 9, 9, 9": 2, 4, 0, 0, 0
PlusOne NonNegative for "9, 9, 9, 9, 9": 1, 0, 0, 0, 0, 0
*/
#endif