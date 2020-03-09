#ifndef REMOVE_DUP_UNSORTED_LINKED_LIST_H
#define REMOVE_DUP_UNSORTED_LINKED_LIST_H
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
/*
Cracking the coding interview 2.1
Remove duplicates (keep one)
Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?

To delete curNode, we need to keep a preNode and update preNode->next to curNode->next before deleting curNode
*/
class RemoveDupUnsortedLinkedList
{
public:
	RemoveDupUnsortedLinkedList(){}
	~RemoveDupUnsortedLinkedList(){}
	struct ListNode
	{
		ListNode(int v) : val(v), next(NULL){}
		int val;
		ListNode * next;
	};

	ListNode * HashTable(ListNode * head)//O(n) time, O(n) space
	{
		ListNode * curNode = head;
		ListNode * preNode;
		std::unordered_map<int, ListNode *> map;//key: ListNode's val, value: first ListNode ptr
		while (curNode != NULL)
		{
			if (map.find(curNode->val) == map.end())//curNode->val doesn't exist
			{
				map.insert(std::make_pair(curNode->val, curNode));
				preNode = curNode;
				curNode = curNode->next;
			}
			else//curNode->val already exists
			{
				preNode->next = curNode->next;
				delete curNode;
				curNode = preNode->next;
			}
		}
		return head;
	}

	ListNode * ConstSpace(ListNode * head)//O(n^2) time, O(1) space
	{
		//for each node in the list, check every node from head till current node for duplicated val of current node
		//if found duplicate, remove current node

		ListNode * preNode = head;
		ListNode * curNode = head->next;
		while (curNode != NULL)
		{
			//check every node from head for duplicate of curNode
			ListNode * keptNode = head;
			while (keptNode != curNode)
			{
				if (keptNode->val == curNode->val)//found a duplicate of curNode: keep 1st dup (keptNode), remove 2nd dup (curNode), advance curNode, stop
				{
					ListNode * nextNode = curNode->next;
					preNode->next = nextNode;
					delete curNode;
					curNode = nextNode;
					break;
				}
				keptNode = keptNode->next;
			}
			if (keptNode == curNode)//found no duplicate of curNode: advance (preNode,curNode)
			{
				preNode = curNode;
				curNode = curNode->next;
			}
		}
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
RemoveDupUnsortedLinkedList HashTable and ConstSpace:
[0,7]->[1,8]->[2,5]->[3,16]->[4,13]->[5,8]->[6,7]->[7,16]->[8,3]->NULL
[0,7]->[1,8]->[2,5]->[3,16]->[4,13]->[5,3]->NULL
[0,7]->[1,8]->[2,5]->[3,16]->[4,13]->[5,8]->[6,7]->[7,16]->[8,3]->NULL
[0,7]->[1,8]->[2,5]->[3,16]->[4,13]->[5,3]->NULL
*/
#endif