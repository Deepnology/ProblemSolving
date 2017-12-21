#ifndef LONGEST_UNI_VAL_PATH_BINARY_TREE_H
#define LONGEST_UNI_VAL_PATH_BINARY_TREE_H
#include "Debug.h"
/*
Leetcode: Longest Univalue Path
Given a binary tree, find the length of the longest path where each node in the path has the same value.
This path may or may not pass through the root.
Note: The length of path between two nodes is represented by the number of edges between them.
Example 1:
Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:
2
Example 2:
Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:
2
*/
class LongestUniValPathBinaryTree
{
public:
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	LongestUniValPathBinaryTree() {}

	int Recur(TreeNode * root)
	{
		auto res = recur(root);
		return res.second == 0 ? 0 : res.second - 1;//-1: convert to num of edges
	}
private:
	std::pair<int, int> recur(TreeNode * cur)//<height,diameter(also includes height)>
	{
		if (cur == NULL) return{ 0,0 };
		auto left = recur(cur->left);
		auto right = recur(cur->right);
		std::pair<int, int> res = { 1, std::max(left.second,right.second) };
		if (cur->left && cur->left->val == cur->val)
		{
			res.first = std::max(res.first, left.first + 1);
			res.second = std::max(res.first, res.second);
		}
		if (cur->right && cur->right->val == cur->val)
		{
			res.first = std::max(res.first, right.first + 1);
			res.second = std::max(res.first, res.second);
		}
		if (cur->left && cur->left->val == cur->val
			&& cur->right && cur->right->val == cur->val)
		{
			res.second = std::max(res.second, left.first + 1 + right.first);
		}

		//std::cout << cur->val << ":" << res.first << "," << res.second << std::endl;
		return res;
	}
};
#endif
