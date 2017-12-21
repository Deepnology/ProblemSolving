#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <queue>
#include <boost/shared_ptr.hpp>
#include "ThreadMgr.h"
/*
C++ Concurrency in Action
*/
namespace thread_safe_queue
{
template<typename T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue(){}
	ThreadSafeQueue(const ThreadSafeQueue & other)
	{
		boost::mutex::scoped_lock lock(other.m_mutex);
		m_queue = other.m_queue;
	}
	~ThreadSafeQueue(){}
	void Push(T t)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_queue.push(t);
		m_condition.notify_one();
	}
	void Wait_And_Pop(T & t)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_condition.wait(lock, [this]
		{
			return !m_queue.empty();
		});
		t = m_queue.front();
		m_queue.pop();
	}
	boost::shared_ptr<T> Wait_And_Pop()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_condition.wait(lock, [this]
		{
			return !m_queue.empty();
		});
		boost::shared_ptr<T> res(new T(m_queue.front()));
		m_queue.pop();
		return res;
	}
	bool Try_Pop(T & t)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (m_queue.empty())
			return false;
		t = m_queue.front();
		m_queue.pop();
		return true;
	}
	boost::shared_ptr<T> Try_Pop()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (m_queue.empty())
			return boost::shared_ptr<T>();
		boost::shared_ptr<T> res(new T(m_queue.front()));
		m_queue.pop();
		return res;
	}
	bool Empty() const
	{
		boost::mutex::scoped_lock lock(m_mutex);
		return m_queue.empty();
	}
private:
	mutable boost::mutex m_mutex;//mutable: for m_mutex used in a const member function
	std::queue<T> m_queue;
	boost::condition m_condition;
};
}
#endif