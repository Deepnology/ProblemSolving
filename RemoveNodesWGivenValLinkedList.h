#ifndef REMOVE_NODES_W_GIVEN_VAL_LINKED_LIST_H
#define REMOVE_NODES_W_GIVEN_VAL_LINKED_LIST_H
#include <iostream>
#include <string>
#include <unordered_set>
/*
Leetcode: Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.
Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/
class RemoveNodesWGivenValLinkedList
{
public:
	RemoveNodesWGivenValLinkedList(){}
	~RemoveNodesWGivenValLinkedList(){}
	struct ListNode
	{
		ListNode(int v) : val(v), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * IterateWOdummy(ListNode * head, int val)//best
	{
		//1. remove front nodes whose val are equal
		while (head && head->val == val)
		{
			ListNode * del = head;
			head = head->next;
			delete del;
		}
		//2. remove non-front nodes whose val are equal
		ListNode * cur = head;
		while (cur && cur->next)
		{
			if (cur->next->val == val)
			{
				ListNode * del = cur->next;
				cur->next = cur->next->next;
				delete del;
			}
			else
				cur = cur->next;
		}
		return head;
	}
	ListNode * Recur(ListNode * head, int val)
	{
		if (head == NULL) return NULL;
		head->next = Recur(head->next, val);
		if (head->val == val)
		{
			ListNode * next = head->next;
			delete head;
			return next;
		}
		return head;
	}

	ListNode * Iterate(ListNode * head, int val)
	{
		ListNode * dummy = this->pushHead(head);
		ListNode * curNode = dummy;
		while (curNode)
		{
			if (curNode->next && curNode->next->val == val)
			{
				ListNode * delNode = curNode->next;
				curNode->next = delNode->next;//advance curNode
				delete delNode;
			}
			else
				curNode = curNode->next;//advance curNode
		}
		return this->popHead(dummy);
	}
private:
	ListNode * pushHead(ListNode * head)
	{
		ListNode * newNode = new ListNode(-1);
		newNode->next = head;
		return newNode;
	}
	ListNode * popHead(ListNode * head)
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
[0,1]->[1,2]->[2,6]->[3,3]->[4,4]->[5,5]->[6,6]->NULL
RemoveNodesWGivenValLinkedList for 6:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL
*/
#endif