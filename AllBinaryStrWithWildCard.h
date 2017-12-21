#ifndef ALL_BINARY_STR_WITH_WILD_CARD_H
#define ALL_BINARY_STR_WITH_WILD_CARD_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=20308668
https://sites.google.com/site/spaceofjameschen/home/string/generate-strings-with-a-specified-pattern----google
Given a binary string pattern s that contains '1', '0', and '?', where wildcard '?' can be either '1' or '0'.
Find out all possible binary strings.

Recur: O(n * 2^k) time, where n is the length of the string, k is the count of '?'
*/
class AllBinaryStrWithWildCard
{
public:
	AllBinaryStrWithWildCard(){}
	~AllBinaryStrWithWildCard(){}

	std::vector<std::string> Recur(const std::string & s)
	{
		std::string path;
		std::vector<std::string> res;
		this->recur(s, 0, path, res);
		std::cout << "AllBinaryStrWithWildCard for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & s, int start, std::string & path, std::vector<std::string> & res)
	{
		int N = s.size();
		if (start == N)
		{
			res.push_back(path);
			return;
		}
		if (s[start] == '?')
		{
			path.push_back('0');
			this->recur(s, start + 1, path, res);
			path.pop_back();
			path.push_back('1');
			this->recur(s, start + 1, path, res);
			path.pop_back();
		}
		else
		{
			path.push_back(s[start]);
			this->recur(s, start + 1, path, res);
			path.pop_back();
		}
	}
};
/*
AllBinaryStrWithWildCard for "1?00?101": 10000101, 10001101, 11000101, 11001101
*/
#endif