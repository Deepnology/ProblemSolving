/*MUST*/
#ifndef AGGREGATED_NUMBER_H
#define AGGREGATED_NUMBER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Additive Number
Google
http://www.careercup.com/question?id=14948278
http://www.quora.com/Programming-Interviews/We-will-name-a-number-aggregated-number-if-this-number-has-the-following-attribute-just-like-the-Fibonacci-numbers-1-1-2-3-5-8-13-the-digits-in-the-number-can-divided-into-several-parts-and-the-later-part-is-the-sum-of-the-former-parts
Aggregated Number:
The digits of a number can be divided into several parts such that the later part is the sum of 2 consecutive former parts.
112358 (1+1=2, 1+2=3, 2+3=5, 3+5=8)
122436 (12+24=36)
1299111210 (12+99=111, 99+111=210)
112112224 (112+112=224)
Determine whether a given number is an aggregated number or not.
O(n^3) time
*/
class AggregatedNumber
{
public:
	AggregatedNumber(){}
	~AggregatedNumber(){}

	//enumerate all possible first 2 consecutive nums' lengths
	bool Solve(const std::string & num)
	{
		std::cout << "AggregatedNumber for \"" << num << "\": ";
		int N = num.size();
		for (int firstLen = 1; firstLen <= N / 2; ++firstLen)
		{
			for (int secondLen = 1; secondLen <= N / 2; ++secondLen)
			{
				if (this->IsValid(firstLen, secondLen, num))
				{
					std::cout << "True. Len of first 2 nums: " << firstLen << ", " << secondLen << std::endl;
					return true;
				}
			}
		}
		std::cout << "False" << std::endl;
		return false;
	}

private:
	bool IsValid(int firstLen, int secondLen, const std::string & num)
	{
		std::string first = num.substr(0, firstLen);
		std::string second = num.substr(firstLen, secondLen);
		std::string res = first + second;//we want to construct a new string with first 2 substrings of num
		if (res.size() == num.size())
			return false;
		while (res.size() < num.size())
		{
			if ((first[0] == '0' && first.size() > 1) || (second[0] == '0' && second.size() > 1))
			{
				return false;//skip numbers that starts with '0'
			}
			std::string third = this->AddTwoStrInt(first, second);
			res += third;
			first = second;
			second = third;
		}
		return res.size() == num.size() && res == num;
	}
	std::string AddTwoStrInt(const std::string & a, const std::string & b)
	{
		unsigned int i = atoi(a.c_str());
		unsigned int j = atoi(b.c_str());
		return std::to_string(i + j);
	}
};
/*
AggregatedNumber for "992101103204": True. Len of first 2 nums: 2, 1
AggregatedNumber for "1034": False
AggregatedNumber for "10313": True. Len of first 2 nums: 2, 1
AggregatedNumber for "112035": False
*/
#endif