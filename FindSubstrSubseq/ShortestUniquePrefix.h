/*SuffixArray*/
#ifndef SHORTEST_UNIQUE_PREFIX_H
#define SHORTEST_UNIQUE_PREFIX_H
#include "TrieST.h"
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the shortest unique prefix
Let D be a set of strings.
Write a function that takes as input a string s and returns the shortest prefix of s which is not a prefix of any string in D.

Google
http://www.careercup.com/question?id=16074662
Given a list of words and a target word.
Find the shortest prefix of the target word that is not of a prefix of any word in the list.
Solution:
Compute a set of longest common prefix of each word in the list and the target word.
Then find the longest string in the lcp set.
Then the longest string along with the next char in the target word will be the answer.
If the longest string is equal to the target word, then there will be no answer.
OR
Build a trie of all words in the list.
Find the longest prefix of all keys in the trie that is also a prefix of the target word.
Then the longest prefix along with the next char in the target word will be the answer.
If the longest prefix is equal to the target word, then there will be no answer.
*/
class ShortestUniquePrefix
{
public:
	ShortestUniquePrefix(){}
	~ShortestUniquePrefix(){}

	std::string UseTrie(const std::vector<std::string> & v, const std::string & tgt)
	{
		int N = v.size();
		TrieST<int> t;
		for (int i = 0; i < N; ++i)
			t.Put(v[i], i);
		
		std::string lcp = t.LongestPrefixOf(tgt);
		std::string res = lcp.size() == tgt.size() ? "N/A" : lcp + tgt.substr(lcp.size(), 1);

		std::vector<std::string> keys = t.Keys();
		std::cout << "keys in trie: " << Debug::ToStr1D<std::string>()(keys) << std::endl;

		std::cout << "ShortestUniquePrefix UseTrie for \"" << tgt << "\" in \"" << Debug::ToStr1D<std::string>()(v) << "\": " << res << " (lcp: " << lcp << ")" << std::endl;
		return res;
	}
};
/*
keys in trie: be, cut, dog
ShortestUniquePrefix UseTrie for "cat" in "dog, be, cut": ca (lcp: c)
keys in trie: be, car, cut, dog
ShortestUniquePrefix UseTrie for "cat" in "dog, be, cut, car": cat (lcp: ca)
keys in trie: be, car, cat, cut, dog
ShortestUniquePrefix UseTrie for "cat" in "dog, be, cut, car, cat": N/A (lcp: cat)
*/
#endif