/*MEMO*/
#ifndef BRIDGES_IN_GRAPH_H
#define BRIDGES_IN_GRAPH_H
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
http://www.geeksforgeeks.org/bridge-in-a-graph/
An edge in an undirected connected graph is a bridge iff removing it disconnects the graph.
For an undirected disconnected graph, a bridge is an edge removing which increasing number of connected components.

Leetcode: Critical connections in a network
There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network
 where connections[i] = [a, b] represents a connection between servers a and b.
Any server can reach any other server directly or indirectly through the network.
A critical connection is a connection that, if removed, will make some server unable to reach some other server.
Return all critical connections in the network in any order.

See also CutVerticesInGraph.h, BiconnectedGraph.h, StronglyConnectedComponents.h
*/
class BridgesInGraph
{
public:
	BridgesInGraph(){}
	~BridgesInGraph(){}

	//DFS w/ adjacency matrix: O(V^2)
	//DFS w/ adjacency list: O(V+E)
	bool Valid_DFS_ConnectedUndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v1, int v2)
	{
		int N = adjMatrix.size();
		if (v1 < 0 || v1 >= N || v2 < 0 || v2 >= N)
			return false;
		if (adjMatrix[v1][v2] == 0 || adjMatrix[v2][v1] == 0)
			return false;

		//1. count connected vertices from v1
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		this->dFS_UndirectedAdjacencyMatrix(adjMatrix, v1, visitCount, visitIndex);
		int reachableVCountWEdge = visitCount + 1;

		//2. remove edge (v1, v2)
		std::vector<std::vector<int> > removedAdjMatrix(adjMatrix);
		removedAdjMatrix[v1][v2] = 0;//remove edge (v1, v2)
		removedAdjMatrix[v2][v1] = 0;//remove edge (v2, v1)

		//3. count connected vertices from v1 again
		std::vector<int>(N, -1).swap(visitIndex);
		visitCount = -1;
		this->dFS_UndirectedAdjacencyMatrix(removedAdjMatrix, v1, visitCount, visitIndex);
		int reachableVCountWoEdge = visitCount + 1;

		//4. compare reachable vertices
		bool isBridge = reachableVCountWEdge > reachableVCountWoEdge ? true : false;
		//std::cout << "BridgesInGraph Valid_DFS_ConnectedUndirectedAdjacencyMatrix for \"(" << v1 << "," << v2 << ")\": " << isBridge << std::endl;
		return isBridge;
	}
private:
	void dFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v,
		int & visitCount, std::vector<int> & visitIndex)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (i != v && adjMatrix[v][i] != 0)
				if (visitIndex[i] == -1)
					this->dFS_UndirectedAdjacencyMatrix(adjMatrix, i, visitCount, visitIndex);
		}
	}


public:
	//DFS w/ adjacency matrix: O(E*V^2)
	//DFS w/ adjacency list: O(E*(V+E))
	std::vector<std::pair<int, int> > FindAll_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::pair<int, int> > res;
		int diagonalNxtRight = 0;
		for (int i = 0; i < N; ++i)
		{
			++diagonalNxtRight;
			for (int j = diagonalNxtRight; j < N; ++j)
			{
				if (adjMatrix[i][j] != 0)
				{
					if (this->Valid_DFS_ConnectedUndirectedAdjacencyMatrix(adjMatrix, i, j))
						res.push_back(std::make_pair(i, j));
				}
			}
		}
		std::cout << "BridgesInGraph FindAll_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//w/ adjacency matrix: O(V^2)
	//w/ adjacency list: O(V+E)
	std::vector<std::pair<int, int> > FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::pair<int, int> > bridges;
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> lowestReachable(N, N);
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				this->findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(adjMatrix, -1, i, visitCount, visitIndex, bridges, lowestReachable);
		}
		std::cout << "BridgesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(bridges) << std::endl;
		return bridges;
	}
private:
	void findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int from, int v,
		int & visitCount, std::vector<int> & visitIndex,
		std::vector<std::pair<int, int> > & bridges, std::vector<int> & lowestReachable)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		lowestReachable[v] = visitIndex[v];
		int dfsChildCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (i != v && adjMatrix[v][i] != 0)
			{
				if (visitIndex[i] == -1)
				{
					++dfsChildCount;
					this->findAll_Tarjan_DFS_UndirectedAdjacencyMatrix(adjMatrix, v, i, visitCount, visitIndex, bridges, lowestReachable);

					//after recursion, lowestReachable[i] might have a lower reachable vertex than lowestReachable[v]
					lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[i]);

					//1 case for edge (v, i) as bridge:
					//if i's DFS children don't have any back edge to to any DFS ancestor of v
					if (lowestReachable[i] > visitIndex[v])
						bridges.push_back(std::make_pair(v, i));
				}
				else if (i != from)//for undirected graph, skip v's DFS parent vertex
					lowestReachable[v] = std::min(lowestReachable[v], visitIndex[i]);
				//i has been visited already, check if i could be a lower reachable DFS ancestor of existing lowestReachable[v]
			}
		}
	}
    //Leetcode: Critical Connections in a Network
    std::vector<std::vector<int>> FindAll_Tarjan_DFS_UndirectedAdjList(int N, std::vector<std::vector<int>> & connections)
    {
        std::vector<std::vector<int>> adjList(N, std::vector<int>());
        for (auto & v : connections)
        {
            adjList[v[0]].push_back(v[1]);
            adjList[v[1]].push_back(v[0]);
        }
        std::vector<std::vector<int>> bridges;
        std::vector<int> visitIndex(N, -1);
        int visitCount = -1;
        std::vector<int> lowestReachable(N, N);
        for (int i = 0; i < N; ++i)
        {
            if (visitIndex[i] == -1)
                findAll_Tarjan_DFS_UndirectedAdjList(adjList, -1, i, visitCount, visitIndex, bridges, lowestReachable);
        }
        std::cout << "BridgesInGraph FindAll_Tarjan_DFS_UndirectedAdjList: " << Debug::ToStr1D<int>()(bridges) << std::endl;
        return bridges;
    }
private:
    void findAll_Tarjan_DFS_UndirectedAdjList(const std::vector<std::vector<int>> & adjList, int from, int v, int & visitCount, std::vector<int> & visitIndex, std::vector<std::vector<int>> & bridges, std::vector<int> & lowestReachable)
    {
        int N = adjList.size();
        visitIndex[v] = ++visitCount;
        lowestReachable[v] = visitIndex[v];
        int dfsChildCount = 0;
        for (auto & i : adjList[v])
        {
            if (visitIndex[i] == -1)
            {
                ++dfsChildCount;
                findAll_Tarjan_DFS_UndirectedAdjList(adjList, v, i, visitCount, visitIndex, bridges, lowestReachable);

                //after recursion, lowestReachable[i] might have a lower reachable vertex than lowestReachable[v]
                lowestReachable[v] = std::min(lowestReachable[v], lowestReachable[i]);

                //1 case for edge (v, i) as bridge:
                //if i's DFS children don't have any back edge to to any DFS ancestor of v
                if (lowestReachable[i] > visitIndex[v])
                    bridges.push_back({v, i});
            }
            else if (i != from)//for undirected graph, skip v's DFS parent vertex
                lowestReachable[v] = std::min(lowestReachable[v], visitIndex[i]);
            //i has been visited already, check if i could be a lower reachable DFS ancestor of existing lowestReachable[v]
        }
    }
};
/*
		1---0---3   5   6   8
		| /     |       |   |
		2       4       7   9---10
BridgesInGraph FindAll_UndirectedAdjacencyMatrix: [0,3], [3,4], [6,7], [8,9], [9,10]
BridgesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: [3,4], [0,3], [6,7], [9,10], [8,9]

		   -----    3----4----6
		 /       \ /        /
		0----1----2      /
		           \  /
		            5----7
BridgesInGraph FindAll_UndirectedAdjacencyMatrix: [5,7]
BridgesInGraph FindAll_Tarjan_DFS_UndirectedAdjacencyMatrix: [5,7]
*/
#endif