#ifndef BALANCED_BINARY_TREE_H
#define BALANCED_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, BinaryTrees: Test if a binary tree is balanced (BottomUp_PostOrder)
A binary tree is said to be balanced if for each node in the tree, the differernce in the height of its left and right subtrees is at most one.
A perfect binary tree is balanced, as is a complete binary tree.
A balanced binary tree doesn't have to be perfect or complete.
Leetcode: Balanced Binary Tree
// Balanced Binary Tree
// Given a binary tree, determine if it is height-balanced.
//
// An example of a height-balanced tree. A height-balanced tree is a tree
// whose subtrees differ in height by no more than one and the subtrees are
// height-balanced, too.
//
// Top-Down, Pre-Order, O(n^2) time, O(h) space
// Bottom-Up, Post-Order, O(n) time, O(h) space

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
/  \  /  \  /  \  /  \
7  8  9 10 11 12 13 14..........8

(perfect binary tree)
leafCount = 8
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)
treeMinSize = 2*leafCount - 1 = 15 (for full binary tree)

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
      /  \  /  \
      7  8  9 10................4

(full binary tree)
leafCount = 6
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)
treeMinSize = 2*leafCount - 1 = 11 (for full binary tree)

       ____0____................1
      /         \
     1           2..............2
   /   \       /   \
  3     4     5     6...........4
/  \  /  \  /
7  8  9 10 11...................5

(complete binary tree)
leafCount = 6
treeHeight = ceil(log2(leafCount)) + 1 = 4
treeMaxSize = 2^treeHeight - 1 = 15 (for perfect binary tree)

A full binary tree is a binary tree in which every node other than the leaves has two children.
A perfect binary tree is a full binary tree in which all leaves are at the same depth, and in which every parent has two children.
A complete binary tree is a binary tree in which every level, except possible the last, is completely filled, and all nodes are as far left as possible.

See also KBalancedNodesBinaryTree.h
*/
class BalancedBinaryTree
{
public:
	BalancedBinaryTree(){}
	~BalancedBinaryTree(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool TopDown_PreOrder(TreeNode * root)
	{
		bool r = this->isBalancedRecurPre(root);
		std::cout << "BalancedBinaryTree (TopDown PreOrder): " << r << std::endl;
		return r;
	}
private:
	bool isBalancedRecurPre(TreeNode * cur)
	{
		if (cur == NULL)//leaf node
			return true;

		return (std::abs(this->heightRecur(cur->left) - this->heightRecur(cur->right) <= 1)//(left subtree height == right subtree height) || (left subtree height == right subtree height + 1) || (left subtree height + 1 = right subtree height)

			//pre-order: now traverse recursively down after visited this node
			&& this->isBalancedRecurPre(cur->left)//left subtree balanced?
			&& this->isBalancedRecurPre(cur->right));//right subtree balanced?
	}
	int heightRecur(TreeNode * cur)
	{
		if (cur == NULL)//leaf node
			return 0;

		//height = max(left subtree height, right subtree height) + 1
		return std::max(this->heightRecur(cur->left), this->heightRecur(cur->right)) + 1;
	}




public:
	bool BottomUp_PostOrder(TreeNode * root)
	{
		std::pair<bool, int> res = this->heightRecurPost(root);
		std::cout << "BalancedBinaryTree (BottomUp PostOrder): " << res.first << ", " << res.second << std::endl;
		return res.first;
	}
private:
	std::pair<bool, int> heightRecurPost(TreeNode * cur)//first: isBalanced, second: height
	{
		if (cur == NULL)//leaf node
			return{ true, 0 };

		std::pair<bool, int> left = this->heightRecurPost(cur->left);
		if (!left.first)//left subtree not balanced
			return{ false, 0 };

		std::pair<bool, int> right = this->heightRecurPost(cur->right);
		if (!right.first)//right subtree not balanced
			return{ false, 0 };

		//post order: now visit this node when both left subtree and right subtree are balanced
		if (std::abs(left.second - right.second) > 1)//left subtree height is not matched with right subtree height
			return{ false, 0 };
		
		return{ true, std::max(left.second, right.second) + 1 };
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
        ______ 2______                  ______ 2______
       /               \               /               \
       3               3               3               3
    __ 3__          __ 3__          __ 3__          __ 3__
   /       \       /       \       /       \       /       \
   4       4       4       4       4       4       X       X
   4       4       4       4       4       4       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 5   5   X   X   X   X   X   X   X   X   X   X   X   X   X   X
 5   5   N   N   N   N   N   N   N   N   N   N   N   N   N   N


BalancedBinaryTree (TopDown PreOrder): 1
BalancedBinaryTree (BottomUp PostOrder): 1, 5
*/
#endif