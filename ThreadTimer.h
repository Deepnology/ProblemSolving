/*****************************************
	ThreadTimer.h
	Copyright (c) 2017 David Feng
	Distributed under the MIT License.
*****************************************/
#ifndef THREAD_TIMER_H
#define THREAD_TIMER_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <map>
#include <boost/function.hpp>
#include <deque>
#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
/*
Design a ThreadTimer class that manages as many threads as required, depends on the current number of tasks, to perform deferred concurrent task execution.
Tasks are in the form of a function whose signature is to return a string and take an arbitrary number of arguments.
Tasks are alone with a time index which is the starting time in the future for it to get executed.
The method that ThreadTimer dispatches tasks should return immediately without a waiting time (asynchronous-callback).

Elements of programming interview, ParallelComputing: Implement a timer class
Develop a Timer class that manages the execution of deferred tasks.
The Timer constructor takes as its argument an object which includes a Run method and a name field, which is a string.
Timer must support (1.) starting a thread, identified by name, at a given time in the future 
(2.) canceling a thread, identified by name (the cancel request is to be ignored if the thread has already started).
*/
namespace thread_timer
{
class Timer
{
public:
	Timer() : m_time(0), m_destroyed(false), m_worker(std::bind(&Timer::Invoke, this))
	{}
	~Timer()
	{
		{
			boost::mutex::scoped_lock lock(m_mutex);
			m_destroyed = true;
		}
		m_worker.join();
	}
	int Get()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		return m_time;
	}
private:
	void Invoke()
	{
		while (true)
		{
			boost::this_thread::sleep(boost::posix_time::seconds(1));
			boost::mutex::scoped_lock lock(m_mutex);
			if (m_destroyed)
				break;
			++m_time;

			std::string t = "<" + std::to_string(m_time) + ">";
			std::cout << t << std::endl;
		}
	}
	boost::mutex m_mutex;
	int m_time;
	bool m_destroyed;
	boost::thread m_worker;
};
struct Future
{
	boost::mutex mutex;
	std::string result;
};
class Worker;
class ThreadTimer
{
	friend Worker;
public:
	ThreadTimer();
	~ThreadTimer();
	boost::shared_ptr<Future> Dispatch(boost::function0<std::string> f, int time);//any function(whose return type should be string) with arbitrary arguments can be binded to a function object with 0 arguments
private:
	void DispatchHandler();

	struct GreaterThan
	{
		bool operator()(const std::pair<int, boost::thread::id> & a, const std::pair<int, boost::thread::id> & b)
		{
			return a.first > b.first;
		}
	};

	boost::mutex m_mutex;
	boost::condition m_condition;
	std::map<boost::thread::id, Worker *> m_pool;
	std::deque<boost::thread::id> m_toRemove;
	std::priority_queue<std::pair<int, boost::thread::id>, std::vector<std::pair<int, boost::thread::id>>, GreaterThan> m_minHeap;//first: time, second: thread id
	bool m_destroyed;
	Timer m_timer;

	boost::thread m_dispatchHandler;
};
class Worker
{
public:
	Worker(boost::function0<std::string> f, boost::shared_ptr<Future> future, ThreadTimer * t);
	~Worker();
	boost::thread::id GetId() const;
	void Start();
private:
	void Invoke();

	boost::shared_ptr<boost::mutex> m_mutex_f;
	boost::shared_ptr<boost::condition> m_condition_f;
	boost::shared_ptr<boost::function0<std::string> > m_f;
	boost::shared_ptr<Future> m_future;
	ThreadTimer * m_ThreadTimer;

	boost::shared_ptr<boost::mutex> m_mutex;
	boost::shared_ptr<bool> m_destroyed;
	boost::shared_ptr<bool> m_exited;

	boost::thread m_worker;
};
Worker::Worker(boost::function0<std::string> f, boost::shared_ptr<Future> future, ThreadTimer * t) : m_mutex_f(new boost::mutex()), m_condition_f(new boost::condition()), m_f(new boost::function0<std::string>(f)), m_future(future), m_ThreadTimer(t)
, m_mutex(new boost::mutex()), m_destroyed(new bool(false)), m_exited(new bool(false))
, m_worker(std::bind(&Worker::Invoke, this))
{

}
Worker::~Worker()
{
	/*critical section: main*/
	boost::mutex::scoped_lock lock(*m_mutex);
	*m_destroyed = true;
	if (!(*m_exited))
	{
		m_worker.interrupt();
		m_worker.detach();
	}
}
boost::thread::id Worker::GetId() const
{
	return m_worker.get_id();
}
void Worker::Start()
{
	/*critical section: f*/
	boost::mutex::scoped_lock lock(*m_mutex_f);
	m_condition_f->notify_one();
}
void Worker::Invoke()
{
	boost::shared_ptr<boost::mutex> scoped_m_mutex_f = m_mutex_f;
	boost::shared_ptr<boost::condition> scoped_m_condition_f = m_condition_f;
	boost::shared_ptr<boost::function0<std::string> > scoped_m_f = m_f;
	boost::shared_ptr<Future> scoped_m_future = m_future;

	boost::shared_ptr<boost::mutex> scoped_m_mutex = m_mutex;
	boost::shared_ptr<bool> scoped_m_destroyed = m_destroyed;
	boost::shared_ptr<bool> scoped_m_exited = m_exited;

	{
		/*critical section: f*/
		boost::mutex::scoped_lock lock(*scoped_m_mutex_f);
		scoped_m_condition_f->wait(lock);

		try
		{
			boost::mutex::scoped_lock lock(scoped_m_future->mutex);
			scoped_m_future->result = (*scoped_m_f)();
		}
		catch (boost::thread_interrupted &)
		{

		}
		catch (std::exception &)
		{

		}
		catch (...)
		{

		}
	}

	/*critical section: main*/
	boost::mutex::scoped_lock lock(*scoped_m_mutex);
	if (!(*scoped_m_destroyed))
	{
		//let m_dispatchHandler thread to destroy
		boost::mutex::scoped_lock lock(m_ThreadTimer->m_mutex);//nested lock: potential deadlock !!
		m_ThreadTimer->m_condition.notify_one();
		m_ThreadTimer->m_toRemove.push_back(boost::this_thread::get_id());
	}
	*scoped_m_exited = true;
}

ThreadTimer::ThreadTimer() : m_mutex(), m_condition(), m_pool(), m_toRemove(), m_minHeap(), m_destroyed(false)
, m_dispatchHandler(std::bind(&ThreadTimer::DispatchHandler, this))
{

}
ThreadTimer::~ThreadTimer()
{
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_destroyed = true;
		m_condition.notify_one();
	}
	m_dispatchHandler.join();//wait until all Workers have been destroyed
}
boost::shared_ptr<Future> ThreadTimer::Dispatch(boost::function0<std::string> f, int time)
{
	boost::mutex::scoped_lock lock(m_mutex);
	boost::shared_ptr<Future> future(new Future);
	if (!m_destroyed)
	{
		Worker * w = new Worker(f, future, this);
		m_pool.emplace(w->GetId(), w);
		m_minHeap.emplace(time, w->GetId());
		m_condition.notify_one();
	}
	return future;
}
void ThreadTimer::DispatchHandler()
{
	boost::mutex::scoped_lock lock(m_mutex);
	while (true)
	{
		if (m_destroyed)
		{
			lock.unlock();//unlock m_mutex before invoking Worker::dtor to avoid deadlock
			for (const auto & p : m_pool)
				delete p.second;
			m_pool.clear();
			//std::cout << "delete" << std::endl;
			break;
		}
		while (!m_toRemove.empty())
		{
			auto itr = m_pool.find(m_toRemove.front());
			if (itr != m_pool.end())
			{
				delete itr->second;
				m_pool.erase(itr);
			}
			else
				std::cout << "ThreadTimer Error: Can't find thread id in pool: " << m_toRemove.front() << std::endl;
			m_toRemove.pop_front();
		}
		if (m_minHeap.empty())
			m_condition.wait(lock);
		else
		{
			int timeToSleep = m_minHeap.top().first - m_timer.Get();
			if (timeToSleep >= 1)
			{
				lock.unlock();
				//std::cout << "sleep" << std::endl;
				boost::this_thread::sleep(boost::posix_time::seconds(timeToSleep));
				//std::cout << "wakeup" << std::endl;
				lock.lock();
			}

			m_pool[m_minHeap.top().second]->Start();
			m_minHeap.pop();
		}
	}
}


/*the following functions are for test*/
std::string aLoop(std::string arg, int time, int count)
{
	arg += ",";
	for (int i = 0; i < count; ++i)
		std::cout << arg;
	std::ostringstream oss;
	oss << "[" << arg << boost::this_thread::get_id() << "," << time << "," << count << "]";
	return oss.str();
}
void Test()
{
	std::cout << "Hit ENTER -> ThreadTimer: construct a ThreadTimer object. ";
	std::cin.ignore();
	ThreadTimer t;
	std::cout << "Hit ENTER -> ThreadTimer: dispatch 80 parallel tasks in a random starting time of [3:12] seconds. ";
	std::cin.ignore();
	std::vector<boost::shared_ptr<Future> > res;
	std::map<int, std::vector<int>> timeMap;//first: time, second: nums to print at that time
	for (int i = 0; i < 80; ++i)
	{
		int time = rand() % 10 + 3;
		res.push_back(t.Dispatch(std::bind(aLoop, std::to_string(i), time, 1), time));
		timeMap[time].push_back(i);
	}
	std::cout << "Hit ENTER -> ThreadTimer: print 80 tasks' results [task_id,thread_id,starting_time,loop_count]. ";
	std::cin.ignore();
	std::ostringstream oss;
	std::map<std::string, int> tMap;//first: thread id, second: count
	for (const auto & p : res)
	{
		oss << (*p).result << ",";
		boost::match_results<std::string::const_iterator> matched_packet;
		if (boost::regex_search(p->result.cbegin(), p->result.cend(), matched_packet, boost::regex("(?<=,).*?(?=,)")))
		{
			if (!matched_packet[0].str().empty())
			{
				++tMap[matched_packet[0].str()];
			}
		}
	}
	std::cout << oss.str() << std::endl;
	oss.str(std::string());
	std::cout << "Hit ENTER -> ThreadTimer: print starting_time and corresponding task_ids. ";
	std::cin.ignore();
	for (const auto & p : timeMap)
	{
		oss << p.first << ": ";
		for (const auto & i : p.second)
		{
			oss << i << ",";
		}
		oss << std::endl;
	}
	std::cout << oss.str() << std::endl;
	oss.str(std::string());
	std::cout << "Hit ENTER -> ThreadTimer: print [thread_id,occurrence_count]. ";
	std::cin.ignore();
	for (const auto & p : tMap)
	{
		oss << "[" << p.first << "," << p.second << "],";
	}
	std::cout << oss.str() << std::endl;
	std::cout << "Hit ENTER -> ThreadTimer: destroy the ThreadTimer object. ";
	std::cin.ignore();
}
}
#endif