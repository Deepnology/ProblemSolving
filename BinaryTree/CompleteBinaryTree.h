#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
http://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
http://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-complete-tree-or-not/
A complete binary tree is a binary tree in which every level, except possible the last, is completely filled, and all nodes are as far left as possible.
It can have between 1 and 2^h nodes inclusive at the last level h.
In a complete binary tree, the level order traversal index of each node must be always smaller than the total count of nodes.
The level order traversal index of the left child node of a parent node i is 2*i+1, whereas the right child node is 2*i+2.
            0
          /   \
         1     2
        / \     \
       3   4     6
The node with level order traversal 6 is not smaller than the total count of the nodes in the tree, which breaks complete.

O(n) time, O(1) space

Elements of programming interview, BinaryTrees: Test if a binary tree is balanced, variant
Write a function that returns the size of the largest subtree that is complete.

Leetcode: Count Complete Tree Nodes
Given a complete binary tree, count the number of nodes.

Leetcode: Check Completeness of a Binary Tree
Given a binary tree, determine if it is a complete binary tree.
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible.
It can have between 1 and 2h nodes inclusive at the last level h.

See also BalancedBinaryTree.h
*/
class CompleteBinaryTree
{
public:
	CompleteBinaryTree(){}
	~CompleteBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool ValidRecur(TreeNode * root)
	{
		int count = this->countNodesRecur(root);
		bool res = this->validRecur(root, 0, count);
		std::cout << "CompleteBinaryTree ValidRecur: " << res << std::endl;
		return res;
	}
private:
	int countNodesRecur(TreeNode * cur)
	{
		if (cur == NULL)
			return 0;
		return this->countNodesRecur(cur->left) + this->countNodesRecur(cur->right) + 1;
	}
	bool validRecur(TreeNode * cur, int index, int count)
	{
		if (cur == NULL)
			return true;
		if (index >= count)
			return false;
		return this->validRecur(cur->left, 2 * index + 1, count) &&
			this->validRecur(cur->right, 2 * index + 2, count);
	}

public:
	int LargestCompleteSubtreeSizeRecur(TreeNode * root)
	{
		int count = this->countNodesRecur(root);
		std::pair<bool, int> res = this->largestCompleteRecur(root, 0, count);
		std::cout << "CompleteBinaryTree LargestCompleteSubtreeSizeRecur: " << res.second << std::endl;
		return res.second;
	}
private:
	std::pair<bool, int> largestCompleteRecur(TreeNode * cur, int index, int count)
	{
		if (cur == NULL)
			return{ true, 0 };

		std::pair<bool, int> leftCount = this->largestCompleteRecur(cur->left, 2 * index + 1, count);
		std::pair<bool, int> rightCount = this->largestCompleteRecur(cur->right, 2 * index + 2, count);
		//postorder
		if (leftCount.first && rightCount.first && index < count)
		{
			//cur node is valid for the complete subtree group, include it
			return{ true, leftCount.second + rightCount.second + 1 };
		}
		else
		{
			//cur node is NOT valid for the complete subtree group, don't include it
			return{ false, std::max(leftCount.second, rightCount.second) };
		}
	}

public:
	int EfficientCountNodesRecur(TreeNode * root)
	{
		int res = this->efficientCountNodesRecur(root);
		std::cout << "CompleteBinaryTree EfficientCountNodesRecur: " << res << std::endl;
		return res;
	}
private:
	int efficientCountNodesRecur(TreeNode * root)
	{
		if (root == NULL)
			return 0;

		int leftHeight = 0;
		TreeNode * leftmost = root;
		while (leftmost)
		{
			++leftHeight;
			leftmost = leftmost->left;
		}

		int rightHeight = 0;
		TreeNode * rightmost = root;
		while (rightmost)
		{
			++rightHeight;
			rightmost = rightmost->right;
		}

		if (leftHeight == rightHeight)
			return (1 << leftHeight) - 1;//(2^leftHeight - 1) nodes for a perfect binary sub-tree
		else
			return this->efficientCountNodesRecur(root->left) + this->efficientCountNodesRecur(root->right) + 1;
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
    __ 0__
   /       \
   2       2
   1       2
 /   \   /   \
 3   3   X   3
 3   4   N   6


CompleteBinaryTree ValidRecur: 0
CompleteBinaryTree LargestCompleteSubtreeSizeRecur: 3

       1
    __ 0__
   /       \
   2       2
   1       2
 /   \   /   \
 3   X   X   X
 3   N   N   N


CompleteBinaryTree ValidRecur: 1
CompleteBinaryTree LargestCompleteSubtreeSizeRecur: 4
CompleteBinaryTree EfficientCountNodesRecur: 4
*/
#endif