#ifndef MEDIAN_OF_SORTED_CIRCULAR_LINKED_LIST_H
#define MEDIAN_OF_SORTED_CIRCULAR_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
/*
Eelements of programming interview, LinkedLists: Compute the median of a sorted circular linked list
Write a function that takes a pointer to an arbitrary node in a sorted circular linked list, and returns the median of the linked list.

A key observation is that the median is n/2 steps from the smallest element in the list.
Therefore, a better approach is to find the smallest element (the first such if there are duplicates) and compute n.

O(n) time, O(1) space
*/
class MedianOfSortedCircularLinkedList
{
public:
	MedianOfSortedCircularLinkedList(){}
	~MedianOfSortedCircularLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};

	double Find(ListNode * aNode)
	{
		//check if all nodes are identical and identifies the first smallest node
		int N = 0;
		ListNode * curNode = aNode;
		ListNode * firstSmallestNode = aNode;
		do
		{
			curNode = curNode->next;
			++N;
			if (curNode->val >= firstSmallestNode->val)
				firstSmallestNode = curNode;
		} while (curNode != aNode);

		//now firstSmallestNode points to the largest node, and its next node would be the first smallest node
		firstSmallestNode = firstSmallestNode->next;

		//advance to the middle of the list
		for (int i = 0; i < (N - 1) / 2; ++i)
			firstSmallestNode = firstSmallestNode->next;

		double res = N % 2 == 1 ? firstSmallestNode->val : (firstSmallestNode->val + firstSmallestNode->next->val) / 2;
		return res;
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
MedianOfSortedCircularLinkedList:
[0,1]->[1,1]->[2,1]->[3,3]->[4,5]->[5,6]->[6,7]->[7,7]->[8,8]->
  ^___________________________________________________________|
5
*/
#endif