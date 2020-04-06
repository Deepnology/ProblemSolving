#ifndef LARGEST_INDEPENDENT_SET_BINARY_TREE_H
#define LARGEST_INDEPENDENT_SET_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "PrintBinaryTree.h"
/*
Leetcode: House Robber III
http://www.geeksforgeeks.org/largest-independent-set-problem/
Given a binary tree, find the size of the largest independent set of nodes.
A set of nodes in a tree is independent if there are no edges directly connecting them in a father-children relation.
Or
A subset of all tree nodes is an independent set if there is no edge between any two nodes of the subset.

Let LISS(X) indicates size of largest independent set of a tree with root X.
LISS(X) = max { 1 + sum of LISS for all grandchildren of X, sum of LISS for all children of X }

There are two possibilities for every node X, either X is a member of the set or not a member.
If X is a member, then the value of LISS(X) is 1 plus LISS of all grandchildren.
If X is not a member, then the value is sum of LISS of all children.

Recur: O(2^n) time
DP: O(n) time
where n is the number of nodes in given binary tree.
*/
class LargestIndependentSetBinaryTree
{
public:
	struct TreeNode
	{
		TreeNode(const int & val, const int liss = 0) : val(val), liss(liss), left(nullptr), right(nullptr){}
		TreeNode(int && val, const int liss = 0) : val(std::move(val)), liss(liss), left(nullptr), right(nullptr){}
		~TreeNode(){}
		int val;
		TreeNode * left;
		TreeNode * right;
		int liss;/*largest independent set size*/
	};
	LargestIndependentSetBinaryTree(){}
	~LargestIndependentSetBinaryTree(){}

	int Recur(TreeNode * root)
	{
		int res = this->recur(root);
		std::cout << "LargestIndependentSetBinaryTree Recur: " << res << std::endl;
		return res;
	}
private:
	int recur(TreeNode * root)
	{
		if (root == nullptr)
			return 0;

		int exclude = this->recur(root->left) + this->recur(root->right);

		int include = 1;
		if (root->left)
			include += this->recur(root->left->left) + this->recur(root->left->right);
		if (root->right)
			include += this->recur(root->right->left) + this->recur(root->right->right);
		
		return std::max(exclude, include);
	}

public:
	int DP_Recur(TreeNode * root)
	{
		int res = this->dp_recur(root);
		std::cout << "LargestIndependentSetBinaryTree DP_Recur: " << res << std::endl;
		return res;
	}
private:
	int dp_recur(TreeNode * root)
	{
		if (root == nullptr)
			return 0;
		if (root->liss != 0)
			return root->liss;

		int exclude = this->dp_recur(root->left) + this->dp_recur(root->right);

		int include = 1;
		if (root->left)
			include += this->dp_recur(root->left->left) + this->dp_recur(root->left->right);
		if (root->right)
			include += this->dp_recur(root->right->left) + this->dp_recur(root->right->right);

		return root->liss = std::max(exclude, include);
	}


public:
	//Leetcode: House Robber III
	int rob(TreeNode * root)
	{
		std::unordered_map<TreeNode*, int> table;
		return this->recur(root, table);
	}
private:
	int recur(TreeNode * root, std::unordered_map<TreeNode*, int> & table)
	{
		if (root == nullptr)
			return 0;
		auto itr = table.find(root);
		if (itr != table.end())
			return itr->second;

		int exclude = this->recur(root->left, table) + this->recur(root->right, table);

		int include = root->val;//accumulate the values instead of count
		if (root->left)
			include += this->recur(root->left->left, table) + this->recur(root->left->right, table);
		if (root->right)
			include += this->recur(root->right->left, table) + this->recur(root->right->right, table);

		return table[root] = std::max(exclude, include);
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

template<>
std::string PrintBinaryTree<LargestIndependentSetBinaryTree::TreeNode, std::ostringstream>::selectVal2(int depth, LargestIndependentSetBinaryTree::TreeNode * n)
{
	return std::to_string(n->liss);
}
/*
LargestIndependentSetBinaryTree Recur: 5
LargestIndependentSetBinaryTree DP_Recur: 5
              
               0
        ______10______
       /               \
       0               0
    __20__          __30__
   /       \       /       \
   0       0       X       0
  40      50       N      60
 /   \   /   \   /   \   /   \
 X   X   0   0   X   X   X   X
 N   N  70  80   N   N   N   N

              
               5
        ______10______
       /               \
       3               1
    __20__          __30__
   /       \       /       \
   1       2       X       1
  40      50       N      60
 /   \   /   \   /   \   /   \
 X   X   1   1   X   X   X   X
 N   N  70  80   N   N   N   N

*/
#endif