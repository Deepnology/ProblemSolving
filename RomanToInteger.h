/*MEMO*/
#ifndef ROMAN_TO_INTEGER_H
#define ROMAN_TO_INTEGER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
/*
Elements of programming interview, Strings: Convert from Roman to decimal
The Roman numeral representation of positive integers uses the symbols I,V,X,L,C,D,M.
Each symbol represents a value:
I: 1, V: 5, X: 10, L: 50, C: 100, D: 500, M: 1000.
Define a string over the Roman number symbols to be a valid Roman number string if symbols appear in nonincreasing order
, with the following exceptions allowed:
- I can immediately precede V and X
- X can immediately precede L and C
- C can immediately precede D and M

A valid complex Roman number string represents the integer which is the sum of the symbols that do not correspond to exceptions
; for the exceptions, add the difference of the larger symbol and the samller symbol.

For example, the strings "XXXXXIIIIIIIII", "LVIIII", and "LIX" are valid Roman number strings representing 59.
The shortest valid complex Roman number string corresponding to the integer 59 is "LIX".

Leetcode: Roman To Integer
// Given a roman numeral, convert it to an integer.
//
// Input is guaranteed to be within the range from 1 to 3999.
Leetcode: Integer To Roman
// Given an integer, convert it to a roman numeral.
//
// Input is guaranteed to be within the range from 1 to 3999.
*/
class RomanToInteger
{
public:
	RomanToInteger()
	{
		table = std::unordered_map<char, int>(
		{
			{ 'M', 1000 },
			{ 'D', 500 },
			{ 'C', 100 },
			{ 'L', 50 },
			{ 'X', 10 },
			{ 'V', 5 },
			{ 'I', 1 }
		});
		ints = std::vector<int>({ 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 });
		romans = std::vector<std::string>({ "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" });
	}
	~RomanToInteger(){}

	int RtoI(std::string s)
	{
		int res = 0;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			if (i < N - 1 && table[s[i]] < table[s[i + 1]])
			{
				res -= table[s[i]];/*subtract current letter WHEN right letter is < current letter*/
				std::cout << "-" << table[s[i]] << std::endl;
			}
			else
			{
				res += table[s[i]];/*plus current letter WHEN right letter is >= current letter, or there is no right letter*/
				std::cout << "+" << table[s[i]] << std::endl;
			}
		}

		std::cout << "RomanToInteger for \"" << s << "\" is: " << res << std::endl;
		return res; 
	}
	std::string ItoR(int num)
	{
		int before = num;
		std::ostringstream oss;
		for (int i = 0; i < 13; ++i)
		{
			while (num >= ints[i])
			{
				num -= ints[i];
				oss << romans[i];
			}
		}

		std::cout << "IntegerToRoman for \"" << before << "\" is: " << oss.str() << std::endl;
		return oss.str();
	}
private:
	std::unordered_map<char, int> table;
	std::vector<int> ints;
	std::vector<std::string> romans;
};
/*
+1000
+1000
+10
-1
+5
RomanToInteger for "MMXIV" is: 2014
IntegerToRoman for "2014" is: MMXIV
*/
#endif