/*Recur*DP*/
#ifndef _LCS_H_
#define _LCS_H_
//Longest Common Subsequence
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Compute the Levenshtein distance, variant
Given two strings A and B, compute a longest sequence of characters that is a subsequence of A and of B.
http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/

See also LongestPalindromeSubseq.h
*/

class LCS
{
public:
	LCS(){}
	~LCS(){}

	//O(2^N) time
	int Len_Recur(const std::string & X, const std::string & Y)
	{
		int len = this->recur(X, 0, Y, 0);
		std::cout << "LCS Len Recur for \"" << X << "\" and \"" << Y << "\": " << len << std::endl;
		return len;
	}
private:
	int recur(const std::string & X, int i, const std::string & Y, int j)
	{
		int N = X.size();
		int M = Y.size();
		if (i == N || j == M)
			return 0;

		if (X[i] == Y[j])
			return 1 + this->recur(X, i + 1, Y, j + 1);
		else
			return std::max(this->recur(X, i + 1, Y, j), this->recur(X, i, Y, j + 1));
	}

public:
	int Len_DP2D_Iterate(const std::string & X, const std::string & Y)//O(N*M) time
	{
		int N = X.size();
		int M = Y.size();
		std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1, 0));
		//dp[i][j]: LCS Len from X[0]~X[i-1] and Y[0]~[j-1]
		std::vector<std::vector<std::string>> dp2(N+1, std::vector<std::string>(M+1, ""));
		//dp2[i][j]: LCS from X[0]~X[i-1] and Y[0]~Y[j-1]
		for (int i = 0; i <= N; ++i)
		{	
			for (int j = 0; j <= M; ++j)
			{
				if (i == 0 || j == 0)//first row || first column
				{
					dp[i][j] = 0;
					dp2[i][j] = "";
				}
				else if (X[i - 1] == Y[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
					dp2[i][j] = dp2[i - 1][j - 1] + X[i - 1];
				}
				else
				{
					dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
					dp2[i][j] = dp2[i - 1][j].size() > dp2[i][j - 1].size() ? dp2[i - 1][j] : dp2[i][j - 1];
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "LCS Len DP2D_Iterate for \"" << X << "\" and \"" << Y << "\": " << dp[N][M] << ", " << dp2[N][M] << std::endl;
		return  dp[N][M];
	}
};
/*
LCS Len Recur for "abcedfghi" and "bxefhki": 5
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 1, 1, 1, 1, 1, 1, 1
Row#3	= 0, 1, 1, 1, 1, 1, 1, 1
Row#4	= 0, 1, 1, 2, 2, 2, 2, 2
Row#5	= 0, 1, 1, 2, 2, 2, 2, 2
Row#6	= 0, 1, 1, 2, 3, 3, 3, 3
Row#7	= 0, 1, 1, 2, 3, 3, 3, 3
Row#8	= 0, 1, 1, 2, 3, 4, 4, 4
Row#9	= 0, 1, 1, 2, 3, 4, 4, 5

LCS Len DP2D_Iterate for "abcedfghi" and "bxefhki": 5, befhi
*/



#endif

