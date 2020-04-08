#ifndef UNIQUE_SUBSTR_IN_WRAPROUND_STR_H
#define UNIQUE_SUBSTR_IN_WRAPROUND_STR_H
#include "Debug.h"
/*
Leetcode: Unique Substring In Wrapround String
Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
Now we have another string p.
Your job is to find out how many unique non-empty substrings of p are present in s.
In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.
Note: p consists of only lowercase English letters and the size of p might be over 10000.
Example 1:
Input: "a"
Output: 1
Explanation: Only the substring "a" of string "a" is in the string s.
Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.
Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.
*/
class UniqueSubstrInWraproundStr
{
public:
	UniqueSubstrInWraproundStr() {}

	//count number of distinct substring in p that is also a substring in "abcdefghijklmnopqrstuvwxyz" with wrapped round
	int DP(std::string p)
	{
		//a valid substr (a substr in incr order of alphabet) ending at x has count of its length
		//zabcd: d, cd, bcd, abcd, zabcd
		//zkbcd: d, cd, bcd
		//so the max count of each valid substr ending at x is equal to the length of longest valid substr ending at x
		int N = p.size();
		std::vector<int> count(26, 0);
		int curLen = 1;
		for (int i = 0; i < N; ++i)
		{
			if (i > 0 && (p[i - 1] + 1 == p[i] || p[i - 1] - 25 == p[i]))
				++curLen;
			else
				curLen = 1;
			count[p[i] - 'a'] = std::max(count[p[i] - 'a'], curLen);
		}
		int res = std::accumulate(count.begin(), count.end(), 0);

		std::cout << "UniqueSubstrInWraproundStr for \"" << p << "\": " << res << std::endl;
		return res;
	}
};
/*
UniqueSubstrInWraproundStr for "zkbcdzabcd": 16
*/
#endif
