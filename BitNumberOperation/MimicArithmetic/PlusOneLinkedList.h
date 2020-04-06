#ifndef PLUS_ONE_LINKED_LIST_H
#define PLUS_ONE_LINKED_LIST_H
#include "Debug.h"
/*
Leetcode: Plus One Linked List
Given a non-negative number represented as a singly linked list of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3
Output:
1->2->4

*/
class PlusOneLinkedList
{
public:
	PlusOneLinkedList() {}
	~PlusOneLinkedList() {}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL) {}
		int val;
		ListNode * next;
	};

	ListNode * ReversePlusOneReverse(ListNode * head)
	{
		head = this->Reverse_Iterate(head);
		int carry = 1;
		ListNode * cur = head;
		ListNode * pre = head;
		while (cur)
		{
			int sum = cur->val + carry;
			cur->val = sum % 10;
			carry = sum / 10;
			if (carry == 0) break;
			pre = cur;
			cur = cur->next;
		}
		
		if (carry)
		{
			pre->next = new ListNode(carry);
		}
		head = this->Reverse_Iterate(head);

		return head;
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

public:
	ListNode * Recur(ListNode * head)
	{
		if (head == NULL) return head;

		int carry = this->recur(head);
		if (carry)
		{
			ListNode * carryNode = new ListNode(carry);
			carryNode->next = head;
			return carryNode;
		}

		return head;
	}
private:
	int recur(ListNode * head)
	{
		if (head == NULL) return 1;//return carry=1 at end of list

		int carry = this->recur(head->next);
		int sum = carry + head->val;
		head->val = sum % 10;
		carry = sum / 10;
		return carry;
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
[0,1]->[1,2]->[2,4]->NULL
PlusOneLinkedList ReversePlusOneReverse and Recur:
[0,1]->[1,2]->[2,5]->NULL
[0,1]->[1,2]->[2,5]->NULL

[0,9]->[1,9]->[2,9]->NULL
PlusOneLinkedList ReversePlusOneReverse and Recur:
[0,1]->[1,0]->[2,0]->[3,0]->NULL
[0,1]->[1,0]->[2,0]->[3,0]->NULL

[0,5]->[1,6]->[2,9]->NULL
PlusOneLinkedList ReversePlusOneReverse and Recur:
[0,5]->[1,7]->[2,0]->NULL
[0,5]->[1,7]->[2,0]->NULL
*/
#endif
