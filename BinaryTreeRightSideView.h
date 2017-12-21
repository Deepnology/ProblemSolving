#ifndef BINARY_TREE_RIGHT_SIDE_VIEW_H
#define BINARY_TREE_RIGHT_SIDE_VIEW_H
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

Similar problem: Leetcode: Find Largest Value in each Tree Row
*/
class BinaryTreeRightSideView
{
public:
	BinaryTreeRightSideView(){}
	~BinaryTreeRightSideView(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//level order traversal to find the rightmost node of each level
	std::vector<int> BFS(TreeNode * root)
	{
		std::vector<int> res;
		std::queue<TreeNode *> levelQueue;
		if (root)
		{
			levelQueue.push(root);
		}
		while (!levelQueue.empty())
		{
			int levelCount = levelQueue.size();
			for (int i = 0; i < levelCount; ++i)
			{
				root = levelQueue.front();
				levelQueue.pop();

				if (root->left)
					levelQueue.push(root->left);
				if (root->right)
					levelQueue.push(root->right);
			}
			res.push_back(root->val);
		}

		std::cout << "BinaryTreeRightSideView BFS: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//postorder traversal to overwrite a path of nodes from depth 0 to height-1
	std::vector<int> DFS(TreeNode * root)
	{
		int height = this->heightRecur(root);
		std::vector<int> res(height);
		this->dfsRecur(root, 0, res);
		std::cout << "BinaryTreeRightSideView DFS: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void dfsRecur(TreeNode * root, int depth, std::vector<int> & path)
	{
		if (root == NULL)
			return;

		this->dfsRecur(root->left, depth + 1, path);
		this->dfsRecur(root->right, depth + 1, path);
		//postorder update path (inorder works too)
		path[depth] = root->val;
	}
	int heightRecur(TreeNode * cur)
	{
		if (cur == NULL)//leaf node
			return 0;

		//height = max(left subtree height, right subtree height) + 1
		return std::max(this->heightRecur(cur->left), this->heightRecur(cur->right)) + 1;
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
                ______________ 1______________
               /                               \
               2                               2
        ______ 2______                  ______ 3______
       /               \               /               \
       X               3               X               3
    __ N__          __ 5__          __ N__          __ 4__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       6       7       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   5   X   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   8   N   N   N   N   N   N   N   N   N   N   N


BinaryTreeRightSideView BFS: 1, 3, 4, 7, 8
BinaryTreeRightSideView DFS: 1, 3, 4, 7, 8
*/
#endif