#ifndef MAX_XOR_OF_2_NUMS_IN_ARRAY_H
#define MAX_XOR_OF_2_NUMS_IN_ARRAY_H
#include "Debug.h"
/*
Leetcode: Max XOR of 2 numbers in an array
Given a non-empty array of numbers, a0, a1, a2, ..., an-1, where 0 <= ai < 2^31.
Find the maximum result of ai XOR aj, where 0 <= i, j < n.
Could you do this in O(n) runtime?
Example:
Input: [3, 10, 5, 25, 2, 8]
Output: 28
Explanation: The maximum result is 5 ^ 25 = 28.
*/
class MaxXORof2NumsInArray
{
public:
	MaxXORof2NumsInArray() {}
	struct TrieNode//binary trie
	{
		std::vector<TrieNode *> children;
		TrieNode() : children(2, NULL)
		{

		}
	};
public:
	int FindMaxXOR_BinaryTrie(const std::vector<int> & v)
	{
		int N = v.size();

		//1. build a binary trie w/ depth = 32
		TrieNode * root = new TrieNode();
		TrieNode * cur = root;
		for (const auto n : v)
		{
			cur = root;
			for (int i = 31; i >= 0; --i)
			{
				int curBit = (n >> i) & 1;
				if (cur->children[curBit] == NULL)
					cur->children[curBit] = new TrieNode();
				cur = cur->children[curBit];
			}
		}

		//2. for each num in v, find its max XOR value, O(n*32) time
		int res = 0;
		for (const auto n : v)
		{
			int XOR = 0;
			cur = root;
			for (int i = 31; i >= 0; --i)
			{
				int curBit = (n >> i) & 1;
				if (cur->children[curBit ^ 1])//found opposite bit: XOR result must be 1
				{
					XOR |= (1 << i);
					cur = cur->children[curBit ^ 1];
				}
				else//no opposite bit, go down w/ same (self) bit
					cur = cur->children[curBit];
			}
			res = std::max(res, XOR);
		}

		std::cout << "MaxXORof2NumsInArray FindMaxXOR_BinaryTrie for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
};
/*
MaxXORof2NumsInArray FindMaxXOR_BinaryTrie for "3, 10, 5, 25, 2, 8": 28
*/
#endif

