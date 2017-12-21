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

∞ˆæiªP¡Î¡Â
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
#endif