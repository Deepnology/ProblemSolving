/*MUST*/
#ifndef DIVISION_TO_DECIMAL_STR_W_REPEAT_H
#define DIVISION_TO_DECIMAL_STR_W_REPEAT_H
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include "Debug.h"
/*
https://leetcode.com/problems/fraction-to-recurring-decimal/
Given two integers representing the numerator and denominator of a fraction
, return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.
For example,
Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
Google
http://www.careercup.com/question?id=5090137058836480
Given 2 integers, a numerator a and a denominator b, print the decimal representation of the rational number "numerator/denominator".
Since all rational numbers end with a repeating section, print the repeating section of digits inside parentheses.

The digit of the decimal part of division would be the (remainder*10)/b.
The remainder of which is (remainder*10)%b.
Repeat this in a loop until remainder is equal to 0.
We keep track of the remainder of each loop by using a table.
If we find a repeated remainder, that should be a starting digit of the decimal digit, then insert '('.
Otherwise, mark the remainder that has been visited.
*/
class DivisionToDecimalStrWRepeat
{
public:
	DivisionToDecimalStrWRepeat(){}
	~DivisionToDecimalStrWRepeat(){}

	std::string Divide(int numerator, int denominator)
	{
		std::string res;
		if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0))
			res += '-';

		long a = numerator;
		long b = denominator;
		a = std::abs(a);
		b = std::abs(b);
		long quotient = a / b;
		long remainder = a % b;

		res += std::to_string(quotient);

		if (remainder != 0)
		{
			res += '.';
			std::string fracStr;

			std::unordered_map<long, int> remainderToRepeatIdx;
			int idx = 0;
			while (remainder != 0)
			{
				if (remainderToRepeatIdx.find(remainder) == remainderToRepeatIdx.end())
				{
					remainderToRepeatIdx[remainder] = idx;
				}
				else//found first repeated remainder: insert parenthesis and stop
				{
					fracStr.insert(remainderToRepeatIdx[remainder], "(");
					fracStr += ")";
					break;
				}
				remainder *= 10;
				long digit = remainder / b;//must be a single digit, which is at most '9'
				remainder = remainder % b;
				fracStr += std::to_string(digit);
				++idx;
			}

			res += fracStr;
		}

		std::cout << "DivisionToDecimalStrWRepeat for \"" << a << "/" << b << "\": " << res << std::endl;
		return res;
	}
};
/*
DivisionToDecimalStrWRepeat for "2/2": 1
DivisionToDecimalStrWRepeat for "5/2": 2.5
DivisionToDecimalStrWRepeat for "1/2": 0.5
DivisionToDecimalStrWRepeat for "1/3": 0.(3)
DivisionToDecimalStrWRepeat for "1/29": 0.(0344827586206896551724137931)
DivisionToDecimalStrWRepeat for "22/7": 3.(142857)
DivisionToDecimalStrWRepeat for "58/2828": 0.0(205091937765)
DivisionToDecimalStrWRepeat for "50/8": -6.25
DivisionToDecimalStrWRepeat for "7/12": -0.58(3)
*/
#endif