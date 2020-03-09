#ifndef MAX_DEPTH_BINARY_TREE_H
#define MAX_DEPTH_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Leetcode: Maximum Depth of Binary Tree
// Maximum Depth of Binary Tree
// Given a binary tree, find its maximum depth.
//
// The maximum depth is the number of nodes along the longest path from the
// root node down to the farthest leaf node.
//
// DFS takes O(n) time, O(h) space, h is the max depth of tree
// BFS takes O(n) time, O(n/2) space
*/
class MaxDepthBinaryTree
{
public:
	MaxDepthBinaryTree(){}
	~MaxDepthBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int DFS_Recur(TreeNode * root)
	{
		int res = this->dfs_Recur(root);
		std::cout << "MaxDepthBinaryTree DFS_Recur: " << res << std::endl;
		return res;
	}

private:
	int dfs_Recur(TreeNode * cur)
	{
		if (cur == NULL)
			return 0;
		return std::max(this->dfs_Recur(cur->left), this->dfs_Recur(cur->right)) + 1;
	}
	
public:
	int BFS(TreeNode * root)
	{
		if (root == NULL)
			return 0;
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
				if (cur->left) levelQueue.push(cur->left);
				if (cur->right) levelQueue.push(cur->right);
			}
		}
		std::cout << "MaxDepthBinaryTree BFS: " << depth << std::endl;
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


MaxDepthBinaryTree DFS_Recur: 4
MaxDepthBinaryTree BFS: 4
*/
#endif