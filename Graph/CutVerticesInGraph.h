/*MEMO*/
#ifndef CUT_VERTICES_IN_GRAPH_H
#define CUT_VERTICES_IN_GRAPH_H
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
Elements of programming interview, Graph: Test degrees of connectedness, variant
http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
A vertex in an undirected connected graph is an articulation point (cut vertex) iff removing it (and edges through it) disconnects the graph.
For an undirected disconnected graph, an articulation point is a vertex removing which increases number of connected components.

See also BridgesInGraph.h, BiconnectedGraph.h, StronglyConnectedComponents.h
*/
class CutVerticesInGraph
{
public:
	CutVerticesInGraph(){}
	~CutVerticesInGraph(){}

	//DFS w/ adjacency matrix: O(V^2)
	//DFS w/ adjacency list: O(V+E)
	bool Valid_DFS_ConnectedUndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v)
	{
		int N = adjMatrix.size();
		int adjVertex;//just any adj vertex of v
		for (adjVertex = 0; adjVertex < N; ++adjVertex)
			if (adjVertex != v && adjMatrix[v][adjVertex] != 0)
				break;
		if (adjVertex == N)//v has no adj vertices
		{
			//std::cout << "CutVerticesInGraph Valid_DFS_ConnectedUndirectedAdjacencyMatrix for \"" << v << "\": " << false << std::endl;
			return false;
		}

		//1. count connected vertices from adjVertex
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		this->dFS_ConnectedUndirectedAdjacencyMatrix(adjMatrix, adjVertex, visitCount, visitIndex);
		int reachableVCount = visitCount + 1 - 1;//must exclude v

		//2. remove all v's edges
		std::vector<std::vector<int> > removedAdjMatrix(adjMatrix);
		for (int i = 0; i < N; ++i)
		{
			removedAdjMatrix[v][i] = 0;
			removedAdjMatrix[i][v] = 0;
		}
		//Debug::Print2D<int>()(removedAdjMatrix, false);

		//3. count connected vertices from adjVertex again
		std::vector<int>(N, -1).swap(visitIndex);
		visitCount = -1;
		this->dFS_ConnectedUndirectedAdjacencyMatrix(removedAdjMatrix, adjVertex, visitCount, visitIndex);
		int reachableVCount2 = visitCount + 1;//already excluded v
		
		//4. compare connected vertices
		bool isCutVertex = reachableVCount > reachableVCount2 ? true : false;
		//std::cout << "CutVerticesInGraph Valid_DFS_ConnectedUndirectedAdjacencyMatrix for \"" << v << "\": " << isCutVertex << std::endl;
		return isCutVertex;
	}
private:
	void dFS_ConnectedUndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (i != v && adjMatrix[v][i] != 0)
				if (visitIndex[i] == -1)
					this->dFS_ConnectedUndirectedAdjacencyMatrix(adjMatrix, i, visitCount, visitIndex);
		}
	}
public:
	//DFS w/ adjacency matrix: O(V*V^2)
	//DFS w/ adjacency list: O(V*(V+E))
	std::vector<int> FindAll_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> res;
		for (int i = 0; i < N; ++i)
		{
			if (this->Valid_DFS_ConnectedUndirectedAdjacencyMatrix(adjMatrix, i))
				res.push_back(i);
		}
		std::cout << "CutVerticesInGraph FindAll_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//w/ adjacency matrix: O(V^2)
	//w/ adjacency list: O(V+E)
	std::vector<int> FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> cutVertices(N, 0);
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> lowestReachable(N, N);
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				this->findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(adjMatrix, -1, i, visitCount, visitIndex, cutVertices, lowestReachable);
		}
		std::cout << "CutVerticesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(cutVertices) << std::endl;
		return cutVertices;
	}
private:
	void findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int from, int v, 
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
					this->findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(adjMatrix, v, i, visitCount, visitIndex, cutVertices, lowestReachable);

					//after recursion, lowestReachable[i] might have a lower reachable vertex than lowestReachable[v]
					lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[i]);

					//2 cases for v as an articulation point:
					//1. v's DFS parent is root and v has at least two DFS paths
					//2. v's DFS parent isn't root and one of v's DFS paths doesn't have a back edge to any DFS ancestor of v
					if ((from == -1 && dfsPathCount > 1) ||
						(from != -1 && lowestReachable[i] >= visitIndex[v]))
						cutVertices[v] = 1;
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
CutVerticesInGraph FindAll_UndirectedAdjacencyMatrix: 0, 3, 9
CutVerticesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0

		   -----    3----4----6
		 /       \ /        /
		0----1----2      /
		           \  /
		            5----7
CutVerticesInGraph FindAll_UndirectedAdjacencyMatrix: 2, 5
CutVerticesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: 0, 0, 1, 0, 0, 1, 0, 0
*/
#endif