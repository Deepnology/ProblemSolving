#ifndef ISOMORPHIC_STRINGS_H
#define ISOMORPHIC_STRINGS_H
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Find and Replace Pattern
Leetcode: Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.
Two strings are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters.
No two characters may map to the same character but a character may map to itself.
For example,
Given "egg", "add", return true.
Given "foo", "bar", return false.
Given "paper", "title", return true.
Note:
You may assume both s and t have the same length.
see also WordPattern.h
*/
class IsomorphicStrings
{
public:
	IsomorphicStrings(){}
	~IsomorphicStrings(){}

	bool Solve(const std::string & s, const std::string & t)
	{
		bool res = this->isIsomorphic(s, t);
		std::cout << "IsomorphicStrings for \"" << s << "\" and \"" << t << "\": " << res << std::endl;
		return res;
	}

	bool isIsomorphic(const std::string & s, const std::string & t)
	{
		int N = s.size();
		if (N != t.size())
			return false;
		std::map<char, char> sTot;//a mapping from s[i] to t[i]
		std::map<char, char> tTos;//a mapping from t[i] to s[i]
		for (int i = 0; i < N; ++i)
		{
			char c1 = s[i];
			char c2 = t[i];
			auto itr1 = sTot.find(c1);
			auto itr2 = tTos.find(c2);

			if (itr1 != sTot.end() && itr2 != tTos.end())
			{
				if (itr1->second == c2 && itr2->second == c1)//both present and consistant with previous
					continue;
				else
					return false;
			}
			else if (itr1 == sTot.end() && itr2 == tTos.end())//both abscent
			{
				sTot.insert({ c1, c2 });
				tTos.insert({ c2, c1 });
			}
			else//one present one abscent
				return false;
		}
		return true;
	}
};
/*
IsomorphicStrings for "egg" and "add": 1
IsomorphicStrings for "foo" and "bar": 0
IsomorphicStrings for "paper" and "title": 1
*/
#endif