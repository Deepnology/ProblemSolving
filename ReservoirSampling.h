#ifndef RESERVOIR_SAMPLING_H
#define RESERVOIR_SAMPLING_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
Elements of programming interview, Array: Sample online data
http://www.keithschwarz.com/interesting/code/?dir=random-sample
http://www.geeksforgeeks.org/reservoir-sampling/
Cracking the coding interview: Hard

Randomly choose k samples from a list of n items, where n is either a very large or unknown number.
Typically n is large enough that the list doesn't fit into main memory.
For example, a list of search queries in Google and Facebook.
So we are given a big array (or stream) for numbers, and we need to write an efficient function to randomly select k numbers
where 1 <= k <= n.

Leetcode: Linked List Random Node
Given a singly linked list, return a random node's value from the linked list.
Each node must have the same probability of being chosen.
Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?
Example:
// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);
// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();

Solution 1: O(k^2) time (trivial)
Create an array reservoir[] with size k.
One by one randomly pick an item from stream[] and put in reservoir[] for k times.
Need to search if the current selected item was selected before in the reservoir, which takes O(k) time

Solution 2: O(n) time (reservoir sampling)
Create an array reservoir[] with size k.
Save the first k elements in reservoir[] from input stream.
Keep track of the total count of elements from input stream.
Iterate over the rest elements and compute a randIdx=rand()%totalCount, if randIdx<k, swap reservoir[randIdx] with current element.

Proof of reservoir sampling for special case k==1: The probability to choose the 2nd element is 1/n (suppose the stream length is n).
The probability to choose the 2nd element = (1/2) * (2/3) * (3/4) * ... * (n-1)/n = 1/n.
where
1/2: choose the 2nd element when there are 2 elements
2/3: choose an element other than the 2nd element when there are 3 elements
...

The probability to choose the 5th element = (1/5) * (5/6) * (6/7) * ... * (n-1)/n = 1/n.
where
1/5: choose the 5th element when there are 5 elements
5/6: choose an element other than the 5th element when there are 6 elements
...

The probability to choose the nth element = 1/n.
*/
class ReservoirSampling
{
public:
	ReservoirSampling(){}
	~ReservoirSampling(){}

	std::vector<int> SolveIterate(const std::vector<int> & stream, int count)
	{
		int N = stream.size();

		/*init reservoir[] with first "count" items from stream[]*/
		std::vector<int> reservoir;
		for (int i = 0; i < count; ++i)
			reservoir.push_back(stream[i]);

		srand((unsigned int)time(NULL));

		/*from the (count+1)-th item*/
		for (int i = count; i < N; ++i)
		{
			/*pick a random index j from 0 to current index and assign current item in stream[i] to reservoir[j]*/
			int j = rand() % (i + 1);
			if (j < count)
				reservoir[j] = stream[i];
		}
		std::cout << "ReservoirSampling Iterate for \"" << count << " out of " << Debug::ToStr1D<int>()(stream) << "\": " << Debug::ToStr1D<int>()(reservoir) << std::endl;
		return reservoir;
	}

	std::vector<int> SolveRecur(const std::vector<int> & stream, int count)
	{
		std::vector<int> reservoir;
		for (int i = 0; i < count; ++i)
			reservoir.push_back(stream[i]);
		srand((unsigned int)time(NULL));
		this->solveRecur(stream, count, reservoir, count);
		std::cout << "ReservoirSampling Recur for \"" << count << " out of " << Debug::ToStr1D<int>()(stream) << "\": " << Debug::ToStr1D<int>()(reservoir) << std::endl;
		return reservoir;
	}
private:
	void solveRecur(const std::vector<int> & stream, int count, std::vector<int>& reservoir, int cur)
	{
		int N = stream.size();
		if (cur == N)
			return;
		int j = rand() % (cur + 1);
		if (j < count)
			reservoir[j] = stream[cur];
		this->solveRecur(stream, count, reservoir, cur + 1);
	}

public:
	std::vector<int> Online(std::istringstream & iss, int k)//better
	{
		std::vector<int> res;
		int buf;

		//stores the first k elements
		for (int i = 0; i < k && iss >> buf; ++i)
			res.emplace_back(buf);

		//after the first k elements
		int count = k;
		while (iss >> buf)
		{
			int curRand = rand() % (++count);
			if (curRand < k)
				res[curRand] = buf;
		}

		std::cout << "ReservoirSampling Online for \"" << k << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

public:
	struct ListNode
	{
		ListNode(int x) : val(x), next(NULL) {}
		int val;
		ListNode * next;
	};
	int GetRandomNodeVal(ListNode * head)//special case for k=1
	{
		int res = head->val;

		//after the first 1 element
		head = head->next;
		int count = 1;
		while (head)
		{
			int curRand = rand() % (++count);
			if (curRand < 1)
				res = head->val;
			head = head->next;
		}

		std::cout << "ReservoirSampling GetRandomNodeVal: " << res << std::endl;
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
ReservoirSampling Iterate for "8 out of 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 10, 14, 2, 3, 13, 5, 15, 7
ReservoirSampling Recur for "8 out of 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15": 10, 14, 2, 3, 13, 5, 15, 7
ReservoirSampling Online for "8": 0, 12, 2, 8, 4, 15, 9, 14
[0,0]->[1,1]->[2,2]->[3,3]->[4,4]->[5,5]->[6,6]->[7,7]->NULL

ReservoirSampling GetRandomNodeVal: 5
*/
#endif