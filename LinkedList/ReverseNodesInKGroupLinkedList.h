#ifndef REVERSE_NODES_IN_K_GROUP_LINKED_LIST_H
#define REVERSE_NODES_IN_K_GROUP_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
/*
Elements of programming interview, LinkLists: Reverse sublists k at a time
Leetcode: Reverse Nodes In K Group
// Given a linked list, reverse the nodes of a linked list k at a time and
// return its modified list.
//
// If the number of nodes is not a multiple of k then left-out nodes in the
// end should remain as it is.
//
// You may not alter the values in the nodes, only nodes itself may be
// changed.
//
// Only constant memory is allowed.
//
// For example,
// Given this linked list: 1->2->3->4->5
//
// For k = 2, you should return: 2->1->4->3->5
//
// For k = 3, you should return: 3->2->1->4->5
*/
class ReverseNodesInKGroupLinkedList
{
public:
	ReverseNodesInKGroupLinkedList(){}
	~ReverseNodesInKGroupLinkedList(){}

	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL) {}
		int val;
		ListNode * next;
	};

	ListNode * Iterate(ListNode * head, int k)
	{
		if (k < 2)
			return head;

		int len = 0;
		ListNode * countNode = head;
		while (countNode != NULL)
		{
			countNode = countNode->next;
			++len;
		}

		ListNode * dummy = this->pushDummy(head);
		ListNode * preNode = dummy;
		ListNode * curNode = preNode->next;
		int count = 1;
		int groupCount = 0;
		//groupCount < len / k:
		//to keep the original order of left-out nodes in the end if len is NOT a multiple of k
		while (curNode && curNode->next && groupCount < len / k)
		{
			if (count < k)
			{
				//same as ReverseLinkedList.h Iterate
				ListNode * nextNode = curNode->next;
				curNode->next = nextNode->next;
				nextNode->next = preNode->next;
				preNode->next = nextNode;
				++count;
			}
			else
			{
				preNode = curNode;
				curNode = curNode->next;
				count = 1;
				++groupCount;
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
ReverseNodesInKGroupLinkedList Iterate for 2 and 4:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,2]->[1,1]->[2,4]->[3,3]->[4,6]->[5,5]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,4]->[1,3]->[2,2]->[3,1]->[4,5]->[5,6]->NULL
*/
#endif