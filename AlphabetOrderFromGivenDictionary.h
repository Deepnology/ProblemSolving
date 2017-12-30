#ifndef ALPHABET_ORDER_FROM_GIVEN_DICTIONARY_H
#define ALPHABET_ORDER_FROM_GIVEN_DICTIONARY_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include "Debug.h"
#include "TopologicalSortDAG.h"
/*
Leetcode: Alien Dictionary
Google, Amazon
http://www.careercup.com/question?id=19114716
Given a dictionary of a new language where it has same characters as English alphabets, i.e., a-z, but different alphabet order of characters.
Given a list of character pairs sorted with the order of the alphabets of the new language.
Find out the order of the alphabets of the new language.

1. find out as many character pairs with alphabetical order as possible
2. the minimum number of distinct character pairs required is 0 + 1 + 2 + 3 + ... + 25
   same characters cannot form a pair
3. based on these character pairs, construct a directed graph where vertices represent characters, directed edges represent alphabetical order between two characters
   the constructed directed graph should be a DAG without cycles
4. perform topological sort of the DAG
   since we have 26 vertices and 0 + 1 + 2 + ... + 25 distinct vertices pairs, the topological ordering of the DAG must be unique, which produces the alphabets of all 26 characters

   Take 5 characters for example:
   Given c->e, c->d, d->e, b->c, b->e, b->d, a->c, a->e, a->d, a->b
   DAG adj Matrix:
		c e d b a
	c   0 1 1 0 0
	e   0 0 0 0 0
	d   0 1 0 0 0
	b   1 1 1 0 0
	a   1 1 1 1 0
	---------------------
	|                   |
	v                   |
	b-------->d         |
	| \     ^ | ^       |
	|    X    |    \    |
	v /     v v       \ |
	c-------->e<--------a
	^                   |
	|                   |
	---------------------
	The correct alphabet order for the given alphabet pairs: a->b->c->d->e
*/
class AlphabetOrderFromGivenDictionary
{
public:
	AlphabetOrderFromGivenDictionary(){}
	~AlphabetOrderFromGivenDictionary(){}

	std::vector<int> SolveFor5Chars(const std::vector<std::pair<int, int> > & alphabetPairs)
	{
		int distinctPairCount = 0;
		int requiredDistinctPairCount = 0;

		//1. count minimum required distinct pairs
		for (int i = 0; i < 5; ++i)
			requiredDistinctPairCount += i;//0+1+2+3+4

		//2. construct DAG and count actual distinct pairs
		std::vector<std::vector<int> > DAG(5, std::vector<int>(5, 0));
		int N = alphabetPairs.size();
		for (int i = 0; i < N; ++i)
		{
			if (DAG[alphabetPairs[i].first][alphabetPairs[i].second] == 0)
			{
				DAG[alphabetPairs[i].first][alphabetPairs[i].second] = 1;
				++distinctPairCount;
				if (distinctPairCount == requiredDistinctPairCount)
					break;
			}
		}
		std::vector<int> res;

		//3. early return for insufficient distinct pairs
		if (distinctPairCount < requiredDistinctPairCount)
		{
			std::cout << "AlphabetOrderFromGivenDictionary 5Chars for \"" << Debug::ToStr1D<int>()(alphabetPairs) << "\": insufficient alphabet pairs to get unique topological ordering of DAG" << std::endl;
			return res;
		}

		//4. compute topological sort order
		res = TopologicalSortDAG().DFS_AdjacencyMatrix(DAG);

		//5. verify if the topological sort order is unique
		UniqueTopologicalOrdering().CheckMissedEdges(res, DAG);
		std::cout << "AlphabetOrderFromGivenDictionary 5Chars for \"" << Debug::ToStr1D<int>()(alphabetPairs) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//Leetcode: Alien Dictionary, given a word array where words are sorted lexicographically by the rules of this new language
	std::string alienOrderDFS(const std::vector<std::string> & words)
	{
		//1. construct DAG
		std::unordered_map<int, std::unordered_set<int>> DAG;
		int N = words.size();
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < (int)words[i].size(); ++j)
				if (DAG.count(words[i][j] - 'a') == 0)
					DAG.insert({ words[i][j] - 'a',std::unordered_set<int>() });
		for (int i = 0; i < N - 1; ++i)
		{
			int len = std::min(words[i].size(), words[i + 1].size());
			for (int j = 0; j < len; ++j)
			{
				if (words[i][j] != words[i + 1][j])
				{
					DAG[words[i][j] - 'a'].insert(words[i + 1][j] - 'a');
					break;//!!!!!
				}
			}
		}

		std::vector<int> stk;
		std::unordered_set<int> visit;
		std::unordered_set<int> completion;
		for (const auto & p : DAG)
			if (visit.count(p.first) == 0)
				if (recur(DAG, p.first, visit, completion, stk))
					return "";//found cycle in DAG
		std::reverse(stk.begin(), stk.end());

		std::string res;
		N = stk.size();
		for (int i = 0; i < N; ++i)
			res += (stk[i] + 'a');

		Debug::Print2D<int>()(DAG);
		std::cout << "AlphabetOrderFromGivenDictionary alienOrderDFS for \"" << Debug::ToStr1D<std::string>()(words) << "\": " << res << std::endl;
		return res;
	}
private:
	bool recur(std::unordered_map<int, std::unordered_set<int>> & DAG, int v, std::unordered_set<int> & visit, std::unordered_set<int> & completion, std::vector<int> & stk)
	{
		visit.insert(v);
		for (auto & nxt : DAG[v])//to use DAG[v]: DAG can't be passed by const ref; must make sure all vertices already be added in DAG!!!
			if (visit.count(nxt) == 0)
			{
				if (recur(DAG, nxt, visit, completion, stk))
					return true;
			}
			else
			{
				if (completion.count(nxt) == 0)
					return true;//back edge: found cycle
			}
		completion.insert(v);
		stk.push_back(v);
		return false;
	}

public:
	std::string alienOrderBFS(const std::vector<std::string> & words)
	{
		std::unordered_map<int, std::unordered_set<int>> DAG;
		int N = words.size();
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < (int)words[i].size(); ++j)
				if (DAG.count(words[i][j] - 'a') == 0)
					DAG.insert({ words[i][j] - 'a',std::unordered_set<int>() });
		for (int i = 0; i < N - 1; ++i)
		{
			int len = std::min(words[i].size(), words[i + 1].size());
			for (int j = 0; j < len; ++j)
			{
				if (words[i][j] != words[i + 1][j])
				{
					DAG[words[i][j] - 'a'].insert(words[i + 1][j] - 'a');
					break;//!!!!!
				}
			}
		}

		//topological sort BFS using inDegree[]
		std::unordered_map<int, int> inDegree;
		for (const auto & p : DAG)
		{
			if (inDegree.count(p.first) == 0)
				inDegree[p.first] = 0;
			for (const auto & v : p.second)
				++inDegree[v];
		}

		std::vector<int> resV;
		std::queue<int> que;
		for (const auto & p : inDegree)
			if (p.second == 0)
				que.push(p.first);
		while (!que.empty())
		{
			int cur = que.front(); que.pop();
			resV.push_back(cur);
			for (const auto & nxt : DAG[cur])
			{
				if (inDegree[nxt] > 0)
				{
					--inDegree[nxt];
					if (inDegree[nxt] == 0)
						que.push(nxt);
				}
			}
		}

		for (const auto & p : inDegree)
			if (p.second > 0) return "";

		std::string res;
		N = resV.size();
		for (int i = 0; i < N; ++i)
			res += (resV[i] + 'a');

		Debug::Print2D<int>()(DAG);
		std::cout << "AlphabetOrderFromGivenDictionary alienOrderBFS for \"" << Debug::ToStr1D<std::string>()(words) << "\": " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 0, 1, 1, 1, 1
Row#1	= 0, 0, 1, 1, 1
Row#2	= 0, 0, 0, 1, 1
Row#3	= 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0

TopologicalSortDAG DFS_AdjacencyMatrix: 0, 1, 2, 3, 4
UniqueTopologicalOrdering CheckMissedEdges for "0, 1, 2, 3, 4":  =>
The DAG adjMatrix has Unique Topological Ordering (has Hamiltonian path that visit each vertex exactly once)
AlphabetOrderFromGivenDictionary 5Chars for "[2,4], [2,3], [3,4], [1,2], [1,4], [1,3], [0,2], [0,4], [0,3], [0,1]": 0, 1, 2, 3, 4
Row#0	= 22: 4
Row#1	= 17: 19
Row#2	= 19: 5
Row#3	= 5:
Row#4	= 4: 17

AlphabetOrderFromGivenDictionary alienOrderDFS for "wrt, wrf, er, ett, rftt": wertf
Row#0	= 22: 4
Row#1	= 17: 19
Row#2	= 19: 5
Row#3	= 5:
Row#4	= 4: 17

AlphabetOrderFromGivenDictionary alienOrderBFS for "wrt, wrf, er, ett, rftt": wertf
*/
#endif