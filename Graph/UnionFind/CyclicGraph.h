#ifndef CYCLIC_GRAPH_H
#define CYCLIC_GRAPH_H
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
#include "../GraphTransform.h"
#include "UnionFindGraphComponent.h"
/*
Leetcode: Graph Valid Tree

1. use Union-Find
http://www.geeksforgeeks.org/union-find/
UnionFind: O(E*V) time, O(V) space
OptimizedUnionFind: O(E*logV) time, O(V) space

2. use DFS to detect back edge
http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
http://www.geeksforgeeks.org/detect-cycle-undirected-graph/
DFS w/ adjMatrix: O(V^2) time, O(V) space

See also Bellman-Ford single source shortest path algorithm which is able to detect negative weight cycle.
ShortestPathInGraph.h
*/
class CyclicGraph
{
public:
	CyclicGraph(){}
	~CyclicGraph(){}
	//1. use union find
	bool Undirected_UnionFind_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();

		//1. transform adjMatrix to an edge list
		std::vector<std::pair<int, std::pair<int, int> > > edgeList = GraphTransform().Undirected_AdjacencyMatrixToEdgeList(adjMatrix);
		int E = edgeList.size();

		std::vector<int> parentIndex(N, -1);//-1: the underlying vertex is a root of a separate component, otherwise: the parent vertex of the underlying vertex
		bool res = false;

		//2. for each edge, find the root vertices of subsets where its 2 end vertices belong to
		for (int i = 0; i < E; ++i)
		{
			//2.1 if the root vertices are identical, they belong to a same subset, which detects a cycle on the 2 end vertices
			int root1 = UnionFindGraphComponent().FindRecur(parentIndex, edgeList[i].second.first);
			int root2 = UnionFindGraphComponent().FindRecur(parentIndex, edgeList[i].second.second);
			if (root1 == root2)
			{
				res = true;
				break;
			}
			//2.2 otherwise, join the 2 subsets
			UnionFindGraphComponent().Union(parentIndex, root1, root2);
			std::cout << Debug::ToStr1D<int>()(parentIndex) << std::endl;
		}
		std::cout << "CyclicGraph Undirected_UnionFind_AdjacencyMatrix for \"" << Debug::ToStr1D<int>()(edgeList) << "\": " << res << std::endl;
		return res;
	}
	bool Undirected_UnionFindOptimized_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<std::pair<int, std::pair<int, int> > > edgeList = GraphTransform().Undirected_AdjacencyMatrixToEdgeList(adjMatrix);
		int E = edgeList.size();
		std::vector<std::pair<int, int> > parentRankPairs(N, std::make_pair(-1, 0));
		for (int i = 0; i < N; ++i)
			parentRankPairs[i].first = i;
		bool res = false;
		for (int i = 0; i < E; ++i)
		{
			int root1 = UnionFindGraphComponent().FindRecur(parentRankPairs, edgeList[i].second.first);
			int root2 = UnionFindGraphComponent().FindRecur(parentRankPairs, edgeList[i].second.second);
			if (root1 == root2)
			{
				res = true;
				break;
			}
			UnionFindGraphComponent().Union(parentRankPairs, root1, root2);
			std::cout << Debug::ToStr1D<int>()(parentRankPairs) << std::endl;
		}
		std::cout << "CyclicGraph Undirected_UnionFindOptimized_AdjacencyMatrix for \"" << Debug::ToStr1D<int>()(edgeList) << "\": " << res << std::endl;
		return res;
	}
	//2. use DFS to detect back edge
	bool Undirected_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		bool res = false;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				if (this->Undirected_DFS_AdjacencyMatrix_Recur(adjMatrix, -1, i, visitCount, visitIndex))
				{
					res = true;
					break;
				}
		}
		std::cout << "CyclicGraph Undirected_DFS_AdjacencyMatrix: " << res << std::endl;
		return res;
	}
private:
	bool Undirected_DFS_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int parent, int v, int & visitCount, std::vector<int> & visitIndex)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					if (this->Undirected_DFS_AdjacencyMatrix_Recur(adjMatrix, v, i, visitCount, visitIndex))
						return true;
				}
				else if (i != parent)
				{
					//(v, i) is a back edge or a down edge in an undirected graph
					std::cout << "Found Back/Down Edge: " << v << "->" << i << std::endl;
					return true;
				}
			}
		}
		return false;
	}

public:
	bool Directed_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> completionIndex(N, -1);
		int completionCount = -1;
		bool res = false;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				if (this->Directed_DFS_AdjacencyMatrix_Recur(adjMatrix, -1, i, visitCount, visitIndex, completionCount, completionIndex))
				{
					res = true;
					break;
				}
		}
		std::cout << "CyclicGraph Directed_DFS_AdjacencyMatrix: " << res << std::endl;
		return res;
	}
private:
	bool Directed_DFS_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int parent, int v,
		int & visitCount, std::vector<int> & visitIndex, int & completionCount, std::vector<int> & completionIndex)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0)
			{
				if (visitIndex[i] == -1)
				{
					if (this->Directed_DFS_AdjacencyMatrix_Recur(adjMatrix, v, i, visitCount, visitIndex, completionCount, completionIndex))
						return true;
				}
				else
				{
					if (completionIndex[i] == -1)
					{
						//(v, i) is a back edge in a directed graph
						std::cout << "Found Back Edge: " << v << "->" << i << std::endl;
						return true;
					}
				}
			}
		}
		completionIndex[v] = ++completionCount;
		return false;
	}

public:
	//Leetcode: Graph valid tree
	bool validTree(int n, std::vector<std::pair<int, int>> & edges)
	{
		std::vector<int> rootIdx(n);
		for (int i = 0; i < n; ++i)
			rootIdx[i] = i;
		for (auto & e : edges)
		{
			int root1 = UnionFindGraphComponent().FindIterate(rootIdx, e.first);
			int root2 = UnionFindGraphComponent().FindIterate(rootIdx, e.second);
			if (root1 == root2)
				return false;
			rootIdx[root1] = root2;
		}
		return edges.size() == n - 1;
	}
};
/*
		1   0---3---5
		|       | \ |
		2       4   6
[rY][cX]
Row#0	= 0, 0, 0, 1, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 1, 1, 1
Row#4	= 0, 0, 0, 1, 0, 0, 0
Row#5	= 0, 0, 0, 1, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 1, 0

3, -1, -1, -1, -1, -1, -1
3, 2, -1, -1, -1, -1, -1
3, 2, -1, 4, -1, -1, -1
3, 2, -1, 4, 5, -1, -1
3, 2, -1, 4, 5, 6, -1
CyclicGraph Undirected_UnionFind_AdjacencyMatrix for "[1,(0,3)], [1,(1,2)], [1,(3,4)], [1,(3,5)], [1,(3,6)], [1,(5,6)]": 1
[rY][cX]
Row#0	= 0, 0, 0, 1, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 1, 1, 1
Row#4	= 0, 0, 0, 1, 0, 0, 0
Row#5	= 0, 0, 0, 1, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 1, 0

[0,1], [1,0], [2,0], [0,0], [4,0], [5,0], [6,0]
[0,1], [1,1], [1,0], [0,0], [4,0], [5,0], [6,0]
[0,1], [1,1], [1,0], [0,0], [0,0], [5,0], [6,0]
[0,1], [1,1], [1,0], [0,0], [0,0], [0,0], [6,0]
[0,1], [1,1], [1,0], [0,0], [0,0], [0,0], [0,0]
CyclicGraph Undirected_UnionFindOptimized_AdjacencyMatrix for "[1,(0,3)], [1,(1,2)], [1,(3,4)], [1,(3,5)], [1,(3,6)], [1,(5,6)]": 1
[rY][cX]
Row#0	= 0, 0, 0, 1, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0
Row#2	= 0, 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 1, 1, 1
Row#4	= 0, 0, 0, 1, 0, 0, 0
Row#5	= 0, 0, 0, 1, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 1, 0

Found Back/Down Edge: 6->3
CyclicGraph Undirected_DFS_AdjacencyMatrix: 1

		5---->0<----4
		| \         |
		|     \     |
		v         v v
		2---->3---->1
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 1, 0, 0, 0, 0
Row#4	= 1, 1, 0, 0, 0, 0
Row#5	= 1, 1, 1, 0, 0, 0

CyclicGraph Directed_DFS_AdjacencyMatrix: 0
*/
#endif