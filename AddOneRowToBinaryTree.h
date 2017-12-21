#ifndef ADD_ONE_ROW_TO_BINARY_TREE_H
#define ADD_ONE_ROW_TO_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Add One Row To Tree
Given the root of a binary tree, then value v and depth d
, you need to add a row of nodes with value v at the given depth d.
The root node is at depth 1.
The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1
, create two tree nodes with value v as N's left subtree root and right subtree root.
And N's original left subtree should be the left subtree of the new left subtree root
, its original right subtree should be the right subtree of the new right subtree root.
If depth d is 1 that means there is no depth d-1 at all
, then create a tree node with value v as the new root of the whole original tree
, and the original tree is the new root's left subtree.
Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   
v = 1
d = 2
Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    
v = 1
d = 3
Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
*/
class AddOneRowToBinaryTree
{
public:
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(0), right(0) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	AddOneRowToBinaryTree() {}

	TreeNode* Recur(TreeNode* root, int v, int d)
	{
		return recur(root, v, d);
	}
private:
	TreeNode * recur(TreeNode * cur, int v, int d)
	{
		if (d == 1)//means add a parent
		{
			TreeNode * node = new TreeNode(v);
			node->left = cur;
			return node;
		}
		if (d == 0)//means add a parent
		{
			TreeNode * node = new TreeNode(v);
			node->right = cur;
			return node;
		}
		if (cur == NULL) return NULL;
		if (d == 2)//means add a new left and right child of cur
		{
			cur->left = recur(cur->left, v, 1);
			cur->right = recur(cur->right, v, 0);
			return cur;
		}
		//now d>2
		cur->left = recur(cur->left, v, d - 1);
		cur->right = recur(cur->right, v, d - 1);
		return cur;
	}
};
#endif
