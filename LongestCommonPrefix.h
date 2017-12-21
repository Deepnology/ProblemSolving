/*SuffixArray*/
#ifndef LONGEST_COMMON_PREFIX_H
#define LONGEST_COMMON_PREFIX_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Longest Common Prefix
// Write a function to find the longest common prefix string amongst an array
// of strings.
//
// Complexity:
// O(NL) time, N is the size of input, L is the length of result
*/
class LongestCommonPrefix
{
public:
	LongestCommonPrefix(){}
	~LongestCommonPrefix(){}

	std::string MultiStrs(const std::vector<std::string> & strs)
	{
		if (strs.empty() || strs[0].empty())
			return "";
		
		int M = strs.size();
		int N = strs[0].size();
		bool identical = true;
		std::string lcp;
		for (int j = 0; j < N; ++j)//strs[0][0:N-1]
		{
			for (int i = 0; i < M; ++i)//strs[0:M-1]
			{
				if (j == (int)strs[i].size() || strs[i][j] != strs[0][j])
				{
					identical = false;
					lcp = strs[0].substr(0, j);
					break;
				}
			}
			if (!identical)
				break;
		}
		if (identical)
			lcp = strs[0];//now LCP of all strings in strs are same as strs[0]
		
		std::cout << "LongestCommonPrefix MultiStrs for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << lcp << std::endl;
		return lcp;
	}

	std::string TwoStrs(const std::string & s, const std::string & t)
	{
		int N = std::min(s.length(), t.length());
		std::string lcp;
		int i;
		for (i = 0; i < N; ++i)
		{
			if (s[i] != t[i])
			{
				lcp = s.substr(0, i);
				break;
			}
		}
		if (i == N)
			lcp = s.length() < t.length() ? s : t;
		
		std::cout << "LongestCommonPrefix TwoStrs for \"" << s << "\" and \"" << t << "\": " << lcp << std::endl;
		return lcp;
	}


};
/*
LongestCommonPrefix MultiStrs for "abcdef, abcxyz, abc, abc123, abcc": abc
LongestCommonPrefix TwoStrs for "abcxyzij" and "abcde": abc
LongestCommonPrefix MultiStrs for "cdef, abcxyz, xyz, ijk123, mnopq":
LongestCommonPrefix TwoStrs for "xyz" and "abcde":
LongestCommonPrefix MultiStrs for "abc, abc, abc, abc, abc": abc
LongestCommonPrefix TwoStrs for "abc" and "abcdef": abc
*/
#endif