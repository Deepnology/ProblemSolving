#ifndef FIND_ALL_DISTINCT_PALINDROME_SUBSTR_H
#define FIND_ALL_DISTINCT_PALINDROME_SUBSTR_H
#include "Debug.h"
/*
http://www.geeksforgeeks.org/find-number-distinct-palindromic-sub-strings-given-string/
Given a lower case string, find all distinct palindrome substrings.
input: abaaa
output: a, aa, aaa, aba, b
input: geek
output: e, ee, g, k

check geeksforgeeks website for a modified Manacher approach O(n^2) time
*/
class FindAllDistinctPalindromeSubstr
{
public:
	FindAllDistinctPalindromeSubstr() {}

	std::vector<std::string> Greedy(std::string & s)
	{
		int N = s.size();
		std::unordered_set<std::string> res;
		for (int i = 0; i < N; ++i)
		{
			expand(s, i, i, res);
			expand(s, i, i + 1, res);
		}

		std::vector<std::string> v;
		for (auto & str : res)
			v.push_back(str);
		std::cout << "FindAllDistinctPalindromeSubstr Greedy for \"" << s << "\": " << Debug::ToStr1D<std::string>()(v) << std::endl;
		return v;
	}
private:
	void expand(std::string & s, int left, int right, std::unordered_set<std::string> & res)
	{
		int N = s.size();
		while (left >= 0 && right < N && s[left] == s[right])
		{
			res.insert(s.substr(left, right - left + 1));
			--left;
			++right;
		}
	}
};
/*
FindAllDistinctPalindromeSubstr Greedy for "abaaa": a, b, aba, aa, aaa
FindAllDistinctPalindromeSubstr Greedy for "abaaba": a, abaaba, b, aba, baab, aa
FindAllDistinctPalindromeSubstr Greedy for "abbaeaea": a, bb, b, abba, aeaea, e, aea, eae
*/
#endif
