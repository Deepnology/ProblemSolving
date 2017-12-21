#ifndef CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H
#define CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H
/*
Leetcode: Convert Sorted List to Binary Search Tree
//
// Given a singly linked list where elements are sorted in ascending order,
// convert it to a height balanced BST.
//
// Complexity:
// Pre-Order, O(nlog(n)) time, O(h) space
// In-Order, O(n) time, O(h) space

See also ConvertBSTtoCircularDoublyLinkedList.h, ConvertSortedArrayToBinarySearchTree.h, CartesianTree.h
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

class ConvertSortedListToBinarySearchTree
{
public:
	ConvertSortedListToBinarySearchTree(){}
	~ConvertSortedListToBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};
	struct ListNode
	{
		ListNode(int v) : val(v), next(NULL){}
		int val;
		ListNode * next;
	};

	//1. pre-order
	TreeNode * PreOrder(ListNode * head)
	{
		if (head == NULL)
			return NULL;

		ListNode * cur = head;
		int count = 1;
		while (NULL != (cur = cur->next))
			++count;

		return this->preOrderRecur(head, 0, count - 1);
	}
private:
	TreeNode * preOrderRecur(ListNode * head, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		int s = middle - start;

		//linearly advance to the middle node between start and end
		ListNode * cur = head;
		while (s > 0)
		{
			cur = cur->next;
			--s;
		}

		TreeNode * root = new TreeNode(cur->val);
		root->left = this->preOrderRecur(head, start, middle - 1);
		root->right = this->preOrderRecur(cur->next, middle + 1, end);

		return root;
	}

	//2. in-order (faster: keep track of middle node)
public:
	TreeNode * InOrder(ListNode * head)
	{
		if (head == NULL)
			return NULL;

		ListNode * cur = head;
		int count = 1;
		while (NULL != (cur = cur->next))
			++count;

		return this->inOrderRecur(head, 0, count - 1);
	}
private:
	TreeNode * inOrderRecur(ListNode *& cur, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * tmp = this->inOrderRecur(cur, start, middle - 1);

		//inorder: cur has been advanced to the middle node
		TreeNode * root = new TreeNode(cur->val);
		root->left = tmp;
		cur = cur->next;//advance cur
		root->right = this->inOrderRecur(cur, middle + 1, end);

		return root;
	}

public:
	TreeNode * IterateInorderStack(ListNode * head)
	{
		if (head == NULL) return NULL;

		int N = 1;
		ListNode * cur = head;
		while (cur = cur->next)
			++N;

		std::stack<std::pair<TreeNode *, std::vector<int>>> stk;//<node,<idx,left,right>>
		TreeNode * root = NULL;

		int left = 0;
		int right = N - 1;
		int mid;
		while (left <= right)//must keep at least 1 element in between inclusive
		{
			mid = (left + right) / 2;
			TreeNode * cur = new TreeNode(0);
			//std::cout << "Push=" << cur->val << ", [" << left << "," << right << "]" << std::endl;
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
			curVisit->val = head->val;//now assign node val when visit inorder
			head = head->next;//advance head when visit inorder
			//std::cout << "Visit=" << curVisit->val << ", [" << left << "," << right << "]" << std::endl;

			left = mid + 1;
			while (left <= right)
			{
				mid = (left + right) / 2;
				TreeNode * cur = new TreeNode(0);
				//std::cout << "Push=" << cur->val << ", [" << left << "," << right << "]" << std::endl;
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
public:
	static void DeleteLinkedList(ListNode * head)
	{
		std::unordered_set<ListNode *> map;
		while (head != NULL)
		{
			if (map.find(head) == map.end())//doesn't exist
			{
				map.insert(head);
				head = head->next;
			}
			else//already exist
			{
				break;
			}
		}
		for (std::unordered_set<ListNode *>::iterator i = map.begin(); i != map.end(); ++i)
		{
			//std::cout << "DeleteListNode: " << (*i)->val << std::endl;
			delete *i;
		}
	}
};
/*
ConvertSortedListToBinarySearchTree Pre-order:
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->[9,9]->[10,10]->NULL
              
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

ConvertSortedListToBinarySearchTree In-order:
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->[9,9]->[10,10]->NULL
              
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

ConvertSortedListToBinarySearchTree In-order IterateStack:
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->[9,9]->[10,10]->NULL
              
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