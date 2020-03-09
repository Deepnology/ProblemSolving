/*Recur*DP*/
#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Compute the Levenshtein Distance
http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
Leetcode: Edit Distance
Notes:
Given two words word1 and word2, find the minimum number of steps required to convert
word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

Complexity:
DP, O(m*n) time, O(m*n) space
Squeeze memory, O(m*n) time, O(n) space

    a b c d (word1)
  0 1 2 3 4
a 1 0 1 2 3
x 2 1 1 2 3
c 3 2 2 1 2

(word2)

Solution:
dp[i][j] = dp[i-1][j-1] if (A[i-1]==B[j-1])
        or = min(dp[i][j-1],dp[i-1][j],dp[i-1][j-1]) + 1
init: dp[0][j] = j, dp[i][0] = i

Solution for LCS distance:
dp[i][j] = dp[i-1][j-1] + 1 if (A[i-1]==B[j-1])
        or = max(dp[i][j-1],dp[i-1][j])
init: dp[0][j] = 0, dp[i][0] = 0

see also KPalindrome.h

Leetcode: Delete Operation for Two Strings
Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same
, where in each step you can delete one character in either string.
Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Approach 1: use Edit Distance
Approach 2: use Longest Common Subsequence (res = Len1-LCS+Len2-LCS)
*/
#define IC 1 /*cost to insert*/
#define RC 1 /*cost to replace*/
#define DC 1 /*cost to delete*/
class EditDistance
{
public:
	EditDistance(){}
	~EditDistance(){}

	int Recur(std::string word1, std::string word2)//tail to head
	{
		int M = word1.size();
		int N = word2.size();
		int d = this->recur(word1, M, word2, N);
		std::cout << "EditDistance Recur to convert \"" << word1 << "\" to \"" << word2 << "\": " << d << std::endl;
		return d;
	}
private:
	int recur(std::string & word1, int i, std::string & word2, int j)
	{
		if (i == 0)
			return j;//use j insertions
		if (j == 0)
			return i;//use i deletions

		if (word1[i - 1] == word2[j - 1])
		{
			return this->recur(word1, i - 1, word2, j - 1);
		}
		else
		{
			int cost1, cost2, cost3;
			cost1 = RC + this->recur(word1, i - 1, word2, j - 1);//replace word1[i-1] with word2[j-1]
			cost2 = IC + this->recur(word1, i, word2, j - 1);//insert word1[i-1] with word2[j-1]
			cost3 = DC + this->recur(word1, i - 1, word2, j);//delete word1[i-1]
			return std::min(std::min(cost1, cost2), cost3);
		}
	}

public:
	int Recur2(std::string word1, std::string word2)//head to tail
	{
		int d = this->recur2(word1, 0, word2, 0);
		std::cout << "EditDistance Recur2 to convert \"" << word1 << "\" to \"" << word2 << "\": " << d << std::endl;
		return d;
	}
private:
	int recur2(std::string & word1, int i, std::string & word2, int j)
	{
		int M = word1.size();
		int N = word2.size();
		if (i == M)
			return N - j;//use N-j insertions on word1
		if (j == N)
			return M - i;//use M-i deletions on word1

		if (word1[i] == word2[j])
		{
			return this->recur2(word1, i + 1, word2, j + 1);
		}
		else
		{
			int cost1, cost2, cost3;
			cost1 = RC + this->recur2(word1, i + 1, word2, j + 1);//replace word1[i] with word2[j]
			cost2 = IC + this->recur2(word1, i, word2, j + 1);//insert word2[j] at word1[i]
			cost3 = DC + this->recur2(word1, i + 1, word2, j);//delete word1[i]
			return std::min(std::min(cost1, cost2), cost3);
		}
	}

public:
	int DP2D_Iterate(std::string word1, std::string word2)
	{
		int M = word1.size();
		int N = word2.size();
		std::vector<std::vector<int> > dp(M + 1, std::vector<int>(N + 1, 0));
		for (int i = 0; i <= M; ++i)
		{
			for (int j = 0; j <= N; ++j)
			{
				if (i == 0)
					dp[i][j] = j;
				else if (j == 0)
					dp[i][j] = i;
				else
				{
					dp[i][j] = std::min(
						std::min(
						dp[i][j - 1] + DC, //delete word1[i] from word1
						dp[i - 1][j] + IC), //insert word2[j] to word1
						(word1[i - 1] == word2[j - 1]) ? dp[i - 1][j - 1] : dp[i - 1][j - 1] + RC //replace word1[i] with word2[j] in word1
						//dp[i - 1][j - 1] + (word1[i - 1] != word2[j - 1]) * RC
						);
				}
			}
			//Debug::Print2D<int>()(dp, false);
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "EditDistance DP2D_Iterate to convert \"" << word1 << "\" to \"" << word2 << "\": " << dp[M][N] << std::endl;
		return dp[M][N];
	}

	int DP1D_Iterate(std::string word1, std::string word2)
	{
		int M = word1.size();
		int N = word2.size();
		std::vector<std::vector<int> > dp(2, std::vector<int>(N + 1, 0));
		int pre = -1, cur = 0;

		for (int j = 0; j <= N; ++j)
			dp[cur][j] = j;

		for (int i = 1; i <= M; i++) 
		{
			pre = cur;
			cur = !cur;
			for (int j = 0; j <= N; ++j) 
			{
				if (j == 0)
					dp[cur][j] = i;
				else
					dp[cur][j] = std::min(
					std::min(dp[cur][j - 1], dp[pre][j]) + 1,
					dp[pre][j - 1] + (word1[i - 1] != word2[j - 1])
					);
			}

			//Debug::Print2D<int>()(dp, false);
		}

		std::cout << "EditDistance DP1D_Iterate to convert \"" << word1 << "\" to \"" << word2 << "\": " << dp[cur][N] << std::endl;
		return dp[cur][N];
	}

	//Leetcode: Delete Operation for Two Strings
	int MinDistanceDeleteOnly(std::string word1, std::string word2)
	{
		int M = word1.size();
		int N = word2.size();
		std::vector<std::vector<int> > dp(M + 1, std::vector<int>(N + 1, 0));
		for (int i = 0; i <= M; ++i)
		{
			for (int j = 0; j <= N; ++j)
			{
				if (i == 0)
					dp[i][j] = j;
				else if (j == 0)
					dp[i][j] = i;
				else
				{
					if (word1[i - 1] == word2[j - 1])
						dp[i][j] = dp[i - 1][j - 1];
					else
						dp[i][j] = std::min(
							std::min(
								dp[i][j - 1] + 1, //delete word1[i] from word1
								dp[i - 1][j] + 1), //delete word2[j] from word2
							dp[i - 1][j - 1] + 2 //delete both word1[i] and word2[j]
						);
				}
			}
		}
		return dp[M][N];
	}
};

/*
EditDistance Recur to convert "abcd" to "axc": 2
EditDistance Recur2 to convert "abcd" to "axc": 2
[rY][cX]
Row#0	= 0, 1, 2, 3
Row#1	= 1, 0, 1, 2
Row#2	= 2, 1, 1, 2
Row#3	= 3, 2, 2, 1
Row#4	= 4, 3, 3, 2

EditDistance DP2D_Iterate to convert "abcd" to "axc": 2
EditDistance DP1D_Iterate to convert "abcd" to "axc": 2
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Row#1	= 1, 0, 1, 2, 3, 4, 5, 6, 7, 8
Row#2	= 2, 1, 0, 1, 2, 3, 4, 5, 6, 7
Row#3	= 3, 2, 1, 1, 2, 3, 4, 4, 5, 6
Row#4	= 4, 3, 2, 1, 2, 3, 3, 4, 5, 6
Row#5	= 5, 4, 3, 2, 2, 2, 3, 4, 5, 6
Row#6	= 6, 5, 4, 3, 2, 3, 3, 4, 5, 6
Row#7	= 7, 6, 5, 4, 3, 3, 3, 4, 5, 6
Row#8	= 8, 7, 6, 5, 4, 4, 4, 4, 4, 5
Row#9	= 9, 8, 7, 6, 5, 5, 5, 5, 5, 4

EditDistance DP2D_Iterate to convert "abxcdycba" to "abcydcxba": 4
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
Row#1	= 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9
Row#2	= 2, 2, 2, 1, 2, 3, 4, 5, 6, 7, 8
Row#3	= 3, 3, 3, 2, 2, 3, 4, 5, 5, 6, 7
Row#4	= 4, 4, 4, 3, 2, 3, 4, 4, 5, 6, 7
Row#5	= 5, 5, 5, 4, 3, 3, 3, 4, 5, 6, 7
Row#6	= 6, 6, 6, 5, 4, 3, 4, 4, 5, 6, 7
Row#7	= 7, 7, 7, 6, 5, 4, 4, 4, 5, 6, 7
Row#8	= 8, 8, 8, 7, 6, 5, 5, 5, 5, 5, 6
Row#9	= 9, 9, 8, 8, 7, 6, 6, 6, 6, 6, 5
Row#10	= 10, 9, 9, 9, 8, 7, 7, 7, 7, 7, 6

EditDistance DP2D_Iterate to convert "abxcdycbaz" to "zabcydcxba": 6
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Row#1	= 1, 1, 2, 3, 4, 5, 6, 7, 8, 9
Row#2	= 2, 2, 2, 3, 4, 5, 6, 7, 8, 8
Row#3	= 3, 3, 2, 3, 4, 5, 6, 7, 7, 8
Row#4	= 4, 4, 3, 3, 4, 5, 6, 6, 7, 8
Row#5	= 5, 5, 4, 4, 3, 4, 5, 6, 7, 8
Row#6	= 6, 6, 5, 5, 4, 4, 5, 6, 7, 8
Row#7	= 7, 7, 6, 6, 5, 5, 5, 6, 6, 7
Row#8	= 8, 8, 7, 7, 6, 6, 5, 6, 7, 7
Row#9	= 9, 9, 8, 8, 7, 6, 6, 6, 7, 8

EditDistance DP2D_Iterate to convert "Carthorse" to "Orchestra": 8
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6
Row#1	= 1, 0, 1, 2, 3, 4, 5
Row#2	= 2, 1, 1, 2, 3, 3, 4
Row#3	= 3, 2, 2, 2, 3, 4, 4
Row#4	= 4, 3, 2, 3, 3, 4, 5
Row#5	= 5, 4, 3, 3, 4, 4, 5
Row#6	= 6, 5, 4, 4, 3, 4, 5
Row#7	= 7, 6, 5, 5, 4, 3, 4
Row#8	= 8, 7, 6, 6, 5, 4, 3

EditDistance DP2D_Iterate to convert "Saturday" to "Sunday": 3
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7
Row#1	= 1, 1, 2, 3, 4, 5, 6, 7
Row#2	= 2, 2, 1, 2, 3, 4, 5, 6
Row#3	= 3, 3, 2, 1, 2, 3, 4, 5
Row#4	= 4, 4, 3, 2, 1, 2, 3, 4
Row#5	= 5, 5, 4, 3, 2, 2, 3, 4
Row#6	= 6, 6, 5, 4, 3, 3, 2, 3

EditDistance DP2D_Iterate to convert "kitten" to "sitting": 3
EditDistance DP1D_Iterate to convert "abxcdycba" to "abcydcxba": 4
EditDistance DP1D_Iterate to convert "abxcdycbaz" to "zabcydcxba": 6
EditDistance DP1D_Iterate to convert "Carthorse" to "Orchestra": 8
EditDistance DP1D_Iterate to convert "Saturday" to "Sunday": 3
EditDistance DP1D_Iterate to convert "kitten" to "sitting": 3
*/
#endif