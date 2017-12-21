#ifndef BINARY_TREE_TILT_H
#define BINARY_TREE_TILT_H
#include "Debug.h"
/*
Leetcode: Binary Tree Tilt
Given a binary tree, return the tilt of the whole tree.
The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values.
Null node has tilt 0.
The tilt of the whole tree is defined as the sum of all nodes' tilt.
Example:
Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
Note:
The sum of node values in any subtree won't exceed the range of 32-bit integer.
All the tilt values won't exceed the range of 32-bit integer.
*/
class BinaryTreeTilt
{
public:
	BinaryTreeTilt() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int CountTilt(TreeNode * root)
	{
		int res = 0;
		recur(root, res);
		return res;
	}
	int recur(TreeNode * cur, int & res)
	{
		if (cur == NULL) return 0;
		int left = recur(cur->left, res);
		int right = recur(cur->right, res);

		res += std::abs(left - right);
		return left + right + cur->val;
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
#endif
