#ifndef MAX_PRODUCT_OF_WORD_LENGTH_H
#define MAX_PRODUCT_OF_WORD_LENGTH_H
#include "Debug.h"
/*
Leetcode: Maximum Product of Word Lengths
Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters.
You may assume that each word will contain "only lower case letters".
If no such two words exist, return 0.
Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".
Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".
Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.

Since each word contains only lower case letters, which means we can use 26 bits to represent the appearance of chars in each word by an 32-bit integer.
Two words do not share common letters: can be checked using bitwise AND to check if there is common set bits between 2 integers

BruteForce: O(n^2 * lenOfWord) time
UseBitMap: O(n^2) time
*/
class MaxProductOfWordLength
{
public:
	MaxProductOfWordLength() {}
	~MaxProductOfWordLength() {}

	int ConvertToBitMap(const std::vector<std::string> & words)
	{
		int N = words.size();
		std::vector<int> charMap(N, 0);//charMap[i]: use an integer's all set bits to represent all chars in words[i]

		for (int i = 0; i < N; ++i)
		{
			for (const char & c : words[i])
			{
				charMap[i] |= (1 << (c - 'a'));
			}
		}

		int maxLenProduct = 0;
		//enumerate all possible pairs
		for (int i = 0; i < N - 1; ++i)//O(n^2) time
		{
			for (int j = i + 1; j < N; ++j)
			{
				if ((charMap[i] & charMap[j]) == 0)
				{
					maxLenProduct = std::max(maxLenProduct, (int)(words[i].size() * words[j].size()));
				}
			}
		}

		std::cout << "BitMap = " << Debug::ToStr1D<int>()(charMap) << std::endl;
		std::cout << "MaxProductOfWordLength ConvertToBitMap for \"" << Debug::ToStr1D<std::string>()(words) << "\": " << maxLenProduct << std::endl;
		return maxLenProduct;
	}
};
#endif
