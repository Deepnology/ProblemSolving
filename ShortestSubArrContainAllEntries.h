/*HashTable*/
#ifndef SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_H
#define SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_H
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the smallest subarray covering all values

Stormrage: O(n) time

See also ShortestSubstrContainAllChars.h
*/
class ShortestSubArrContainAllEntries
{
public:
	ShortestSubArrContainAllEntries(){}
	~ShortestSubArrContainAllEntries(){}

	std::pair<int, int> Stormrage(const std::vector<std::string> & v, const std::vector<std::string> & entries)
	{
		int N = v.size();
		int M = entries.size();
		std::unordered_map<std::string, int> wordMap;//first: entry, second: count
		for (const auto & s : entries)
			++wordMap[s];

		std::unordered_map<std::string, int> foundMap;//first: entry, second: count
		int begin = 0;
		int end = 0;
		int foundCount = 0;
		int minLen = INT_MAX;
		int minBegin = -1;
		int minEnd = -1;
		for (; end < N; ++end)
		{
			if (wordMap.find(v[end]) == wordMap.end())
				continue;

			++foundMap[v[end]];//might also exceed the required amount
			if (foundMap[v[end]] <= wordMap[v[end]])
				++foundCount;

			if (foundCount == M)
			{
				//advance begin for 2 cases: irrelevant and redundant
				while (true)
				{
					if (wordMap.find(v[begin]) == wordMap.end())//irrelevant
						++begin;
					else if (foundMap[v[begin]] > wordMap[v[begin]])//redundant
					{
						--foundMap[v[begin]];
						++begin;
					}
					else
						break;
				}
				if (end - begin + 1 < minLen)
				{
					minLen = end - begin + 1;
					minBegin = begin;
					minEnd = end;
				}
			}
		}

		std::cout << Debug::ToStr1D<std::string, int>()(wordMap) << std::endl;
		std::string res("NULL");
		if (minLen != INT_MAX)
			res = Debug::ToStr1D<std::string>()(v, minBegin, minEnd);
		std::cout << "ShortestSubArrContainAllEntries Stormrage for \"" << Debug::ToStr1D<std::string>()(entries) << "\" in \"" << Debug::ToStr1D<std::string>()(v) << "\": [" << minBegin << "," << minEnd << "] = " << res << std::endl;
		return{ minBegin, minEnd };
	}

	//in this case, we can't keep track of the begin ptr
	std::pair<int, int> FromStream_DistinctEntries(std::istringstream & iss, const std::vector<std::string> & entries)
	{
		std::list<int> lastIdxQue;//keep track of distinct entries' last occurrence index
		std::unordered_map<std::string, std::list<int>::iterator> wordToItr;//first: entry, second: itr to entry's last occurrence index
		for (const std::string & s : entries)
		{
			wordToItr.insert({ s, lastIdxQue.end() });//vector.end() iterator can be invalidated, so use list
		}

		int minLen = INT_MAX;
		int minBegin = 0;
		int minEnd = 0;
		int idx = 0;
		std::string buf;
		while (iss >> buf)
		{
			auto itr = wordToItr.find(buf);
			if (itr != wordToItr.end())
			{
				//1. remove previous occurrence
				if (itr->second != lastIdxQue.end())
					lastIdxQue.erase(itr->second);
				//2. update last occurrence index
				lastIdxQue.push_back(idx);
				itr->second = std::prev(lastIdxQue.end());
			}
			if (lastIdxQue.size() == entries.size() && idx - lastIdxQue.front() < minLen)
			{
				minLen = idx - lastIdxQue.front();
				minBegin = lastIdxQue.front();
				minEnd = idx;
			}
			++idx;
		}

		std::cout << "ShortestSubArrContainAllEntries FromStream_DistinctEntries for \"" << Debug::ToStr1D<std::string>()(entries) << "\" in \"" << iss.str() << "\": [" << minBegin << "," << minEnd << "]" << std::endl;
		return{ minBegin, minEnd };
	}
};
/*
[B,1], [D,1]
ShortestSubArrContainAllEntries Stormrage for "B, D" in "A, C, B, B, B, A, C, D, D, A, D, C, A, C, B": [4,7] = B, A, C, D
[A,2], [B,2]
ShortestSubArrContainAllEntries Stormrage for "A, B, B, A" in "A, C, D, A, B, A, C, D, A, A, D, B, A, B, C": [9,13] = A, D, B, A, B
ShortestSubArrContainAllEntries FromStream_DistinctEntries for "B, D" in "A C B B B A C D D A D C A C B": [4,7]
ShortestSubArrContainAllEntries FromStream_DistinctEntries for "B, C, D" in "A B D A B A A D D C A A A D B A B C": [13,17]
*/
#endif