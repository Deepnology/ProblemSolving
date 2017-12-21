#ifndef LONGEST_WORD_MADE_OF_OTHERS_H
#define LONGEST_WORD_MADE_OF_OTHERS_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Concatenated words
Cracking the coding interview: Hard
Given an array of words.
Find the longest word that can be decomposed into other words.
*/
class LongestWordMadeOfOthers
{
public:
	LongestWordMadeOfOthers(){}
	~LongestWordMadeOfOthers(){}

	std::string Solve_DP(std::vector<std::string> strs)
	{
		std::unordered_set<std::string> strMap;
		std::unordered_set<std::string> skipMap;
		int N = strs.size();
		for (int i = 0; i < N; ++i)
		{
			strMap.insert(strs[i]);
		}
		std::vector<std::string> res;
		std::sort(strs.begin(), strs.end(), [&](const std::string & a, const std::string & b)->bool
		{
			return a.size() > b.size();
		});
		for (int i = 0; i < N; ++i)
		{
			//since strs is sorted in descending order, the first string that is decomposable will be the longest one
			if (this->decomposableRecur(strs[i], strMap, skipMap))
			{
				res.push_back(strs[i]);
			}
		}

		std::cout << "LongestWordMadeOfOthers for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res.empty() ? std::string () : res[0];
	}
private:
	/*test if word can be decomposable into other words in the map*/
	bool decomposableRecur(const std::string & word, std::unordered_set<std::string> & strMap, std::unordered_set<std::string> & skipMap)
	{
		if (skipMap.count(word))
			return false;

		int N = word.size();
		for (int i = 1; i < N; ++i)
		{
			std::string left = word.substr(0, i);
			std::string right = word.substr(i);

			if (strMap.count(left))//if left is an original word
			{
				if (strMap.count(right))//if right is an original word
					return true;
				else if (this->decomposableRecur(right, strMap, skipMap))
					return true;
			}
		}
		//now word cannot be decomposed into any other words in the map
		skipMap.insert(word);
		return false;
	}
};
/*
LongestWordMadeOfOthers for "catxdogcatsrat, hippopotamuses, ratcatdogcat, catsdogcats, dogcatsdog, cats, cat, dog, rat": ratcatdogcat, catsdogcats, dogcatsdog
*/
#endif