#ifndef MIN_DIST_BTW_2_WORDS_IN_FILE_H
#define MIN_DIST_BTW_2_WORDS_IN_FILE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Debug.h"
#include "MinPairDiff2SortedArrays.h"
/*
Cracking the coding interview: Hard
http://k2code.blogspot.tw/2014/04/shortest-distances-between-two-words-in.html

Leetcode: Shortest Word Distance I
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
For example, Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = "coding", word2 = "practice", return 3.
Given word1 = "makes", word2 = "coding", return 1.
Note
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

Leetcode: Shortest Word Distance II
This is a follow up of Shortest Word Distance.
The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters.
How would you optimize it?
Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = "coding��, word2 = "practice��, return 3. Given word1 = "makes", word2 = "coding", return 1.
Note
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

Leetcode: Shortest Word Distance III
word1 and word2 can be equal

Compute min dist of every char in a string to a target char.
ex: s="bloomberg", c='b', return [0,1,2,2,1,0,1,2,3]
*/
class MinDistBtw2WordsInFile
{
public:
	MinDistBtw2WordsInFile(){}
	~MinDistBtw2WordsInFile(){}

	//I. one scan, O(n) time
	int OneScan(const std::vector<std::string> & strs, const std::string & w1, const std::string & w2)
	{
		int N = strs.size();
		int minDist = INT_MAX;
		int lastIdx1 = -1;
		int lastIdx2 = -1;
		for (int i = 0; i < N; ++i)
		{
			if (strs[i].compare(w1) == 0)
			{
				lastIdx1 = i;
			}
			else if (strs[i].compare(w2) == 0)
			{
				lastIdx2 = i;
			}

			if (lastIdx1 != -1 && lastIdx2 != -1)
			{
				minDist = std::min(minDist, std::abs(lastIdx1 - lastIdx2));
			}
		}
		std::cout << "MinDistBtw2WordsInFile OneScan for [" << w1 << "," << w2 << "] in \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << minDist << std::endl;
		return minDist;
	}

	//II.i.: Build Word Map, O(n) time, O(n) space
	std::unordered_map<std::string, std::vector<int> > BuildWordMap(const std::vector<std::string> & strs)
	{
		std::unordered_map<std::string, std::vector<int> > wordMap;//first: entry, second: a vector of indicies
		int N = strs.size();
		for (int i = 0; i < N; ++i)
		{
			if (wordMap.count(strs[i]) == 0)
				wordMap.insert(std::make_pair(strs[i], std::vector<int>(1, i)));
			else
				wordMap[strs[i]].push_back(i);//second: vector of indices must be sorted in increasing order
		}
		std::cout << "MinDistBtw2WordsInFile BuildWordMap for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << std::endl;
		Debug::Print2D<std::string, int>()(wordMap);
		return wordMap;
	}
	//II.ii.: Query From Word Map, O(1) time lookup wordMap, O(n) time find min pair diff from 2 sorted arrays
	int QueryFromWordMap(std::unordered_map<std::string, std::vector<int> > & wordMap, const std::string & w1, const std::string & w2)
	{
		int minDist = INT_MAX;
		if (wordMap.count(w1) != 0 && wordMap.count(w2) != 0)
		{
			minDist = MinPairDiff2SortedArrays().ModifiedMerge2SortedArrays(wordMap[w1], wordMap[w2]);
		}
		std::cout << "MinDistBtw2WordsInFile QueryFromWordMap for [" << w1 << "," << w2 << "]: " << minDist << std::endl;
		return minDist;
	}

	//III: 
	int OneScan2(const std::vector<std::string> & strs, const std::string & w1, const std::string & w2)
	{
		int N = strs.size();
		int lastIdx1 = -1;
		int lastIdx2 = -1;
		int minDist = INT_MAX;
		bool isEqual = w1.compare(w2) == 0 ? true : false;
		for (int i = 0; i < N; ++i)
		{
			if (isEqual)
			{
				if (strs[i].compare(w1) == 0)
				{
					//update the smaller one of lastIdx1 and lastIdx2
					if (lastIdx2 < lastIdx1)
						lastIdx2 = i;
					else
						lastIdx1 = i;

					//std::cout << lastIdx1 << "," << lastIdx2 << std::endl;
				}
			}
			else//same as I.
			{
				if (strs[i].compare(w1) == 0)
					lastIdx1 = i;
				else if (strs[i].compare(w2) == 0)
					lastIdx2 = i;
			}

			if (lastIdx1 != -1 && lastIdx2 != -1)
				minDist = std::min(minDist, std::abs(lastIdx1 - lastIdx2));
		}

		std::cout << "MinDistBtw2WordsInFile OneScan2 for [" << w1 << "," << w2 << "] in \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << minDist << std::endl;
		return minDist;
	}
};
class MinDistToTgtChar
{
public:
	MinDistToTgtChar(){}

	std::vector<int> TwoScan(const std::string & s, char c)
	{
		int N = s.size();
		std::vector<int> res(N, INT_MAX);
		int lastIdx = -1;
		for (int i = 0; i < N; ++i)
		{
			if (s[i] == c)
				lastIdx = i;
			if (lastIdx != -1)
				res[i] = i - lastIdx;
		}
		lastIdx = -1;
		for (int i = N-1; i >= 0; --i)
		{
			if (s[i] == c)
				lastIdx = i;
			if (lastIdx != -1)
				res[i] = std::min(res[i], lastIdx - i);
		}
		std::cout << "MinDistToTgtChar TwoScan for \"" << c << "\" from [" << s << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
MinDistBtw2WordsInFile OneScan for [tea,eat] in "ace, tea, and, ad, eat, kk, eat, dan, ate, tea, abc, eat, xyz": 2
MinDistBtw2WordsInFile BuildWordMap for "ace, tea, and, ad, eat, kk, eat, dan, ate, tea, abc, eat, xyz":
Row#0	= ace: 0
Row#1	= dan: 7
Row#2	= ad: 3
Row#3	= tea: 1, 9
Row#4	= and: 2
Row#5	= eat: 4, 6, 11
Row#6	= abc: 10
Row#7	= kk: 5
Row#8	= ate: 8
Row#9	= xyz: 12

MinPairDiff2SortedArrays ModifiedMerge2SortedArrays for "1, 9", and "4, 6, 11": 2, [9,11]
MinDistBtw2WordsInFile QueryFromWordMap for [tea,eat]: 2
MinDistBtw2WordsInFile OneScan2 for [eat,eat] in "ace, tea, and, ad, eat, kk, eat, dan, ate, tea, abc, eat, xyz": 2

MinDistToTgtChar TwoScan for "b" from [bloomberg]: 0, 1, 2, 2, 1, 0, 1, 2, 3
MinDistToTgtChar TwoScan for "a" from [bloomberg]: -1, -1, -1, -1, -1, -1, -1, -1, -1
*/
#endif