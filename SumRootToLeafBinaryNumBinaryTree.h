#ifndef SUM_ROOT_TO_LEAF_BINARY_NUM_BINARY_TREE_H
#define SUM_ROOT_TO_LEAF_BINARY_NUM_BINARY_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>
/*
Elements of programming interview, BinaryTrees: Sum the leaves in a binary tree encoding integers
Consider a binary tree in which each node contains a digit.
A root-to-leaf path can be associated with a binary number--the MSB is the one at the root.
Design an algorithm to compute the sum of the binary numbers represented by the root-to-leaf paths.

First note that each node encodes an integer.
To compute the integer for a nonroot node u, we take the integer for its parent, double it, and add the bit at u.
Therefore, we can compute the sum of all root to leaf integers via an inorder traversal.

See also SumRootToLeafNums.h
*/
class SumRootToLeafBinaryNumBinaryTree
{
public:
	SumRootToLeafBinaryNumBinaryTree(){}
	~SumRootToLeafBinaryNumBinaryTree(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	int Recur(TreeNode * root)
	{
		int res = 0;
		this->recur(root, 0, res);
		std::cout << "SumRootToLeafBinaryNumBinaryTree Recur: " << res << std::endl;
		return res;
	}
private:
	void recur(TreeNode * root, int num, int & res)
	{
		if (root == nullptr)
			return;
		num = num * 2 + root->val;
		if (root->left == nullptr && root->right == nullptr)//current node is a leaf
		{
			res += num;
			return;
		}
		this->recur(root->left, num, res);
		this->recur(root->right, num, res);
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
                                ______________________________ 1______________________________
                               /                                                               \
                               2                                                               2
                ______________ 0______________                                  ______________ 1______________
               /                               \                               /                               \
               3                               3                               3                               3
        ______ 0______                  ______ 1______                  ______ 0______                  ______ 0______
       /               \               /               \               /               \               /               \
       4               4               X               4               X               4               X               4
    __ 0__          __ 1__          __ N__          __ 1__          __ N__          __ 0__          __ N__          __ 0__
   /       \       /       \       /       \       /       \       /       \       /       \       /       \       /       \
   X       X       X       X       X       X       5       X       X       X       5       5       X       X       X       X
   N       N       N       N       N       N       0       N       N       N       1       0       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   X   6   X   X   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   N   1   N   N   N   N   N   N   N   N   N   N


SumRootToLeafBinaryNumBinaryTree Recur: 126
*/
#endif