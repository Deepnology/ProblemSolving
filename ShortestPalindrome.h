#ifndef SHORTEST_PALINDROME_H
#define SHORTEST_PALINDROME_H
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Shortest Palindrome
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it.
Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".

Worst case: reverse(s.begin() + 1, s.end()) + s

Approach1:
find the "longest prefix palindrome of original string"
reverse the right part of the longest prefix panlindrome
then append original string to the back of reversed right part
O(n^2) time, O(1) space

Input: abbacd
longest prefix palindrome: abba
reverse the right part: dc
result: dc + abbacd = dcabbacd

Approach2:
concatenate s + reverse(s)
then find the LPS vector of the concat string
the last element in LPS vector is the length of "longest common prefix and suffix of the concat string"
, which is also the length of "longest prefix palindrom of original string"
then get the reverse of the right part of the longest prefix palindrome
, and append original string the the back of reversed right part, same as Approach1
O(n) time, O(n) space

Input: abbacd
concat: abbacd + dcabba = abbacddcabba
LPS:                      000100001234
reverse the right part: dc
result: dc + abbacd = dcabbacd

*/
class ShortestPalindrome
{
public:
	ShortestPalindrome(){}
	~ShortestPalindrome(){}

	std::string BruteForce(std::string s)
	{
		int N = s.size();
		if (N <= 1)
			return s;
		int mid = N / 2;
		int right = 1;//worst case: keep the first char
		for (int ctr = mid; ctr >= 1; --ctr)
		{
			if (this->expandReachBegin(s, ctr, ctr, right))
			{
				break;
			}
			if (this->expandReachBegin(s, ctr - 1, ctr, right))
			{
				break;
			}
		}

		std::string front = s;
		std::reverse(front.begin() + right, front.end());
		std::string res = front.substr(right) + s;

		std::cout << "ShortestPalindrome BruteForce for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	bool expandReachBegin(const std::string & s, int begin, int end, int & right)
	{
		while (begin >= 0 && s[begin] == s[end])
		{
			--begin;
			++end;
		}
		if (begin == -1)
		{
			right = end;//end is now the next right of matched palindrome
			return true;
		}
		else
			return false;
	}

public:
	std::string UseLPS_KMP(std::string s)
	{
		int N = s.size();
		if (N <= 1)
			return s;

		std::string r = s;
		std::reverse(r.begin(), r.end());
		std::string concat = s + r;
		std::vector<int> LPS = this->getLPSVector(concat, 2 * N);
		int lenLongestCommonPrefixSuffix = LPS.back();

		std::string res = r.substr(0, N - lenLongestCommonPrefixSuffix) + s;

		std::cout << "LPS for \"" << concat << "\": " << Debug::ToStr1D<int>()(LPS) << std::endl;
		std::cout << "ShortestPalindrome UseLPS_KMP for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	std::vector<int> getLPSVector(const std::string & needle, int M)
	{
		std::vector<int> LPS(M);

		int commonPrefixEnd = 0;
		int suffixEnd = 1;

		LPS[0] = 0;//init (prefix and suffix cannot overlap)

		for (; suffixEnd < M;)
		{
			if (needle[suffixEnd] == needle[commonPrefixEnd])
			{
				++commonPrefixEnd;
				LPS[suffixEnd] = commonPrefixEnd;
				++suffixEnd;
			}
			else
			{
				if (commonPrefixEnd != 0)
				{
					commonPrefixEnd = LPS[commonPrefixEnd - 1];//jump to previous commonPrefixEnd
				}
				else//commonPrefixEnd == 0, no common characters
				{
					LPS[suffixEnd] = 0;
					++suffixEnd;
				}
			}
		}
		return LPS;
	}
};
/*
ShortestPalindrome BruteForce for "abcd": dcbabcd
ShortestPalindrome BruteForce for "abbacd": dcabbacd
ShortestPalindrome BruteForce for "abba": abba
LPS for "abcddcba": 0, 0, 0, 0, 0, 0, 0, 1
ShortestPalindrome UseLPS_KMP for "abcd": dcbabcd
LPS for "abbacddcabba": 0, 0, 0, 1, 0, 0, 0, 0, 1, 2, 3, 4
ShortestPalindrome UseLPS_KMP for "abbacd": dcabbacd
LPS for "abbaabba": 0, 0, 0, 1, 1, 2, 3, 4
ShortestPalindrome UseLPS_KMP for "abba": abba
*/
#endif