#ifndef VALIDATE_CAPITAL_STRING_H
#define VALIDATE_CAPITAL_STRING_H
#include "Debug.h"
/*
Leetcode: Detect Capital
Given a word, you need to judge whether the usage of capitals in it is right or not.
We define the usage of capitals in a word to be right when one of the following cases holds:
All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.
*/
class ValidateCapitalString
{
public:
	ValidateCapitalString() {}
	bool Iterate(std::string word)
	{
		bool res = iterate(word);
		std::cout << "ValidateCapitalString for \"" << word << "\": " << res << std::endl;
		return res;
	}
private:
	bool iterate(std::string word)
	{
		int N = word.size();
		int i = 0;
		bool h = isCapital(word[i++]);
		if (i == N) return true;
		bool h2 = isCapital(word[i++]);
		if (!h && h2) return false;//fA
		while (i < N)
		{
			if ((!h || !h2) && isCapital(word[i]))//faC, fAC, FaC
				return false;
			if ((h && h2) && !isCapital(word[i]))//FAc
				return false;
			++i;
		}
		return true;
	}
	bool isCapital(char c)
	{
		if ((c - 'A') >= 0 && (c - 'A') < 26)
			return true;
		return false;
	}
};
/*
ValidateCapitalString for "FACEBOOk": 0
ValidateCapitalString for "FaceBook": 0
ValidateCapitalString for "fAcebook": 0
ValidateCapitalString for "faceBook": 0
*/
#endif
