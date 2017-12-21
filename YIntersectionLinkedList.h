#ifndef Y_INTERSECTION_LINKED_LIST_H
#define Y_INTERSECTION_LINKED_LIST_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
#include "PrintLinkedList.h"
/*
Leetcode: Intersection of two linked lists (without cycles)
Write a program to find the node at which the intersection of two singly linked list begins.

Elements of programming interview, LinkLists:
Test for overlapping lists: lists are cycle-free
Test for overlapping lists: lists may have cycles

Given two linked lists.
Find out whether they are converged to a single linked list or not.
If yes, find the point of convergence.

HashTable: O(n) time, O(n) space
Traverse list A and store the address / reference to each node in a hash set. Then check every node bi in list B: if bi appears in the hash set, then bi is the intersection node.
BruteForce: O(n^2) time, O(1) space
For each node ai in list A, traverse the entire list B and check if any node in list B coincides with ai.
Linear: O(n) time, O(1) space
2Pointers: O(n) time, O(1) space
Maintain two pointers pA and pB initialized at the head of A and B, respectively.
Then let them both traverse through the lists, one node at a time.
When pA reaches the end of a list, then redirect it to the head of B (yes, B, that's right.);
similarly when pB reaches the end of a list, redirect it the head of A.
If at any point pA meets pB, then pA/pB is the intersection node.
To see why the above trick would work, consider the following two lists: A = {1,3,5,7,9,11} and B = {2,4,9,11}
, which are intersected at node '9'.
Since B.length (=4) < A.length (=6), pB would reach the end of the merged list first, because pB traverses exactly 2 nodes less than pA does.
By redirecting pB to head A, and pA to head B, we now ask pB to travel exactly 2 more nodes than pA would.
So in the second iteration, they are guaranteed to reach the intersection node at the same time.
If two lists have intersection, then their last nodes must be the same one.
So when pA/pB reaches the end of a list, record the last element of A/B respectively.
If the two last elements are not the same one, then the two lists have no intersections.
*/
class YIntersectionLinkedList
{
public:
	YIntersectionLinkedList(){}
	~YIntersectionLinkedList(){}
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL){}
		int val;
		ListNode * next;
	};
	/*
			 1
			 6 v 77
			     2->N
	3  4  5  6 ^ 5
	1->2->3->4

	      4  5
	      1->N
	2  3  4  5
	1->2->3->N
	*/
	ListNode * FindIntersectionNode_(ListNode * head1, ListNode * head2)//w/o knowing length
	{
		if (head1 == NULL || head2 == NULL) return NULL;
		ListNode * a = head1;
		ListNode * b = head2;
		while (a != b)
		{
			a = a == NULL ? head2 : a->next;
			b = b == NULL ? head1 : b->next;
		}
		return a;
	}
	ListNode * FindIntersectionNode(ListNode * head1, ListNode * head2)
	{
		/*1. find tail1 and len1*/
		int len1 = 0;
		ListNode * tail1 = head1;
		while (tail1->next != nullptr)
		{
			tail1 = tail1->next;
			++len1;
		}
		++len1;

		/*1. find tail2 and len2*/
		int len2 = 0;
		ListNode * tail2 = head2;
		while (tail2->next != nullptr)
		{
			tail2 = tail2->next;
			++len2;
		}
		++len2;

		/*3. compare tail1 and tail2*/
		bool converged = tail1 == tail2;
		ListNode * intersection = nullptr;
		if (converged)
		{
			/*4. advance longer from head to diff of len1 and len2*/
			ListNode * longer = len1 > len2 ? head1 : head2;
			ListNode * shorter = len1 <= len2 ? head1 : head2;
			
			int diff = std::abs(len1 - len2);
			while (diff-- > 0)
				longer = longer->next;

			/*5. advance both longer and shorter until they point to the same*/
			while (longer != shorter)
			{
				longer = longer->next;
				shorter = shorter->next;
			}
			intersection = longer;
		}

		std::ostringstream oss;
		PrintLinkedList<ListNode, std::ostringstream>(head1, oss);
		PrintLinkedList<ListNode, std::ostringstream>(head2, oss);
		std::cout << oss.str();
		std::string val = intersection == nullptr ? "N" : std::to_string(intersection->val);
		std::cout << "YIntersectionLinkedList for the above 2 linked lists: " << val << std::endl;
		return intersection;
	}

	ListNode * FindIntersectionNode_WCycles(ListNode * head1, ListNode * head2)
	{
		ListNode * cycleBegin1 = this->GetCycleBegin(head1);
		ListNode * cycleBegin2 = this->GetCycleBegin(head2);

		if (cycleBegin1 == nullptr && cycleBegin2 == nullptr)
		{
			return this->FindIntersectionNode(head1, head2);//Case1: both doesn't have cycles
		}
		else if ((cycleBegin1 == nullptr && cycleBegin2 != nullptr) || (cycleBegin1 != nullptr && cycleBegin2 == nullptr))
		{
			std::ostringstream oss;
			PrintLinkedList<ListNode, std::ostringstream>(head1, oss);
			PrintLinkedList<ListNode, std::ostringstream>(head2, oss);
			std::cout << oss.str();
			std::cout << "YIntersectionLinkedList WCycles for the above 2 linked lists: Case2, one has cycle and the other doesn't, they cannot overlap" << std::endl;
			return nullptr;
		}

		//both lists have cycles: either cycleBegin should meet the other one Before or At the Same Time when meeting itself again!!
		ListNode * cycleBegin1_ = cycleBegin1;
		do
		{
			cycleBegin1_ = cycleBegin1_->next;
		} while (cycleBegin1_ != cycleBegin1 && cycleBegin1_ != cycleBegin2);

		if (cycleBegin1_ != cycleBegin2)//cycleBegin1_ == cycleBegin1
		{
			std::ostringstream oss;
			PrintLinkedList<ListNode, std::ostringstream>(head1, oss);
			PrintLinkedList<ListNode, std::ostringstream>(head2, oss);
			std::cout << oss.str();
			std::cout << "YIntersectionLinkedList WCycles for the above 2 linked lists: Case3, both have cycles, but cycles are disjoint. they cannot overlap" << std::endl;
			return nullptr;
		}

		//now cycleBegin1_ == cycleBegin2: both lists have same cycle

		/*
		1. Calculate the distance from head1 to cycleBegin1 and distance from head2 to cycleBegin2
		   then calculate the difference between the two
		*/
		int len1 = 0;//len from head1 to cycleBegin1
		ListNode * h1 = head1;
		while (h1 != cycleBegin1)
		{
			h1 = h1->next;
			++len1;
		}
		int len2 = 0;//len from head2 to cycleBegin2
		ListNode * h2 = head2;
		while (h2 != cycleBegin2)
		{
			h2 = h2->next;
			++len2;
		}
		int diff = std::abs(len1 - len2);

		/*
		2. advance the head of longer distance from head to cycleBegin
		   so that both heads have same distances from themselves to their cycleBegins
		*/
		ListNode * longer = len1 > len2 ? head1 : head2;
		ListNode * shorter = len1 <= len2 ? head1 : head2;
		ListNode * longerCB = len1 > len2 ? cycleBegin1 : cycleBegin2;
		ListNode * shorterCB = len1 <= len2 ? cycleBegin1 : cycleBegin2;

		while (diff-- > 0)
			longer = longer->next;

		/*
		3. now both heads have same distances from themselves to their cycleBegins
		   advance both heads until they meet each other, or one of them reaches its cycleBegin
		*/
		while (longer != shorter && longer != longerCB && shorter != shorterCB)
		{
			longer = longer->next;
			shorter = shorter->next;
		}

		/*
		4. 2 sub-cases:
		   if both heads meet each other before any of them reaches its cycleBegin: overlap first occurs before the cycle starts
		   
		    1 -> 2 -> 3 -> 4
		                    v
					         5 -> 6 -> 7 -> 8 -> 9		firstIntersection=5, longerCB=7, shorterCB=7
						    ^          ^_________|
           11-> 12-> 13-> 14

		   otherwise, the first overlapping node is not unique, so we can return any node on the cycle
		   
		    1 -> 2 -> 3 -> 4
		                    v
					         5 -> 6 -> 7 -> 8 -> 9		longerCB=5, shorterCB=13
						    ^                    |
           11-> 12-> 13-> 14                     |
		             ^___________________________|
		*/
		ListNode * intersection = longer == shorter ? longer : longerCB;

		std::ostringstream oss;
		PrintLinkedList<ListNode, std::ostringstream>(head1, oss);
		PrintLinkedList<ListNode, std::ostringstream>(head2, oss);
		std::cout << oss.str();
		std::cout << "YIntersectionLinkedList WCycles for the above 2 linked lists: Case4, both have joint cycles, with intersection=" << intersection->val << ", longerCB=" << longerCB->val << ", shorterCB=" << shorterCB->val << std::endl;
		return intersection;
	}

private:
	ListNode * GetCycleBegin(ListNode * head)
	{
		if (head == NULL || head->next == NULL) return NULL;

		/*
		1. advance one ptr 1 node/step, the other ptr 2 nodes/step
		stop when they meet
		*/
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

		/*
		2. find the cycle length
		*/
		int cycleLen = 0;
		do
		{
			++cycleLen;
			fastNode = fastNode->next;
		} while (fastNode != slowNode);

		/*
		3. find the node with cycle length from head,
		then advance it as well as head until they meet
		*/
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

public:
	static void DeleteLinkedList(ListNode * head1, ListNode * head2, ListNode * intersection)
	{
		while (head1 && head1 != intersection)
		{
			ListNode * del = head1;
			//std::cout << del->val << std::endl;
			head1 = head1->next;
			delete del;
		}
		while (head2 && head2 != intersection)
		{
			ListNode * del = head2;
			//std::cout << del->val << std::endl;
			head2 = head2->next;
			delete del;
		}
		while (intersection)
		{
			ListNode * del = intersection;
			//std::cout << del->val << std::endl;
			intersection = intersection->next;
			delete del;
		}
	}

	static void DeleteLinkedList(ListNode * head1, ListNode * head2)
	{
		std::unordered_set<ListNode *> map;
		while (head1 != NULL || head2 != NULL)
		{
			if (map.find(head1) == map.end())//doesn't exist
			{
				map.insert(head1);
				head1 = head1->next;
			}
			else if (map.find(head2) == map.end())//doesn't exist
			{
				map.insert(head2);
				head2 = head2->next;
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
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->NULL
[0,11]->[1,12]->[2,13]->[3,14]->[4,5]->[5,6]->[6,7]->[7,8]->NULL
YIntersectionLinkedList for the above 2 linked lists: 5
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->[9,13]->[10,14]->
                              ^________________________________________________|
[0,11]->[1,12]->[2,13]->[3,14]->[4,5]->[5,6]->[6,7]->[7,8]->[8,9]->
                  ^_______________________________________________|
YIntersectionLinkedList WCycles for the above 2 linked lists: Case4, both have joint cycles, with intersection=5, longerCB=5, shorterCB=13
*/
#endif