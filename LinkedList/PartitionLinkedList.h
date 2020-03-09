#ifndef PARTITION_LINKED_LIST_H
#define PARTITION_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
/*
Elements of programming interview, LinkedLists: Implement list pivoting (Partition_3way)
For any integer k, the pivot of a list of integers with respect to k is that list with its nodes reordered so that all nodes containing keys less than k appear before nodes containing k
, and all nodes containing keys greater than k appear after the nodes containing k.
Implement a function which takes as input a singly linked list and an integer k and performs a pivot of the list with respect to k.
The relative ordering of nodes that appear before k, and after k, must remain unchanged; the same must hold for nodes holding keys equal to k.

Leetcode: Partition List
// Given a linked list and a value x, partition it such that all nodes less
// than x come before nodes greater than or equal to x.
//
// You should preserve the original relative order of the nodes in each of the
// two partitions.
//
// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.
//
// Complexity:
// O(n) time
*/
class PartitionLinkedList
{
public:
	PartitionLinkedList(){}
	~PartitionLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * Partition(ListNode * head, int x)
	{
		ListNode * frontDummy = new ListNode(-1);
		ListNode * frontNode = frontDummy;
		ListNode * backDummy = new ListNode(-1);
		ListNode * backNode = backDummy;
		while (head != NULL)
		{
			if (head->val < x)
			{
				frontNode->next = head;
				frontNode = frontNode->next;
			}
			else
			{
				backNode->next = head;
				backNode = backNode->next;
			}
			head = head->next;
		}
		backNode->next = NULL;
		frontNode->next = this->deleteNode(backDummy);
		return this->deleteNode(frontDummy);
	}

	ListNode * Partition_3way(ListNode * head, int x)
	{
		ListNode * frontDummy = new ListNode(-1);
		ListNode * frontNode = frontDummy;
		ListNode * backDummy = new ListNode(-1);
		ListNode * backNode = backDummy;
		ListNode * midDummy = new ListNode(-1);
		ListNode * midNode = midDummy;
		while (head != NULL)
		{
			if (head->val < x)
			{
				frontNode->next = head;
				frontNode = frontNode->next;
			}
			else if (head->val == x)
			{
				midNode->next = head;
				midNode = midNode->next;
			}
			else
			{
				backNode->next = head;
				backNode = backNode->next;
			}
			head = head->next;
		}
		backNode->next = NULL;
		midNode->next = this->deleteNode(backDummy);
		frontNode->next = this->deleteNode(midDummy);
		return this->deleteNode(frontDummy);
	}

private:
	ListNode * deleteNode(ListNode * curNode)
	{
		ListNode * toDel = curNode;
		curNode = curNode->next;
		delete toDel;
		toDel = 0;
		return curNode;
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
PartitionLinkedList for 6:
[0,7]->[1,3]->[2,8]->[3,6]->[4,10]->[5,5]->[6,4]->[7,6]->[8,5]->[9,6]->NULL
[0,3]->[1,5]->[2,4]->[3,5]->[4,7]->[5,8]->[6,6]->[7,10]->[8,6]->[9,6]->NULL

PartitionLinkedList 3way for 6:
[0,7]->[1,3]->[2,8]->[3,6]->[4,10]->[5,5]->[6,4]->[7,6]->[8,5]->[9,6]->NULL
[0,3]->[1,5]->[2,4]->[3,5]->[4,6]->[5,6]->[6,6]->[7,7]->[8,8]->[9,10]->NULL
*/
#endif