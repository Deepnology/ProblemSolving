#ifndef CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE_H
#define CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE_H
/*
Elements of programming interview, BST: Build a BST of min possible height from a sorted array

Leetcode: Convert Sorted Array to Binary Search Tree
//
// Given an array where elements are sorted in ascending order, convert it to
// a height balanced BST.
//
// Pre-Order, O(n) time, O(h) space
// In-Order, O(n) time, O(h) space

Def of BST:
A binary search tree is a binary tree in symmetric order.
Symmetric order means:
1. every node has a key
2. every node's key is
	a. larger than or equal to all keys in its left subtree
	b. smaller than or equal to all keys in its right subtree

See also ConvertSortedListToBinarySearchTree.h, ConvertBSTtoCircularDoublyLinkedList.h, CartesianTree.h
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class ConvertSortedArrayToBinarySearchTree
{
public:
	ConvertSortedArrayToBinarySearchTree(){}
	~ConvertSortedArrayToBinarySearchTree(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//1. pre-order
	TreeNode * PreOrder(const std::vector<int> & inorder)
	{
		if (inorder.empty())
			return NULL;
		
		return this->preOrderRecur(inorder, 0, inorder.size() - 1);
	}
private:
	TreeNode * preOrderRecur(const std::vector<int> & inorder, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * cur = new TreeNode(inorder[middle]);
		cur->left = this->preOrderRecur(inorder, start, middle - 1);
		cur->right = this->preOrderRecur(inorder, middle + 1, end);
		return cur;
	}


	//2. in-order (faster: keep track of middle node)
public:
	TreeNode * InOrder(const std::vector<int> & inorder)
	{
		if (inorder.empty())
			return NULL;

		auto it = inorder.cbegin();
		return this->inOrderRecur(it, 0, inorder.size() - 1);
	}
private:
	TreeNode * inOrderRecur(std::vector<int>::const_iterator & it, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * tmp = this->inOrderRecur(it, start, middle - 1);

		//inorder: itr has been advanced to middle node
		TreeNode * cur = new TreeNode(*it++);//advance itr
		cur->left = tmp;
		cur->right = this->inOrderRecur(it, middle + 1, end);
		return cur;
	}
public:
	TreeNode * IteratePreorderStack(const std::vector<int> & inorder)
	{
		int N = inorder.size();
		if (N == 0) return NULL;

		std::stack<std::pair<TreeNode *, std::pair<int, int>>> stk;//<node,<left,right>>
		TreeNode * root = new TreeNode(inorder[(0 + (N - 1)) / 2]);//(left+right)/2
		stk.push({ root, {0, N - 1} });//[0,N-1] must keep at least 1 element in between inclusive
		while (!stk.empty())
		{
			auto p = stk.top(); stk.pop();
			TreeNode * cur = p.first;
			int left = p.second.first;
			int right = p.second.second;
			std::cout << "Visit=" << cur->val << ", [" << left << "," << right << "]" << std::endl;

			//if (left == right)//[left, right] has 1 element in between inclusive
			//	continue;

			//now [left,right] has at least 2 elements in between inclusive
			int mid = (left + right) / 2;
			
			if (mid + 1 <= right)//[mid+1, right] must keep at least 1 element in between inclusive
			{
				cur->right = new TreeNode(inorder[((mid + 1) + right) / 2]);
				stk.push({ cur->right,{ mid + 1, right } });
			}
			if (mid - 1 >= left)//[left,mid-1] must keep at least 1 element in between inclusive
			{
				cur->left = new TreeNode(inorder[(left + (mid - 1)) / 2]);
				stk.push({ cur->left, {left, mid - 1} });
			}
		}

		return root;
	}

	TreeNode * IterateInorderStack(const std::vector<int> & inorder)
	{
		int N = inorder.size();
		if (N == 0) return NULL;

		std::stack<std::pair<TreeNode *, std::vector<int>>> stk;//<node,<idx,left,right>>
		TreeNode * root = NULL;
		
		int left = 0;
		int right = N - 1;
		int mid;
		while (left <= right)//must keep at least 1 element in between inclusive
		{
			mid = (left + right) / 2;
			TreeNode * cur = new TreeNode(inorder[mid]);
			std::cout << "Push=" << cur->val << ", [" << left << "," << right << "]" << std::endl;
			if (root == NULL)
				root = cur;
			if (!stk.empty())
				stk.top().first->left = cur;
			stk.push({ cur,{ mid, left, right } });
			right = mid - 1;
		}
		while (!stk.empty())
		{
			auto p = stk.top(); stk.pop();
			TreeNode * curVisit = p.first;
			mid = p.second[0];
			left = p.second[1];
			right = p.second[2];
			std::cout << "Visit=" << curVisit->val << ", [" << left << "," << right << "]" << std::endl;

			left = mid + 1;
			while (left <= right)
			{
				mid = (left + right) / 2;
				TreeNode * cur = new TreeNode(inorder[mid]);
				std::cout << "Push=" << cur->val << ", [" << left << "," << right << "]" << std::endl;
				if (curVisit->right == NULL)//connect curVisit to first node which is its right child
					curVisit->right = cur;
				else if (!stk.empty())
					stk.top().first->left = cur;
				stk.push({ cur,{ mid, left, right } });
				right = mid - 1;
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
ConvertSortedArrayToBinarySearchTree Pre-Order:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
              
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


ConvertSortedArrayToBinarySearchTree In-Order:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
              
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


Visit=5, [0,10]
Visit=2, [0,4]
Visit=0, [0,1]
Visit=1, [1,1]
Visit=3, [3,4]
Visit=4, [4,4]
Visit=8, [6,10]
Visit=6, [6,7]
Visit=7, [7,7]
Visit=9, [9,10]
Visit=10, [10,10]
ConvertSortedArrayToBinarySearchTree IteratePreorderStack:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
              
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


Push=5, [0,10]
Push=2, [0,4]
Push=0, [0,1]
Visit=0, [0,1]
Push=1, [1,1]
Visit=1, [1,1]
Visit=2, [0,4]
Push=3, [3,4]
Visit=3, [3,4]
Push=4, [4,4]
Visit=4, [4,4]
Visit=5, [0,10]
Push=8, [6,10]
Push=6, [6,7]
Visit=6, [6,7]
Push=7, [7,7]
Visit=7, [7,7]
Visit=8, [6,10]
Push=9, [9,10]
Visit=9, [9,10]
Push=10, [10,10]
Visit=10, [10,10]
ConvertSortedArrayToBinarySearchTree IterateInorderStack:
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
              
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