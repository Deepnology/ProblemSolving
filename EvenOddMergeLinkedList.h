#ifndef EVEN_ODD_MERGE_LINKED_LIST_H
#define EVEN_ODD_MERGE_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, LinkedLists: Implement even-odd merge
Define the even-odd merge of a linked list to be the list consisting of even-numbered nodes followed by the odd-numbered nodes.
Input: 0->1->2->3->4->NULL
Output: 0->2->4->1->3->NULL
We can use two iterators, one for the even nodes, the other for the odd nodes.
As we iterate, we append the even nodes to one list and the odd nodes to another.
Finally, we append the odd list to the even list.
Care has to be taken to handle odd/even length lists uniformly, and to correctly process extreme cases (first and last nodes).

O(n) time, O(1) space
*/
class EvenOddMergeLinkedList
{
public:
	EvenOddMergeLinkedList(){}
	~EvenOddMergeLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * Solve_Iterate(ListNode * head)
	{
		if (head == nullptr)
			return nullptr;

		ListNode * oddHead = head;
		ListNode * odd = oddHead;
		ListNode * evenHead = head->next;
		ListNode * even = evenHead;
		ListNode * preOdd = nullptr;

		while (odd != nullptr && even != nullptr)
		{
			odd->next = even->next;//1. get next odd and connect
			preOdd = odd;//save for later
			odd = odd->next;//2. advance odd

			if (odd != nullptr)
			{
				even->next = odd->next;//1. get next even and connect
				even = even->next;//2. advance even
			}
		}

		//append even list to the tail of odd list
		if (odd != nullptr)
		{
			odd->next = evenHead;
		}
		else
		{
			preOdd->next = evenHead;
		}

		return oddHead;
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
EvenOddMergeLinkedList Iterate:
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->NULL
[0,0]->[1,2]->[2,4]->[3,6]->[4,1]->[5,3]->[6,5]->[7,7]->NULL

EvenOddMergeLinkedList Iterate:
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->[8,8]->NULL
[0,0]->[1,2]->[2,4]->[3,6]->[4,8]->[5,1]->[6,3]->[7,5]->[8,7]->NULL
*/
#endif