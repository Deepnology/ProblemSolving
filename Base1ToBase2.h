/*MUST*/
#ifndef BASE1_TO_BASE2_H
#define BASE1_TO_BASE2_H
#include <string>
#include <iostream>
#include <sstream>
/*
A collection of bit programming
Elements of programming interview, PrimitiveTypes: Convert base

The time complexity is O(n(1 + log  b1)), where n is the length of s.
                                  b2
First, we perform n multiply-and-adds to get the decimal from s.
Then we perform (log  decimal) multiply-and-adds to get the result.
                    b2
The decimal is upper bounded by b1^n, and log  b1^n = n * log  b1.
                                             b2              b2
*/
class Base1ToBase2
{
public:
	Base1ToBase2(){}
	~Base1ToBase2(){}

	std::string Solve(const std::string & s, unsigned int b1, unsigned int b2)
	{
		std::string res;
		if (s.empty())
			res = s;
		else
		{
			/*1. convert s (b1 based) to a decimal number from left to right*/
			bool neg = s[0] == '-' ? true : false;
			int N = s.size();
			int decimal = 0;
			for (int i = neg ? 1 : 0; i < N; ++i)
			{
				decimal = decimal * b1 + (this->isDigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10);
			}
			std::cout << decimal << std::endl;

			/*2. convert the decimal to b2 based string from right to left*/
			while (decimal)
			{
				int remainder = decimal % b2;
				res.push_back(remainder >= 10 ? 'A' + remainder - 10 : '0' + remainder);
				decimal /= b2;
			}

			if (neg)
				res.push_back('-');

			/*3. reverse the b2 based string*/
			std::reverse(res.begin(), res.end());
		}

		std::cout << "Base1ToBase2 for \"" << s << "\" from \"" << b1 << "\" to \"" << b2 << "\": " << res << std::endl;
		return res;
	}

private:
	bool isDigit(const char a)
	{
		return (a - '0' >= 0) && (a - '0' <= 9);
	}
};
/*
56
Base1ToBase2 for "56" from "10" to "2": 111000
10
Base1ToBase2 for "1010" from "2" to "16": A
*/
#endif