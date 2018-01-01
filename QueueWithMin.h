#ifndef QUEUE_WITH_MIN_H
#define QUEUE_WITH_MIN_H
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Implement a queue with max API
http://www.careercup.com/question?id=7263132
http://stackoverflow.com/questions/4802038/implement-a-queue-in-which-push-rear-pop-front-and-get-min-are-all-consta
http://www.keithschwarz.com/interesting/code/?dir=min-queue
Implement a queue with a GetMin() method in const time.

Push: amortized O(1) time
Pop: O(1) time
Front: O(1) time
Min: O(1) time

See also MaxBandwidthOverWindowTimeInterval.h, SubArrWLessEqualMinMaxDiff.h
*/
class QueueWithMin
{
	std::deque<int> m_que;
	std::deque<std::pair<int, int> > m_sortedQue;//first: min value (in ascending order from front), second: count
public:
	QueueWithMin() : m_que(), m_sortedQue()
	{}
	~QueueWithMin(){}

	void Push(int v)
	{
		if (this->Empty())
			m_sortedQue.push_back(std::make_pair(v, 1));
		else
		{
			while (!m_sortedQue.empty() && m_sortedQue.back().first > v)
				m_sortedQue.pop_back();
			if (!m_sortedQue.empty() && m_sortedQue.back().first == v)
				++m_sortedQue.back().second;
			else
				m_sortedQue.push_back(std::make_pair(v, 1));
		}
		m_que.push_back(v);
	}
	void Pop()
	{
		if (this->Empty())
			throw std::runtime_error("");

		int v = m_que.front();
		if (v == m_sortedQue.front().first)
		{
			--m_sortedQue.front().second;
			if (m_sortedQue.front().second == 0)
				m_sortedQue.pop_front();
		}
		m_que.pop_front();
	}
	int Front()
	{
		if (this->Empty())
			throw std::runtime_error("");

		return m_que.front();
	}
	int Min()
	{
		if (this->Empty())
			throw std::runtime_error("");

		return m_sortedQue.front().first;
	}

	int Size() const
	{
		return m_que.size();
	}
	bool Empty() const
	{
		return m_que.empty();
	}

	void Print()
	{
		std::cout << "QueuekWithMin: \"" << Debug::ToStr1D<int>()(m_que) << "\", \"" << Debug::ToStr1D<int>()(m_sortedQue) << "\", Min: \"" << this->Min() << "\"" << std::endl;
	}
};
/*
QueuekWithMin: "10, 14, 9, 11, 9, 13", "[9,2], [13,1]", Min: "9"
QueuekWithMin: "11, 9, 13", "[9,1], [13,1]", Min: "9"
QueuekWithMin: "11, 9, 13, 5, 7, 8", "[5,1], [7,1], [8,1]", Min: "5"
*/
#endif