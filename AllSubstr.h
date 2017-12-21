/*Recur*/
#ifndef ALL_SUBSTR_H
#define ALL_SUBSTR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Given a string s.
Enumerate all possible substrings in s.
*/
class AllSubstr
{
public:
	AllSubstr(){}
	~AllSubstr(){}

	std::vector<std::string> Iterate(const std::string & s)
	{
		int N = s.size();
		std::vector <std::string> res;
		for (int curEnd = 0; curEnd < N; ++curEnd)
		{
			for (int curBegin = 0; curBegin <= curEnd; ++curBegin)
			{
				res.push_back(s.substr(curBegin, curEnd - curBegin + 1));
			}
		}
		std::cout << "AllSubstr Iterate for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	std::vector<std::string> Recur(const std::string & s)
	{
		std::vector<std::string> res;
		this->recur(s, 0, 0, res);
		std::cout << "AllSubstr Recur for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & s, int curBegin, int curEnd, std::vector<std::string> & res)
	{
		int N = s.size();
		if (curEnd == N)//outer for loop corner condition
			return;
		if (curBegin > curEnd)//inner for loop corner condition
		{
			this->recur(s, 0, curEnd + 1, res);//advance in outer loop
			return;
		}
		res.push_back(s.substr(curBegin, curEnd - curBegin + 1));//visit
		this->recur(s, curBegin + 1, curEnd, res);//advance in inner loop
	}
};
/*
AllSubstr Iterate for "a": a
AllSubstr Iterate for "aa": a, aa, a
AllSubstr Iterate for "ab": a, ab, b
AllSubstr Iterate for "abbc": a, ab, b, abb, bb, b, abbc, bbc, bc, c
AllSubstr Iterate for "abac": a, ab, b, aba, ba, a, abac, bac, ac, c
AllSubstr Iterate for "aabab": a, aa, a, aab, ab, b, aaba, aba, ba, a, aabab, abab, bab, ab, b
AllSubstr Iterate for "12345": 1, 12, 2, 123, 23, 3, 1234, 234, 34, 4, 12345, 2345, 345, 45, 5
AllSubstr Recur for "a": a
AllSubstr Recur for "aa": a, aa, a
AllSubstr Recur for "ab": a, ab, b
AllSubstr Recur for "abbc": a, ab, b, abb, bb, b, abbc, bbc, bc, c
AllSubstr Recur for "abac": a, ab, b, aba, ba, a, abac, bac, ac, c
AllSubstr Recur for "aabab": a, aa, a, aab, ab, b, aaba, aba, ba, a, aabab, abab, bab, ab, b
AllSubstr Recur for "12345": 1, 12, 2, 123, 23, 3, 1234, 234, 34, 4, 12345, 2345, 345, 45, 5
*/
#endif