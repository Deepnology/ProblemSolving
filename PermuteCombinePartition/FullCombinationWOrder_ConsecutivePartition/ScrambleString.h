/*Recur*DP*/
#ifndef SCRAMBLE_STRING_H
#define SCRAMBLE_STRING_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
https://github.com/anson627/leetcode/blob/master/ScrambleString/ScrambleString.cpp
http://www.lifeincode.net/programming/leetcode-scramble-string-java/
// Given a string s1, we may represent it as a binary tree by partitioning it
// to two non-empty substrings recursively.
//
// Below is one possible representation of s1 = "great":
//
//    great
//   /    \
//  gr    eat
// / \    /  \
//g   r  e   at
//           / \
//          a   t
//To scramble the string, we may choose any non-leaf node and swap its two
// children.
//
//For example, if we choose the node "gr" and swap its two children, it
// produces a scrambled string "rgeat".
//
//    rgeat
//   /    \
//  rg    eat
// / \    /  \
//r   g  e   at
//           / \
//          a   t
//We say that "rgeat" is a scrambled string of "great".
//
//Similarly, if we continue to swap the children of nodes "eat" and "at", it
// produces a scrambled string "rgtae".
//
//    rgtae
//   /    \
//  rg    tae
// / \    /  \
//r   g  ta  e
//       / \
//      t   a
//We say that "rgtae" is a scrambled string of "great".
//
//Given two strings s1 and s2 of the same length, determine if s2 is a
// scrambled string of s1.
//
// Complexity:
// O(n^3) time, O(n^3) space

If string s1 and s2 are scramble strings
, there must be a point that breaks s1 to two parts s11, s12
, and a point that breaks s2 to two parts, s21, s22
, and "isScramble(s11, s21) && isScramble(s12, s22)" is true
, OR "isScramble(s11, s22) && isScramble(s12, s21)" is true.

dp[i][j][k] == 1 means two substrings of length k
, one starts from i of string s1
, another one starts from j of string s2, are scramble.

The overall result can be determined at dp[0][0][N].
For every length k, we try to divide the string to two parts differently
, checking if there is a way that can make it true.
*/
class ScrambleString
{
public:
	ScrambleString(){}
	~ScrambleString(){}

	//faster
	bool Recur(const std::string & s1, const std::string & s2)
	{
		if (s1.size() != s2.size())
			return false;
		if (s1 == s2)
			return true;
		int N = s1.size();
		std::vector<std::vector<std::vector<int> > > memo(N + 1, std::vector<std::vector<int> >(N + 1, std::vector<int>(N + 1, -1)));
		bool res = this->recur(s1, s2, 0, 0, N, memo);

		Debug::Print3D<int>()(memo);
		std::cout << "ScrambleString Recur for \"" << s1 << "\" and \"" << s2 << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(const std::string & s1, const std::string & s2, int i, int j, int len
		, std::vector<std::vector<std::vector<int> > > & memo)
	{
		if (memo[i][j][len] != -1)
			return memo[i][j][len] == 1 ? true : false;
		if (len == 1)//base case for len==1
			return (memo[i][j][len] = (s1[i] == s2[j])) == 1 ? true : false;

		//k: length of s11 and s21
		//len-k: length of s12 and s22
		for (int k = 1; k < len; ++k)
		{
			if ((this->recur(s1, s2, i, j, k, memo) && this->recur(s1, s2, i + k, j + k, len - k, memo)) ||//isScramble(s11,s21,k) && isScramble(s12,s22,len-k)
				this->recur(s1, s2, i, j + len - k, k, memo) && this->recur(s1, s2, i + k, j, len - k, memo))//isScramble(s11,s22,k) && isScramble(s12,s21,len-k)
				return (memo[i][j][len] = 1) == 1 ? true : false;
		}

		return (memo[i][j][len] = 0) == 1 ? true : false;
	}

public:
	//slower
	bool DP3D(const std::string & s1, const std::string & s2)
	{
		if (s1.size() != s2.size())
			return false;
		int N = s1.size();
		std::vector<std::vector<std::vector<int> > > dp(N, std::vector<std::vector<int> >(N, std::vector<int>(N + 1, 0)));
		for (int len = 1; len <= N; ++len)
		{
			for (int i = 0; i <= N - len; ++i)
			{
				for (int j = 0; j <= N - len; ++j)
				{
					if (len == 1)
					{
						if (s1[i] == s2[j])//base case for len==1
							dp[i][j][len] = 1;
						continue;
					}

					//now len >= 2
					//k: length of s11 and s21
					//len-k: length of s12 and s22
					for (int k = 1; k < len; ++k)
					{
						if ((dp[i][j][k] && dp[i + k][j + k][len - k]) ||//isScramble(s11,s21,k) && isScramble(s12,s22,len-k)
							(dp[i][j + len - k][k] && dp[i + k][j][len - k]))//isScramble(s11,s22,k) && isScramble(s12,s21,len-k)
							dp[i][j][len] = 1;

						if (dp[i][j][len])
							break;
					}
				}
			}
			Debug::Print3D<int>()(dp);
		}
		std::cout << "ScrambleString DP3D for \"" << s1 << "\" and \"" << s2 << "\": " << dp[0][0][N] << std::endl;
		return dp[0][0][N] == 1 ? true : false;
	}
};
/*
[cX][rY][dZ]
Row#0	= -1,0,1,-1,-1,1.	-1,1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.
Row#1	= -1,1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.
Row#2	= -1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,0,-1,1,-1,-1.	-1,0,1,-1,-1,-1.	-1,1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.
Row#3	= -1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.
Row#4	= -1,0,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.
Row#5	= -1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.	-1,-1,-1,-1,-1,-1.

ScrambleString Recur for "great" and "rgtae": 1
[cX][rY][dZ]
Row#0	= 0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#1	= 0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#2	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.
Row#3	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.
Row#4	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.

[cX][rY][dZ]
Row#0	= 0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#1	= 0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#2	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.
Row#3	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.
Row#4	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.

[cX][rY][dZ]
Row#0	= 0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#1	= 0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#2	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,1,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.
Row#3	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.
Row#4	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.

[cX][rY][dZ]
Row#0	= 0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#1	= 0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#2	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,1,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.
Row#3	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.
Row#4	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.

[cX][rY][dZ]
Row#0	= 0,0,1,0,0,1.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#1	= 0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.
Row#2	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,0,1,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.
Row#3	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,0,1,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.
Row#4	= 0,0,0,0,0,0.	0,0,0,0,0,0.	0,1,0,0,0,0.	0,0,0,0,0,0.	0,0,0,0,0,0.

ScrambleString DP3D for "great" and "rgtae": 1
*/
#endif