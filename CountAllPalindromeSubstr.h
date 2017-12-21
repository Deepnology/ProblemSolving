#ifndef COUNT_ALL_PALINDROME_SUBSTR_H
#define COUNT_ALL_PALINDROME_SUBSTR_H
#include "Debug.h"
/*
Leetcode: Palindromic Substrings
http://www.geeksforgeeks.org/count-palindrome-sub-strings-string/
Given a string, count all palindrome substrings with length >= 2 in the given string.
input: abaab
output: 3 (aba, aa, baab)
input: abaaba
output: 5 (aba, aa, baab, aba, abaaba)
input: abbaeae
output: 4 (bb, abba, aea, eae)
input: abbaeaea
output: 6 (bb, abba, aea, eae, aea, aeaea)
*/
class CountAllPalindromeSubstr
{
public:
	CountAllPalindromeSubstr() {}
	int DP2D(std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));//dp[i][j]==1: s[i:j] is palindrome
		std::vector<std::vector<int>> dp2(N, std::vector<int>(N, 0));//dp2[i][j]: num of palindrome substr in s[i:j]
		for (int len = 1; len <= N; ++len)
		{
			for (int i = 0; i < N - len + 1; ++i)
			{
				int j = i + len - 1;
				if (len == 1)
					dp[i][j] = 1;//s[i] must be palindrome
				else if (len == 2)
				{
					if (s[i] == s[j])
					{
						dp[i][j] = 1;//s[i:j] is palindrome
						dp2[i][j] = 1;
					}
				}
				else
				{
					if (s[i] == s[j] && dp[i+1][j-1])
					{
						dp[i][j] = 1;//s[i:j] is palindrome
						dp2[i][j] = dp2[i + 1][j] + dp2[i][j - 1] + 1 - dp2[i + 1][j - 1];
						//increment and accumulate num of palindrome substr from both dp2[i + 1][j] and dp2[i][j - 1], then remove num of common palindrome substr dp2[i + 1][j - 1]
					}
					else
						dp2[i][j] = dp2[i + 1][j] + dp2[i][j - 1] - dp2[i + 1][j - 1];
						//accumulate num of palindrome substr from both dp2[i + 1][j] and dp2[i][j - 1], then remove num of common palindrome substr dp2[i + 1][j - 1]
				}
			}
		}

		Debug::Print2D<int>()(dp, false);
		Debug::Print2D<int>()(dp2, false);
		std::cout << "CountAllPalindromeSubstr DP2D for \"" << s << "\": " << dp2[0][N - 1] << std::endl;
		return dp2[0][N - 1];
	}

	//Leetcode: Palindromic Substrings (count all palindromic substrings w/ length >= 1)
	int DP2D_(std::string s)
	{
		int N = s.size();
		std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));//dp[i][j]==1: s[i:j] is palindrome
		std::vector<std::vector<int>> dp2(N, std::vector<int>(N, 0));//dp2[i][j]: num of palindrome substr in s[i:j]
		for (int len = 1; len <= N; ++len)
		{
			for (int i = 0; i < N - len + 1; ++i)
			{
				int j = i + len - 1;
				if (len == 1)
				{
					dp[i][j] = 1;//s[i] must be palindrome
					dp2[i][j] = 1;
				}
				else if (len == 2)
				{
					if (s[i] == s[j])
					{
						dp[i][j] = 1;//s[i:j] is palindrome
						dp2[i][j] = 3;
					}
					else
						dp2[i][j] = 2;
				}
				else
				{
					if (s[i] == s[j] && dp[i + 1][j - 1])
					{
						dp[i][j] = 1;//s[i:j] is palindrome
						dp2[i][j] = dp2[i + 1][j] + dp2[i][j - 1] + 1 - dp2[i + 1][j - 1];
						//increment and accumulate num of palindrome substr from both dp2[i + 1][j] and dp2[i][j - 1], then remove num of common palindrome substr dp2[i + 1][j - 1]
					}
					else
						dp2[i][j] = dp2[i + 1][j] + dp2[i][j - 1] - dp2[i + 1][j - 1];
						//accumulate num of palindrome substr from both dp2[i + 1][j] and dp2[i][j - 1], then remove num of common palindrome substr dp2[i + 1][j - 1]
				}
			}
		}
		return dp2[0][N - 1];
	}
	int Expand(std::string s)//O(N^2) time
	{
		int N = s.size();
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			expand(s, i, i, res);
			expand(s, i, i + 1, res);
		}
		return res;
	}
	void expand(const std::string & s, int left, int right, int & res)
	{
		int N = s.size();
		while (left >= 0 && right < N && s[left] == s[right])
		{
			--left;
			++right;
			++res;
		}
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 1, 0, 0
Row#1	= 0, 1, 0, 0, 1
Row#2	= 0, 0, 1, 1, 0
Row#3	= 0, 0, 0, 1, 0
Row#4	= 0, 0, 0, 0, 1

[rY][cX]
Row#0	= 0, 0, 1, 2, 3
Row#1	= 0, 0, 0, 1, 2
Row#2	= 0, 0, 0, 1, 1
Row#3	= 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0

CountAllPalindromeSubstr DP2D for "abaab": 3
[rY][cX]
Row#0	= 1, 0, 1, 0, 0, 1
Row#1	= 0, 1, 0, 0, 1, 0
Row#2	= 0, 0, 1, 1, 0, 0
Row#3	= 0, 0, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 1, 0
Row#5	= 0, 0, 0, 0, 0, 1

[rY][cX]
Row#0	= 0, 0, 1, 2, 3, 5
Row#1	= 0, 0, 0, 1, 2, 3
Row#2	= 0, 0, 0, 1, 1, 2
Row#3	= 0, 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

CountAllPalindromeSubstr DP2D for "abaaba": 5
[rY][cX]
Row#0	= 1, 0, 0, 1, 0, 0, 0
Row#1	= 0, 1, 1, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 0, 1, 0, 1
Row#5	= 0, 0, 0, 0, 0, 1, 0
Row#6	= 0, 0, 0, 0, 0, 0, 1

[rY][cX]
Row#0	= 0, 0, 1, 2, 2, 3, 4
Row#1	= 0, 0, 1, 1, 1, 2, 3
Row#2	= 0, 0, 0, 0, 0, 1, 2
Row#3	= 0, 0, 0, 0, 0, 1, 2
Row#4	= 0, 0, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 0

CountAllPalindromeSubstr DP2D for "abbaeae": 4
[rY][cX]
Row#0	= 1, 0, 0, 1, 0, 0, 0, 0
Row#1	= 0, 1, 1, 0, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 1, 0, 1, 0
Row#5	= 0, 0, 0, 0, 0, 1, 0, 1
Row#6	= 0, 0, 0, 0, 0, 0, 1, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1

[rY][cX]
Row#0	= 0, 0, 1, 2, 2, 3, 4, 6
Row#1	= 0, 0, 1, 1, 1, 2, 3, 5
Row#2	= 0, 0, 0, 0, 0, 1, 2, 4
Row#3	= 0, 0, 0, 0, 0, 1, 2, 4
Row#4	= 0, 0, 0, 0, 0, 0, 1, 2
Row#5	= 0, 0, 0, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0

CountAllPalindromeSubstr DP2D for "abbaeaea": 6
*/
#endif
