#ifndef SECOND_MIN_NODE_IN_BINARY_TREE_H
#define SECOND_MIN_NODE_IN_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Second Minimum Node In a Binary Tree
Given a non-empty special binary tree consisting of nodes with the non-negative value
, where each node in this tree has exactly two or zero sub-node.
If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.
Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
If no such second minimum value exists, output -1 instead.
Example 1:
Input: 
    2
   / \
  2   5
     / \
    5   7
Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input: 
    2
   / \
  2   2
Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
*/
class SecondMinNodeInBinaryTree
{
public:
	SecondMinNodeInBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	int Recur(TreeNode * root)
	{
		int res = INT_MAX;
		recur(root, res);
		if (res == INT_MAX) return -1;
		return res;
	}
	void recur(TreeNode * cur, int & res)
	{
		if (cur == NULL || cur->left == NULL) return;

		if (cur->left->val == cur->right->val)//need to search for both subtrees
		{
			recur(cur->left, res);
			recur(cur->right, res);
		}
		else if (cur->left->val < cur->right->val)//just need to search for left subtree
		{
			res = std::min(res, cur->right->val);
			recur(cur->left, res);
		}
		else//cur->left->val > cur->right->val, just need to search for right subtree
		{
			res = std::min(res, cur->left->val);
			recur(cur->right, res);
		}
	}
};
#endif
