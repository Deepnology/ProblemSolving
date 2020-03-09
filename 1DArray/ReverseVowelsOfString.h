#ifndef REVERSE_VOWELS_OF_STRING_H
#define REVERSE_VOWELS_OF_STRING_H
#include "Debug.h"
/*
Leetcode: Reverse Vowels of a String
Write a function that takes a string as input and reverse only the vowels of a string.
Example 1:
Given s = "hello", return "holle".
Example 2:
Given s = "leetcode", return "leotcede".
Note:
The vowels does not include the letter "y".
*/
class ReverseVowelsOfString
{
public:
	ReverseVowelsOfString() {}
	~ReverseVowelsOfString() {}

	void reverseVowels(std::string && s)
	{
		std::string before(s);
		int i = 0;
		int j = s.size() - 1;
		while (i < j)
		{
			if (isVowel(s[i]) && isVowel(s[j]))
			{
				std::swap(s[i], s[j]);
				++i, --j;
			}
			else if (isVowel(s[i]))
				--j;
			else
				++i;
		}

		std::cout << "ReverseVowelsOfString for \"" << before << "\": " << s << std::endl;
	}
private:
	bool isVowel(char c)
	{
		return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
	}
};
/*
ReverseVowelsOfString for "hello": holle
ReverseVowelsOfString for "leetcode": leotcede
*/
#endif
