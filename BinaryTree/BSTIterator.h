#ifndef BST_ITERATOR_H
#define BST_ITERATOR_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
/*
Leetcode: Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST). 
Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST (in-order successor).
Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

See also BinaryTreeInorderSucc.h
*/
class BSTIterator
{
public:
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};
private:
	std::stack<TreeNode *> m_LmostStk;
public:
	BSTIterator(TreeNode * root)
	{
		TreeNode * cur = root;
		while (cur)
		{
			m_LmostStk.push(cur);
			cur = cur->left;
		}
	}
	~BSTIterator(){}

	bool HasNext() const
	{
		return m_LmostStk.size() > 0;
	}
	TreeNode * Next()
	{
		TreeNode * res = m_LmostStk.top();
		m_LmostStk.pop();
		/*
		iterate to RSubLmost and push to stack
		so that stack.top() will be its in-order successor (next node)
		*/
		TreeNode * RSubLmost = res->right;
		while (RSubLmost)
		{
			m_LmostStk.push(RSubLmost);
			RSubLmost = RSubLmost->left;
		}
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
        ______ 8______
       /               \
       2               2
    __ 4__          __12__
   /       \       /       \
   3       3       3       3
   2       6      10      14
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 1   3   5   7   9  11  13  15

BSTIterator for above tree: 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
*/
#endif