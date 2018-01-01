#ifndef MIN_HEIGHT_TREES_IN_GRAPH_H
#define MIN_HEIGHT_TREES_IN_GRAPH_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>//for std::max
#include <limits>
#include <vector>
#include <queue>
#include "Debug.h"
/*
Leetcode: Minimum Height Trees
For a undirected graph with tree characteristics, we can choose any node as the root.
The result graph is then a rooted tree.
Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs).
Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1.
You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges.
Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1:
Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:
Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

Hint: How many MHTs can a graph have at most? Ans: 2
Note:
(1) According to the definition of tree on Wikipedia:
"a tree is an undirected graph in which any two vertices are connected by exactly one path.
In other words, any connected graph without simple cycles is a tree."
(2) The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

Perform BFS from the leaves until the number of unvisited nodes is less than 3.
*/
class MinHeightTreesInGraph
{
public:
	MinHeightTreesInGraph() {}
	~MinHeightTreesInGraph() {}

	std::vector<int> BFS(int n, const std::vector<std::pair<int, int>> & edges)
	{
		if (n == 1)
			return{ 0 };
		std::vector<std::vector<int>> adjList(n, std::vector<int>());
		std::vector<int> degree(n, 0);
		for (const auto & p : edges)
		{
			adjList[p.first].emplace_back(p.second);
			++degree[p.first];
			adjList[p.second].emplace_back(p.first);
			++degree[p.second];
		}

		//enqueue leaves
		std::queue<int> queue;
		for (int i = 0; i < n; ++i)
		{
			if (degree[i] == 1)
				queue.push(i);
		}

		//BFS from leaves until 1 or 2 nodes left unvisited
		int count = n;
		while (count > 2)//the all possible MHT root number is 1 or 2
		{
			//iterate over all cur level nodes ONLY
			int curLevelCount = queue.size();
			for (int i = 0; i < curLevelCount; ++i)
			{
				int cur = queue.front();
				queue.pop();
				--count;
				for (int & nxt : adjList[cur])
				{
					--degree[nxt];//remove the edge cur->nxt
					if (degree[nxt] == 1)//enqueue this neighbor only when it has one edge left
					{
						queue.push(nxt);
					}
				}
			}
		}

		std::vector<int> res;
		while (!queue.empty())
			res.emplace_back(queue.front()), queue.pop();

		std::cout << "MinHeightTreesInGraph BFS for \"" << n << "\", \"" << Debug::ToStr1D<int, int>()(edges) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
		        0
				|
				1
			   / \
			  2   3
			return [1]
MinHeightTreesInGraph BFS for "4", "[0,1], [1,2], [1,3]": 1

		     0  1  2
			  \ | /
				3
				|
				4
				|
				5
			return [3, 4]
MinHeightTreesInGraph BFS for "6", "[0,3], [1,3], [2,3], [4,3], [5,4]": 3, 4
*/
#endif
