#ifndef LEN_OF_LAST_WORD_H
#define LEN_OF_LAST_WORD_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
/*
Leetcode: Length Of Last Word
// Given a string s consists of upper/lower-case alphabets and empty space
// characters ' ', return the length of last word in the string.
//
// If the last word does not exist, return 0.
//
// Note: A word is defined as a character sequence consists of non-space
// characters only.
//
// For example,
// Given s = "Hello World",
// return 5.
//
// Complexity:
// O(n)
*/
class LenOfLastWord
{
public:
	LenOfLastWord(){}
	~LenOfLastWord(){}

	int Count(const char * s)
	{
		if (s == NULL || *s == '\0')
			return 0;
		int N = strlen(s);
		int i = N - 1;
		while (i >= 0 && isspace(s[i]))
			--i;
		int res = 0;
		while (i >= 0 && !isspace(s[i]))
		{
			--i;
			++res;
		}
		std::cout << "LenOfLastWord for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
LenOfLastWord for " hello world   ": 5
*/
#endif