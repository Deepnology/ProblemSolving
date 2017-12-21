#ifndef PALINDROME_PAIRS_H
#define PALINDROME_PAIRS_H
#include "Debug.h"
/*
Leetcode: Palindrome Pairs
Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, 
so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.
Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]

BruteForce: O(n^2 * k) time, where k is the longest length of word in words
UseHashMap: O(n * k^2) time, where k is the longest length of word in words
*/
class PalindromePairs
{
public:
	PalindromePairs() {}
	~PalindromePairs() {}

	std::vector<std::vector<int>> UseHashMap(const std::vector<std::string> & words)
	{
		int N = words.size();
		std::unordered_map<std::string, int> lookup;
		for (int i = 0; i < N; ++i)
		{
			lookup[words[i]] = i;
		}

		std::vector<std::vector<int>> res;
		for (int i = 0; i < N; ++i)
		{
			int M = words[i].length();
			for (int len = 0; len <= M; ++len)
			{
				//"prefix + palindrome" + reversedPrefix
				if (this->is_palindrome(words[i], len, M - 1))
				{
					std::string prefix = words[i].substr(0, len);
					std::reverse(prefix.begin(), prefix.end());
					if (lookup.find(prefix) != lookup.end() && i != lookup[prefix])
					{
						res.push_back({ i, lookup[prefix] });
					}
				}

				//reversedSuffix + "palindrome + suffix"
				//len > 0: to skip the condition of reversing the entire string that has already done using prefix
				if (len > 0 && this->is_palindrome(words[i], 0, len - 1))
				{
					std::string suffix = words[i].substr(len);
					std::reverse(suffix.begin(), suffix.end());
					if (lookup.find(suffix) != lookup.end() && lookup[suffix] != i)
					{
						res.push_back({ lookup[suffix], i });
					}
				}
			}
		}

		std::cout << "PalindromePairs UseHashMap for \"" << Debug::ToStr1D<std::string>()(words) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	bool is_palindrome(const std::string & s, int start, int end)
	{
		while (start < end)
		{
			if (s[start++] != s[end--])
			{
				return false;
			}
		}
		return true;
	}
};
/*
PalindromePairs UseHashMap for "bat, tab, cat": [0,1], [1,0]
PalindromePairs UseHashMap for "abcd, dcba, lls, s, sssll": [0,1], [1,0], [3,2], [2,4]
*/
#endif
