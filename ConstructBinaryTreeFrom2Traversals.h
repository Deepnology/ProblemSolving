#ifndef CONSTRUCT_BINARY_TREE_FROM_2_TRAVERSALS_H
#define CONSTRUCT_BINARY_TREE_FROM_2_TRAVERSALS_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
/*
Elements of programming interview, BinaryTrees: Reconstruct a binary tree from traversal data
Leetcode: Construct Binary Tree from Inorder and Postorder Traversal
// Given inorder and postorder traversal of a tree, construct the binary tree.
//
// Note:
// You may assume that duplicates do not exist in the tree.
//
// Complexity:
// Brute Force, O(n^2) time in worst case of right-skewed tree, O(n) time in best case of left-skewed tree, O(nlog(n)) time in the case of balanced BST, O(h) space
// Hash Table, O(n) time, O(n) space

Leetcode: Construct Binary Tree from Preorder and Inorder Traversal
// Given preorder and inorder traversal of a tree, construct the binary tree.
//
// Note:
// You may assume that duplicates do not exist in the tree.
//
// Complexity:
// Brute Force, O(n^2) time in worst case of left-skewed tree, O(n) time in best case of right-skewed tree, O(nlog(n)) time in the case of balanced BST, O(h) space
// Hash Table, O(n) time, O(n) space

See also ConstructBSTFromTraversal.h
*/
class ConstructBinaryTreeFrom2Traversals
{
public:
	ConstructBinaryTreeFrom2Traversals(){}
	~ConstructBinaryTreeFrom2Traversals(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//1. from inorder and postorder: create nodes in postorder from back (reverse postorder then perform mirror-preorder)
	//the key is to "lookup inorder array to find postorder[cur] node's mid" to decide the inorder indices of its left child [left,mid-1] and right child [mid+1,right] while performing postorder traversal

	//1.1 Brute Force
	TreeNode * BruteForce_InPost(const std::vector<int> & inorder, const std::vector<int> & postorder)
	{
		return this->bruteForceRecur_InPost(inorder, postorder, postorder.size() - 1, 0, inorder.size() - 1);
	}
private:
	TreeNode * bruteForceRecur_InPost(const std::vector<int> & inorder, const std::vector<int> & postorder
		, int last, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle;//inorder[middle] represents the root of inorder[start...end] nodes, which should be equal to postorder[last]
		for (middle = end; middle >= start; --middle)
			if (postorder[last] == inorder[middle])
				break;

		TreeNode * root = new TreeNode(postorder[last]);
		root->left = this->bruteForceRecur_InPost(inorder, postorder, last - (end - middle + 1), start, middle - 1);//left root: postorder[(last-(end-middle+1)+1)-1] (shift left one from middle)
		root->right = this->bruteForceRecur_InPost(inorder, postorder, last - 1, middle + 1, end);//right root: postorder[last-1] (shift left one from last)

		return root;
	}

	//1.2 Hash Table
public:
	TreeNode * HashTable_InPost(const std::vector<int> & inorder, const std::vector<int> & postorder)
	{
		std::unordered_map<int, int> table;
		for (int i = 0; i < (int)inorder.size(); ++i)
		{
			table[inorder[i]] = i;//key: node number, value: inorder index
		}

		return this->hashTableRecur_InPost(inorder, postorder, table, postorder.size() - 1, 0, inorder.size() - 1);
	}
private:
	TreeNode * hashTableRecur_InPost(const std::vector<int> & inorder, const std::vector<int> & postorder
		, std::unordered_map<int, int> & table, int last, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = table[postorder[last]];

		TreeNode * root = new TreeNode(postorder[last]);
		root->left = this->hashTableRecur_InPost(inorder, postorder, table, last - (end - middle + 1), start, middle - 1);
		root->right = this->hashTableRecur_InPost(inorder, postorder, table, last - 1, middle + 1, end);

		return root;
	}

	//1.3 Iterate Stack Hash Table
public:
	TreeNode * IterateStack_InPost(const std::vector<int> & inorder, const std::vector<int> & postorder)
	{
		std::unordered_map<int, int> table;
		for (int i = 0; i < (int)inorder.size(); ++i)
		{
			table[inorder[i]] = i;//key: node number, value: inorder index
		}

		//reverse postorder then perform mirror-preorder
		int N = postorder.size();
		if (N == 0) return NULL;
		std::vector<int> rev_postorder(postorder);
		std::reverse(rev_postorder.begin(), rev_postorder.end());
		std::stack<std::pair<TreeNode*, std::pair<int, int>>> stk;//<node,<left,right>>
		TreeNode * root = new TreeNode(0);
		stk.push({ root,{ 0, N - 1 } });
		int idx = -1;
		while (!stk.empty())
		{
			auto p = stk.top(); stk.pop();
			++idx;
			TreeNode * cur = p.first;
			cur->val = rev_postorder[idx];//update cur node's val in postorder
			int left = p.second.first;
			int right = p.second.second;
			int mid = table[rev_postorder[idx]];
			//[left, mid-1]
			if (mid - 1 >= left)//keep at least 1 element in between inclusive
			{
				cur->left = new TreeNode(0);
				stk.push({ cur->left,{ left,mid - 1 } });
			}
			//[mid+1, right]
			if (mid + 1 <= right)//keep at least 1 element in between inclusive
			{
				cur->right = new TreeNode(0);
				stk.push({ cur->right,{ mid + 1,right } });
			}
		}

		return root;
	}

	//2. from inorder and preorder: create nodes in preorder from front
	//the key is to "lookup inorder array to find preorder[cur] node's mid" to decide the inorder indices of its left child [left,mid-1] and right child [mid+1,right] while performing preorder traversal

	//2.1 Brute Force
public:
	TreeNode * BruteForce_PreIn(const std::vector<int> & preorder, const std::vector<int> & inorder)
	{
		return this->bruteForceRecur_PreIn(preorder, inorder, 0, 0, inorder.size() - 1);
	}
private:
	TreeNode * bruteForceRecur_PreIn(const std::vector<int> & preorder, const std::vector<int> & inorder
		, int first, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle;//inorder[middle] represents the root of inorder[start...end] nodes, which should be equal to preorder[first]
		for (middle = start; middle <= end; ++middle)
		{
			if (preorder[first] == inorder[middle])
				break;
		}

		TreeNode * root = new TreeNode(preorder[first]);
		root->left = this->bruteForceRecur_PreIn(preorder, inorder, first + 1, start, middle - 1);//left root: preorder[first+1] (shift right one from first)
		root->right = this->bruteForceRecur_PreIn(preorder, inorder, first + (middle - start + 1), middle + 1, end);//right root: preorder[(first+(middle-start+1)-1)+1] (shift right one from middle)

		return root;
	}

	//2.2 Hash Table
public:
	TreeNode * HashTable_PreIn(const std::vector<int> & preorder, const std::vector<int> & inorder)
	{
		std::unordered_map<int, int> table;
		for (int i = 0; i < (int)inorder.size(); ++i)
			table[inorder[i]] = i;//key: node number, value: inorder index

		return this->hashTableRecur_PreIn(preorder, inorder, table, 0, 0, inorder.size() - 1);
	}
private:
	TreeNode * hashTableRecur_PreIn(const std::vector<int> & preorder, const std::vector<int> & inorder
		, std::unordered_map<int, int> & table, int first, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = table[preorder[first]];

		TreeNode * root = new TreeNode(preorder[first]);
		root->left = this->hashTableRecur_PreIn(preorder, inorder, table, first + 1, start, middle - 1);
		root->right = this->hashTableRecur_PreIn(preorder, inorder, table, first + (middle - start + 1), middle + 1, end);

		return root;
	}

	//2.3 Iterate Stack Hash Table
public:
	TreeNode * IterateStack_PreIn(const std::vector<int> & preorder, const std::vector<int> & inorder)
	{
		std::unordered_map<int, int> table;
		for (int i = 0; i < (int)inorder.size(); ++i)
		{
			table[inorder[i]] = i;//key: node number, value: inorder index
		}

		int N = preorder.size();
		if (N == 0) return NULL;
		std::stack<std::pair<TreeNode*, std::pair<int, int>>> stk;//<node,<left,right>>
		TreeNode * root = new TreeNode(0);
		stk.push({ root, {0, N - 1} });
		int idx = -1;
		while (!stk.empty())
		{
			auto p = stk.top(); stk.pop();
			++idx;
			TreeNode * cur = p.first;
			cur->val = preorder[idx];//update cur node's val in preorder
			int left = p.second.first;
			int right = p.second.second;
			int mid = table[preorder[idx]];
			//[mid+1, right]
			if (mid + 1 <= right)//keep at least 1 element in between inclusive
			{
				cur->right = new TreeNode(0);
				stk.push({ cur->right, {mid + 1,right} });
			}
			//[left, mid-1]
			if (mid - 1 >= left)//keep at least 1 element in between inclusive
			{
				cur->left = new TreeNode(0);
				stk.push({ cur->left,{ left,mid - 1 } });
			}
		}

		return root;
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
ConstructBinaryTreeFrom2Traversals BruteForce InPost-Order:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
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


ConstructBinaryTreeFrom2Traversals HashTable InPost-Order:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
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


ConstructBinaryTreeFrom2Traversals IterateStack InPost-Order:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
0, 2, 4, 6, 5, 3, 1, 8, 10, 9, 7
                              
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


ConstructBinaryTreeFrom2Traversals BruteForce PreIn-Order:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
                              
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


ConstructBinaryTreeFrom2Traversals HashTable PreIn-Order:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
                              
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


ConstructBinaryTreeFrom2Traversals IterateStack PreIn-Order:
7, 1, 0, 3, 2, 5, 4, 6, 9, 8, 10
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
                              
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