#ifndef TWO_SUM_BINARY_SEARCH_TREE_H
#define TWO_SUM_BINARY_SEARCH_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <algorithm>
/*
Leetcode: Two Sum IV - Input is a BST
Google
http://www.careercup.com/question?id=15320677
Find two nodes from a binary search tree that sum to a target value
Greedy: O(n) time, O(h) space

Refer to TwoSum.h for finding two elements that sum to a target value from a sorted array

Leetcode: Two Sum BSTs
Given two binary search trees, return True if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer target.
*/
class TwoSumBinarySearchTree
{
public:
	TwoSumBinarySearchTree(){}
	~TwoSumBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(0), right(0) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::pair<TreeNode *, TreeNode *> Greedy(TreeNode * root, int target)
	{
		TreeNode * found1 = NULL;
		TreeNode * found2 = NULL;

		std::stack<TreeNode *> LmostStk;
		std::stack<TreeNode *> RmostStk;

		TreeNode * curNode = root;
		while (curNode != NULL)
		{
			LmostStk.push(curNode);
			curNode = curNode->left;
		}
		curNode = root;
		while (curNode != NULL)
		{
			RmostStk.push(curNode);
			curNode = curNode->right;
		}

		while (LmostStk.top() != RmostStk.top())
		{
			//std::cout << LmostStk.top()->val << "," << RmostStk.top()->val << std::endl;
			if (LmostStk.top()->val + RmostStk.top()->val < target)
			{
				TreeNode * curMinNode = LmostStk.top();
				LmostStk.pop();
				if (curMinNode->right != NULL)
				{
					curMinNode = curMinNode->right;
					while (curMinNode != NULL)
					{
						LmostStk.push(curMinNode);
						curMinNode = curMinNode->left;
					}
				}
			}
			else if (LmostStk.top()->val + RmostStk.top()->val > target)
			{
				TreeNode * curMaxNode = RmostStk.top();
				RmostStk.pop();
				if (curMaxNode->left != NULL)
				{
					curMaxNode = curMaxNode->left;
					while (curMaxNode != NULL)
					{
						RmostStk.push(curMaxNode);
						curMaxNode = curMaxNode->right;
					}
				}
			}
			else
			{
				found1 = LmostStk.top();
				found2 = RmostStk.top();
				break;
			}
		}

		std::string res1 = found1 == NULL ? "NULL" : std::to_string(found1->val);
		std::string res2 = found2 == NULL ? "NULL" : std::to_string(found2->val);
		std::cout << "TwoSumBinarySearchTree Greedy for \"" << target << "\": " << res1 << ", " << res2 << std::endl;
		return std::make_pair(found1, found2);
	}

	bool From2BSTs(TreeNode * root1, TreeNode * root2, int target)
	{
		//inorder traversal for root1, reversed inorder traversal for root2
		std::stack<TreeNode*> stk1, stk2;
		for (; root1 != NULL; root1 = root1->left)
			stk1.push(root1);
		for (; root2 != NULL; root2 = root2->right)
			stk2.push(root2);

		while (!stk1.empty() && !stk2.empty())
		{
			int sum = stk1.top()->val + stk2.top()->val;
			if (sum == target)
				return true;
			else if (sum < target) //advance root1
			{
				TreeNode * cur = stk1.top();
				stk1.pop();
				for (cur = cur->right; cur != NULL; cur = cur->left)
					stk1.push(cur);
			}
			else //advance root2
			{
				TreeNode * cur = stk2.top();
				stk2.pop();
				for (cur = cur->left; cur != NULL; cur = cur->right)
					stk2.push(cur);
			}
		}

		return false;
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
TwoSumBinarySearchTree Greedy for "-13": -8, -5
TwoSumBinarySearchTree Greedy for "0": -8, 8
TwoSumBinarySearchTree Greedy for "39": 15, 24
TwoSumBinarySearchTree Greedy for "11": NULL, NULL
              
               1
        ______ 8______
       /               \
       2               2
    __-5__          __20__
   /       \       /       \
   3       3       3       3
  -11       2      13      23
 /   \   /   \   /   \   /   \
 X   4   X   4   X   4   X   4
 N  -8   N   6   N  15   N  24

*/
#endif