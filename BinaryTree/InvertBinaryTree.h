#ifndef INVERT_BINARY_TREE_H
#define INVERT_BINARY_TREE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Invert Binary Tree
Invert a binary tree. (Mirror it)

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1

*/
class InvertBinaryTree
{
public:
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	InvertBinaryTree(){}
	~InvertBinaryTree(){}

	TreeNode * Recur(TreeNode * root)
	{
		this->recur(root);
		return root;
	}
private:
	void recur(TreeNode * root)
	{
		if (root == NULL)
			return;
		//preorder
		TreeNode * tmp = root->left;
		root->left = root->right;
		root->right = tmp;
		this->recur(root->left);
		this->recur(root->right);
	}
public:
	TreeNode * IterateWQueue(TreeNode * root)
	{
		//perform levelorder traversal with queue
		std::queue<TreeNode *> que;
		if (root)
			que.push(root);
		while (!que.empty())
		{
			TreeNode * cur = que.front();
			que.pop();
			TreeNode * tmp = cur->left;
			cur->left = cur->right;
			cur->right = tmp;
			if (cur->left) que.push(cur->left);
			if (cur->right) que.push(cur->right);
		}
		return root;
	}
	TreeNode * IterateWStack(TreeNode * root)
	{
		//perform preorder traversal with stack
		std::stack<TreeNode *> stk;
		if (root)
			stk.push(root);
		while (!stk.empty())
		{
			TreeNode * cur = stk.top();
			stk.pop();
			TreeNode * tmp = cur->left;
			cur->left = cur->right;
			cur->right = tmp;
			if (cur->right) stk.push(cur->right);
			if (cur->left) stk.push(cur->left);
		}
		return root;
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
        ______ 7______
       /               \
       2               2
    __ 3__          __11__
   /       \       /       \
   3       3       3       3
   1       5       9      13
 /   \   /   \   /   \   /   \
 X   4   X   4   X   4   4   X
 N   2   N   6   N  10  12   N

InvertBinaryTree Recur for above tree:
              
               1
        ______ 7______
       /               \
       2               2
    __11__          __ 3__
   /       \       /       \
   3       3       3       3
  13       9       5       1
 /   \   /   \   /   \   /   \
 X   4   4   X   4   X   4   X
 N  12  10   N   6   N   2   N

InvertBinaryTree IterateWQueue for above tree:
              
               1
        ______ 7______
       /               \
       2               2
    __ 3__          __11__
   /       \       /       \
   3       3       3       3
   1       5       9      13
 /   \   /   \   /   \   /   \
 X   4   X   4   X   4   4   X
 N   2   N   6   N  10  12   N

InvertBinaryTree IterateWStack for above tree:
              
               1
        ______ 7______
       /               \
       2               2
    __11__          __ 3__
   /       \       /       \
   3       3       3       3
  13       9       5       1
 /   \   /   \   /   \   /   \
 X   4   4   X   4   X   4   X
 N  12  10   N   6   N   2   N

*/
#endif