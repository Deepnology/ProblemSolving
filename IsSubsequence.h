#ifndef IS_SUBSEQUENCE_H
#define IS_SUBSEQUENCE_H
#include "Debug.h"
/*
Leetcode: Is Subsequence
Given a string s and a string t, check if s is subsequence of t.
You may assume that there is only lower case English letters in both s and t.
t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"
Return true.

Example 2:
s = "axc", t = "ahbgdc"
Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence.
In this scenario, how would you change your code?
*/
class IsSubsequence
{
public:
	IsSubsequence() {}

	void Validate(std::string s, std::string t)
	{
		bool res1 = BruteForce(s, t);
		bool res2 = FreqLookup(s, t);
		std::cout << "IsSubsequence for \"" << s << "\", \"" << t << "\" BruteForce and FreqLookup: " << res1 << ", " << res2 << std::endl;
	}

	bool BruteForce(std::string s, std::string t)//smaller, bigger
	{
		int N = t.size();
		int M = s.size();
		if (N == 0 && M == 0) return true;
		if (N == 0) return false;
		if (M == 0) return true;

		int j = 0;//s
		for (int i = 0; i < N; ++i)//t
		{
			if (t[i] == s[j])
				++j;
			if (j == M)
				return true;
		}
		return false;
	}

	//follow-up
	bool FreqLookup(std::string s, std::string t)
	{
		int N = t.size();
		int M = s.size();
		if (N == 0 && M == 0) return true;
		if (N == 0) return false;
		if (M == 0) return true;

		//for more freq lookup: using binary search
		std::vector<std::vector<int>> idxList(26, std::vector<int>());
		for (int i = 0; i < N; ++i)
			idxList[t[i] - 'a'].push_back(i);
		int prevIdx = -1;
		for (int i = 0; i < M; ++i)
		{
			auto ub = std::upper_bound(idxList[s[i] - 'a'].begin(), idxList[s[i] - 'a'].end(), prevIdx);
			if (ub == idxList[s[i] - 'a'].end())
				return false;
			prevIdx = *ub;
		}
		return true;
	}
};
/*
IsSubsequence for "abc", "ahbgdc" BruteForce and FreqLookup: 1, 1
IsSubsequence for "axc", "ahbgdc" BruteForce and FreqLookup: 0, 0
*/
#endif
