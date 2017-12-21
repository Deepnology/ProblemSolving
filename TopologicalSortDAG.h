#ifndef TOPOLOGICAL_SORT_DAG_H
#define TOPOLOGICAL_SORT_DAG_H
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
/*
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module7/module7.html
http://www.geeksforgeeks.org/topological-sorting/
http://algs4.cs.princeton.edu/42directed/
Topological Sort:
Input must be DAG (Directed Acyclic Graph: a directed graph without a cycle)
Topological sort order should be the reverse order of the vertices' completion order of DFS
We can use a stack to store vertices in completion order
When popping out the stack, it will be the reverse order of the completion order

There can be more than one topological sorting for a graph
The first vertex in topological sorting is always a vertex with in-degree as 0
O(V+E)

Hamiltonian path in DAG:
Given a DAG, design a linear time algorithm to determine whether there is a directed path that visits each VERTEX exactly once.
We can compute a topological sort and check if there is an edge between each consecutive pair of vertices in the topological order.

Unique Topological Ordering:
Determine whether a directed graph has a unique topological ordering.
A directed graph has a unique topological ordering iff there is a directed edge between each pair of consecutive vertices in the topological order (i.e., the directed graph has a Hamiltonian path).
If the DAG has multiple topological orderings, then a second topological order can be obtained by swapping a pair of consecutive vertices where no directed edge between them.
*/
class TopologicalSortDAG
{
public:
	TopologicalSortDAG(){}
	~TopologicalSortDAG(){}
	std::vector<int> DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & DAGadjMatrix)
	{
		int N = DAGadjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::stack<int> stk;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				this->DFS_AdjacencyMatrix_Recur(DAGadjMatrix, i, visitCount, visitIndex, stk);
			}
		}
		
		std::vector<int> topoOrdering;
		while (!stk.empty())
		{
			topoOrdering.push_back(stk.top());
			stk.pop();
		}

		Debug::Print2D<int>()(DAGadjMatrix, false);
		std::cout << "TopologicalSortDAG DFS_AdjacencyMatrix: " << Debug::ToStr1D<int>()(topoOrdering) << std::endl;
		return topoOrdering;
	}
private:
	void DFS_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & DAGadjMatrix, int v, int & visitCount, std::vector<int> & visitIndex, std::stack<int> & stk)
	{
		int N = DAGadjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (DAGadjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					this->DFS_AdjacencyMatrix_Recur(DAGadjMatrix, i, visitCount, visitIndex, stk);
				}
			}
		}
		stk.push(v);
	}
};

class UniqueTopologicalOrdering
{
public:
	UniqueTopologicalOrdering(){}
	~UniqueTopologicalOrdering(){}

	bool CheckMissedEdges(const std::vector<int> & topoOrdering, const std::vector<std::vector<int> > & DAGadjMatrix)
	{
		int N = topoOrdering.size();
		std::vector<std::pair<int, int> > missedEdges;
		for (int i = 0; i < N - 1; ++i)
		{
			if (DAGadjMatrix[topoOrdering[i]][topoOrdering[i + 1]] == 0)
				missedEdges.push_back(std::make_pair(topoOrdering[i], topoOrdering[i + 1]));
		}

		std::cout << "UniqueTopologicalOrdering CheckMissedEdges for \"" << Debug::ToStr1D<int>()(topoOrdering) << "\": " << Debug::ToStr1D<int>()(missedEdges) << " =>" << std::endl;
		if (missedEdges.empty())
			std::cout << "The DAG adjMatrix has Unique Topological Ordering (has Hamiltonian path that visit each vertex exactly once)" << std::endl;
		else
			std::cout << "The DAG adjMatrix has No Unique Topological Ordering (has No Hamiltonian path that visit each vertex exactly once)" << std::endl;
		return missedEdges.empty() ? true : false;
	}
};
/*
		5---->0<----4
		|           |
		|           |
		v           v
		2---->3---->1
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 1, 0, 0, 0, 0
Row#4	= 1, 1, 0, 0, 0, 0
Row#5	= 1, 0, 1, 0, 0, 0

TopologicalSortDAG DFS_AdjacencyMatrix: 5, 4, 2, 3, 1, 0
UniqueTopologicalOrdering CheckMissedEdges for "5, 4, 2, 3, 1, 0": [5,4], [4,2], [1,0] =>
The DAG adjMatrix has No Unique Topological Ordering (has No Hamiltonian path that visit each vertex exactly once)

		---------------------
		|                   |
		v                   |
		1-------->3         |
		|         |         |
		|         |         |
		v         v         |
		2-------->4<--------0
[rY][cX]
Row#0	= 0, 1, 0, 0, 1
Row#1	= 0, 0, 1, 1, 1
Row#2	= 0, 0, 0, 0, 1
Row#3	= 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0

TopologicalSortDAG DFS_AdjacencyMatrix: 0, 1, 3, 2, 4
UniqueTopologicalOrdering CheckMissedEdges for "0, 1, 3, 2, 4": [3,2] =>
The DAG adjMatrix has No Unique Topological Ordering (has No Hamiltonian path that visit each vertex exactly once)
*/
#endif