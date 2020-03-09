#ifndef VALID_BINARY_SEARCH_TREE_H
#define VALID_BINARY_SEARCH_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, BST: Test if a binary tree satisfies the BST property
Cracking the coding interview: Trees and Graphs
Leetcode:
Given a binary tree, determine if it is a valid binary search tree (BST).
Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Recur: O(n) time, O(h) space
RecurWPrev: O(n) time, O(h) space
IterateThreaded: O(n) time, O(1) space
TopDownBFSQueue: O(n) time, O(n) space
*/
class ValidBinarySearchTree
{
public:
	ValidBinarySearchTree(){}
	~ValidBinarySearchTree(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	bool PreorderRecur(TreeNode * root)
	{
		bool res = this->recur(root, LLONG_MIN, LLONG_MAX);
		std::cout << "ValidBinarySearchTree PreorderRecur: " << res << std::endl;
		return res;
	}
private:
	bool recur(TreeNode * curNode, long long min, long long max)
	{
		if (curNode == nullptr)
			return true;

		//preorder
		if (curNode->val <= min || curNode->val >= max)
			return false;

		return this->recur(curNode->left, min, curNode->val) && 
			this->recur(curNode->right, curNode->val, max);
	}
public:
	bool IteratePreorderStack(TreeNode * root)
	{
		if (root == NULL) return true;
		bool res = true;
		std::stack<std::pair<TreeNode *, std::pair<long long, long long>>> stk;
		stk.push({ root,{ LLONG_MIN,LLONG_MAX } });
		while (!stk.empty())
		{
			auto cur = stk.top(); stk.pop();
			if (cur.first->val <= cur.second.first || cur.first->val >= cur.second.second)
			{
				res = false; break;
			}
			if (cur.first->right)
				stk.push({ cur.first->right,{ cur.first->val, cur.second.second } });
			if (cur.first->left)
				stk.push({ cur.first->left,{ cur.second.first, cur.first->val } });
		}

		std::cout << "ValidBinarySearchTree IteratePreorderStack: " << res << std::endl;
		return res;
	}

public:
	bool InorderRecurWPrev(TreeNode * root)
	{
		long long prev = LLONG_MIN;
		bool res = this->recurWPrev(root, prev);
		std::cout << "ValidBinarySearchTree InorderRecurWPrev: " << res << std::endl;
		return res;
	}
private:
	bool recurWPrev(TreeNode * curNode, long long & prev)
	{
		if (curNode == nullptr)
			return true;

		if (!this->recurWPrev(curNode->left, prev))
			return false;

		//inorder
		if (curNode->val <= prev)
			return false;

		prev = curNode->val;
		return this->recurWPrev(curNode->right, prev);
	}
public:
	bool IterateInorderStack(TreeNode * root)
	{
		if (root == NULL) return true;
		bool res = true;
		long long prev = LLONG_MIN;
		std::stack<TreeNode *> stk;
		TreeNode * cur = root;
		for (; cur; cur = cur->left)
			stk.push(cur);
		while (!stk.empty())
		{
			cur = stk.top(); stk.pop();
			if (cur->val <= prev)
			{
				res = false;
				break;
			}
			prev = cur->val;
			for (cur = cur->right; cur; cur = cur->left)
				stk.push(cur);
		}

		std::cout << "ValidBinarySearchTree IteratePostorderStack: " << res << std::endl;
		return res;
	}

public:
	bool Iterate_Threaded(TreeNode * root)//perform inorder traversal
	{
		bool res = true;
		long long last = LLONG_MIN;
		while (root != NULL)
		{
			if (root->left != NULL)/*current node: has left child*/
			{
				auto LSubRmost = root->left;
				while (LSubRmost->right != NULL && LSubRmost->right != root)
					LSubRmost = LSubRmost->right;/*rightmost node in the left subtree of the current node*/

				if (LSubRmost->right == NULL)/*current node: has no right child of rightmost node in the left subtree*/
				{
					LSubRmost->right = root;/*make right child the in-order successor of the rightmost node*/
					root = root->left;/*move current node to its left child*/
				}
				else/*current node: has right child of rightmost node in the left subtree, which is current node itself*/
				{
					LSubRmost->right = NULL;/*restore right child of rightmost node in the left subtree*/

					/*now visiting the current node*/
					if (last >= root->val)
						res = false;
					last = root->val;

					root = root->right;/*move current node to its right child*/
				}
			}
			else/*current node: has no left child*/
			{
				/*now visiting the current node*/
				if (last >= root->val)
					res = false;
				last = root->val;

				root = root->right;/*move current node to its right child*/
				/*which could be 1. the (new link) in-order successor the current node 2. the original right child of the current node*/
			}
		}

		std::cout << "ValidBinarySearchTree Iterate_Threaded: " << res << std::endl;
		return res;
	}

	bool TopDown_BFS_Queue(TreeNode * root)
	{
		bool res = true;
		std::queue<std::pair<TreeNode *, std::pair<long long, long long> > > levelQueue;//first: TreeNode ptr, second.first: lower bound, second.second: upper bound

		if (root)
		{
			levelQueue.push({ root, { LLONG_MIN, LLONG_MAX } });
		}
		while (!levelQueue.empty())
		{
			auto cur = levelQueue.front();
			levelQueue.pop();

			if (cur.first->val <= cur.second.first || cur.first->val >= cur.second.second)//check if cur node's val is in between lower bound and upper bound
			{
				res = false;
				break;
			}

			if (cur.first->left)
				levelQueue.push({ cur.first->left, { cur.second.first, cur.first->val } });//left child's lower bound: cur node's lower bound, upper bound: cur node's value
			if (cur.first->right)
				levelQueue.push({ cur.first->right, { cur.first->val, cur.second.second } });//right child's lower bound: cur node's value, upper bound: cur node's upper bound
		}

		std::cout << "ValidBinarySearchTree TopDown_BFS_Queue: " << res << std::endl;
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
        ______ 9______
       /               \
       2               2
    __ 5__          __14__
   /       \       /       \
   3       3       3       3
   3       7      12      17
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 1   4   6   8  11  13  16  18


ValidBinarySearchTree PreorderRecur: 1
ValidBinarySearchTree IteratePreorderStack: 1
ValidBinarySearchTree InorderRecurWPrev: 1
ValidBinarySearchTree IteratePostorderStack: 1
ValidBinarySearchTree Iterate_Threaded: 1
ValidBinarySearchTree TopDown_BFS_Queue: 1
              
               1
        ______ 9______
       /               \
       2               2
    __ 5__          __14__
   /       \       /       \
   3       3       3       3
   3       7      12      17
 /   \   /   \   /   \   /   \
 4   4   4   4   4   4   4   4
 1   4   6   8  37  13  16  18


ValidBinarySearchTree PreorderRecur: 0
ValidBinarySearchTree IteratePreorderStack: 0
ValidBinarySearchTree InorderRecurWPrev: 0
ValidBinarySearchTree IteratePostorderStack: 0
ValidBinarySearchTree Iterate_Threaded: 0
ValidBinarySearchTree TopDown_BFS_Queue: 0
*/
#endif