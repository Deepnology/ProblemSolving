#ifndef CONVERT_BST_TO_CIRCULAR_DOUBLY_LINKED_LIST_H
#define CONVERT_BST_TO_CIRCULAR_DOUBLY_LINKED_LIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "PrintLinkedList.h"
/*
Elements of programming interview, BST: Convert a BST to a sorted doubly linked list, Convert a sorted doubly linked list into a BST
http://www.geeksforgeeks.org/the-great-tree-list-recursion-problem/
http://cslibrary.stanford.edu/109/TreeListRecursion.html
Aka the great tree-list recursion problem
Write a recursive function treeToList(Node root) that takes an ordered binary tree and rearranges the internal pointers to make a circular doubly linked list out of the tree nodes.
The "previous" pointer should be stored in the "small" field and the "next" pointers should be stored in the "large" field.
The list should be arranged so that the nodes are in increasing order.
Return the head pointer to the new list.
O(n) time, O(h) = O(logn) space for recursion stack

See also ConvertSortedListToBinarySearchTree.h, ConvertSortedArrayToBinarySearchTree.h
*/
class ConvertBSTtoCircularDoublyLinkedList
{
public:
	ConvertBSTtoCircularDoublyLinkedList(){}
	~ConvertBSTtoCircularDoublyLinkedList(){}

	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//1. BST to SortedList Postorder
	TreeNode * InPlaceTreeToListPostorderRecur(TreeNode * root)
	{
		if (root == NULL)
			return NULL;
		TreeNode * leftHead = this->InPlaceTreeToListPostorderRecur(root->left);
		TreeNode * rightHead = this->InPlaceTreeToListPostorderRecur(root->right);

		//post-order: now visit the node
		std::string lh = leftHead ? std::to_string(leftHead->val) : "N";
		std::string rh = rightHead ? std::to_string(rightHead->val) : "N";
		std::cout << root->val << " [" << lh << "," << rh << "]" << std::endl;

		//1. make current node CDLL
		root->left = root;
		root->right = root;

		//2. connect left child CDLL with current node CDLL
		leftHead = this->join2CDLL(leftHead, root);

		//3. connect the result CDLL from 2. with right child CDLL
		leftHead = this->join2CDLL(leftHead, rightHead);

		return leftHead;
	}
private:
	TreeNode * join2CDLL(TreeNode * leftHead, TreeNode * rightHead)
	{
		if (leftHead == NULL)
			return rightHead;
		if (rightHead == NULL)
			return leftHead;

		TreeNode * leftTail = leftHead->left;
		TreeNode * rightTail = rightHead->left;

		//leftHead->right->right->...->leftTail are in increasing order
		//leftTail->left->left->...->leftHead are in decreasing order
		//only leftHead<->leftTail is in reverse order
		//same for rightHead<->rightTail

		//1. connect leftTail to rightHead (in forward order)
		leftTail->right = rightHead;
		rightHead->left = leftTail;

		//2. connect rightTail to leftHead (in reverse order)
		rightTail->right = leftHead;
		leftHead->left = rightTail;

		//now only leftHead<->rightTail is in reverse order
		return leftHead;
	}

	//2. SortedList To BST Inorder
	//see also ConvertSortedListToBinarySearchTree.h
public:
	TreeNode * InPlaceListToTreeInorderRecur(TreeNode * head)
	{
		if (head == NULL)
			return NULL;

		//1. count total number of nodes in CDLL
		TreeNode * tail = head->left;
		tail->right = NULL;//for counting nodes
		TreeNode * cur = head;
		int count = 1;
		while (NULL != (cur = cur->right))
			++count;
		tail->right = head;//restore
		std::cout << "CDLL node count: " << count << std::endl;

		//2. perform inorder traversal
		return this->inOrderRecur(head, 0, count - 1);//O(n)
	}
private:
	TreeNode * inOrderRecur(TreeNode *& cur, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * tmp = this->inOrderRecur(cur, start, middle - 1);

		TreeNode * root = cur;
		cur = cur->right;//equivalent to cur = cur->next
		root->left = tmp;
		root->right = this->inOrderRecur(cur, middle + 1, end);

		return root;
	}
	TreeNode * reversedInOrderRecur(TreeNode *& cur, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * tmp = this->reversedInOrderRecur(cur, start, middle - 1);

		TreeNode * root = cur;
		cur = cur->right;//equivalent to cur = cur->next
		root->right = tmp;
		root->left = this->reversedInOrderRecur(cur, middle + 1, end);

		return root;
	}
public:
	TreeNode * InPlaceListToReversedTreeInorderRecur(TreeNode * head)
	{
		if (head == NULL)
			return NULL;

		//1. count total number of nodes in CDLL
		TreeNode * tail = head->left;
		tail->right = NULL;//for counting nodes
		TreeNode * cur = head;
		int count = 1;
		while (NULL != (cur = cur->right))
			++count;
		tail->right = head;//restore
		std::cout << "CDLL node count: " << count << std::endl;

		//2. perform inorder traversal
		return this->reversedInOrderRecur(head, 0, count - 1);//O(n)
	}

public:
	static void DeleteLinkedList(TreeNode * head)
	{
		std::unordered_set<TreeNode *> map;
		while (head != NULL)
		{
			if (map.find(head) == map.end())//doesn't exist
			{
				map.insert(head);
				head = head->right;
			}
			else//already exist
			{
				break;
			}
		}
		for (std::unordered_set<TreeNode *>::iterator i = map.begin(); i != map.end(); ++i)
		{
			//std::cout << "DeleteListNode: " << (*i)->val << std::endl;
			delete *i;
		}
	}
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
ConvertBSTtoCircularDoublyLinkedList::TreeNode * PrintLinkedList<ConvertBSTtoCircularDoublyLinkedList::TreeNode, std::ostringstream>::GetNextNode(ConvertBSTtoCircularDoublyLinkedList::TreeNode * curNode)
{
	return curNode->right;
}
/*
1 [N,N]
0 [N,1]
4 [N,N]
3 [N,4]
2 [0,3]
7 [N,N]
6 [N,7]
10 [N,N]
9 [N,10]
8 [6,9]
5 [0,6]
CDLL node count: 11
1 [N,N]
0 [N,1]
4 [N,N]
3 [N,4]
2 [0,3]
7 [N,N]
6 [N,7]
10 [N,N]
9 [N,10]
8 [6,9]
5 [0,6]
CDLL node count: 11
ConvertBSTtoCircularDoublyLinkedList and CircularDoublyLinkedListToBST and CircularDoublyLinkedListToReversedBST:
              
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

[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->[9,9]->[10,10]->
  ^___________________________________________________________________________|
              
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

              
               1
        ______ 5______
       /               \
       2               2
    __ 8__          __ 2__
   /       \       /       \
   3       3       3       3
   9       6       3       0
 /   \   /   \   /   \   /   \
 4   X   4   X   4   X   4   X
10   N   7   N   4   N   1   N

*/
#endif