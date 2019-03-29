/*HashTable*/
#ifndef LONGEST_SUB_ARR_W_DISTINCT_ENTRIES_H
#define LONGEST_SUB_ARR_W_DISTINCT_ENTRIES_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
1.
Leetcode: Longest Substring Without Repeating Characters (LongestSubstrWoRepeatChars.h)
Elements of programming interview, HashTable: Find the longest subarray with distinct entries
Write a function that takes an array of integers A and returns the length of a longest subarray of A with the constraint that all its elements are distinct.

BruteForce HashTable:
For each element, create a hash table, put all elements on its right to the hash table until meet a duplicate.
O(n^2) time, O(c) space, where c is the distinct entries in A

SlideWindow HashTable: O(n) time, O(c) space, where c is the distinct entries in A

2.
Leetcode: Longest Substring with At Most Two Distinct Characters
Given a string S, find the length of the longest substring T that contains at most 2 distinct characters.
For example, Given S = "eceba", T is "ece" which its length is 3.
Leetcode: Fruit into baskets
In a row of trees, the i-th tree produces fruit with type tree[i].
You start at any tree of your choice, then repeatedly perform the following steps:
Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.
You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.
What is the total amount of fruit you can collect with this procedure?

SlideWindow HashTable: O(n) time, O(1) space
SlideWindow 2Ptrs: O(n) time, O(1) space

3.
Leetcode: Longest Substring with At Most K Distinct Characters
Follow-up: find the length of the longest substring T that contains at most K distinct characters.
SlideWindow HashTable: O(n) time, O(K) space
*/
class LongestSubArrWDistinctEntries
{
public:
	LongestSubArrWDistinctEntries(){}
	~LongestSubArrWDistinctEntries(){}

	int HashTable(const std::vector<int> & v)//better...see also LongestSubstrWoRepeatChars.h
	{
		int N = v.size();
		std::unordered_map<int, int> lastIdx;//the index of the last occurrence of a value in v
		int maxLen = 0;
		int maxBegin = 0;
		int maxEnd = 0;
		int curBegin = 0;
		for (int i = 0; i < N; ++i)
		{
			auto itr = lastIdx.find(v[i]);
			if (itr == lastIdx.end())//doesn't exist
			{
				lastIdx.insert({ v[i], i });
			}
			else//already exist
			{
				if (itr->second >= curBegin)//last occurrence is inside the window, must exclude it to adopt v[i]
				{
					curBegin = itr->second + 1;
				}
				itr->second = i;
			}

			if (i - curBegin + 1 > maxLen)
			{
				maxLen = i - curBegin + 1;
				maxBegin = curBegin;
				maxEnd = i;
			}
		}

		std::cout << "LongestSubArrWDistinctEntries HashTable for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << " (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxLen;
	}

	int AtMost2_HashTable(const std::vector<int> & v)
	{
		int N = v.size();
		std::unordered_map<int, int> lastIdx;//the index of the last occurrence of a value in v
		int maxLen = 0;
		int maxBegin = 0;
		int maxEnd = 0;
		int curBegin = 0;
		for (int i = 0; i < N; ++i)
		{
			auto itr = lastIdx.find(v[i]);
			if (lastIdx.size() == 2 && itr == lastIdx.end())//size is 2 && doesn't exist
			{
				//remove the one whose lastIdx is more left
				//update curBegin to the next right idx of the removed element
				int leftmostEntry;
				int leftmostIdx = INT_MAX;
				for (const auto & p : lastIdx)
				{
					if (p.second < leftmostIdx)
					{
						leftmostIdx = p.second;
						leftmostEntry = p.first;
					}
				}

				lastIdx.erase(leftmostEntry);
				curBegin = leftmostIdx + 1;
			}

			//update existing entry's last idx OR insert new entry
			lastIdx[v[i]] = i;

			if (i - curBegin + 1 > maxLen)
			{
				maxLen = i - curBegin + 1;
				maxBegin = curBegin;
				maxEnd = i;
			}
		}

		std::cout << "LongestSubArrWDistinctEntries AtMost2_HashTable for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << " (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxLen;
	}

	int AtMostK_HashTable(const std::vector<int> & v, int K)
	{
		int N = v.size();
		std::unordered_map<int, int> count;//the count of the distinct entry in the current window
		int maxLen = 0;
		int maxBegin = 0;
		int maxEnd = 0;
		int curBegin = 0;
		for (int i = 0; i < N; ++i)
		{
			auto itr = count.find(v[i]);
			if (itr == count.end())//doesn't exist
			{
				count.insert({ v[i], 1 });

				//keep removing the leftmost entry until count.size() <= K
				//and advancing curBegin
				while ((int)count.size() > K)
				{
					int leftmostEntry = v[curBegin++];
					int leftmostCount = count[leftmostEntry];
					if (leftmostCount > 1)
						--count[leftmostEntry];
					else
						count.erase(leftmostEntry);
				}
			}
			else//already exist
			{
				++count[v[i]];
			}

			if (i - curBegin + 1 > maxLen)
			{
				maxLen = i - curBegin + 1;
				maxBegin = curBegin;
				maxEnd = i;
			}
		}

		std::cout << "LongestSubArrWDistinctEntries AtMostK_HashTable for \"" << K << ", From " << Debug::ToStr1D<int>()(v) << "\": " << maxLen << " (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxLen;
	}

	int AtMost2_2Ptrs(const std::vector<int> & v)
	{
		int N = v.size();
		int maxLen = 0;
		int maxBegin = 0;
		int maxEnd = 0;
		int curBegin = 0;
		int prevDiff = -1;//last idx of the prev diff element of current v[i]
		for (int i = 1; i < N; ++i)
		{
			if (v[i] == v[i - 1])
				continue;

			//now v[i] diff from v[i-1]
			if (prevDiff >= 0 && v[i] != v[prevDiff])//v[i] also diff from v[prevDiff]
			{
				//now v[i] diff from both v[i-1] and v[prevDiff]
				//must exclude v[prevDiff] to adopt v[i]

				//update maxLen before update curBegin
				//check the range [curBegin,i-1] length
				if (i - curBegin > maxLen)
				{
					maxLen = i - curBegin;//exclude i
					maxBegin = curBegin;
					maxEnd = i - 1;
				}
				
				curBegin = prevDiff + 1;
			}

			prevDiff = i - 1;
		}

		if (N - curBegin > maxLen)
		{
			maxLen = N - curBegin;
			maxBegin = curBegin;
			maxEnd = N - 1;
		}

		std::cout << "LongestSubArrWDistinctEntries AtMost2_2Ptrs for \"" << Debug::ToStr1D<int>()(v) << "\": " << maxLen << " (" << Debug::ToStr1D<int>()(v, maxBegin, maxEnd) << ")" << std::endl;
		return maxLen;
	}
};
/*
LongestSubArrWDistinctEntries HashTable for "6, 2, 6, 1, 1, 5, 4, 0, 5, 7, 5, 1, 7, 8, 8, 0, 5, 2, 8, 6, 4, 5, 5, 0, 0": 6 (0, 5, 2, 8, 6, 4)
LongestSubArrWDistinctEntries AtMost2_HashTable for "6, 2, 6, 1, 1, 5, 4, 0, 5, 7, 5, 1, 7, 8, 8, 0, 5, 2, 8, 6, 4, 5, 5, 0, 0": 4 (5, 5, 0, 0)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "6, 2, 6, 1, 1, 5, 4, 0, 5, 7, 5, 1, 7, 8, 8, 0, 5, 2, 8, 6, 4, 5, 5, 0, 0": 4 (5, 5, 0, 0)
LongestSubArrWDistinctEntries AtMostK_HashTable for "6, From 6, 2, 6, 1, 1, 5, 4, 0, 5, 7, 5, 1, 7, 8, 8, 0, 5, 2, 8, 6, 4, 5, 5, 0, 0": 14 (1, 1, 5, 4, 0, 5, 7, 5, 1, 7, 8, 8, 0, 5)
LongestSubArrWDistinctEntries HashTable for "0, 3, 7, 6, 4, 4, 6, 8, 9, 8, 1, 4, 6, 2, 8, 8, 8, 0, 4, 0, 0, 6, 2, 3, 2": 6 (9, 8, 1, 4, 6, 2)
LongestSubArrWDistinctEntries AtMost2_HashTable for "0, 3, 7, 6, 4, 4, 6, 8, 9, 8, 1, 4, 6, 2, 8, 8, 8, 0, 4, 0, 0, 6, 2, 3, 2": 4 (6, 4, 4, 6)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "0, 3, 7, 6, 4, 4, 6, 8, 9, 8, 1, 4, 6, 2, 8, 8, 8, 0, 4, 0, 0, 6, 2, 3, 2": 4 (6, 4, 4, 6)
LongestSubArrWDistinctEntries AtMostK_HashTable for "5, From 0, 3, 7, 6, 4, 4, 6, 8, 9, 8, 1, 4, 6, 2, 8, 8, 8, 0, 4, 0, 0, 6, 2, 3, 2": 12 (4, 6, 2, 8, 8, 8, 0, 4, 0, 0, 6, 2)
LongestSubArrWDistinctEntries HashTable for "7, 0, 4, 7, 4, 7, 9, 6, 8, 2, 5, 3, 3, 1, 1, 0, 4, 2, 8, 5, 4, 7, 8, 7, 1": 8 (4, 7, 9, 6, 8, 2, 5, 3)
LongestSubArrWDistinctEntries AtMost2_HashTable for "7, 0, 4, 7, 4, 7, 9, 6, 8, 2, 5, 3, 3, 1, 1, 0, 4, 2, 8, 5, 4, 7, 8, 7, 1": 4 (4, 7, 4, 7)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "7, 0, 4, 7, 4, 7, 9, 6, 8, 2, 5, 3, 3, 1, 1, 0, 4, 2, 8, 5, 4, 7, 8, 7, 1": 4 (4, 7, 4, 7)
LongestSubArrWDistinctEntries AtMostK_HashTable for "4, From 7, 0, 4, 7, 4, 7, 9, 6, 8, 2, 5, 3, 3, 1, 1, 0, 4, 2, 8, 5, 4, 7, 8, 7, 1": 7 (7, 0, 4, 7, 4, 7, 9)
LongestSubArrWDistinctEntries HashTable for "3, 4, 4, 1, 6, 2, 8, 7, 0, 7, 0, 8, 0, 5, 2, 8, 3, 3, 9, 4, 3, 2, 7, 8, 4": 7 (4, 1, 6, 2, 8, 7, 0)
LongestSubArrWDistinctEntries AtMost2_HashTable for "3, 4, 4, 1, 6, 2, 8, 7, 0, 7, 0, 8, 0, 5, 2, 8, 3, 3, 9, 4, 3, 2, 7, 8, 4": 4 (7, 0, 7, 0)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "3, 4, 4, 1, 6, 2, 8, 7, 0, 7, 0, 8, 0, 5, 2, 8, 3, 3, 9, 4, 3, 2, 7, 8, 4": 4 (7, 0, 7, 0)
LongestSubArrWDistinctEntries AtMostK_HashTable for "5, From 3, 4, 4, 1, 6, 2, 8, 7, 0, 7, 0, 8, 0, 5, 2, 8, 3, 3, 9, 4, 3, 2, 7, 8, 4": 11 (2, 8, 7, 0, 7, 0, 8, 0, 5, 2, 8)
LongestSubArrWDistinctEntries HashTable for "7, 8, 7, 5, 4, 4, 9, 8, 3, 9, 8, 8, 3, 6, 7, 2, 3, 5, 0, 9, 6, 0, 2, 2, 4": 7 (6, 7, 2, 3, 5, 0, 9)
LongestSubArrWDistinctEntries AtMost2_HashTable for "7, 8, 7, 5, 4, 4, 9, 8, 3, 9, 8, 8, 3, 6, 7, 2, 3, 5, 0, 9, 6, 0, 2, 2, 4": 3 (7, 8, 7)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "7, 8, 7, 5, 4, 4, 9, 8, 3, 9, 8, 8, 3, 6, 7, 2, 3, 5, 0, 9, 6, 0, 2, 2, 4": 3 (7, 8, 7)
LongestSubArrWDistinctEntries AtMostK_HashTable for "5, From 7, 8, 7, 5, 4, 4, 9, 8, 3, 9, 8, 8, 3, 6, 7, 2, 3, 5, 0, 9, 6, 0, 2, 2, 4": 10 (5, 4, 4, 9, 8, 3, 9, 8, 8, 3)
LongestSubArrWDistinctEntries HashTable for "4, 4, 8, 6, 4, 5, 3, 5, 7, 4, 9, 2, 5, 7, 7, 1, 2, 6, 8, 7, 0, 8, 3, 7, 1": 6 (3, 5, 7, 4, 9, 2)
LongestSubArrWDistinctEntries AtMost2_HashTable for "4, 4, 8, 6, 4, 5, 3, 5, 7, 4, 9, 2, 5, 7, 7, 1, 2, 6, 8, 7, 0, 8, 3, 7, 1": 3 (4, 4, 8)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "4, 4, 8, 6, 4, 5, 3, 5, 7, 4, 9, 2, 5, 7, 7, 1, 2, 6, 8, 7, 0, 8, 3, 7, 1": 3 (4, 4, 8)
LongestSubArrWDistinctEntries AtMostK_HashTable for "4, From 4, 4, 8, 6, 4, 5, 3, 5, 7, 4, 9, 2, 5, 7, 7, 1, 2, 6, 8, 7, 0, 8, 3, 7, 1": 6 (4, 4, 8, 6, 4, 5)
LongestSubArrWDistinctEntries HashTable for "8, 4, 8, 7, 7, 6, 2, 5, 6, 1, 8, 1, 8, 9, 6, 5, 4, 8, 0, 0, 2, 4, 6, 4, 3": 6 (1, 8, 9, 6, 5, 4)
LongestSubArrWDistinctEntries AtMost2_HashTable for "8, 4, 8, 7, 7, 6, 2, 5, 6, 1, 8, 1, 8, 9, 6, 5, 4, 8, 0, 0, 2, 4, 6, 4, 3": 4 (1, 8, 1, 8)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "8, 4, 8, 7, 7, 6, 2, 5, 6, 1, 8, 1, 8, 9, 6, 5, 4, 8, 0, 0, 2, 4, 6, 4, 3": 4 (1, 8, 1, 8)
LongestSubArrWDistinctEntries AtMostK_HashTable for "4, From 8, 4, 8, 7, 7, 6, 2, 5, 6, 1, 8, 1, 8, 9, 6, 5, 4, 8, 0, 0, 2, 4, 6, 4, 3": 7 (6, 1, 8, 1, 8, 9, 6)
LongestSubArrWDistinctEntries HashTable for "2, 9, 1, 0, 9, 9, 0, 6, 4, 6, 7, 7, 4, 8, 0, 1, 4, 3, 4, 8, 2, 4, 8, 4, 1": 5 (7, 4, 8, 0, 1)
LongestSubArrWDistinctEntries AtMost2_HashTable for "2, 9, 1, 0, 9, 9, 0, 6, 4, 6, 7, 7, 4, 8, 0, 1, 4, 3, 4, 8, 2, 4, 8, 4, 1": 4 (0, 9, 9, 0)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "2, 9, 1, 0, 9, 9, 0, 6, 4, 6, 7, 7, 4, 8, 0, 1, 4, 3, 4, 8, 2, 4, 8, 4, 1": 4 (0, 9, 9, 0)
LongestSubArrWDistinctEntries AtMostK_HashTable for "5, From 2, 9, 1, 0, 9, 9, 0, 6, 4, 6, 7, 7, 4, 8, 0, 1, 4, 3, 4, 8, 2, 4, 8, 4, 1": 10 (0, 9, 9, 0, 6, 4, 6, 7, 7, 4)
LongestSubArrWDistinctEntries HashTable for "1, 6, 5, 8, 3, 7, 2, 4, 1, 4, 3, 0, 2, 2, 6, 5, 1, 0, 7, 8, 2, 2, 6, 3, 4": 8 (1, 6, 5, 8, 3, 7, 2, 4)
LongestSubArrWDistinctEntries AtMost2_HashTable for "1, 6, 5, 8, 3, 7, 2, 4, 1, 4, 3, 0, 2, 2, 6, 5, 1, 0, 7, 8, 2, 2, 6, 3, 4": 3 (4, 1, 4)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "1, 6, 5, 8, 3, 7, 2, 4, 1, 4, 3, 0, 2, 2, 6, 5, 1, 0, 7, 8, 2, 2, 6, 3, 4": 3 (4, 1, 4)
LongestSubArrWDistinctEntries AtMostK_HashTable for "5, From 1, 6, 5, 8, 3, 7, 2, 4, 1, 4, 3, 0, 2, 2, 6, 5, 1, 0, 7, 8, 2, 2, 6, 3, 4": 8 (2, 4, 1, 4, 3, 0, 2, 2)
LongestSubArrWDistinctEntries HashTable for "8, 7, 2, 9, 9, 9, 1, 6, 1, 7, 4, 3, 8, 9, 9, 9, 5, 8, 6, 5, 4, 4, 1, 3, 1": 7 (6, 1, 7, 4, 3, 8, 9)
LongestSubArrWDistinctEntries AtMost2_HashTable for "8, 7, 2, 9, 9, 9, 1, 6, 1, 7, 4, 3, 8, 9, 9, 9, 5, 8, 6, 5, 4, 4, 1, 3, 1": 4 (2, 9, 9, 9)
LongestSubArrWDistinctEntries AtMost2_2Ptrs for "8, 7, 2, 9, 9, 9, 1, 6, 1, 7, 4, 3, 8, 9, 9, 9, 5, 8, 6, 5, 4, 4, 1, 3, 1": 4 (2, 9, 9, 9)
LongestSubArrWDistinctEntries AtMostK_HashTable for "4, From 8, 7, 2, 9, 9, 9, 1, 6, 1, 7, 4, 3, 8, 9, 9, 9, 5, 8, 6, 5, 4, 4, 1, 3, 1": 8 (8, 9, 9, 9, 5, 8, 6, 5)
*/
#endif