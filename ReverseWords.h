#ifndef _REVERSE_WORDS_H
#define _REVERSE_WORDS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Strings: Reverse all the words in a sentence
Leetcode: Reverse Words In a String
// Given an input string, reverse the string word by word. (The letters' order in each word is unchanged.)
//
// For example,
// Given s = "the sky is blue",
// return "blue is sky the".
//
// Clarification:
// What constitutes a word?
// A sequence of non-space characters constitutes a word.
// Could the input string contain leading or trailing spaces?
// Yes. However, your reversed string should not contain leading or trailing
// spaces.
// How about multiple spaces between two words?
// Reduce them to a single space in the reversed string.

Leetcode: Reverse Words in a String II
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces and the words are always separated by a single space.
For example,
Given s = "the sky is blue",
return "blue is sky the".
Could you do it in-place without allocating extra space?
*/
/*
Let the input string be ��i like this program very much��. The function should change the string to ��much very program this like i��
1) Reverse the individual words, we get the below string.
"i ekil siht margorp yrev hcum"
2) Reverse the whole string from start to end and you get the desired output.
"much very program this like i"
http://www.geeksforgeeks.org/archives/7150
http://stackoverflow.com/questions/198199/how-do-you-reverse-a-string-in-place-in-c-or-c

O(n) time
*/
class ReverseWords
{
public:
	ReverseWords(){}
	~ReverseWords(){}



	void ReverseChars(char s[])//the char* string must be contained in a char array. A string constant cannot be overwritten.
	{
		std::string before(s);
		this->ReverseChars(s, 0, strlen(s) - 1);
		//this->ReverseChars(s, s + strlen(s) - 1);
		/*
		char * end = s;
		while (*end)
			++end;
		this->ReverseChars(s, end - 1);
		*/
		std::cout << "ReverseChars for \"" << before << "\": \"" << s << "\"" << std::endl;
	}
	void ReverseChars(char A[], int first, int last)//Leetcode: Reverse String
	{
		while (first < last)
		{
			std::swap(A[first], A[last]);
			++first;
			--last;
		}
	}
	void ReverseChars(char * first, char * last)
	{
		while (first < last)
		{
			std::swap(*first, *last);
			++first;
			--last;
		}
	}

	//Leetcode: Reverse Words in a String
	void ReverseWordsInPlace_RemoveExtraSpace(std::string && s)
	{
		std::string before(s);
		/*
		int N = s.size();
		int wordBegin = -1;
		for (int i = 0; i < N;)
		{
			if (wordBegin == -1 && s[i] == ' ' && (i == N - 1 || s[i + 1] == ' '))//remove consecutive 2nd space
			{
				s.erase(i, 1);
				--N;
				continue;
			}
			if (wordBegin == -1 && s[i] != ' ')
			{
				wordBegin = i;
			}
			if (wordBegin != -1 && (i == N - 1 || s[i + 1] == ' '))
			{
				std::reverse(s.begin() + wordBegin, s.begin() + i + 1);//reverse a single word
				wordBegin = -1;
			}
			++i;
		}
		if (N > 0 && s[0] == ' ')//remove leading single space
		{
			s.erase(0, 1);
			--N;
		}
		std::reverse(s.begin(), s.end());//reverse the whole string
		*/
		int N = s.size();
		int begin = 0;
		while (begin < N)
		{
			while (begin < N && s[begin] == ' ')
				++begin;
			if (begin == N - 1) break;
			int end = begin;
			while (end < N && s[end] != ' ')
				++end;
			std::reverse(s.begin() + begin, s.begin() + end);
			begin = end;
		}
		std::reverse(s.begin(), s.end());
		int newEnd = 0;
		begin = 0;
		while (begin < N)
		{
			if (s[begin] != ' ')
				s[newEnd++] = s[begin++];
			else//space
			{
				int end = begin;
				while (end < N && s[end] == ' ')
					++end;

				if (end < N)//condition to insert space
				{
					//now end points to next char
					if (newEnd > 0)//skip leading space
						s[newEnd++] = ' ';
				}
				begin = end;
			}
		}
		s = s.substr(0, newEnd);

		std::cout << "ReverseWords InPlace_RemoveExtraSpace for \"" << before << "\": \"" << s << "\"" << std::endl;
	}

	//Leetcode: Reverse Words in a String II
	void ReverseWordsInPlace_KeepExtraSpace(std::string && s)
	{
		std::string before(s);
		/*
		int N = s.size();
		int wordBegin = -1;
		for (int i = 0; i < N; ++i)
		{
			if (wordBegin == -1 && s[i] != ' ')
			{
				wordBegin = i;
			}
			if (wordBegin != -1 && (i == N - 1 || s[i + 1] == ' '))
			{
				std::reverse(s.begin() + wordBegin, s.begin() + i + 1);//reverse a single word
				wordBegin = -1;
			}
		}
		std::reverse(s.begin(), s.end());//reverse the whole string
		*/
		int N = s.size();
		int begin = 0;
		while (begin < N)
		{
			while (begin < N && s[begin] == ' ')
				++begin;
			if (begin == N - 1) break;
			int end = begin;
			while (end < N && s[end] != ' ')
				++end;
			std::reverse(s.begin() + begin, s.begin() + end);
			begin = end;
		}
		std::reverse(s.begin(), s.end());

		std::cout << "ReverseWords InPlace_KeepExtraSpace for \"" << before << "\": \"" << s << "\"" << std::endl;
	}

	//Leetcode: Reverse Words in a String III
	void ReverseCharsInWordsInPlace_KeepExtraSpace(std::string && s)
	{
		std::string before(s);
		int N = s.size();
		int begin = 0;
		while (begin < N)
		{
			while (begin < N && s[begin] == ' ')
				++begin;
			if (begin == N - 1) break;
			int end = begin;
			while (end < N && s[end] != ' ')
				++end;
			std::reverse(s.begin() + begin, s.begin() + end);
			begin = end;
		}

		std::cout << "ReverseCharsInWords InPlace_KeepExtraSpace for \"" << before << "\": \"" << s << "\"" << std::endl;
	}
};

/*
ReverseChars for "abcdefg": "gfedcba"
ReverseWords InPlace_RemoveExtraSpace for " the  sky is   blue  ": "blue is sky the"
ReverseWords InPlace_KeepExtraSpace for " the  sky is   blue  ": "  blue   is sky  the "
ReverseCharsInWords InPlace_KeepExtraSpace for " the  sky is   blue  ": " eht  yks si   eulb  "
*/


#endif