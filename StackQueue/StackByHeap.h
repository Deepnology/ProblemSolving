#ifndef STACK_BY_HEAP_H
#define STACK_BY_HEAP_H
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
/*
Elements of programming interview, Heap: Implement stack and queue APIs using heaps
Implement a stack API using a heap.
We keep track an order number along with each element.
When pushing a new element, increment the order.
Use a maxHeap to always keep the latest element with the largest order on the top.

See also QueueByHeap.h
*/
class StackByHeap
{
	struct SmallerThanComp
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first < b.first;
		}
	};
	int m_order = 0;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, SmallerThanComp> m_maxHeap;//first: order, second: val
public:
	StackByHeap(){}
	~StackByHeap(){}

	void Push(int v)
	{
		m_maxHeap.push(std::make_pair(m_order++, v));
	}
	int Pop()
	{
		int res = m_maxHeap.top().second;
		m_maxHeap.pop();
		return res;
	}
	const int & Top() const
	{
		return m_maxHeap.top().second;
	}

	void Print()
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, SmallerThanComp> copy(m_maxHeap);
		std::ostringstream oss;
		while (!copy.empty())
		{
			oss << "[" << copy.top().first << "," << copy.top().second << "]";
			copy.pop();
			if (!copy.empty())
				oss << ", ";
		}
		std::cout << "StackByHeap: " << oss.str() << std::endl;
	}
};
/*
StackByHeap: [4,15], [3,14], [2,13], [1,12], [0,11]
StackByHeap: [2,13], [1,12], [0,11]
StackByHeap: [6,17], [5,16], [2,13], [1,12], [0,11]
*/
#endif