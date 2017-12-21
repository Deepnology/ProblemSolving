#ifndef CONVERT_BST_TO_GREATER_TREE_H
#define CONVERT_BST_TO_GREATER_TREE_H
#include "Debug.h"
/*
Leetcode: Convert BST To Greater Tree
Given a Binary Search Tree (BST), convert it to a Greater Tree such that 
every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.
Example:
Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
*/
class ConvertBSTtoGreaterTree
{
public:
	ConvertBSTtoGreaterTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	TreeNode* convertBST(TreeNode* root)
	{
		int prefixSum = 0;
		recur(root, prefixSum);
		return root;
	}
private:
	void recur(TreeNode * cur, int & prefixSum)
	{
		if (cur == NULL) return;
		recur(cur->right, prefixSum);
		cur->val += prefixSum;
		prefixSum = cur->val;
		recur(cur->left, prefixSum);
	}
};
#endif