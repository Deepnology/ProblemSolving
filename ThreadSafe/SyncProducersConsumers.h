#ifndef SYNC_PRODUCERS_CONSUMERS_H
#define SYNC_PRODUCERS_CONSUMERS_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <boost/function.hpp>
#include <deque>
#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
#include "Semaphore.h"
#include "ThreadMgr.h"
/*
Elements of programming interview, ParallelComputing: The producers consumers problem
http://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
The problem is to make sure that the producer won't try to add data into the buffer if it's full
and that the consumer won't try to remove data from an empty buffer.
*/
namespace SyncProducersConsumers
{
class ProducerConsumerQueue
{
public:
	explicit ProducerConsumerQueue(unsigned size) : m_semaphoreMutex(1), m_size(size), m_queue()
		, m_semaphoreConsume(0), m_semaphoreProduce(size)
	{

	}
	~ProducerConsumerQueue(){}

	void Produce(const std::string & s)
	{
		m_semaphoreProduce.Wait();
		{
			m_semaphoreMutex.Wait();
			{
				m_queue.push_back(s);
				std::ostringstream oss;
				oss << "<" << boost::this_thread::get_id() << ">";
				std::cout << oss.str();
			}
			m_semaphoreMutex.Signal();
		}
		m_semaphoreConsume.Signal();
	}
	std::string Consume()
	{
		std::string res;

		m_semaphoreConsume.Wait();
		{
			m_semaphoreMutex.Wait();
			{
				res = m_queue.front();
				m_queue.pop_front();
				std::ostringstream oss;
				oss << "[" << boost::this_thread::get_id() << "]";
				std::cout << oss.str();
			}
			m_semaphoreMutex.Signal();
		}
		m_semaphoreProduce.Signal();

		return res;
	}
private:
	Semaphore m_semaphoreMutex;
	unsigned m_size;
	std::deque<std::string> m_queue;

	Semaphore m_semaphoreConsume;
	Semaphore m_semaphoreProduce;
};

//using monitors
class ProducerConsumerQueue2
{
public:
	explicit ProducerConsumerQueue2(unsigned size) : m_size(size)
	{

	}
	~ProducerConsumerQueue2(){}

	void Produce(const std::string & s)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		while (m_queue.size() == m_size)
			m_conditionFull.wait(lock);

		m_queue.push_back(s);
		std::ostringstream oss;
		oss << "<" << boost::this_thread::get_id() << ">";
		std::cout << oss.str();

		m_conditionEmpty.notify_one();
	}
	std::string Consume()
	{
		std::string res;

		boost::mutex::scoped_lock lock(m_mutex);
		while (m_queue.size() == 0)
			m_conditionEmpty.wait(lock);

		res = m_queue.front();
		m_queue.pop_front();
		std::ostringstream oss;
		oss << "[" << boost::this_thread::get_id() << "]";
		std::cout << oss.str();

		m_conditionFull.notify_one();
		return res;
	}
private:
	boost::mutex m_mutex;
	boost::condition m_conditionFull;
	boost::condition m_conditionEmpty;
	unsigned m_size;
	std::deque<std::string> m_queue;
};


/*the following functions are for test*/
std::string Producer(boost::shared_ptr<ProducerConsumerQueue> pcq)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pcq->Produce("");
	}
	return "";
}
std::string Consumer(boost::shared_ptr<ProducerConsumerQueue> pcq)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pcq->Consume();
	}
	return "";
}
std::string Producer2(boost::shared_ptr<ProducerConsumerQueue2> pcq)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pcq->Produce("");
	}
	return "";
}
std::string Consumer2(boost::shared_ptr<ProducerConsumerQueue2> pcq)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pcq->Consume();
	}
	return "";
}
void Test()
{
	{
		std::cout << "Test SyncProducersConsumers ProducerConsumerQueue:" << std::endl;
		boost::shared_ptr<ProducerConsumerQueue> pcq(new ProducerConsumerQueue(7));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Producer, pcq));
			else
				m.Dispatch(std::bind(Consumer, pcq));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
	{
		std::cout << "Test SyncProducersConsumers ProducerConsumerQueue2:" << std::endl;
		boost::shared_ptr<ProducerConsumerQueue2> pcq(new ProducerConsumerQueue2(7));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Producer2, pcq));
			else
				m.Dispatch(std::bind(Consumer2, pcq));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
}

}
#endif