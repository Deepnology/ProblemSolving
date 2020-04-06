#ifndef SWAP_NODES_IN_PAIRS_LINKED_LIST_H
#define SWAP_NODES_IN_PAIRS_LINKED_LIST_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
/*
Leetcode: Swap Nodes In Pairs
// Given a linked list, swap every two adjacent nodes and return its head.
//
// For example,
// Given 1->2->3->4, you should return the list as 2->1->4->3.
//
// Your algorithm should use only constant space. You may not modify the
// values in the list, only nodes itself can be changed.
//
// Complexity:
// O(n)
*/
class SwapNodesInPairsLinkedList
{
public:
	SwapNodesInPairsLinkedList(){}
	~SwapNodesInPairsLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL) {}
		int val;
		ListNode * next;
	};
	ListNode * SwapRecur(ListNode * head)
	{
		return this->swapRecur(head);
	}
private:
	ListNode * swapRecur(ListNode * curNode)//return the headNode after swap (curNode,curNode->next)
	{
		if (curNode == NULL || curNode->next == NULL)
			return curNode;
		ListNode * nextNode = curNode->next;//now (curNode,nextNode)
		//after swap should be (nextNode,curNode):
		curNode->next = this->swapRecur(nextNode->next);
		nextNode->next = curNode;
		return nextNode;//return the headNode of (nextNode,curNode)
	}
public:
	ListNode * SwapIterate(ListNode * head)
	{
		head = this->pushDummy(head);//dummy head won't be swapped, that's the reason for dummy head
		ListNode * preNode = head;
		ListNode * curNode = head->next;
		while (curNode != NULL && curNode->next != NULL)
		{
			ListNode * nextNode = curNode->next;
			//after swap should be (nextNode,curNode):
			curNode->next = nextNode->next;
			nextNode->next = curNode;
			//connect preNode->next to headNode of this node pair
			preNode->next = nextNode;
			//update preNode to tailNode of this node pair
			preNode = curNode;
			//advance curNode with 1 node to the headNode of next node pair
			curNode = curNode->next;
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
SwapNodesInPairsLinkedList Recur and Iterate:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,2]->[1,1]->[2,4]->[3,3]->[4,6]->[5,5]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->NULL
[0,2]->[1,1]->[2,4]->[3,3]->[4,6]->[5,5]->NULL
*/
#endif