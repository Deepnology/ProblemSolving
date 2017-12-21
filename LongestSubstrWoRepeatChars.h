/*HashTable*/
#ifndef _LONGEST_SUBSTR_WO_REPEAT_CHARS_H
#define _LONGEST_SUBSTR_WO_REPEAT_CHARS_H
#include <string>
#include <vector>
#include <iostream>
#include <queue>
/*
//http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
Leetcode: Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating
// characters. For example,
//
// the longest substring without repeating letters for "abcabcbb" is "abc",
// which the length is 3. For "bbbbb" the longest substring is "b", with the
// length of 1.
//
// Complexity:
// Sliding Window, O(n) time

see also LongestSubArrWDistinctEntries.h
*/
class LongestSubstrWoRepeatChars
{
public:
	LongestSubstrWoRepeatChars(){}
	~LongestSubstrWoRepeatChars(){}

	int FindFirstOne_SlideWindow(const std::string & s)//see also LongestSubArrWDistinctEntries.h HashTable which is better
	{
		bool visit[256] = { false };
		int N = s.size();
		int maxLen = 0;
		int maxBegin = 0;
		int begin = 0;
		std::vector<std::string> res;
		for (int end = 0; end < N; ++end)
		{
			if (visit[s[end]])
			{
				//shrink window to exclude visited words until the first s[end]
				while (s[begin] != s[end])
				{
					visit[s[begin]] = false;
					++begin;
				}
				//now begin points to the first s[end], advance it to the next char
				visit[s[begin]] = false;
				++begin;
			}
			visit[s[end]] = true;//mark s[end] ANYWAY

			//record
			if (end - begin + 1 > maxLen)
			{
				maxLen = end - begin + 1;
				maxBegin = begin;
			}

			if (end - begin + 1 > 0)
				res.push_back(s.substr(begin, end - begin + 1));
		}

		std::cout << "LongestSubstrWoRepeatChars FindFirstOne_SlideWindow for \"" << s << "\": " << maxLen << "(" << s.substr(maxBegin, maxLen) << ")" << std::endl;
		std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		return maxLen;
	}
};
/*
LongestSubstrWoRepeatChars FindFirstOne_SlideWindow for "abcdefgdijkxyz": 10(efgdijkxyz)
a, ab, abc, abcd, abcde, abcdef, abcdefg, efgd, efgdi, efgdij, efgdijk, efgdijkx, efgdijkxy, efgdijkxyz
*/
#endif