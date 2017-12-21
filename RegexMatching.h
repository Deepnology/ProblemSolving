/*MEMO*Recur*DP*/
#ifndef REGEX_MATCHING_H
#define REGEX_MATCHING_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Regular Expression Matching
// Implement regular expression matching with support for '.' and '*'.
//
// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
//
// The matching should cover the entire input string (not partial).
//
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
//
// Some examples:
// isMatch("aa","a") = false
// isMatch("aa","aa") = true
// isMatch("aaa","aa") = false
// isMatch("aa", "a*") = true
// isMatch("aa", ".*") = true
// isMatch("ab", ".*") = true
// isMatch("aab", "c*a*b") = true

Perl regex matching:
The . operator will match any single character
The * operator will match the preceding atom zero or more times
The ? operator will match the preceding atom zero or one times

See also ExtendedSimpleRegexMatching.h
*/
class RegexMatching
{
public:
	RegexMatching(){}
	~RegexMatching(){}
public:
	bool IsMatch_Recur(const std::string & s, const std::string & p)//better
	{
		bool res = this->isMatch_Recur(s, 0, p, 0);
		std::cout << "RegexMatching Recur for \"" << s << "\" and \"" << p << "\": " << res << std::endl;
		return res;
	}
private:
	bool isMatch_Recur(const std::string & s, int i, const std::string & p, int j)
	{
		int N = s.size();
		int M = p.size();
		if (j == M)
			return (i == N);

		//1. p[j+1] is '*'
		if (j + 1 < M && p[j + 1] == '*')
		{
			//try match 0 or more s[i] with p[j]
			//consume as many matched chars as possible and jump if not valid for remaining regex matching
			while (i < N && (s[i] == p[j] || p[j] == '.'))
			{
				if (this->isMatch_Recur(s, i, p, j + 2))
					return true;
				++i;//jump over matched char
			}
			//now all matched char of p[j] have been tested and jumpped
			return this->isMatch_Recur(s, i, p, j + 2);
		}

		else//2. j==M-1 OR p[j+1] isn't '*'
		{
			return i < N && (s[i] == p[j] || p[j] == '.') &&
				this->isMatch_Recur(s, i + 1, p, j + 1);
		}
	}

public:
	bool IsMatch_DP2D(const std::string & s, const std::string & p)
	{
		int N = s.size();
		int M = p.size();
		std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));
		dp[0][0] = 1;
		//dp[i][j] == 1: means s[i-1] matches p[j-1] so far

		//special case for i==0: 
		for (int i = 0; i <= N; ++i)
		{
			for (int j = 1; j <= M; ++j)
			{
				if (p[j - 1] != '.' && p[j - 1] != '*')
				{
					if (i > 0 && s[i - 1] == p[j - 1] && dp[i - 1][j - 1])
						dp[i][j] = 1;
				}
				else if (p[j - 1] == '.')
				{
					if (i > 0 && dp[i - 1][j - 1])
						dp[i][j] = 1;
				}
				else if (j > 1)//p[j-1]=='*', but '*' cannot be the 1st element
				{
					if (dp[i][j - 1] || dp[i][j - 2])//match 0 or 1 preceding element
						dp[i][j] = 1;
					else if (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j])//match multiple preceding elements
						dp[i][j] = 1;
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "RegexMatching DP2D for \"" << s << "\" and \"" << p << "\": " << dp[N][M] << std::endl;
		return dp[N][M] == 1 ? true : false;
	}

public:
	bool IsMatch_Recur(const char * s, const char * p)
	{
		std::cout << "RegexMatching Recur for \"" << s << "\" and \"" << p << "\": ";
		bool res = this->isMatch_Recur(s, p);
		std::cout << res << std::endl;
		return res;
	}
private:
	bool isMatch_Recur(const char * s, const char * p)
	{
		if (*p == '\0')
			return (*s == '\0');

		//1. *p's next is '*'
		if (*(p + 1) == '*')
		{
			//now *s can match 0 or more *p
			while ((*p == *s) || (*p == '.' && *s != '\0'))//*s matches *p ?
			{
				//*s has matched 1 or more *p
				if (this->isMatch_Recur(s, p + 2))//next try match *s with *(p+2)
					return true;

				//*s doesn't match *(p+2)
				//=> next try match *s with one more *p
				++s;
			}

			//1). *s has matched 0 *p or
			//2). *s has matched all its precedings with *p
			//=> next try match *s with *(p+2)
			return this->isMatch_Recur(s, p + 2);
		}

		//2. *p's next isn't '*'
		return ((*p == *s) || (*p == '.' && *s != '\0')) &&//*s matches *p ?
			this->isMatch_Recur(s + 1, p + 1);//*(s+1) matches *(p+1) ?
	}
};
/*
RegexMatching Recur for "b" and "a*b": 1
RegexMatching Recur for "ab" and "a*b": 1
RegexMatching Recur for "aaaab" and "a*b": 1
RegexMatching Recur for "b" and "a*.": 1
RegexMatching Recur for "ab" and "a*.": 1
RegexMatching Recur for "aaaab" and "a*.": 1
RegexMatching Recur for "xyaW9123" and "a.9": 0
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 0, 0, 1

RegexMatching DP2D for "b" and "a*b": 1
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 0, 0, 1

RegexMatching DP2D for "ab" and "a*b": 1
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 0, 1, 0
Row#3	= 0, 0, 1, 0
Row#4	= 0, 0, 1, 0
Row#5	= 0, 0, 0, 1

RegexMatching DP2D for "aaaab" and "a*b": 1
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 0, 0, 1

RegexMatching DP2D for "b" and "a*.": 1
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 1, 1, 1
Row#2	= 0, 0, 0, 1

RegexMatching DP2D for "ab" and "a*.": 1
[rY][cX]
Row#0	= 1, 0, 1, 0
Row#1	= 0, 1, 1, 1
Row#2	= 0, 0, 1, 1
Row#3	= 0, 0, 1, 1
Row#4	= 0, 0, 1, 1
Row#5	= 0, 0, 0, 1

RegexMatching DP2D for "aaaab" and "a*.": 1
[rY][cX]
Row#0	= 1, 0, 0, 0
Row#1	= 0, 0, 0, 0
Row#2	= 0, 0, 0, 0
Row#3	= 0, 0, 0, 0
Row#4	= 0, 0, 0, 0
Row#5	= 0, 0, 0, 0
Row#6	= 0, 0, 0, 0
Row#7	= 0, 0, 0, 0
Row#8	= 0, 0, 0, 0

RegexMatching DP2D for "xyaW9123" and "a.9": 0
*/
#endif