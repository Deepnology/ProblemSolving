#ifndef QUEUE_BY_HEAP_H
#define QUEUE_BY_HEAP_H
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
/*
Elements of programming interview, Heap: Implement stack and queue APIs using heaps
Implement a queue API using a heap.
We keep track an order number along with each element.
When enqueuing a new element, decrement the order.
Use a maxHeap to always keep the oldest element with the largest order on the top.

See also StackByHeap.h
*/
class QueueByHeap
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
	QueueByHeap(){}
	~QueueByHeap(){}

	void Enqueue(int v)
	{
		m_maxHeap.push(std::make_pair(m_order--, v));
	}
	int Dequeue()
	{
		int res = m_maxHeap.top().second;
		m_maxHeap.pop();
		return res;
	}
	const int & Head() const
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
		std::cout << "QueueByHeap: " << oss.str() << std::endl;
	}
};
/*
QueueByHeap: [0,11], [-1,12], [-2,13], [-3,14], [-4,15]
QueueByHeap: [-2,13], [-3,14], [-4,15]
QueueByHeap: [-2,13], [-3,14], [-4,15], [-5,16], [-6,17]
*/
#endif