#ifndef PALINDROME_LINKED_LIST_H
#define PALINDROME_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, LinkedLists: Test whether a singly linked list is palindromic
http://codingrecipies.blogspot.in/2013/11/palindrome-linked-list.html
http://www.geeksforgeeks.org/function-to-check-if-a-singly-linked-list-is-palindrome/

1. Recursion: O(n) time, O(n) space
2. Reverse 2nd Half and Compare: O(n) time, O(1) space
*/
class PalindromeLinkedList
{
public:
	PalindromeLinkedList(){}
	~PalindromeLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};
	//1. recursion
	bool Solve_Recur(ListNode * head)
	{
		ListNode * tail = this->nextNodeLeftToRight_Recur(head, head);
		bool res;
		if (tail == nullptr)
			res = false;
		else
			res = true;
		return res;
	}
private:
	ListNode * nextNodeLeftToRight_Recur(ListNode * head, ListNode * rightNode)//returns a leftNode going from head to tail
	{
		if (rightNode == nullptr)//rightNode reaches tail: return head
			return head;
		ListNode * leftNode = this->nextNodeLeftToRight_Recur(head, rightNode->next);

		/*
		post order: (can be thought as iteration from tail to head)
		now we have the (leftNode, rightNode) pair
		leftNode: going from head to tail
		rightNode: going from tail to head
		if their values are equal, return the next right node of leftNode
		else return nullptr
		*/

		std::string left = (leftNode == nullptr ? std::string("N") : std::to_string(leftNode->val));
		std::cout << "postorder visit [left,right] = [" << left << "," << rightNode->val << "]" << std::endl;

		if (leftNode != nullptr && leftNode->val == rightNode->val)
			return leftNode->next == nullptr ? leftNode : leftNode->next;
		else
			return nullptr;
	}

	//2. find middle node, reverse 2nd half list, compare
public:
	bool Solve_Reverse2ndHalf_Compare(ListNode * head)
	{
		if (head == NULL || head->next == NULL)
			return true;

		/*1. find the middle node and split*/
		ListNode * slow = head;
		ListNode * fast = head;
		ListNode * preSlow = NULL;
		while (fast && fast->next)
		{
			preSlow = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		/*
		now slow is the middle node for an odd list,
		OR the right node of middle node pair for an even list.
		(Aka the first node of the 2nd half list.)

		preSlow is the left node of the middle node for an odd list,
		OR the left node of middle node pair for an even list.
		(Aka the last node of the 1st half list.)
		*/
		preSlow->next = NULL;
		ListNode * mid4Odd_midR4Even = slow;
		std::cout << "mid4Odd_midR4Even: " << mid4Odd_midR4Even->val << std::endl;

		/*2. reverse the 2nd half list*/
		ListNode * head2 = this->Reverse_Iterate(mid4Odd_midR4Even);

		/*
		3. compare 1st half list with reversed 2nd half list
		*/
		bool res = true;
		while (head != NULL && head2 != NULL)
		{
			if (head->val == head2->val)
			{
				head = head->next;
				head2 = head2->next;
			}
			else
			{
				res = false;
				break;
			}
		}
		
		return res;
	}
private:
	ListNode * Reverse_Iterate(ListNode * head)
	{
		ListNode * dummy = this->pushDummy(head);
		ListNode * curNode = dummy->next;
		while (curNode && curNode->next)
		{
			ListNode * nextNode = curNode->next;
			curNode->next = nextNode->next;
			nextNode->next = dummy->next;
			dummy->next = nextNode;
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
postorder visit [left,right] = [1,1]
postorder visit [left,right] = [2,2]
postorder visit [left,right] = [3,3]
postorder visit [left,right] = [4,4]
postorder visit [left,right] = [5,5]
postorder visit [left,right] = [4,4]
postorder visit [left,right] = [3,3]
postorder visit [left,right] = [2,2]
postorder visit [left,right] = [1,1]
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,4]->[6,3]->[7,2]->[8,1]->NULL
PalindromeLinkedList Recur for the above linked list: 1

postorder visit [left,right] = [1,1]
postorder visit [left,right] = [2,2]
postorder visit [left,right] = [3,6]
postorder visit [left,right] = [N,4]
postorder visit [left,right] = [N,4]
postorder visit [left,right] = [N,3]
postorder visit [left,right] = [N,2]
postorder visit [left,right] = [N,1]
[0,1]->[1,2]->[2,3]->[3,4]->[4,4]->[5,6]->[6,2]->[7,1]->NULL
PalindromeLinkedList Recur for the above linked list: 0

mid4Odd_midR4Even: 5
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,4]->[6,3]->[7,2]->[8,1]->NULL
PalindromeLinkedList Reverse2ndHalf_Compare for the above linked list: 1

mid4Odd_midR4Even: 5
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,3]->[6,2]->[7,1]->NULL
PalindromeLinkedList Reverse2ndHalf_Compare for the above linked list: 0
*/
#endif