/*MEMO*/
#ifndef BICONNECTED_GRAPH_H
#define BICONNECTED_GRAPH_H
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
Elements of programming interview, Graph: Test degrees of connectedness, variant
http://www.geeksforgeeks.org/biconnectivity-in-a-graph/
An undirected graph is called biconnected if there are two vertex-disjoint paths between any two vertices.
In a biconnected graph, there is a simple cycle through any two vertices.
A connected graph is biconnected if it is connected and doesn't have any articulation point.
So we need to check two things in a graph:
1. The graph is connected
2. There is no articulation point in graph

see also CutVerticesInGraph.h, BridgesInGraph.h, StronglyConnectedComponents.h
*/
class BiconnectedGraph
{
public:
	BiconnectedGraph(){}
	~BiconnectedGraph(){}

	//DFS w/ adjacency matrix: O(V^2)
	//DFS w/ adjacency list: O(V+E)
	bool DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> cutVertices;
		std::vector<int> lowestReachable(N, N);
		this->dFS_UndirectedAdjacencyMatrix(adjMatrix, -1, 0, visitCount, visitIndex, cutVertices, lowestReachable);
		//std::cout << Debug::ToStr1D<int>()(cutVertices) << std::endl;
		bool isConnected = (visitCount == N - 1) ? true : false;
		bool noArticulationPoints = (cutVertices.size() == 0) ? true : false;
		bool isBiconnected = isConnected && noArticulationPoints;
		std::cout << "BiconnectedGraph DFS_UndirectedAdjacencyMatrix isConnected: " << isConnected << ", noArticulationPoints: " << noArticulationPoints << " => isBiconnected: " << isBiconnected << std::endl;
		return isBiconnected;
	}
private:
	void dFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int from, int v,
		int & visitCount, std::vector<int> & visitIndex,
		std::vector<int> & cutVertices, std::vector<int> & lowestReachable)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		lowestReachable[v] = visitIndex[v];
		int dfsPathCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i != v && adjMatrix[v][i] != 0)
			{
				if (visitIndex[i] == -1)
				{
					++dfsPathCount;
					this->dFS_UndirectedAdjacencyMatrix(adjMatrix, v, i, visitCount, visitIndex, cutVertices, lowestReachable);

					//after recursion, lowestReachable[i] might have a lower reachable vertex than lowestReachable[v]
					lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[i]);

					//2 cases for v as an articulation point:
					//1. v's DFS parent is root and v has at least two DFS paths
					//2. v's DFS parent isn't root and one of v's DFS paths doesn't have a back edge to any DFS ancestor of v
					if ((from == -1 && dfsPathCount > 1) ||
						(from != -1 && lowestReachable[i] >= visitIndex[v]))
						cutVertices.push_back(v);
				}
				else if (i != from)//for undirected graph, skip v's DFS parent vertex
					lowestReachable[v] = std::min(lowestReachable[v], visitIndex[i]);
				//i has been visited already, check if i could be a lower reachable DFS ancestor of existing lowestReachable[v]
			}
		}
	}
};
/*
		1---0---3   5   6   8
		| /     |       |   |
		2       4       7   9---10
BiconnectedGraph DFS_UndirectedAdjacencyMatrix isConnected: 0, noArticulationPoints: 0 => isBiconnected: 0

		   -----    3----4----6
		 /       \ /        /
		0----1----2      /
		           \  /
		            5----7
BiconnectedGraph DFS_UndirectedAdjacencyMatrix isConnected: 1, noArticulationPoints: 0 => isBiconnected: 0
*/
#endif