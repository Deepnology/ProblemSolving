#ifndef COPY_RANDOM_LINKED_LIST_H
#define COPY_RANDOM_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
/*
Elements of programming interview, LinkLists: Copy a posting list
A posting list is a singly linked list with an addition "jump" field at each node.
The jump field points to any other node.
Implement a function which takes a posting list and returns a copy of it.
You can modify the original list, but must restore it to its initial state before returning.

Leetcode: Copy List With Random Pointer
// A linked list is given such that each node contains an additional random
// pointer which could point to any node in the list or null.
//
// Return a deep copy of the list.
//
// Complexity:
// hash table with original and copy nodes pair: O(n) time O(n) space
// original node -> copy node -> original node: O(n) time O(1) space

See also JumpFirstOrderPostingsLinkedList.h
*/
class CopyRandomLinkedList
{
public:
	CopyRandomLinkedList(){}
	~CopyRandomLinkedList(){}

	struct RandomListNode
	{
		RandomListNode(int x) : label(x), next(NULL), random(NULL){}
		int label;
		RandomListNode * next;
		RandomListNode * random;
	};

	RandomListNode * HashTable(RandomListNode * head)
	{
		if (head == NULL)
			return head;
		std::unordered_map<RandomListNode *, RandomListNode *> oldToNew;
		for (RandomListNode * oldNode = head; oldNode != NULL; oldNode = oldNode->next)
		{
			RandomListNode * newNode = new RandomListNode(oldNode->label);
			oldToNew[oldNode] = newNode;
		}
		for (RandomListNode * oldNode = head; oldNode != NULL; oldNode = oldNode->next)
		{
			oldToNew[oldNode]->next = oldToNew[oldNode->next];
			oldToNew[oldNode]->random = oldToNew[oldNode->random];
		}
		return oldToNew[head];
	}

	RandomListNode * ConstSpace(RandomListNode * head)
	{
		if (head == NULL)
			return NULL;
		//1. make a copy of each node
		for (RandomListNode * oldNode = head; oldNode != NULL; oldNode = oldNode->next->next) 
		{
			RandomListNode * newNode = new RandomListNode(oldNode->label);
			/*insert newNode in between oldNode and oldNode->next*/
			newNode->next = oldNode->next;
			oldNode->next = newNode;
		}
		//now: oldNode0->newNode0->oldNode1->newNode1->oldNode2->newNode2->oldNode3->newNode3...

		//2. assign the random field of all new nodes
		for (RandomListNode * oldNode = head; oldNode != NULL; oldNode = oldNode->next->next) 
		{
			/*newNode->random = oldNode->random*/
			oldNode->next->random = (oldNode->random == NULL) ? NULL : oldNode->random->next;//oldNode->random: points to an old node; oldNode->random->next: points to a new node
		}

		//3. split old list and new list
		RandomListNode * oldNode = head;
		RandomListNode * newHead = head->next;
		RandomListNode * newNode = newHead;
		while (true)
		{
			oldNode->next = newNode->next;
			oldNode = oldNode->next;//advance oldNode
			if (oldNode == NULL)
				break;
			newNode->next = oldNode->next;
			newNode = newNode->next;//advance newNode
		}
		return newHead;
	}

	static void Print(RandomListNode * head, std::ostringstream & oss)
	{
		RandomListNode * curNode = head;
		int index = 0;
		while (curNode != NULL)
		{
			if (index != 0)
				oss << "->";
			oss << "[" << index << "," << curNode->label << "#";
			if (curNode->random)
				oss << curNode->random->label;
			else
				oss << "NULL";
			oss << "]";
			curNode = curNode->next;
			++index;
		}
		oss << "->NULL";
		oss << std::endl;
	}


public:
	static void DeleteLinkedList(RandomListNode * head)
	{
		std::unordered_set<RandomListNode *> map;
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
		for (std::unordered_set<RandomListNode *>::iterator i = map.begin(); i != map.end(); ++i)
		{
			//std::cout << "DeleteListNode: " << (*i)->label << std::endl;
			delete *i;
		}
	}
};
/*
CopyRandomLinkedList HashTable and ConstSpace:
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL
*/
#endif