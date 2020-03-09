#ifndef LINKED_LIST_CYCLE_H
#define LINKED_LIST_CYCLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, LinkLists: Test for cyclicity
Leetcode: Linked List Cycle
// Given a linked list, determine if it has a cycle in it.
//
// Follow up:
// Can you solve it without using extra space?
//
// Complexity
// O(n)

Leetcode: Linked List Cycle II
// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
//
// Follow up:
// Can you solve it without using extra space?
//
// Complexity
// HashTable: O(n) time, O(n) space
// BruteForce: O(n^2) time, O(1) space
// (Traverse the list in 2 loops: the outer loop traverses the nodes one-by-one, and the inner loop starts from the head, and traverses as many nodes as the outer loop has gone through so far.
// If the node being visited by the outer loop is visited twice by the inner loop, a loop has been detected.
// If the outer loop encounters the end of the list, no cycle exists.)
// SlowFastIter: O(n) time, O(1) space

 _______a________  _____b_____  _________n*L____________
/                \/           \/                        \(include 6)
0->1->2->3->4->5->6->7->8->9->10->11->12->13->14->15->
                  ^__________________________________|

slow and fast will meet at 10
slow: a+b+m*L, where m is number of cycles, L is the cycle length
fast: a+b+n*L, where n is number of cycles, L is the cycle length
since the speed of fast is 2 times of slow, the total distance of fast is 2 times of the total distance of slow.
2*(a+b+m*L) = a+b+n*L
=> a+b = N*L
=> a = N*L-b
Let ptr1 start from head, ptr2 start from meeting point. Advance both ptr1 and ptr2 by 1 step until they meet.
Let ptr1 start from head, ptr2 start from head w/ L in advance. Advance both ptr1 and ptr2 by 1 step until they meet.
*/
class LinkedListCycle
{
public:
	LinkedListCycle(){}
	~LinkedListCycle(){}

	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};
	bool HasCycle(ListNode * head)
	{
		ListNode * fastNode = head, *slowNode = head;
		while (fastNode != NULL && fastNode->next != NULL) 
		{
			fastNode = fastNode->next->next;
			slowNode = slowNode->next;
			if (fastNode == slowNode)
				return true;
		}
		return false;
	}

	ListNode * GetCycleBegin(ListNode * head)
	{
		if (head == NULL || head->next == NULL) return NULL;

		//1. advance slow ptr 1 node, fast ptr 2 nodes
		//they will meet at some node in the middle of the cycle
		ListNode * fastNode = head, *slowNode = head;
		while (fastNode != NULL && fastNode->next != NULL)
		{
			fastNode = fastNode->next->next;
			slowNode = slowNode->next;
			if (fastNode == slowNode)
				break;
		}
		if (fastNode != slowNode)
			return NULL;
		std::cout << "CycleMiddle: " << fastNode->val << std::endl;

		//2. find the cycle length
		int cycleLen = 0;
		do
		{
			++cycleLen;
			fastNode = fastNode->next;
		} while (fastNode != slowNode);

		//3. find the node with cycle length from head
		//advance both nodes ptrs 1 node until they meet, where must be the cycle begin node
		ListNode * cycleLenNode = head;
		while (cycleLen--)
			cycleLenNode = cycleLenNode->next;
		ListNode * cycleBegin = head;
		while (cycleLenNode != cycleBegin)
		{
			cycleLenNode = cycleLenNode->next;
			cycleBegin = cycleBegin->next;
		}

		return cycleBegin;
	}

	ListNode * GetCycleBegin_Correct(ListNode * head)
	{
		if (head == NULL || head->next == NULL) return NULL;

		//1. advance slow ptr 1 node, fast ptr 2 nodes
		//they will meet at some node in the middle of the cycle
		ListNode * fastNode = head, *slowNode = head;
		while (fastNode != NULL && fastNode->next != NULL)
		{
			fastNode = fastNode->next->next;
			slowNode = slowNode->next;
			if (fastNode == slowNode) 
				break;
		}
		if (fastNode != slowNode)
			return NULL;
		std::cout << "CycleMiddle: " << fastNode->val << std::endl;

		//2. let fast ptr start from head, slow ptr start from its current node, advance both ptrs 1 node
		//they will meet at the cylce begin node
		fastNode = head;
		while (fastNode != slowNode) 
		{
			fastNode = fastNode->next;
			slowNode = slowNode->next;
		}
		return fastNode;
	}

	ListNode * GetCycleBegin_Brent(ListNode * head)
	{
		if (head == NULL || head->next == NULL) return NULL;

		ListNode * slow = head;
		ListNode * fast = head->next;
		int len = 1;
		int pow = 1;
		while (fast && fast != slow)
		{
			if (len == pow)
			{
				pow *= 2;
				len = 0;
				slow = fast;
			}
			fast = fast->next;
			++len;
		}
		if (fast == NULL) return NULL;
		//now len is the length of loop
		ListNode * cycleLenNode = head;
		while (len--)
			cycleLenNode = cycleLenNode->next;
		ListNode * cycleBegin = head;
		while (cycleBegin != cycleLenNode)
		{
			cycleBegin = cycleBegin->next;
			cycleLenNode = cycleLenNode->next;
		}

		return cycleBegin;
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
CycleMiddle: 3
CycleMiddle: 3
[0,17]->[1,8]->[2,16]->[3,5]->[4,11]->[5,3]->[6,24]->[7,9]->
                         ^_________________________________|
LinkedListCycle HasCycle: 1, CycleBegin: 5, 5, 5

CycleMiddle: 10
CycleMiddle: 10
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->[9,9]->[10,10]->[11,11]->[12,12]->[13,13]->[14,14]->[15,15]->
                                            ^______________________________________________________________________________|
LinkedListCycle HasCycle: 1, CycleBegin: 6, 6, 6
*/
#endif