#ifndef MERGE_K_SORTED_LINKED_LISTS_H
#define MERGE_K_SORTED_LINKED_LISTS_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <queue>
/*
Leetcode: Merge K Sorted Lists
Merge k sorted linked lists and return it as one sorted list.
Analyze and describe its complexity.
Complexity:
O(nlog(k)) time
*/
class MergeKSortedLinkedLists
{
public:
	MergeKSortedLinkedLists(){}
	~MergeKSortedLinkedLists(){}

	struct ListNode
	{
		ListNode(int v):val(v), next(0){}
		int val;
		ListNode * next;
	};

	struct Greater
	{
		bool operator()(const ListNode * a, const ListNode * b)
		{
			return a->val > b->val;
		}
	};

	ListNode * MinHeap(const std::vector<ListNode *> & lists)//lists: a list of headNodes of sorted linked lists
	{
		/*construct a minHeapOfHeadNodes where the top node is the smallest headNode*/
		std::priority_queue<ListNode *, std::vector<ListNode *>, Greater> minHeapHeadNodes;//minHeap uses "greater than" comparator
		for (std::vector<ListNode *>::const_iterator i = lists.begin(); i != lists.end(); ++i)
		{
			if (*i)
				minHeapHeadNodes.push(*i);//push all the headNodes of each list to the minHeap
		}

		if (minHeapHeadNodes.empty())
			return NULL;

		/*construct a new list from minHeapOfHeadNodes by popping the smallest headNode and pushing the nextNode of the popped headNode until the minHeap is empty*/
		//1. pop
		ListNode * newHead = minHeapHeadNodes.top();
		minHeapHeadNodes.pop();
		ListNode * curNode = newHead;
		//2. push
		if (curNode->next != NULL)
			minHeapHeadNodes.push(curNode->next);

		while (!minHeapHeadNodes.empty())
		{
			//1. pop
			curNode->next = minHeapHeadNodes.top();
			minHeapHeadNodes.pop();
			curNode = curNode->next;//advance curNode
			//2. push
			if (curNode->next != NULL)
				minHeapHeadNodes.push(curNode->next);
		}

		return newHead;
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
MergeKSortedLinkedList:
[0,7]->[1,13]->[2,16]->[3,18]->[4,24]->NULL
[0,8]->[1,11]->[2,15]->[3,17]->[4,37]->NULL
[0,5]->[1,12]->[2,14]->[3,23]->[4,25]->NULL
[0,5]->[1,7]->[2,8]->[3,11]->[4,12]->[5,13]->[6,14]->[7,15]->[8,16]->[9,17]->[10,18]->[11,23]->[12,24]->[13,25]->[14,37]->NULL
*/
#endif