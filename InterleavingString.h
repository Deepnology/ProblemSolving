/*Recur*DP*/
#ifndef INTERLEAVING_STRING_H
#define INTERLEAVING_STRING_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Test if s is an interleaving of s1 and s2
http://www.geeksforgeeks.org/check-whether-a-given-string-is-an-interleaving-of-two-other-given-strings-set-2/
Leetcode: Interleaving String
// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
// s3 is said to be interleaving s1 and s2, if it contains all characters of s1 and s2 
// and order of all characters in individual strings is preserved.
//
// For example,
// Given:
// s1 = "aabcc",
// s2 = "dbbca",
//
// When s3 = "aadbbcbcac", return true.
// When s3 = "aadbbbaccc", return false.
//
// Complexity:
// Recur: O(2^n) time
// DP2D: O(n^2) time, O(n^2) space

aadbbcbcac

    a a b c c (s1)
  1 1 1 0 0 0
d 0 0 1 1 0 0
b 0 0 1 1 1 0
b 0 0 1 0 1 0
c 0 0 1 1 1 0
a 0 0 0 0 1 1
(s2)

dp[i][j] = 1 if non-empty matched s1[] with s3[] (s1[i-1]==s3[i+j-1] && dp[i-1][j]) 
or non-empty matched s2[] with s3[] (s2[j-1]==s3[i+j-1] && dp[i][j-1])
init: dp[0][0] = 1 for empty s1 and s2 strings
*/
class InterleavingString
{
public:
	InterleavingString(){}
	~InterleavingString(){}

	bool Recur(const std::string & s1, const std::string & s2, const std::string & s3)
	{
		int n1 = s1.size();
		int n2 = s2.size();
		int n3 = s3.size();
		if (n3 != n1 + n2)
			return false;
		bool res = this->recur(s1, s2, s3, 0, 0, 0);
		std::cout << "InterleavingString Recur of \"" << s1 << "\" and \"" << s2 << "\" as \"" << s3 << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(const std::string & s1, const std::string & s2, const std::string & s3,
		int idx1, int idx2, int idx3)
	{
		int n1 = s1.size();
		int n2 = s2.size();
		int n3 = s3.size();

		if (idx3 == n3)
		{
			if (idx1 == n1 && idx2 == n2)
				return true;
			else
				return false;
		}

		return (s1[idx1] == s3[idx3] && this->recur(s1, s2, s3, idx1 + 1, idx2, idx3 + 1)) ||
			(s2[idx2] == s3[idx3] && this->recur(s1, s2, s3, idx1, idx2 + 1, idx3 + 1));
	}

public:
	bool DP2D(const std::string & s1, const std::string & s2, const std::string & s3)
	{
		int n1 = s1.size();
		int n2 = s2.size();
		if (s3.size() != n1 + n2)
			return false;

		std::vector<std::vector<int> > dp(n1 + 1, std::vector<int>(n2 + 1, 0));//std::vector<std::vector<bool> >
		/*
		dp[i][j] = 1: s3[0]~s3[i+j-1] is an interleaving of s1[0]~s1[i-1] and s2[0]~s2[j-1]
		*/

		for (int i = 0; i <= n1; ++i)
		{
			for (int j = 0; j <= n2; ++j)
			{
				if (i == 0 && j == 0)
					dp[i][j] = 1;//base case init for empty s1 and s2 strings

				/*1. non-empty matched s1[] with s3[]*/
				else if (i != 0 && s1[i - 1] == s3[i + j - 1] && dp[i - 1][j])
					dp[i][j] = 1;
				/*2. non-empty matched s2[] with s3[]*/
				else if (j != 0 && s2[j - 1] == s3[i + j - 1] && dp[i][j - 1])
					dp[i][j] = 1;
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "InterleavingString DP2D of \"" << s1 << "\" and \"" << s2 << "\" as \"" << s3 << "\": " << dp[n1][n2] << std::endl;
		return dp[n1][n2] == 1 ? true : false;
	}
};
/*
InterleavingString Recur of "aabcc" and "dbbca" as "aadbbcbcac": 1
InterleavingString Recur of "aabcc" and "dbbca" as "aadbbbaccc": 0
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 1, 1, 1, 0
Row#3	= 0, 1, 1, 0, 1, 0
Row#4	= 0, 0, 1, 1, 1, 1
Row#5	= 0, 0, 0, 1, 0, 1

InterleavingString DP2D of "aabcc" and "dbbca" as "aadbbcbcac": 1
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 1, 1, 0, 0
Row#3	= 0, 1, 1, 1, 0, 0
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

InterleavingString DP2D of "aabcc" and "dbbca" as "aadbbbaccc": 0
*/
#endif