#ifndef MERGE_2_SORTED_LINKED_LISTS_H
#define MERGE_2_SORTED_LINKED_LISTS_H
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include "PrintLinkedList.h"
/*
Elements of programming interview, LinkedLists: Merge 2 sorted lists
Leetcode: Merge Two Sorted Lists
Merge two sorted DOUBLY linked lists and return it as a new list. The new list
should be made by splicing together the nodes of the first two lists.

Traverse the two lists, always choosing the node containing the smaller key to continue traversing from.
O(n+m) time
*/
class Merge2SortedLinkedLists
{
public:
	Merge2SortedLinkedLists(){}
	~Merge2SortedLinkedLists(){}

	struct ListNode
	{
		ListNode(int v): val(v), next(NULL), prev(NULL){}
		int val;
		ListNode * next;
		ListNode * prev;
	};

	/*check also SortLinkedList.h, which is better*/
	ListNode * GO(ListNode * head1, ListNode * head2)
	{
		ListNode * newHead = NULL;
		ListNode * curNode = NULL;

		while (head1 != NULL && head2 != NULL)
		{
			if (head1->val < head2->val)
			{
				if (newHead == NULL)//head hasn't been assigned => the 1st node
				{
					newHead = head1;
					curNode = newHead;
				}
				else
				{
					curNode->next = head1;
					head1->prev = curNode;
					curNode = curNode->next;
				}
				head1 = head1->next;
			}
			else//head1->val >= head2->val
			{
				if (newHead == NULL)
				{
					newHead = head2;
					curNode = newHead;
				}
				else
				{
					curNode->next = head2;
					head2->prev = curNode;
					curNode = curNode->next;
				}
				head2 = head2->next;
			}
		}

		//when one of l1 or l2 points to the end of the sorted list
		if (head1 == NULL)//only l2 remains
		{
			if (newHead == NULL)
				newHead = head2;
			else
			{
				curNode->next = head2;
				head2->prev = curNode;
			}
		}
		else if (head2 == NULL)//only l1 remains
		{
			if (newHead == NULL)
				newHead = head1;
			else
			{
				curNode->next = head1;
				head1->prev = curNode;
			}
		}

		return newHead;
	}

	ListNode * GO2(ListNode * head1, ListNode * head2)
	{
		ListNode * dummyHead = new ListNode(-1);
		ListNode * curNode = dummyHead;
		while (head1 && head2)
			this->appendNode(curNode, head1->val < head2->val ? head1 : head2);
		if (head1 != nullptr)
			this->appendNode(curNode, head1);
		else if (head2 != nullptr)
			this->appendNode(curNode, head2);
		curNode = dummyHead->next;
		curNode->prev = nullptr;
		delete dummyHead;
		dummyHead = nullptr;
		return curNode;
	}
private:
	void appendNode(ListNode *& curNode, ListNode *& toAppend)
	{
		curNode->next = toAppend;
		toAppend->prev = curNode;

		curNode = toAppend;
		toAppend = toAppend->next;
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

template<>
std::string PrintLinkedList<Merge2SortedLinkedLists::ListNode, std::ostringstream>::SelectVal2(int index, Merge2SortedLinkedLists::ListNode * curNode)
{
	return curNode->prev == nullptr ? "N" : std::to_string(curNode->prev->val);
}

/*
Merge2SortedLinkedList:
[N,7]->[7,13]->[13,16]->[16,18]->[18,24]->NULL
[N,8]->[8,11]->[11,15]->[15,17]->[17,37]->NULL
[N,7]->[7,8]->[8,11]->[11,13]->[13,15]->[15,16]->[16,17]->[17,18]->[18,24]->[24,37]->NULL
*/
#endif