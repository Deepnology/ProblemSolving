#ifndef BINARY_TREE_POSTORDER_SUCC_H
#define BINARY_TREE_POSTORDER_SUCC_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Google
http://www.careercup.com/question?id=6195668792115200
Observation:
1. if aNode is a left child, succ will be its 
	1.a. parent's RSub's LSub 1st leaf, 
	1.b. parent's RSub's RSub 1st leaf if LSub == NULL,
	1.c. parent if parent's RSub == NULL
2. if aNode is a right child, succ will be its parent
3. if aNode's parent is NULL, aNode must be root, succ will be NULL
*/
class BinaryTreePostOrderSucc
{
public:
	BinaryTreePostOrderSucc(){}
	~BinaryTreePostOrderSucc(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};
	TreeNode * Find_WParentPtr(TreeNode * aNode)
	{
		if (aNode == nullptr)
			return nullptr;
		TreeNode * succ = this->find_WParentPtr(aNode);
		
		std::cout << "BinaryTreePostorderSucc Find_WParentPtr for \"" << aNode->val << "\": " << (succ == NULL ? std::string("NULL") : std::to_string(succ->val)) << std::endl;
		return succ;
	}
	TreeNode * find_WParentPtr(TreeNode * aNode)
	{
		if (aNode == nullptr)
			return nullptr;
		if (aNode->parent == nullptr)//3. aNode is root
			return nullptr;

		TreeNode * parent = aNode->parent;
		if (parent->right == aNode)//2. aNode is a right child
			return parent;

		//1. aNode is a left child
		if (parent->right == nullptr)//1.c. parent's RSub == NULL
			return parent;
		//1.b., 1.a. find the LRDeepestNode of parent's RSub
		TreeNode * LRDeepestNode = parent->right;
		while (true)
		{
			if (LRDeepestNode->left != nullptr)//go down left if available
				LRDeepestNode = LRDeepestNode->left;
			else if (LRDeepestNode->right != nullptr)//otherwise, go down right if available
				LRDeepestNode = LRDeepestNode->right;
			else//otherwise, we are at leaf, stop here
				break;
		}
		return LRDeepestNode;
	}
	TreeNode * Find_BST_Only(TreeNode * root, TreeNode * aNode)
	{
		if (root == NULL || aNode == NULL)
			return NULL;
		TreeNode * res = NULL;

		/*1. perform binary search for (parent, aNode) pair*/
		TreeNode * parent = nullptr;
		TreeNode * curNode = root;
		while (curNode != nullptr)
		{
			if (aNode->val < curNode->val)
			{
				parent = curNode;
				curNode = curNode->left;
			}
			else if (aNode->val > curNode->val)
			{
				parent = curNode;
				curNode = curNode->right;
			}
			else//aNode->val == curNode->val
				break;
		}

		/*2. when we have the parent ptr, it is same for Find_WParentPtr*/
		if (parent == nullptr)//3. aNode is root
			res = nullptr;
		else if (parent->right == curNode)//2. aNode is a right child
			res = parent;
		else//1. aNode is a left child
		{
			if (parent->right == nullptr)//1.c. parent's RSub == NULL
				res = parent;
			else
			{
				//1.b., 1.a. find the LRDeepestNode of parent's RSub
				TreeNode * LRDeepestNode = parent->right;
				while (true)
				{
					if (LRDeepestNode->left != nullptr)//go down left if available
						LRDeepestNode = LRDeepestNode->left;
					else if (LRDeepestNode->right != nullptr)//otherwise, go down right if available
						LRDeepestNode = LRDeepestNode->right;
					else//otherwise, we are at leaf, stop here
						break;
				}
				res = LRDeepestNode;
			}
		}

		std::cout << "BinaryTreePostorderSucc Find_BST_Only for \"" << aNode->val << "\": " << (res == NULL ? std::string("NULL") : std::to_string(res->val)) << std::endl;
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
std::string PrintBinaryTree<BinaryTreePostOrderSucc::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreePostOrderSucc::TreeNode * n)
{
	std::ostringstream oss;
	if (n->parent)
		oss << n->parent->val;
	else
		oss << "N";
	return oss.str();
};
/*
BinaryTreePostorderSucc Find_WParentPtr for "3": 8
BinaryTreePostorderSucc Find_WParentPtr for "4": 6
BinaryTreePostorderSucc Find_WParentPtr for "9": 12
BinaryTreePostorderSucc Find_BST_Only for "3": 8
BinaryTreePostorderSucc Find_BST_Only for "4": 6
BinaryTreePostorderSucc Find_BST_Only for "9": 12
              
               N
        ______ 7______
       /               \
       7               7
    __ 3__          __11__
   /       \       /       \
   3       3      11      11
   1       5       9      13
 /   \   /   \   /   \   /   \
 1   1   5   5   9   9  13  13
 0   2   4   6   8  10  12  14

*/
#endif