/*Recur*DP*/
#ifndef DISTINCT_SUBSEQUENCES_H_
#define DISTINCT_SUBSEQUENCES_H_
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
// Leetcode: Distinct Subsequences
// Given a string S and a string T, count the number of distinct subsequences
// of T in S.
//
// A subsequence of a string is a new string which is formed from the original
// string by deleting some (can be none) of the characters without disturbing
// the relative positions of the remaining characters. (ie, "ACE" is a
// subsequence of "ABCDE" while "AEC" is not).
//
// Here is an example:
// S = "rabbbit", T = "rabbit"
//
// Return 3.
//
// Complexity:
// O(n^2) time O(n^2) space

    r a b b b i t (S)
  1 1 1 1 1 1 1 1
r 0 1 1 1 1 1 1 1
a 0 0 1 1 1 1 1 1
b 0 0 0 1 2 3 3 3
b 0 0 0 0 1 3 3 3
i 0 0 0 0 0 0 3 3
t 0 0 0 0 0 0 0 3
(T)

dp[i][j] = dp[i-1][j] + (S[i-1] == T[j-1] ? dp[i-1][j-1] : 0)
init: dp[i][0] = 1, dp[0][j] = 0
*/
class DistinctSubsequences
{
public:
	DistinctSubsequences(){}
	~DistinctSubsequences(){}

	int InExcludeRecur(std::string S, std::string T)
	{
		int N = S.size();
		int count = T.size();
		std::vector<std::vector<int> > memo(N + 1, std::vector<int>(count + 1, -1));
		int res = this->inExcludeRecur(S, T, 0, 0, memo);
		Debug::Print2D<int>()(memo, false);
		std::cout << "DistinctSubsequences InExcludeRecur of \"" << S << "\" and \"" << T << "\" is: " << res << std::endl;
		return res;
	}
private:
	int inExcludeRecur(std::string & S, std::string & T, int i, int j, std::vector<std::vector<int> > & memo)
	{
		int N = S.size();
		int count = T.size();
		if (memo[i][j] != -1) return memo[i][j];
		if (j == count) return memo[i][j] = 1;
		if (i == N) return memo[i][j] = 0;

		int exclude = this->inExcludeRecur(S, T, i + 1, j, memo);
		int include = 0;
		if (S[i] == T[j])
			include = this->inExcludeRecur(S, T, i + 1, j + 1, memo);

		return memo[i][j] = exclude + include;
	}
public:
	int DP_2D(std::string S, std::string T)
	{
		int N = S.size();
		int count = T.size();
		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(count + 1, 0));
		for (int i = 0; i <= N; ++i)
		{
			for (int j = 0; j <= count; ++j)
			{
				if (j == 0)
					dp[i][j] = 1;
				else if (i == 0)
					dp[i][j] = 0;
				else
					dp[i][j] = dp[i - 1][j] + //exclude
					((S[i - 1] == T[j - 1]) ? dp[i - 1][j - 1] : 0);//include
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "DistinctSubsequences DP_2D of \"" << S << "\" and \"" << T << "\" is: " << dp[N][count] << std::endl;
		return dp[N][count];
	}

	int DP_1D(std::string S, std::string T)
	{
		int N = S.size();
		int count = T.size();
		std::vector<int> dp(count + 1, 0);
		for (int i = 1; i <= N; ++i)
		{
			dp[0] = 1;
			for (int j = count; j > 0; --j)
				dp[j] += ((S[i - 1] == T[j - 1]) ? dp[j - 1] : 0);

			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::cout << "DistinctSubsequences DP_1D of \"" << S << "\" and \"" << T << "\" is: " << dp[count] << std::endl;
		return dp[count];
	}

};
/*
[rY][cX]
Row#0	= 3, -1, -1, -1, -1, -1, -1
Row#1	= 0, 3, -1, -1, -1, -1, -1
Row#2	= 0, 0, 3, -1, -1, -1, -1
Row#3	= 0, 0, 1, 2, -1, -1, -1
Row#4	= 0, 0, 0, 1, 1, -1, -1
Row#5	= 0, 0, 0, 0, 1, -1, -1
Row#6	= 0, 0, 0, 0, 0, 1, -1
Row#7	= 0, 0, 0, 0, 0, 0, 1

DistinctSubsequences InExcludeRecur of "rabbbit" and "rabbit" is: 3
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0, 0
Row#1	= 1, 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 1, 0, 0, 0, 0
Row#3	= 1, 1, 1, 1, 0, 0, 0
Row#4	= 1, 1, 1, 2, 1, 0, 0
Row#5	= 1, 1, 1, 3, 3, 0, 0
Row#6	= 1, 1, 1, 3, 3, 3, 0
Row#7	= 1, 1, 1, 3, 3, 3, 3

DistinctSubsequences DP_2D of "rabbbit" and "rabbit" is: 3
1, 1, 0, 0, 0, 0, 0
1, 1, 1, 0, 0, 0, 0
1, 1, 1, 1, 0, 0, 0
1, 1, 1, 2, 1, 0, 0
1, 1, 1, 3, 3, 0, 0
1, 1, 1, 3, 3, 3, 0
1, 1, 1, 3, 3, 3, 3
DistinctSubsequences DP_1D of "rabbbit" and "rabbit" is: 3
[rY][cX]
Row#0	= 1, -1, -1, -1
Row#1	= 0, 1, -1, -1
Row#2	= 0, 1, -1, -1
Row#3	= 0, 0, 1, -1
Row#4	= 0, 0, 1, -1
Row#5	= 0, 0, 0, 1

DistinctSubsequences InExcludeRecur of "abcde" and "ace" is: 1
[rY][cX]
Row#0	= 1, 0, 0, 0
Row#1	= 1, 1, 0, 0
Row#2	= 1, 1, 0, 0
Row#3	= 1, 1, 1, 0
Row#4	= 1, 1, 1, 0
Row#5	= 1, 1, 1, 1

DistinctSubsequences DP_2D of "abcde" and "ace" is: 1
1, 1, 0, 0
1, 1, 0, 0
1, 1, 1, 0
1, 1, 1, 0
1, 1, 1, 1
DistinctSubsequences DP_1D of "abcde" and "ace" is: 1
[rY][cX]
Row#0	= 0, -1, -1, -1
Row#1	= 0, 0, -1, -1
Row#2	= 0, 0, -1, -1
Row#3	= 0, 0, -1, -1
Row#4	= 0, 0, -1, -1
Row#5	= 0, 0, 0, -1

DistinctSubsequences InExcludeRecur of "abcde" and "aec" is: 0
[rY][cX]
Row#0	= 1, 0, 0, 0
Row#1	= 1, 1, 0, 0
Row#2	= 1, 1, 0, 0
Row#3	= 1, 1, 0, 0
Row#4	= 1, 1, 0, 0
Row#5	= 1, 1, 1, 0

DistinctSubsequences DP_2D of "abcde" and "aec" is: 0
1, 1, 0, 0
1, 1, 0, 0
1, 1, 0, 0
1, 1, 0, 0
1, 1, 1, 0
DistinctSubsequences DP_1D of "abcde" and "aec" is: 0
*/
#endif