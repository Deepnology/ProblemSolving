/*HashTable*/
#ifndef ANONYMOUS_LETTER_H
#define ANONYMOUS_LETTER_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Ransom Note
Elements of programming interview, HashTable: Test if an anonymous letter is constructible
You are required to write a method which takes an anonymous letter L and text from a magazine M.
Your method is to return true if and only if L can be written using M,
i.e., if a letter appears k times in L, it must appear at least k times in M.

HashTable: O(n) time, O(c) space, where n is the length of M and c is the number of distinct characters in L.
*/
class AnonymousLetter
{
public:
	AnonymousLetter(){}
	~AnonymousLetter(){}

	bool Constructable_HashTable(const std::string & L, const std::string & M)
	{
		if (L.empty())
			return true;

		std::unordered_map<char, int> charMap;//first: char in L, second: count
		for (const char & c : L)
			++charMap[c];

		bool res = false;
		for (const char & c : M)
		{
			auto itr = charMap.find(c);
			if (itr != charMap.end())
			{
				--itr->second;
				if (itr->second == 0)
				{
					charMap.erase(itr);
					if (charMap.empty())
					{
						res = true;
						break;
					}
				}
			}
		}

		std::cout << "AnonymousLetter Constructable_HashTable for \"" << L << "\" in \"" << M << "\": " << res << std::endl;
		return res;
	}
};
/*
AnonymousLetter Constructable_HashTable for "abccaba" in "mcnbopqcrstauvacwcxyazb": 1
*/
#endif