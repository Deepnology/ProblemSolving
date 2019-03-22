#ifndef BINARY_TREE_VERTICAL_ORDER_TRAVERSAL_H
#define BINARY_TREE_VERTICAL_ORDER_TRAVERSAL_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>//for std::max
#include <limits>
#include <unordered_map>
#include <vector>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/print-binary-tree-vertical-order-set-2/
Leetcode: Binary Tree Vertical Order Traversal
Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).
If two nodes are in the same row and column, the order should be from left to right.

Examples:
Given binary tree [3,9,20,null,null,15,7],
   3
  /\
 /  \
 9  20
    /\
   /  \
 15   7
return its vertical order traversal as:
[
 [9],
 [3,15],
 [20],
 [7]
]
Given binary tree [3,9,8,4,0,1,7],
      3
     /\
    /  \
   9    8
  /\    /\
 /  \  /  \
 4  0  1  7
return its vertical order traversal as:
[
 [4],
 [9],
 [3,0,1],
 [8],
 [7]
]
Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
     __3__
    /     \
   /       \
  9         8
 /\        /\
/  \      /  \
4   0    1   7
     \  /
      \/
	  52
return its vertical order traversal as:
[
 [4],
 [9,5],
 [3,0,1],
 [8,2],
 [7]
]

Leetcode: Vertical Order Traversal of a Binary Tree
Given a binary tree, return the vertical order traversal of its nodes values.
For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).
Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes
 , we report the values of the nodes in order from top to bottom (decreasing Y coordinates).
If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.
Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.
*/
class BinaryTreeVerticalOrderTraversal
{
public:
	BinaryTreeVerticalOrderTraversal() {}
	~BinaryTreeVerticalOrderTraversal() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	// I.
	std::vector<std::vector<int>> BFS_I(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		std::unordered_map<int, std::vector<int>> cols;//first: col index, second: nodes
		std::queue<std::pair<TreeNode *, int>> levelQueue;//first: node, second: col index
		if (root)
			levelQueue.push({ root, 0 });
		while (!levelQueue.empty())//level order traversal
		{
			auto p = levelQueue.front();
			levelQueue.pop();
			cols[p.second].emplace_back(p.first->val);
			if (p.first->left)
				levelQueue.push({ p.first->left, p.second - 1 });
			if (p.first->right)
				levelQueue.push({ p.first->right, p.second + 1 });
		}

		Debug::Print2D<int>()(cols);

		int minColIdx = INT_MAX;
		int maxColIdx = INT_MIN;
		for (const auto & p : cols)
		{
			minColIdx = std::min(minColIdx, p.first);
			maxColIdx = std::max(maxColIdx, p.first);
		}

		for (int i = minColIdx; !cols.empty() && i <= maxColIdx; ++i)
			res.emplace_back(std::move(cols[i]));

		std::cout << "BinaryTreeVerticalOrderTraversal BFS_I: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	// II.
	std::vector<std::vector<int>> BFS_II(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		std::unordered_map<int, std::vector<std::pair<int,int>>> cols;//<x,<y,val>>
		std::queue<std::pair<TreeNode *, std::pair<int,int>>> levelQueue;//<node,<x,y>>
		if (root)
			levelQueue.push({ root, {0,0} });
		while (!levelQueue.empty())//level order traversal
		{
			auto p = levelQueue.front();
			levelQueue.pop();
			cols[p.second.first].push_back({p.second.second, p.first->val});
			if (p.first->left)
				levelQueue.push({ p.first->left, {p.second.first-1, p.second.second+1} });
			if (p.first->right)
				levelQueue.push({ p.first->right, {p.second.first+1, p.second.second+1} });
		}
		int minColIdx = INT_MAX;
		int maxColIdx = INT_MIN;
		for (const auto & p : cols)
		{
			minColIdx = std::min(minColIdx, p.first);
			maxColIdx = std::max(maxColIdx, p.first);
		}
		for (int i = minColIdx; i <= maxColIdx; ++i)
		{
			std::sort(cols[i].begin(), cols[i].end());//sort based on <y,val>
			res.push_back({});
			for (auto & p : cols[i])
				res.back().push_back(p.second);
		}
		std::cout << "BinaryTreeVerticalOrderTraversal BFS_II: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<std::vector<int>> DFS_II(TreeNode * root)
	{
		std::vector<std::vector<int>> res;
		std::unordered_map<int,std::vector<std::pair<int,int>>> cols;//<x,<y,val>>
		recur(root, cols, 0, 0);
		int minColIdx = INT_MAX;
		int maxColIdx = INT_MIN;
		for (const auto & p : cols)
		{
			minColIdx = std::min(minColIdx, p.first);
			maxColIdx = std::max(maxColIdx, p.first);
		}
		for (int i = minColIdx; i <= maxColIdx; ++i)
		{
			std::sort(cols[i].begin(), cols[i].end());//sort based onn <y,val>
			res.push_back({});
			for (auto & p : cols[i])
				res.back().push_back(p.second);
		}
		std::cout << "BinaryTreeVerticalOrderTraversal DFS_II: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	void recur(TreeNode * cur, std::unordered_map<int, std::vector<std::pair<int,int>>> & cols, int x, int y)
	{
		if (cur == NULL) return;
		cols[x].push_back({y,cur->val});
		recur(cur->left, cols, x-1, y+1);
		recur(cur->right, cols, x+1, y+1);
	}


public:
	static void DeleteTree(TreeNode * root)
	{
		if (root == 0)
			return;

		DeleteTree(root->left);
		DeleteTree(root->right);

		//post order
		delete root;
		root = 0;
	}
};
/*

               1
        ______ 3______
       /               \
       2               2
    __ 9__          __ 8__
   /       \       /       \
   3       3       3       3
   4       0       1       7
 /   \   /   \   /   \   /   \
 X   X   X   4   4   X   X   X
 N   N   N   2   5   N   N   N


Row#0	= 2: 7
Row#1	= -2: 4
Row#2	= 1: 8, 2
Row#3	= -1: 9, 5
Row#4	= 0: 3, 0, 1

BinaryTreeVerticalOrderTraversal BFS_I: [4], [9,5], [3,0,1], [8,2], [7]
BinaryTreeVerticalOrderTraversal BFS_II: [4], [9,5], [3,0,1], [8,2], [7]
BinaryTreeVerticalOrderTraversal DFS_II: [4], [9,5], [3,0,1], [8,2], [7]
*/
#endif
