#ifndef K_BALANCED_NODES_BINARY_TREE_H
#define K_BALANCED_NODES_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
/*
Elements of programming interview, BinaryTrees: Find K-unbalanced nodes
Define a node in a binary tree to be k-balanced if the difference in the number of nodes in its left and right subtrees is no more than k.
Given a binary tree, find a node u in the binary tree such that u is not k-balanced, but all of u's descendants are k-balanced.
If no such node exists, return null.

O(n) time, O(h) space

See also BalancedBinaryTree.h
*/
class KBalancedNodesBinaryTree
{
public:
	KBalancedNodesBinaryTree(){}
	~KBalancedNodesBinaryTree(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	TreeNode * FindKUnbalancedNode(TreeNode * root, int k)
	{
		TreeNode * res = this->findRecur(root, k).first;
		std::string node = res == nullptr ? "N" : std::to_string(res->val);
		std::cout << "KBalancedNodesBinaryTree FindKUnbalancedNode for node count diff in left and right subtrees more than \"" << k << "\": " << node << std::endl;
		return res;
	}
private:
	std::pair<TreeNode *, int> findRecur(TreeNode * root, int k)
	{
		if (root == nullptr)
			return{ nullptr, 0 };

		//early return if left subtree is not k-balanced (parent of k-balanced nodes)
		auto left = this->findRecur(root->left, k);
		if (left.first)
			return left;

		//early return if right subtree is not k-balanced (parent of k-balanced nodes)
		auto right = this->findRecur(root->right, k);
		if (right.first)
			return right;

		//now both left and right subtrees are k-balanced
		int count = left.second + right.second + 1;
		if (std::abs(left.second - right.second) > k)//parent is not k-balanced
			return{ root, count };

		return{ nullptr, count };//parent is also k-balanced
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
                                ______________________________34______________________________
                               /                                                               \
                               2                                                               2
                ______________ 6______________                                  ______________ 6______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______27______                  ______56______                  ______32______                  ______21______
       /               \               /               \               /               \               /               \
       4               4               X               4               X               4               X               4
    __28__          __ 0__          __ N__          __ 3__          __ N__          __ 1__          __ N__          __28__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       5       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N      17       N       N       N      41      27       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N  64   N   N   N   N   N   N   N   N   N   N


KBalancedNodesBinaryTree FindKUnbalancedNode for node count diff in left and right subtrees more than "3": 32
*/
#endif