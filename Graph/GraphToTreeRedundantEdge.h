#ifndef GRAPH_TO_TREE_REDUNDANT_EDGE_H
#define GRAPH_TO_TREE_REDUNDANT_EDGE_H
#include "Debug.h"
/*
Leetcode: Redundant Connection
In this problem, a tree is an undirected graph that is connected and has no cycles.
The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with "one additional edge added".
The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges.
Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.
Return an edge that can be removed so that the resulting graph is a tree of N nodes.
If there are multiple answers, return the answer that occurs last in the given 2D-array.
The answer edge [u, v] should be in the same format, with u < v.
Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3

Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Leetcode: Redundant Connection II
In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with "one additional directed edge added".
The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges.
Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.
Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes.
If there are multiple answers, return the answer that occurs last in the given 2D-array.
Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3

Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
*/
class GraphToTreeRedundantEdge
{
public:
	GraphToTreeRedundantEdge() {}

	std::vector<int> Undirected_UnionFind(const std::vector<std::vector<int>> & edges)
	{
		int N = 0;
		for (auto & p : edges)
			N = std::max(N, std::max(p[0], p[1]));
		std::vector<int> root;
		for (int i = 0; i <= N; ++i)
			root.push_back(i);
		for (auto & p : edges)
		{
			int root1 = Find(root, p[0]);
			int root2 = Find(root, p[1]);
			if (root1 == root2)
				return p;
			root[root1] = root2;
		}
		return{ 0,0 };
	}

	std::vector<int> Directed_UnionFind(const std::vector<std::vector<int>> & edges)
	{
		int N = edges.size();
		std::vector<int> rootIdx;
		//init rootIdx with [0:N]
		for (int i = 0; i <= N; ++i)
			rootIdx.push_back(i);

		std::vector<int> edge1;
		std::vector<int> edge2;
		for (int i = 0; i < N; ++i)
		{
			int src = edges[i][0];
			int tgt = edges[i][1];
			int rootSrc = Find(rootIdx, src);
			int rootTgt = Find(rootIdx, tgt);
			if (rootSrc == rootTgt)
			{
				edge1 = edges[i];//record last edge for cycle issue
			}
			else
			{
				if (rootTgt == tgt)
					rootIdx[rootTgt] = rootSrc;
				else
					edge2 = edges[i];//record last edge for multiple parents issue
			}
		}

		if (edge1.empty()) return edge2;
		if (edge2.empty()) return edge1;
		for (int i = 0; i < N; ++i)
			if (edge2[1] == edges[i][1])//return first edge that has multiple parents issue
				return edges[i];

		return std::vector<int>();
	}

private:
	int Find(std::vector<int> & v, int idx)
	{
		while (idx != v[idx])
		{
			v[idx] = v[v[idx]];
			idx = v[idx];
		}
		return idx;
	}
};
#endif
