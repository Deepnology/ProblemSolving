#ifndef MERGE_2_BINARY_TREES_H
#define MERGE_2_BINARY_TREES_H
#include "Debug.h"
/*
Leetcode: Merge Two Binary Trees
Given two binary trees and imagine that when you put one of them to cover the other
, some nodes of the two trees are overlapped while the others are not.
You need to merge them into a new binary tree.
The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node.
Otherwise, the NOT null node will be used as the node of new tree.
Example 1:
Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
Note: The merging process must start from the root nodes of both trees. 
*/
class Merge2BinaryTrees
{
public:
	Merge2BinaryTrees() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	TreeNode* Recur(TreeNode* t1, TreeNode* t2)
	{
		return recur(t1, t2);
	}
private:
	TreeNode * recur(TreeNode * t1, TreeNode * t2)
	{
		if (t1 == NULL) return t2;
		if (t2 == NULL) return t1;
		t1->val += t2->val;
		t1->left = recur(t1->left, t2->left);
		t1->right = recur(t1->right, t2->right);
		return t1;
	}
};
#endif
