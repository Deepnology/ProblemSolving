/*HashTable*/
#ifndef SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_IN_ORDER_H
#define SHORTEST_SUB_ARR_CONTAIN_ALL_ENTRIES_IN_ORDER_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the smallest subarray that sequentially covering all values
Write a function that takes two integer-valued arrays A and Q and computes a minimum length subarray A[i:j] that sequentially covers Q.
Assume all elements in Q are distinct.

DistinceEntries: O(n) time, O(m) space, where n is the size of A, and m the size of Q

See also ShortestSubArrContainAllEntries.h, ShortestSubstrContainAllChars.h
*/
class ShortestSubArrContainAllEntriesInOrder
{
public:
	ShortestSubArrContainAllEntriesInOrder(){}
	~ShortestSubArrContainAllEntriesInOrder(){}

	std::pair<int, int> DistinctEntries(const std::vector<std::string> & v, const std::vector<std::string> & entries)
	{
		int N = v.size();
		int M = entries.size();
		std::unordered_map<std::string, int> wordMap;//first: entry, second: index in entries
		for (int i = 0; i < M; ++i)
		{
			wordMap[entries[i]] = i;
		}
		std::vector<int> latestIdx(M, -1);
		std::vector<int> curLenTill(M, INT_MAX);
		int minLen = INT_MAX;
		int minBegin = 0;
		int minEnd = 0;

		for (int i = 0; i < N; ++i)
		{
			auto itr = wordMap.find(v[i]);
			if (itr != wordMap.end())
			{
				int curWordIdx = itr->second;
				if (curWordIdx == 0)
				{
					curLenTill[0] = 1;
				}
				else if (curLenTill[curWordIdx - 1] != INT_MAX)//update curLenTill[curWordIdx] only when its preceding entry have been met
				{
					curLenTill[curWordIdx] = (i - latestIdx[curWordIdx - 1]) + curLenTill[curWordIdx - 1];
				}
				latestIdx[curWordIdx] = i;

				if (curWordIdx == M - 1 && curLenTill[M - 1] < minLen)//update minLen only when current word is the last entry in entries
				{
					minLen = curLenTill[M - 1];
					minBegin = i - curLenTill[M - 1] + 1;
					minEnd = i;
				}
			}
		}

		std::cout << Debug::ToStr1D<std::string, int>()(wordMap) << std::endl;
		std::string resStr = minLen == INT_MAX ? "N" : Debug::ToStr1D<std::string>()(v, minBegin, minEnd);
		std::cout << "ShortestSubArrContainAllEntriesInOrder DistinctEntries for \"" << Debug::ToStr1D<std::string>()(entries) << "\" in \"" << Debug::ToStr1D<std::string>()(v) << "\": " << minLen << " (" << resStr << ")" << std::endl;
		return{ minBegin, minEnd };
	}

	//not implemented
	std::pair<int, int> DuplicatedEntries(const std::vector<std::string> & v, const std::vector<std::string> & entries)
	{
		int N = v.size();
		int M = entries.size();
		std::unordered_map<std::string, std::set<int> > wordMap;//first: entry, second: a set of indices
		for (int i = 0; i < M; ++i)
		{
			wordMap[entries[i]].insert(i);
		}

		for (int i = 0; i < N; ++i)
		{
			auto itr = wordMap.find(v[i]);
			if (itr != wordMap.end())
			{

			}
		}

		return{ 0, 0 };
	}
};
/*
[B,0], [D,1]
ShortestSubArrContainAllEntriesInOrder DistinctEntries for "B, D" in "A, C, B, B, B, A, C, D, D, A, D, C, A, C, B": 4 (B, A, C, D)
*/
#endif