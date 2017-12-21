#ifndef BINARY_TREE_MAX_PATH_SUM_H
#define BINARY_TREE_MAX_PATH_SUM_H
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>
/*
Leetcode: Binary Tree Maximum Path Sum
// Given a binary tree, find the maximum path sum.
//
// The path may start and end at any node in the tree.
//
// For example:
// Given the below binary tree,
//
//  "     1     "
//  "    / \    "
//  "   2   3   "
//
//  Return 6.
//
// Complexity:
// O(n) time, O(h) space

See also DiameterOfTree.h
*/
class BinaryTreeMaxPathSum
{
public:
	BinaryTreeMaxPathSum(){}
	~BinaryTreeMaxPathSum(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int GO_Recur(TreeNode * root)
	{
		if (root == NULL)
			return 0;

		int resPath = INT_MIN;//resPath can include at most 1 turn
		this->maxPathSumRecurAt(root, resPath);

		std::cout << "BinaryTreeMaxPathSum is " << resPath << std::endl;
		return resPath;
	}
private:
	std::pair<int, int> recur(TreeNode * cur)//better
	{
		if (cur == NULL) return{ 0,INT_MIN };//note maxDiameter must be INT_MIN !!!
		auto left = recur(cur->left);
		auto right = recur(cur->right);
		int maxHeight = std::max(cur->val, std::max(left.first, right.first) + cur->val);
		int maxDiameter = std::max(maxHeight, std::max(left.first + right.first + cur->val, std::max(left.second, right.second)));//max of 4 !!!
		return{ maxHeight,maxDiameter };
	}
	int maxPathSumRecurAt(TreeNode * cur, int & resPath)
	{
		if (cur == NULL)
			return 0;

		int leftPath = this->maxPathSumRecurAt(cur->left, resPath);//leftPath must include no turns
		int rightPath = this->maxPathSumRecurAt(cur->right, resPath);//rightPath must include no turns

		int curPath = std::max(cur->val, cur->val + std::max(leftPath, rightPath));//curPath must include no turns
		//curPath: max of (cur->val, cur->val + leftPath, cur->val + rightPath)

		resPath = std::max(resPath, std::max(curPath, cur->val + leftPath + rightPath));//resPath can include at most 1 turn
		//resPath: max of (resPath, cur->val, cur->val + leftPath, cur->val + rightPath, cur->val + leftPath + rightPath)

		return curPath;
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
                ______________ 8______________
               /                               \
               2                               2
        ______-4______                  ______ 5______
       /               \               /               \
       3               3               3               3
    __ 7__          __ 3__          __-6__          __ 9__
   /       \       /       \       /       \       /       \
   4       4       4       4       4       4       X       X
   2       4      -2       5       7      -1       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 5   5   X   X   X   X   X   X   X   X   X   X   X   X   X   X
-4   6   N   N   N   N   N   N   N   N   N   N   N   N   N   N


BinaryTreeMaxPathSum is 33
*/

/*
Leetcode: Diameter of binary tree
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.
Example:
Given a binary tree

          1
         / \
        2   3
       / \     
      4   5    

Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
Note: The length of path between two nodes is represented by the number of edges between them. 
*/
class DiameterOfBinaryTree
{
public:
	DiameterOfBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	int Recur(TreeNode* root)
	{
		if (root == NULL)
			return 0;
		auto res = recur(root);
		return res.second - 1;//-1 to convert to num of edges
	}
	std::pair<int, int> recur(TreeNode * cur)
	{
		if (cur == NULL) return{ 0,0 };
		auto left = recur(cur->left);
		auto right = recur(cur->right);
		int maxHeight = std::max(left.first, right.first) + 1;
		int maxDiameter = std::max(left.first + right.first + 1, std::max(left.second, right.second));//max of 3 !!!
		return{ maxHeight,maxDiameter };
	}
};
/*

*/
#endif