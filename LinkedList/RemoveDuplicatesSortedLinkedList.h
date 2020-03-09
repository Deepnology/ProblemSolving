#ifndef REMOVE_DUPLICATES_SORTED_LINKED_LIST_H
#define REMOVE_DUPLICATES_SORTED_LINKED_LIST_H
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
/*
Elements of programming interview, LinkedLists: Remove duplicates from a sorted list
1.
Leetcode: Remove Duplicates from Sorted List
// Given a sorted linked list, delete all duplicates such that each element
// appear only once.
//
// For example,
// Given 1->1->2, return 1->2.
// Given 1->1->2->3->3, return 1->2->3.
//
// Complexity:
// O(n) time

2.
Leetcode: Remove Duplicates from Sorted List II
// Given a sorted linked list, delete all nodes that have duplicate numbers,
// leaving only distinct numbers from the original list.
//
// For example,
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.
//
// Complexity:
// O(n) time
*/

class RemoveDuplicatesSortedLinkedList
{
public:
	RemoveDuplicatesSortedLinkedList(){}
	~RemoveDuplicatesSortedLinkedList(){}

	struct ListNode
	{
		ListNode(int v): val(v), next(0){}
		int val;
		ListNode * next;
	};

	ListNode * KeepOneDup(ListNode * head)
	{
		if (head == NULL || head->next == NULL)
			return head;

		ListNode * curNode = head;

		while (curNode != NULL && curNode->next != NULL)
		{
			if (curNode->val == curNode->next->val)
			{
				//found duplicate: delete next node
				ListNode * delNextNode = curNode->next;
				curNode->next = delNextNode->next;
				delete delNextNode;
				delNextNode = 0;
			}
			else
				curNode = curNode->next;
		}
		return head;
	}


	ListNode * DontKeepAnyDup(ListNode * head)
	{
		if (head == NULL || head->next == NULL)
			return head;

		head = this->pushHead(head);//use a dummyHead so we don't have to keep track of head if head is being deleted

		ListNode * tailOfDistinctNodes = head;//this will update dummyHead->next to nullptr when all nodes were deleted
		ListNode * curNode = head->next;

		//for each node in the list
		while (curNode != NULL)
		{
			//1. find the next node of the last same node of curNode
			ListNode * nextOfLastSameNode = curNode->next;

			while (nextOfLastSameNode != NULL && curNode->val == nextOfLastSameNode->val)
				nextOfLastSameNode = nextOfLastSameNode->next;
			//now nextOfLastSameNode points to the next node of the last same node

			//2. remove duplicates and update: 1). tailOfDistinctNodes, 2). tailOfDistinctNodes->next, 3). curNode
			if (curNode->next == nextOfLastSameNode)//found no duplicates between curNode and curNode->next
			{
				tailOfDistinctNodes = curNode;//1). tailOfDistinctNodes
				//2). tailOfDistinctNodes->next==nextOfLastSameNode already done
				curNode = nextOfLastSameNode;//3). curNode
			}
			else//remove duplicated nodes in [curNode, nextOfLastSameNode)
			{
				//1). tailOfDistinctNodes already done
				tailOfDistinctNodes->next = nextOfLastSameNode;//2). tailOfDistinctNodes->next
				while (curNode != nextOfLastSameNode)
				{
					ListNode * del = curNode;
					curNode = curNode->next;
					//std::cout << del->val << std::endl;
					delete del;
				}
				//3). curNode==nextOfLastSameNode
			}
		}
		return this->popHead(head);
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
RemoveDuplicateSortedLinkedList KeepOneDup and DontKeepDup:
[0,1]->[1,2]->[2,3]->[3,3]->[4,4]->[5,4]->[6,5]->NULL
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->NULL
[0,1]->[1,1]->[2,1]->[3,1]->[4,1]->[5,2]->[6,2]->NULL
->NULL
*/
#endif