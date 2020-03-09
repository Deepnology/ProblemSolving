#ifndef STRING_TO_INtEGER_H
#define STRING_TO_INtEGER_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
/*
Leetcode: String to Integer (atoi)
// Implement atoi to convert a string to an integer.
//
// Hint: Carefully consider all possible input cases. If you want a challenge,
// please do not see below and ask yourself what are the possible input cases.
//
// Notes: It is intended for this problem to be specified vaguely (ie, no given
// input specs). You are responsible to gather all the input requirements up
// front.
//
// Requirements for atoi:
// The function first discards as many whitespace characters as necessary until
// the first non-whitespace character is found. Then, starting from this
// character, takes an optional initial plus or minus sign followed by as many
// numerical digits as possible, and interprets them as a numerical value.
//
// The string can contain additional characters after those that form the
// integral number, which are ignored and have no effect on the behavior of
// this function.
//
// If the first sequence of non-whitespace characters in str is not a valid
// integral number, or if no such sequence exists because either str is empty
// or it contains only whitespace characters, no conversion is performed.
//
// If no valid conversion could be performed, a zero value is returned. If the
// correct value is out of the range of representable values, INT_MAX
// (2147483647) or INT_MIN (-2147483648) is returned.
*/
class StringToInteger
{
public:
	StringToInteger(){}
	~StringToInteger(){}

	int atoi(const std::string & str)
	{
		int N = str.size();
		int i = 0;

		//1. trim leading spaces
		while (i < N && str[i] == ' ')
			++i;

		//2. +/-
		bool isNegative = false;
		if (i < N && str[i] == '+')
			++i;
		else if (i < N && str[i] == '-')
		{
			isNegative = true;
			++i;
		}

		//3. pure digits
		long long res = 0;
		while (i < N && str[i] >= '0' && str[i] <= '9')
		{
			res = res * 10 + str[i] - '0';

			if (!isNegative && res > INT_MAX)
			{
				res = INT_MAX;
				break;
			}
			if (isNegative && res - 1 > INT_MAX)
			{
				res = INT_MIN;
				break;
			}
			++i;
		}

		if (isNegative && res != INT_MIN)
			res = 0 - res;

		std::cout << "StringToInteger for \"" << str << "\": " << res << std::endl;
		return (int)res;
	}
};
/*
StringToInteger for "-1": -1
StringToInteger for "   -13453456": -13453456
*/
#endif