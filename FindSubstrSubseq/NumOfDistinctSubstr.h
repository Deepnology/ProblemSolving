/*SuffixArray*/
#ifndef NUM_OF_DISTINCT_SUBSTR_H
#define NUM_OF_DISTINCT_SUBSTR_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Debug.h"
#include "../TrieSuffixArray/SuffixArray.h"
/*
http://www.stanford.edu/class/cs97si/suffix-array.pdf
http://www.quora.com/Programming-Interviews/Given-a-string-how-do-I-find-the-number-of-distinct-substrings-of-the-string
Given a string, find the number of all distinct substrings in a string.
Equivalent to compute the number of nodes (without root) of a string's corresponding suffix trie.

1. suffix array
Build the suffix array.
For each suffix, compute the "LCP of prev suffix and current suffix"
, then the "current suffix's extra node count" will be "current suffix size - LCP".
The overall node count will be accumulation of all "current suffix's extra node count" plus "first suffix size".

2. hash table
*/
class NumOfDistinctSubstr
{
public:
	NumOfDistinctSubstr(){}
	~NumOfDistinctSubstr(){}

	int SuffixArray(const std::string & s)
	{
		SuffixArraySimple suffixes(s);//construct suffix array: O(nlogn)
		//count by LCP: O(nlogn)
		int res = 0;
		for (int i = 0; i < suffixes.Size(); ++i)
		{
			if (i - 1 >= 0)
			{
				res += s.substr(suffixes[i]).size() - 
					suffixes.LongestCommonPrefix(suffixes[i - 1], suffixes[i]);//LCP: O(logn)
			}
			else//for i == 0
			{
				res += s.substr(suffixes[i]).size();
			}
		}

		std::cout << "NumOfDistinctSubstr SuffixArray for \"" << s << "\": " << res << std::endl;
		return res;
	}

	int BruteForce_HashSet(const std::string & s)
	{
		std::unordered_set<std::string> strs;
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			for (int j = i; j < N; ++j)
			{
				std::string ss = s.substr(i, j - i + 1);
				strs.insert(ss);
			}
		}

		std::cout << "NumOfDistinctSubstr HashSet for \"" << s << "\": " << strs.size() << " (" << Debug::ToStr1D<std::string>()(strs) << ")" << std::endl;
		return strs.size();
	}
};

/*
SuffixArraySimple for "banana":
0:	a-------------->1
1:	ana------------>3-1=2
2:	anana---------->5-3=2
3:	banana--------->6-0=6
4:	na------------->2-0=2
5:	nana----------->4-2=2
NumOfDistinctSubstr SuffixArray for "banana": 15
NumOfDistinctSubstr HashSet for "banana": 15 (ana, b, bana, a, ba, an, ban, banan, banana, n, anan, na, anana, nan, nana)
SuffixArraySimple for "aabab":
0:	aabab---------->5
1:	ab------------->2-1=1
2:	abab----------->4-2=2
3:	b-------------->1-0=1
4:	bab------------>3-1=2
NumOfDistinctSubstr SuffixArray for "aabab": 11
NumOfDistinctSubstr HashSet for "aabab": 11 (a, aab, aa, ab, bab, aaba, aabab, abab, aba, b, ba)
SuffixArraySimple for "abac":
0:	abac----------->4
1:	ac------------->2-1=1
2:	bac------------>3-0=3
3:	c-------------->1-0=1
NumOfDistinctSubstr SuffixArray for "abac": 9
NumOfDistinctSubstr HashSet for "abac": 9 (ba, a, c, ab, aba, abac, ac, bac, b)
*/
#endif