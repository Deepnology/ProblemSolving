#ifndef CONSTRUCT_BINARY_TREE_FROM_TRAVERSAL_H
#define CONSTRUCT_BINARY_TREE_FROM_TRAVERSAL_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
/*
Elements of programming interview, BinaryTrees: Reconstruct a binary tree from a preorder traversal with marker
Design an O(n) time algorithm for reconstructing a binary tree from a preorder traversal visit sequence that uses null to mark empty children.
How would you modify your resconstruction algorithm if the sequence corresponded to a postorder or inorder traversal?

Reconstructing from an inorder traversal is impossible, even with the null markers.
This is because every binary tree that yields (v0, v1, ..., vn-1) on an inorder traversal has a modified sequence of (null, v0, null, v1, null, v2, ...., null, vn-1, null).
An inorder traversal order is not enough to uniquely reconstruct a binary tree, so the inorder sequence with markers will also be insufficient.
If all we want is a binary tree that yields the given sequence, we can simply return a completely right-skewed tree, i.e., its root is v0, left child empty, and right child is reconstructed recursively from (v1, v2, ..., vn-1).

similar Leetcode: Serialize and Deserialize Binary Tree
see also VerifyPreOrderTraversalBinaryTree.h, VerifyPostOrderTraversalBinaryTree.h, VerifyLevelOrderTraversalBinaryTree.h
*/
class ConstructBinaryTreeFromTraversal
{
public:
	ConstructBinaryTreeFromTraversal(){}
	~ConstructBinaryTreeFromTraversal(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//iterate preorder from back, push each node in stack
	//the top 2 from stack would be left and right child of cur node, respectively
	TreeNode * PreOrder(const std::vector<TreeNode *> & preorder)
	{
		/*
		std::stack<TreeNode *> stk;
		int N = preorder.size();
		for (int i = N - 1; i >= 0; --i)
		{
			TreeNode * cur = preorder[i];
			if (cur != nullptr)
			{
				TreeNode * left = stk.top();
				stk.pop();
				TreeNode * right = stk.top();
				stk.pop();
				cur->left = left;
				cur->right = right;
			}
			stk.push(cur);
		}
		return stk.top();
		*/
		
		int index = 0;
		return preorderRecur(preorder, index);
	}
	TreeNode * preorderRecur(const std::vector<TreeNode *> & preorder, int & cur)
	{
		int N = preorder.size();
		if (cur >= N || preorder[cur] == nullptr)
			return nullptr;
		TreeNode * root = preorder[cur];
		++cur;
		root->left = preorderRecur(preorder, cur);
		++cur;
		root->right = preorderRecur(preorder, cur);
		return root;
	}
	//iterate postorder from front, push each node in stack
	//the top 2 from stack would be right and left child of cur node, respectively
	TreeNode * PostOrder(const std::vector<TreeNode *> & postorder)
	{
		/*
		std::stack<TreeNode *> stk;
		int N = postorder.size();
		for (int i = 0; i < N; ++i)
		{
			TreeNode * cur = postorder[i];
			if (cur != nullptr)
			{
				TreeNode * right = stk.top();
				stk.pop();
				TreeNode * left = stk.top();
				stk.pop();
				cur->left = left;
				cur->right = right;
			}
			stk.push(cur);
		}
		return stk.top();
		*/

		int index = postorder.size() - 1;
		return postorderRecur(postorder, index);
	}
	TreeNode * postorderRecur(const std::vector<TreeNode *> & postorder, int & cur)
	{
		if (cur < 0 || postorder[cur] == nullptr)
			return nullptr;
		TreeNode * root = postorder[cur];
		--cur;
		root->right = postorderRecur(postorder, cur);
		--cur;
		root->left = postorderRecur(postorder, cur);
		return root;
	}

	//levelorder array is the way leetcode to serialize a binary tree
	//we cannot use 2*index+1 and 2*index+2 to lookup left and right child from this levelorder array bc this levelorder array is not a full-sized binary tree
	TreeNode * LevelOrder(const std::vector<TreeNode *> & levelorder)
	{
		int N = levelorder.size();
		int leaf = 1;
		for (int i = 0; i < N; ++i)
		{
			if (levelorder[i])
			{
				levelorder[i]->left = levelorder[leaf++];
				levelorder[i]->right = levelorder[leaf++];
			}
		}
		std::cout << "leaf=" << leaf << std::endl;
		return levelorder[0];
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
ConstructBinaryTreeFromTraversal PreOrder for "7, 1, 0, N, N, 3, 2, N, N, 5, 4, N, N, 6, N, N, 9, 8, N, N, 10, N, N":
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBinaryTreeFromTraversal PostOrder for "N, N, 0, N, N, 2, N, N, 4, N, N, 6, 5, 3, 1, N, N, 8, N, N, 10, 9, 7":
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N


ConstructBinaryTreeFromTraversal LevelOrder for "7, 1, 9, 0, 3, 8, 10, N, N, 2, 5, N, N, N, N, N, N, 4, 6, N, N, N, N":
                              
                               1
                ______________ 7______________
               /                               \
               2                               2
        ______ 1______                  ______ 9______
       /               \               /               \
       3               3               3               3
    __ 0__          __ 3__          __ 8__          __10__
   /       \       /       \       /       \       /       \
   X       X       4       4       X       X       X       X
   N       N       2       5       N       N       N       N
 /   \   /   \   /   \   /   \   /   \   /   \   /   \   /   \
 X   X   X   X   X   X   5   5   X   X   X   X   X   X   X   X
 N   N   N   N   N   N   4   6   N   N   N   N   N   N   N   N
*/
#endif