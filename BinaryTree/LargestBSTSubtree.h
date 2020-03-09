#ifndef LARGEST_BST_SUBTREE_H
#define LARGEST_BST_SUBTREE_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>//for std::max
#include <limits>
#include <queue>
#include "Debug.h"
/*
http://buttercola.blogspot.tw/2016/02/leetcode-largest-bst-subtree.html
Leetcode: Largest BST Subtree
Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.
Note:
A subtree must include all of its descendants.
For example,
    10
    / \
   5  15
  / \   \ 
 1   8   7
The largest subtree is
   5
  / \
 1   8
The return value is the subtree's size, which is 3.
Hint:
You can recursively use algorithm similar to 98. Validate Binary Search Tree at each node of the tree, which will result in O(nlogn) time complexity.
see also LargestInRangeBSTSubtree.h
*/
class LargestBSTSubtree
{
public:
	LargestBSTSubtree() {}
	~LargestBSTSubtree() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
private:
	struct data
	{
		data(): isBST(false), size(0), upper(INT_MIN), lower(INT_MAX) {}
		~data() {}
		bool isBST;
		int size;
		int upper;
		int lower;
	};
public:
	int Recur(TreeNode * root)
	{
		int maxCount = 0;
		this->recur(root, maxCount);
		std::cout << "LargestBSTSubtree PostorderRecur: " << maxCount << std::endl;
		return maxCount;
	}
private:
	data recur(TreeNode * cur, int & maxCount)
	{
		data res;
		if (cur == nullptr)
		{
			res.isBST = true;
			return res;
		}

		data left = this->recur(cur->left, maxCount);
		data right = this->recur(cur->right, maxCount);

		//postorder
		res.lower = std::min(cur->val, std::min(left.lower, right.lower));
		res.upper = std::max(cur->val, std::max(left.upper, right.upper));

		if (left.isBST && cur->val > left.upper &&
			right.isBST && cur->val < right.lower)
		{
			res.isBST = true;
			res.size = left.size + right.size + 1;
			maxCount = std::max(maxCount, res.size);
		}
		return res;
	}

public:
	int IteratePostorderStack_HashMap(TreeNode * root)
	{
		if (root == NULL) return 0;
		int maxBSTSize = 0;
		std::stack<TreeNode *> stk;
		std::unordered_map<TreeNode *, std::vector<int>> map;//<node, {isBST,size,lower,upper}>
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			if (cur->left == NULL && cur->right == NULL)//leaf
			{
				map[cur] = { 1, 1, cur->val, cur->val };
			}
			else//non leaf
			{
				if ((cur->left == NULL || (map[cur->left][0] && cur->val > map[cur->left][2])) &&
					(cur->right == NULL || (map[cur->right][0] && cur->val < map[cur->right][3])))//isBST
				{
					int size = (cur->left == NULL ? 0 : map[cur->left][1]) + (cur->right == NULL ? 0 : map[cur->right][1]) + 1;
					int lower = std::min(cur->val, std::min((cur->left == NULL ? INT_MAX : map[cur->left][2]), (cur->right == NULL ? INT_MAX : map[cur->right][2])));
					int upper = std::max(cur->val, std::max((cur->left == NULL ? INT_MIN : map[cur->left][3]), (cur->right == NULL ? INT_MIN : map[cur->right][3])));
					map[cur] = { 1, size, lower, upper };
				}
				else//notBST
				{
					map[cur] = { 0, 0, INT_MAX, INT_MIN };
				}
			}
			maxBSTSize = std::max(maxBSTSize, map[cur][1]);

			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree
			{
				cur = stk.top()->right;
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}
		}

		std::cout << "LargestBSTSubtree IteratePostorderStack_HashMap: " << maxBSTSize << std::endl;
		return maxBSTSize;
	}

	int IteratePostorderStack_LeftSibStk(TreeNode * root)
	{
		if (root == NULL) return 0;
		int maxBSTSize = 0;
		std::stack<TreeNode *> stk;
		std::stack<std::vector<int>> leftSibStk;//<{isBST,size,lower,upper}>
		std::vector<int> curBST;
		std::vector<int> leftBST;//data from left child
		std::vector<int> rightBST;//data from right child
		TreeNode * cur = root;
		while (cur)
		{
			stk.push(cur);
			if (cur->left) cur = cur->left;
			else cur = cur->right;
		}
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			TreeNode * top = cur;
			if (cur->left == NULL && cur->right == NULL)//leaf
			{
				curBST = { 1, 1, cur->val, cur->val };
			}
			else//non leaf
			{
				if ((cur->left == NULL || (leftBST[0] && cur->val > leftBST[2])) &&
					(cur->right == NULL || (rightBST[0] && cur->val < rightBST[3])))//isBST
				{
					int size = (cur->left == NULL ? 0 : leftBST[1]) + (cur->right == NULL ? 0 : rightBST[1]) + 1;
					int lower = std::min(cur->val, std::min((cur->left == NULL ? INT_MAX : leftBST[2]), (cur->right == NULL ? INT_MAX : rightBST[2])));
					int upper = std::max(cur->val, std::max((cur->left == NULL ? INT_MIN : leftBST[3]), (cur->right == NULL ? INT_MIN : rightBST[3])));
					curBST = { 1, size, lower, upper };
				}
				else//notBST
				{
					curBST = { 0, 0, INT_MAX, INT_MIN };
				}
			}
			maxBSTSize = std::max(maxBSTSize, curBST[1]);

			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree
			{
				cur = stk.top()->right;
				if (cur) leftSibStk.push(curBST);
				while (cur)
				{
					stk.push(cur);
					if (cur->left) cur = cur->left;
					else cur = cur->right;
				}
			}

			cur = top;
			if (!stk.empty() && stk.top()->left == cur)//going up from left subtree w/o right sibling
			{
				leftBST = curBST;
			}
			else if (!stk.empty() && stk.top()->right == cur)//going up from right subtree
			{
				rightBST = curBST;
				if (stk.top()->left) leftBST = leftSibStk.top(), leftSibStk.pop();
			}
			else//going (down) to right sibling leaf
			{

			}
		}

		std::cout << "LargestBSTSubtree IteratePostorderStack_LeftSibStk: " << maxBSTSize << std::endl;
		return maxBSTSize;
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
    __10__
   /       \
   2       2
   5      15
 /   \   /   \
 3   3   X   3
 1   8   N   7


LargestBSTSubtree PostorderRecur: 3
LargestBSTSubtree IteratePostorderStack_HashMap: 3
LargestBSTSubtree IteratePostorderStack_LeftSibStk: 3
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 3______                  ______11______
       /               \               /               \
       3               3               3               3
    __ 1__          __ 5__          __ 9__          __15__
   /       \       /       \       /       \       /       \
   X       4       X       4       X       X       4       X
   N       2       N       6       N       N      13       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   5   5   X   X
 N   N   N   N   N   N   N   N   N   N   N   N  12  14   N   N


LargestBSTSubtree PostorderRecur: 12
LargestBSTSubtree IteratePostorderStack_HashMap: 12
LargestBSTSubtree IteratePostorderStack_LeftSibStk: 12
*/
#endif
