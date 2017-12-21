/*Recur*DP*/
#ifndef PALINDROME_PARTITIONING_H
#define PALINDROME_PARTITIONING_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate palindromic decompositions
Compute all palindromic decompositions of a given string.
Elements of programming interview, DynamicProgramming: Decompose into palindromic strings
How would you compute a palindromic decomposition of a string s that uses a minimum number of substrings?
Leetcode: Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition
// is a palindrome.
//
// Return all possible palindrome partitioning of s.
//
// For example, given s = "aab",
// Return
//
//   [
//       ["aa","b"],
//       ["a","a","b"]
//   ]
//
// Complexity:
// Recursion, O(2^n) time
// DP, O(n^2) time, O(n^3) space

http://www.geeksforgeeks.org/dynamic-programming-set-17-palindrome-partitioning/
Leetcode: Palindrome Partitioning II
// Given a string s, partition s such that every substring of the partition
// is a palindrome.
//
// Return the minimum cuts needed for a palindrome partitioning of s.
//
// For example, given s = "aab",
// Return 1 since the palindrome partitioning ["aa","b"] could be produced
// using 1 cut.
//
// Complexity:
// O(n^2) time, O(n^2) space
//
// See also WordBreak.h
*/
class PalindromePartitioning
{
public:
	PalindromePartitioning(){}
	~PalindromePartitioning(){}
	//1
	//1.1 Recur, O(2^n) time
	std::vector<std::vector<std::string> > FindAll_Recur(std::string s)
	{
		std::vector<std::vector<std::string> > res;
		std::vector<std::string> path;

		this->buildPalindromePathRecur(s, 0, path, res);

		std::cout << "PalindromePartitioning FindAll_Recur for " << s << ":" << std::endl;
		Debug::Print2D<std::string>()(res, false);
		return res;
	}
private:
	void buildPalindromePathRecur(std::string & s, int start, std::vector<std::string> & path
		, std::vector<std::vector<std::string> > & res)
	{
		int N = s.size();
		if (start == N)
		{
			res.push_back(path);
			return;
		}

		for (int end = start; end < N; ++end)//check each palindrome substr in the range of s[start]~s[N-1] at the current index.
		{
			if (!this->validPalindromeSubstr(s, start, end))
				continue;

			//now found a valid palindrome segment s[start]~s[end]
			path.push_back(s.substr(start, end - start + 1));//put current palindrome segment s[start]~s[end] to path
			this->buildPalindromePathRecur(s, end + 1, path, res);//build the path from the remaining substr s[end+1]~s[N-1]
			path.pop_back();
		}
	}
	bool validPalindromeSubstr(std::string & s, int start, int end)
	{
		while (start < end && s[start] == s[end])
		{
			++start;
			--end;
		}
		return (start >= end);
	}

	//1.2 DP2D, O(n^2) time, O(n^3) space. see also WordBreak.h
public:
	std::vector<std::vector<std::string> > FindAll_DP2D(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N, 0));
		//dp[left][right]==1 means s[left]~s[right] is a palindrome

		std::vector<std::vector<std::vector<std::string> > > breakables(N, std::vector<std::vector<std::string> >());
		//breakables[right] is a vector of "vector of palindrome segments till right (s[0]~s[right])"

		//enumerate all possible substrings
		for (int right = 0; right < N; ++right)
		{
			for (int left = 0; left <= right; ++left)
			{
				if (s[left] == s[right] &&
					(right - left < 2 || //0: 1 char; 1: two same chars
					dp[left + 1][right - 1])//s[left+1]~s[right-1] is a palindrome
					)
				{
					//s[left]~s[right] is a palindrome
					dp[left][right] = 1;

					if (left == 0)
					{
						//add the 1st vector of palindrome segments till right (s[0]~s[right])
						breakables[right].push_back(std::vector<std::string>(1, s.substr(left, right - left + 1)));
					}
					else
					{
						/*
						append prev vectors of palindrome segments till left-1 with current palindrome segment s[left]~s[right]
						, then add all vectors of palindrome segments till right to breakables[right]
						*/
						for (auto palindromeSegments : breakables[left - 1])
						{
							palindromeSegments.push_back(s.substr(left, right - left + 1));
							breakables[right].push_back(palindromeSegments);
						}
					}
				}
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "PalindromePartitioning FindAll_DP2D for " << s << ":" << std::endl;
		Debug::Print2D<std::string>()(breakables[N - 1], false);
		return breakables[N - 1];
	}

	//2.
	//2.1
	int CountMinCut_DP2D_1(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dpPalindrome(N, std::vector<int>(N, 0));
		//dpPalindrome[left][right]==1 means s[left]~s[right] is a palindrome

		std::vector<int> dpCut(N, 0);
		//dpCut[right] means the number of cuts of s[0]~s[right]

		for (int right = 1; right < N; ++right)
		{
			dpCut[right] = right;//initial value is cut between each char which is the max for s[0]~s[right]
			for (int left = 0; left <= right; ++left)
			{
				if (s[left] == s[right] && (right - left < 2 || dpPalindrome[left + 1][right - 1]))
				{
					//now s[left]~s[right] is a palindrome
					dpPalindrome[left][right] = 1;
					dpCut[right] = std::min(dpCut[right], (left == 0) ? 0 : dpCut[left - 1] + 1);
				}
			}
		}
		Debug::Print2D<int>()(dpPalindrome, false);
		std::cout << Debug::ToStr1D<int>()(dpCut) << std::endl;
		std::cout << "PalindromePartitioning CountMinCut_DP2D_1 for " << s << " is " << dpCut[N - 1] << std::endl;
		return dpCut[N - 1];
	}

	//2.2
	int CountMinCut_DP2D_2(const std::string & s)
	{
		int N = s.size();
		std::vector<std::vector<int> > dpPalindrome(N, std::vector<int>(N, 0));
		//dpPalindrome[left][right]==1 means s[left]~s[right] is a palindrome

		for (int len = 1; len <= N; ++len)
		{
			for (int left = 0; left < N - len + 1; ++left)
			{
				int right = left + len - 1;
				if (s[left] == s[right] && (len <= 2 || dpPalindrome[left + 1][right - 1]))
					dpPalindrome[left][right] = 1;
			}
		}

		std::vector<int> dpCut(N, 0);
		//dpCut[right] means the number of cuts of s[0]~s[right]

		for (int right = 1; right < N; ++right)
		{
			dpCut[right] = right;//initial value is cut between each char which is the max for s[0]~s[right]
			for (int left = 0; left <= right; ++left)
			{
				if (dpPalindrome[left][right])//if s[left]~s[right] is a palindrome
					dpCut[right] = std::min(dpCut[right], (left == 0) ? 0 : dpCut[left - 1] + 1);
			}
		}
		Debug::Print2D<int>()(dpPalindrome, false);
		std::cout << Debug::ToStr1D<int>()(dpCut) << std::endl;
		std::cout << "PalindromePartitioning CountMinCut_DP2D_2 for " << s << " is " << dpCut[N - 1] << std::endl;
		return dpCut[N - 1];
	}
};
/*
PalindromePartitioning FindAll_Recur for babcbabcbaccba:
[rY][cX]
Row#0	= b, a, b, c, b, a, b, c, b, a, c, c, b, a
Row#1	= b, a, b, c, b, a, b, c, b, a, cc, b, a,
Row#2	= b, a, b, c, b, a, bcb, a, c, c, b, a,  ,
Row#3	= b, a, b, c, b, a, bcb, a, cc, b, a,  ,  ,
Row#4	= b, a, b, c, b, abcba, c, c, b, a,  ,  ,  ,
Row#5	= b, a, b, c, b, abcba, cc, b, a,  ,  ,  ,  ,
Row#6	= b, a, b, c, bab, c, b, a, c, c, b, a,  ,
Row#7	= b, a, b, c, bab, c, b, a, cc, b, a,  ,  ,
Row#8	= b, a, b, cbabc, b, a, c, c, b, a,  ,  ,  ,
Row#9	= b, a, b, cbabc, b, a, cc, b, a,  ,  ,  ,  ,
Row#10	= b, a, bcb, a, b, c, b, a, c, c, b, a,  ,
Row#11	= b, a, bcb, a, b, c, b, a, cc, b, a,  ,  ,
Row#12	= b, a, bcb, a, bcb, a, c, c, b, a,  ,  ,  ,
Row#13	= b, a, bcb, a, bcb, a, cc, b, a,  ,  ,  ,  ,
Row#14	= b, a, bcb, abcba, c, c, b, a,  ,  ,  ,  ,  ,
Row#15	= b, a, bcb, abcba, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#16	= b, a, bcbabcb, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#17	= b, a, bcbabcb, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#18	= b, abcba, b, c, b, a, c, c, b, a,  ,  ,  ,
Row#19	= b, abcba, b, c, b, a, cc, b, a,  ,  ,  ,  ,
Row#20	= b, abcba, bcb, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#21	= b, abcba, bcb, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#22	= b, abcbabcba, c, c, b, a,  ,  ,  ,  ,  ,  ,  ,
Row#23	= b, abcbabcba, cc, b, a,  ,  ,  ,  ,  ,  ,  ,  ,
Row#24	= bab, c, b, a, b, c, b, a, c, c, b, a,  ,
Row#25	= bab, c, b, a, b, c, b, a, cc, b, a,  ,  ,
Row#26	= bab, c, b, a, bcb, a, c, c, b, a,  ,  ,  ,
Row#27	= bab, c, b, a, bcb, a, cc, b, a,  ,  ,  ,  ,
Row#28	= bab, c, b, abcba, c, c, b, a,  ,  ,  ,  ,  ,
Row#29	= bab, c, b, abcba, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#30	= bab, c, bab, c, b, a, c, c, b, a,  ,  ,  ,
Row#31	= bab, c, bab, c, b, a, cc, b, a,  ,  ,  ,  ,
Row#32	= bab, cbabc, b, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#33	= bab, cbabc, b, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#34	= babcbab, c, b, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#35	= babcbab, c, b, a, cc, b, a,  ,  ,  ,  ,  ,  ,

[rY][cX]
Row#0	= 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1

PalindromePartitioning FindAll_DP2D for babcbabcbaccba:
[rY][cX]
Row#0	= b, abcbabcba, cc, b, a,  ,  ,  ,  ,  ,  ,  ,  ,
Row#1	= b, a, bcb, abcba, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#2	= bab, c, b, abcba, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#3	= b, a, b, c, b, abcba, cc, b, a,  ,  ,  ,  ,
Row#4	= b, a, bcbabcb, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#5	= b, abcba, bcb, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#6	= b, a, bcb, a, bcb, a, cc, b, a,  ,  ,  ,  ,
Row#7	= bab, c, b, a, bcb, a, cc, b, a,  ,  ,  ,  ,
Row#8	= b, a, b, c, b, a, bcb, a, cc, b, a,  ,  ,
Row#9	= bab, cbabc, b, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#10	= b, a, b, cbabc, b, a, cc, b, a,  ,  ,  ,  ,
Row#11	= babcbab, c, b, a, cc, b, a,  ,  ,  ,  ,  ,  ,
Row#12	= bab, c, bab, c, b, a, cc, b, a,  ,  ,  ,  ,
Row#13	= b, a, b, c, bab, c, b, a, cc, b, a,  ,  ,
Row#14	= b, abcba, b, c, b, a, cc, b, a,  ,  ,  ,  ,
Row#15	= b, a, bcb, a, b, c, b, a, cc, b, a,  ,  ,
Row#16	= bab, c, b, a, b, c, b, a, cc, b, a,  ,  ,
Row#17	= b, a, b, c, b, a, b, c, b, a, cc, b, a,
Row#18	= b, abcbabcba, c, c, b, a,  ,  ,  ,  ,  ,  ,  ,
Row#19	= b, a, bcb, abcba, c, c, b, a,  ,  ,  ,  ,  ,
Row#20	= bab, c, b, abcba, c, c, b, a,  ,  ,  ,  ,  ,
Row#21	= b, a, b, c, b, abcba, c, c, b, a,  ,  ,  ,
Row#22	= b, a, bcbabcb, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#23	= b, abcba, bcb, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#24	= b, a, bcb, a, bcb, a, c, c, b, a,  ,  ,  ,
Row#25	= bab, c, b, a, bcb, a, c, c, b, a,  ,  ,  ,
Row#26	= b, a, b, c, b, a, bcb, a, c, c, b, a,  ,
Row#27	= bab, cbabc, b, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#28	= b, a, b, cbabc, b, a, c, c, b, a,  ,  ,  ,
Row#29	= babcbab, c, b, a, c, c, b, a,  ,  ,  ,  ,  ,
Row#30	= bab, c, bab, c, b, a, c, c, b, a,  ,  ,  ,
Row#31	= b, a, b, c, bab, c, b, a, c, c, b, a,  ,
Row#32	= b, abcba, b, c, b, a, c, c, b, a,  ,  ,  ,
Row#33	= b, a, bcb, a, b, c, b, a, c, c, b, a,  ,
Row#34	= bab, c, b, a, b, c, b, a, c, c, b, a,  ,
Row#35	= b, a, b, c, b, a, b, c, b, a, c, c, b, a

[rY][cX]
Row#0	= 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1

0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 2, 3, 4
PalindromePartitioning CountMinCut_DP2D_1 for babcbabcbaccba is 4
[rY][cX]
Row#0	= 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1

0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 2, 3, 4
PalindromePartitioning CountMinCut_DP2D_2 for babcbabcbaccba is 4
*/
#endif