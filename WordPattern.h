#ifndef WORD_PATTERN_H
#define WORD_PATTERN_H
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"
/*
Leetcode: Word Pattern
Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.
Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
see also IsomorphicStrings.h

Leetcode: Word Pattern II
Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.
Examples:
pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false.
Notes:
You may assume both pattern and str contains only lowercase letters.

Why do we need bi-directional mapping?
If we have only one-directional mapping, pattern="ab", str="dog dog", will return true, which is incorrect.
*/
class WordPattern
{
public:
	WordPattern() {}
	~WordPattern() {}

	bool Match(std::string pattern, std::string str)
	{
		//split all strs in str by whitespace
		std::vector<std::string> v;
		int M = str.size();
		int begin = 0;
		for (int i = 0; i < M; ++i)
		{
			if (str[i] == ' ')
			{
				v.push_back(str.substr(begin, i - begin));
				begin = i + 1;
			}
			else if (i == M - 1)
			{
				v.push_back(str.substr(begin, M - begin));
			}
		}


		int N = pattern.size();
		M = v.size();
		if (N != M || N == 0) return false;

		//keep track of a forward mapping from char to string, and a backward mapping from string to char
		std::unordered_map<char, std::string> fwdMap;
		std::unordered_map<std::string, char> bwdMap;

		bool res = true;
		for (int i = 0; i < N; ++i)
		{
			char c = pattern[i];
			std::string s = v[i];

			if (fwdMap.find(c) == fwdMap.end() && bwdMap.find(s) == bwdMap.end())//both not found, just insert both
			{
				fwdMap.insert({ c, s });
				bwdMap.insert({ s, c });
			}
			else if (fwdMap.find(c) != fwdMap.end() && bwdMap.find(s) != bwdMap.end())//both are found, compare found with current
			{
				std::string ss = fwdMap.find(c)->second;
				char cc = bwdMap.find(s)->second;

				if (ss.compare(s) != 0 || cc != c)
				{
					res = false;
					break;
				}
			}
			else//one found but the other one not found
			{
				res = false;
				break;
			}
		}

		std::cout << "WordPattern Match for pattern=\"" << pattern << "\", str=\"" << str << "\": " << res << std::endl;
		return res;
	}

	int MatchII(std::string pattern, std::string str)
	{
		std::unordered_map<char, std::string> fwdMap;
		std::unordered_map<std::string, char> bwdMap;
		bool res = this->recur(pattern, 0, str, 0, fwdMap, bwdMap);

		std::cout << "WordPattern MatchII for pattern=\"" << pattern << "\", str=\"" << str << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(const std::string & pattern, int pBegin, const std::string & str, int sBegin, std::unordered_map<char, std::string> & fwdMap, std::unordered_map<std::string, char> & bwdMap)
	{
		int N = pattern.size();
		int M = str.size();
		if (pBegin == N && sBegin == M)
			return true;
		if (pBegin >= N || sBegin >= M)
			return false;

		char c = pattern[pBegin];
		for (int i = sBegin; i < M; ++i)
		{
			std::string s = str.substr(sBegin, i - sBegin + 1);//str[sBegin:i]

			if (fwdMap.find(c) == fwdMap.end() && bwdMap.find(s) == bwdMap.end())
			{
				fwdMap.insert({ c, s });
				bwdMap.insert({ s, c });
				if (this->recur(pattern, pBegin + 1, str, i + 1, fwdMap, bwdMap))
					return true;
				fwdMap.erase(c);
				bwdMap.erase(s);
			}
			else if (fwdMap.find(c) != fwdMap.end() && bwdMap.find(s) != bwdMap.end())
			{
				std::string ss = fwdMap.find(c)->second;
				char cc = bwdMap.find(s)->second;
				if (ss.compare(s) != 0 || cc != c)
					continue;
				if (this->recur(pattern, pBegin + 1, str, i + 1, fwdMap, bwdMap))
					return true;
			}
			else
				continue;
		}

		return false;
	}
};
/*
WordPattern Match for pattern="abba", str="dog cat cat dog": 1
WordPattern Match for pattern="abba", str="dog cat cat fish": 0
WordPattern Match for pattern="aaaa", str="dog cat cat dog": 0
WordPattern Match for pattern="abba", str="dog dog dog dog": 0
WordPattern MatchII for pattern="abab", str="redblueredblue": 1
WordPattern MatchII for pattern="aaaa", str="asdasdasdasd": 1
WordPattern MatchII for pattern="aabb", str="xyzabcxyzabc": 0
*/
#endif
