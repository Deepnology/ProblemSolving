#ifndef SUBSTR_W_CONCAT_ALL_WORDS_H
#define SUBSTR_W_CONCAT_ALL_WORDS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
/*
Elements of programming interview, HashTable: compute all string decompositions (FindAll_BruteForce)
Leetcode: Substring With Concatenation Of All Words
// Substring with Concatenation of All Words
// You are given a string, S, and a list of words, L, that are all of the
// same length. Find all starting indices of substring(s) in S that is a
// concatenation of each word in L exactly once and without any intervening
// characters.
//
// For example, given:
// S: "barfoothefoobarman"
// L: ["foo", "bar"]
//
// You should return the indices: [0,9].
// (order does not matter).
//
// Complexity:
// Brute Force O(N*count) time, O(count*len) space
// Sliding Window O(N*len) time, O(count*len) space
// where N is the size of S, count is the size of L, len is the size of L[0]
*/
class SubstrWConcatAllWords
{
public:
	SubstrWConcatAllWords(){}
	~SubstrWConcatAllWords(){}

	//this one can pass online judge, but slower
	std::vector<int> FindAll_BruteForce_HashMap(const std::string & S, const std::vector<std::string> & L)
	{
		std::vector<int> res;
		if (S.empty() || L.empty() || L[0].empty())
			return res;
		int N = S.size();
		int count = L.size();
		int len = L[0].size();

		//build wordMap
		std::unordered_map<std::string, int> wordMap;//key: word, val: count
		for (const auto & word : L)
			++wordMap[word];

		for (int i = 0; (i + count * len - 1) < N; ++i)//count*len must include i, so subtract 1
		{
			std::unordered_map<std::string, int> foundMap;//key: word, val: count
			int j = 0;
			for (; j < count; ++j)
			{
				std::string substr = S.substr(i + j * len, len);
				if (wordMap.find(substr) == wordMap.end())
					break;
				else
				{
					++foundMap[substr];//insert {substr,1} when not present OR increment when foundMap[substr]>=1
					if (foundMap[substr] > wordMap[substr])
						break;
				}
			}
			if (j == count)
				res.push_back(i);
		}
		std::cout << "SubstrWConcatAllWords FindAll_BruteForce_HashMap for \"" << Debug::ToStr1D<std::string>()(L) << "\" from \"" << S << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


	std::vector<int> FindAll_SlideWindow(const std::string & S, const std::vector<std::string> & L)
	{
		std::vector<int> res;
		if (S.empty() || L.empty() || L[0].empty())
			return res;
		int N = S.size();
		int count = L.size();
		int len = L[0].size();

		//build wordMap
		std::unordered_map<std::string, int> wordMap;
		for (const auto & word : L)
			++wordMap[word];

		for (int i = 0; i < len; ++i)
		{
			std::unordered_map<std::string, int> foundMap;
			int foundCount = 0;
			
			for (int curBegin = i, curEnd = i; curEnd < N; curEnd += len)
			{
				std::string curWord = S.substr(curEnd, len);
				if (wordMap.find(curWord) == wordMap.end())//not found
				{
					foundMap.clear();//reset
					foundCount = 0;//reset
					curBegin = curEnd + len;//advance curBegin
				}
				else if (foundMap[curWord] < wordMap[curWord])//found but insufficient
				{
					++foundMap[curWord];
					++foundCount;
				}
				else//found but already full
				{
					//shrink window to exclude found words until the first curWord
					while (S.substr(curBegin, len) != curWord)
					{
						--foundMap[S.substr(curBegin, len)];
						--foundCount;
						curBegin += len;
					}
					//now curBegin points to the first curWord, advance it to the next word
					curBegin += len;
				}

				if (foundCount == count)
					res.push_back(curBegin);
			}
		}
		std::cout << "SubstrWConcatAllWords FindAll_SlideWindow for \"" << Debug::ToStr1D<std::string>()(L) << "\" from \"" << S << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

};
/*
SubstrWConcatAllWords FindAll_BruteForce_HashMap for "foo, bar" from "xyzbarfoobarbarfoothe123foobarfoo456man": 3, 6, 12, 24, 27
SubstrWConcatAllWords FindAll_SlideWindow for "foo, bar" from "xyzbarfoobarbarfoothe123foobarfoo456man": 3, 6, 12, 24, 27
*/
/*
Leetcode: Permutation in string
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1.
In other words, one of the first string's permutations is the substring of the second string.
Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
Note:
The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
*/
class PermutationInString
{
public:
	PermutationInString() {}

	bool checkInclusion(std::string s1, std::string s2)
	{
		std::vector<int> count(26, 0);
		for (auto & c : s1)
			++count[c - 'a'];
		int i = 0;
		int N = s2.size();
		int M = s1.size();
		int foundCount = 0;
		std::vector<int> found(26, 0);
		while (i < N)
		{
			if (count[s2[i] - 'a'])
			{
				++found[s2[i] - 'a'];
				if (found[s2[i] - 'a'] <= count[s2[i] - 'a'])
					++foundCount;
				
				if (foundCount == M)
					return true;
			}
			if (i - M + 1 >= 0)
			{
				if (count[s2[i - M + 1] - 'a'])
				{
					--found[s2[i - M + 1] - 'a'];
					if (found[s2[i - M + 1] - 'a'] < count[s2[i - M + 1] - 'a'])
						--foundCount;
				}
			}
			++i;
		}
		return false;
	}
};
#endif