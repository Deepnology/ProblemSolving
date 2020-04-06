#ifndef SYMMETRIC_BINARY_TREE_H
#define SYMMETRIC_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
/*
Elements of programming interview
Leetcode: Symmetric Tree
// Given a binary tree, check whether it is a mirror of itself (ie, symmetric
// around its center).
//
// For example, this binary tree is symmetric:
//
//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
// But the following is not:
//    1
//   / \
//  2   2
//   \   \
//   3    3
// Note:
// Bonus points if you could solve it both recursively and iteratively.
//
// DFS, O(n) time, O(h) space, h is the height of tree
// BFS, O(n) time, O(n) space

See also SameBinaryTree.h
*/
class SymmetricBinaryTree
{
public:
	SymmetricBinaryTree(){}
	~SymmetricBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool DFS(TreeNode * root)
	{
		if (root == NULL)
			return true;
		bool res = this->dfsRecur(root->left, root->right);
		std::cout << "SymmetricBinaryTree DFS: " << res << std::endl;
		return res;
	}
private:
	bool dfsRecur(TreeNode * p, TreeNode * q)
	{
		if (p == NULL && q == NULL)
			return true;
		if (p == NULL || q == NULL)
			return false;
		return (p->val == q->val) &&
			this->dfsRecur(p->left, q->right) &&
			this->dfsRecur(p->right, q->left);
	}
public:
	bool BFS(TreeNode * root)
	{
		if (root == NULL)
			return true;
		std::cout << "SymmetricBinaryTree BFS: ";
		TreeNode * p = root->left;
		TreeNode * q = root->right;
		std::queue<TreeNode *> ps;
		std::queue<TreeNode *> qs;
		if (p != NULL)
			ps.push(p);
		if (q != NULL)
			qs.push(q);
		while (!ps.empty() && !qs.empty())
		{
			p = ps.front();
			ps.pop();
			q = qs.front();
			qs.pop();
			if (p->val != q->val)
			{
				std::cout << false << std::endl;
				return false;
			}

			if (p->left != NULL && q->right != NULL)
			{
				ps.push(p->left);
				qs.push(q->right);
			}
			else if (!(p->left == NULL && q->right == NULL))
			{
				std::cout << false << std::endl;
				return false;
			}

			if (p->right != NULL && q->left != NULL)
			{
				ps.push(p->right);
				qs.push(q->left);
			}
			else if (!(p->right == NULL && q->left == NULL))
			{
				std::cout << false << std::endl;
				return false;
			}
		}

		bool res = ps.empty() && qs.empty();
		std::cout << res << std::endl;
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
/*
       1
    __ 1__
   /       \
   2       2
   2       2
 /   \   /   \
 3   3   3   3
 3   4   4   3


SymmetricBinaryTree DFS: 1
SymmetricBinaryTree BFS: 1
*/
#endif