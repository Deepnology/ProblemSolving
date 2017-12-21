#ifndef ADD_2_BINARY_STR_H
#define ADD_2_BINARY_STR_H
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
/*
Elements of programming interview, Array: Increment a big integer
Leetcode: Add Binary
// Given two binary strings, return their sum (also a binary string).
//
// For example,
// a = "11"
// b = "1"
// Return "100".
//
// Complexity:
// O(n) time

see also Add2IntStr.h
*/
class Add2BinaryStr
{
public:
	Add2BinaryStr(){}
	~Add2BinaryStr(){}

	std::string GO(std::string & a, std::string & b)
	{
		int N = std::max(a.size(), b.size());
		std::string res(N + 1, '0');
		int carry = 0;
		int ai = a.size() - 1;
		int bi = b.size() - 1;
		for (int i = N; i >= 0; --i)
		{
			int sum = carry;
			if (ai >= 0)
			{
				sum += a[ai--] - '0';
			}
			if (bi >= 0)
			{
				sum += b[bi--] - '0';
			}
			carry = sum / 2;
			res[i] = sum % 2 + '0';
		}
		if (res[0] == '0')
			res = res.substr(1, N);

		std::cout << "Add2BinaryStr for \"" << a << "\" and \"" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
Add2BinaryStr for "11" and "1111": 10010
*/

#endif