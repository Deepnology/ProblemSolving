#ifndef JUMP_FIRST_ORDER_POSTINGS_LINKED_LIST_H
#define JUMP_FIRST_ORDER_POSTINGS_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Search a posting list
A posting list is a singly linked list with an addition "jump" field at each node.
The jump field points to any other node.
One way to enumerate the nodes in a postings list is to iteratively follow the next field.
Another is to always first follow the jump field if it leads to a node that has not been explored previously, and then search from the next node.
Call the order in which these nodes are traversed the jump-first order.

O(n) time, O(n) space
See also CopyRandomLinkedList.h
*/
class JumpFirstOrderPostingsLinkedList
{
public:
	JumpFirstOrderPostingsLinkedList(){}
	~JumpFirstOrderPostingsLinkedList(){}

	struct RandomListNode
	{
		RandomListNode(int x) : label(x), next(NULL), random(NULL){}
		int label;
		RandomListNode * next;
		RandomListNode * random;
	};

	std::vector<int> DFSRecur_HashTable(RandomListNode * head)
	{
		std::vector<int> res;
		std::unordered_set<RandomListNode *> visited;
		this->dfsRecur(head, visited, res);
		std::cout << "JumpFirstOrderPostingsLinkedList DFSRecur_HashTable: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void dfsRecur(RandomListNode * head, std::unordered_set<RandomListNode *> & visited, std::vector<int> & res)
	{
		if (head == nullptr || visited.count(head) != 0)
			return;
		
		res.push_back(head->label);//now visit head
		visited.insert(head);//mark this node been visited
		this->dfsRecur(head->random, visited, res);//check head->random first
		this->dfsRecur(head->next, visited, res);//check head->next
	}

public:
	std::vector<int> Iterate_HashTable_Stack(RandomListNode * head)
	{
		std::stack<RandomListNode *> stk;
		std::unordered_set<RandomListNode *> visited;
		std::vector<int> res;
		stk.push(head);
		while (!stk.empty())
		{
			RandomListNode * cur = stk.top();
			stk.pop();
			if (cur && visited.count(cur) == 0)
			{
				res.push_back(cur->label);//visit the node
				visited.insert(cur);//mark this node been visited
				stk.push(cur->next);
				stk.push(cur->random);//cur->random will be poped out first
			}
		}

		std::cout << "JumpFirstOrderPostingsLinkedList Iterate_HashTable_Stack: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
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
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL

JumpFirstOrderPostingsLinkedList DFSRecur_HashTable: 1, 5, 6, 2, 3, 4
[0,1#5]->[1,2#2]->[2,3#4]->[3,4#3]->[4,5#6]->[5,6#1]->NULL

JumpFirstOrderPostingsLinkedList Iterate_HashTable_Stack: 1, 5, 6, 2, 3, 4
*/
#endif