#ifndef IMPLEMENT_ASYNC_CALLBACK_H
#define IMPLEMENT_ASYNC_CALLBACK_H
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>
/*
Elements of programming interview, ParallelComputing: Implement asynchronous callbacks
It is common in a distributed computing environment for the responses to not return in the same order as the requests were made.
One way to handle this is through an "asynchronous callback"---a method to be invoked on response.
*/
namespace ImplementAsyncCallback
{
	struct Future
	{
		boost::mutex mutex;
		std::string result;
	};
	/*
	the FuncWrapper function object does 3 tasks:
	1. enable the underlying function getting executed under lock and capture the result
	2. a try catch structure to catch interrupt
	3. scoped shared_ptr of m_f and m_future so that the resources are safe while thread object and FuncWrapper object are getting destroyed after detached
	*/
	struct FuncWrapper
	{
		~FuncWrapper()
		{
			std::cout << "~FuncWrapper" << std::endl;
		}
		void operator()()
		{
			boost::shared_ptr<boost::function0<std::string> > scoped_m_f = m_f;
			boost::shared_ptr<Future> scoped_m_future = m_future;
			try
			{
				boost::mutex::scoped_lock lock(scoped_m_future->mutex);
				scoped_m_future->result = (*scoped_m_f)();
			}
			catch (boost::thread_interrupted &)
			{
				std::cout << "Interrupt Caught !!!" << std::endl;
			}
			catch (std::exception &)
			{

			}
			catch (...)
			{

			}
		}
		boost::shared_ptr<boost::function0<std::string> > m_f;
		boost::shared_ptr<Future> m_future;
	};
	static boost::shared_ptr<Future> Dispatch(boost::function0<std::string> f)
	{
		FuncWrapper fw;
		boost::shared_ptr<boost::function0<std::string>>(new boost::function0<std::string>(f)).swap(fw.m_f);
		boost::shared_ptr<Future>(new Future).swap(fw.m_future);
		boost::thread t(std::bind(&FuncWrapper::operator(), &fw));
		t.detach();//detach the thread so that it continues to run after the thread object is getting destroyed
		std::cout << "Detached" << std::endl;
		return fw.m_future;
	}

	struct FuncWrapperWTimeOut
	{
		~FuncWrapperWTimeOut()
		{
			std::cout << "~FuncWrapperWTimeOut" << std::endl;
		}
		void operator()()
		{
			FuncWrapper fw;
			fw.m_f = m_f;//equivalent to scoped_m_f
			fw.m_future = m_future;//equivalent to scoped_m_future
			boost::thread t(std::bind(&FuncWrapper::operator(), &fw));//create another thread to perform the task
			boost::this_thread::sleep(boost::posix_time::seconds(m_sec));//use this thread as a timer
			std::cout << "Time's Up !!!" << std::endl;
			t.interrupt();//interrupt t when time's up
			t.detach();
		}
		int m_sec;
		boost::shared_ptr<boost::function0<std::string> > m_f;
		boost::shared_ptr<Future> m_future;
	};
	static boost::shared_ptr<Future> Dispatch_WTimeOut(boost::function0<std::string> f, int sec)
	{
		FuncWrapperWTimeOut fw;
		fw.m_sec = sec;
		boost::shared_ptr<boost::function0<std::string>>(new boost::function0<std::string>(f)).swap(fw.m_f);
		boost::shared_ptr<Future>(new Future).swap(fw.m_future);
		boost::thread t(std::bind(&FuncWrapperWTimeOut::operator(), &fw));
		t.detach();//detach the thread so that it continues to run after the thread object is getting destroyed
		std::cout << "Detached" << std::endl;
		return fw.m_future;
	}


	/*the following are for test*/
	std::string aLoop(std::string arg, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			std::cout << arg;
			boost::this_thread::interruption_point();//adding interrupt point to make the loop interruptable
		}
		std::ostringstream oss;
		oss << "[" << arg << "," << boost::this_thread::get_id() << "," << count << "]";
		return oss.str();
	}
	void Test()
	{
		std::cout << "Hit ENTER -> ImplementAsyncCallback, Dispatch:" << std::endl;
		std::cin.ignore();
		boost::shared_ptr<Future> future1 = Dispatch(boost::bind(aLoop, std::string("v"), 70000));
		std::cout << "Hit ENTER -> ImplementAsyncCallback, Dispatch_WTimeOut:" << std::endl;
		std::cin.ignore();
		boost::shared_ptr<Future> future2 = Dispatch_WTimeOut(boost::bind(aLoop, std::string("v"), 70000), 1);
		std::cout << "Hit ENTER" << std::endl;
		std::cin.ignore();
	}
}

#endif