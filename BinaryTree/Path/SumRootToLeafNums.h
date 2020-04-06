#ifndef SUM_ROOT_TO_LEAF_NUMS_H
#define SUM_ROOT_TO_LEAF_NUMS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
/*
Leetcode: Sum Root To Leaf Numbers
//  Given a binary tree containing digits from 0-9 only, each root-to-leaf
//  path could represent a number.
//
//  An example is the root-to-leaf path 1->2->3 which represents the number
//  123.
//
//  Find the total sum of all root-to-leaf numbers.
//
//  For example,
//
//      1
//     / \
//    2   3
//  The root-to-leaf path 1->2 represents the number 12.
//  The root-to-leaf path 1->3 represents the number 13.
//
//  return the sum = 12 + 13 = 25.
//
// Complexity:
// O(n) time, O(h) space

See also SumRootToLeafBinaryNumBinaryTree.h
*/
class SumRootToLeafNums
{
public:
	SumRootToLeafNums(){}
	~SumRootToLeafNums(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int SolveRecur(TreeNode * root)
	{
		int res = 0;
		this->recur(root, 0, res);
		std::cout << "SumRootToLeafNums Recur: " << res << std::endl;
		return res;
	}
private:
	void recur(TreeNode * cur, int path, int & res)
	{
		if (cur == NULL)
			return;
		path = path * 10 + cur->val;
		if (cur->left == NULL && cur->right == NULL)
		{
			res += path;
			return;
		}
		this->recur(cur->left, path, res);
		this->recur(cur->right, path, res);
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
        ______ 5______
       /               \
       2               2
    __ 4__          __ 8__
   /       \       /       \
   3       X       3       3
   1       N       9       4
 /   \   /   \   /   \   /   \
 4   4   X   X   X   X   4   4
 7   2   N   N   N   N   5   1


SumRootToLeafNums Recur: 23104
*/
#endif