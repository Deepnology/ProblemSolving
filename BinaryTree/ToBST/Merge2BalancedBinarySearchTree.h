#ifndef MERGE_2_BALANCED_BINARY_SEARCH_TREE_H
#define MERGE_2_BALANCED_BINARY_SEARCH_TREE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../SortSearchSelect/SortedMatrix/Merge2SortedArrays.h"
/*
Leetcode: All Elements in Two Binary Search Trees
Given two binary search trees root1 and root2.
Return a list containing all the integers from both trees sorted in ascending order.

Elements of programming interview, BST: Merge 2 BSTs
http://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/
http://www.careercup.com/question?id=5261732222074880
Merge inorder traversals: O(M+N) time, O(h) space where h is the max height of the 2 trees
*/
class Merge2BalancedBinarySearchTree
{
public:
	Merge2BalancedBinarySearchTree(){}
	~Merge2BalancedBinarySearchTree(){}
	struct TreeNode
	{
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
		int val;
		TreeNode * left;
		TreeNode * right;
	};

	//1. merge through 2 sorted arrays
	TreeNode * NewBST_From2SortedArrays(TreeNode * root1, TreeNode * root2)
	{
		std::vector<int> inorder1;
		this->BSTtoSortedArray_InorderRecur(root1, inorder1);//O(M)
		int M = inorder1.size();
		std::vector<int> inorder2;
		this->BSTtoSortedArray_InorderRecur(root2, inorder2);//O(N)
		int N = inorder2.size();
		std::vector<int> merged = Merge2SortedArrays().Solve(inorder1, inorder2);//O(M+N)
		return this->SortedArrayToBST_PreorderRecur(merged, 0, M + N - 1);//O(M+N)
	}
private:
	void BSTtoSortedArray_InorderRecur(TreeNode * root, std::vector<int> & inorder)
	{
		if (root == NULL)
			return;
		this->BSTtoSortedArray_InorderRecur(root->left, inorder);
		inorder.push_back(root->val);
		this->BSTtoSortedArray_InorderRecur(root->right, inorder);
	}
	TreeNode * SortedArrayToBST_PreorderRecur(const std::vector<int> & num, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * cur = new TreeNode(num[middle]);
		cur->left = this->SortedArrayToBST_PreorderRecur(num, start, middle - 1);
		cur->right = this->SortedArrayToBST_PreorderRecur(num, middle + 1, end);
		return cur;
	}
    std::vector<int> Merge2BSTtoSortedArray(TreeNode * root1, TreeNode * root2)
    {
        std::stack<TreeNode*> stk1;
        std::stack<TreeNode*> stk2;
        PushStack(root1, stk1);
        PushStack(root2, stk2);
        std::vector<int> res;
        while (!stk1.empty() || !stk2.empty())
        {
            std::stack<TreeNode*> * found;
            if (stk1.empty())
                found = &stk2;
            else if (stk2.empty())
                found = &stk1;
            else
                found = stk1.top()->val < stk2.top()->val ? &stk1 : &stk2;
            TreeNode * cur = found->top(); found->pop();
            res.push_back(cur->val);
            PushStack(cur->right, *found);
        }
        return res;
    }
    void PushStack(TreeNode * cur, std::stack<TreeNode*> & stk)
    {
        for (; cur; cur = cur->left)
            stk.push(cur);
    }


public:
	//2. merge in-place through 2 circular doubly linked lists
	TreeNode * InPlace_FromMerged2SortedDoublyLinkedLists(TreeNode * root1, TreeNode * root2)
	{
		//1. in-place convert root1 to a circular doubly linked list head1 (ConvertBSTtoCircularDoublyLinkedList.h) O(M)
		TreeNode * head1 = this->bSTtoCDLLRecur(root1);
		head1->left->right = nullptr;//disconnect tail to head
		head1->left = nullptr;//disconnect head to tail

		//2. in-place convert root2 to a circular doubly linked list head2 (ConvertBSTtoCircularDoublyLinkedList.h) O(N)
		TreeNode * head2 = this->bSTtoCDLLRecur(root2);
		head2->left->right = nullptr;//disconnect tail to head
		head2->left = nullptr;//disconnect head to tail

		//3. merge 2 sorted doubly linked list head1 and head2 (Merge2SortedLinkedLists.h) O(M+N)
		TreeNode * mergedDLL = this->merge2SortedDLLs(head1, head2);

		//4. in-place convert sorted circular doubly linked list to BST (ConvertBSTtoCircularDoublyLinkedList.h) O(M+N)
		TreeNode * mergedBST = this->dLLtoBSTInorderRecur(mergedDLL);

		return mergedBST;
	}

private:
	TreeNode * bSTtoCDLLRecur(TreeNode * root)
	{
		if (root == NULL)
			return NULL;
		TreeNode * leftHead = this->bSTtoCDLLRecur(root->left);
		TreeNode * rightHead = this->bSTtoCDLLRecur(root->right);

		root->left = root;
		root->right = root;

		leftHead = this->join2CDLL(leftHead, root);
		leftHead = this->join2CDLL(leftHead, rightHead);
		return leftHead;
	}
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

		//connect leftTail to rightHead
		leftTail->right = rightHead;
		rightHead->left = leftTail;

		//connect rightTail to leftHead
		rightTail->right = leftHead;
		leftHead->left = rightTail;

		//now only leftHead<->rightTail is in reverse order
		return leftHead;
	}
	TreeNode * merge2SortedDLLs(TreeNode * head1, TreeNode * head2)
	{
		TreeNode * dummyHead = new TreeNode(-1);
		TreeNode * curNode = dummyHead;
		while (head1 || head2)
		{
			if (head2 == NULL || (head1 && head1->val <= head2->val))
			{
				curNode->right = head1;
				head1->left = curNode;
				head1 = head1->right;
			}
			else
			{
				curNode->right = head2;
				head2->left = curNode;
				head2 = head2->right;
			}
			curNode = curNode->right;
		}
		curNode = dummyHead->right;
		curNode->left = nullptr;
		delete dummyHead;
		dummyHead = nullptr;
		return curNode;
	}
	TreeNode * dLLtoBSTInorderRecur(TreeNode * head)
	{
		if (head == NULL)
			return NULL;
		TreeNode * cur = head;
		int count = 1;
		while (NULL != (cur = cur->right))
			++count;

		return this->inOrderRecur(head, 0, count - 1);//O(n)
	}
	TreeNode * inOrderRecur(TreeNode *& cur, int start, int end)
	{
		if (start > end)
			return NULL;

		int middle = start + (end - start) / 2;
		TreeNode * tmp = this->inOrderRecur(cur, start, middle - 1);

		TreeNode * root = cur;
		root->left = tmp;
		cur = cur->right;
		root->right = this->inOrderRecur(cur, middle + 1, end);

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
Merge2SortedArray for "20, 50, 70, 100, 300", and "40, 80, 120": 20, 40, 50, 70, 80, 100, 120, 300
Merge2BalancedBinarySearchTree root1, root2, merged, merged2:
      
       1
    __100__
   /       \
   2       2
  50      300
 /   \   /   \
 3   3   X   X
20  70   N   N

  
   1
  80
 /   \
 2   2
40  120

              
               1
        ______70______
       /               \
       2               2
    __40__          __100__
   /       \       /       \
   3       3       3       3
  20      50      80      120
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   4
 N   N   N   N   N   N   N  300

              
               1
        ______70______
       /               \
       2               2
    __40__          __100__
   /       \       /       \
   3       3       3       3
  20      50      80      120
 /   \   /   \   /   \   /   \
 X   X   X   X   X   X   X   4
 N   N   N   N   N   N   N  300

*/
#endif