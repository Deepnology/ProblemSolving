#ifndef DEQUE_BY_CIRCULAR_ARRAY_H
#define DEQUE_BY_CIRCULAR_ARRAY_H
#include "Debug.h"
/*
Leetcode: Design Circular Deque
http://www.geeksforgeeks.org/implementation-deque-using-circular-array/
see also CircularQueueByArray.h
*/
class DequeByCircularArray
{
	const int m_scaleFactor = 2;//for resizing only
	int m_head;//points to 1st element
	int m_tail;//points to next element of last element
	int m_count;//count of entries that have been enqueued but haven't been dequeued
	std::vector<int> m_data;
public:
	explicit DequeByCircularArray(int capacity) : m_head(0), m_tail(0), m_count(0), m_data(capacity)
	{}
	~DequeByCircularArray() {}

	void PushBack(int v)//same as CircularQueueByArray.h
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
	void PushFront(int v)
	{
		if (m_count == m_data.size())//need to resize
		{
			std::rotate(m_data.begin(), m_data.begin() + m_head, m_data.end());//left rotate
			//std::rotate(first, middle, last). the middle will become the new first element, and [first, middle) elements will be append to back of [middle, last)

			m_head = 0;//reset
			m_tail = m_count;//reset
			m_data.resize(m_data.size() * m_scaleFactor);
		}
		m_head = (m_head - 1 + m_data.size()) % m_data.size();//advance head to end of array
		m_data[m_head] = v;//append the new element
		++m_count;//increment
	}
	int PopFront()//same as CircularQueueByArray.h
	{
		if (m_count == 0)
			throw std::runtime_error("");
		--m_count;//decrement
		int res = m_data[m_head];
		m_head = (m_head + 1) % m_data.size();//advance head
		return res;
	}
	int PopBack()
	{
		if (m_count == 0)
			throw std::runtime_error("");
		--m_count;//decrement
		int res = m_data[(m_tail - 1 + m_data.size()) % m_data.size()];//point to prev of tail
		m_tail = (m_tail - 1 + m_data.size()) % m_data.size();//advance tail to left
		return res;
	}
	std::pair<int,bool> Get(int idx)//O(1) time
	{
		if (idx < 0 || idx >= m_count)
			return{ 0,false };
		return{ m_data[(m_head + idx) % m_data.size()],true };
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
DequeByCircularArray:
0, 0
^   
8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 14, 13, 12, 11, 10, 9
                        t      h                   
8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 14, 13, 12, 11, 10, 9
                     t         h                   
8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 14, 13, 12, 11, 10, 9
                  t            h                   
8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 14, 13, 12, 11, 10, 9
               t               h                   
8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 14, 13, 12, 11, 10, 9
            t                  h                   
8, 7, 6, 5, 4, 3, 2, 1, 0, 101, 14, 13, 12, 11, 10, 9
            t                h                       
8, 7, 6, 5, 4, 3, 2, 1, 102, 101, 14, 13, 12, 11, 10, 9
            t             h                            
8, 7, 6, 5, 4, 3, 2, 103, 102, 101, 14, 13, 12, 11, 10, 9
            t          h                                 
8, 7, 6, 5, 4, 3, 104, 103, 102, 101, 14, 13, 12, 11, 10, 9
            t       h                                      
8, 7, 6, 5, 4, 105, 104, 103, 102, 101, 14, 13, 12, 11, 10, 9
            t    h                                           
8, 7, 6, 5, 106, 105, 104, 103, 102, 101, 14, 13, 12, 11, 10, 9
              ^                                                
106, 105, 104, 103, 102, 101, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107
                                                                 t                                              h
106, 105, 104, 103, 102, 101, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 108, 107
                                                                 t                                           h     
108
107
106
105
104
103
102
101
14
13
12
11
10
9
8
7
6
5
*/
#endif
