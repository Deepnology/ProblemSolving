#ifndef TRIM_OUT_OF_BOUNDARY_NODES_BST_H
#define TRIM_OUT_OF_BOUNDARY_NODES_BST_H
#include "Debug.h"
/*
Leetcode: Trim a binary search tree
Given a binary search tree and the lowest and highest boundaries as L and R
, trim the tree so that all its elements lies in [L, R] (R >= L). You might need to change the root of the tree
, so the result should return the new root of the trimmed binary search tree.
Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2
Output: 
    1
      \
       2

Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3
Output: 
      3
     / 
   2   
  /
 1
*/
class TrimOutOfBoundaryNodesBST
{
public:
	TrimOutOfBoundaryNodesBST() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	TreeNode* Recur(TreeNode * root, int L, int R)
	{
		return recur(root, L, R, true);
	}
	TreeNode * recur(TreeNode * cur, int L, int R, bool top)
	{
		if (cur == NULL) return NULL;
		cur->left = recur(cur->left, L, R, false);
		cur->right = recur(cur->right, L, R, false);
		if (cur->val >= L && cur->val <= R)
			return cur;
		//now either cur->val < L OR cur->val > R, need to delete cur
		TreeNode * chd = cur->val < L ? cur->right : cur->left;
		if (!top)
			delete cur;
		return chd;
	}
};
#endif
