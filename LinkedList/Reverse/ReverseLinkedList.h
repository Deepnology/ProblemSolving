#ifndef REVERSE_LINKED_LIST_H
#define REVERSE_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
/*
Leetcode: Reverse Linked List
Elements of programming interview, LinkedLists: Reverse a singly linked list, Reverse a single sublist

Leetcode: Reverse Linked List II
// Reverse a linked list from position m to n. Do it in-place and in one-pass.
//
// For example:
// Given 1->2->3->4->5->NULL, m = 2 and n = 4,
//
// return 1->4->3->2->5->NULL.
//
// Note:
// Given m, n satisfy the following condition:
// 1 <= m <= n <= length of list.
*/
class ReverseLinkedList
{
public:
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL) {}
		int val;
		ListNode * next;
	};
	/*      __________
	       v          |
	Dummy----->1----->2----->3----->4----->N
	          Cur    Nxt
	        _________________
	       v                 |
	Dummy----->2----->1----->3----->4----->N
	                 Cur    Nxt
	        ________________________
	       v                        |
	Dummy----->3----->2----->1----->4----->N
	                        Cur    Nxt


	Dummy----->4----->3----->2----->1----->N
	                               Cur    Nxt
	*/
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

	/*  ___________
	   v           |
	      N        1----->2----->3----->4----->N
	    Tail      Cur    Nxt
		__________________
	   v                  |
	      1----->N        2----->3----->4----->N
	    Tail             Cur    Nxt
		_________________________
	   v                         |
	      2----->1----->N        3----->4----->N
	    Tail                    Cur    Nxt
		________________________________
	   v                                |
	      3----->2----->1----->N        4----->N
	    Tail                           Cur    Nxt


	      4----->3----->2----->1----->N        N
	    Tail                                  Cur
	*/
	ListNode * Reverse_Iterate2(ListNode * head)
	{
		ListNode * tailNode = NULL;
		ListNode * curNode = head;
		while (curNode)
		{
			ListNode * nextNode = curNode->next;
			curNode->next = tailNode;
			tailNode = curNode;
			curNode = nextNode;
		}
		return tailNode;
	}

	//return the tail of original list, which is also the head of the reversed list
	ListNode * Reverse_Recur(ListNode * curNode)
	{
		if (curNode->next == nullptr)
			return curNode;
		ListNode * tailNode = this->Reverse_Recur(curNode->next);
		std::cout << curNode->val << "," << curNode->next->val << "," << tailNode->val << std::endl;

		//post order: (can be thought as iteration from tail to head)
		//curNode: from one-prior-to-tail node to head node
		//tailNode: always points to the tail node
		curNode->next->next = curNode;

		//this update is useful for curNode at head node ONLY
		curNode->next = nullptr;

		return tailNode;
	}

public:
	ListNode * ReverseBetween(ListNode * head, int m, int n)//front, middle (to reverse), back
	{
		if (m == n)
			return head;
		head = this->pushDummy(head);
		ListNode * preNode = head;
		int k = 1;
		while (k++ < m)
			preNode = preNode->next;
		ListNode * curNode = preNode->next;
		/*now preNode = tailNodeFrontGroup, curNode = headNodeMiddleGroup*/
		std::cout << "pre,cur: " << preNode->val << "," << curNode->val << std::endl;
		while (m++ < n)
		{
			ListNode * nextNode = curNode->next;
			curNode->next = nextNode->next;
			nextNode->next = preNode->next;
			preNode->next = nextNode;
		}
		return this->popDummy(head);
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
5,6,6
4,5,6
3,4,6
2,3,6
1,2,6
pre,cur: 1,2
ReverseLinkedList Iterate, Iterate2, Recur, Between:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,6]->[1,5]->[2,4]->[3,3]->[4,2]->[5,1]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,6]->[1,5]->[2,4]->[3,3]->[4,2]->[5,1]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,6]->[1,5]->[2,4]->[3,3]->[4,2]->[5,1]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,1]->[1,4]->[2,3]->[3,2]->[4,5]->[5,6]->NULL
*/

#endif