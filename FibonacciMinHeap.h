#ifndef FIBONACCI_MIN_HEAP_H
#define FIBONACCI_MIN_HEAP_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include "Debug.h"
#include "PrintLinkedList.h"
/*
http://keithschwarz.com/interesting/code/?dir=fibonacci-heap

FibonacciHeap:
Root level is a circular doubly linked list where the min node is pointed by root


				LinkedList	FibonacciHeap
Insert			O(1)		O(1)
FindMin			O(n)		O(1)
DeleteMin		O(n)		O(n), O(logn) amortized
Union			O(1)		O(1)

DecreaseKey		O(1)		O(n), O(1) amortized
DeleteNode		O(1)		O(n), O(logn) amortized


*/
class FibonacciMinHeap
{
public:
	struct HeapNode
	{
		HeapNode(int val) : next(this), prev(this), parent(nullptr), child(nullptr),
		val(val), degree(0), mark(false)
		{}
		HeapNode * next;//next node
		HeapNode * prev;//prev node
		HeapNode * parent;//parent node
		HeapNode * child;//one of the child node
		int val;
		int degree;//number of all the nodes of the circular doubly linked list where the child node resides in
		bool mark;
	};
private:
	HeapNode * m_minNode;
	int m_nodeCount;
public:
	FibonacciMinHeap() : m_minNode(nullptr), m_nodeCount(0)
	{}
	FibonacciMinHeap(const std::vector<int> & v) : m_minNode(nullptr), m_nodeCount(0)
	{
		int N = v.size();
		for (int i = 0; i < N; ++i)
			this->Insert(v[i]);
	}
	~FibonacciMinHeap()
	{
		this->MakeEmpty();
	}
	bool IsEmpty() const
	{
		return m_minNode == nullptr;
	}
	void MakeEmpty()
	{
		if (m_minNode)
			this->deleteRecur(m_minNode);
	}
private:
	void deleteRecur(HeapNode *& head)
	{
		HeapNode * curNode = head->next;
		while (curNode != head)//check if reaching head of doubly linked list
		{
			if (curNode->child)
				this->deleteRecur(curNode->child);
			HeapNode * prevNode = curNode;
			curNode = curNode->next;
			//std::cout << "deleteA " << prevNode->val << std::endl;
			delete prevNode;
			prevNode = nullptr;
		}
		if (head->child)
			this->deleteRecur(head->child);
		//std::cout << "deleteB " << head->val << std::endl;
		delete head;
		head = nullptr;
	}
public:
	const int & FindMin() const
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		std::cout << "FibonacciHeap FindMin: " << m_minNode->val << std::endl;
		return m_minNode->val;
	}
	HeapNode * Insert(int val)
	{
		HeapNode * node = new HeapNode(val);
		m_minNode = merge2DoublyLinkedLists(m_minNode, node);
		++m_nodeCount;
		std::cout << "FibonacciMinHeap Insert: " << val << std::endl;
		return node;
	}
	HeapNode * DeleteMin()
	{
		if (this->IsEmpty())
			throw std::runtime_error("");
		std::cout << "FibonacciMinHeap DeleteMin: " << m_minNode->val << std::endl;
		--m_nodeCount;
		HeapNode * curMinNode = m_minNode;
		if (m_minNode->next == m_minNode)
			m_minNode = nullptr;
		else
		{
			m_minNode->prev->next = m_minNode->next;
			m_minNode->next->prev = m_minNode->prev;
			m_minNode = m_minNode->next;
		}
		if (curMinNode->child != nullptr)
		{
			HeapNode * cur = curMinNode->child;
			do
			{
				cur->parent = nullptr;
				cur = cur->next;
			} while (cur != curMinNode->child);
		}
		m_minNode = merge2DoublyLinkedLists(m_minNode, curMinNode->child);
		if (m_minNode == nullptr)
			return curMinNode;
		std::vector<HeapNode *> treeTable;
		std::vector<HeapNode *> toVisit;
		for (HeapNode * cur = m_minNode; toVisit.empty() || toVisit[0] != cur; cur = cur->next)
			toVisit.push_back(cur);
		for (auto & cur : toVisit)
		{
			while (true)
			{
				while (cur->degree >= (int)treeTable.size())
					treeTable.push_back(nullptr);

				if (treeTable[cur->degree] == nullptr)
				{
					treeTable[cur->degree] = cur;
					break;
				}

				HeapNode * other = treeTable[cur->degree];
				treeTable[cur->degree] = nullptr;

				HeapNode * min = other->val < cur->val ? other : cur;
				HeapNode * max = other->val < cur->val ? cur : other;

				max->next->prev = max->prev;
				max->prev->next = max->next;

				max->next = max->prev = max;
				min->child = merge2DoublyLinkedLists(min->child, max);

				max->parent = min;

				max->mark = false;

				++min->degree;

				cur = min;
			}
			if (cur->val <= m_minNode->val)
				m_minNode = cur;
		}
		return curMinNode;
	}
	void DecreaseKey(HeapNode * node, int val)
	{
		if (val > node->val)
			throw std::runtime_error("");
		std::cout << "FibonacciMinHeap DecreaseKey for \"" << node->val << "\": " << val << std::endl;
		this->decreaseKeyUnchecked(node, val);
	}
	void Delete(HeapNode * node)
	{
		this->decreaseKeyUnchecked(node, INT_MIN);
		this->DeleteMin();
	}
	void Merge(FibonacciMinHeap & rhs)
	{
		if (this == &rhs)
			return;
		m_minNode = merge2DoublyLinkedLists(m_minNode, rhs.m_minNode);
		m_nodeCount += rhs.m_nodeCount;
		rhs.m_minNode = nullptr;
		rhs.m_nodeCount = 0;
	}
private:
	/*
	Cuts a node from its parent.
	If the parent was already marked, recursively cuts that node from its parent as well.
	*/
	void cutNodeRecur(HeapNode * node)
	{
		//1. un-mark the current node
		node->mark = false;

		if (node->parent == nullptr)
			return;

		//2. link current node's prev and next nodes
		if (node->next != node)
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}

		//3.1. update its parent node's child ptr if that ptr points to the current node
		if (node->parent->child == node)
		{
			if (node->next != node)
				node->parent->child = node->next;
			else
				node->parent->child = nullptr;
		}
		//3.2. update its parent node's degree
		--node->parent->degree;

		//4. merge the current node into the topmost roots circular doubly linked list
		node->prev = node->next = node;
		m_minNode = merge2DoublyLinkedLists(m_minNode, node);

		//5. recursively cut its parent node if it was marked, else, mark its parent node (that its child node was cut)
		if (node->parent->mark)
			this->cutNodeRecur(node->parent);
		else
			node->parent->mark = true;

		node->parent = nullptr;
	}
	void decreaseKeyUnchecked(HeapNode * node, int val)
	{
		node->val = val;
		if (node->parent != nullptr && node->val <= node->parent->val)
			this->cutNodeRecur(node);

		//if the node's val is smaller than m_minNode's val,
		//this node must have already been merged into the topmost roots circular doubly linked list in cutNodeRecur()
		//so we can update m_minNode to point to that node in the topmost roots circular doubly linked list
		if (node->val <= m_minNode->val)
			m_minNode = node;
	}
	/*
	merge 2 doubly linked lists
	O(1) time
	we assume h1 and h2 are the min nodes of the linked lists they are in,
	and return a pointer to whichever is smaller
	*/
	static HeapNode * merge2DoublyLinkedLists(HeapNode * h1, HeapNode * h2)
	{
		if (h1 == nullptr && h2 == nullptr)
			return nullptr;
		else if (h1 != nullptr && h2 == nullptr)
			return h1;
		else if (h1 == nullptr && h2 != nullptr)
			return h2;
		else
		{
			/* This is actually not as easy as it seems.  The idea is that we'll
			* have two lists that look like this:
			*
			* +----+     +----+     +----+
			* |    |--N->|one |--N->|    |
			* |    |<-P--|    |<-P--|    |
			* +----+     +----+     +----+
			*
			*
			* +----+     +----+     +----+
			* |    |--N->|two |--N->|    |
			* |    |<-P--|    |<-P--|    |
			* +----+     +----+     +----+
			*
			* And we want to relink everything to get
			*
			* +----+     +----+     +----+---+
			* |    |--N->|one |     |    |   |
			* |    |<-P--|    |     |    |<+ |
			* +----+     +----+<-\  +----+ | |
			*                  \  P        | |
			*                   N  \       N |
			* +----+     +----+  \->+----+ | |
			* |    |--N->|two |     |    | | |
			* |    |<-P--|    |     |    | | P
			* +----+     +----+     +----+ | |
			*              ^ |             | |
			*              | +-------------+ |
			*              +-----------------+
			*
			*/
			HeapNode * h1Next = h1->next;
			h1->next = h2->next;
			h1->next->prev = h1;
			h2->next = h1Next;
			h2->next->prev = h2;
			return h1->val < h2->val ? h1 : h2;
		}
	}
	
public:
	void Print()
	{
		std::ostringstream oss;
		oss << "FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):" << std::endl;
		this->printRecur(nullptr, m_minNode, oss);
		std::cout << oss.str() << std::endl;
	}
private:
	void printRecur(HeapNode * prevParentNode, HeapNode * curChildHeadNode, std::ostringstream & oss)
	{
		if (prevParentNode == nullptr)
			oss << "Root:" << std::endl;
		else
			oss << prevParentNode->val << "'s children:" << std::endl;
		PrintLinkedList<HeapNode, std::ostringstream>(curChildHeadNode, oss);
		HeapNode * curParentNode = curChildHeadNode;
		do
		{
			HeapNode * curChildNode = curParentNode->child;
			if (curChildNode != nullptr)
			{
				this->printRecur(curParentNode, curChildNode, oss);
			}

		} while ((curParentNode = curParentNode->next) != curChildHeadNode);
	}

};

template<>
std::string PrintLinkedList<FibonacciMinHeap::HeapNode, std::ostringstream>::SelectVal2(int index, FibonacciMinHeap::HeapNode * curNode)
{
	//if (curNode->mark)
	//	return std::to_string(1);
	//else
	//	return std::to_string(0);
	return std::to_string(curNode->degree);
}
/*
FibonacciMinHeap Insert: 41
FibonacciMinHeap Insert: 67
FibonacciMinHeap Insert: 34
FibonacciMinHeap Insert: 0
FibonacciMinHeap Insert: 69
FibonacciMinHeap Insert: 24
FibonacciMinHeap Insert: 78
FibonacciMinHeap Insert: 58
FibonacciMinHeap Insert: 62
FibonacciMinHeap Insert: 64
FibonacciMinHeap Insert: 5
FibonacciMinHeap Insert: 45
FibonacciMinHeap Insert: 81
FibonacciMinHeap Insert: 27
FibonacciMinHeap Insert: 61
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[0,0]->[0,61]->[0,27]->[0,81]->[0,45]->[0,5]->[0,64]->[0,62]->[0,58]->[0,78]->[0,24]->[0,69]->[0,67]->[0,41]->[0,34]->
  ^__________________________________________________________________________________________________________________|

FibonacciMinHeap DeleteMin: 0
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,5]->[2,24]->[1,34]->
  ^___________________|
5's children:
[2,27]->[0,64]->[1,58]->
  ^____________________|
27's children:
[1,45]->[0,61]->
  ^____________|
45's children:
[0,81]->
  ^____|
58's children:
[0,62]->
  ^____|
24's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|
34's children:
[0,41]->
  ^____|

FibonacciMinHeap DeleteMin: 5
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,24]->[0,64]->[2,34]->
  ^____________________|
24's children:
[2,27]->[0,78]->[1,67]->
  ^____________________|
27's children:
[1,45]->[0,61]->
  ^____________|
45's children:
[0,81]->
  ^____|
67's children:
[0,69]->
  ^____|
34's children:
[0,41]->[1,58]->
  ^____________|
58's children:
[0,62]->
  ^____|

FibonacciMinHeap DeleteMin: 24
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,27]->[2,64]->
  ^____________|
27's children:
[2,34]->[0,61]->[1,45]->
  ^____________________|
34's children:
[0,41]->[1,58]->
  ^____________|
58's children:
[0,62]->
  ^____|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|

FibonacciMinHeap DeleteMin: 27
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,34]->[0,61]->[1,45]->
  ^____________________|
34's children:
[0,41]->[2,64]->[1,58]->
  ^____________________|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|
58's children:
[0,62]->
  ^____|
45's children:
[0,81]->
  ^____|

FibonacciMinHeap DeleteMin: 34
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,41]->[1,58]->
  ^____________|
41's children:
[1,45]->[2,64]->[0,61]->
  ^____________________|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|
58's children:
[0,62]->
  ^____|

FibonacciMinHeap Insert: 51
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,41]->[0,51]->[1,58]->
  ^____________________|
41's children:
[1,45]->[2,64]->[0,61]->
  ^____________________|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|
58's children:
[0,62]->
  ^____|

FibonacciMinHeap Insert: 99
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[3,41]->[0,99]->[0,51]->[1,58]->
  ^____________________________|
41's children:
[1,45]->[2,64]->[0,61]->
  ^____________________|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|
58's children:
[0,62]->
  ^____|

FibonacciMinHeap DecreaseKey for "51": 24
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[0,24]->[1,58]->[3,41]->[0,99]->
  ^____________________________|
58's children:
[0,62]->
  ^____|
41's children:
[1,45]->[2,64]->[0,61]->
  ^____________________|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|

FibonacciMinHeap DecreaseKey for "99": 37
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[0,24]->[1,58]->[3,41]->[0,37]->
  ^____________________________|
58's children:
[0,62]->
  ^____|
41's children:
[1,45]->[2,64]->[0,61]->
  ^____________________|
45's children:
[0,81]->
  ^____|
64's children:
[1,67]->[0,78]->
  ^____________|
67's children:
[0,69]->
  ^____|

FibonacciMinHeap Insert: 4
FibonacciMinHeap Insert: 2
FibonacciMinHeap Insert: 3
FibonacciMinHeap Insert: 5
FibonacciMinHeap Insert: 7
FibonacciMinHeap Insert: 9
FibonacciMinHeap Insert: 8
FibonacciMinHeap Insert: 1
FibonacciMinHeap Insert: 10
FibonacciMinHeap Insert: 15
FibonacciMinHeap Insert: 13
FibonacciMinHeap Insert: 18
FibonacciMinHeap Insert: 20
FibonacciMinHeap Insert: 31
FibonacciMinHeap (CircularDoublyLinkedList) ([degree,val]):
Root:
[0,1]->[0,31]->[0,20]->[0,18]->[0,13]->[0,15]->[0,10]->[0,8]->[0,9]->[0,7]->[0,5]->[0,3]->[0,4]->[0,2]->
  ^____________________________________________________________________________________________________|

*/
#endif