#ifndef REPEATED_SUBSTRING_PATTERN_H
#define REPEATED_SUBSTRING_PATTERN_H
#include "Debug.h"
/*
Leetcode: Repeated Substring Pattern
Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.
You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
Example 1:
Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"
Output: False
Example 3:
Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
*/
class RepeatedSubstringPattern
{
public:
	RepeatedSubstringPattern() {}

	bool UseKMP(std::string s)//O(n) time, O(n) space
	{
		int N = s.size();
		std::vector<int> LPS = getLPSVector(s);
		int lenLCPS = LPS[N - 1];//length of longest common prefix suffix of s
		bool res = lenLCPS > 0 && (N % (N - lenLCPS) == 0);

		std::cout << Debug::ToStr1D<int>()(LPS) << std::endl;
		std::cout << "RepeatedSubstringPattern UseKMP for \"" << s << "\": " << res << std::endl;
		return res;
	}
private:
	std::vector<int> getLPSVector(const std::string & needle)
	{
		int M = needle.size();
		std::vector<int> LPS(M);

		int commonPrefixEnd = 0;
		int suffixEnd = 1;

		LPS[0] = 0;//init (prefix and suffix cannot overlap)

		for (; suffixEnd < M;)
		{
			if (needle[suffixEnd] == needle[commonPrefixEnd])
			{
				++commonPrefixEnd;
				LPS[suffixEnd] = commonPrefixEnd;
				++suffixEnd;
			}
			else
			{
				if (commonPrefixEnd != 0)
				{
					commonPrefixEnd = LPS[commonPrefixEnd - 1];//jump to previous commonPrefixEnd
				}
				else//commonPrefixEnd == 0, no common characters
				{
					LPS[suffixEnd] = 0;
					++suffixEnd;
				}
			}
		}
		return LPS;
	}
};
/*
0, 0, 1, 2
RepeatedSubstringPattern UseKMP for "abab": 1
0, 0, 1
RepeatedSubstringPattern UseKMP for "aba": 0
0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
RepeatedSubstringPattern UseKMP for "abcabcabcabc": 1
*/
#endif
