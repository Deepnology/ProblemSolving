/*HashTable*/
#ifndef PERMUTED_PALINDROME_H
#define PERMUTED_PALINDROME_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "Debug.h"
/*
Leetcode: Palindrome Permutation
Elements of programming interview, HashTable: Test for palindromic permutations
Write a program to test whether the letters forming a string s can be permuted to form a palindrome.
For example, "edified" can be permuted to form "deified".
Explore solutions that trade time for space.

HashTable: O(n) time, O(c) space, where n is the length of the string, c is number of distinct characters
Sort: O(nlogn) time, O(1) space

Leetcode: Palindrome Permutation II
Given a string s, return all the palindromic permutations (without duplicates) of it.
Return an empty list if no palindromic permutation could be form.
For example:
Given s = "aabb", return ["abba", "baab"].
Given s = "abc", return [].
Hint:
If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

Leetcode: Longest Palindrome
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
This is case sensitive, for example "Aa" is not considered a palindrome here.
Note:
Assume the length of given string will not exceed 1,010.
Example:
Input:
"abccccdd"
Output:
7
Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/
class PermutedPalindrome
{
public:
	PermutedPalindrome(){}
	~PermutedPalindrome(){}

	bool HashTable(const std::string & s)
	{
		std::unordered_map<char, int> t;
		for (const char & c : s)
			++t[c];

		int oddCount = 0;
		for (const auto & p : t)
		{
			if (p.second & 1)//current char has odd count
			{
				++oddCount;
				if (oddCount > 1)
					break;
			}
		}
		std::cout << Debug::ToStr1D<char, int>()(t) << std::endl;

		bool res = oddCount <= 1 ? true : false;
		std::cout << "PermutedPalindrome HashTable for \"" << s << "\": " << res << std::endl;
		return res;
	}

	bool Sort(std::string & s)
	{
		std::string before = s;
		int N = s.size();
		std::sort(s.begin(), s.end());
		std::cout << s << std::endl;

		int oddCount = 0;
		int curCharCount = 1;
		for (int i = 1; i < N; ++i)
		{
			if (s[i] == s[i - 1])
			{
				++curCharCount;
			}
			else
			{
				if (curCharCount & 1)//odd
				{
					++oddCount;
					if (oddCount > 1)
						break;
				}
				curCharCount = 1;
			}
		}
		if (curCharCount & 1)
			++oddCount;

		bool res = oddCount <= 1 ? true : false;
		std::cout << "PermutedPalindrome Sort for \"" << before << "\": " << res << std::endl;
		return res;
	}

	std::vector<std::string> GenerateAllPalindromePermutations(const std::string & s)
	{
		std::unordered_map<char, int> t;
		for (const char & c : s)
			++t[c];

		std::string half;//first half chars excluding mid if s is odd
		std::string mid;//mid char if s is odd
		int oddCount = 0;
		for (const auto & p : t)
		{
			if (p.second & 1)//odd count
			{
				++oddCount;
				if (oddCount > 1)
					return std::vector<std::string>();

				mid.append(1, p.first);
				if (p.second > 1)//must be 3, 5, 7, 9, ...
					half.append((p.second - 1) / 2, p.first);
			}
			else//even count
			{
				half.append(p.second / 2, p.first);
			}
		}

		std::sort(half.begin(), half.end());
		std::vector<std::string> res;
		this->recur(half, 0, res);
		//now res contains all permutations of half: append mid + reverseOfHalf
		for (std::string & s : res)
		{
			std::string rev(s);
			std::reverse(rev.begin(), rev.end());
			if (!mid.empty())
				s += mid[0];
			s += rev;
		}

		std::cout << "PermutedPalindrome GenerateAllPalindromePermutations for \"" << s << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
private:
	void recur(std::string & half, int begin, std::vector<std::string> & res)//generate all unique permutations of half. see Permutations2.h
	{
		int N = half.size();
		if (begin == N)
		{
			res.emplace_back(half);
			return;
		}

		std::unordered_set<char> visit;
		for (int i = begin; i < N; ++i)
		{
			if (visit.count(half[i]))
				continue;
			visit.insert(half[i]);

			std::swap(half[i], half[begin]);
			this->recur(half, begin + 1, res);
			std::swap(half[i], half[begin]);
		}
	}
};
class LongestPermutedPalindrome
{
public:
	int HashTable(const std::string & s)
	{
		std::unordered_map<char, int> charMap;
		for (const auto & c : s)
			++charMap[c];
		bool odd = false;
		int oddCount = 0;
		int evenCount = 0;
		for (auto itr = charMap.begin(); itr != charMap.end(); ++itr)
		{
			if (itr->second & 1)//odd
			{
				odd = true;
				oddCount += (itr->second - 1);//-1: to exclude a mid char
			}
			else
				evenCount += itr->second;
		}

		if (!odd)
			return s.size();

		return evenCount + oddCount + 1;//+1: to include a mid char
	}
};
/*
PermutedPalindrome HashTable for "edified": 1
ddeefii
PermutedPalindrome Sort for "edified": 1
PermutedPalindrome GenerateAllPalindromePermutations for "aaa": aaa
PermutedPalindrome GenerateAllPalindromePermutations for "aabb": abba, baab
PermutedPalindrome GenerateAllPalindromePermutations for "aaabb": aababaa, abaaaba, baaaaab
PermutedPalindrome GenerateAllPalindromePermutations for "abccba": abccba, acbbca, baccab, bcaacb, cbaabc, cabbac
PermutedPalindrome GenerateAllPalindromePermutations for "abcdcba": abcdcba, acbdbca, bacdcab, bcadacb, cbadabc, cabdbac
*/
#endif