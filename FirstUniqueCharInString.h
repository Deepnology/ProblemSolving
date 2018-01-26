#ifndef FIRST_UNIQUE_CHAR_IN_STRING_H
#define FIRST_UNIQUE_CHAR_IN_STRING_H
#include "Debug.h"
/*
Leetcode: First Unique Character in a String
Given a string, find the first non-repeating character in it and return it's index.
If it doesn't exist, return -1.
Examples:
s = "leetcode"
return 0.
s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.
see also FirstUniqueURL.h
*/
class FirstUniqueCharInString
{
public:
	FirstUniqueCharInString() {}

	int UseHashMapAndList(std::string s)
	{
		//similar to LRUCache
		std::list<int> charList;//list of idx of chars that appear for only once
		std::vector<std::pair<int, std::list<int>::iterator>> charMap(26, { 0,charList.end() });//count, itr to list
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			++charMap[s[i] - 'a'].first;
			if (charMap[s[i] - 'a'].first == 2)
			{
				charList.erase(charMap[s[i] - 'a'].second);
				//charMap[s[i]-'a'].second = charList.end();
			}
			if (charMap[s[i] - 'a'].first == 1)
			{
				charList.push_back(i);
				charMap[s[i] - 'a'].second = std::prev(charList.end());
			}
		}
		if (charList.empty()) return -1;
		return charList.front();
	}

	int UseHashMap(std::string s)
	{
		std::vector<int> count(26, 0);
		int N = s.size();
		for (int i = 0; i < N; ++i)
			++count[s[i]-'a'];
		for (int i = 0; i < N; ++i)
			if (count[s[i]-'a'] == 1)
				return i;
		return -1;
	}
};
#endif
