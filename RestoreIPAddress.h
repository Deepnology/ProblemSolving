#ifndef RESTORE_IP_ADDRESS_H
#define RESTORE_IP_ADDRESS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Compute all valid IP addresses
https://github.com/anson627/leetcode/blob/master/RestoreIPAddresses/RestoreIPAddresses.cpp
// Given a string containing only digits, restore it by returning all possible
// valid IP address combinations.
//
// For example:
// Given "25525511135",
//
// return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

The total number of IP addresses is a constant 2^32, implying an O(1) time complexity for the algorithm.
*/
class RestoreIPAddress
{
public:
	RestoreIPAddress(){}
	~RestoreIPAddress(){}

	std::vector<std::string> Recur(const std::string & s)
	{
		std::vector<std::string> res;
		std::string path;
		this->recur(s, 0, 0, path, res);
		std::cout << "RestoreIPAddress Recur for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(const std::string & s, int begin, int step
		, std::string & path, std::vector<std::string> & res)
	{
		if (begin == s.size() || step == 4)//reaches the end
		{
			if (begin == s.size() && step == 4)//valid IP address
				res.push_back(path);
			return;
		}
		/*
		for each next possible number (0~255)
		add to path and recur down to the next level
		*/
		std::string copy = path;
		if (begin != 0)
			copy.push_back('.');
		int num = 0;
		for (; begin < (int)s.size(); ++begin)
		{
			num = num * 10 + s[begin] - '0';
			copy.push_back(s[begin]);
			if (num > 255)//invalid num
				break;//stop
			this->recur(s, begin + 1, step + 1, copy, res);//recur down with the next possible number (0~255)
			if (num == 0)//no valid num starting with 0
				break;//stop
		}
	}

public:
	std::vector<std::string> Iterate(const std::string & s)
	{
		std::vector<std::string> res;
		int N = s.size();
		for (int i = 1; i < 4 && i < N; ++i)
		{
			auto first = s.substr(0, i);
			if (this->isValidPart(first))
			{
				for (int j = 1; i + j < N && j < 4; ++j)
				{
					auto second = s.substr(i, j);
					if (this->isValidPart(second))
					{
						for (int k = 1; i + j + k < N && k < 4; ++k)
						{
							auto third = s.substr(i + j, k);
							auto fourth = s.substr(i + j + k);
							if (this->isValidPart(third) && this->isValidPart(fourth))
							{
								res.push_back(first + "." + second + "." + third + "." + fourth);
							}
						}
					}
				}
			}
		}

		std::cout << "RestoreIPAddress Iterate for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	bool isValidPart(const std::string & s)
	{
		int N = s.size();
		if (N > 3)
			return false;
		if (s.front() == '0' && N > 1)
			return false;

		int val = stoi(s);
		return val <= 255 && val >= 0;
	}
};
/*
RestoreIPAddress Recur for "25525511135": 255.255.11.135, 255.255.111.35
RestoreIPAddress Iterate for "25525511135": 255.255.11.135, 255.255.111.35
*/
#endif