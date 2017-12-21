#ifndef CLOSEST_VAL_BST_H
#define CLOSEST_VAL_BST_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>//for std::max
#include <limits>
#include <queue>
#include "Debug.h"
/*
Leetcode: Closest Binary Search Tree Value
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

Leetcode: Closest Binary Search Tree Value II
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
Note:
Given target value is a floating point.
You may assume k is always valid, that is: k <= total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?
Hint:
1. Consider implement these two helper functions
getPredecessor(N), which returns the next smaller node to N
getSuccessor(N), which returns the next larger node to N
2. Try to assume that each node has a parent pointer, it makes the problem much easier
3. Without parent pointer we just need to keep track of the path from the root to the current node using a stack
4. You would need two stacks to track the path in finding predecessor and successor node separately

UseMinHeap: O(n) time, O(k) space
UseTwoStacks: O(k * log n) time
*/
class ClosestValBST
{
public:
	ClosestValBST() {}
	~ClosestValBST() {}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	int Recur(TreeNode * root, double target)
	{
		if (root == nullptr)
			return INT_MAX;
		double minDiff = std::numeric_limits<double>::max();
		int res = 0;
		this->recur(root, target, minDiff, res);
		std::cout << "ClosestValBST Recur for \"" << target << "\": " << res << std::endl;
		return res;
	}
private:
	void recur(TreeNode * cur, double target, double & minDiff, int & res)
	{
		if (cur == nullptr)
			return;

		if ((double)cur->val == target)
		{
			res = cur->val;
			return;
		}
		if (std::abs((double)cur->val - target) < minDiff)
		{
			minDiff = std::abs((double)cur->val - target);
			res = cur->val;
		}

		if (cur->val > target)//too big: go left
			this->recur(cur->left, target, minDiff, res);
		else if (cur->val < target)//too small: go right
			this->recur(cur->right, target, minDiff, res);
	}
public:
	int Iterate(TreeNode * root, double target)
	{
		if (root == nullptr)
			return INT_MAX;
		double minDiff = std::numeric_limits<double>::max();
		int res = 0;

		while (root)
		{
			if ((double)root->val == target)
			{
				res = root->val;
				break;
			}

			if (std::abs((double)root->val - target) < minDiff)
			{
				minDiff = std::abs((double)root->val - target);
				res = root->val;
			}

			if (root->val > target)//too big: go left
				root = root->left;
			else if (root->val < target)//too small: go right
				root = root->right;
		}
		std::cout << "ClosestValBST Iterate for \"" << target << "\": " << res << std::endl;
		return res;
	}

	//II. find K closest
	struct PairLess
	{
		bool operator()(const std::pair<double, int> & a, const std::pair<double, int> & b) const
		{
			return a.first < b.first;
		}
	};
	std::vector<int> UseMaxHeap(TreeNode * root, double target, int k)
	{
		std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, PairLess> maxHeap;
		this->recur(root, target, k, maxHeap);
		std::vector<int> res;
		while (!maxHeap.empty())
			res.push_back(maxHeap.top().second), maxHeap.pop();

		std::cout << "ClosestValBST UseMaxHeap for \"" << target << "\", \"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void recur(TreeNode * root, double target, int k, std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, PairLess> & maxHeap)
	{
		if (root == nullptr)
			return;
		maxHeap.push(std::make_pair(std::abs((double)root->val - target), root->val));
		if ((int)maxHeap.size() > k)
			maxHeap.pop();
		this->recur(root->left, target, k, maxHeap);
		this->recur(root->right, target, k, maxHeap);
	}
public:
	std::vector<int> UseTwoStacks(TreeNode * root, double target, int k)
	{
		int k2 = k;
		std::vector<int> res;
		std::vector<TreeNode *> predStk;//keep track of nodes whose vals are smaller than target in the path from root to target to leaf
		std::vector<TreeNode *> succStk;//keep track of nodes whose vals are greater than target in the path from root to target to leaf
		this->initPredStack(root, target, predStk);
		this->initSuccStack(root, target, succStk);

		std::ostringstream oss;
		oss << "initPredStk: ";
		for (const auto & n : predStk)
			oss << n->val << ",";
		oss << std::endl << "initSuccStk: ";
		for (const auto & n : succStk)
			oss << n->val << ",";
		std::cout << oss.str() << std::endl;

		if (!predStk.empty() && !succStk.empty() && predStk.back()->val == succStk.back()->val)//target exists
			this->getNxtPred(predStk);

		while (k-- > 0)//O(k * log n) time
		{
			if (succStk.empty())
				res.push_back(this->getNxtPred(predStk));
			else if (predStk.empty())
				res.push_back(this->getNxtSucc(succStk));
			else//both succStk and predStk are non-empty
			{
				double succDiff = std::abs((double)succStk.back()->val - target);
				double predDiff = std::abs((double)predStk.back()->val - target);
				if (succDiff < predDiff)
					res.push_back(this->getNxtSucc(succStk));
				else
					res.push_back(this->getNxtPred(predStk));
			}
		}

		std::cout << "ClosestValBST UseTwoStacks for \"" << target << "\", \"" << k2 << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	int getNxtPred(std::vector<TreeNode *> & predStk)
	{
		//pop out next pred
		TreeNode * cur = predStk.back();
		predStk.pop_back();
		int res = cur->val;
		//push all its pred nodes in the LSubRmost path
		cur = cur->left;
		while (cur)
		{
			predStk.push_back(cur);
			cur = cur->right;
		}
		return res;
	}
	int getNxtSucc(std::vector<TreeNode *> & succStk)
	{
		//pop out next succ
		TreeNode * cur = succStk.back();
		succStk.pop_back();
		int res = cur->val;
		//push all its succ nodes in the RSubLmost path
		cur = cur->right;
		while (cur)
		{
			succStk.push_back(cur);
			cur = cur->left;
		}
		return res;
	}
	void initPredStack(TreeNode * root, double target, std::vector<TreeNode *> & predStk)
	{
		//init predStk with all target's predecessors in the path from root to leaf that traverses target (stop at target if found)
		while (root)
		{
			if ((double)root->val == target)
			{
				predStk.push_back(root);
				break;
			}
			else if ((double)root->val < target)
			{
				predStk.push_back(root);
				root = root->right;
			}
			else
				root = root->left;
		}
	}
	void initSuccStack(TreeNode * root, double target, std::vector<TreeNode *> & succStk)
	{
		//init succStk with all target's successors in the path from root to leaf that traverses target (stop at target if found)
		while (root)
		{
			if ((double)root->val == target)
			{
				succStk.push_back(root);
				break;
			}
			else if ((double)root->val > target)
			{
				succStk.push_back(root);
				root = root->left;
			}
			else
				root = root->right;
		}
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


ClosestValBST Recur for "15.5": 16
ClosestValBST Iterate for "15.5": 16
ClosestValBST UseMaxHeap for "9.2", "7": 13, 6, 12, 7, 11, 8, 9
initPredStk: 9,
initSuccStk: 14,12,11,
ClosestValBST UseTwoStacks for "9.2", "7": 9, 8, 11, 7, 12, 6, 13
initPredStk: 3,
initSuccStk: 9,5,3,
ClosestValBST UseTwoStacks for "3", "7": 3, 4, 1, 5, 6, 7, 8
initPredStk: 5,7,
initSuccStk: 9,7,
ClosestValBST UseTwoStacks for "7", "7": 7, 6, 8, 5, 9, 4, 3
initPredStk: 9,12,
initSuccStk: 14,12,
ClosestValBST UseTwoStacks for "12", "7": 12, 11, 13, 14, 9, 8, 16
initPredStk: 9,14,17,
initSuccStk: 17,
ClosestValBST UseTwoStacks for "17", "7": 17, 16, 18, 14, 13, 12, 11
initPredStk: 1,
initSuccStk: 9,5,3,
ClosestValBST UseTwoStacks for "2.5", "3": 3, 1, 4
initPredStk: 9,14,17,
initSuccStk: 18,
ClosestValBST UseTwoStacks for "17.5", "3": 17, 18, 16
initPredStk: 1,
initSuccStk: 9,5,3,
ClosestValBST UseTwoStacks for "1.5", "3": 1, 3, 4
initPredStk: 3,
initSuccStk: 9,5,4,
ClosestValBST UseTwoStacks for "3.5", "3": 3, 4, 5
initPredStk: 3,4,
initSuccStk: 9,5,
ClosestValBST UseTwoStacks for "4.5", "3": 4, 5, 3
initPredStk: 5,
initSuccStk: 9,7,6,
ClosestValBST UseTwoStacks for "5.5", "3": 5, 6, 4
initPredStk: 5,6,
initSuccStk: 9,7,
ClosestValBST UseTwoStacks for "6.5", "3": 6, 7, 5
initPredStk: 5,7,
initSuccStk: 9,8,
ClosestValBST UseTwoStacks for "7.5", "3": 7, 8, 6
initPredStk: 5,7,8,
initSuccStk: 9,
ClosestValBST UseTwoStacks for "8.5", "3": 8, 9, 7
*/
#endif
