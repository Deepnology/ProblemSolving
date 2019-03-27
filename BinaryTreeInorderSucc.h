#ifndef BINARY_TREE_INORDER_SUCC_H
#define BINARY_TREE_INORDER_SUCC_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BinaryTrees: Compute the successor(Find_WParentPtr)
Design an algorithm that takes a node n in a binary tree, and returns its successor.
Assume that each node has a parent field; the parent field of root is null.

http://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
Cracking the coding interview 4.5
Write an algorithm to find the 'next' node (e.g., in-order successor) of a given node in a binary search tree where each node has a link to its parent.

On an in-order traversal, we visit X.left, then X, then X.right.
So, if we want to find X.successor(), we do the following:
1. If X has a right child, then the successor must be on the right side of X (because of the order in which we visit nodes). Specifically, the left-most child must be the first node visited in that subtree.
2. Else, we go to X��s parent (call it P).
2.a. If X was a left child (P.left = X), then P is the successor of X
2.b. If X was a right child (P.right = X), then we have fully visited P, so we call successor(P).

Observation:
1. if aNode has a right child, succ will be RSub's leftmost node
2. else
2.a. if aNode is a left child, succ will be its parent
2.b. if aNode is a right child, succ will be the parent in the lowest (parent,parent->left) pair

O(height) time

See also BSTIterator.h

Leetcode: Inorder successor in BST II: Find_WParentPtr
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
The successor of a node p is the node with the smallest key greater than p.val.
You will have direct access to the node but not to the root of the tree. Each node will have a reference to its parent node.
*/
class BinaryTreeInorderSucc
{
public:
	BinaryTreeInorderSucc(){}
	~BinaryTreeInorderSucc(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};

	//1. Search from target node: needs parent ptr, works for both binary tree and BST
	TreeNode * Find_WParentPtr(TreeNode * aNode)
	{
		if (aNode == NULL)
			return NULL;
		TreeNode * res = NULL;
		
		if (aNode->right != NULL)//1. has right child => find RSubLmost
		{
			/*Find RSubLmost*/
			TreeNode * RSubLmost = aNode->right;
			while (RSubLmost->left != NULL)
				RSubLmost = RSubLmost->left;

			res = RSubLmost;
		}
		else//2. has no right child => go up until curNode is on the left of its parent
		{
			/*Find lowest (curNode == lowestP->left) pair*/
			TreeNode * curNode = aNode;
			TreeNode * lowestP = curNode->parent;
			while (lowestP != NULL)
			{
				if (lowestP->left == curNode)
					break;
				curNode = lowestP;
				lowestP = curNode->parent;
			}

			res = lowestP;
		}
		std::cout << "BinaryTreeInorderSucc Find_WParentPtr for \"" << aNode->val << "\": " << (res == NULL ? std::string("NULL") : std::to_string(res->val)) << std::endl;
		return res;
	}

	//2. Search from root: works only for BST
	TreeNode * Find_BST_Only(TreeNode * root, TreeNode * aNode)
	{
		if (root == NULL || aNode == NULL)
			return NULL;
		TreeNode * res = NULL;

		if (aNode->right != NULL)//1. has right child => find RSubLmost
		{
			/*Find RSubLmost*/
			TreeNode * RSubLmost = aNode->right;
			while (RSubLmost->left != NULL)
				RSubLmost = RSubLmost->left;

			res = RSubLmost;
		}
		else//2. has no right child => start from root and perform binary search to find lowest (parent,parent->left) pair
		{
			/*this part works only for BST cause it compares the val of node*/
			TreeNode * curNode = root;
			while (curNode != NULL)
			{
				if (aNode->val < curNode->val)
				{
					res = curNode;
					curNode = curNode->left;
				}
				else if (aNode->val > curNode->val)
					curNode = curNode->right;
				else//aNode->val == curNode->val, now (res,res->left) is the lowest (parent,parent->left) pair
					break;
			}
		}
		std::cout << "BinaryTreeInorderSucc Find_BST_Only for \"" << aNode->val << "\": " << (res == NULL ? std::string("NULL") : std::to_string(res->val)) << std::endl;
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

template<>
std::string PrintBinaryTree<BinaryTreeInorderSucc::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreeInorderSucc::TreeNode * n)
{
	std::ostringstream oss;
	if (n->parent)
		oss << n->parent->val;
	else
		oss << "N";
	return oss.str();
};

/*
BinaryTreeInorderSucc Find_WParentPtr for "3": 6
BinaryTreeInorderSucc Find_WParentPtr for "8": NULL
BinaryTreeInorderSucc Find_BST_Only for "3": 6
BinaryTreeInorderSucc Find_BST_Only for "8": NULL
      
       N
    __ 6__
   /       \
   6       6
   2       8
 /   \   /   \
 X   2   8   X
 N   3   7   N

*/
#endif