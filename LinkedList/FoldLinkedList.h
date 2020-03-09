#ifndef FOLD_LINKED_LIST_H
#define FOLD_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, LinkedLists: Implement list zipping
Input:	1->2->3->4->5->6->7->8->9->N
Output:	1->9->2->8->3->7->4->6->5->N

Leetcode: Reorder List
// Given a singly linked list L: L0->L1->...->Ln-1->Ln,
// reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...
//
// You must do this in-place without altering the nodes' values.
//
// For example,
// Given {1,2,3,4}, reorder it to {1,4,2,3}.

1. Recursion

2. Split, Reverse 2nd half, and Merge: O(n) time, O(1) space
a. Find middle node
b. reverse the second part
c. merge first part with reversed second part

3. Random Access Cache: O(n) time, O(n) space
*/
class FoldLinkedList
{
public:
	FoldLinkedList(){}
	~FoldLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};
	//1. recursion
	ListNode * Solve_Recur(ListNode * head)
	{
		return this->nextNodeLeftToRight_Recur(head, head);
	}
private:
	ListNode * nextNodeLeftToRight_Recur(ListNode * head, ListNode * rightNode)
	{
		if (rightNode == nullptr)
			return head;
		ListNode * leftNode = this->nextNodeLeftToRight_Recur(head, rightNode->next);
		/*
		post order: (can be thought as iteration from tail to head)
		now we have the (leftNode, rightNode) pair
		leftNode: going from head to tail
		rightNode: going from tail to head
		perform node connection in 1st half iteration (leftNode: from head to middle, rightNode: from tail to middle)
		and skip 2nd half iteration (leftNode: from middle to tail, rightNode: from middle to head)
		*/
		std::cout << "postorder visit [left,right] = [" << leftNode->val << "," << rightNode->val << "]" << std::endl;
		
		if (leftNode != head || //for 1st half of iteration (leftNode: from head to middle, rightNode: from tail to middle)
			rightNode->next == nullptr)//for (leftNode, rightNode) = (head, tail)
		{
			if (leftNode != rightNode && leftNode->next != rightNode)
			{
				/*
				make this order:
				left->right->(left's next)
				return (right's next) as next leftNode
				*/
				rightNode->next = leftNode->next;
				leftNode->next = rightNode;
				return rightNode->next;
			}
			else//leftNode==rightNode || leftNode->next==rightNode
			{
				/*
				the (leftNode, rightNode) pair is now in the middle of the list:
				1. both leftNode and rightNode are the single middle node, or
				2. both leftNode and rightNode are the middle node pair

				after folded, the middle node should be the tail
				so mark its next nullptr
				*/
				std::cout << "===> Middle Node: " << rightNode->val << std::endl;
				rightNode->next = nullptr;
			}
		}

		//for 2nd half of iteration (leftNode: from middle to tail, rightNode: from middle to head):
		//return head for indication
		return head;
	}

	//2. find middle node, reverse 2nd half list, merge
public:
	ListNode * Solve_Reverse2ndHalf_Merge(ListNode * head)
	{
		if (head == NULL || head->next == NULL)
			return head;

		/*1. find the middle node and split*/
		ListNode * slow = head;
		ListNode * fast = head;
		ListNode * preSlow = NULL;
		while (fast && fast->next)
		{
			preSlow = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		/*
		now slow is the middle node for an odd list,
		OR the right node of middle node pair for an even list.
		(Aka the first node of the 2nd half list.)

		preSlow is the left node of the middle node for an odd list,
		OR the left node of middle node pair for an even list.
		(Aka the last node of the 1st half list.)
		*/
		preSlow->next = NULL;
		ListNode * mid4Odd_midR4Even = slow;
		std::cout << "mid4Odd_midR4Even: " << mid4Odd_midR4Even->val << std::endl;

		/*2. reverse the 2nd half list*/
		ListNode * head2 = this->Reverse_Iterate(mid4Odd_midR4Even);

		/*3. merge 1st half list with reversed 2nd half list*/
		head = this->Merge_Interleave(head, head2);
		
		return head;
	}
private:
	ListNode * Reverse_Iterate(ListNode * head)
	{
		ListNode * dummy = this->pushDummy(head);
		ListNode * curNode = dummy->next;
		while (curNode && curNode->next)
		{
			ListNode * nextNode = curNode->next;
			curNode->next = nextNode->next;
			nextNode->next = dummy->next;
			dummy->next = nextNode;
		}
		return this->popDummy(dummy);
	}
	ListNode * Merge_Interleave(ListNode * head1, ListNode * head2)
	{
		ListNode * dummy = this->pushDummy(head1);
		ListNode * curNode = dummy;
		while (head1 || head2)
		{
			if (head1)
			{
				curNode->next = head1;
				head1 = head1->next;
				curNode = curNode->next;
			}
			if (head2)
			{
				curNode->next = head2;
				head2 = head2->next;
				curNode = curNode->next;
			}
		}
		return this->popDummy(dummy);
	}
private:
	ListNode * pushDummy(ListNode * head)
	{
		ListNode * newNode = new ListNode(-1);
		newNode->next = head;
		return newNode;
	}
	ListNode * popDummy(ListNode * head)
	{
		ListNode * delNode = head;
		head = head->next;
		delete delNode;
		delNode = 0;
		return head;
	}

public:
	ListNode * RandomAccessCache(ListNode * head)
	{
		if (head == NULL)
			return head;
		std::vector<ListNode *> v;
		ListNode * curNode = head;
		while (curNode != NULL)
		{
			v.push_back(curNode);
			curNode = curNode->next;
		}
		int start = 0;
		int end = v.size() - 1;
		while (start < end)
		{
			v[start]->next = v[end];
			v[end]->next = v[start + 1];
			++start;
			--end;
		}
		v[start]->next = NULL;
		return head;
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
postorder visit [left,right] = [1,11]
postorder visit [left,right] = [2,10]
postorder visit [left,right] = [3,9]
postorder visit [left,right] = [4,8]
postorder visit [left,right] = [5,7]
postorder visit [left,right] = [6,6]
===> Middle Node: 6
postorder visit [left,right] = [1,5]
postorder visit [left,right] = [1,4]
postorder visit [left,right] = [1,3]
postorder visit [left,right] = [1,2]
postorder visit [left,right] = [1,1]
FoldLinkedList Recur:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,10]->[10,11]->NULL
[0,1]->[1,11]->[2,2]->[3,10]->[4,3]->[5,9]->[6,4]->[7,8]->[8,5]->[9,7]->[10,6]->NULL

postorder visit [left,right] = [1,10]
postorder visit [left,right] = [2,9]
postorder visit [left,right] = [3,8]
postorder visit [left,right] = [4,7]
postorder visit [left,right] = [5,6]
===> Middle Node: 6
postorder visit [left,right] = [1,5]
postorder visit [left,right] = [1,4]
postorder visit [left,right] = [1,3]
postorder visit [left,right] = [1,2]
postorder visit [left,right] = [1,1]
FoldLinkedList Recur:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,10]->NULL
[0,1]->[1,10]->[2,2]->[3,9]->[4,3]->[5,8]->[6,4]->[7,7]->[8,5]->[9,6]->NULL

mid4Odd_midR4Even: 6
FoldLinkedList Reverse 2nd Half and Merge:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,10]->[10,11]->NULL
[0,1]->[1,11]->[2,2]->[3,10]->[4,3]->[5,9]->[6,4]->[7,8]->[8,5]->[9,7]->[10,6]->NULL

mid4Odd_midR4Even: 6
FoldLinkedList Reverse 2nd Half and Merge:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,10]->NULL
[0,1]->[1,10]->[2,2]->[3,9]->[4,3]->[5,8]->[6,4]->[7,7]->[8,5]->[9,6]->NULL

mid4Odd_midR4Even: 3
FoldLinkedList Reverse 2nd Half and Merge:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL
[0,1]->[1,5]->[2,2]->[3,4]->[4,3]->NULL

mid4Odd_midR4Even: 4
FoldLinkedList Reverse 2nd Half and Merge:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,1]->[1,6]->[2,2]->[3,5]->[4,3]->[5,4]->NULL

FoldLinkedList RandomAccessCache:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL
[0,1]->[1,5]->[2,2]->[3,4]->[4,3]->NULL

FoldLinkedList RandomAccessCache:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,1]->[1,6]->[2,2]->[3,5]->[4,3]->[5,4]->NULL
*/
#endif