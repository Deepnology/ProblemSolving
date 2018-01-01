#ifndef UNION_FIND_GRAPH_COMPONENT_H
#define UNION_FIND_GRAPH_COMPONENT_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module8/module8.html
http://www.geeksforgeeks.org/union-find/
http://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
on-line graph component problem:
1. first, number of vertices is given to algorithm
2. then, algorithm receives one pair edge at a time
Algorithm must output currently known components at each step

see also CyclicGraph.h, MinSpanningTree.h, LowestCommonAncestorUnionFind.h

parentIndex array:
the parent vertex of each underlying vertex
initially, all parent vertices in the array are set to -1
(if the parent vertex of the underlying vertex is -1, the underlying vertex is a root of a subset)
Find(v): 
return the root vertex of the subset that v belongs to
Union(v1, v2):
find the root vertices of the subsets that v1 and v2 belongs to, respectively, from parentIndex array
then set one root vertex as the parent vertex of the other root vertex

parentRankPairs array:
initially, all parent vertices in the array are set to its index, and all ranks in the array are set to 0

see also NumberOfIslandsInMatrix.h
*/
class UnionFindGraphComponent
{
public:
	UnionFindGraphComponent(){}
	~UnionFindGraphComponent(){}

	//1. naive: O(n) time (parentIndex are init to be all -1s)
	int FindRecur(const std::vector<int> & parentIndex, int v)
	{
		if (parentIndex[v] == -1)
			return v;
		return this->FindRecur(parentIndex, parentIndex[v]);
	}
	void Union(std::vector<int> & parentIndex, int v1, int v2)
	{
		int root1 = this->FindRecur(parentIndex, v1);
		int root2 = this->FindRecur(parentIndex, v2);
		parentIndex[root1] = root2;
	}

	//2. rank and path compression: O(logn) time (parentRankPairs are init to be {index, 0}s.)
	int FindRecur(std::vector<std::pair<int, int>> & parentRankPairs, int v)//first: parent, second: rank(height of underlying node)
	{
		if (parentRankPairs[v].first != v)//means v has a parent node (v is not a root)
			parentRankPairs[v].first = this->FindRecur(parentRankPairs, parentRankPairs[v].first);//update v's parent node to be the root node (path compression)
		return parentRankPairs[v].first;
	}
	void Union(std::vector<std::pair<int, int>> & parentRankPairs, int v1, int v2)
	{
		int root1 = this->FindRecur(parentRankPairs, v1);
		int root2 = this->FindRecur(parentRankPairs, v2);

		if (parentRankPairs[root1].second < parentRankPairs[root2].second)
			parentRankPairs[root1].first = root2;//connect the root w/ smaller rank(height) to be a child of the root w/ bigger rank(height)
		else if (parentRankPairs[root1].second > parentRankPairs[root2].second)
			parentRankPairs[root2].first = root1;//connect the root w/ smaller rank(height) to be a child of the root w/ bigger rank(height)
		else//same rank(height)
		{
			parentRankPairs[root2].first = root1;
			++parentRankPairs[root1].second;
		}
	}
	
	//3. simple iterative version path comopression: O(logn) time (rootIndex are init to be {index}s.)
	//union-find is specially suited for input is edge list !!!
	int FindIterate(std::vector<int> & rootIndex, int idx)
	{
		while (rootIndex[idx] != idx)
		{
			rootIndex[idx] = rootIndex[rootIndex[idx]];//only one line added
			idx = rootIndex[idx];
		}
		return idx;
	}
	void UnionIterate(std::vector<int> & rootIndex, int v1, int v2)
	{
		int root1 = FindIterate(rootIndex, v1);
		int root2 = FindIterate(rootIndex, v2);
		if (root1 != root2)
		{
			rootIndex[root1] = root2;
			//after union: num of total components decrement 1 !!!
		}
		//else: root1==root2, edge[v1,v2] doesn't connect 2 diff components, found a cycle in undirected graph !!!
	}


};

/*
Leetcode: Friend Circle (compute connected components in undirected graph)
There are N students in a class.
Some of them are friends, while some are not.
Their friendship is transitive in nature.
For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C.
And we defined a friend circle is a group of students who are direct or indirect friends.
Given a N*N matrix M representing the friend relationship between students in the class.
If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not.
And you have to output the total number of friend circles among all the students.
*/
class FriendCircle
{
public:
	FriendCircle() {}

	int DFS(const std::vector<std::vector<int>> & adjM)
	{
		int N = adjM.size();
		if (N == 0) return 0;
		std::vector<int> visit(N, 0);
		int count = 0;
		for (int i = 0; i < N; ++i)
			if (!visit[i])
			{
				recur(adjM, i, visit);
				++count;
			}
		Debug::Print2D<int>()(adjM, false);
		std::cout << "FriendCircle DFS for the above adjM: " << count << std::endl;
		return count;
	}
private:
	void recur(const std::vector<std::vector<int>> & adjM, int cur, std::vector<int> & visit)
	{
		int N = adjM.size();
		visit[cur] = 1;
		for (int i = 0; i < N; ++i)
		{
			if (i != cur && adjM[cur][i] && !visit[i])
			{
				recur(adjM, i, visit);
			}
		}
	}

public:
	int UnionFind(const std::vector<std::vector<int>> & adjM)
	{
		int N = adjM.size();
		if (N == 0) return 0;
		std::vector<int> rootIdx(N);
		for (int i = 0; i < N; ++i) rootIdx[i] = i;
		int count = N;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i + 1; j < N; ++j)
			{
				if (adjM[i][j])
				{
					int root1 = UnionFindGraphComponent().FindIterate(rootIdx, i);
					int root2 = UnionFindGraphComponent().FindIterate(rootIdx, j);
					if (root1 != root2)
					{
						rootIdx[root1] = root2;
						--count;
					}
				}
			}
		}
		Debug::Print2D<int>()(adjM, false);
		std::cout << "FriendCircle UnionFind for the above adjM: " << count << std::endl;
		return count;
	}
};
/*
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

FriendCircle DFS for the above adjM: 2
[rY][cX]
Row#0	= 1, 1, 0
Row#1	= 1, 1, 0
Row#2	= 0, 0, 1

FriendCircle UnionFind for the above adjM: 2
*/
#endif