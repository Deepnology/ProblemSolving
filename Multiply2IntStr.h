/*MUST*/
#ifndef MULTIPLY_2_INT_STR_H
#define MULTIPLY_2_INT_STR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, Array: Multiply 2 big integers
Leetcode: Multiply Strings
// Given two numbers represented as strings, return multiplication of the
// numbers as a string.
//
// Note: The numbers can be arbitrarily large and are non-negative.
// O(m*n) time, where m and n are the number of digits of the two numbers, respectively.

See also Mul2IntWoArithmeticOp.h
*/
class Multiply2IntStr
{
public:
	Multiply2IntStr(){}
	~Multiply2IntStr(){}

	std::string GO(const std::string & num1, const std::string & num2)
	{
		if (num1.empty() || num2.empty())
			return std::string();

		int N1 = num1.size();
		int N2 = num2.size();
		std::string res(N1 + N2, '0');

		for (int i = N1 - 1; i >= 0; --i)
		{
			//multiply num1[i] with each digit of num2 from right to left plus the carry
			//save the sum % 10 in res[i+j+1]
			int carry = 0;
			for (int j = N2 - 1; j >= 0; --j)
			{
				int sum = carry + (res[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0');
				res[i + j + 1] = '0' + sum % 10;
				carry = sum / 10;
			}
			res[i] = '0' + carry;//can be thought as j==-1, so i+j+1 = i
		}

		/*remove heading 0s*/
		while (res.size() > 1 && (*res.begin()) == '0')
			res.erase(res.begin());

		std::cout << "Multiply2IntStr for \"" << num1 << "\" and \"" << num2 << "\" is: " << res << std::endl;
		return res;
	}

};
/*
Multiply2IntStr for "102" and "7811" is: 796722
Multiply2IntStr for "896" and "38" is: 34048
*/
#endif