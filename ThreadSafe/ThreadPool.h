#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <map>
#include <boost/function.hpp>
#include <deque>
#include <boost/shared_ptr.hpp>
/*
Design a ThreadPool class that manages a fixed given number of standby threads that are ready to perform concurrent task execution.
Tasks are in the form of a function whose signature is to return a string and take an arbitrary number of arguments.
The method that ThreadPool dispatches tasks should return immediately without a waiting time (asynchronous-callback).

for infinite loop:
std::thread's dtor will cause error without calling detach before dtor. If detach is called before dtor, dtor will work fine, but the infinite loop will continue to execute after dtor is called.
boost::thread's dtor won't cause error without calling detach before dtor. The infinite loop will continue to execute after dtor is called.
boost::thread's interrupt works only for interrupt points.

Key ideas:
1. In ThreadPool, maintain a m_dispatchHandler thread to dispatch queued tasks to queued available Worker threads, and delete all Worker objects when ThreadPool's dtor is called.
   In this way, ThreadPool::Dispatch can return immediately (asynchronous callback).
2. ThreadPool::Dispatch enqueues a binded function object with 0 argument(note that arbitrary arguments can be binded into the function object), unblock m_dispatchHandler, and returns a shared pointer to a Future object
3. In ThreadPool dtor, mark m_destroyed, unblock m_dispatchHandler thread to delete all Worker objects, and wait for m_dispatchHandler to finish deletion and join.
4. In Worker, maintain a m_worker thread that invokes Worker::Invoke.
   In Worker::Invoke, keep scoped shared points to Worker's data member, keep a infinite while loop to execute its new task, and push back the m_standBy queue in ThreadPool when a task is done iff the Worker dtor critical section hasn't been entered.
5. Worker::Accept updates m_f and m_future, and unblocks m_worker thread to execute m_f.
6. In Worker dtor, interrupt and detach the m_worker thread.
   Since m_mutex_f, m_condition_f, m_f, m_mutex, m_destroyed are all in shared pointers, and m_worker thread is detached, the Worker object can be safely destroyed while m_worker thread is still running.
*/
namespace thread_pool
{
struct Future
{
	boost::mutex mutex;
	std::string result;
};
class Worker;
class ThreadPool
{
	friend Worker;
public:
	explicit ThreadPool(size_t count);
	~ThreadPool();
	boost::shared_ptr<Future> Dispatch(boost::function0<std::string> f);//any function(whose return type should be string) with arbitrary arguments can be binded to a function object with 0 arguments
private:
	void DispatchHandler();

	boost::mutex m_mutex;
	boost::condition m_condition;
	std::map<boost::thread::id, Worker *> m_pool;
	std::deque<boost::thread::id> m_standBy;
	std::deque<std::pair<boost::function0<std::string>, boost::shared_ptr<Future> > > m_tasks;
	bool m_destroyed;
	
	boost::thread m_dispatchHandler;
};
class Worker
{
public:
	explicit Worker(ThreadPool * t);
	~Worker();
	boost::thread::id GetId() const;
	void Accept(boost::function0<std::string> f, boost::shared_ptr<Future> future);
private:
	void Invoke();

	ThreadPool * m_ThreadPool;

	boost::shared_ptr<boost::mutex> m_mutex_f;
	boost::shared_ptr<boost::condition> m_condition_f;
	boost::shared_ptr<boost::function0<std::string> > m_f;
	boost::shared_ptr<Future> m_future;

	boost::shared_ptr<boost::mutex> m_mutex;
	boost::shared_ptr<bool> m_destroyed;

	boost::thread m_worker;
};
Worker::Worker(ThreadPool * t) : m_ThreadPool(t)
, m_mutex_f(new boost::mutex()), m_condition_f(new boost::condition()), m_f(), m_future()
, m_mutex(new boost::mutex()), m_destroyed(new bool(false))
, m_worker(std::bind(&Worker::Invoke, this))
{

}
Worker::~Worker()
{
	/*critical section: main*/
	boost::mutex::scoped_lock lock(*m_mutex);
	*m_destroyed = true;
	m_worker.interrupt();
	m_worker.detach();
}
boost::thread::id Worker::GetId() const
{
	return m_worker.get_id();
}
void Worker::Accept(boost::function0<std::string> f, boost::shared_ptr<Future> future)
{
	/*critical section: f*/
	boost::mutex::scoped_lock lock(*m_mutex_f);
	boost::shared_ptr<boost::function0<std::string>>(new boost::function0<std::string>(f)).swap(m_f);
	m_future.swap(future);
	m_condition_f->notify_one();
}
void Worker::Invoke()
{
	boost::shared_ptr<boost::mutex> scoped_m_mutex_f = m_mutex_f;
	boost::shared_ptr<boost::condition> scoped_m_condition_f = m_condition_f;

	boost::shared_ptr<boost::mutex> scoped_m_mutex = m_mutex;
	boost::shared_ptr<bool> scoped_m_destroyed = m_destroyed;
	
	while (true)
	{
		{
			/*critical section: f*/
			boost::mutex::scoped_lock lock(*scoped_m_mutex_f);
			scoped_m_condition_f->wait(lock);

			boost::shared_ptr<boost::function0<std::string> > scoped_m_f = m_f;
			boost::shared_ptr<Future> scoped_m_future = m_future;

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
			boost::mutex::scoped_lock lock2(m_ThreadPool->m_mutex);//nested lock: potential deadlock !!
			m_ThreadPool->m_condition.notify_one();
			m_ThreadPool->m_standBy.push_back(boost::this_thread::get_id());
		}
		else
			break;
	}
}

ThreadPool::ThreadPool(size_t count) : m_mutex(), m_condition(), m_pool(), m_standBy(), m_tasks(), m_destroyed(false)
, m_dispatchHandler(std::bind(&ThreadPool::DispatchHandler, this))
{
	for (size_t i = 0; i < count; ++i)
	{
		Worker * w = new Worker(this);
		m_pool.emplace(w->GetId(), w);
		m_standBy.push_back(w->GetId());
	}
}
ThreadPool::~ThreadPool()
{
	{
		boost::mutex::scoped_lock lock(m_mutex);
		m_destroyed = true;
		m_condition.notify_one();
	}
	m_dispatchHandler.join();//wait until all Workers have been destroyed
}
boost::shared_ptr<Future> ThreadPool::Dispatch(boost::function0<std::string> f)
{
	boost::mutex::scoped_lock lock(m_mutex);
	boost::shared_ptr<Future> future(new Future);
	m_tasks.push_back(std::make_pair(f, future));
	m_condition.notify_one();
	return future;
}
void ThreadPool::DispatchHandler()
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
		while (!m_standBy.empty() && !m_tasks.empty())
		{
			m_pool[m_standBy.front()]->Accept(m_tasks.front().first, m_tasks.front().second);
			m_standBy.pop_front();
			m_tasks.pop_front();
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
	std::cout << "Hit ENTER -> ThreadPool: init for 5 threads in pool. ";
	std::cin.ignore();
	ThreadPool p(5);
	std::cout << "Hit ENTER -> ThreadPool: dispatch 200 tasks with random number of loops in [1:150]. ";
	std::cin.ignore();
	std::vector<boost::shared_ptr<Future> > res;
	for (size_t i = 0; i < 200; ++i)
		res.push_back(p.Dispatch(std::bind(aLoop, std::to_string(i), rand() % 150 + 1)));
	std::cout << "ThreadPool: print 200 tasks' results [task_id,thread_id,loop_count]. ";
	std::cin.ignore();
	std::ostringstream oss;
	for (const auto & p : res)
		oss << (*p).result << ",";
	std::cout << oss.str() << std::endl;
	std::cout << "Hit ENTER -> ThreadPool: detach all threads in pool. ";
	std::cin.ignore();
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>//std::shared_ptr
#include <functional>
namespace thread_pool2
{
	class Worker;
	class ThreadPool
	{
		friend Worker;
	public:
		explicit ThreadPool(size_t count);
		~ThreadPool();
		void Dispatch(std::function<void()> f);
	private:
		void DispatchHandler();

		std::mutex m_mutex;
		std::condition_variable m_condition;
		std::map<std::thread::id, Worker *> m_pool;
		std::deque<std::thread::id> m_standBy;
		std::deque<std::function<void()>> m_tasks;
		bool m_destroyed;

		std::thread m_dispatchHandler;
	};
	class Worker
	{
	public:
		explicit Worker(ThreadPool * t);
		~Worker();
		std::thread::id GetId() const;
		void Accept(std::function<void()> f);
	private:
		void Invoke();

		ThreadPool * m_ThreadPool;

		std::shared_ptr<std::mutex> m_mutex_f;
		std::shared_ptr<std::condition_variable> m_condition_f;
		std::shared_ptr<std::function<void()>> m_f;

		std::shared_ptr<std::mutex> m_mutex;
		std::shared_ptr<bool> m_destroyed;

		std::thread m_worker;
	};
	Worker::Worker(ThreadPool * t): m_ThreadPool(t)
			, m_mutex_f(new std::mutex()), m_condition_f(new std::condition_variable()), m_f()
			, m_mutex(new std::mutex()), m_destroyed(new bool(false))
			, m_worker(std::bind(&Worker::Invoke, this))
	{

	}
	Worker::~Worker()
	{
		/*critical section: main*/
		std::unique_lock<std::mutex> lock(*m_mutex);
		*m_destroyed = true;
		m_worker.detach();
	}
	std::thread::id Worker::GetId() const
	{
		return m_worker.get_id();
	}
	void Worker::Accept(std::function<void()> f)
	{
		/*critical section: f*/
		std::unique_lock<std::mutex> lock(*m_mutex_f);
		std::shared_ptr<std::function<void()>>(new std::function<void()>(f)).swap(m_f);
		m_condition_f->notify_one();
	}
	void Worker::Invoke()
	{
		std::shared_ptr<std::mutex> scoped_m_mutex_f = m_mutex_f;
		std::shared_ptr<std::condition_variable> scoped_m_condition_f = m_condition_f;

		std::shared_ptr<std::mutex> scoped_m_mutex = m_mutex;
		std::shared_ptr<bool> scoped_m_destroyed = m_destroyed;

		while (true)
		{
			{
				/*critical section: f*/
				std::unique_lock<std::mutex> lock(*scoped_m_mutex_f);
				scoped_m_condition_f->wait(lock);

				std::shared_ptr<std::function<void()>> scoped_m_f = m_f;

				try {
					(*scoped_m_f)();
				}
				catch (std::exception &) {

				}
				catch (...) {

				}
			}

			/*critical section: main*/
			std::unique_lock<std::mutex> lock(*scoped_m_mutex);
			if (!(*scoped_m_destroyed))
			{
				std::unique_lock<std::mutex> lock2(m_ThreadPool->m_mutex);
				m_ThreadPool->m_condition.notify_one();
				m_ThreadPool->m_standBy.push_back(std::this_thread::get_id());
			}
			else
				break;
		}
	}

	ThreadPool::ThreadPool(size_t count):
			m_mutex(), m_condition(), m_pool(), m_standBy(), m_tasks(), m_destroyed(false)
			, m_dispatchHandler(std::bind(&ThreadPool::DispatchHandler, this))
	{
		for (size_t i = 0; i < count; ++i)
		{
			Worker * w = new Worker(this);
			m_pool.emplace(w->GetId(), w);
			m_standBy.push_back(w->GetId());
		}
	}
	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_destroyed = true;
			m_condition.notify_one();
		}
		m_dispatchHandler.join();
	}
	void ThreadPool::Dispatch(std::function<void()> f)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_tasks.push_back(f);
		m_condition.notify_one();
	}
	void ThreadPool::DispatchHandler()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while(true)
		{
			m_condition.wait(lock);
			if (m_destroyed)
			{
				lock.unlock();
				for (const auto & p : m_pool)
					delete p.second;
				m_pool.clear();
				break;
			}
			while (!m_standBy.empty() && !m_tasks.empty())
			{
				m_pool[m_standBy.front()]->Accept(m_tasks.front());
				m_standBy.pop_front();
				m_tasks.pop_front();
			}
		}
	}

	/*the following functions are for test*/
	void aLoop(std::string arg, size_t count)
	{
		std::ostringstream oss;
		oss << "[" << arg << "," << std::this_thread::get_id() << "," << count << "]";
		for (size_t i = 0; i < count; ++i)
			//std::cout << oss.str();
			std::cout << arg;
	}
	void Test()
	{
		std::cout << "Hit ENTER -> ThreadPool: init for 5 threads in pool. ";
		std::cin.ignore();
		ThreadPool p(5);
		std::cout << "Hit ENTER -> ThreadPool: dispatch 200 tasks with random number of loops in [1:150]. ";
		std::cin.ignore();
		for (size_t i = 0; i < 200; ++i)
			p.Dispatch(std::bind(aLoop, std::to_string(i), rand() % 150 + 1));
		std::cout << "ThreadPool: print 200 tasks' results [task_id,thread_id,loop_count]. ";
		std::cin.ignore();
		std::cout << "Hit ENTER -> ThreadPool: detach all threads in pool. ";
		std::cin.ignore();
	}
}
#endif