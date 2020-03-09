#ifndef MIN_DEPTH_BINARY_TREE_H
#define MIN_DEPTH_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Leetcode: Minimum Depth of Binary Tree
//
// Given a binary tree, find its minimum depth.
//
// The minimum depth is the number of nodes along the shortest path from the
// root node down to the nearest leaf node.
//
// Complexity:
// DFS takes O(2^h-1) time, O(h) space, h is the min depth of tree
// BFS takes O(2^h-1) time, O(2^(h-1)) space
*/
class MinDepthBinaryTree
{
public:
	MinDepthBinaryTree(){}
	~MinDepthBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};


	int DFS_Recur(TreeNode * root)
	{
		if (root == NULL)
			return 0;
		int res = INT_MAX;
		this->dfsRecur(root, 1, res);
		std::cout << "MinDepthBinaryTree DFS_Recur: " << res << std::endl;
		return res;
	}
private:
	void dfsRecur(TreeNode * cur, int depth, int & res)
	{
		if (cur == NULL)
			return;
		if (depth >= res)
			return;

		if (cur->left == NULL && cur->right == NULL)//met a leaf node
		{
			res = depth;
			return;
		}

		this->dfsRecur(cur->left, depth + 1, res);
		this->dfsRecur(cur->right, depth + 1, res);
	}

public:
	int BFS(TreeNode * root)
	{
		if (root == NULL)
			return 0;
		bool found = false;
		int depth = 0;
		std::queue<TreeNode *> levelQueue;
		levelQueue.push(root);
		while (!levelQueue.empty())
		{
			++depth;
			int levelCount = levelQueue.size();
			for (int i = 0; i < levelCount; ++i)
			{
				TreeNode * cur = levelQueue.front();
				levelQueue.pop();
				if (cur->left == NULL && cur->right == NULL)
				{ found = true; break; }
				if (cur->left) levelQueue.push(cur->left);
				if (cur->right) levelQueue.push(cur->right);
			}
			if (found) break;
		}
		std::cout << "MinDepthBinaryTree BFS: " << depth << std::endl;
		return depth;
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
        ______ 1______
       /               \
       2               2
    __ 2__          __ 4__
   /       \       /       \
   X       X       3       3
   N       N       5       3
 /   \   /   \   /   \   /   \
 X   X   X   X   X   4   X   X
 N   N   N   N   N   6   N   N


MinDepthBinaryTree DFS_Recur: 2
MinDepthBinaryTree BFS: 2
*/
#endif