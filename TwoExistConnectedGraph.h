#ifndef TWO_EXIST_CONNECTED_GRAPH_H
#define TWO_EXIST_CONNECTED_GRAPH_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Graph: Test degrees of connectedness
A connected graph is one in which for any two vertices u and v there exists a path from u to v.
2-ForAll-Connected graph: A connected graph remains connected if ANY single edge is removed.
2-Exist-Connected graph: A connected graph remains connected if THERE EXISTS an edge that can be removed.

2-Exist-Connected graph: 1. the graph is connected, 2. the graph has at least a cycle (at least a back edge)
If there is a back/down edge exists in the graph, there must be a cycle.

See also CyclicGraph.h
O(V) time
*/
class TwoExistConnectedGraph
{
public:
	TwoExistConnectedGraph(){}
	~TwoExistConnectedGraph(){}

	//suppose adjMatrix is a connected undirected graph
	bool Undirected_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		bool hasCycle = this->Undirected_DFS_AdjacencyMatrix_Recur(adjMatrix, -1, 0, visitCount, visitIndex);
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TwoExistConnectedGraph Undirected_DFS_AdjacencyMatrix: " << hasCycle << std::endl;
		return hasCycle;
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
};
/*
		            3----4----6
		           /
		0----1----2
		           \
				    5----7
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 1, 0, 1, 0, 0, 0, 0, 0
Row#2	= 0, 1, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0
Row#5	= 0, 0, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 0, 1, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

TwoExistConnectedGraph Undirected_DFS_AdjacencyMatrix: 0

		   -----    3----4----6
		 /       \ /        /
		0----1----2      /
		           \  /
		            5----7
Found Back/Down Edge: 2->0
[rY][cX]
Row#0	= 0, 1, 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0
Row#5	= 0, 0, 1, 0, 0, 0, 1, 1
Row#6	= 0, 0, 0, 0, 1, 1, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

TwoExistConnectedGraph Undirected_DFS_AdjacencyMatrix: 1
*/
#endif