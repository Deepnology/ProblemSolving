#ifndef ROTATE_LINKED_LIST_H
#define ROTATE_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
/*
Elements of programming interview, LinkLists: Implement cyclic right shift for singly linked list
Leetcode: Rotate List
// Given a list, rotate the list to the right by k places, where k is
// non-negative.
//
// For example:
// Given 1->2->3->4->5->NULL and k = 2,
// return 4->5->1->2->3->NULL.
*/
class RotateLinkedList
{
public:
	RotateLinkedList(){}
	~RotateLinkedList(){}

	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	//move the tail k nodes to the front: 1. make the list circular & find the new headNode 2. make tailNode->next = NULL 3. return headNode
	ListNode * RotateRight(ListNode * head, int k)
	{
		if (head == NULL || k < 0)
			return head;
		int len = 1;
		ListNode * curNode = head;
		for (; curNode->next != NULL; curNode = curNode->next)
			++len;
		/*now curNode is the tailNode*/
		curNode->next = head;//make it a circular linked list
		k = len - k%len;//instead of "len - k" to avoid negative number
		/*now k is the len from head to the node to be move*/
		for (; k > 0; --k)
			curNode = curNode->next;
		/*now curNode is the tailNode of the group that won't be moved*/
		head = curNode->next;//the new head node
		curNode->next = NULL;//the new tail node's next should be NULL
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
RotateLinkedList for 2:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,5]->[1,6]->[2,1]->[3,2]->[4,3]->[5,4]->NULL
*/
#endif