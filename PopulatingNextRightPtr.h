#ifndef POPULATING_NEXT_RIGHT_POINTERS_H
#define POPULATING_NEXT_RIGHT_POINTERS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BinaryTrees: Compute right siblings
Leetcode: Populating Next Right Pointers In Each Node
// Given a binary tree
//
// struct TreeLinkNode {
//     TreeLinkNode *left;
//     TreeLinkNode *right;
//     TreeLinkNode *next;
// }
//
// Populate each next pointer to point to its next right node. If there is no
// next right node, the next pointer should be set to NULL.
//
// Initially, all next pointers are set to NULL.
//
// Note:
//
// You may only use constant extra space.
// You may assume that it is a perfect binary tree (ie, all leaves are at the
// same level, and every parent has two children).
//
// For example, given the following perfect binary tree:
//  "     1     "
//  "    / \    "
//  "   2   3   "
//  "  / \ / \  "
//  " 4  5 6  7 "
// After calling your function, the tree should look like:
//  "      1 -> NULL      "
//  "     /  \            "
//  "    2 -> 3 -> NULL   "
//  "   / \  / \          "
//  "  4->5->6->7 -> NULL "
//
// Complexity:
// O(n) time, O(1) space

Leetcode: Populating Next Right Pointers In Each Node II
// Follow up for problem "Populating Next Right Pointers in Each Node".
//
// What if the given tree could be any binary tree? Would your previous
// solution still work?
//
// Note:
//
// You may only use constant extra space.
//
// For example, given the following perfect binary tree:
//  "     1     "
//  "    / \    "
//  "   2   3   "
//  "  / \   \  "
//  " 4  5    7 "
// After calling your function, the tree should look like:
//  "      1 -> NULL      "
//  "     /  \            "
//  "    2 -> 3 -> NULL   "
//  "   / \    \          "
//  "  4-> 5 -> 7 -> NULL "
//
// Complexity:
// O(n) time, O(1) space
*/
class PopulatingNextRightPtr
{
public:
	PopulatingNextRightPtr(){}
	~PopulatingNextRightPtr(){}
	struct TreeLinkNode
	{
		TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL){}
		int val;
		TreeLinkNode * left;
		TreeLinkNode * right;
		TreeLinkNode * next;
	};
	void Connect_PerfectBST(TreeLinkNode * root)
	{
		//top down: from root to leftmost
		while (root && root->left)
		{
			//level order traversal: from leftmost to rightmost
			TreeLinkNode * cur = root;
			while (cur)
			{
				cur->left->next = cur->right;
				cur->right->next = cur->next ? cur->next->left : NULL;
				cur = cur->next;
			}

			root = root->left;
		}
	}
	
	void Connect_NonPerfectBST1(TreeLinkNode * root)
	{
		std::queue<TreeLinkNode *> levelQueue;
		if (root != NULL)
		{
			levelQueue.push(root);
		}
		while (!levelQueue.empty())
		{
			int levelCount = levelQueue.size();
			for (int i = 0; i < levelCount; ++i)
			{
				root = levelQueue.front();
				levelQueue.pop();
				if (i != levelCount - 1)
					root->next = levelQueue.front();
				if (root->left != NULL)
					levelQueue.push(root->left);
				if (root->right != NULL)
					levelQueue.push(root->right);
			}
		}
	}

	void Connect_NonPerfectBST2(TreeLinkNode * root)
	{
		//top down: from root to bottom leftmost non-leaf nodes
		while (root != NULL)
		{
			TreeLinkNode * curNode = root;

			//level traversal: move curNode from left to right (skip leaf nodes) and connect its child level nodes
			while (curNode != NULL)
			{
				//1. connect curNode's left child and right child
				if (curNode->left != NULL && curNode->right != NULL)
					curNode->left->next = curNode->right;

				//2. find curNode's next right non-leaf sibling
				TreeLinkNode * nextNode = curNode->next;
				while (nextNode != NULL && nextNode->left == NULL && nextNode->right == NULL)
					nextNode = nextNode->next;
				if (nextNode == NULL)
					break;

				//3. connect curNode's child with nextNode's child
				TreeLinkNode * childNode = (nextNode->left != NULL) ? nextNode->left : nextNode->right;
				if (curNode->right != NULL)
					curNode->right->next = childNode;
				else if (curNode->left != NULL)
					curNode->left->next = childNode;

				//4. move curNode to nextNode
				curNode = nextNode;
			}

			//if root is a leaf, move it to the next right non-leaf sibling
			while (root != NULL && root->left == NULL && root->right == NULL)
				root = root->next;

			//move root down to the leftmost child
			if (root != NULL)
				root = (root->left != NULL) ? root->left : root->right;
		}
	}

public:
	static void DeleteTree(TreeLinkNode * root)
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
std::string PrintBinaryTree<PopulatingNextRightPtr::TreeLinkNode, std::ostringstream>::selectVal2(int depthY, PopulatingNextRightPtr::TreeLinkNode * n)
{
	std::ostringstream oss;
	if (n->next)
		oss << n->next->val;
	else
		oss << "N";
	return oss.str();
};

/*
PopulatingNextRightPtr PerfectBST:
      
       N
    __ 1__
   /       \
   3       N
   2       3
 /   \   /   \
 5   6   7   N
 4   5   6   7

PopulatingNextRightPtr NonPerfectBST1:
      
       N
    __ 1__
   /       \
   3       N
   2       3
 /   \   /   \
 5   7   X   N
 4   5   N   7

PopulatingNextRightPtr NonPerfectBST2:
      
       N
    __ 1__
   /       \
   3       N
   2       3
 /   \   /   \
 5   7   X   N
 4   5   N   7

*/
#endif