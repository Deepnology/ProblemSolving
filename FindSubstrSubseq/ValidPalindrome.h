#ifndef VALID_PALINDROME_H
#define VALID_PALINDROME_H
#include "Debug.h"
/*
Leetcode: Valid Palindrome II
Given a non-empty string s, you may delete at most one character.
Judge whether you can make it a palindrome.
Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z.
The maximum length of the string is 50000.
*/
class ValidPalindrome
{
public:
	ValidPalindrome() {}

	bool Linear(std::string s)
	{
		int N = s.size();
		int left = 0;
		int right = N - 1;
		while (left < right)
		{
			if (s[left] != s[right])
				return valid(s, left + 1, right) || valid(s, left, right - 1);
			++left;
			--right;
		}
		return true;
	}
	bool valid(const std::string & s, int left, int right)
	{
		while (left < right)
		{
			if (s[left] != s[right])
				return false;
			++left;
			--right;
		}
		return true;
	}
};
#endif
