/*Recur*DP*/
#ifndef _LONGEST_PALINDROME_SUBSEQ_H_
#define _LONGEST_PALINDROME_SUBSEQ_H_
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Debug.h"
#include "LCS.h"
#include "ReverseWords.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/

See also LongestPalindromeSubstr.h, KPalindrome.h
*/
class LongestPalindromeSubseq
{
public:
	LongestPalindromeSubseq(){}
	~LongestPalindromeSubseq(){}


	/*find the length of longest palindrome subsequence recursively:
	用頭指針和尾指針
	1。若頭指針和尾指針指到同一個字元：則每個字元都是長度為1的palindrome
	2。若頭指針和尾指針指到的字元相同，且只有這二個字元：則這二個字串為長度為2的palindrome
	3。若頭指針和尾指針指到的字元相同，且字串長度大於2：往下遞迴，頭指針往右一位，尾指針往左一位，總長度加2
	4。否則繼續2個往下遞迴，分別是頭指針不動尾針指往前一位，和頭指針指往後一位尾指針不動，再較哪一個比較大
               L(0, 5)
             /        \ 
            /          \  
        L(1,5)          L(0,4)
       /    \            /    \
      /      \          /      \
  L(2,5)    L(1,4)  L(1,4)  L(0,3)  <--- 重複計算
	*/

	int Len_Recur(const std::string & s)//length of longest palindrome subsequence
	{
		int len = this->recur(s, 0, s.length() - 1);
		std::cout << "LongestPalindromeSubseq Recur for \"" << s << "\": " << len << std::endl;
		return len;
	}
private:
	int recur(const std::string & X, int start, int end)
	{
		if (start == end)
			return 1;
		if (X[start] == X[end])
		{
			if (start + 1 == end)
				return 2;
			else
				return this->recur(X, start + 1, end - 1) + 2;
		}
		return std::max(this->recur(X, start, end - 1), this->recur(X, start + 1, end));
	}


public:
	//time complexity: O(N^2)
	int Len_DP2D(const std::string & X)//length of longest palindrome subsequence
	{
		int N = X.length();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, 0));
		
		for (int i = 0; i < N; ++i)
			dp[i][i] = 1;

		/*
		Note that the lower diagonal values of dp are
		useless and not filled in the process. The values are filled in a
		manner similar to Matrix Chain Multiplication DP solution
		cl: the length of substring
		row i: head index of substring
		column j: tail index of substring
		dp value: length
		*/
		for (int curLen = 2; curLen <= N; ++curLen)
		{
			for (int curBegin = 0; curBegin < N - curLen + 1; ++curBegin)
			{
				int curEnd = curBegin + curLen - 1;
				if (X[curBegin] == X[curEnd] && curLen == 2)
					dp[curBegin][curEnd] = 2;
				else if (X[curBegin] == X[curEnd])
					dp[curBegin][curEnd] = dp[curBegin + 1][curEnd - 1] + 2;
				else
					dp[curBegin][curEnd] = std::max(dp[curBegin][curEnd - 1], dp[curBegin + 1][curEnd]);
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "LongestPalindromeSubseq DP2D for \"" << X << "\": " << dp[0][N - 1] << std::endl;
		return dp[0][N - 1];
	}



	/*
	1) Reverse the given sequence and store the reverse in another array say rev[0..n-1]
	2) LCS of the given sequence and rev[] will be the longest palindromic sequence.
	*/
	//time complexity: O(N^2)
	int Len_byLCS(const std::string & X)
	{
		std::string R(X);//use a container to hold X
		ReverseWords().ReverseChars(&R[0], &R[0] + R.size() - 1);
		std::cout << "Reverse \"" << X << "\" is \"" << R << "\"." << std::endl;

		unsigned int len = LCS().Len_DP2D_Iterate(X, R);

		std::cout << "LongestPalindromeSubseq by LongestCommonSubseq for \"" << X << "\": " << len << std::endl;
		return static_cast<int>(len);
	}
};
/*
LongestPalindromeSubseq Recur for "ydijkrlmlkjixabcbayz": 11
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 7, 9, 9, 9, 9, 9, 9, 9, 11, 11
Row#1	= 0, 1, 1, 1, 1, 1, 1, 1, 3, 5, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#2	= 0, 0, 1, 1, 1, 1, 1, 1, 3, 5, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9
Row#3	= 0, 0, 0, 1, 1, 1, 1, 1, 3, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
Row#4	= 0, 0, 0, 0, 1, 1, 1, 1, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
Row#5	= 0, 0, 0, 0, 0, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5
Row#6	= 0, 0, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 5
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 5
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 5
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 5, 5, 5
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 5, 5, 5
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 5, 5, 5
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 5, 5, 5
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3
Row#15	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1
Row#16	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1
Row#17	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1
Row#18	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1
Row#19	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1

LongestPalindromeSubseq DP2D for "ydijkrlmlkjixabcbayz": 11
Reverse "ydijkrlmlkjixabcbayz" is "zyabcbaxijklmlrkjidy".
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
Row#3	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
Row#4	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
Row#5	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
Row#6	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5
Row#7	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5
Row#8	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6
Row#9	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7
Row#10	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 8, 8, 8, 8, 8
Row#11	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 9, 9
Row#12	= 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#13	= 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#14	= 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#15	= 0, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#16	= 0, 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#17	= 0, 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 6, 7, 7, 8, 9, 10, 10, 10
Row#18	= 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 8, 9, 10, 10, 10
Row#19	= 0, 0, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 8, 9, 10, 10, 11
Row#20	= 0, 1, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 8, 9, 10, 10, 11

LCS Len DP2D_Iterate for "ydijkrlmlkjixabcbayz" and "zyabcbaxijklmlrkjidy": 11, yydiijjkkrllmllkkjjiixaabbcbbaayyz
LongestPalindromeSubseq by LongestCommonSubseq for "ydijkrlmlkjixabcbayz": 11
*/
#endif

