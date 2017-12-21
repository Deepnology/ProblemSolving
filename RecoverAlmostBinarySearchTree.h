#ifndef RECOVER_ALMOST_BINARY_SEARCH_TREE_H
#define RECOVER_ALMOST_BINARY_SEARCH_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, BST: Test if a binary tree is an almost BST
Define a binary tree with integer-labeled nodes to be an almost BST if it does not satisfy the BST property
, but there exists a pair of nodes such that swapping the keys at the nodes makes the resulting binary tree a BST.
Design an algorithm that takes as input a binary tree with integer-labeled nodes, and determines if it is an almost BST.
If it is an almost BST, reconstruct the original BST.

Leetcode: Recover Binary Search Tree
// Two elements of a binary search tree (BST) are swapped by mistake.
//
// Recover the tree without changing its structure.
//
// Complexity:
// Recursion or Stack: O(n) time, O(h) space, h is the depth of tree
// Threaded Binary Tree : O(n) time, O(1) space

In-order traversal of a BST must be in the ascending order
*/
class RecoverAlmostBinarySearchTree
{
public:
	RecoverAlmostBinarySearchTree(){}
	~RecoverAlmostBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	void InorderRecur(TreeNode * root)
	{
		TreeNode * preNode = NULL;
		TreeNode * first = NULL;
		TreeNode * second = NULL;
		this->inOrderRecur(root, preNode, first, second);//in-order recursive traversal
		std::swap(first->val, second->val);//now found the first and second nodes. swap them.
	}
private:
	void inOrderRecur(TreeNode * curNode, TreeNode *& preNode, TreeNode *& first, TreeNode *& second)
	{
		if (curNode == NULL)
			return;

		this->inOrderRecur(curNode->left, preNode, first, second);

		//in-order: now visiting the node
		if (preNode && preNode->val > curNode->val)
		{
			if (first == NULL)
				first = preNode;//met the first node (pre) that is not in the ascending order
			second = curNode;//the 2nd update is the second node that is not in the ascending order
		}
		preNode = curNode;//update the pre pointer

		this->inOrderRecur(curNode->right, preNode, first, second);
	}

public:
	void IterateInorderStack(TreeNode * root)
	{
		TreeNode * pre = NULL;
		TreeNode * first = NULL;
		TreeNode * second = NULL;

		std::stack<TreeNode *> stk;

		for (; root != NULL; root = root->left)
			stk.push(root);

		//in-order traversal
		while (!stk.empty())
		{
			root = stk.top();
			stk.pop();

			/*now visiting the current node*/
			if (pre != NULL && pre->val > root->val)
			{
				if (first == NULL)
					first = pre;
				second = root;
			}
			pre = root;

			for (root = root->right; root != NULL; root = root->left)
				stk.push(root);
		}

		std::swap(first->val, second->val);
	}

	void GO_Threaded(TreeNode * root)
	{
		TreeNode * pre = NULL;
		TreeNode * first = NULL;
		TreeNode * second = NULL;

		while (root != NULL)
		{
			if (root->left != NULL)/*current node: has left child*/
			{
				TreeNode * LSubRmost = root->left;
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
					if (pre != NULL && pre->val > root->val)
					{
						if (first == NULL)
							first = pre;//met the first node that is not in the ascending order
						second = root;//the 2nd update is the second node that is not in the ascending order
					}
					pre = root;

					root = root->right;/*move current node to its right child*/
					/*which could be 1. the (new link) in-order successor the current node 2. the original right child of the current node*/
				}
			}
			else/*current node: has no left child*/
			{
				/*now visiting the current node*/
				if (pre != NULL && pre->val > root->val)
				{
					if (first == NULL)
						first = pre;//met the first node that is not in the ascending order
					second = root;//the 2nd update is the second node that is not in the ascending order
				}
				pre = root;

				root = root->right;/*move current node to its right child*/
			}
		}//done while loop

		std::swap(first->val, second->val);
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
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       8       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   4   N

RecoverAlmostBinarySearchTree for the above tree InorderRecur:
              
               1
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       4       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   8   N


              
               1
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       8       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   4   N

RecoverAlmostBinarySearchTree for the above tree IterateInorderStack:
              
               1
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       4       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   8   N


              
               1
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       8       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   4   N

RecoverAlmostBinarySearchTree for the above tree Threaded:
              
               1
        ______ 6______
       /               \
       2               2
    __ 2__          __ 7__
   /       \       /       \
   3       3       X       3
   1       4       N       9
 /   \   /   \   /   \   /   \
 X   X   4   4   X   X   4   X
 N   N   3   5   N   N   8   N

*/
#endif