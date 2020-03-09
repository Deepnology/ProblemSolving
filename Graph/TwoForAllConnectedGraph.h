/*MEMO*/
#ifndef TWO_FOR_ALL_CONNECTED_GRAPH_H
#define TWO_FOR_ALL_CONNECTED_GRAPH_H
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


2-ForAll-Connected graph: 1. the graph must be connected, 2. all vertices must be on cycles (no articulation points)
For a vertex to be on a cycle, its lowestReachable vertex must be smaller than its visitIndex.
For all vertices to be on cycles, all vertices' lowestReachable vertex must be smaller than their visitIndicies.
A vertex's lowestReachable is the vertex that has a lower visit index and that can be reached through one of its DFS decendants.
If a vertex's lowestReachable is smaller than its visitIndex, then it must be on a cycle
, because there exists a DFS path from the vertex through one of its descendants to an ancestor of that vertex.

DFS: O(V+E) time
*/
class TwoForAllConnectedGraph
{
public:
	TwoForAllConnectedGraph(){}
	~TwoForAllConnectedGraph(){}

	//suppose adjMatrix is a connected undirected graph
	bool Undirected_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		std::vector<int> lowestReachable(N, INT_MAX);
		int visitCount = -1;
		bool allVerticesOnCycles = this->Undirected_DFS_AdjacencyMatrix(adjMatrix, -1, 0, visitCount, visitIndex, lowestReachable);
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TwoForAllConnectedGraph Undirected_DFS_AdjacencyMatrix: " << allVerticesOnCycles << std::endl;
		return allVerticesOnCycles;
	}
private:
	bool Undirected_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int from, int v, int & visitCount, std::vector<int> & visitIndex, std::vector<int> & lowestReachable)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)//forward edge
				{
					if (!this->Undirected_DFS_AdjacencyMatrix(adjMatrix, v, i, visitCount, visitIndex, lowestReachable))
						return false;//early return from a DFS path through neighbor i that has no cycle

					//now the DFS path through neighbor i does have a cycle
					//check if neighbor i's DFS path can reach an ancestor of v
					//i's DFS visit index must be greater than v, so we don't need to consider it
					lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[i]);
				}
				else if (i != from)//back edge
				{
					//neighbor i isn't v's DFS parent and has already been visited
					//which means i must have a lower DFS visit index than v
					lowestReachable[v] = std::min(lowestReachable[v], std::min(lowestReachable[i], visitIndex[i]));
				}
			}
		}

		return (from == -1 || //v is root
			lowestReachable[v] < visitIndex[v]);//v lies on a cycle (there exists a path from v through one of its descendants to an ancestor or v)
	}
};
/*
		      2-----3-----------
		          /   \         |
		        /       \       |
		4-----10----9-----8     1
		|     | \   |   /     /
		|     |   \ | /     /
		5-----6-----7-----0
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1
Row#7	= 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1
Row#10	= 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0

TwoForAllConnectedGraph Undirected_DFS_AdjacencyMatrix: 0

		      2-----3-----------
		      |   /   \         |
		      | /       \       |
		4-----10----9-----8     1
		|     | \   |   /     /
		|     |   \ | /     /
		5-----6-----7-----0
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1
Row#3	= 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1
Row#7	= 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1
Row#10	= 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0

TwoForAllConnectedGraph Undirected_DFS_AdjacencyMatrix: 1
*/
#endif