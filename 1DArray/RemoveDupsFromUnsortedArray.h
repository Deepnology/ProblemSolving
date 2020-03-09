#ifndef REMOVE_DUPS_FROM_UNSORTED_ARRAY_H
#define REMOVE_DUPS_FROM_UNSORTED_ARRAY_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=3515013
Cracking the coding interview: Array and String
Remove duplicated chars from a string in place.
See also RemoveDuplicatesFromSortedArray.h

Leetcode: Remove Duplicate Letters
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.
Example:
Given "bcabc"
Return "abc"
Given "cbacdcbc"
Return "acdb"
*/
class RemoveDupsFromUnsortedArray
{
public:
	RemoveDupsFromUnsortedArray(){}
	~RemoveDupsFromUnsortedArray(){}

	void InPlace_QuadraticTime(std::string && s)//O(n^2) time
	{
		int N = s.size();
		if (N < 2)
			return;
		std::string before = s;

		int newEnd = 0;
		for (int oldCur = 0; oldCur < N; ++oldCur)
		{
			int newCur = 0;
			for (; newCur < newEnd; ++newCur)
			{
				if (s[newCur] == s[oldCur])
					break;
			}
			if (newCur == newEnd)//found no duplicate of s[oldCur]
				s[newEnd++] = s[oldCur];//push back s[oldCur] to new array, advance newEnd
		}
		s = s.substr(0, newEnd);

		std::cout << "RemoveDupsFromUnsortedArray InPlace_QuadraticTime for \"" << before << "\": " << s << std::endl;
	}

	void CharVec_LinearTime(std::string && s)
	{
		int N = s.size();
		if (N < 2)
			return;
		std::string before = s;

		std::vector<int> visit(256, 0);
		int newEnd = 0;
		for (int oldCur = 0; oldCur < N; ++oldCur)
		{
			if (visit[s[oldCur]] == 0)//s[oldCur] hasn't been visited
			{
				s[newEnd++] = s[oldCur];//push back s[oldCur] to new array, advance newEnd
				visit[s[oldCur]] = 1;//mark as visited
			}
		}
		s = s.substr(0, newEnd);
		
		std::cout << "RemoveDupsFromUnsortedArray CharVec_LinearTime for \"" << before << "\": " << s << std::endl;
	}

};
class RemoveDupsFromUnsortedArrayMinLexicographical
{
public:
	RemoveDupsFromUnsortedArrayMinLexicographical() {}
	~RemoveDupsFromUnsortedArrayMinLexicographical() {}

	std::string SortedStack(const std::string & s)
	{
		int N = s.size();
		if (N < 2)
			return s;

		std::vector<int> count(256, 0);
		for (int i = 0; i < N; ++i)
			++count[s[i]];

		std::vector<int> visit(256, 0);//visit[i]==1 means char i has beed added to res
		std::string res;
		for (int i = 0; i < N; ++i)
		{
			--count[s[i]];
			if (visit[s[i]])
				continue;

			while (!res.empty() && s[i] < res.back() && count[res.back()] > 0)//keep res in ascending order (lexicographical order), pop out back char that can be added later
			{
				visit[res.back()] = 0;
				res.pop_back();
			}
			res.push_back(s[i]);
			visit[s[i]] = 1;
		}

		std::cout << "RemoveDupsFromUnsortedArrayMinLexicographical SortedStack for \"" << s << "\": " << res << std::endl;
		return res;
	}
};
/*
RemoveDupsFromUnsortedArray InPlace_QuadraticTime for "abcd": abcd
RemoveDupsFromUnsortedArray InPlace_QuadraticTime for "aaaa": a
RemoveDupsFromUnsortedArray InPlace_QuadraticTime for "aaabbb": ab
RemoveDupsFromUnsortedArray InPlace_QuadraticTime for "abababa": ab
RemoveDupsFromUnsortedArray CharVec_LinearTime for "abcd": abcd
RemoveDupsFromUnsortedArray CharVec_LinearTime for "aaaa": a
RemoveDupsFromUnsortedArray CharVec_LinearTime for "aaabbb": ab
RemoveDupsFromUnsortedArray CharVec_LinearTime for "abababa": ab
RemoveDupsFromUnsortedArrayMinLexicographical SortedStack for "bcabc": abc
RemoveDupsFromUnsortedArrayMinLexicographical SortedStack for "cbacdcbc": acdb
*/
#endif