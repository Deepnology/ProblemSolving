#ifndef REMOVE_KTH_NODE_FROM_END_LINKED_LIST_H
#define REMOVE_KTH_NODE_FROM_END_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
/*
Elements of programming interview, LinkedLists: Remove the k-th last element from a list
Leetcode: Remove Nth Node From End Of List
// Given a linked list, remove the nth node from the end of list and return
// its head.
//
// For example,
//
// Given linked list: 1->2->3->4->5, and n = 2.
//
// After removing the second node from the end, the linked list becomes
// 1->2->3->5.
// Note:
// Given n will always be valid.
// Try to do this in one pass.
//
// Complexity:
// O(n) time
*/
class RemoveKthNodeFromEndLinkedList
{
public:
	RemoveKthNodeFromEndLinkedList(){}
	~RemoveKthNodeFromEndLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * GO(ListNode * head, int K)
	{
		if (head == nullptr)
			return head;

		/*1. find KthFromBegin*/
		ListNode * KthFromBegin = head;
		while (K-- > 0)
			KthFromBegin = KthFromBegin->next;

		/*2. find (PreKthFromEnd, KthFromEnd) pair from KthFromBegin*/
		ListNode * PreKthFromEnd = nullptr;
		ListNode * KthFromEnd = head;
		while (KthFromBegin)
		{
			KthFromBegin = KthFromBegin->next;

			PreKthFromEnd = KthFromEnd;
			KthFromEnd = KthFromEnd->next;
		}

		/*3. remove KthFromEnd*/
		ListNode * nextOfKthFromEnd = KthFromEnd->next;
		if (nextOfKthFromEnd)
		{
			/*3.1 if KthFromEnd isn't the tail node, we don't need PreKthFromEnd*/
			KthFromEnd->val = nextOfKthFromEnd->val;
			KthFromEnd->next = nextOfKthFromEnd->next;
			delete nextOfKthFromEnd;
		}
		else
		{
			/*3.2 if KthFromEnd is the tail node, we need to update PreKthFromEnd->next or head*/
			delete KthFromEnd;
			if (PreKthFromEnd)//if original list size is greater than 1
				PreKthFromEnd->next = nullptr;
			else//if original list size is equal to 1
				head = nullptr;
		}

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
RemoveKthNodeFromEndLinkedList for 3:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL
[0,1]->[1,2]->[2,4]->[3,5]->NULL
*/
#endif