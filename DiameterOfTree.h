#ifndef DIAMETER_OF_TREE_H
#define DIAMETER_OF_TREE_H
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Tree Diameter
Elements of programming interview, Recursion: Compute the diameter of a tree
Let T be a tree, where each edge is labeled with a nonnegative real-valued distance.
Define the diameter of T to be "the length of a longest path in T".
Diameter of root = Max(max diameter of root's children, largest height of a child node + 2nd largest height of a child node).

           _______________v_____________
          /                             \
     _____v____                         v
    /          \
  __v__      __v
 /     \    /
 v     v    v
/ \   / \  /
v v   v v  v

The diameter of the tree above is 7.

BruteForce:
run BFS, from each node and recording the maximum value of the shortest path distances computed.
BFS in a graph whose vertex set is V and edge set is E has complexity O(|V|+|E|).
Therefore, the brute force algorithm has O(|V|(|V|+|E|)) = O(|V|^2) time complexity since |E| = |V| - 1 in a tree.

DivdeConquer:
O(|V|) time

See also BinaryTreeMaxPathSum.h
*/
class DiameterOfTree
{
public:
	DiameterOfTree(){}
	~DiameterOfTree(){}
	struct TreeNode
	{
		std::vector<std::pair<TreeNode *, double> > edges;//first: adj vertex, second: edge weight
	};

	double DFSRecur(TreeNode * root)
	{
		std::pair<double, double> res({ 0.0, 0.0 });//first: height, second: diameter
		if (root)
			res = this->recur(root, NULL);
		std::cout << "DiameterOfTree DFSRecur: height=" << res.first << ", diameter=" << res.second << std::endl;
		return res.second;
	}
private:
	//first: height, second: diameter
	std::pair<double, double> recur(TreeNode * curNode, TreeNode * parent)
	{
		double height1 = 0.0;//the largest height of curNode
		double height2 = 0.0;//the 2nd largest height or curNode
		double diameter = std::numeric_limits<double>::min();
		//enumerate all adj vertices (edges)
		for (std::pair<TreeNode*, double> & e : curNode->edges)
		{
			if (e.first == parent) continue;
			std::pair<double, double> height_Diameter = this->recur(e.first, curNode);

			//post-order
			//1. height = height of the largest height in child nodes + edge weight
			if (height_Diameter.first + e.second > height1)
			{
				height2 = height1;
				height1 = height_Diameter.first + e.second;
			}
			else if (height_Diameter.first + e.second > height2)
			{
				height2 = height_Diameter.first + e.second;
			}
			//2. find max diameter among children
			if (height_Diameter.second > diameter)
				diameter = height_Diameter.second;
		}

		//2. diameter = the larger one between max diameter among children (the longest path that doesn't pass thru curNode) and the first 2 heights of children (the longest path that passes thru curNode)
		diameter = std::max(diameter, height1 + height2);
		return{ height1, diameter };
	}



public:
	//use DAG to represent a tree so that the edge direction is always from top to down
	//adjMatrix[0] must also be the root
	double DFSRecur_DiAdjMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		std::pair<double, double> res({ 0.0, 0.0 });//first: height, second: diameter
		res = this->diAdjMatrixRecur(adjMatrix, 0, -1);
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "DiameterOfTree DFSRecur_DiAdjMatrix: height=" << res.first << ", diameter=" << res.second << std::endl;
		return res.second;
	}
private:
	std::pair<double, double> diAdjMatrixRecur(const std::vector<std::vector<int> > & adjMatrix, int curNode, int parent)
	{
		int N = adjMatrix.size();
		double height1 = 0.0;//the largest height of curNode
		double height2 = 0.0;//the 2nd largest height or curNode
		double diameter = std::numeric_limits<double>::min();
		//enumerate all adj vertices (edges)
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[curNode][i] != 0 && adjMatrix[curNode][i] != parent)
			{
				std::pair<double, double> height_Diameter = this->diAdjMatrixRecur(adjMatrix, i, curNode);

				//post-order
				//1. height = height of the largest height in child nodes + edge weight
				if (height_Diameter.first + adjMatrix[curNode][i] > height1)
				{
					height2 = height1;
					height1 = height_Diameter.first + adjMatrix[curNode][i];
				}
				else if (height_Diameter.first + adjMatrix[curNode][i] > height2)
				{
					height2 = height_Diameter.first + adjMatrix[curNode][i];
				}
				//2. find max diameter among children
				if (height_Diameter.second > diameter)
					diameter = height_Diameter.second;
			}
		}

		//2. diameter = the larger one between max diameter among children (the longest path that doesn't pass thru curNode) and the first 2 heights of children (the longest path that passes thru curNode)
		diameter = std::max(diameter, height1 + height2);
		return{ height1, diameter };
	}


public:
	//leetcode
	int DFS(std::vector<std::vector<int>> & edges)
	{
		std::unordered_map<int,std::vector<int>> adjList;
		for (auto & p : edges)
		{
			adjList[p[0]].push_back(p[1]);
			adjList[p[1]].push_back(p[0]);
		}
		//first: height, second: diameter
		std::pair<int,int> res = this->dfs(adjList, edges[0][0], -1);
		return res.second;
	}
private:
	std::pair<int,int> dfs(std::unordered_map<int,std::vector<int>> & adjList, int cur, int parent)
	{
		int height1 = 0.0;//the largest height of curNode
		int height2 = 0.0;//the 2nd largest height or curNode
		int diameter = INT_MIN;
		//enumerate all adj vertices (edges)
		for (auto nxt : adjList[cur])
		{
			if (nxt == parent) continue;
			std::pair<int,int> height_Diameter = this->dfs(adjList, nxt, cur);

			//post-order
			//1. height = height of the largest height in child nodes + edge weight
			if (height_Diameter.first + 1 > height1)
			{
				height2 = height1;
				height1 = height_Diameter.first + 1;
			}
			else if (height_Diameter.first + 1 > height2)
			{
				height2 = height_Diameter.first + 1;
			}
			//2. find max diameter among children
			if (height_Diameter.second > diameter)
				diameter = height_Diameter.second;
		}

		//2. diameter = the larger one between max diameter among children (the longest path that doesn't pass thru curNode) and the first 2 heights of children (the longest path that passes thru curNode)
		diameter = std::max(diameter, height1 + height2);
		return{ height1, diameter };
	}
};
/*
[rY][cX]
Row#0	= 0, 7, 0, 0, 0, 14, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#15	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

DiameterOfTree DFSRecur_DiAdjMatrix: height=17, diameter=31
*/
#endif