#ifndef CONNECT_BINARY_TREE_LEAVES_H
#define CONNECT_BINARY_TREE_LEAVES_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
/*
Elements of programming interview, BinaryTrees: Form a linked list from the leaves of a binary tree
Given a binary tree, write a function which forms a linked list from the leaves of the binary tree.
The leaves should appear in left-to-right order.

O(n) time, where n is the number of nodes.
*/
class ConnectBinaryTreeLeaves
{
public:
	ConnectBinaryTreeLeaves(){}
	~ConnectBinaryTreeLeaves(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	std::list<TreeNode *> Recur(TreeNode * root)
	{
		std::list<TreeNode *> list;
		this->recur(root, list);

		std::ostringstream oss;
		for (const auto & p : list)
			oss << p->val << ",";
		std::cout << "ConnectBinaryTreeLeaves Recur: " << oss.str() << std::endl;
		return list;
	}
private:
	void recur(TreeNode * cur, std::list<TreeNode* > & list)
	{
		if (cur == NULL)
			return;
		if (cur->left == NULL && cur->right == NULL)
			list.push_back(cur);
		else
		{
			this->recur(cur->left, list);
			this->recur(cur->right, list);
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
        ______ 0______
       /               \
       2               2
    __ 1__          __ 6__
   /       \       /       \
   3       3       3       3
   2       4       7       9
 /   \   /   \   /   \   /   \
 4   X   4   X   X   4   4   X
 3   N   5   N   N   8  10   N


ConnectBinaryTreeLeaves Recur: 3,5,8,10,
*/
#endif