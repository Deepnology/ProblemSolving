#ifndef SORT_LINKED_LIST_H
#define SORT_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
/*
Elements of programming interview, LinkedLists: Sort a list (InsertionSort)
Elements of programming interview, Sorting: Implement a fast sorting algorithm for lists (MergeSort)
Implement a routine which sorts a list.
It must run in O(nlogn) time.
It should be a stable sort, i.e., the relative positions of equal elements must remain unchanged.

MergeSort linked list: O(nlogn) time, O(logn) space for recursion stack
(MergeSort is stable)
insertion sort linked list: O(n^2) time

Leetcode: Sort List
// Sort a linked list in O(n log n) time using constant space complexity.

Leetcode: Insertion Sort List
// Sort a linked list using insertion sort.
//
// Complexity:
// O(n^2) time
*/
class SortLinkedList
{
public:
	SortLinkedList(){}
	~SortLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		ListNode(): val(INT_MIN), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * MergeSort(ListNode * head)
	{
		if (head == NULL || head->next == NULL)
			return head;
		ListNode * frontHead = NULL;
		ListNode * backHead = NULL;
		//pre order: split into front group and back group
		this->split(head, frontHead, backHead);
		//sort front group
		frontHead = this->MergeSort(frontHead);
		//sort back group
		backHead = this->MergeSort(backHead);
		//post order: merge sorted front group and sorted back group
		return this->merge(frontHead, backHead);
	}
private:
	void split(ListNode * head, ListNode *& frontHead, ListNode *& backHead)//after split, frontHead should be headNodeFrontGroup, backHead should be headNodeBackGroup
	{
		ListNode * fastNode = head;
		ListNode * slowNode = head;
		ListNode * preSlowNode = NULL;
		while (fastNode && fastNode->next)
		{
			preSlowNode = slowNode;
			slowNode = slowNode->next;
			fastNode = fastNode->next->next;
		}
		preSlowNode->next = NULL;
		backHead = slowNode;
		frontHead = head;
	}

	/*check also Merge2SortedLinkedList.h (but this is better)*/
	ListNode * merge(ListNode * frontHead, ListNode * backHead)//merge two sorted group: front and back
	{
		ListNode * dummy = this->pushDummy(NULL);//construct a new list with a dummyHead. with dummyHead, we don't need to write the special case to decide head is from frontHead or from backHead
		ListNode * curNode = dummy;
		while (frontHead|| backHead)
		{
			if (backHead == NULL || (frontHead && frontHead->val <= backHead->val))//insert frontHead when (back group is empty or frontHead <= backHead)
			{
				/*insert frontHead to curNode->next*/
				curNode->next = frontHead;
				/*advance frontHead*/
				frontHead = frontHead->next;
			}
			else//insert backHead when (back group is non-empty and frontHead > backHead)
			{
				/*insert backHead to curNode->next*/
				curNode->next = backHead;
				/*advance backHead*/
				backHead = backHead->next;
			}
			/*advance curNode*/
			curNode = curNode->next;
		}
		return this->popDummy(dummy);
	}
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

	void insertNode(ListNode * head, ListNode * newNode)
	{
		ListNode * curNode = head;
		while (curNode->next != NULL && curNode->next->val <= newNode->val)
			curNode = curNode->next;
		/*now curNode->next->val > newNode->val: insert newNode between curNode and curNode->next*/
		newNode->next = curNode->next;
		curNode->next = newNode;
	}
public:
	ListNode * InsertionSort(ListNode * head)
	{
		ListNode * dummy = this->pushDummy(NULL);//construct a new sorted list with a dummyHead
		ListNode * curNode = head;
		while (curNode != NULL)
		{
			ListNode * nextNode = curNode->next;//backup original curNode->next
			this->insertNode(dummy, curNode);//insert curNode to the new sorted list
			curNode = nextNode;//advance curNode
		}
		return this->popDummy(dummy);
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
SortLinkedList Merge and Insertion Sort:
[0,7]->[1,6]->[2,8]->[3,4]->[4,3]->[5,2]->NULL
[0,2]->[1,3]->[2,4]->[3,6]->[4,7]->[5,8]->NULL
[0,7]->[1,6]->[2,8]->[3,4]->[4,3]->[5,2]->NULL
[0,2]->[1,3]->[2,4]->[3,6]->[4,7]->[5,8]->NULL
*/
#endif