#ifndef LONGEST_UNCOMMON_SUBSEQ_H
#define LONGEST_UNCOMMON_SUBSEQ_H
#include "Debug.h"
/*
Leetcode: Longest Uncommon Subsequence I
Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings.
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.
A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements.
Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.
The input will be two strings, and the output needs to be the length of the longest uncommon subsequence.
If the longest uncommon subsequence doesn't exist, return -1.
Example 1:
Input: "aba", "cdc"
Output: 3
Explanation: The longest uncommon subsequence is "aba" (or "cdc"),
because "aba" is a subsequence of "aba",
but not a subsequence of any other strings in the group of two strings.

Leetcode: Longest Uncommon Subsequence II
Given a list of strings, you need to find the longest uncommon subsequence among them.
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.
A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements.
Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.
The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence.
If the longest uncommon subsequence doesn't exist, return -1.
Example 1:
Input: "aba", "cdc", "eae"
Output: 3
*/
class LongestUncommonSubseq
{
public:
	LongestUncommonSubseq() {}

	int LUSOf2(std::string a, std::string b)
	{
		int res = FindLUSlength(a, b);
		std::cout << "LongestUncommonSubseq LUSof2 for \"" << a << "\", \"" << b << "\": " << res << std::endl;
		return res;
	}
private:
	int FindLUSlength(std::string a, std::string b)
	{
		if (a.size() < b.size())
			std::swap(a, b);
		//now a.size() >= b.size()
		if (a.size() > b.size())
			return a.size();
		//now a.size() == b.size()
		if (a != b) return a.size();
		return -1;//a==b
	}

public:
	int LUSOfArray(std::vector<std::string> &strs)
	{
		int res = FindLUSlength(strs);
		std::cout << "LongestUncommonSubseq LUSofArray for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << res << std::endl;
		return res;
	}
private:
	int FindLUSlength(std::vector<std::string> & strs)
	{
		std::sort(strs.begin(), strs.end(), [](const std::string & a, const std::string & b)->bool
		{
			return a.size() > b.size();
		});
		int N = strs.size();
		for (int i = 0; i < N; ++i)
		{
			//test if strs[i] is a valid longest str: it cannot be a subseq of any other str whose size >= strs[i].size()
			bool valid = true;
			int j;
			for (j = 0; j < N; ++j)
			{
				if (strs[i].size() > strs[j].size()) break;
				if (j == i) continue;
				if (isSubseq(strs[j], strs[i]))//strs[j].size() >= strs[i].size()
				{
					valid = false;
					break;
				}
			}
			if (valid)
			{
				return strs[i].size();
			}
		}
		return -1;
	}
private:
	bool isSubseq(const std::string & a, const std::string & b)//a.size() >= b.size()
	{
		//check if b is a subseq of a
		int N = a.size();
		int M = b.size();
		if (N < M) return false;
		int i = 0;
		int j = 0;
		for (; i < N; ++i)
		{
			if (a[i] == b[j])
				++j;
			if (j == M)
				return true;
		}
		return false;
	}
};
/*
LongestUncommonSubseq LUSof2 for "aba", "cdc": 3
LongestUncommonSubseq LUSofArray for "aaa, aaa, aa": -1
LongestUncommonSubseq LUSofArray for "aabbcc, aabbcc, ab": -1
LongestUncommonSubseq LUSofArray for "aabbccc, aabbcc, aabbcc, bcc, ab": 7
*/
#endif
