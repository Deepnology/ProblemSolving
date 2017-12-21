#ifndef BINARY_TREE_UPSIDE_DOWN_H
#define BINARY_TREE_UPSIDE_DOWN_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Binary tree upside down
http://blog.csdn.net/whuwangyi/article/details/43186045
Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty
, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes.
Return the new root.
For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
   4
  / \
 5   2
    / \
   3   1

=> Perform rotate right starting from the leftmost node
*/
class BinaryTreeUpsideDown
{
public:
	BinaryTreeUpsideDown(){}
	~BinaryTreeUpsideDown(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(0), right(0) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//bottom up: from leftmost node to root
	TreeNode * Recur(TreeNode * root)
	{
		if (root == nullptr)//used only for testing an empty tree
			return nullptr;
		if (root->left == nullptr)//leftmost node
			return root;

		TreeNode * left = root->left;
		TreeNode * right = root->right;
		TreeNode * leftmost = this->Recur(left);
		//postorder, now cur is left, parent is root
		//leftmost is the leftmost node of the entire tree
		
		//std::cout << root->val << std::endl;
		left->left = right;//1
		left->right = root;//2
		root->left = nullptr;//in case root becomes a leaf
		root->right = nullptr;//in case root becomes a leaf
		return leftmost;
	}

	//top down: from root to leftmost node
	TreeNode * Iterate(TreeNode * root)
	{
		//keep parent, parentLeft, parentRight ptrs
		TreeNode * parent = nullptr;
		TreeNode * curNode = root;//curNode: the parentLeft node
		TreeNode * parentRight = nullptr;

		while (curNode)
		{
			TreeNode * left = curNode->left;
			curNode->left = parentRight;//1

			parentRight = curNode->right;//move down to left side
			curNode->right = parent;//2

			//move down to left side
			parent = curNode;
			curNode = left;
		}
		//now parentLeft == nullptr, so parent must be the leftmost node

		return parent;
	}
	TreeNode * Iterate2(TreeNode * root)//better
	{
		TreeNode * parent = nullptr;
		TreeNode * cur = root;
		TreeNode * left = nullptr;
		TreeNode * right = nullptr;
		while (cur)
		{
			left = cur->left;
			cur->left = right;//1

			right = cur->right;
			cur->right = parent;//2

			parent = cur;
			cur = left;
		}

		return parent;
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
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   X   X
 4   5   N   N

BinaryTreeUpsideDown Recur for above tree: 
      
       1
    __ 4__
   /       \
   2       2
   5       2
 /   \   /   \
 X   X   3   3
 N   N   3   1


      
       1
    __ 1__
   /       \
   2       2
   2       3
 /   \   /   \
 3   3   X   X
 4   5   N   N

BinaryTreeUpsideDown Iterate for above tree: 
      
       1
    __ 4__
   /       \
   2       2
   5       2
 /   \   /   \
 X   X   3   3
 N   N   3   1

*/
#endif