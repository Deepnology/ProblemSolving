#ifndef UNIQUE_SEQUENCE_RECONSTRUCTABLE_H
#define UNIQUE_SEQUENCE_RECONSTRUCTABLE_H
#include "Debug.h"
/*
Leetcode: Sequence Reconstruction
Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs.
The org sequence is a permutation of the integers from 1 to n, with 1 <= n <= 10^4.
Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it).
Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

Example 1:
Input:
org: [1,2,3], seqs: [[1,2],[1,3]]
Output:
false
Explanation:
[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:
Input:
org: [1,2,3], seqs: [[1,2]]
Output:
false
Explanation:
The reconstructed sequence can only be [1,2].
Example 3:
Input:
org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]
Output:
true
Explanation:
The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:
Input:
org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]
Output:
true

each sequence in seqs is a path in DAG, use these paths to build the DAG,
find topological sort, check if there exists missed edges in topological sort and if the last node in topological sort has 0 out degree
see also ConnectAllStrInChain.h
*/
class UniqueSequenceReconstructable
{

public:
	UniqueSequenceReconstructable() {}
	void IsUniquelyReconstructable(const std::vector<int> & org, const std::vector<std::vector<int>> & seqs)
	{
		bool dfs = this->IsUniquelyReconstructableDFS(org, seqs);
		bool bfs = this->IsUniquelyReconstructableBFS(org, seqs);
		Debug::Print2D<int>()(seqs, false);
		std::cout << "UniqueSequenceReconstructable for \"" << Debug::ToStr1D<int>()(org) << "\" from above seqs: DFS=" << dfs << ", BFS=" << bfs << std::endl;
	}

	bool IsUniquelyReconstructableDFS(const std::vector<int> & org, const std::vector<std::vector<int>> & seqs)
	{
		if (seqs.empty()) return false;
		std::unordered_map<int, std::unordered_set<int>> DAG;
		for (auto & p : seqs)
		{
			if (p.empty()) continue;
			int N = p.size();
			for (int i = 0; i < N - 1; ++i)
				DAG[p[i]].insert(p[i + 1]);

			if (DAG.count(p[N - 1]) == 0)
				DAG.insert({ p[N - 1],std::unordered_set<int>() });
		}
		Debug::Print2D<int>()(DAG);

		std::vector<int> stk;
		std::unordered_set<int> visit;
		std::unordered_set<int> completion;
		for (auto & p : DAG)
		if (visit.count(p.first) == 0)
			if (recur(DAG, p.first, visit, completion, stk))//found cycle in DAG
				return false;
		std::reverse(stk.begin(), stk.end());

		int N = org.size();
		if (N != stk.size()) return false;

		//need to compare one by one !!!!
		for (int i = 0; i < N; ++i)
		    if (org[i] != stk[i]) return false;

		for (int i = 0; i < N - 1; ++i)
		{
			if (DAG[stk[i]].count(stk[i + 1]) == 0)//check missed edge in topological sort
				return false;
		}
		if (!DAG[stk[N - 1]].empty())//check last node in topological sort must have 0 out degree
			return false;
		return true;
	}
private:
	bool recur(std::unordered_map<int, std::unordered_set<int>> & DAG, int v, std::unordered_set<int> & visit, std::unordered_set<int> & completion, std::vector<int> & stk)
	{
		visit.insert(v);
		for (auto & nxt : DAG[v])
			if (visit.count(nxt) == 0)
			{
				if (recur(DAG, nxt, visit, completion, stk))
					return true;
			}
			else
			{
				if (completion.count(nxt) == 0)
					return true;
			}
		completion.insert(v);
		stk.push_back(v);
		return false;
	}

public:
	bool IsUniquelyReconstructableBFS(const std::vector<int> & org, const std::vector<std::vector<int>> & seqs)
	{
		if (seqs.empty()) return false;
		std::unordered_map<int, std::unordered_set<int>> DAG;
		for (auto & p : seqs)
		{
			if (p.empty()) continue;
			int N = p.size();
			for (int i = 0; i < N - 1; ++i)
				DAG[p[i]].insert(p[i + 1]);

			if (DAG.count(p[N - 1]) == 0)
				DAG.insert({ p[N - 1],std::unordered_set<int>() });
		}
		Debug::Print2D<int>()(DAG);

		//topological sort BFS using inDegree[]
		std::unordered_map<int, int> inDegree;
		for (const auto & p : DAG)
		{
			if (inDegree.count(p.first) == 0)
				inDegree[p.first] = 0;
			for (const auto & v : p.second)
				++inDegree[v];
		}
		std::vector<int> res;
		std::queue<int> que;
		for (const auto & p : inDegree)
			if (p.second == 0)
				que.push(p.first);
		while (!que.empty())
		{
			int cur = que.front(); que.pop();
			res.push_back(cur);
			for (const auto & nxt : DAG[cur])
			{
			    --inDegree[nxt];
			    if (inDegree[nxt] == 0)
			        que.push(nxt);
			}
		}
		for (const auto & p : inDegree)
			if (p.second > 0) return false;

		int N = org.size();
		if (N != res.size()) return false;

		//need to compare one by one !!!!
		for (int i = 0; i < N; ++i)
		    if (org[i] != res[i]) return false;

		for (int i = 0; i < N - 1; ++i)
		{
			if (DAG[res[i]].count(res[i + 1]) == 0)//check missed edge in topological sort
				return false;
		}
		if (!DAG[res[N - 1]].empty())//check last node in topological sort must have 0 out degree
			return false;
		return true;
	}
};
/*
Row#0	= 1: 2, 3
Row#1	= 2: 3
Row#2	= 3:

Row#0	= 1: 2, 3
Row#1	= 2: 3
Row#2	= 3:

[rY][cX]
Row#0	= 1, 2
Row#1	= 1, 3
Row#2	= 2, 3

UniqueSequenceReconstructable for "1, 2, 3" from above seqs: DFS=1, BFS=1
*/
#endif
