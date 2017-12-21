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
	int FindShortestLadderLengthBFS(std::string start, std::string end, std::unordered_set<std::string> dict)//dict will be modified
	{
		std::string dictBefore = Debug::ToStr1D<std::string>()(dict);
		std::cout << "WordLadder FindShortestLadderLengthBFS for \"" << start << "\", \"" << end << "\" from \"" << dictBefore << "\": ";

		std::queue<std::pair<std::string, int>> que;//key: ladder word, value: length
		que.push({ start, 1 });
		while (!que.empty())
		{
			int curLevelCount = que.size();
			for (int k = 0; k < curLevelCount; ++k)
			{
				std::string curWord = que.front().first;
				int curLen = que.front().second;
				que.pop();
				if (curWord == end)//found shortest path
				{
					std::cout << curLen << std::endl;
					return curLen;
				}

				for (int i = 0; i < (int)curWord.size(); ++i)
				{
					std::string nxtWord = curWord;
					for (char c = 'a'; c <= 'z'; ++c)
					{
						if (c == curWord[i])
							continue;
						nxtWord[i] = c;

						if (dict.find(nxtWord) != dict.end() || nxtWord == end)
						{
							if (nxtWord != end)
								dict.erase(nxtWord);
							//since we just need to find the FIRST reached shortest path without enumerating ALL, mark this neighbor of cur level node visited regardless of other latter cur level nodes !!!

							que.push({ nxtWord, curLen + 1 });
						}
					}
				}
			}
			
		}

		std::cout << 0 << std::endl;
		return 0;
	}

	//2. enumerate all diff shortest paths instead of enumerating all diff result configurations with a shortest path
	std::vector<std::vector<std::string>> FindAllShortestLaddersBFS(std::string start, std::string end, std::unordered_set<std::string> dict)//better
	{
		std::string dictBefore = Debug::ToStr1D<std::string>()(dict);

		std::vector<std::vector<std::string>> res;
		std::queue<std::string> que;
		que.push(start);
		std::queue<std::vector<std::string>> pathQue;
		pathQue.push(std::vector<std::string>(1, start));

		int maxLen = INT_MAX;
		while (!que.empty())
		{
			int curLevelCount = que.size();
			bool reached = false;
			std::vector<std::string> levelVisit;
			for (int k = 0; k < curLevelCount; ++k)
			{
				std::string curWord = que.front();
				que.pop();
				std::vector<std::string> curPath = pathQue.front();
				pathQue.pop();

				int curLen = curPath.size();
				if (curLen > maxLen)//redundant
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

						if (dict.find(nxtWord) != dict.end() || nxtWord == end)
						{
							//cannot mark this neighbor visited here to find ALL diff shortest paths: bc this neighbor of cur level node might be a neighbor of other latter cur level nodes !!!
							if (nxtWord != end)
								levelVisit.push_back(nxtWord);

							curPath.push_back(nxtWord);
							que.push(nxtWord);
							pathQue.push(curPath);
							curPath.pop_back();
						}
					}
				}
			}
			if (reached)
				break;

			//now mark all neighbors of all cur level nodes as visited after all neighbors of all cur level nodes have been visited
			//this is to ensure ALL diff shortest paths can be enumerated
			for (auto & s : levelVisit)
				dict.erase(s);
		}
		
		std::cout << "WordLadder FindAllShortestLaddersBFS for \"" << start << "\", \"" << end << "\" from \"" << dictBefore << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

	std::vector<std::vector<std::string>> FindAllShortestLaddersDFS(std::string start, std::string end, std::unordered_set<std::string> dict)//Time Limit Exceeded
	{
		std::string dictBefore = Debug::ToStr1D<std::string>()(dict);

		std::map<int, std::vector<std::vector<std::string>>> allValid;
		std::unordered_map<std::string, int> visit;
		std::vector<std::string> path;
		path.push_back(start);
		int minDepth = INT_MAX;
		recur(start, end, minDepth, path, visit, allValid, dict);
		std::vector<std::vector<std::string>> res;
		if (!allValid.empty())
			for (auto & p : allValid.begin()->second)
				res.push_back(p);
		for (auto & p : allValid)
			Debug::Print2D<std::string>()(p.second, false);
		std::cout << "WordLadder FindAllShortestLaddersDFS for \"" << start << "\", \"" << end << "\" from \"" << dictBefore << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
	void recur(std::string cur, const std::string & end, int & minDepth, std::vector<std::string> & path, std::unordered_map<std::string, int> & visit, std::map<int, std::vector<std::vector<std::string>>> & allValid, const std::unordered_set<std::string> & dict)
	{
		int curLen = path.size();
		if (curLen > minDepth)
			return;
		if (cur == end)
		{
			minDepth = std::min(minDepth, curLen);
			allValid[curLen].push_back(path);
			return;
		}
		else if (curLen == minDepth)
			return;

		for (int i = 0; i < (int)cur.size(); ++i)
		{
			std::string nxt = cur;
			for (char c = 'a'; c <= 'z'; ++c)
			{
				if (c == cur[i]) continue;
				nxt[i] = c;
				if (nxt == end || (dict.find(nxt) != dict.end() && (visit.find(nxt) == visit.end() || visit[nxt] >= curLen + 1)))
				{
					if (nxt != end)
						visit[nxt] = curLen + 1;
					path.push_back(nxt);
					recur(nxt, end, minDepth, path, visit, allValid, dict);
					path.pop_back();
				}
			}
		}
	}








	//faster but harder to memo
	std::vector<std::vector<std::string> > FindAllShortestLadders(std::string start, std::string end, std::unordered_set<std::string> dict)
	{
		std::cout << "WordLadder FindAllShortestLadders for \"" << start << "\", \"" << end << "\" from \"" << Debug::ToStr1D<std::string>()(dict) << "\": " << std::endl;

		//key: next 1-letter-diff-word in dict or "end"
		//value: a vector of all the prev 1-letter-diff-word in dict
		std::unordered_map<std::string, std::vector<std::string> > ladderWordMap;

		std::vector<std::vector<std::string> > res;
		std::unordered_set<std::string> currLadderWords;//all 1-letter-diff-words in curr level
		std::unordered_set<std::string> prevLadderWords;//all 1-letter-diff-words in prev level

		//add start to prevLadderWords
		prevLadderWords.insert(start);

		//BFS build the ladderWordMap
		while (true)
		{
			//1. remove all prevLadderWords from dict
			for (std::unordered_set<std::string>::const_iterator itr = prevLadderWords.begin(); itr != prevLadderWords.end(); ++itr)
				dict.erase(*itr);
			//std::cout << "dict: " << Debug::ToStr1D<std::string>()(dict) << std::endl;

			//2. enumerate all possible 1-letter-diff-prevLadderWords from dict, and insert in ladderWordMap and curLadderWords
			for (std::unordered_set<std::string>::const_iterator itr = prevLadderWords.begin(); itr != prevLadderWords.end(); ++itr)
			{
				//double-for-loops to try all 1-letter-diff-words
				for (int j = 0; j < (int)itr->size(); ++j)
				{
					std::string nextLadderWord = *itr;
					for (char c = 'a'; c <= 'z'; ++c)
					{
						if (itr->at(j) == c)//self => skip
							continue;
						nextLadderWord[j] = c;//1-letter-diff-word

						if (dict.find(nextLadderWord) == dict.end() && //can't find 1-letter-diff-word in dict
							nextLadderWord != end)//can't find 1-letter-diff-word in "end"
							continue;

						//now this nextLadderWord is in dict or is "end"
						ladderWordMap[nextLadderWord].push_back(*itr);//put it and all its prev 1-letter-diff-words in map

						//put this nextLadderWord in currLadderWords for next while loop
						std::pair<std::unordered_set<std::string>::iterator, bool> r = 
							currLadderWords.insert(nextLadderWord);
						//std::cout << next << "," << r.second << "," << curr.size() << "." << Debug::ToStr1D<std::string>()(curr) << std::endl;
					}
				}
			}

			//3. if found NO 1-letter-diff-prevLadderWords for next while loop, can't form any ladder toward end, stop and return
			if (currLadderWords.size() == 0)
			{
				std::cout << "No Word Ladders Were Found!" << std::endl;
				return res;
			}

			//4. if found "end" is a 1-letter-diff-prevLadderWords, ladder is completed, stop while loop
			if (currLadderWords.find(end) != currLadderWords.end())
				break;

			//5. update buffer
			prevLadderWords = currLadderWords;
			currLadderWords.clear();
		}

		this->printLadderWordMap(ladderWordMap);

		std::vector<std::string> path;
		this->getPathRecur_DFS_FromBack(end, start, ladderWordMap, path, res);//recursively build the all word ladders map

		std::cout << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}

private:
	//start: a prev word in start's prev word vector in ladderWordMap
	//end: the target beginning of the ladder
	void getPathRecur_DFS_FromBack(std::string & start, std::string & end, std::unordered_map<std::string, std::vector<std::string> > & map
		, std::vector<std::string> & path, std::vector<std::vector<std::string> > & res)
	{
		path.push_back(start);//form the path vector backward

		if (start == end)
		{
			res.push_back(std::vector<std::string>(path.rbegin(), path.rend()));
		}
		else
		{
			for (std::vector<std::string>::iterator pre = map[start].begin(); pre != map[start].end(); ++pre)
			{
				this->getPathRecur_DFS_FromBack(*pre, end, map, path, res);
			}
		}
		path.pop_back();
	}

	void printLadderWordMap(const std::unordered_map<std::string, std::vector<std::string> > & map)
	{
		std::ostringstream oss;
		for (std::unordered_map<std::string, std::vector<std::string> >::const_iterator i = map.begin(); i != map.end(); ++i)
		{
			oss << i->first << ": ";
			for (std::vector<std::string>::const_iterator j = i->second.begin(); j != i->second.end(); ++j)
			{
				oss << *j;
				if (j != i->second.end() - 1)
					oss << ",";
				else
					oss << ".";
			}
			oss << std::endl;
		}
		std::cout << "Ladder Word Map:" << std::endl << oss.str();
	}
};
/*
WordLadder FindShortestLadderLengthBFS for "hit", "cog" from "hot, dot, lot, dog, log": 5
WordLadder FindAllShortestLaddersBFS for "hit", "cog" from "hot, dot, lot, dog, log": [hit,hot,dot,dog,cog], [hit,hot,lot,log,cog]
[rY][cX]
Row#0	= hit, hot, dot, dog, cog
Row#1	= hit, hot, lot, log, cog

[rY][cX]
Row#0	= hit, hot, dot, lot, log, cog

WordLadder FindAllShortestLaddersDFS for "hit", "cog" from "hot, dot, lot, dog, log": [hit,hot,dot,dog,cog], [hit,hot,lot,log,cog]
WordLadder FindAllShortestLadders for "hit", "cog" from "hot, dot, lot, dog, log":
Ladder Word Map:
hot: hit.
cog: dog,log.
lot: hot.
dot: hot.
log: lot.
dog: dot.
[hit,hot,dot,dog,cog], [hit,hot,lot,log,cog]
WordLadder FindShortestLadderLengthBFS for "red", "tax" from "ted, tax, tex, tad, red, den, rex, pee": 4
WordLadder FindAllShortestLaddersBFS for "red", "tax" from "ted, tax, tex, tad, red, den, rex, pee": [red,ted,tad,tax], [red,ted,tex,tax], [red,rex,tex,tax]
[rY][cX]
Row#0	= red, ted, tad, tax
Row#1	= red, ted, tex, tax
Row#2	= red, rex, tex, tax

[rY][cX]
Row#0	= red, ted, red, rex, tex, tax

WordLadder FindAllShortestLaddersDFS for "red", "tax" from "ted, tax, tex, tad, red, den, rex, pee": [red,ted,tad,tax], [red,ted,tex,tax], [red,rex,tex,tax]
WordLadder FindAllShortestLadders for "red", "tax" from "ted, tax, tex, tad, red, den, rex, pee":
Ladder Word Map:
tax: tad,tex.
ted: red.
rex: red.
tex: ted,rex.
tad: ted.
[red,ted,tad,tax], [red,ted,tex,tax], [red,rex,tex,tax]
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

	int CountMinMutation_BFS(std::string start, std::string end, std::vector<std::string> & bank)
	{
		std::unordered_set<std::string> dict;
		for (const auto & s : bank)
			dict.insert(s);
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
				{
					std::cout << "MinGeneticMutation CountMinMutation_BFS for start=\"" << start << "\", end=\"" << end << "\", from \"" << Debug::ToStr1D<std::string>()(bank) << "\": " << dist << std::endl;
					return dist;
				}
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

		std::cout << "MinGeneticMutation CountMinMutation_BFS for start=\"" << start << "\", end=\"" << end << "\", from \"" << Debug::ToStr1D<std::string>()(bank) << "\": " << -1 << std::endl;
		return -1;
	}
};
/*
MinGeneticMutation CountMinMutation_BFS for start="AAAAACCC", end="AACCCCCC", from "AAAACCCC, AAACCCCC, AACCCCCC": 3
*/
#endif