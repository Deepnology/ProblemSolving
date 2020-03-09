#ifndef JOSEPHUS_PROBLEM_H
#define JOSEPHUS_PROBLEM_H
#include <vector>
#include <list>
#include <unordered_set>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Determine the critical height (Egg drop), variant:
Men numbered from 1 to n are arranged in a circle in clockwise order.
Every k-th man is removed, until only one man remains.
What is the number of the last man?
http://www.careercup.com/question?id=14467673
http://en.wikipedia.org/wiki/Josephus_problem
http://www.geeksforgeeks.org/josephus-problem-set-1-a-on-solution/
Given a circular single linked list.
Write a program that deletes every K-th node until only one node is left.
After K-th node is deleted, start the procedure from (K+1)-th node.

Recursion: O(n) time
*/
class JosephusProblem
{
public:
	JosephusProblem(){}
	~JosephusProblem(){}

	int GetSurvivorIdxRecur(int N, int K)//use 1-based index
	{
		int res = this->getSurvivorIdxRecur(N, K);
		std::cout << "JosephusProblem Recur for N, K = \"" << N << "\", \"" << K << "\": " << res << std::endl;
		return res;
	}
private:
	int getSurvivorIdxRecur(int N, int K)//use 1-based index
	{
		if (N == 1)
			return 1;
		else
			return (this->getSurvivorIdxRecur(N - 1, K) + K - 1) % N + 1;//+K: to get next startingIdx (toRemove), -1: convert to 0-base, %N using 0-base: circle, +1: convert to 1-base
		/*
		The position returned by getSurvivorIdxRecur(N-1,K) is adjusted 
		because the recursive call getSurvivorIdxRecur(N-1,K) considers the original position K%N + 1 as position 1
		*/
	}

public:
	int GetSurvivorIdxRecur2(int N, int K)//use 1-based index
	{
		int res = this->getSurvivorIdxRecur2(N, K, 1);
		std::cout << "JosephusProblem Recur2 for N, K = \"" << N << "\", \"" << K << "\": " << res << std::endl;
		return res;
	}
	int getSurvivorIdxRecur2(int N, int K, int startingIdx)//use 1-based index
	{
		if (N == 1)
			return 1;
		
		int nxtStartingIdx = (startingIdx + K - 2) % N + 1;//remove "startingIdx+K-1", conver to 0-base for %N: "startIdx+K-2", %N using 0-based to circle, convert to 1-base: +1
		int survivorIdx = this->getSurvivorIdxRecur2(N - 1, K, nxtStartingIdx);
		if (survivorIdx < nxtStartingIdx)
			return survivorIdx;
		else
			return survivorIdx + 1;//to skip nxtStartingIdx
	}

public:
	int GetSurvivorIdxIterate(int N, int K)//thinking: derived from recursion
	{
		int res = 0;//0-base
		for (int i = 1; i <= N; ++i)
		{
			std::cout << res + K << "%" << i << "=";
			res = (res + K) % i;//remove index "res+K", which is also the next startingIdx
			std::cout << res << std::endl;
		}
		res += 1;//convert to 1-base
		std::cout << "JosephusProblem Iterate for N, K = \"" << N << "\", \"" << K << "\": " << res << std::endl;
		return res;
	}

public:
	struct ListNode
	{
		ListNode(int v) : val(v), next(nullptr) {}
		ListNode * next;
		int val;
	};
	//O(K*N) time, O(N^2) time when K=N
	ListNode * GetLastNodeIterate(ListNode * head, int K)//head is already circular
	{
		ListNode * cur = head;
		while (cur != nullptr && cur->next != cur)
		{
			for (int i = 0; i < K - 1; ++i)//advance K-1 nodes to include the beginning node
				cur = cur->next;
			
			/*
			to delete cur node in a single linked list:
			1. copy the content of cur->next to cur
			2. then delete cur->next
			*/
			std::cout << "delete: " << cur->val << std::endl;
			ListNode * toDel = cur->next;
			cur->next = toDel->next;
			cur->val = toDel->val;
			delete toDel;
		}

		return cur;
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
JosephusProblem Recur for N, K = "5", "2": 3
JosephusProblem Recur2 for N, K = "5", "2": 3
2%1=0
2%2=0
2%3=2
4%4=0
2%5=2
JosephusProblem Iterate for N, K = "5", "2": 3
delete: 2
delete: 4
delete: 1
delete: 5
JosephusProblem GetLastNodeIterate for K = 2:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->
  ^_______________________________|
[0,3]->
  ^___|

JosephusProblem Recur for N, K = "8", "5": 3
JosephusProblem Recur2 for N, K = "8", "5": 3
5%1=0
5%2=1
6%3=0
5%4=1
6%5=1
6%6=0
5%7=5
10%8=2
JosephusProblem Iterate for N, K = "8", "5": 3
delete: 5
delete: 2
delete: 8
delete: 7
delete: 1
delete: 4
delete: 6
JosephusProblem GetLastNodeIterate for K = 5:
[0,1]->[1,2]->[2,3]->[3,4]->[4,5]->[5,6]->[6,7]->[7,8]->
  ^____________________________________________________|
[0,3]->
  ^___|

*/
#endif