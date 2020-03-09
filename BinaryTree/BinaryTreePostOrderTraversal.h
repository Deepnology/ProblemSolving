#ifndef BINARY_TREE_POSTORDER_TRAVERSAL_H
#define BINARY_TREE_POSTORDER_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "Debug.h"
#include "PrintBinaryTree.h"
/*
Elements of programming interview, BinaryTrees: Iterate_Stack_InvertedPreorder, Iterate_Stack_PrevNodePtr, Iterate_WParentPtr
Leetcode: Binary Tree Postorder Traversal
//
// Given a binary tree, return the postorder traversal of its nodes' values.
//
// For example:
// Given binary tree {1,#,2,3},
//   1
//    \
//     2
//    /
//   3
// return [3,2,1].
//
// Note: Recursive solution is trivial, could you do it iteratively?
//
// Complexity:
// O(n) time, O(k) space, k is the depth of tree
*/
class BinaryTreePostOrderTraversal
{
public:
	BinaryTreePostOrderTraversal(){}
	~BinaryTreePostOrderTraversal(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
		TreeNode * parent;
	};

	std::vector<int> Iterate_Stack(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		this->PushLRDeepestPathNodes(stk, root);//post order starts from the leaf node in the LRDeepest path

		while (!stk.empty())
		{
			root = stk.top();
			stk.pop();
			res.push_back(root->val);

			if (!stk.empty() && root == stk.top()->left)//going up from left subtree
				this->PushLRDeepestPathNodes(stk, stk.top()->right);//Push LRDeepest Path Nodes in the right subtree
		}

		std::cout << "BinaryTreePostOrderTraversal Iterate_Stack: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void PushLRDeepestPathNodes(std::stack<TreeNode *> & stk, TreeNode * cur)//LRDeepestPath: a path down to the leaf node with branching priority left > right
	{
		while (cur != NULL)
		{
			stk.push(cur);
			if (cur->left != NULL)
				cur = cur->left;//go down left path if it has a left child node
			else
				cur = cur->right;//otherwsie, go down right path
		}
	}

public:
	std::vector<int> Iterate_Stack2(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;

		//perform Mirro-Preorder iteration (go right first), then reverse result
		while (!stk.empty() || root)
		{
			if (root)
			{
				stk.push(root);
				res.push_back(root->val);//preorder: visit the node
				root = root->right;//go right
			}
			else
			{
				root = stk.top();
				stk.pop();
				root = root->left;//go left
			}
		}
		std::reverse(res.begin(), res.end());

		std::cout << "BinaryTreePostOrderTraversal Iterate Stack2: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_Stack3(TreeNode * root)
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;

		//perform Mirro-Preorder iteration (go right first), then reverse result
		if (root)
			stk.push(root);
		while (!stk.empty())
		{
			root = stk.top();
			stk.pop();
			res.push_back(root->val);
			if (root->left)
				stk.push(root->left);//1. push left
			if (root->right)
				stk.push(root->right);//2. push right
		}
		std::reverse(res.begin(), res.end());

		std::cout << "BinaryTreePostOrderTraversal Iterate_Stack3: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Iterate_Stack_Generic(TreeNode * root)
	{
		std::stack<TreeNode*> stk;
		std::vector<int> res;
		std::unordered_set<TreeNode *> visit;
		if (root)
		{
			stk.push(root);
			visit.insert(root);
		}
		while (!stk.empty())
		{
			//push all nodes in the LR deepest path to stk
			while ((stk.top()->left && !visit.count(stk.top()->left)) || (stk.top()->right && !visit.count(stk.top()->right)))
			{
				root = stk.top();
				if (root->left != NULL && !visit.count(root->left))
					stk.push(root->left), visit.insert(root->left);//1. push left
				else if (root->right != NULL && !visit.count(root->right))
					stk.push(root->right), visit.insert(root->right);//2. push right
			}
			//now visit cur node in postorder
			root = stk.top();
			res.push_back(root->val);
			stk.pop();
		}

		std::cout << "BinaryTreePostOrderTraversal Iterate_Stack_Generic: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

public:
	std::vector<int> Iterate_Stack_PrevNodePtr(TreeNode * root)//use stack for ParentPtr
	{
		std::vector<int> res;
		std::stack<TreeNode *> stk;
		if (root)
			stk.push(root);
		TreeNode * prev = nullptr;
		while (!stk.empty())
		{
			TreeNode * cur = stk.top();
			if (!prev || prev->left == cur || prev->right == cur)//going down to left or to right subtree
			{
				if (cur->left)
				{
					stk.push(cur->left);
				}
				else if (cur->right)
				{
					stk.push(cur->right);
				}
				else//leaf node
				{
					//now visit the node
					res.push_back(cur->val);
					stk.pop();
				}
			}
			else if (cur->left == prev)//going up from left subtree
			{
				if (cur->right)//then going down to right subtree
				{
					stk.push(cur->right);
				}
				else
				{
					//now visit the node
					res.push_back(cur->val);
					stk.pop();
				}
			}
			else//cur->right == prev, going up from right subtree
			{
				//now visit the node
				res.push_back(cur->val);
				stk.pop();
			}
			prev = cur;
		}

		std::cout << "BinaryTreePostOrderTraversal Iterate_Stack_PrevNodePtr: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

public:
	std::vector<int> Iterate_WParentPtr(TreeNode * root)
	{
		std::vector<int> res;
		TreeNode * prev = nullptr;
		TreeNode * cur = root;
		TreeNode * next;

		while (cur)
		{
			if (prev == nullptr || prev->left == cur || prev->right == cur)//going down to left or right subtree
			{
				if (cur->left)
				{
					next = cur->left;//go down left
				}
				else if (cur->right)
				{
					next = cur->right;//go down right
				}
				else//leaf node
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->parent;//go up
				}
			}
			else if (cur->left == prev)//going up from left subtree
			{
				if (cur->right)//then going down to right subtree
				{
					next = cur->right;
				}
				else
				{
					//now visit the node
					res.push_back(cur->val);
					next = cur->parent;//go up
				}
			}
			else//cur->right == prev, going up from right subtree
			{
				//now visit the node
				res.push_back(cur->val);
				next = cur->parent;//go up
			}
			prev = cur;
			cur = next;
		}

		std::cout << "BinaryTreePostOrderTraversal Iterate_WParentPtr: " << Debug::ToStr1D<int>()(res) << std::endl;
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

template<>
std::string PrintBinaryTree<BinaryTreePostOrderTraversal::TreeNode, std::ostringstream>::selectVal2(int depthY, BinaryTreePostOrderTraversal::TreeNode * n)
{
	std::ostringstream oss;
	if (n->parent)
		oss << n->parent->val;
	else
		oss << "N";
	return oss.str();
};
/*
       N
    __ 1__
   /       \
   X       1
   N       2
 /   \   /   \
 X   X   2   X
 N   N   3   N


BinaryTreePostOrderTraversal Iterate_Stack: 3, 2, 1
BinaryTreePostOrderTraversal Iterate Stack2: 3, 2, 1
BinaryTreePostOrderTraversal Iterate_Stack3: 3, 2, 1
BinaryTreePostOrderTraversal Iterate_Stack_Generic: 3, 2, 1
BinaryTreePostOrderTraversal Iterate_Stack_PrevNodePtr: 3, 2, 1
BinaryTreePostOrderTraversal Iterate_WParentPtr: 3, 2, 1
              
               N
        ______ 7______
       /               \
       7               7
    __ 3__          __11__
   /       \       /       \
   3       3      11      11
   1       5       9      13
 /   \   /   \   /   \   /   \
 1   1   5   5   9   9  13  13
 0   2   4   6   8  10  12  14


BinaryTreePostOrderTraversal Iterate_Stack: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
BinaryTreePostOrderTraversal Iterate Stack2: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
BinaryTreePostOrderTraversal Iterate_Stack3: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
BinaryTreePostOrderTraversal Iterate_Stack_Generic: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
BinaryTreePostOrderTraversal Iterate_Stack_PrevNodePtr: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
BinaryTreePostOrderTraversal Iterate_WParentPtr: 0, 2, 1, 4, 6, 5, 3, 8, 10, 9, 12, 14, 13, 11, 7
*/
#endif