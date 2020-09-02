#ifndef _ANAGRAMS_H
#define _ANAGRAMS_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
anagrams: orchestra <-> carthorse (different permutations of a same set of letters)
(Any word that exactly reproduces the letters in another order is an anagram.)
=> all anagrams that are sorted letter by letter should produce a same word

Elements of programming interview, HashTable: partition into anagrams
https://github.com/anson627/leetcode/blob/master/Anagrams/Anagrams.cpp
// Given an array of strings, return all groups of strings that are anagrams.
// Note: All inputs will be in lower-case.
// Complexity:
// O(k*n) time, O(k*n) space, where k is the average length of string

Cracking the coding interview 9.2
Write a method to sort an array of strings so that 
all the anagrams are next to each other.

Google
http://www.careercup.com/question?id=5389078581215232
Determine if any anagram of string T is a substring of string S.
See also ShortestSubstrContainAllChars.h, SubstrWConcatAllWords.h

Determine if two given strings are anagrams.
*/

class Anagrams
{
public:
	Anagrams(){}
	~Anagrams(){}

	std::vector<std::string> FindAll(const std::vector<std::string> & strs)
	{
		std::unordered_map<std::string, std::vector<std::string> > sortToAgms;//key: sorted string or hash string, value: anagram vector
		for (const std::string & s : strs)
		{
			//sortToAgms[this->hash(s)].push_back(s);//all anagrams have a same hash string value
			//std::cout << this->hash(s) << std::endl;
			std::string key(s);
			std::sort(key.begin(), key.end());
			sortToAgms[key].push_back(s);
		}
		std::vector<std::string> res;
		for (const auto & itr : sortToAgms)
		{
			if (itr.second.size() > 1)
			{
				res.insert(std::end(res), std::begin(itr.second), std::end(itr.second));
				//insert all strings in itr.second vector to the end of res
			}
		}

		Debug::Print2D<std::string>()(sortToAgms);
		std::cout << "Anagrams FindAll in \"" << Debug::ToStr1D<std::string>()(strs) << "\" are: " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

public:
	void Sort(std::vector<std::string> && strs)
	{
		std::string before = Debug::ToStr1D<std::string>()(strs);

		std::sort(std::begin(strs), std::end(strs), 
			[](const std::string & a, const std::string & b)->bool
		{
			std::string a1(a);
			std::sort(std::begin(a1), std::end(a1));
			std::string b1(b);
			std::sort(std::begin(b1), std::end(b1));
			return a1.compare(b1) < 0 ? true : false;
		}
		);

		std::string after = Debug::ToStr1D<std::string>()(strs);
		std::cout << "Anagrams Sort \"" << before << "\": " << after << std::endl;
	}

	//Leetcode: Find all anagrams in a string
	//Special case (fixed length window) of Stormrage
	std::vector<std::string> FindAllAnagramSubstr(const std::string & S, const std::string & T)
	{
		int N = S.size();
		int count = T.size();

		std::vector<int> charMap(256, 0);
		for (int i = 0; i < count; ++i)
			++charMap[T[i]];

		std::vector<int> foundMap(256, 0);
		int foundCount = 0;
		std::vector<std::string> res;

		//slide a fixed length window
		for (int end = 0; end < N; ++end)
		{
			int begin = end - count + 1;
			//1. add S[end]
			if (charMap[S[end]] > 0)
			{
				++foundMap[S[end]];
				if (foundMap[S[end]] <= charMap[S[end]])
					++foundCount;
				
				if (foundCount == count)
				{
					res.push_back(S.substr(begin, count));
				}
			}
			//2. remove S[begin] for next iteration
			if (begin >= 0 && foundMap[S[begin]] > 0)
			{
				--foundMap[S[begin]];
				if (foundMap[S[begin]] < charMap[S[begin]])
					--foundCount;
			}
		}
		std::cout << "Anagrams FindAllAnagramSubstr for \"" << S << "\", \"" << T << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	bool IsAnagram(const std::string & s, const std::string & t)
	{
		std::vector<int> charMap(26, 0);
		for (int i = 0; i < (int)s.size(); ++i)
			++charMap[s[i] - 'a'];

		std::vector<int> charMap2(26, 0);
		for (int i = 0; i < (int)t.size(); ++i)
			++charMap2[t[i] - 'a'];

		for (int i = 0; i < 26; ++i)
			if (charMap[i] != charMap2[i])
				return false;

		return true;
	}

	//Leetcode: Minimum Number of Steps to Make Two Strings Anagram
    int MinCharReplaceToMake2StrAnagram(std::string s, std::string t) //s.size()=t.size()
    {
        std::unordered_map<char, int> count;
        for (auto & c : s)
            ++count[c]; //positive count means extra chars in s
        for (auto & c : t)
            --count[c]; //negative count means extra chars in t
        int res = 0;
        for (auto & p : count)
            if (p.second < 0) //replace these chars in t w/ those chars in s, since they are equal-sized
                res += std::abs(p.second);

        std::cout << "Anagram MinCharReplaceToMake2StrAnagram for [\"" << s << "\", \"" << t << "\"]: " << res << std::endl;
        return res;
    }
};
/*
Row#0	= aet: tea, eat, ate
Row#1	= adn: and, dan
Row#2	= ad: ad
Row#3	= ace: ace, cae
Row#4	=   eeellnopstuvw: eleven plus two, twelve plus one

Anagrams FindAll in "tea, and, ace, ad, eat, dan, cae, ate, eleven plus two, twelve plus one" are: tea, eat, ate, and, dan, ace, cae, eleven plus two, twelve plus one
Anagrams Sort "tea, and, ace, ad, eat, dan, cae, ate, eleven plus two, twelve plus one": eleven plus two, twelve plus one, ace, cae, ad, and, dan, tea, eat, ate
Anagrams FindAllAnagramSubstr for "afdzyxyzcejyzxknyzxypq", "xyz": zyx, xyz, yzx, yzx, zxy
Anagrams FindAllAnagramSubstr for "afdzyxycejyzxkxyyxyxyq", "yxy": yxy, xyy, yyx, yxy, yxy
*/
#endif