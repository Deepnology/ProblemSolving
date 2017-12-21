#ifndef ADD_2_INT_STR_H
#define ADD_2_INT_STR_H
#include <iostream>
#include <string>
#include <algorithm>
/*
Leetcode: Add Strings
http://www.careercup.com/question?id=6330205329162240
Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.
Note:
The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

See also Add2BinaryStr.h
*/
class Add2IntStr
{
public:
	Add2IntStr(){}
	~Add2IntStr(){}

	std::string Solve(const std::string & a, const std::string & b)
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
			carry = sum / 10;
			res[i] = sum % 10 + '0';
		}
		if (res[0] == '0')
			res = res.substr(1, N);

		std::cout << "Add2IntStr for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
Add2IntStr for "6701", "4312": 11013
Add2IntStr for "7001", "23": 7024
Add2IntStr for "1", "2": 3
Add2IntStr for "5", "7": 12
*/
#endif