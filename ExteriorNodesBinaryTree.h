#ifndef EXTERIOR_NODES_BINARY_TREE_H
#define EXTERIOR_NODES_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Boundary of Binary Tree
Elements of programming interview, BinaryTrees: Compute the exterior of a binary tree
Write a function that prints the nodes on the exterior of a binary tree in anti-clockwise order, i.e.
, print the nodes on the path from the root to the leftmost leaf in that order, then the leaves from left-to-right
, then the nodes from the rightmost leaf up to the root.
(By leftmost/rightmost leaf, we mean the leaf that appears first/last in an inorder traversal.)

*/
class ExteriorNodesBinaryTree
{
public:
	ExteriorNodesBinaryTree(){}
	~ExteriorNodesBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	std::vector<int> OnePassPreorderRecur(TreeNode* root)
	{
		std::vector<int> lb;//root + left boundary + leaves
		std::vector<int> rb;//right boundary
		recur(root, lb, rb, 0);
		std::reverse(rb.begin(), rb.end());
		lb.insert(lb.end(), rb.begin(), rb.end());
		return lb;
	}
private:
	//status: 0: root, 1: left boundary, 2: right boundary, 3: middle nodes
	void recur(TreeNode * cur, std::vector<int> & lb, std::vector<int> & rb, int status)
	{
		if (cur == NULL) return;
		if (status == 0 || status == 1 || !cur->left && !cur->right)
			lb.push_back(cur->val);
		else if (status == 2)
			rb.push_back(cur->val);
		recur(cur->left, lb, rb, status <= 1 ? 1 : status == 2 && !cur->right ? 2 : 3);
		recur(cur->right, lb, rb, status % 2 == 0 ? 2 : status == 1 && !cur->left ? 1 : 3);
	}

public:
	std::vector<int> Recur(TreeNode * root)
	{
		std::vector<int> res;
		if (root)
		{
			res.push_back(root->val);

			//perform preorder traversal for left subtree
			if (root->left)
				this->preorderRecur(root->left, true, res);

			//perform postorder traversal for right subtree
			if (root->right)
				this->postorderRecur(root->right, true, res);
		}
		std::cout << "ExteriorNodesBinaryTree Recur: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void preorderRecur(TreeNode * root, bool isBoundary, std::vector<int> & res)
	{
		std::cout << "left: " << root->val << std::endl;
		//preorder: visit the node
		if (isBoundary || (root->left == nullptr && root->right == nullptr))//boundary node or leaf node
			res.push_back(root->val);

		if (root->left)
			this->preorderRecur(root->left, isBoundary, res);
		if (root->right)
			this->preorderRecur(root->right, (isBoundary && root->left == nullptr), res);
	}
	void postorderRecur(TreeNode * root, bool isBoundary, std::vector<int> & res)
	{
		std::cout << "right: " << root->val << std::endl;
		if (root->left)
			this->postorderRecur(root->left, (isBoundary && root->right == nullptr), res);
		if (root->right)
			this->postorderRecur(root->right, isBoundary, res);

		//postorder: visit the node
		if (isBoundary || (root->left == nullptr && root->right == nullptr))//boundary node or leaf node
			res.push_back(root->val);
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
                                ______________________________34______________________________
                               /                                                               \
                               2                                                               2
                ______________ 6______________                                  ______________ 6______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______27______                  ______56______                  ______ 2______                  ______21______
       /               \               /               \               /               \               /               \
       4               4               X               4               X               4               X               4
    __28__          __ 0__          __ N__          __ 3__          __ N__          __ 1__          __ N__          __28__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       5       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N      17       N       N       N      41      27       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  64   N   N   N   N   N   N   N   N   N   N


left: 6
left: 27
left: 28
left: 0
left: 56
left: 3
left: 17
right: 6
right: 2
right: 1
right: 41
right: 64
right: 27
right: 21
right: 28
ExteriorNodesBinaryTree Recur: 34, 6, 27, 28, 0, 17, 64, 27, 28, 21, 6
*/
#endif