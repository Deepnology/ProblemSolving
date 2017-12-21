/*****************************************
	ThreadMgr.h
	Copyright (c) 2017 David Feng
	Distributed under the MIT License.
*****************************************/
#ifndef THREAD_MGR_H
#define THREAD_MGR_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <map>
#include <boost/function.hpp>
#include <deque>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
/*
Design a ThreadMgr class that manages as many threads as required, depends on the current number of tasks, to perform concurrent task execution.
Tasks are in the form of a function whose signature is to return a string and take an arbitrary number of arguments.
The method that ThreadMgr dispatches tasks should return immediately without a waiting time (asynchronous-callback).

for infinite loop:
std::thread's dtor will cause error without calling detach before dtor. If detach is called before dtor, dtor will work fine, but the infinite loop will continue to execute after dtor is called.
boost::thread's dtor won't cause error without calling detach before dtor. The infinite loop will continue to execute after dtor is called.
boost::thread's interrupt works only for interrupt points.

Key ideas:
1. In ThreadMgr, maintain a m_dtorHandler thread to delete all Worker objects in the m_toRemove queue and remove from m_pool.
   In this way, ThreadMgr::Dispatch can return immediately (asynchronous callback).
2. ThreadPool::Dispatch creates a new Worker object to perform a binded function object with 0 argument(note that arbitrary arguments can be binded into the function object), and returns a shared pointer to a Future object
3. In ThreadMgr dtor, mark m_exit, unblock m_dtorHandler thread to delete all Worker objects, and wait for m_dtorHandler to finish deletion and join.
4. In Worker, maintain a m_worker thread that invokes Worker::Invoke.
   In Worker::Invoke, keep scoped shared points to Worker's data member, execute its own task, and push back the m_toRemove queue when the task is done iff the Worker dtor critical section hasn't been entered.
5. In Worker dtor, interrupt and detach the m_worker thread iff the m_worker thread hasn't passed the critical section.
   Since m_f, m_mutex, m_destroyed, m_exited are all in shared pointers, and m_worker thread is detached, the Worker object can be safely destroyed while m_worker thread is still running.
*/
namespace thread_mgr
{
struct Future
{
	boost::mutex mutex;
	std::string result;
};
class Worker;
class ThreadMgr
{
	friend Worker;
public:
	ThreadMgr();
	~ThreadMgr();
	boost::shared_ptr<Future> Dispatch(boost::function0<std::string> f);//any function(whose return type should be string) with arbitrary arguments can be binded to a function object with 0 arguments
private:
	void DtorHandler();

	boost::mutex m_mutex;
	std::map<boost::thread::id, Worker *> m_pool;
	std::deque<boost::thread::id> m_toRemove;
	bool m_destroyed;
	boost::condition m_condition;

	boost::thread m_dtorHandler;
};
class Worker
{
public:
	Worker(boost::function0<std::string> f, boost::shared_ptr<Future> future, ThreadMgr * t);
	~Worker();
	boost::thread::id GetId() const;
private:
	void Invoke();

	boost::shared_ptr<boost::function0<std::string> > m_f;
	boost::shared_ptr<Future> m_future;
	ThreadMgr * m_ThreadMgr;

	boost::shared_ptr<boost::mutex> m_mutex;
	boost::shared_ptr<bool> m_destroyed;
	boost::shared_ptr<bool> m_exited;

	boost::thread m_worker;
};
Worker::Worker(boost::function0<std::string> f, boost::shared_ptr<Future> future, ThreadMgr * t) : m_f(new boost::function0<std::string>(f)), m_future(future), m_ThreadMgr(t)
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
void Worker::Invoke()
{
	boost::shared_ptr<boost::function0<std::string> > scoped_m_f = m_f;
	boost::shared_ptr<Future> scoped_m_future = m_future;

	boost::shared_ptr<boost::mutex> scoped_m_mutex = m_mutex;
	boost::shared_ptr<bool> scoped_m_destroyed = m_destroyed;
	boost::shared_ptr<bool> scoped_m_exited = m_exited;

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

	/*critical section: main*/
	boost::mutex::scoped_lock lock(*scoped_m_mutex);
	if (!(*scoped_m_destroyed))
	{
		//let m_dtorHandler thread to destroy
		boost::mutex::scoped_lock lock2(m_ThreadMgr->m_mutex);//nested lock: potential deadlock !!
		m_ThreadMgr->m_condition.notify_one();
		m_ThreadMgr->m_toRemove.push_back(boost::this_thread::get_id());
	}
	*scoped_m_exited = true;
}

ThreadMgr::ThreadMgr() : m_destroyed(false)
	, m_dtorHandler(std::bind(&ThreadMgr::DtorHandler, this))
{

}
ThreadMgr::~ThreadMgr()
{
	//boost::this_thread::sleep(boost::posix_time::seconds(1));
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_destroyed = true;
		m_condition.notify_one();
	}
	m_dtorHandler.join();//wait until all Workers have been destroyed
}
boost::shared_ptr<Future> ThreadMgr::Dispatch(boost::function0<std::string> f)
{
	boost::mutex::scoped_lock lock(m_mutex);
	boost::shared_ptr<Future> future(new Future);
	if (!m_destroyed)
	{
		Worker * w = new Worker(f, future, this);
		m_pool.emplace(w->GetId(), w);
	}
	return future;
}
void ThreadMgr::DtorHandler()
{
	boost::mutex::scoped_lock lock(m_mutex);
	while (true)
	{
		m_condition.wait(lock);
		if (m_destroyed)
		{
			lock.unlock();//unlock m_mutex before invoking Worker::dtor to avoid deadlock
			for (const auto & p : m_pool)
				delete p.second;
			m_pool.clear();
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
				std::cout << "ThreadMgr Error: Can't find thread id in pool: " << m_toRemove.front() << std::endl;
			m_toRemove.pop_front();
		}
	}
}


/*the following functions are for test*/
std::string aLoop(std::string arg, size_t count)
{
	for (size_t i = 0; i < count; ++i)
		std::cout << arg;
	std::ostringstream oss;
	oss << "[" << arg << "," << boost::this_thread::get_id() << "," << count << "]";
	return oss.str();
}
void Test()
{
	std::cout << "ThreadMgr: construct the ThreadMgr object. ";
	system("pause");
	ThreadMgr m;
	std::cout << "ThreadMgr: dispatch 80 parallel tasks with random number of loops in [1:150]. ";
	system("pause");
	std::vector<boost::shared_ptr<Future> > res;
	for (size_t i = 0; i < 80; ++i)
		res.push_back(m.Dispatch(std::bind(aLoop, std::to_string(i), rand() % 150 + 1)));
	std::cout << "ThreadMgr: print 80 tasks' results [task_id,thread_id,loop_count]. ";
	system("pause");
	std::ostringstream oss;
	std::map<std::string, size_t> tMap;//first: thread id, second: count
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
	std::cout << "ThreadMgr: print [thread_id,occurrence_count]. ";
	system("pause");
	for (const auto & p : tMap)
	{
		oss << "[" << p.first << "," << p.second << "],";
	}
	std::cout << oss.str() << std::endl;
	std::cout << "ThreadMgr: destroy the ThreadMgr object. ";
	system("pause");
}

}
#endif