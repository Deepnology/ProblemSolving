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


Leetcode: Task Scheduler
Given a char array representing tasks CPU need to do.
It contains capital letters A to Z where different letters represent different tasks.
Tasks could be done without original order.
Each task could be done in one interval.
For each interval, CPU could finish one task or just be idle.
However, there is a non-negative cooling interval n that means between two same tasks
, there must be at least n intervals that CPU are doing different tasks or just be idle.
You need to return the least number of intervals the CPU will take to finish all the given tasks.
Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
Followup: the char order cannot change


Leetcode: Reorganize string
Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
If possible, output any possible result.
If not possible, return the empty string.
Example 1:
Input: S = "aab"
Output: "aba"
Example 2:
Input: S = "aaab"
Output: ""
This is a special case of Rearrange String k Distance Apart, where k is equal to 2.
Leetcode: Distant Barcodes
In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].
Rearrange the barcodes so that no two adjacent barcodes are equal.
You may return any answer, and it is guaranteed an answer exists.
Example 1:
Input: [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
Example 2:
Input: [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,2,1,2,1]
*/
class RearrangeArrWEqualEntriesKAway
{
public:
	RearrangeArrWEqualEntriesKAway(){}
	~RearrangeArrWEqualEntriesKAway(){}

	struct Less
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) const
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
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b) const
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
class RearrangeArrWEqualCharsKAway
{
public:
    RearrangeArrWEqualCharsKAway(){}

    int CountLeastSpace_Linear(const std::vector<char> & tasks, int n)//n: number of other elements (or empty) between 2 same elements
    {
        std::unordered_map<char, int> freq;
        for (const auto &c : tasks)
            ++freq[c];
        int maxFreq = 0;
        for (const auto &p : freq)
            maxFreq = std::max(maxFreq, p.second);
        int countOfMaxFreq = 0;
        for (const auto &p : freq)
            if (p.second == maxFreq)
                ++countOfMaxFreq;

        int space = (maxFreq - 1) //num of intervals in between maxFreq elements
                    * (n + 1) //interval space + 1st element on its left
                    + countOfMaxFreq; //remainings

        int res = space < (int)tasks.size() ? (int)tasks.size() : space;

        std::cout << "RearrangeArrWEqualEntriesKAway CountLeastSpace_Linear for \"" << n << "\" from \"" << Debug::ToStr1D<char>()(tasks) << "\": " << res << std::endl;
        return res;
    }


    struct Less
    {
        bool operator()(const std::pair<int,char> & a, const std::pair<int,char> & b) const
        {
            return a.first < b.first;
        }
    };
public:
    int CountLeastSpace_MaxHeap(const std::vector<char> & tasks, int n)//n: number of other elements (or empty) between 2 same elements
    {
        std::vector<char> count(26, 0);
        for (auto & c : tasks)
            ++count[c-'a'];
        std::priority_queue<std::pair<int,char>, std::vector<std::pair<int,char>>, Less> maxHeap;
        for (int i = 0; i < 26; ++i)
            if (count[i])
                maxHeap.push({count[i], i+'a'});
        std::vector<char> res;
        int total = 0;
        while (!maxHeap.empty())
        {
            int binSize = n+1;
            std::vector<std::pair<int,char>> remains;
            while (binSize-->0)
            {
                if (!maxHeap.empty())
                {
                    std::pair<int,char> p = maxHeap.top();
                    maxHeap.pop();
                    if (--p.first)
                        remains.push_back(p);

					res.push_back(p.second);
                    ++total;
                }
                else
                {
                    if (!remains.empty())
                    {
						res.insert(res.end(), binSize+1, ' ');
                        total += binSize+1;
                        break;
                    }
                }
            }
            for (auto & p : remains)
                maxHeap.push(p);
        }
        std::cout << "RearrangeArrWEqualCharsKAway CountLeastSpace_MaxHeap for \"" << n << "\" from \"" << Debug::ToStr1D<char>()(tasks) << "\": " << total << " (" << Debug::ToStr1D<char>()(res) << ")" << std::endl;
        return total;
    }

public:
	int CountLeastSpace_WithSameOrder(const std::vector<char> & tasks, int n)//n: number of other elements (or empty) between 2 same elements
	{
		int N = tasks.size();
		int res = N;
		std::unordered_map<char, int> lastIdx;
		for (int i = 0; i < N; ++i)
		{
			if (lastIdx.count(tasks[i]) && i - lastIdx[tasks[i]] - 1 < n)
				res += n - (i - lastIdx[tasks[i]] - 1);
			lastIdx[tasks[i]] = i;
		}

		std::cout << "RearrangeArrWEqualCharsKAway CountLessSpace_WithSameOrder for \"" << n << "\" from \"" << Debug::ToStr1D<char>()(tasks) << "\": " << res << std::endl;
		return res;
	}
};
class RearrangeArrWithoutAdjacentEqualChars
{
public:
    RearrangeArrWithoutAdjacentEqualChars(){}

    std::string Linear(std::string s)//O(N) time
    {
        int N = s.size();
        std::vector<int> count(26,0);
        for (char c : s)
            ++count[c-'a'];
        int maxCount = 0;
        int maxChar = 0;
        for (int i = 0; i < 26; ++i)
            if (maxCount < count[i])
            {
                maxCount = count[i];
                maxChar = i;
            }
        if (N%2==0 && maxCount>N/2) return "";//the most frequent char cannot exceed half length
        if (N%2==1 && maxCount>N/2+1) return "";//the most frequent char cannot exceed half length + 1
        std::string res(N, ' ');
        //1. fill up the most frequent char
        int i = 0;
        for (; i<N && count[maxChar]; i += 2)
        {
            res[i] = maxChar+'a';
            --count[maxChar];
        }
        //2. fill up the remaining chars
        int curChar = 0;
        for (; i<N; i += 2)
        {
            while (count[curChar]==0) ++curChar;
            res[i] = curChar + 'a';
            --count[curChar];
        }
        for (i=1; i<N; i+=2)
        {
            while (count[curChar]==0) ++curChar;
            res[i] = curChar +'a';
            --count[curChar];
        }

        std::cout << "RearrangeArrWithoutAdjacentEqualChars for \"" << s << "\": " << res << std::endl;
        return res;
    }

    std::vector<int> Linear(std::vector<int> && s) //Leetcode: Distant Barcodes
    {
        int N = s.size();
        std::unordered_map<int,int> count;
        for (auto i : s)
            ++count[i];
        int maxCount = 0;
        int maxNum = 0;
        for (auto & p : count)
            if (maxCount < p.second)
            {
                maxCount = p.second;
                maxNum = p.first;
            }
        std::vector<int> res(N);
        if (N%2==0 && maxCount>N/2) return res;//the most frequent char cannot exceed half length
        if (N%2==1 && maxCount>N/2+1) return res;//the most frequent char cannot exceed half length + 1

        //1. fill up the most frequent char
        int i = 0;
        for (; i<N && count.count(maxNum); i += 2)
        {
            res[i] = maxNum;
            --count[maxNum];
            if (count[maxNum]==0) count.erase(maxNum);
        }
        //2. fill up the remaining chars
        int curNum = 0;
        for (; i<N; i += 2)
        {
            while (!count.count(curNum)) ++curNum;
            res[i] = curNum;
            --count[curNum];
            if (count[curNum]==0) count.erase(curNum);
        }
        for (i=1; i<N; i+=2)
        {
            while (!count.count(curNum)) ++curNum;
            res[i] = curNum;
            --count[curNum];
            if (count[curNum]==0) count.erase(curNum);
        }
        std::cout << "RearrangeArrWithoutAdjacentEqualChars for \"" << Debug::ToStr1D<int>()(s) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
class RearrangeArrWo3ConsecuEqualChars //Amazon OA
{
public:
	RearrangeArrWo3ConsecuEqualChars(){}
	struct Less
	{
		bool operator()(const std::pair<int,char> & a, const std::pair<int,char> & b) const
		{
			return a.first < b.first;
		}
	};
	std::string UseMaxHeap(int countA, int countB, int countC)
	{
		std::priority_queue<std::pair<int,char>, std::vector<std::pair<int,char>>, Less> maxHeap;
		maxHeap.push({countA, 'a'});
		maxHeap.push({countB, 'b'});
		maxHeap.push({countC, 'c'});
		std::string res;
		while (!maxHeap.empty())
		{
			std::vector<std::pair<int,char>> remains;
			auto cur = maxHeap.top();
			maxHeap.pop();
			if (!res.empty() && res.back() == cur.second)
			{
				if (maxHeap.empty())
				{
					std::cout << "RearrangeArrWo3ConsecuEqualChars UseMaxHeap for " << countA << ", " << countB << ", " << countC << ": impossible " << res << std::endl;
					return "impossible";
				}
				auto nxt = maxHeap.top();
				maxHeap.pop();
				if (nxt.first >= 2)
				{
					res.push_back(nxt.second);
					res.push_back(nxt.second);
					nxt.first -= 2;
				} else
				{
					res.push_back(nxt.second);
					--nxt.first;
				}
				if (nxt.first > 0)
					remains.push_back(nxt);
				maxHeap.push(cur);
			} else
			{
				if (cur.first >= 2)
				{
					res.push_back(cur.second);
					res.push_back(cur.second);
					cur.first -= 2;
				} else
				{
					res.push_back(cur.second);
					--cur.first;
				}
				if (cur.first > 0)
					remains.push_back(cur);
			}

			for (auto & p : remains)
				maxHeap.push(p);
		}

		std::cout << "RearrangeArrWo3ConsecuEqualChars UseMaxHeap for " << countA << ", " << countB << ", " << countC << ": " << res << std::endl;
		return res;
	}
};
/*
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aabbcc": abcabc
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "3", "aabbcc": abcabc
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aaabc": abaca
RearrangeArrWEqualEntriesKAway MaxHeapGreedyAssign for "2", "aaadbbcc": abacabcd
RearrangeArrWEqualEntriesKAway CountLeastSpace_Linear for "2" from "a, a, b, b, c, c": 6
RearrangeArrWEqualEntriesKAway CountLeastSpace_Linear for "3" from "a, a, b, b, c, c": 7
RearrangeArrWEqualEntriesKAway CountLeastSpace_Linear for "2" from "a, a, a, b, c": 7
RearrangeArrWEqualEntriesKAway CountLeastSpace_Linear for "2" from "a, a, a, d, b, b, c, c": 8
RearrangeArrWEqualCharsKAway CountLeastSpace_MaxHeap for "2" from "a, a, b, b, c, c": 6 (a, b, c, a, b, c)
RearrangeArrWEqualCharsKAway CountLeastSpace_MaxHeap for "3" from "a, a, b, b, c, c": 7 (a, b, c,  , a, b, c)
RearrangeArrWEqualCharsKAway CountLeastSpace_MaxHeap for "2" from "a, a, a, b, c": 7 (a, b, c, a,  ,  , a)
RearrangeArrWEqualCharsKAway CountLeastSpace_MaxHeap for "2" from "a, a, a, d, b, b, c, c": 8 (a, b, c, a, d, c, b, a)
RearrangeArrWEqualCharsKAway CountLessSpace_WithSameOrder for "2" from "a, a, b, b, c, c": 12
RearrangeArrWEqualCharsKAway CountLessSpace_WithSameOrder for "3" from "a, a, b, b, c, c": 15
RearrangeArrWEqualCharsKAway CountLessSpace_WithSameOrder for "2" from "a, a, a, b, c": 9
RearrangeArrWEqualCharsKAway CountLessSpace_WithSameOrder for "2" from "a, a, a, d, b, b, c, c": 16
RearrangeArrWithoutAdjacentEqualChars for "aab": aba
RearrangeArrWithoutAdjacentEqualChars for "aabb": abab

RearrangeArrWo3ConsecuEqualChars UseMaxHeap for 1, 1, 6: ccaccbcc
RearrangeArrWo3ConsecuEqualChars UseMaxHeap for 1, 2, 3: ccbbac
RearrangeArrWo3ConsecuEqualChars UseMaxHeap for 3, 3, 3: aabbccabc
RearrangeArrWo3ConsecuEqualChars UseMaxHeap for 1, 1, 9: impossible ccaccbcc
*/
#endif