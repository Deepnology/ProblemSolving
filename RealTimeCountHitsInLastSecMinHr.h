#ifndef REAL_TIME_COUNT_HITS_IN_LAST_SEC_MIN_HR_H
#define REAL_TIME_COUNT_HITS_IN_LAST_SEC_MIN_HR_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Debug.h"
/*
http://www.careercup.com/question?id=5654693460049920
http://stackoverflow.com/questions/17562089/how-to-count-number-of-requests-in-last-second-minute-and-hour
*/
class RealTimeCountHitsInLastSecMinHr
{
public:
	RealTimeCountHitsInLastSecMinHr()
	{
		m_curTime = currentTimeSeconds();
		m_first = m_hits.end();
		m_second = m_hits.end();
		m_third = m_hits.end();
		m_firstCount = 0;
		m_secondCount = 0;
		m_thirdCount = 0;
		m_break = false;
	}
	~RealTimeCountHitsInLastSecMinHr(){}
private:
	std::list<long long> m_hits;
	std::list<long long>::iterator m_first;
	std::list<long long>::iterator m_second;
	std::list<long long>::iterator m_third;
	int m_firstCount;
	int m_secondCount;
	int m_thirdCount;
	std::mutex m_mutex;
	long long m_curTime;
	bool m_break;

	void Update()
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_break)
				break;
			if (!m_hits.empty())
			{
				m_curTime = currentTimeSeconds();
				while (m_third != m_hits.end() && (m_curTime - *m_third > 15))
				{
					++m_third;
					--m_thirdCount;
				}
				m_hits.erase(m_hits.begin(), m_third);
				while (m_second != m_hits.end() && (m_curTime - *m_second > 9))
				{
					++m_second;
					--m_secondCount;
				}
				while (m_first != m_hits.end() && (m_curTime - *m_first > 3))
				{
					++m_first;
					--m_firstCount;
				}
			}
			std::cout << "Last 3/9/15 sec hits: " << m_firstCount << ", " << m_secondCount << ", " << m_thirdCount << std::endl;
		}
	}
public:
	void Solve()
	{
		std::cout << "RealTimeCountHitsInLastSecMinHr: " << std::endl;
		std::cout << "Press ENTER to Count Hits." << std::endl;
		std::cout << "Press \"e\"+ENTER to exit." << std::endl;

		std::thread t(std::bind(&RealTimeCountHitsInLastSecMinHr::Update, this));

		std::string s;
		while (true)
		{
			std::getline(std::cin, s);//cin: the cin buffer is refreshed every few seconds, only after pressing ENTER will the cin buffer be read to s
			std::cout << "Entered: " << s << std::endl;
			if (s.compare("e") == 0)
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_break = true;
				break;
			}
			std::unique_lock<std::mutex> lock(m_mutex);
			m_hits.push_back(currentTimeSeconds());
			++m_firstCount;
			++m_secondCount;
			++m_thirdCount;
			if (m_first == m_hits.end())
				--m_first;
			if (m_second == m_hits.end())
				--m_second;
			if (m_third == m_hits.end())
				--m_third;
		}
		t.join();
	}

private:
	static long long currentTimeSeconds()
	{
		return (std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			)).count();
	}

	static long long currentTimeMicroSeconds()
	{
		return (std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			)).count();
	}

	static long long currentTimeMinutes()
	{
		return (std::chrono::duration_cast<std::chrono::minutes>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			)).count();
	}

	static long long currentTimeHours()
	{
		return (std::chrono::duration_cast<std::chrono::hours>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			)).count();
	}
};
#endif