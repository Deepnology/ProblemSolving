#ifndef LOWEST_COMMON_ANCESTOR_BINARY_SEARCH_TREE_H
#define LOWEST_COMMON_ANCESTOR_BINARY_SEARCH_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
//#include "PrintBinaryTree.h"
/*
Elements of programming interview, BST: find_Iterate
http://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/

O(height) time
*/
class LowestCommonAncestorBinarySearchTree
{
public:
	LowestCommonAncestorBinarySearchTree(){}
	~LowestCommonAncestorBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	TreeNode * Find_Recur(TreeNode * root, int val1, int val2)
	{
		if (val1 > val2)
			std::swap(val1, val2);
		/*1. find the candidate LCA*/
		TreeNode * res = this->find_Recur(root, val1, val2);
		if (res != NULL)
		{
			/*
			2. check if both val1 and val2 exist
			3 cases:
			1. the LCA isn't either val1 or val2
			2. the LCA is val1 itself
			3. the LCA is val2 itself
			*/
			bool exist1;
			bool exist2;
			if (res->val == val1)
				exist1 = true;
			else
				exist1 = this->exist(res->left, val1);
			if (res->val == val2)
				exist2 = true;
			else
				exist2 = this->exist(res->right, val2);
			if (exist1 && exist2)
			{ }
			else
				res = NULL;
		}
		std::cout << "LowestCommonAncestorBinarySearchTree Find_Recur for \"" << val1 << "," << val2 << "\": ";
		(res == NULL) ? std::cout << "NULL" : std::cout << res->val;
		std::cout << std::endl;
		return res;
	}
private:
	/*
	returns the supposed LCA node whose val is in between val1 and val2
	*/
	TreeNode * find_Recur(TreeNode * curNode, int val1, int val2)
	{
		if (curNode == NULL)
			return NULL;
		if (curNode->val > val1 && curNode->val > val2)//just need curNode->val > val2 only
			return this->find_Recur(curNode->left, val1, val2);
		if (curNode->val < val1 && curNode->val < val2)//just need curNode->val < val1 only
			return this->find_Recur(curNode->right, val1, val2);

		return curNode;//now val1 <= curNode->val <= val2
	}
	TreeNode * find_Iterate(TreeNode * curNode, int val1, int val2)
	{
		while (curNode != NULL)
		{
			if (curNode->val > val1 && curNode->val > val2)//just need curNode->val > val2 only
				curNode = curNode->left;
			else if (curNode->val < val1 && curNode->val < val2)//just need curNode->val < val1 only
				curNode = curNode->right;
			else
				break;//now val1 <= curNode->val <= val2
		}
		return curNode;
	}
	bool exist(TreeNode * root, int val)
	{
		if (root == NULL)
			return false;
		if (root->val == val || this->exist(root->left, val) || this->exist(root->right, val))
			return true;
		return false;
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
LowestCommonAncestorBinarySearchTree Find_Recur for "1,4": 2
LowestCommonAncestorBinarySearchTree Find_Recur for "7,8": 8
LowestCommonAncestorBinarySearchTree Find_Recur for "3,11": NULL
LowestCommonAncestorBinarySearchTree Find_Recur for "7,7": 7
              
               1
        ______ 5______
       /               \
       2               2
    __ 2__          __ 8__
   /       \       /       \
   3       3       3       3
   0       3       6       9
 /   \   /   \   /   \   /   \
 X   4   X   4   X   4   X   4
 N   1   N   4   N   7   N  10

*/
#endif