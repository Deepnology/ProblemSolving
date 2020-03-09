#ifndef CIRCULAR_QUEUE_BY_ARRAY_H
#define CIRCULAR_QUEUE_BY_ARRAY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, StacksAndQueues: Implement a circular queue
Dequeue: O(1) time
Enqueue: amortized O(1) time

use an array to store entries
keep track of the size of entries that have been enqueued/dequeued, a head index for dequeue, and a tail index for enqueue
enqueue: increment size, write entry into tail index, advance tail index circularly
dequeue: decrement size, advance head index circularly
special case: when the entry size is equal to the array size before enqueuing a new entry, need to resize the array

see also MinLexicographicStrRotation.h, RotatedStr.h, RotatedArray.h, DequeByCircularArray.h
*/
class CircularQueueByArray
{
	const int m_scaleFactor = 2;//for resizing only
	int m_head;//points to 1st element
	int m_tail;//points to next element of last element
	int m_count;//count of entries that have been enqueued but haven't been dequeued
	std::vector<int> m_data;
public:
	explicit CircularQueueByArray(int capacity) : m_head(0), m_tail(0), m_count(0), m_data(capacity)
	{}
	~CircularQueueByArray(){}

	void Enqueue(int v)//PushBack
	{
		if (m_count == m_data.size())//need to resize
		{
			std::rotate(m_data.begin(), m_data.begin() + m_head, m_data.end());//left rotate
			//std::rotate(first, middle, last). the middle will become the new first element, and [first, middle) elements will be append to back of [middle, last)

			m_head = 0;//reset
			m_tail = m_count;//reset
			m_data.resize(m_data.size() * m_scaleFactor);
		}
		m_data[m_tail] = v;//append the new element
		m_tail = (m_tail + 1) % m_data.size();//advance tail
		++m_count;//increment
	}
	int Dequeue()//PopFront
	{
		if (m_count == 0)
			throw std::runtime_error("");
		--m_count;//decrement
		int res = m_data[m_head];
		m_head = (m_head + 1) % m_data.size();//advance head
		return res;
	}
	int Size() const
	{
		return m_count;
	}
	void Print()
	{
		std::ostringstream oss;
		int N = m_data.size();
		for (int i = 0; i < N; ++i)
		{
			int digits = this->CountDigit(m_data[i]);
			if (m_head == i || m_tail == i)
				--digits;
			while (digits-- > 0)
			{
				oss << " ";
			}
			if (m_head == i && m_tail == i)
				oss << "^";
			else if (m_head == i)
				oss << "h";
			else if (m_tail == i)
				oss << "t";
			if (i != N - 1)
				oss << "  ";//", "
		}
		std::cout << Debug::ToStr1D<int>()(m_data) << std::endl;
		std::cout << oss.str() << std::endl;
	}
private:
	int CountDigit(int n)
	{
		if (n == 0)
			return 1;
		int count = 0;
		while (n)
		{
			n /= 10;
			++count;
		}
		return count;
	}
};
/*
CircularQueueByArray:
0, 0
^   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
h                                              t   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
   h                                           t   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
      h                                        t   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
         h                                     t   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
            h                                  t   
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 0
            h                                       t
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102
t           h                                          
103, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102
     t        h                                          
103, 104, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102
          t     h                                          
103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102
               t  h                                          
103, 104, 105, 106, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102
                    ^                                          
5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102, 103, 104, 105, 106, 107, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
h                                                                     t                                          
5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 101, 102, 103, 104, 105, 106, 107, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
h                                                                          t                                       
*/
#endif