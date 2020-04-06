/*Recur*/
#ifndef EXTENDED_SIMPLE_REGEX_MATCHING_H
#define EXTENDED_SIMPLE_REGEX_MATCHING_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Implement regular expression matching
A simple regular expression (SRE) is an alphanumeric character, the metacharacter . (dot), an alphanumeric character or dot followed by the metacharacter * (star), or the concatenation of two simple regular expressions.
An extended simple regular expression (ESRE) is an SRE, an SRE prepended with the metacharacter ^, an SRE ended with the metacharacter $, or an SRE prepended with ^ and ended with $.

. matches any single character
* matches zero or more occurrences of the preceding regular expression
^ indicates the match must begin at the start of the string
$ indicates the match must end at the end of the string

An ESRE r that does not start with ^ or end with $ matches s if there is a substring t of s such that r strictly matches t.

See also RegexMatching.h
*/
class ExtendedSimpleRegexMatching
{
public:
	ExtendedSimpleRegexMatching(){}
	~ExtendedSimpleRegexMatching(){}

public:
	//Extended Simple Regular Expression includes ^ and $
	bool Recur(const std::string & regex, const std::string & str)
	{
		bool res = false;
		if (regex.front() == '^')
		{
			//special case of regex: ^
			res = this->recur(regex, 1, str, 0);
		}
		else
		{
			//as long as the regex matches a substring of str, we say regex matches str
			for (int i = 0; i <= (int)str.size(); ++i)
				if (this->recur(regex, 0, str, i))
				{
					res = true;
					break;
				}
		}

		std::cout << "ExtendedSimpleRegexMatching Recur for \"" << regex << "\" and \"" << str << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(const std::string & regex, int rBegin, const std::string & str, int sBegin)
	{
		//end of regex
		if (rBegin == (int)regex.size())
			return true;

		//special case of regex: $
		if (rBegin == (int)regex.size() - 1 && regex[rBegin] == '$')
			return sBegin == (int)str.size();

		//special case of regex: *
		if (rBegin + 1 < (int)regex.size() && regex[rBegin + 1] == '*')
		{
			//1. test 0 predecessor of *
			if (this->recur(regex, rBegin + 2, str, sBegin))
				return true;

			//2. test 1 or more predecessor of *
			while (sBegin < (int)str.size() && (regex[rBegin] == '.' || regex[rBegin] == str[sBegin]))
			{
				if (this->recur(regex, rBegin + 2, str, ++sBegin))
					return true;
			}
		}

		//general case
		return sBegin < (int)str.size() && (regex[rBegin] == '.' || regex[rBegin] == str[sBegin]) &&
			this->recur(regex, rBegin + 1, str, sBegin + 1);
	}
};
/*
ExtendedSimpleRegexMatching Recur for "a" and "aa": 1
ExtendedSimpleRegexMatching Recur for "aW9" and "xyaW9123": 1
ExtendedSimpleRegexMatching Recur for "a.9" and "xyaW9123": 1
ExtendedSimpleRegexMatching Recur for "^aW9" and "aW9123": 1
ExtendedSimpleRegexMatching Recur for "aW9$" and "xyaW9": 1
ExtendedSimpleRegexMatching Recur for "^aW9$" and "aW9": 1
ExtendedSimpleRegexMatching Recur for "^aW.*9$" and "aWxyz9": 1
*/
#endif