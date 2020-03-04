/*Recur*DP*/
#ifndef K_PALINDROME_H
#define K_PALINDROME_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Valid Palindrome III
Elements of programming interview, DynamicProgramming: Compute the Levenshtein distance, variant
Given a string A, compute the minimum number of characters you need to delete from A to make the resulting string a palindrome.
Facebook
http://www.careercup.com/question?id=6287528252407808
http://www.geeksforgeeks.org/dynamic-programming-set-28-minimum-insertions-to-form-a-palindrome/
A K-palindrome is a string which transforms into a palindrome on removing/inserting at most K characters.
Given a string, determine if s is a K-palindrome.
Given a string, count the number of deletions/insertions of characters (K) to transform it into a palindrome.

Valid K
Recur: O(N^2) time
EditDistDP2D: O(N*(2K)) time, O(N*(2K)) space

Count K
Recur: O(N^2) time
DP2D: O(N^2) time, O(N^2) space
*/
class KPalindrome
{
public:
	KPalindrome(){}
	~KPalindrome(){}

	bool Valid_K_Recur(const std::string & s, int K)
	{
		int N = s.size();
		bool res = this->valid_K_recur(s, 0, N - 1, K);
		std::cout << "KPalindrome Valid_K_Recur for \"" << K << "\", \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	bool valid_K_recur(const std::string & s, int left, int right, int K)
	{
		while (left < right && s[left] == s[right])
		{
			++left;
			--right;
		}
		if (left >= right)
			return true;
		//now s[left:right] is not palindrome

		if (K == 0)
			return false;

		return this->valid_K_recur(s, left + 1, right, K - 1) ||//jump over s[left]
			this->valid_K_recur(s, left, right - 1, K - 1);//jump over s[right]
	}


public:
	bool Valid_K_EditDistWReverse(const std::string & s, int K)
	{
		std::string r(s);
		std::reverse(r.begin(), r.end());
		int N = s.size();
		/*
		Compute the edit distance to convert s into its reverse, r.
		We only need to compute the needed operations of deletion and insertion on s to convert to r.
		If the total number of operations of insertion and deletion required to transform s to r is N,
		the number of insertions must be N/2, and the number of deletions must be N/2
		, bc it is transformed into its reverse.
		Given K deletions, as long as we can transform s into its reverse with another K insertions
		(the edit distance between s and its reverse should be 2*K)
		, s will be a K-Palindrome.
		*/

		std::vector<std::vector<int> > dp(N + 1, std::vector<int>(N + 1, INT_MAX - N));//INT_MAX-N: to avoid overloading
		for (int i = 0; i <= N; ++i)
		{
			dp[i][0] = i;
			dp[0][i] = i;
		}
		for (int i = 1; i <= N; ++i)
		{
			int left = std::max(1, i - K);
			int right = std::min(N, i + K);
			for (int j = left; j <= right; ++j)
			{
				dp[i][j] = std::min(
					std::min(
					dp[i][j - 1] + 1, //delete s[i] from s
					dp[i - 1][j] + 1), //insert r[j] to s
					(s[i - 1] == r[j - 1]) ? dp[i - 1][j - 1] : INT_MAX //ignore replacement
					);
			}
		}
		Debug::Print2D<int>()(dp, false);
		bool res = dp[N][N] <= 2 * K ? true : false;
		std::cout << "KPalindrome Valid_K_EditDistWReverse <= 2*K for \"" << K << "\", \"" << s << "\": " << res << ". (Count_K: EditDistWReverse/2 = " << dp[N][N] / 2 << ")" << std::endl;
		return res;
	}


public:
	int Count_K_Recur(const std::string & s)
	{
		int N = s.size();
		int res = this->count_K_recur(s, 0, N - 1);
		std::cout << "KPalindrome Count_K_Recur for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	int count_K_recur(const std::string & s, int left, int right)
	{
		while (left < right && s[left] == s[right])
		{
			++left;
			--right;
		}
		if (left >= right)
			return 0;
		//now s[left:right] is not palindrome
		
		return std::min(this->count_K_recur(s, left + 1, right),
			this->count_K_recur(s, left, right - 1)) + 1;
	}

public:
	int Count_K_DP2D(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, 0));

		for (int len = 2; len <= N; ++len)//len is the length in between [left, right] inclusive
		{
			for (int left = 0; left < N - len + 1; ++left)
			{
				int right = left + len - 1;
				dp[left][right] = (s[left] == s[right]) ? dp[left + 1][right - 1] : (std::min(dp[left][right - 1], dp[left + 1][right]) + 1);
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "KPalindrome Count_K_DP2D for \"" << s << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}
};
/*
KPalindrome Valid_K_Recur for "2", "abxcdycba": 1
KPalindrome Valid_K_Recur for "2", "abxcdycbaz": 0
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Row#1	= 1, 0, 1, 2, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638
Row#2	= 2, 1, 0, 1, 2, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638
Row#3	= 3, 2, 1, 2, 3, 4, 2147483638, 2147483638, 2147483638, 2147483638
Row#4	= 4, 2147483638, 2, 1, 2, 3, 4, 2147483638, 2147483638, 2147483638
Row#5	= 5, 2147483638, 2147483638, 2, 3, 2, 3, 4, 2147483638, 2147483638
Row#6	= 6, 2147483638, 2147483638, 2147483638, 2, 3, 4, 5, 6, 2147483638
Row#7	= 7, 2147483638, 2147483638, 2147483638, 2147483638, 4, 3, 4, 5, 6
Row#8	= 8, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638, 4, 5, 4, 5
Row#9	= 9, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638, 2147483638, 6, 5, 4

KPalindrome Valid_K_EditDistWReverse <= 2*K for "2", "abxcdycba": 1. (Count_K: EditDistWReverse/2 = 2)
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
Row#1	= 1, 2, 1, 2, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637
Row#2	= 2, 3, 2, 1, 2, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637
Row#3	= 3, 4, 3, 2, 3, 4, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637
Row#4	= 4, 2147483637, 4, 3, 2, 3, 4, 2147483637, 2147483637, 2147483637, 2147483637
Row#5	= 5, 2147483637, 2147483637, 4, 3, 4, 3, 4, 2147483637, 2147483637, 2147483637
Row#6	= 6, 2147483637, 2147483637, 2147483637, 4, 3, 4, 5, 6, 2147483637, 2147483637
Row#7	= 7, 2147483637, 2147483637, 2147483637, 2147483637, 4, 5, 4, 5, 6, 2147483637
Row#8	= 8, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 6, 5, 6, 5, 6
Row#9	= 9, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 6, 7, 6, 5
Row#10	= 10, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 2147483637, 8, 7, 6

KPalindrome Valid_K_EditDistWReverse <= 2*K for "2", "abxcdycbaz": 0. (Count_K: EditDistWReverse/2 = 3)
KPalindrome Count_K_Recur for "abxcdycba": 2
KPalindrome Count_K_Recur for "abxcdycbaz": 3
KPalindrome Count_K_Recur for "abcd": 3
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 4, 3, 2
Row#1	= 0, 0, 1, 2, 3, 4, 3, 2, 3
Row#2	= 0, 0, 0, 1, 2, 3, 2, 3, 4
Row#3	= 0, 0, 0, 0, 1, 2, 1, 2, 3
Row#4	= 0, 0, 0, 0, 0, 1, 2, 3, 4
Row#5	= 0, 0, 0, 0, 0, 0, 1, 2, 3
Row#6	= 0, 0, 0, 0, 0, 0, 0, 1, 2
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0

KPalindrome Count_K_DP2D for "abxcdycba": 2
[rY][cX]
Row#0	= 0, 1, 2, 3, 4, 5, 4, 3, 2, 3
Row#1	= 0, 0, 1, 2, 3, 4, 3, 2, 3, 4
Row#2	= 0, 0, 0, 1, 2, 3, 2, 3, 4, 5
Row#3	= 0, 0, 0, 0, 1, 2, 1, 2, 3, 4
Row#4	= 0, 0, 0, 0, 0, 1, 2, 3, 4, 5
Row#5	= 0, 0, 0, 0, 0, 0, 1, 2, 3, 4
Row#6	= 0, 0, 0, 0, 0, 0, 0, 1, 2, 3
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 2
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

KPalindrome Count_K_DP2D for "abxcdycbaz": 3
[rY][cX]
Row#0	= 0, 1, 2, 3
Row#1	= 0, 0, 1, 2
Row#2	= 0, 0, 0, 1
Row#3	= 0, 0, 0, 0

KPalindrome Count_K_DP2D for "abcd": 3
*/
#endif