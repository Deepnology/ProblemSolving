#ifndef BINARY_TREE_INORDER_TRAVERSAL_H
#define BINARY_TREE_INORDER_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BinaryTrees: Morris traversal(Iterate_Threaded), Implement an inorder traversal with O(1) space(Iterate_WParentPtr)
Leetcode: Binary Tree Inorder Traversal
// Given a binary tree, return the inorder traversal of its nodes' values.
//
// For example:
// Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
// return [1,3,2].
//
// Note: Recursive solution is trivial, could you do it iteratively?
//
// Complexity:
// Recursion or Stack: O(n) time, O(h) space, h is the depth of tree
// Threaded Binary Tree : O(n) time, O(1) space
// (This approach is based on temporarily setting right child fields for leaf nodes, and later undoing these changes. AKA Morris traversal.)
// (It is largely of theoretical interest; one major shortcoming is that it is not thread-safe, since it mutates the tree, albeit temporarily.)
*/

class BinaryTreeInOrderTraversal
{
public:
	BinaryTreeInOrderTraversal(){}
	~BinaryTreeInOrderTraversal(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};
	/*
	We can also use iterative in-order traversal on a BST to find the Kth smallest node in a BST.
	Just keep tracking the number of nodes that were popped out of the stack.
	*/
	std::vector<int> Iterate_Stack(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		for (; root != NULL; root = root->left)
			stk.push(root);
		//now stk has all the nodes in the leftmost node path (straight left) (straight left path might not go to the leaf node)

		while (!stk.empty())
		{
			root = stk.top();
			stk.pop();
			res.push_back(root->val);//in-order: visit the node

			//push all the nodes in the leftmost node path (straight left) of the right subtree to stk (straight left path might not go to the leaf node)
			for (root = root->right; root != NULL; root = root->left)
				stk.push(root);//RSubLmost path
		}

		std::cout << "BinaryTreeInOrderTraversal Iterate Stack: " << Debug::ToStr1D<int>()(res) << std::endl;
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
				root = root->left;//go left
			}
			else
			{
				root = stk.top();
				stk.pop();
				res.push_back(root->val);//in-order: visit the node
				root = root->right;//go right
			}
		}

		std::cout << "BinaryTreeInOrderTraversal Iterate Stack2: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_Threaded(TreeNode * root)
	{
		std::vector<int> res;
		while (root != NULL)
		{
			if (root->left != NULL)/*current node: has left child*/
			{
				auto LSubRmost = root->left;
				while (LSubRmost->right != NULL && LSubRmost->right != root)
					LSubRmost = LSubRmost->right;/*rightmost node in the left subtree of the current node*/

				if (LSubRmost->right == NULL)/*current node: has no right child of rightmost node in the left subtree*/
				{
					LSubRmost->right = root;/*make right child the in-order successor of the rightmost node*/
					root = root->left;/*move current node to its left child*/
				}
				else/*current node: has right child of rightmost node in the left subtree, which is current node itself*/
				{
					LSubRmost->right = NULL;/*restore right child of rightmost node in the left subtree*/

					res.push_back(root->val);/*now visiting the current node*/

					root = root->right;/*move current node to its right child*/
				}
			}
			else/*current node: has no left child*/
			{
				res.push_back(root->val);/*now visiting the current node*/

				root = root->right;/*move current node to its right child*/
				/*which could be 1. the (new link) in-order successor the current node 2. the original right child of the current node*/
			}
		}

		std::cout << "BinaryTreeInOrderTraversal Iterate Threaded: " << Debug::ToStr1D<int>()(res) << std::endl;
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
			if (prev == nullptr || prev->left == cur || prev->right == cur)//going down to left or right subtree
			{
				if (cur->left)
				{
					next = cur->left;//go down left
				}
				else
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->right ? cur->right : cur->parent;//go down right or go up
				}
			}
			else if (cur->left == prev)//going up from left subtree
			{
				//now visit the node
				res.push_back(cur->val);
				next = cur->right ? cur->right : cur->parent;//go down right or go up
			}
			else//cur->right == prev, going up from right subtree
			{
				next = cur->parent;//going up
			}
			prev = cur;
			cur = next;
		}

		std::cout << "BinaryTreeInOrderTraversal Iterate_WParentPtr: " << Debug::ToStr1D<int>()(res) << std::endl;
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
std::string PrintBinaryTree<BinaryTreeInOrderTraversal::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreeInOrderTraversal::TreeNode * n)
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


 BinaryTreeInOrderTraversal Iterate Stack: 1, 3, 2
 BinaryTreeInOrderTraversal Iterate Stack2: 1, 3, 2
 BinaryTreeInOrderTraversal Iterate Threaded: 1, 3, 2
 BinaryTreeInOrderTraversal Iterate_WParentPtr: 1, 3, 2
              
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


 BinaryTreeInOrderTraversal Iterate Stack: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 BinaryTreeInOrderTraversal Iterate Stack2: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 BinaryTreeInOrderTraversal Iterate Threaded: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 BinaryTreeInOrderTraversal Iterate_WParentPtr: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
*/
#endif