/*HashTable*/
#ifndef REPEATED_DNA_SUBSTR_H
#define REPEATED_DNA_SUBSTR_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iostream>
#include "Debug.h"
/*
https://leetcode.com/problems/repeated-dna-sequences/
http://blog.csdn.net/wzy_1988/article/details/44224749
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". 
When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,
Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
Return:
["AAAAACCCCC", "CCCCCAAAAA"].
*/
class RepeatedDNASubstr
{
public:
	RepeatedDNASubstr(){}
	~RepeatedDNASubstr(){}

	std::vector<std::string> HashTable(const std::string & s)
	{
		int N = s.size();
		std::map<int, int> visited;//visited substring. key: hash, value: count
		std::vector<std::string> res;
		for (int i = 0; i < N - 10 + 1; ++i)
		{
			if (visited.find(this->hash(s.substr(i, 10))) == visited.end())
			{
				visited.insert({ this->hash(s.substr(i, 10)), 1 });
			}
			else
			{
				if (visited[this->hash(s.substr(i, 10))] == 1)
					res.push_back(s.substr(i, 10));//add to result when visiting a substr for its 2nd time
				++visited[this->hash(s.substr(i, 10))];
			}
		}

		std::cout << "RepeatedDNASubstr HashTable for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

private:
	/*
	each char(A,C,G,T) is 2-bit long
	10 chars long of each substring
	=> 20 bit for each substring, which can be represented by a 32-bit integer
	*/
	int hash(const std::string & s)
	{
		int res = 0;
		for (const char & c : s)
		{
			res = res << 2 | this->cToI(c);
		}
		return res;
	}
	int cToI(char c)
	{
		switch (c)
		{
		case 'A':
			return 0;//00
		case 'C':
			return 1;//01
		case 'G':
			return 2;//10
		case 'T':
			return 3;//11
		default:
			return -1;
		}
	}
};
/*
RepeatedDNASubstr HashTable for "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT": AAAAACCCCC, CCCCCAAAAA
*/
#endif