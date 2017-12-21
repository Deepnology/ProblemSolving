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
	std::vector<std::vector<int>> HashMap(TreeNode * root)
	{
		std::unordered_map<int, std::vector<int>> cols;//first: col index, second: nodes
		std::queue<std::pair<TreeNode *, int>> levelQueue;//first: node, second: col index
		levelQueue.push({ root, 0 });
		while (!levelQueue.empty())//level order traversal
		{
			auto p = levelQueue.front();
			levelQueue.pop();
			if (p.first != nullptr)
			{
				cols[p.second].emplace_back(p.first->val);
				levelQueue.push({ p.first->left, p.second - 1 });
				levelQueue.push({ p.first->right, p.second + 1 });
			}
		}

		Debug::Print2D<int>()(cols);

		int minColIdx = INT_MAX;
		int maxColIdx = INT_MIN;
		for (const auto & p : cols)
		{
			minColIdx = std::min(minColIdx, p.first);
			maxColIdx = std::max(maxColIdx, p.first);
		}

		std::vector<std::vector<int>> res;
		for (int i = minColIdx; !cols.empty() && i <= maxColIdx; ++i)
			res.emplace_back(std::move(cols[i]));

		std::cout << "BinaryTreeVerticalOrderTraversal HashMap: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
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

Row#0	= 0: 3, 0, 1
Row#1	= -1: 9, 5
Row#2	= 1: 8, 2
Row#3	= -2: 4
Row#4	= 2: 7

BinaryTreeVerticalOrderTraversal HashMap: [4], [9,5], [3,0,1], [8,2], [7]
*/
#endif
