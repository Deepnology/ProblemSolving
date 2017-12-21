#ifndef	LONGEST_SUBSTR_W_LEAST_K_REPEAT_CHARS_H
#define LONGEST_SUBSTR_W_LEAST_K_REPEAT_CHARS_H
#include "Debug.h"
/*
Leetcode: Longest substring with at least k repeating characters
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:
Input:
s = "aaabb", k = 3
Output: 3
The longest substring is "aaa", as 'a' is repeated 3 times.

Example 2:
Input:
s = "ababbc", k = 2
Output: 5
The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/
class LongestSubStrWLeastKRepeatChars
{
public:
	LongestSubStrWLeastKRepeatChars() {}

	int Recur(std::string s, int k)
	{
		if (s.empty()) return 0;
		int res = recur(s, k, 0, s.size() - 1);
		std::cout << "LongestSubStrWLeastKRepeatChars Recur for \"" << s << "\", K=\"" << k << "\": " << res << std::endl;
		return res;
	}

	int recur(const std::string & s, int k, int left, int right)
	{
		std::vector<int> count(26, 0);
		for (int i = left; i <= right; ++i)
			++count[s[i] - 'a'];
		bool allValidChars = true;
		for (int i = left; i <= right; ++i)
		{
			if (count[s[i] - 'a'] < k)
			{
				allValidChars = false;
				break;
			}
		}
		if (allValidChars) return right - left + 1;

		int maxLen = 0;
		int i = left;
		while (i <= right)
		{
			int begin = i;
			while (i <= right && count[s[i] - 'a'] >= k)
				++i;
			if (i == begin)
			{
				++i; continue;
			}
			//now all chars in s[begin:i-1] are >= k
			maxLen = std::max(maxLen, recur(s, k, begin, i - 1));
		}
		return maxLen;
	}
};
/*
LongestSubStrWLeastKRepeatChars Recur for "aaabb", K="3": 3
LongestSubStrWLeastKRepeatChars Recur for "ababbc", K="2": 5
*/
#endif
