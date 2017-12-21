#ifndef REARRANGE_ARR_W_EQUAL_ENTRIES_K_AWAY_H
#define REARRANGE_ARR_W_EQUAL_ENTRIES_K_AWAY_H
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Rearrange String k Distance Apart
Elements of programming interview, HashTable: Find the smallest subarray covering all values, variant
Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".
http://www.geeksforgeeks.org/rearrange-a-string-so-that-all-same-characters-become-at-least-d-distance-away/

Key idea:
Fill out the original array starting with the entries that have max count at first available empty position and next k away positions

maxHeap:
O(n + mlogm) time, O(m) space for maxHeap, where n is the number of entries in A, m is the number of distinct entries in A

Similar problem: minimum run time task scheduler
Given a task sequence tasks such as ABBABBC, and an integer k, which is the cool down time between two same tasks.
Assume the execution for each individual task is 1 unit.
For example, if k = 3, then tasks BB takes a total of 5 unit time to finish, because B takes 1 unit of time to execute, then wait for 3 unit, and execute the second B again for another unit of time. So 1 + 3 + 1 = 5 unit for BB.
Given a task sequence and the cool down time, return the total execution time.
Follow up: Given a task sequence and the cool down time, rearrange the task sequence such that the execution time is minimal.
*/
class RearrangeArrWEqualEntriesKAway
{
public:
	RearrangeArrWEqualEntriesKAway(){}
	~RearrangeArrWEqualEntriesKAway(){}

	struct Less
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first == b.first ? a.second > b.second : a.first < b.first;//a.second > b.second ensures char order in diff bins the same which ensures same chars can be k apart
		}
	};
	std::string MaxHeapGreedyAssign(std::string s, int k)
	{
		if (k == 0) return s;
		int N = s.size();

		std::unordered_map<int, int> count;
		for (int i = 0; i < N; ++i)
		{
			++count[s[i] - 'a'];
		}
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Less> maxHeap;//<count,char>
		for (auto & p : count)
		{
			maxHeap.push({ p.second, p.first });
		}

		//simply greedy assign maxFreq chars w/ exactly k dist apart is wrong (aabbcc, 2 => abcabc)
		//greedy assign diff chars to fill each bin size is correct
		std::string res;
		while (!maxHeap.empty())
		{
			int binSize = std::min(k, N - (int)res.size());
			std::vector<std::pair<int, int>> remains;//<count,char>
			while (binSize-->0)
			{
				if (maxHeap.empty()) return "";
				auto p = maxHeap.top();
				maxHeap.pop();

				res.push_back(p.second + 'a');

				if (--p.first > 0)
					remains.push_back(p);

				//std::cout << "\"" << res << "\"" << std::endl;
			}
			for (auto & p : remains)
				maxHeap.push(p);
		}

		std::cout << "RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for \"" << k << "\", \"" << s << "\": " << res << std::endl;
		return res;
	}



	//WRONG: simply greedy assign maxFreq chars w/ exactly k dist apart is wrong (aabbcc, 2 => abcabc)
	struct SmallerThan
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first < b.first;
		}
	};
	void MaxHeap(std::vector<int> & v, int k)//wrong
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		
		//1. prepare a maxHeap<count, key> where the entry with max count is on top
		std::unordered_map<int, int> keyToCount;//first: key, second: count
		for (int i = 0; i < N; ++i)
		{
			++keyToCount[v[i]];
			v[i] = INT_MAX;//mark this position as empty
		}
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, SmallerThan> maxHeap;//first: count, second: key
		for (const auto p : keyToCount)
		{
			maxHeap.push({ p.second, p.first });
		}

		//2. fill the original array with the entry with max count at first empty position and next k away positions
		int front = 0;
		bool fail = false;
		while (!maxHeap.empty())
		{
			auto p = maxHeap.top();
			maxHeap.pop();
			for (int i = 0; i < p.first; ++i)
			{
				if (front + i * k >= N)
				{
					std::cout << "Cannot Rearrange!" << std::endl;
					fail = true;
					break;
				}
				v[front + i * k] = p.second;
			}

			if (fail)
				break;

			//3. advance front to next empty position
			while (front < N && v[front] != INT_MAX)
				++front;
		}

		std::cout << "RearrangeArrWEqualEntriesKAway MaxHeap for \"" << k << "\", \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aabbcc": abcabc
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "3", "aabbcc": abcabc
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aaabc": abaca
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aaadbbcc": abacabcd
*/
#endif