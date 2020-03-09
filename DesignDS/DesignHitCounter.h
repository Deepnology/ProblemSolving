#ifndef DESIGN_HIT_COUNTER_H
#define DESIGN_HIT_COUNTER_H
#include "Debug.h"
/*
Leetcode: Design Hit Counter
Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order
(ie, the timestamp is monotonically increasing).
You may assume that the earliest timestamp starts at 1.
It is possible that several hits arrive roughly at the same time.

Example:
HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);

// hit at timestamp 2.
counter.hit(2);

// hit at timestamp 3.
counter.hit(3);

// get hits at timestamp 4, should return 3.
counter.getHits(4);

// hit at timestamp 300.
counter.hit(300);

// get hits at timestamp 300, should return 4.
counter.getHits(300);

// get hits at timestamp 301, should return 3.
counter.getHits(301);
Follow up:
What if the number of hits per second could be very large? Does your design scale?
*/
class DesignHitCounter
{
public:
	DesignHitCounter() 
	{
		m_totalCount = 0;
		m_buf.resize(300);
	}
	~DesignHitCounter() {}

	void hit(int timestamp)
	{
		std::cout << "DesignHitCounter hit at \"" << timestamp << "\"" << std::endl;

		++m_totalCount;
		if (!m_queue.empty() && m_queue.back().first == timestamp)
		{
			++m_queue.back().second;
			return;
		}
		if (m_queue.size() == 300)
		{
			m_totalCount -= m_queue.front().second;
			m_queue.pop();
		}
		m_queue.push({ timestamp, 1 });
	}

	int getHits(int timestamp)
	{
		while (!m_queue.empty() && timestamp - m_queue.front().first >= 300)
		{
			m_totalCount -= m_queue.front().second;
			m_queue.pop();
		}

		std::cout << "DesignHitCounter getHits for \"" << timestamp << "\": " << m_totalCount << std::endl;
		return m_totalCount;
	}
private:
	std::queue<std::pair<int, int>> m_queue;//first: timestamp, second: hitCount
	int m_totalCount;


//=========================================================================================
public:
	void hit2(int timestamp)
	{
		std::cout << "DesignHitCounter hit2 at \"" << timestamp << "\"" << std::endl;

		int idx = timestamp % 300;
		if (m_buf[idx].first != timestamp)
		{
			m_buf[idx].first = timestamp;
			m_buf[idx].second = 1;
		}
		else
		{
			++m_buf[idx].second;
		}
	}

	int getHits2(int timestamp)
	{
		int res = 0;
		for (int i = 0; i < 300; ++i)
		{
			if (timestamp - m_buf[i].first < 300)
				res += m_buf[i].second;
		}

		std::cout << "DesignHitCounter getHits2 for \"" << timestamp << "\": " << res << std::endl;
		return res;
	}
private:
	std::vector<std::pair<int, int>> m_buf;//first: timestamp, second: hitCount
};
/*
DesignHitCounter hit at "1"
DesignHitCounter hit at "2"
DesignHitCounter hit at "3"
DesignHitCounter getHits for "4": 3
DesignHitCounter hit at "300"
DesignHitCounter getHits for "300": 4
DesignHitCounter getHits for "301": 3
DesignHitCounter hit2 at "1"
DesignHitCounter hit2 at "2"
DesignHitCounter hit2 at "3"
DesignHitCounter getHits2 for "4": 3
DesignHitCounter hit2 at "300"
DesignHitCounter getHits2 for "300": 4
DesignHitCounter getHits2 for "301": 3
*/
#endif
