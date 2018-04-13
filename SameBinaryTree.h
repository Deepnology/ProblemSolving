#ifndef SAME_BINARY_TREE_H
#define SAME_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
/*
Leetcode: Same Tree
// Given two binary trees, write a function to check if they are equal or not.
//
// Two binary trees are considered equal if they are structurally identical
// and the nodes have the same value.
//
// Complexity:
// DFS, O(n) time, O(h) space, h is the height of tree
// BFS, O(n) time, O(n) space

Leetcode: Subtree of another tree
Cracking the coding interview 4.7
Contain tree
You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes.
Create an algorithm to decide if T2 is a subtree of T1.

See also SymmetricBinaryTree.h
*/
class SameBinaryTree
{
public:
	SameBinaryTree(){}
	~SameBinaryTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	bool DFS(TreeNode * p, TreeNode * q)
	{
		bool res = this->dfsRecur(p, q);
		std::cout << "SameBinaryTree DFS: " << res << std::endl;
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
			this->dfsRecur(p->left, q->left) &&
			this->dfsRecur(p->right, q->right);
	}
public:
	bool BFS(TreeNode * p, TreeNode * q)
	{
		std::cout << "SameBinaryTree BFS: ";
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

			if (p->left != NULL && q->left != NULL)
			{
				ps.push(p->left);
				qs.push(q->left);
			}
			else if (!(p->left == NULL && q->left == NULL))
			{
				std::cout << false << std::endl;
				return false;
			}

			if (p->right != NULL && q->right != NULL)
			{
				ps.push(p->right);
				qs.push(q->right);
			}
			else if (!(p->right == NULL && q->right == NULL))
			{
				std::cout << false << std::endl;
				return false;
			}
		}

		bool res = ps.empty() && qs.empty();
		std::cout << res << std::endl;
		return res;
	}

	bool ContainTree(TreeNode * s, TreeNode * t)
	{
		int d = depthRecur(t);
		std::vector<TreeNode*> nodes;//nodes in s with same depth as t
		depthRecur2(s, d, nodes);
		bool res = false;
		for (auto & n : nodes)
			if (sameRecur(n, t))
			{
				res = true;
				break;
			}
		std::cout << "SameBinaryTree ContainTree: " << res << std::endl;
		return res;
	}
private:
	int depthRecur(TreeNode * cur)
	{
		if (cur == NULL) return 0;
		return std::max(depthRecur(cur->left), depthRecur(cur->right)) + 1;
	}
	int depthRecur2(TreeNode * cur, int tgtDepth, std::vector<TreeNode*> & v)
	{
		if (cur == NULL) return 0;
		int d = std::max(depthRecur2(cur->left, tgtDepth, v), depthRecur2(cur->right, tgtDepth, v)) + 1;
		if (d == tgtDepth) v.push_back(cur);
		return d;
	}
	bool sameRecur(TreeNode * s, TreeNode * t)
	{
		if (s == NULL && t == NULL) return true;
		if (s == NULL || t == NULL) return false;
		if (s->val != t->val) return false;
		return sameRecur(s->left, t->left) && sameRecur(s->right, t->right);
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
   2       5
 /   \   /   \
 3   3   3   3
 7   8  17  18

      
       1
    __ 1__
   /       \
   2       2
   2       5
 /   \   /   \
 3   3   3   3
 7   8  17  18


SameBinaryTree DFS: 1
SameBinaryTree BFS: 1
SameBinaryTree ContainTree: 1
*/
#endif