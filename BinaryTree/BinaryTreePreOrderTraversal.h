#ifndef BINARY_TREE_PREORDER_TRAVERSAL_H
#define BINARY_TREE_PREORDER_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BinaryTrees: Iterate_Stack, Iterate_WParentPtr
Leetcode: Binary Tree PreOrder Traversal
//
// Given a binary tree, return the preorder traversal of its nodes' values.
//
// For example,
//
// Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
// return [1,2,3].
//
// Note: Recursive solution is trivial, could you do it iteratively?
//
// Complexity:
// O(n) time, O(h) space, h is the depth of tree

see also TreeFromParentChildPairs.h, FlattenNestedListIterator.h
*/
class BinaryTreePreOrderTraversal
{
public:
	BinaryTreePreOrderTraversal(){}
	~BinaryTreePreOrderTraversal(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};

	std::vector<int> Iterate_Stack(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		if (root != NULL)
			stk.push(root);

		while (!stk.empty())
		{
			root = stk.top();
			stk.pop();
			res.push_back(root->val);

			if (root->right != NULL)
				stk.push(root->right);//1. push right
			if (root->left != NULL)
				stk.push(root->left);//2. push left
		}

		std::cout << "BinaryTreePreOrderTraversal Iterate_Stack: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_Stack2(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		while (!stk.empty() || root)
		{
			if (root)
			{
				stk.push(root);
				res.push_back(root->val);//preorder: visit the node
				root = root->left;//go left
			}
			else
			{
				root = stk.top();
				stk.pop();
				root = root->right;//go right
			}
		}

		std::cout << "BinaryTreePreOrderTraversal Iterate Stack2: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_Stack_Generic(TreeNode * root)
	{
		std::stack<TreeNode*> stk;
		std::vector<int> res;
		std::unordered_set<TreeNode *> visit;
		if (root)
		{
			stk.push(root);
			visit.insert(root);
		}
		while (!stk.empty())
		{
			//push all nodes in the RL deepest path to stk
			while ((stk.top()->right && !visit.count(stk.top()->right)) || (stk.top()->left && !visit.count(stk.top()->left)))
			{
				root = stk.top();
				if (root->right != NULL && !visit.count(root->right))
					stk.push(root->right), visit.insert(root->right);//1. push right
				else if (root->left != NULL && !visit.count(root->left))
					stk.push(root->left), visit.insert(root->left);//2. push left
			}
			//now visit cur node in reversed preorder
			root = stk.top();
			res.push_back(root->val);
			stk.pop();
		}
		std::reverse(res.begin(), res.end());

		std::cout << "BinaryTreePreOrderTraversal Iterate_Stack_Generic: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_WParentPtr(TreeNode * root)
	{
		std::vector<int> res;
		TreeNode * prev = nullptr;
		TreeNode * cur = root;
		TreeNode * next;
		while (cur)
		{
			if (!prev || prev->left == cur || prev->right == cur)//going down to left or to right subtree
			{
				if (cur->left)
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->left;
				}
				else if (cur->right)
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->right;
				}
				else//leaf node
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->parent;
				}
			}
			else if (cur->left == prev)//going up from left subtree
			{
				if (cur->right)
				{
					next = cur->right;
				}
				else
				{
					next = cur->parent;
				}
			}
			else//cur->right == prev, going up from right subtree
			{
				next = cur->parent;
			}
			prev = cur;
			cur = next;
		}

		std::cout << "BinaryTreePreOrderTraversal Iterate_WParentPtr: " << Debug::ToStr1D<int>()(res) << std::endl;
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
std::string PrintBinaryTree<BinaryTreePreOrderTraversal::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreePreOrderTraversal::TreeNode * n)
{
	std::ostringstream oss;
	if (n->parent)
		oss << n->parent->val;
	else
		oss << "N";
	return oss.str();
};
/*
      
       N
    __ 1__
   /       \
   X       1
   N       2
 /   \   /   \
 X   X   2   X
 N   N   3   N


 BinaryTreePreOrderTraversal Iterate_Stack: 1, 2, 3
 BinaryTreePreOrderTraversal Iterate Stack2: 1, 2, 3
 BinaryTreePreOrderTraversal Iterate_Stack_Generic: 1, 2, 3
 BinaryTreePreOrderTraversal Iterate_WParentPtr: 1, 2, 3
              
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


 BinaryTreePreOrderTraversal Iterate_Stack: 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14
 BinaryTreePreOrderTraversal Iterate Stack2: 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14
 BinaryTreePreOrderTraversal Iterate_Stack_Generic: 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14
 BinaryTreePreOrderTraversal Iterate_WParentPtr: 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14
*/
#endif