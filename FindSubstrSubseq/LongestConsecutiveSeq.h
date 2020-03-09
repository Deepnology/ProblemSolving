/*HashTable*/
#ifndef LONGEST_CONSECUTIVE_SEQ_H
#define LONGEST_CONSECUTIVE_SEQ_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the length of a longest contained range
The notion [a..b] when a and b are integers, is sometimes used to indicate the set of all integers between a and b, including both;
such a set is referred to as a range.
The size of the range [a..b] is defined to be b-a+1.
Write a function which takes as input a set of integers represented by an array A, and returns the size of a biggest range [x..y] contained in the set.

Leetcode: Longest Consecutive Sequence
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.

Hash map: O(n)
Sort and scan: O(nlogn) time

see also LISubstr.h
(after sorting the array, it would be the LISubstr problem)
*/

class LongestConsecutiveSeq
{
public:
	LongestConsecutiveSeq(){}
	~LongestConsecutiveSeq(){}

	int Len_HashSet(const std::vector<int> & num)
	{
		int N = num.size();
		std::unordered_set<int> hashSet;
		for (auto i : num)
			hashSet.insert(i);//O(1) time in average, O(n) time in worst case

		int lo = 0;
		int hi = 0;

		while (hashSet.size() > 0)
		{
			int cur = *hashSet.begin();
			hashSet.erase(cur);//O(1) time in average, O(n) time in worst case
			int min = cur;
			int max = cur;
			while (hashSet.count(min - 1))
			{
				hashSet.erase(--min);
			}
			while (hashSet.count(max + 1))
			{
				hashSet.erase(++max);
			}
			if (max - min > hi - lo)
			{
				hi = max;
				lo = min;
			}
		}
		std::cout << "LongestConsecutiveSeq HashSet for\"" << Debug::ToStr1D<int>()(num) << "\": " << hi - lo + 1 << " (" << lo << "..." << hi << ")" << std::endl;
		return hi - lo + 1;
	}

	int Len_HashMap(const std::vector<int> & num)
	{
		if (num.empty())
			return 0;
		int N = num.size();
		std::unordered_map<int, bool> hashMap;//key: num[i], value: visited
		for (int i = 0; i < N; ++i)
			hashMap.insert(std::make_pair(num[i], false));//insert all the numbers in num into map

		int maxConsecuCount = 0;
		int maxConsecuBegin = 0;
		int maxConsecuEnd = 0;
		for (std::unordered_map<int, bool>::iterator itr = hashMap.begin(); itr != hashMap.end(); ++itr)
		{
			if (itr->second)//already visited
				continue;

			int curConsecuCount = 1;
			int curNum = itr->first;
			itr->second = true;
			int prevNum = curNum - 1;
			int nextNum = curNum + 1;
			while (hashMap.count(prevNum) > 0)
			{
				++curConsecuCount;
				hashMap[prevNum] = true;
				--prevNum;
			}
			while (hashMap.count(nextNum) > 0)
			{
				++curConsecuCount;
				hashMap[nextNum] = true;
				++nextNum;
			}

			if (curConsecuCount > maxConsecuCount)
			{
				maxConsecuCount = curConsecuCount;
				maxConsecuBegin = prevNum + 1;
				maxConsecuEnd = nextNum - 1;
			}
		}

		std::cout << "LongestConsecutiveSeq HashMap for\"" << Debug::ToStr1D<int>()(num) << "\": " << maxConsecuCount << " (" << maxConsecuBegin << "..." << maxConsecuEnd << ")" << std::endl;
		return maxConsecuCount;
	}

	int Len_HashMap2(const std::vector<int> & num)
	{
		if (num.empty())
			return 0;
		int N = num.size();
		std::unordered_map<int,int> hashMap;//key: num[i], value: num[i]'s longest consecutive length as num[i] being the leftest or rightest
		int maxConsecuCount = 1;
		for (int i = 0; i < N; ++i)
		{
			if (hashMap.find(num[i]) != hashMap.end())//num[i] already exist in map
				continue;

			hashMap[num[i]] = 1;//add num[i] in map

			if (hashMap.find(num[i] - 1) != hashMap.end())//if num[i]'s left consecutive already exist in map
				maxConsecuCount = std::max(maxConsecuCount, this->updateMap(hashMap, num[i] - 1, num[i]));//update num[i]'s leftest consecutive's and num[i]'s longest consecutive length in map

			if (hashMap.find(num[i] + 1) != hashMap.end())//if num[i]'s right consecutive already exist in map
				maxConsecuCount = std::max(maxConsecuCount, this->updateMap(hashMap, num[i], num[i] + 1));//update num[i]'s leftest consecutive's and num[i]'s rightest longest consecutive length in map
		}

		std::cout << "LongestConsecutiveSeq HashMap2 for \"" << Debug::ToStr1D<int>()(num) << "\": " << maxConsecuCount << std::endl;
		return maxConsecuCount;
	}
private:
	int updateMap(std::unordered_map<int, int> & hashMap, int left, int right)
	{
		int leftest = left - hashMap[left] + 1;
		int rightest = right + hashMap[right] - 1;
		int len = rightest - leftest + 1;
		hashMap[leftest] = len;
		hashMap[rightest] = len;
		return len;
	}

public:
	int Len_Sort_Iterate(std::vector<int> num)
	{
		if (num.empty())
			return 0;
		std::string before = Debug::ToStr1D<int>()(num);
		int N = num.size();
		std::sort(num.begin(), num.end(), std::less<int>());//O(nlogn) time
		int maxConsecuCount = 0;
		int maxConsecuBegin = 0;
		int maxConsecuEnd = 0;
		int i = 0;
		while (i < N - 1)//O(n) time
		{
			int curBegin = i;
			for (int j = i + 1; j < N; ++j)
			{
				if (num[j] - num[i] != 1)
					break;
				++i;
			}
			if (i - curBegin + 1 > maxConsecuCount)
			{
				maxConsecuBegin = curBegin;
				maxConsecuEnd = i;
				maxConsecuCount = i - curBegin + 1;
			}
			++i;
		}
		std::vector<int> lcs(num.begin() + maxConsecuBegin, num.begin() + maxConsecuEnd + 1);
		std::cout << "LongestConsecutiveSeq Sort_Iterate for \"" << before << "\": " << maxConsecuCount << " (" << Debug::ToStr1D<int>()(lcs) << ")" << std::endl;
		return maxConsecuCount;
	}

	int Len_Sort_Iterate2(std::vector<int> num)
	{
		if (num.empty())
			return 0;
		std::string before = Debug::ToStr1D<int>()(num);
		int N = num.size();
		std::sort(num.begin(), num.end(), std::less<int>());//O(nlogn) time
		int maxConsecuCount = 1;
		int curConsecuCount = 1;

		int curConsecuBegin = 0;
		int maxConsecuBegin = 0;
		int maxConsecuEnd = 0;
		for (int i = 1; i < N; ++i)//O(n) time
		{
			int diff = num[i] - num[i - 1];
			if (diff == 0)//skip same number
				continue;
			if (diff == 1)//this element is a consecutive of previous one
			{
				++curConsecuCount;
				if (curConsecuCount > maxConsecuCount)
				{
					maxConsecuCount = curConsecuCount;
					maxConsecuBegin = curConsecuBegin;
					maxConsecuEnd = i;
				}
			}
			else
			{
				curConsecuCount = 1;//reset
				curConsecuBegin = i;//reset
			}
		}
		std::vector<int> lcs(num.begin() + maxConsecuBegin, num.begin() + maxConsecuEnd + 1);
		std::cout << "LongestConsecutiveSeq Sort_Iterate2 for \"" << before << "\": " << maxConsecuCount << " (" << Debug::ToStr1D<int>()(lcs) << ")" << std::endl;
		return maxConsecuCount;
	}
};
/*
LongestConsecutiveSeq HashSet for"4, 2, 5, 1, -4, 8, 6, -6, 9, 11, 7, -3, -5": 6 (4...9)
LongestConsecutiveSeq HashMap for"4, 2, 5, 1, -4, 8, 6, -6, 9, 11, 7, -3, -5": 6 (4...9)
LongestConsecutiveSeq HashMap2 for "4, 2, 5, 1, -4, 8, 6, -6, 9, 11, 7, -3, -5": 6
LongestConsecutiveSeq Sort_Iterate for "4, 2, 5, 1, -4, 8, 6, -6, 9, 11, 7, -3, -5": 6 (4, 5, 6, 7, 8, 9)
LongestConsecutiveSeq Sort_Iterate2 for "4, 2, 5, 1, -4, 8, 6, -6, 9, 11, 7, -3, -5": 6 (4, 5, 6, 7, 8, 9)
*/
#endif