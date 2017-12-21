#ifndef SHORTEST_SUBSTR_CONTAIN_ALL_CHARS_H
#define SHORTEST_SUBSTR_CONTAIN_ALL_CHARS_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Minimum Window Substring
Given a set T of characters and a string S, find the minimum window in S which will contain all the characters in T in complexity O(n).

eg,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC"

S = "ACBBACA"
T = "ABA"
Minimum window is "BACA"

Note:
If there is no such window in S that covers all characters in T, return the
empty string "".
If there are multiple such windows, you are guaranteed that there will
always be only one unique minimum window in S.

1. BruteForce: O(n^3), time O(1) space
2. Stormrage: O(n) time

See also Anagrams.h FindAllAnagramSubstr, ShortestSubArrContainAllEntries.h
*/
class ShortestSubstrContainAllChars
{
public:
	ShortestSubstrContainAllChars(){}
	~ShortestSubstrContainAllChars(){}

	std::string FindAll_BruteForceIterate(const std::string & S, const std::string & T)
	{
		int N = S.size();
		int count = T.size();
		std::vector<int> charMap(256, 0);//hash table

		for (int i = 0; i < count; ++i)
			++charMap[T[i]];

		int minWindowLen = INT_MAX;
		int minWindowBegin = 0;
		int minWindowEnd = 0;

		std::vector<std::string> res;

		//enumerate all possible substrs with length equal to count in S
		for (int end = count - 1; end < N; ++end)
		{
			for (int begin = 0; begin <= end - count + 1; ++begin)
			{
				//check if S[begin,end] contains all chars
				std::vector<int> foundMap(256, 0);
				for (int i = begin; i <= end; ++i)
					++foundMap[S[i]];
				bool match = true;
				for (int i = 0; i < 256; ++i)
				{
					if (foundMap[i] < charMap[i])
					{
						match = false;
						break;
					}
				}
				if (match && minWindowLen > end - begin + 1)
				{
					minWindowLen = end - begin + 1;
					minWindowBegin = begin;
					minWindowEnd = end;
				}
				if (match)
					res.push_back(S.substr(begin, end - begin + 1));
			}
		}

		std::cout << "ShortestSubstrContainAllChars FindAll_BruteForceIterate for \"" << T << "\" from \"" << S << "\": " << S.substr(minWindowBegin, minWindowLen) << std::endl;
		std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		return S.substr(minWindowBegin, minWindowLen);
	}

	std::string Stormrage(const std::string & v, const std::string & entries)
	{
		int N = v.size();
		int M = entries.size();

		std::unordered_map<char, int> charMap;//first: entry, second: count
		for (const auto & c : entries)
			++charMap[c];

		std::unordered_map<char, int> foundMap;//first: entry, second: count
		int begin = 0;
		int end = 0;
		int foundCount = 0;
		int minLen = INT_MAX;
		int minBegin = -1;
		int minEnd = -1;
		for (; end < N; ++end)
		{
			if (charMap.find(v[end]) == charMap.end())
				continue;

			++foundMap[v[end]];//might also exceed the required amount
			if (foundMap[v[end]] <= charMap[v[end]])
				++foundCount;

			if (foundCount == M)
			{
				//advance begin for 2 cases: irrelevant and redundant
				while (true)
				{
					if (charMap.find(v[begin]) == charMap.end())//irrelevant
						++begin;
					else if (foundMap[v[begin]] > charMap[v[begin]])//redundant
					{
						--foundMap[v[begin]];
						++begin;
					}
					else
						break;
				}
				if (end - begin + 1 < minLen)
				{
					minLen = end - begin + 1;
					minBegin = begin;
					minEnd = end;
				}
			}
		}

		std::string res;
		if (minLen == INT_MAX)
			res = "";
		else
			res = v.substr(minBegin, minLen);
		std::cout << "ShortestSubstrContainAllChars Stormrage for \"" << entries << "\" from \"" << v << "\": " << res << std::endl;
		return res;
	}
};
/*
ShortestSubstrContainAllChars FindAll_BruteForceIterate for "ABA" from "ACBBACA": BACA
ACBBA, ACBBAC, ACBBACA, CBBACA, BBACA, BACA
ShortestSubstrContainAllChars Stormrage for "ABA" from "ACBBACA": BACA
ShortestSubstrContainAllChars Stormrage for "ABC" from "ADOBECODEBANC": BANC
ShortestSubstrContainAllChars Stormrage for "tist" from "this is a test string": t stri
*/
#endif