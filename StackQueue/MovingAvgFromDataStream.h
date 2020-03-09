#ifndef MOVING_AVG_FROM_DATA_STREAM_H
#define MOVING_AVG_FROM_DATA_STREAM_H
#include "Debug.h"
/*
Leetcode: Moving Average From Data Stream
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.
For example,
MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
*/
class MovingAvgFromDataStream
{
public:
	MovingAvgFromDataStream(int size): m_size(size), m_que(), m_sum(0)
	{}
	~MovingAvgFromDataStream() {}

	double next(int val)
	{
		if ((int)m_que.size() == m_size)
		{
			m_sum -= m_que.front();
			m_que.pop();
		}
		m_sum += val;
		m_que.push(val);
		double avg = (double)m_sum / (double)m_que.size();

		std::cout << "MovingAvgFromDataStream next for \"" << val << "\": sum of \"(" << Debug::ToStr1D<int>()(m_que) << ") / " << m_que.size() << "\" = " << avg << std::endl;
		return avg;
	}

private:
	int m_size;
	std::queue<int> m_que;
	double m_sum; // sum of all int in m_que
};
/*
MovingAvgFromDataStream next for "1": sum of "(1) / 1" = 1
MovingAvgFromDataStream next for "10": sum of "(1, 10) / 2" = 5.5
MovingAvgFromDataStream next for "3": sum of "(1, 10, 3) / 3" = 4.66667
MovingAvgFromDataStream next for "5": sum of "(10, 3, 5) / 3" = 6
*/
#endif
