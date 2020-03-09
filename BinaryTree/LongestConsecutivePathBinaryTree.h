#ifndef LONGEST_CONSECUTIVE_PATH_BINARY_TREE_H
#define LONGEST_CONSECUTIVE_PATH_BINARY_TREE_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>//for std::max
/*
http://buttercola.blogspot.tw/2015/12/blog-post.html
Leetcode: Binary Tree Longest Consecutive Sequence
Given a binary tree, find the length of the longest consecutive sequence path.
The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections.
The longest consecutive path need to be from parent to child (cannot be the reverse).
   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.

   2
    \
     3
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

Leetcode: Binary Tree Longest Consecutive Sequence II
Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.
Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.
Example 1:
Input:
        1
       / \
      2   3
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
Example 2:
Input:
        2
       / \
      1   3
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
*/
class LongestConsecutivePathBinaryTree
{
public:
	LongestConsecutivePathBinaryTree() {}
	~LongestConsecutivePathBinaryTree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int Recur(TreeNode * root)
	{
		if (root == nullptr)
			return 0;

		int maxLen = 0;
		this->recur(root, root->val + 1, 1, maxLen);

		std::cout << "LongestConsecutivePathBinaryTree Recur: " << maxLen << std::endl;
		return maxLen;
	}
private:
	void recur(TreeNode * cur, int nxtVal, int curLen, int & maxLen)
	{
		if (cur == nullptr)
			return;

		if (cur->val == nxtVal)
			++curLen;
		else
			curLen = 1;

		maxLen = std::max(curLen, maxLen);

		this->recur(cur->left, cur->val + 1, curLen, maxLen);
		this->recur(cur->right, cur->val + 1, curLen, maxLen);
	}

public:
	int Recur2(TreeNode * root)
	{
		if (root == nullptr)
			return 0;

		int maxLen = this->recur2(root, root->val + 1, 1);

		std::cout << "LongestConsecutivePathBinaryTree Recur2: " << maxLen << std::endl;
		return maxLen;
	}
private:
	int recur2(TreeNode * cur, int nxtVal, int curLen)
	{
		if (cur == nullptr)
			return curLen;

		if (cur->val == nxtVal)
			++curLen;
		else
			curLen = 1;

		int left = this->recur2(cur->left, cur->val + 1, curLen);
		int right = this->recur2(cur->right, cur->val + 1, curLen);

		return std::max(curLen, std::max(left, right));
	}

public:
	int CanIncludeATurnRecur(TreeNode * root)
	{
		int res = 0;
		if (root == NULL) return res;
		recur(root, res);
		return res;
	}
private:
	std::vector<int> recur(TreeNode * cur, int & maxLen)
	{
		if (cur == NULL) return{ 0,0 };
		auto left = recur(cur->left, maxLen);
		auto right = recur(cur->right, maxLen);

		std::vector<int> res(2, 1);//[incrLenFromCurToChildren,decrLenFromCurToChildren]
		if (cur->left)
		{
			if (cur->val + 1 == cur->left->val)
				res[0] = std::max(res[0], left[0] + 1);
			if (cur->val - 1 == cur->left->val)
				res[1] = std::max(res[1], left[1] + 1);
		}
		if (cur->right)
		{
			if (cur->val + 1 == cur->right->val)
				res[0] = std::max(res[0], right[0] + 1);
			if (cur->val - 1 == cur->right->val)
				res[1] = std::max(res[1], right[1] + 1);
		}
		maxLen = std::max(maxLen, res[0] + res[1] - 1);
		return res;
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
        ______ 1______
       /               \
       X               2
    __ N__          __ 3__
   /       \       /       \
   X       X       3       3
   N       N       2       4
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   4
 N   N   N   N   N   N   N   5


LongestConsecutivePathBinaryTree Recur: 3
LongestConsecutivePathBinaryTree Recur2: 3

               1
        ______ 2______
       /               \
       X               2
    __ N__          __ 3__
   /       \       /       \
   X       X       3       X
   N       N       2       N
 /   \   /   \   /   \   /   \
 X   X   X   X   4   X   X   X
 N   N   N   N   1   N   N   N


LongestConsecutivePathBinaryTree Recur: 2
LongestConsecutivePathBinaryTree Recur2: 2
*/
#endif