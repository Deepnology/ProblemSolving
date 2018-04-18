#ifndef REMOVE_GIVEN_NODE_IN_LINKED_LIST_H
#define REMOVE_GIVEN_NODE_IN_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
/*
Elements of programming interview, LinkedLists: Delete a node from a singly linked list
http://codingrecipies.blogspot.in/2013/11/linked-list-deleted-node-with-given.html
Cracking the coding interview: linked list

O(1) time
*/
class RemoveGivenNodeInLinkedList
{
public:
	RemoveGivenNodeInLinkedList(){}
	~RemoveGivenNodeInLinkedList(){}
	struct ListNode
	{
		ListNode(int v) : val(v), next(NULL){}
		int val;
		ListNode * next;
	};
	bool Solve(ListNode * n)
	{
		if (n == nullptr || n->next == nullptr)//n cannot not be a tail! (bc its prevNode->next cannot be updated)
			return false;

		//copy n->next's properties to n, and delete n->next
		ListNode * nextNode = n->next;
		n->val = nextNode->val;
		n->next = nextNode->next;
		delete nextNode;
		return true;
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
class RemoveGivenNodeInDoublyLinkedList
{
public:
	struct ListNode
	{
		ListNode(int v) : val(v), next(NULL), prev(NULL){}
		int val;
		ListNode * next;
		ListNode * prev;
	};
	RemoveGivenNodeInDoublyLinkedList(){}

	ListNode * Solve(ListNode * head, ListNode * tgt)
	{
		if (head == NULL || tgt == NULL) return NULL;

		if (tgt->prev == NULL)//tgt is head: update tgt->next and head
		{
			if (tgt->next)
				tgt->next->prev = NULL;
			head = tgt->next;
			delete tgt;
			return head;
		}
		else if (tgt->next == NULL)//tgt is tail (and not head): update tgt->prev
		{
			tgt->prev->next = NULL;
			delete tgt;
			return head;
		}
		else if (tgt->prev == tgt)//single node with a ring: update head
		{
			delete tgt;
			return NULL;
		}
		else//tgt is a middle node in a list w/o ring OR can be any node in a list w/ ring and size >= 2
		{
			tgt->prev->next = tgt->next;
			tgt->next->prev = tgt->prev;
			if (head == tgt)
				head = tgt->next;
			delete tgt;
			return head;
		}
	}
};
#endif