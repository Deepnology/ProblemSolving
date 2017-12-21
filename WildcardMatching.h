/*MEMO*Recur*DP*/
#ifndef WILDCARD_MATCHING_H
#define WILDCARD_MATCHING_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Wildcard Matching
// Implement wildcard pattern matching with support for '?' and '*'.
//
// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
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
// isMatch("aa", "*") = true
// isMatch("aa", "a*") = true
// isMatch("ab", "?*") = true
// isMatch("aab", "c*a*b") = false

This problem (wildcard matching) is different from Perl "regex matching":
The ? operator will match the preceding atom zero or one times
The * operator will match the preceding atom zero or more times
*/
class WildcardMatching
{
public:
	WildcardMatching(){}
	~WildcardMatching(){}
public:
	bool IsMatch_Recur(const std::string & s, const std::string & p)//time limit exceeded
	{
		bool res = this->isMatch_Recur(s, 0, p, 0);
		std::cout << "WildcardMatching Recur for \"" << s << "\" and \"" << p << "\": " << res << std::endl;
		return res;
	}
private:
	bool isMatch_Recur(const std::string & s, int i, const std::string & p, int j)
	{
		int N = s.size();
		int M = p.size();
		if (j == M)
			return (i == N);

		//1. p[j] is '*'
		if (p[j] == '*')
		{
			while (i < N)
			{
				//try match 0 or more s[i] with ANY CHAR
				//consume as many matched chars as possible and jump if not valid for remaining regex matching
				if (this->isMatch_Recur(s, i, p, j + 1))
					return true;
				++i;//jump over matched chars
			}
			//now all matched char have been tested and jumpped
			return this->isMatch_Recur(s, i, p, j + 1);
		}

		else//2. p[j] isn't '*'
		{
			return i < N && (s[i] == p[j] || p[j] == '?') &&
				this->isMatch_Recur(s, i + 1, p, j + 1);
		}
	}
	
public:
	bool IsMatch_Iterate(const std::string & s, const std::string & p)//better
	{
		int N = s.size();
		int M = p.size();
		int i = 0;
		int j = 0;
		int iStarMatch = 0;
		int jStar = -1;
		bool res = true;
		while (i < N)
		{
			if (s[i] == p[j] || p[j] == '?')//matched
			{
				++i;
				++j;
			}
			else if (p[j] == '*')//not matched, but meet a '*'
			{
				jStar = j;//record star idx
				iStarMatch = i;//record star idx
				++j;//advance
			}
			else if (jStar != -1)//not matched, not '*', but have met a '*' before
			{
				j = jStar + 1;//reset j
				i = iStarMatch + 1;//reset i
				++iStarMatch;//advance
			}
			else//not matched, not '*', haven't met a '*' before
			{
				res = false;//s and p will never match
				break;
			}
		}

		if (res)
		{
			//now i == N
			//if j != M, the remainings of p must be all '*' to match s
			while (j < M && p[j] == '*')
				++j;
			res = j == M;
		}
		
		std::cout << "WildcardMatching Iterate for \"" << s << "\" and \"" << p << "\": " << res << std::endl;
		return res;
	}

public:
	bool IsMatch_DP2D(const std::string & s, const std::string & p)//memory limit exceeded
	{
		int N = s.size();
		int M = p.size();

		std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));
		dp[0][0] = 1;
		//dp[i][j] == 1: means s[i-1] matches p[j-1] so far

		for (int i = 0; i <= N; ++i)
		{
			for (int j = 1; j <= M; ++j)
			{
				if (p[j - 1] != '?' && p[j - 1] != '*')
				{
					if (i > 0 && s[i - 1] == p[j - 1] && dp[i - 1][j - 1])
						dp[i][j] = 1;
				}
				else if (p[j - 1] == '?')
				{
					if (i > 0)
						dp[i][j] = dp[i - 1][j - 1];
				}
				else
				{
					if (dp[i][j - 1])
						dp[i][j] = 1;
					else if (i > 0 && dp[i - 1][j])
						dp[i][j] = 1;
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "WildcardMatching DP2D for \"" << s << "\" and \"" << p << "\": " << dp[N][M] << std::endl;
		return dp[N][M] == 1 ? true : false;
	}
	bool IsMatch_DP2D_2(const std::string & s, const std::string & p)//memory limit exceeded
	{
		int N = s.size();
		int M = p.size();
		
		std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));
		dp[0][0] = 1;
		//dp[i][j] == 1: means s[i-1] matches p[j-1] so far

		for (int j = 1; j <= M; ++j)
		{
			//i == 0
			if (dp[0][j - 1] && p[j - 1] == '*')
				dp[0][j] = 1;
			//i > 0
			for (int i = 1; i <= N; ++i)
			{
				if (p[j - 1] == '*')
					dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
				else if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
					dp[i][j] = dp[i - 1][j - 1];
				else
					dp[i][j] = 0;
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "WildcardMatching DP2D_2 for \"" << s << "\" and \"" << p << "\": " << dp[N][M] << std::endl;
		return dp[N][M] == 1 ? true : false;
	}



public:
	bool IsMatch_Recur(const char * s, const char * p)
	{
		std::cout << "WildcardMatching Recur for \"" << s << "\" and \"" << p << "\": ";
		bool res = this->isMatch_Recur(s, p);
		std::cout << res << std::endl;
		return res;
	}
private:
	bool isMatch_Recur(const char * s, const char * p)
	{
		if (*p == '\0')
			return (*s == '\0');

		//1. *p is '*'
		if (*p == '*')
		{
			//now *s can match 0 or more any char
			while (*s != '\0')
			{
				//*s has matched 1 or more any char
				if (this->isMatch_Recur(s, p + 1))//next try match *s with *(p+1)
					return true;

				//*s doesn't match *(p+1)
				//=> next try match *s with one more any char
				++s;
			}

			//1). *s has matched 0 char or
			//2). *s has matched all its precedings before '\0'
			//=> next try match *s with *(p+1)
			return this->isMatch_Recur(s, p + 1);
		}

		//2. *p isn't '*'
		return ((*p == '?' && *s != '\0') || (*p == *s)) &&//*s matches *p ?
			this->isMatch_Recur(s + 1, p + 1);//*(s+1) matches *(p+1) ?
	}
public:
	bool IsMatch_Iterate(const char * sCurBegin, const char * pCurBegin)
	{
		std::cout << "WildcardMatching Iterate for \"" << sCurBegin << "\" and \"" << pCurBegin << "\": ";

		const char * sCurStarMatch = sCurBegin;
		const char * pCurStar = NULL;
		while (*sCurBegin != '\0')
		{
			//1. sCurBegin matches pCurBegin: advance both
			if ((*pCurBegin == '?') || (*pCurBegin == *sCurBegin))
			{
				++sCurBegin;
				++pCurBegin;
			}
			//2. doesn't match, but *pCurBegin == '*': just advance pCurBegin until pCurBegin != '*'
			else if (*pCurBegin == '*')
			{
				pCurStar = pCurBegin;//pCurStar will finally point to the last '*' of all continuous '*'
				sCurStarMatch = sCurBegin;//sCurStarMatch will finally point to the the first mismatch where pCurBegin is a '*'
				++pCurBegin;//advance pCurBegin
			}
			//3. doesn't match and *pCurBegin != '*', but sCurBegin matched pCurBegin with '*' before
			//now pCurStar still points to the last '*' of all continuous '*'
			else if (pCurStar != NULL)
			{
				pCurBegin = pCurStar + 1;//backtrace pCurBegin to the next char of pCurStar while advancing sCurBegin for '*'
				sCurBegin = sCurStarMatch + 1;//backtrace sCurBegin to the next char of sCurStarMatch
				++sCurStarMatch;//advance sCurStarMatch
			}
			//4. doesn't match, *pCurBegin != '*', and sCurBegin has never matched pCurBegin with '*' before
			else
			{
				std::cout << false << std::endl;
				return false;
			}
		}
		//now sCurBegin == '\0': all chars before sCurBegin have been matched
		//check if all remainings chars after pCurBegin are '*'
		while (*pCurBegin == '*')
			++pCurBegin;
		bool res = (*pCurBegin == '\0');
		std::cout << res << std::endl;
		return res;
	}
};
/*
WildcardMatching Recur for "aa" and "a": 0
WildcardMatching Recur for "aa" and "aa": 1
WildcardMatching Recur for "aaa" and "aa": 0
WildcardMatching Recur for "aa" and "*": 1
WildcardMatching Recur for "aa" and "a*": 1
WildcardMatching Recur for "ab" and "?*": 1
WildcardMatching Recur for "aab" and "c*a*b": 0
WildcardMatching Recur for "acc" and "a*b": 0
WildcardMatching Iterate for "aa" and "a": 0
WildcardMatching Iterate for "aa" and "aa": 1
WildcardMatching Iterate for "aaa" and "aa": 0
WildcardMatching Iterate for "aa" and "*": 1
WildcardMatching Iterate for "aa" and "a*": 1
WildcardMatching Iterate for "ab" and "?*": 1
WildcardMatching Iterate for "aab" and "c*a*b": 0
WildcardMatching Iterate for "acc" and "a*b": 0
[rY][cX]
Row#0	= 1, 0
Row#1	= 0, 1
Row#2	= 0, 0

WildcardMatching DP2D for "aa" and "a": 0
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 0, 1

WildcardMatching DP2D for "aa" and "aa": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 0, 1
Row#3	= 0, 0, 0

WildcardMatching DP2D for "aaa" and "aa": 0
[rY][cX]
Row#0	= 1, 1
Row#1	= 0, 1
Row#2	= 0, 1

WildcardMatching DP2D for "aa" and "*": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 1
Row#2	= 0, 0, 1

WildcardMatching DP2D for "aa" and "a*": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 1
Row#2	= 0, 0, 1

WildcardMatching DP2D for "ab" and "?*": 1
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0

WildcardMatching DP2D for "aab" and "c*a*b": 0
[rY][cX]
Row#0	= 1, 0, 0, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 0, 1, 0
Row#3	= 0, 0, 1, 0

WildcardMatching DP2D for "acc" and "a*b": 0
[rY][cX]
Row#0	= 1, 0
Row#1	= 0, 1
Row#2	= 0, 0

WildcardMatching DP2D_2 for "aa" and "a": 0
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 0, 1

WildcardMatching DP2D_2 for "aa" and "aa": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 0
Row#2	= 0, 0, 1
Row#3	= 0, 0, 0

WildcardMatching DP2D_2 for "aaa" and "aa": 0
[rY][cX]
Row#0	= 1, 1
Row#1	= 0, 1
Row#2	= 0, 1

WildcardMatching DP2D_2 for "aa" and "*": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 1
Row#2	= 0, 0, 1

WildcardMatching DP2D_2 for "aa" and "a*": 1
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 0, 1, 1
Row#2	= 0, 0, 1

WildcardMatching DP2D_2 for "ab" and "?*": 1
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0

WildcardMatching DP2D_2 for "aab" and "c*a*b": 0
[rY][cX]
Row#0	= 1, 0, 0, 0
Row#1	= 0, 1, 1, 0
Row#2	= 0, 0, 1, 0
Row#3	= 0, 0, 1, 0

WildcardMatching DP2D_2 for "acc" and "a*b": 0
*/
#endif