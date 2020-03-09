#ifndef TRIANGLES_IN_GRAPH_H
#define TRIANGLES_IN_GRAPH_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=5988741646647296
Given an undirected graph with corresponding edges
Find the number of possible triangles

BFS & Adjacency Matrix: O(n*d^2) time, where n is number of vertices, d is average vertex degree => O(n^3) time
*/
class TrianglesInGraph
{
public:
	TrianglesInGraph(){}
	~TrianglesInGraph(){}
	struct UndirectedGraphNode
	{
		UndirectedGraphNode(int x) : label(x) {}
		int label;
		std::vector<UndirectedGraphNode *> neighbors;
	};

	int Count_BFS(UndirectedGraphNode * node)
	{
		int count = 0;
		std::unordered_set<UndirectedGraphNode *> visited;
		std::queue<UndirectedGraphNode *> queue;
		queue.push(node);
		while (!queue.empty())
		{
			node = queue.front();
			queue.pop();

			//now visit the node
			//for each vertex in graph, check if its any two adjacent vertices have edge
			int M = node->neighbors.size();
			for (int i = 0; i < M - 1; ++i)
			{
				UndirectedGraphNode * adj1 = node->neighbors[i];
				for (int j = i + 1; j < M; ++j)
				{
					UndirectedGraphNode * adj2 = node->neighbors[j];

					/*check if adj2 is one vertex of adj1's neighbors*/
					int N = adj1->neighbors.size();
					for (int k = 0; k < N; ++k)
					{
						if (adj1->neighbors[k] == adj2)
						{
							++count;
							break;
						}
					}
				}
			}

			for (auto nebr : node->neighbors)
			{
				if (visited.count(nebr) == 0)//nebr of node that hasn't been visited
				{
					visited.insert(nebr);//mark nebr visited
					queue.push(nebr);//push nebr to queue
				}
			}
		}
		count /= 3;
		std::cout << "TrianglesInGraph Count_BFS: " << count << std::endl;
		return count;
	}

	int Count_AdjacencyList(const std::vector<std::vector<int>> & graph)//graph[i][j]: the j-th adjacent vertex of vertex graph[i]
	{
		int count = 0;
		int N = graph.size();//num of vertices in graph

		//for each vertex in graph, check if its any two adjacent vertices have edge
		for (int v = 0; v < N; ++v)
		{
			int M = graph[v].size();
			for (int i = 0; i < M - 1; ++i)
			{
				int adj1 = graph[v][i];
				for (int j = i + 1; j < M; ++j)
				{
					int adj2 = graph[v][j];
					int L = graph[adj1].size();
					for (int k = 0; k < L; ++k)
					{
						if (graph[adj1][k] == adj2)
						{
							++count;
							break;
						}
					}
				}
			}
		}
		count /= 3;
		Debug::Print2D<int>()(graph, false);
		std::cout << "TrianglesInGraph Count_AdjacencyList: " << count << std::endl;
		return count;
	}

	//adjacencyMatrix of an undirected graph must be diagonally symmetric
	int Count_AdjacencyMatrix(const std::vector<std::vector<int>> & graph)//graph[i][j]: 1, vertex i has edge with vertex j, otherwise, 0
	{
		int count = 0;
		int N = graph.size();//num of vertices in graph

		//for each vertex, graph[v], in graph, check if any two adjacent vertices, graph[v][i] and graph[v][j], have edge (graph[i][j] == 1)
		for (int v = 0; v < N; ++v)//for each vertex in graph
		{
			int M = graph[v].size();//num of adjacent vertex of vertex graph[i]. M should be equal to N for Adjacency Matrix
			for (int i = 0; i < M - 1; ++i)//for each adjacent vertex of vertex graph[v]
			{
				if (graph[v][i] == 1)//vertex graph[v] has edge to vertex graph[i]
				{
					for (int j = i + 1; j < M; ++j)
					{
						if (graph[v][j] == 1 && graph[i][j] == 1)
						{
							//std::cout << v << "," << i << "," << j << std::endl;
							++count;
						}
					}
				}
			}
		}
		count /= 3;
		Debug::Print2D<int>()(graph, false);
		std::cout << "TrianglesInGraph Count_AdjacencyMatrix: " << count << std::endl;
		return count;
	}

	static void DeleteGraph(UndirectedGraphNode * node)
	{
		std::vector<UndirectedGraphNode *> tmp;

		std::unordered_set<UndirectedGraphNode *> visited;
		std::queue<UndirectedGraphNode *> queue;
		queue.push(node);
		visited.insert(node);
		while (!queue.empty())
		{
			node = queue.front();
			queue.pop();

			tmp.push_back(node);//now visit the node

			for (auto nebr : node->neighbors)
			{
				if (visited.count(nebr) == 0)
				{
					visited.insert(nebr);
					queue.push(nebr);
				}
			}
		}

		//now delete tmp
		for (std::vector<UndirectedGraphNode *>::iterator i = tmp.begin(); i != tmp.end(); ++i)
		{
			delete *i;
			*i = 0;
		}
	}
};
/*
		  4
		  |
		  1    3
		 / \
		0---2

		    1-------4
		   /|\    / |\
		  / | \ /   | \
		 /  | /\    |  \
		0---2   \   |   6
		 \\-|----\--|--//
		  \ |     \ |  /
		   \|      \| /
			3-------5

TrianglesInGraph Count_BFS: 1
TrianglesInGraph Count_BFS: 5
[rY][cX]
Row#0	= 1, 2,  
Row#1	= 0, 2, 4
Row#2	= 0, 1,  
Row#3	=  ,  ,  
Row#4	= 1,  ,  

TrianglesInGraph Count_AdjacencyList: 1
[rY][cX]
Row#0	= 1, 2, 3, 6
Row#1	= 0, 2, 4, 5
Row#2	= 0, 1, 3, 4
Row#3	= 0, 2, 5,  
Row#4	= 1, 2, 5, 6
Row#5	= 1, 3, 4, 6
Row#6	= 0, 4, 5,  

TrianglesInGraph Count_AdjacencyList: 5
[rY][cX]
Row#0	= 0, 1, 1, 0
Row#1	= 1, 0, 1, 1
Row#2	= 1, 1, 0, 0
Row#3	= 0, 0, 0, 0
Row#4	= 0, 1, 0, 0

TrianglesInGraph Count_AdjacencyMatrix: 1
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 1
Row#1	= 1, 0, 1, 0, 1, 1, 0
Row#2	= 1, 1, 0, 1, 1, 0, 0
Row#3	= 1, 0, 1, 0, 0, 1, 0
Row#4	= 0, 1, 1, 0, 0, 1, 1
Row#5	= 0, 1, 0, 1, 1, 0, 1
Row#6	= 1, 0, 0, 0, 1, 1, 0

TrianglesInGraph Count_AdjacencyMatrix: 5
*/
#endif