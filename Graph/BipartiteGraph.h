#ifndef BIPARTITE_GRAPH_H
#define BIPARTITE_GRAPH_H
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
Leetcode: Is Graph Bipartite?
Aka 2-colorable problem
Elements of programming interview, Graph: Making wired connection
Design an algorithm that takes a set of pins and a set of wires connecting pairs of pins
, and determines if it is possible to place some pins on the left half of a PCB
, and the remainder on the right half
, such that each wire is between left and right halves.
Return such a division, if one exists.
http://www.geeksforgeeks.org/bipartite-graph/
A bipartite graph is a graph whose vertices can be divided into two independent sets, U and V 
such that every edge (u, v) either connects a vertex from U to V or a vertex from V to U.
In otherwords, for every edge (u, v), either u belongs to U and v to V, or u belongs to V and v to U.
There is no edge that connects vertices of same set.

A bipartite graph is possible if the graph coloring is possible using two colors such that vertices in a set are colored with the same color.
Note that it is possible to color a cycle graph with "even cycle" using two colors.

���i�P����
Given an acyclic undirected graph, determine if all the vertices in the graph can be labeled with 2 colors.
The colors of adjacent vertices cannot be the same.

Adjacency Matrix: O(V^2)
Adjacency List: O(V+E)
*/
class BipartiteGraph
{
public:
	BipartiteGraph(){}
	~BipartiteGraph(){}

	bool BFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> color(N, 0);//0: not labeled, 1/-1: labeled
		bool twoColorable = true;
		for (int i = 0; i < N; ++i)
		{
			if (color[i] == 0)//if vertex i hasn't been labeled
			{
				if (!this->bFS_UndirectedAdjacencyMatrix(adjMatrix, i, color, 1))
				{
					twoColorable = false;
					break;
				}
			}
		}
		std::cout << "BipartiteGraph BFS_UndirectedAdjacencyMatrix: " << twoColorable << std::endl;
		return twoColorable;
 	}
	bool bFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, std::vector<int> & color, int c)
	{
		int N = adjMatrix.size();
		color[v] = c;//label vertex v with an arbitrary color
		std::queue<int> que;
		que.push(v);
		while (!que.empty())
		{
			v = que.front();
			que.pop();
			c = color[v];

			//enumerate all adj vertices
			for (int i = 0; i < N; ++i)
			{
				if (i != v && adjMatrix[v][i] != 0)
				{
					if (color[i] == c)//found a neighbor vertex i that has same color
						return false;
					if (color[i] == 0)//if the neighbor vertex i hasn't been labeled
					{
						color[i] = -c;//label the neighbor vertex i with v's opposite color
						que.push(i);
					}
				}
			}
		}
		return true;
	}

	bool DFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> color(N, 0);//0: not labeled, 1/-1: labeled
		bool twoColorable = true;
		for (int i = 0; i < N; ++i)
		{
			if (color[i] == 0)
			{
				if (!this->dFS_UndirectedAdjacencyMatrix(adjMatrix, i, color, 1))
				{
					twoColorable = false;
					break;
				}
			}
		}
		std::cout << "BipartiteGraph DFS_UndirectedAdjacencyMatrix: " << twoColorable << std::endl;
		return twoColorable;
	}
	bool dFS_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, std::vector<int> & color, int c)
	{
		int N = adjMatrix.size();
		color[v] = c;
		//enumerate all adj vertices
		for (int i = 0; i < N; ++i)
		{
			if (i != v && adjMatrix[v][i] != 0)
			{
				if (color[i] == c)
					return false;
				if (color[i] == 0)
				{
					if (!this->dFS_UndirectedAdjacencyMatrix(adjMatrix, i, color, -c))
						return false;
				}
			}
		}
		return true;
	}
};

/*
Leetcode: Possible Bipartition
Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.
Each person may dislike some other people, and they should not go into the same group.
Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.
Return true if and only if it is possible to split everyone into two groups in this way.
Example 1:
Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4], group2 [2,3]
Example 2:
Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Example 3:
Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false
 */
class PossibleBipartition
{
public:
	PossibleBipartition(){}

	bool Solve(int N, std::vector<std::vector<int>> & dislikes)
	{
		std::vector<std::unordered_set<int>> adjList(N+1, std::unordered_set<int>());
		for (auto & p : dislikes)
		{
			adjList[p[0]].insert(p[1]);
			adjList[p[1]].insert(p[0]);
		}
		std::vector<int> color(N+1, 0);
		for (int i = 1; i <= N; ++i)
		{
			if (color[i] != 0) continue;
			if (!DFS(adjList, i, color, 1))
				return false;
		}
		return true;
	}
private:
	bool BFS(const std::vector<std::unordered_set<int>> & adjList, int cur, std::vector<int> & color, int c)
	{
		color[cur] = c;
		std::queue<int> que;
		que.push(cur);
		while (!que.empty())
		{
			cur = que.front(); que.pop();
			c = color[cur];
			for (int nxt : adjList[cur])
			{
				if (color[nxt] == c)
					return false;
				if (color[nxt] == 0)
				{
					color[nxt] = -c;
					que.push(nxt);
				}
			}
		}
		return true;
	}
	bool DFS(const std::vector<std::unordered_set<int>> & adjList, int cur, std::vector<int> & color, int c)
	{
		color[cur] = c;
		for (int nxt : adjList[cur])
		{
			if (color[nxt] == c)
				return false;
			if (color[nxt] == 0)
			{
				if (!DFS(adjList, nxt, color, -c))
					return false;
			}
		}
		return true;
	}
};
#endif