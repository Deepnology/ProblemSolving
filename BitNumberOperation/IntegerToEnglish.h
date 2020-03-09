/*MUST*/
#ifndef INTEGER_TO_ENGLISH_H
#define INTEGER_TO_ENGLISH_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Integer to English Words
Cracking the coding interview: Moderate
Given an integer, print an English phrase that describes the integer.
*/
class IntegerToEnglish
{
public:
	IntegerToEnglish(){}
	~IntegerToEnglish(){}

	std::string Convert(int n)
	{
		long long N = n;//for the case of INT_MIN
		std::string res;
		if (N == 0)
			res.append("Zero");
		else
		{
			if (N < 0)
			{
				res.append("Negative ");
				N *= -1;
			}
			//now n is positive

			static const std::vector<std::string> Thousands({ "", "Thousand", "Million", "Billion" });
			int thousandsCount = 0;
			std::string positive;
			while (N)
			{
				//convert each 3-digit (1 to 999) from the right
				if (N % 1000 != 0)
				{
					positive = this->convert_1_to_999((int)(N % 1000)) + Thousands[thousandsCount] + " " + positive;//insert front
				}
				N /= 1000;
				++thousandsCount;
			}
			res.append(positive);
		}

		while (!res.empty() && res.back() == ' ')
			res.pop_back();
		std::cout << "IntegerToEnglish for \"" << n << "\": \"" << res << "\"" << std::endl;
		return res;
	}

	std::string convert_1_to_999(int n)//n: 1~999
	{
		static const std::vector<std::string> Digits({ "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" });//1...9
		static const std::vector<std::string> Teens({ "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" });//11...19
		static const std::vector<std::string> Tens({ "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" });//10,20,...,90
		std::string res;

		/*1. how many hundreds*/
		if (n >= 100)
		{
			res += Digits[n / 100 - 1] + " Hundred ";
			n %= 100;
		}

		/*2. how many doubles*/
		if (n >= 11 && n <= 19)
		{
			res += Teens[n - 11] + " ";
		}
		else
		{
			if (n == 10 || n >= 20)
			{
				res += Tens[n / 10 - 1] + " ";
				n %= 10;
			}
			if (n >= 1 && n <= 9)
			{
				res += Digits[n - 1] + " ";
			}
		}
		return res;
	}
};
/*
IntegerToEnglish for "123": "One Hundred Twenty Three"
IntegerToEnglish for "19323984": "Nineteen Million Three Hundred Twenty Three Thousand Nine Hundred Eighty Four"
IntegerToEnglish for "1200000": "One Million Two Hundred Thousand"
IntegerToEnglish for "-231200453": "Negative Two Hundred Thirty One Million Two Hundred Thousand Four Hundred Fifty Three"
IntegerToEnglish for "1234567891": "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
IntegerToEnglish for "2147483647": "Two Billion One Hundred Forty Seven Million Four Hundred Eighty Three Thousand Six Hundred Forty Seven"
IntegerToEnglish for "-2147483648": "Negative Two Billion One Hundred Forty Seven Million Four Hundred Eighty Three Thousand Six Hundred Forty Eight"
*/
#endif