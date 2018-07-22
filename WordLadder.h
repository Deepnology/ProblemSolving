#ifndef WORD_LADDER_H
#define WORD_LADDER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Debug.h"
/*
Elements of programming interview, Graph: Transform one string to another
Given a dictionary D and two strings s and t, write a function to compute the length of the shortest production sequence if s produces t.
This is a shortest path in undirected graph problem, which is solved with BFS.

Leetcode: Word Ladder
// Given two words (start and end), and a dictionary, find the length of 
// shortest transformation sequence from start to end, such that:
//
// Only one letter can be changed at a time
// Each intermediate word must exist in the dictionary
// For example,
//
// Given:
// start = "hit"
// end = "cog"
// dict = ["hot","dot","dog","lot","log"]
// As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
// return its length 5.

Leetcode: Word Ladder II
// Given two words (start and end), and a dictionary, find all shortest 
// transformation sequence(s) from start to end, such that:
//
// Only one letter can be changed at a time
// Each intermediate word must exist in the dictionary
// For example,
//
// Given:
// start = "hit"
// end = "cog"
// dict = ["hot","dot","dog","lot","log"]
// Return
//   [
//       ["hit","hot","dot","dog","cog"],
//       ["hit","hot","lot","log","cog"]
//   ]
// Note:
//  All words have the same length.
//  All words contain only lowercase alphabetic characters.
*/
class WordLadder
{
public:
	WordLadder(){}
	~WordLadder(){}

	//1. find an arbitrary shortest path
	int BFS(const std::string & start, const std::string & end, const std::vector<std::string> & wordList)
	{
		std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
		if (dict.count(end) == 0) return 0;
		std::unordered_set<std::string> visit;
		std::queue<std::string> que;
		que.push(start);
		visit.insert(start);
		int dist = 1;
		while (!que.empty())
		{
			int levelCount = que.size();
			while (levelCount-->0)
			{
				std::string curWord = que.front();
				que.pop();
				if (curWord == end)//found shortest path
					return dist;
				for (int i = 0; i < (int)curWord.size(); ++i)
				{
					std::string nxtWord = curWord;
					for (char c = 'a'; c <= 'z'; ++c)
					{
						if (c == curWord[i])
							continue;
						nxtWord[i] = c;
						if (dict.count(nxtWord) && !visit.count(nxtWord))
						{
							visit.insert(nxtWord);
							que.push(nxtWord);
						}
					}
				}
			}
			++dist;
		}
		return 0;
	}
	int BFS_2Dir(const std::string & start, const std::string & end, const std::vector<std::string> & wordList)
	{
		std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
		if (dict.count(end) == 0) return 0;
		std::unordered_set<std::string> fwd;
		std::unordered_set<std::string> bwd;
		std::unordered_set<std::string> visit;
		fwd.insert(start);
		bwd.insert(end);
		visit.insert(start);
		visit.insert(end);
		int dist = 1;
		while (!fwd.empty() && !bwd.empty())
		{
			if (bwd.size() < fwd.size())
				std::swap(fwd, bwd);
			std::unordered_set<std::string> nxtLevel;
			for (auto & cur : fwd)
			{
				for (int i = 0; i < (int)cur.size(); ++i)
				{
					std::string nxt = cur;
					for (char c = 'a'; c <= 'z'; ++c)
						if (c != cur[i])
						{
							nxt[i] = c;
							if (bwd.count(nxt))
								return dist + 1;
							if (dict.count(nxt) && !visit.count(nxt))
							{
								visit.insert(nxt);
								nxtLevel.insert(nxt);
							}
						}
				}
			}
			++dist;
			std::swap(fwd, nxtLevel);
		}
		return 0;
	}

	//2. enumerate all diff shortest paths instead of enumerating all diff result configurations with a shortest path
	std::vector<std::vector<std::string>> FindAllBFS(const std::string & start, const std::string & end, const std::vector<std::string> & strs)
	{
		std::unordered_set<std::string> dict(strs.begin(), strs.end());
		std::vector<std::vector<std::string>> res;
		std::queue<std::string> que;
		que.push(start);
		std::unordered_set<std::string> visit;
		visit.insert(start);
		std::queue<std::vector<std::string>> pathQue;
		pathQue.push(std::vector<std::string>(1, start));
		int maxLen = INT_MAX;
		while (!que.empty())
		{
			int levelCount = que.size();
			bool reached = false;
			std::vector<std::string> levelVisit;
			while (levelCount-->0)
			{
				std::string curWord = que.front();
				que.pop();
				std::vector<std::string> curPath = pathQue.front();
				pathQue.pop();
				int curLen = curPath.size();
				if (curLen > maxLen)
					continue;
				if (curWord == end)
				{
					res.push_back(curPath);
					if (maxLen == INT_MAX)
						maxLen = curLen;
					if (!reached)
						reached = true;
					continue;
				}
				else if (curLen == maxLen)
					continue;
				for (int i = 0; i < (int)curWord.size(); ++i)
				{
					std::string nxtWord = curWord;
					for (char c = 'a'; c <= 'z'; ++c)
					{
						if (c == curWord[i])
							continue;
						nxtWord[i] = c;
						if (dict.count(nxtWord) && !visit.count(nxtWord))
						{
							levelVisit.push_back(nxtWord);
							que.push(nxtWord);
							curPath.push_back(nxtWord);
							pathQue.push(curPath);
							curPath.pop_back();
						}
					}
				}
			}
			if (reached)
				break;
			for (auto & s : levelVisit)
				visit.insert(s);
		}
		return res;
	}
	std::vector<std::vector<std::string>> FindAllBFS_2Dir(const std::string & start, const std::string & end, const std::vector<std::string> & strs)
	{
		std::unordered_set<std::string> dict(strs.begin(), strs.end());
		std::vector<std::vector<std::string>> res;
		if (!dict.count(end)) return res;
		std::unordered_map<std::string,std::unordered_set<std::string>> fwdAdjList;
		std::unordered_set<std::string> visit;
		std::unordered_set<std::string> fwd;
		std::unordered_set<std::string> bwd;
		fwd.insert(start);
		bwd.insert(end);
		visit.insert(start);
		visit.insert(end);
		bool isFwd = true;
		int dist = 1;
		while (!fwd.empty() && !bwd.empty())
		{
			bool reach = false;
			if (bwd.size() < fwd.size())
			{
				std::swap(fwd, bwd);
				isFwd = !isFwd;
			}
			std::unordered_set<std::string> nxtLevel;
			std::unordered_map<std::string,std::unordered_set<std::string>> fwdAdjList2;
			for (auto & cur : fwd)
			{
				for (int i = 0; i < (int)cur.size(); ++i)
				{
					std::string nxt = cur;
					for (char c = 'a'; c <= 'z'; ++c)
						if (c != cur[i])
						{
							nxt[i] = c;
							if (bwd.count(nxt))
							{
								reach = true;
								if (isFwd)
									fwdAdjList[cur].insert(nxt);
								else
									fwdAdjList[nxt].insert(cur);
							}
							if (reach) continue;
							if (dict.count(nxt) && !visit.count(nxt))
							{
								nxtLevel.insert(nxt);
								if (isFwd)
									fwdAdjList2[cur].insert(nxt);
								else
									fwdAdjList2[nxt].insert(cur);
							}
						}
				}
			}
			++dist;
			if (reach) break;
			fwd.clear();
			for (auto & nxt : nxtLevel)
			{
				visit.insert(nxt);//mark visit here to avoid skipping some paths
				fwd.insert(nxt);
			}
			//now adding extras (if reached, we don't need to add extras)
			for (auto & p : fwdAdjList2)
				for (auto & s : p.second)
					fwdAdjList[p.first].insert(s);
		}

		std::vector<std::string> path;
		recur(fwdAdjList, start, end, path, res);
		return res;
	}
	void recur(std::unordered_map<std::string,std::unordered_set<std::string>> & adjList, std::string cur, const std::string & end, std::vector<std::string> & path, std::vector<std::vector<std::string>> & res)
	{
		path.push_back(cur);
		if (cur == end)
		{
			res.push_back(path);
			path.pop_back();
			return;
		}
		for (auto & nxt : adjList[cur])
			recur(adjList, nxt, end, path, res);
		path.pop_back();
	}

	void Test(const std::string & start, const std::string & end, const std::vector<std::string> & words)
	{
		int res1 = BFS(start, end, words);
		int res2 = BFS_2Dir(start, end, words);
		std::vector<std::vector<std::string>> res3 = FindAllBFS(start, end, words);
		std::vector<std::vector<std::string>> res4 = FindAllBFS_2Dir(start, end, words);
		std::cout << "WordLadder BFS, BFS_2Dir, FindAllBFS, FindAllBFS_2Dir for \"" << start << "\", \"" << end << "\" from [" << Debug::ToStr1D<std::string>()(words) << "]" << std::endl;
		std::cout << res1 << std::endl;
		std::cout << res2 << std::endl;
		Debug::Print2D<std::string>()(res3, false);
		Debug::Print2D<std::string>()(res4, false);
	}
};
/*
WordLadder BFS, BFS_2Dir, FindAllBFS, FindAllBFS_2Dir for "hit", "cog" from [hot, dot, dog, lot, log, cog]
5
5
[rY][cX]
Row#0	= hit, hot, dot, dog, cog
Row#1	= hit, hot, lot, log, cog

[rY][cX]
Row#0	= hit, hot, dot, dog, cog
Row#1	= hit, hot, lot, log, cog

WordLadder BFS, BFS_2Dir, FindAllBFS, FindAllBFS_2Dir for "red", "tax" from [ted, tex, red, tax, tad, den, rex, pee]
4
4
[rY][cX]
Row#0	= red, ted, tad, tax
Row#1	= red, ted, tex, tax
Row#2	= red, rex, tex, tax

[rY][cX]
Row#0	= red, ted, tad, tax
Row#1	= red, ted, tex, tax
Row#2	= red, rex, tex, tax
*/

/*
Leetcode: Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".
Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.
For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.
Also, there is a given gene "bank", which records all the valid gene mutations.
A gene must be in the bank to make it a valid gene string.
Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.
Note:
Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.
Example 1:
start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]
return: 1
Example 2:
start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]
return: 2
Example 3:
start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]
return: 3
*/
class MinGeneticMutation
{
public:
	MinGeneticMutation() {}

	int CountMinMutation_BFS(const std::string & start, const std::string & end, const std::vector<std::string> & bank)
	{
		std::unordered_set<std::string> dict(bank.begin(), bank.end());
		std::unordered_set<std::string> visit;
		visit.insert(start);
		int dist = 0;
		std::queue<std::string> que;
		que.push(start);
		while (!que.empty())
		{
			int count = que.size();
			while (count-->0)
			{
				std::string s = que.front();
				que.pop();
				if (s == end)
					return dist;
				std::string c = "ACGT";
				int N = s.size();
				for (int i = 0; i < N; ++i)
				{
					int cc = s[i];
					for (int j = 0; j < 4; ++j)
					{
						if (c[j] == cc) continue;
						s[i] = c[j];
						if (dict.count(s) && !visit.count(s))
						{
							que.push(s);
							visit.insert(s);
						}
					}
					s[i] = cc;
				}
			}
			++dist;
		}
		return -1;
	}
	int CountMinMutation_BFS_2Dir(const std::string & start, const std::string & end, const std::vector<std::string> & bank)
	{
		std::unordered_set<std::string> dict(bank.begin(), bank.end());
		if (!dict.count(end)) return -1;
		std::unordered_set<std::string> fwd;
		std::unordered_set<std::string> bwd;
		std::unordered_set<std::string> visit;
		fwd.insert(start);
		bwd.insert(end);
		visit.insert(start);
		visit.insert(end);
		int dist = 0;
		while (!fwd.empty() && !bwd.empty())
		{
			if (bwd.size() < fwd.size())
				std::swap(fwd, bwd);
			std::unordered_set<std::string> nxtLevel;
			for (auto & cur : fwd)
			{
				for (int i = 0; i < (int)cur.size(); ++i)
				{
					std::string nxt = cur;
					std::string set = "ACGT";
					for (int j = 0; j < 4; ++j)
					{
						if (set[j] != cur[i])
						{
							nxt[i] = set[j];
							if (bwd.count(nxt))
								return dist + 1;
							if (dict.count(nxt) && !visit.count(nxt))
							{
								visit.insert(nxt);
								nxtLevel.insert(nxt);
							}
						}
					}
				}
			}
			++dist;
			std::swap(fwd, nxtLevel);
		}
		return -1;
	}

	void Test(const std::string & start, const std::string & end, const std::vector<std::string> & bank)
	{
		int res1 = CountMinMutation_BFS(start, end, bank);
		int res2 = CountMinMutation_BFS_2Dir(start, end, bank);
		std::cout << "MinGeneticMutation CountMinMutation BFS, BFS_2Dir for \"" << start << "\", \"" << end << "\" from [" << Debug::ToStr1D<std::string>()(bank) << "]: " << res1 << "," << res2 << std::endl;
	}
};
/*
MinGeneticMutation CountMinMutation BFS, BFS_2Dir for "AAAAACCC", "AACCCCCC" from [AAAACCCC, AAACCCCC, AACCCCCC]: 3,3
*/
#endif