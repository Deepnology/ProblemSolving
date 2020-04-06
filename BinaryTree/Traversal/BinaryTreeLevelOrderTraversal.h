#ifndef BINARY_TREE_LEVEL_ORDER_TRAVERSAL_H
#define BINARY_TREE_LEVEL_ORDER_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Print a binary tree in order of increasing depth (TopDown_BFS_Queue, TopDownZigzag_BFS_Queue, BottomUp_BFS_Queue)
Leetcode: Binary Tree Level Order Traversal
// Given a binary tree, return the level order traversal of its nodes' values.
// (ie, from left to right, level by level).
//
// For example:
// Given binary tree {3,9,20,#,#,15,7},
//    3
//   / \
//  9  20
//    /  \
//   15   7
// return its level order traversal as:
// [
//   [3],
//   [9,20],
//   [15,7]
// ]
//
// Complexity:
// DFS O(n) time, O(h) space, h is the height (max depth) of tree
// BFS O(n) time, O(n) space

Leetcode: Binary Tree Level Order Traversal II
// Given a binary tree, return the bottom-up level order traversal of its
// nodes' values. (ie, from left to right, level by level from leaf to root).
//
// For example:
// Given binary tree {3,9,20,#,#,15,7},
// "    3      "
// "   / \     "
// "  9  20    "
// "    /  \   "
// "   15   7  "
// return its bottom-up level order traversal as:
// [
//   [15,7]
//   [9,20],
//   [3],
// ]
//
// Complexity:
// DFS O(n) time, O(h) space, h is the height (max depth) of tree
// BFS O(n) time, O(n) space

Leetcode: Binary Tree Zigzag Level Order Traversal
// Given a binary tree, return the zigzag level order traversal of its nodes'
// values. (ie, from left to right, then right to left for the next level and
// alternate between).
//
//For example:
// Given binary tree {3,9,20,#,#,15,7},
//    3
//   / \
//  9  20
//    /  \
//   15   7
// return its zigzag level order traversal as:
// [
//   [3],
//   [20,9],
//   [15,7]
// ]
//
// Complexity:
// O(n) time, O(n) space
*/
class BinaryTreeLevelOrderTraversal
{
public:
	BinaryTreeLevelOrderTraversal(){}
	~BinaryTreeLevelOrderTraversal(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::vector<std::vector<int> > TopDown_DFS_Recur(TreeNode * root)
	{
		int d = maxDepthRecur(root);
		std::vector<std::vector<int>> res(d, std::vector<int>());
		recur(root, 0, res);

		std::cout << "BinaryTreeLevelOrderTraversal TopDown DFS Recur: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	int maxDepthRecur(TreeNode * cur)
	{
		if (cur == NULL)
			return 0;
		return std::max(this->maxDepthRecur(cur->left), this->maxDepthRecur(cur->right)) + 1;
	}
	void recur(TreeNode * root, int d, std::vector<std::vector<int>>&level)
	{
		if (root == NULL) return;
		level[d].push_back(root->val);
		recur(root->left, d + 1, level);
		recur(root->right, d + 1, level);
	}

public:
	std::vector<std::vector<int> > TopDown_BFS_Queue(TreeNode * root)
	{
		std::vector<std::vector<int> > res;
		std::queue<TreeNode *> levelQueue;
		if (root != NULL)
		{
			levelQueue.push(root);
			res.push_back(std::vector<int>());
		}
		while (!levelQueue.empty())
		{
			int levelCount = levelQueue.size();
			for (int i = 0; i < levelCount; ++i)
			{
				TreeNode * cur = levelQueue.front();
				levelQueue.pop();
				res.back().push_back(cur->val);
				if (cur->left != NULL)
					levelQueue.push(cur->left);
				if (cur->right != NULL)
					levelQueue.push(cur->right);
			}
			if (!levelQueue.empty())
				res.push_back(std::vector<int>());
		}

		std::cout << "BinaryTreeLevelOrderTraversal TopDown BFS Queue: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<std::vector<int> > TopDown_BFS_Queue2(TreeNode * root)
	{
		std::vector<std::vector<int> > res;
		std::queue<TreeNode *> levelQueue;
		int nodeCountCurLevel;
		if (root != NULL)
		{
			levelQueue.push(root);
			nodeCountCurLevel = 1;
			res.push_back(std::vector<int>());
		}
		while (!levelQueue.empty())
		{
			TreeNode * cur = levelQueue.front();
			levelQueue.pop();
			--nodeCountCurLevel;

			res.back().push_back(cur->val);

			if (cur->left != NULL)
				levelQueue.push(cur->left);
			if (cur->right != NULL)
				levelQueue.push(cur->right);

			if (nodeCountCurLevel == 0)
			{
				nodeCountCurLevel = levelQueue.size();
				if (nodeCountCurLevel != 0)
					res.push_back(std::vector<int>());
			}
		}

		std::cout << "BinaryTreeLevelOrderTraversal TopDown BFS Queue2: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<std::vector<int> > TopDown_BFS_Queue3(TreeNode * root)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		std::queue<TreeNode *> levelQueue;

		if (root != NULL)
		{
			levelQueue.push(root);
			levelQueue.push(NULL);//end of the 1st level
		}

		while (!levelQueue.empty())
		{
			TreeNode * cur = levelQueue.front();
			levelQueue.pop();

			if (cur == NULL)//end of current level
			{
				res.push_back(path);
				path.clear();

				//push NULL to the end of level queue to indicate the end of the next level
				if (!levelQueue.empty())
					levelQueue.push(NULL);
			}
			else
			{
				path.push_back(cur->val);

				//push the next level nodes to the end of level queue
				if (cur->left != NULL)
					levelQueue.push(cur->left);
				if (cur->right != NULL)
					levelQueue.push(cur->right);
			}
		}

		std::cout << "BinaryTreeLevelOrderTraversal TopDown BFS Queue3: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}


	std::vector<std::vector<int> > BottomUp_DFS_Recur(TreeNode * root)//for each level from bottom, build path
	{
		int d = maxDepthRecur(root);
		std::vector<std::vector<int>> res(d, std::vector<int>());
		recur(root, 0, res);

		//reverse top down to be bottom up
		std::reverse(res.begin(), res.end());
		std::cout << "BinaryTreeLevelOrderTraversal BottomUp DFS Recur: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<std::vector<int> > BottomUp_BFS_Queue(TreeNode * root)
	{
		std::vector<std::vector<int> > res = this->TopDown_BFS_Queue(root);

		//reverse top down to be bottom up
		std::reverse(res.begin(), res.end());

		std::cout << "BinaryTreeLevelOrderTraversal BottomUp BFS Queue: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<std::vector<int> > TopDownZigzag_BFS(TreeNode * root)
	{
		std::vector<std::vector<int> > res;
		std::queue<TreeNode *> que;
		if (root != NULL)
		{
			que.push(root);
			res.push_back(std::vector<int>());
		}
		bool leftToRight = true;
		while (!que.empty())
		{
			std::stack<TreeNode *> stk;
			int levelCount = que.size();
			for (int i = 0; i < levelCount; ++i)
			{
				TreeNode * cur = que.front();
				que.pop();
				res.back().push_back(cur->val);

				if (leftToRight)//next level must be RightToLeft
				{
					if (cur->left != NULL)
						stk.push(cur->left);
					if (cur->right != NULL)
						stk.push(cur->right);
				}
				else//RightToLeft: next level must be LeftToRight
				{
					if (cur->right != NULL)
						stk.push(cur->right);
					if (cur->left != NULL)
						stk.push(cur->left);
				}
			}
			leftToRight = !leftToRight;
			if (!que.empty() || !stk.empty())
			{
				res.push_back(std::vector<int>());
				while (!stk.empty())
					que.push(stk.top()), stk.pop();
			}
		}

		std::cout << "BinaryTreeLevelOrderTraversal TopDownZigzag BFS: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	std::vector<std::vector<int> > TopDownZigzag_BFS_2Stack(TreeNode * root)//use 2 stacks
	{
		std::vector<std::vector<int> > res;
		std::stack<TreeNode *> curLevelStk;
		std::stack<TreeNode *> nxtLevelStk;
		
		if (root != NULL)
		{
			curLevelStk.push(root);
			res.push_back(std::vector<int>());
		}
		bool leftToRight = true;

		while (!curLevelStk.empty())
		{
			while (!curLevelStk.empty())
			{
				TreeNode * cur = curLevelStk.top();
				curLevelStk.pop();

				res.back().push_back(cur->val);

				if (leftToRight)
				{
					if (cur->left != NULL)
						nxtLevelStk.push(cur->left);
					if (cur->right != NULL)
						nxtLevelStk.push(cur->right);
				}
				else
				{
					if (cur->right != NULL)
						nxtLevelStk.push(cur->right);
					if (cur->left != NULL)
						nxtLevelStk.push(cur->left);
				}
			}

			if (!nxtLevelStk.empty())
			{
				res.push_back(std::vector<int>());
				leftToRight = !leftToRight;
				std::swap(nxtLevelStk, curLevelStk);
			}
		}

		std::cout << "BinaryTreeLevelOrderTraversal TopDownZigzag BFS 2Stack: " << Debug::ToStr1D<int>()(res) << std::endl;
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
    __ 3__
   /       \
   2       2
   9      20
 /   \   /   \
 X   X   3   3
 N   N  15   7


 BinaryTreeLevelOrderTraversal TopDown DFS Recur: [3], [9,20], [15,7]
 BinaryTreeLevelOrderTraversal TopDown BFS Queue: [3], [9,20], [15,7]
 BinaryTreeLevelOrderTraversal TopDown BFS Queue2: [3], [9,20], [15,7]
 BinaryTreeLevelOrderTraversal TopDown BFS Queue3: [3], [9,20], [15,7]
 BinaryTreeLevelOrderTraversal BottomUp DFS Recur: [15,7], [9,20], [3]
 BinaryTreeLevelOrderTraversal TopDown BFS Queue: [3], [9,20], [15,7]
 BinaryTreeLevelOrderTraversal BottomUp BFS Queue: [15,7], [9,20], [3]
 BinaryTreeLevelOrderTraversal TopDownZigzag BFS: [3], [20,9], [15,7]
 BinaryTreeLevelOrderTraversal TopDownZigzag BFS 2Stack: [3], [20,9], [15,7]
*/
#endif