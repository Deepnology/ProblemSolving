#ifndef	SYNC_READERS_WRITERS_H
#define SYNC_READERS_WRITERS_H
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
Elements of programming interview, ParallelComputing: The readers writers problem
https://en.wikipedia.org/wiki/Readers-writers_problem
The first readers-writers problem (readers-preference):
no reader shall be kept waiting if the shared resource is currently opened for reading
The second readers-writers problem (writers-preference):
no writer, once added to the queue, shall be kept waiting longer than absolutely necessary
The third readers-writers problem (fair readers writers):
no thread shall be allowed to starve; that is, the operation of obtaining a lock on the shared resource will always terminate in a bounded amount of time
(Note that the solution can only satisfy the condition that "no thread shall be allowed to starve" if and only if semaphores preserve first-in first-out ordering when blocking and releasing threads)
*/
namespace SyncReadersWriters
{
class PreferReader //1. simplest
{
public:
	explicit PreferReader(const std::string & s) : m_s(s)
		, m_semaphoreResource(1), m_semaphoreRC(1), m_readCount(0)
	{

	}
	std::string Read()
	{
		m_semaphoreRC.Wait();//works like a mutex that protects m_readCount among multiple readers
		{
			++m_readCount;
			if (m_readCount == 1)//check if you are the first reader thread
				m_semaphoreResource.Wait();//make first reader thread (and all its successive reader threads) mutual exclusive to any writer thread in the resource critical section. (resource critical section starts)
		}
		m_semaphoreRC.Signal();

		std::string res = m_s;
		std::ostringstream oss;
		oss << "[" << boost::this_thread::get_id() << "]";
		std::cout << oss.str();

		m_semaphoreRC.Wait();//works like a mutex that protects m_readCount among multiple readers
		{
			--m_readCount;
			if (m_readCount == 0)//check if you are the last reader thread
				m_semaphoreResource.Signal();//(resource critical section ends)
		}
		m_semaphoreRC.Signal();

		return res;
	}
	void Write(const std::string & s)
	{
		m_semaphoreResource.Wait();//(resource critical section starts)
		{
			m_s = s;
			std::ostringstream oss;
			oss << "<" << boost::this_thread::get_id() << ">";
			std::cout << oss.str();
		}
		m_semaphoreResource.Signal();//(resource critical section ends)
	}
private:
	std::string m_s;

	Semaphore m_semaphoreResource;//between both reader and writer threads

	Semaphore m_semaphoreRC;//between reader threads
	int m_readCount;
};

class PreferWriter //3. hardest: adding m_semaphoreWC, m_semaphoreReader
{
public:
	explicit PreferWriter(const std::string & s) : m_s(s)
		, m_semaphoreShared(1), m_semaphoreResource(1)
		, m_semaphoreRC(1), m_readCount(0)
		, m_semaphoreWC(1), m_writeCount(0)
		, m_semaphoreReader(1)
	{

	}
	std::string Read()
	{
		m_semaphoreReader.Wait();
		{
			m_semaphoreShared.Wait();
			{
				m_semaphoreRC.Wait();
				{
					++m_readCount;
					if (m_readCount == 1)//check if you are the first reader thread
						m_semaphoreResource.Wait();//make first reader thread (and all its successive reader threads) mutual exclusive to any writer thread in the resource critical section. (resource critical section starts)
				}
				m_semaphoreRC.Signal();
			}
			m_semaphoreShared.Signal();
		}
		m_semaphoreReader.Signal();

		std::string res = m_s;
		std::ostringstream oss;
		oss << "[" << boost::this_thread::get_id() << "]";
		std::cout << oss.str();

		m_semaphoreRC.Wait();
		{
			--m_readCount;
			if (m_readCount == 0)//check if you are the last reader thread
				m_semaphoreResource.Signal();//(resource critical section ends)
		}
		m_semaphoreRC.Signal();

		return res;
	}
	void Write(const std::string & s)
	{
		m_semaphoreWC.Wait();
		{
			++m_writeCount;
			if (m_writeCount == 1)//check if you are the first writer thread
				m_semaphoreShared.Wait();//->make first writer thread (and all its successive writer threads) mutual exclusive to any reader thread in the m_semaphoreReader critical section (hold m_semaphoreReader critical section)
		}
		m_semaphoreWC.Signal();

		m_semaphoreResource.Wait();//(resource critical section starts)
		{
			m_s = s;
			std::ostringstream oss;
			oss << "<" << boost::this_thread::get_id() << ">";
			std::cout << oss.str();
		}
		m_semaphoreResource.Signal();//(resource critical section ends)

		m_semaphoreWC.Wait();
		{
			--m_writeCount;
			if (m_writeCount == 0)//check if you are the last writer thread
				m_semaphoreShared.Signal();//->(release m_semaphoreReader critical section)
		}
		m_semaphoreWC.Signal();
	}
private:
	std::string m_s;

	Semaphore m_semaphoreShared;//between both reader and writer threads
	Semaphore m_semaphoreResource;//between both reader and writer threads

	Semaphore m_semaphoreRC;//between reader threads
	int m_readCount;

	Semaphore m_semaphoreWC;//between writer threads
	int m_writeCount;

	Semaphore m_semaphoreReader;//between reader threads
};

class FairReaderWriter //2. medium: adding m_semaphoreShared
{
public:
	explicit FairReaderWriter(const std::string & s) : m_s(s)
		, m_semaphoreShared(1), m_semaphoreResource(1), m_semaphoreRC(1), m_readCount(0)
	{

	}
	std::string Read()
	{
		m_semaphoreShared.Wait();
		{
			m_semaphoreRC.Wait();
			{
				++m_readCount;
				if (m_readCount == 1)//check if you are the first reader thread
					m_semaphoreResource.Wait();//make first reader thread (and all its successive reader threads) mutual exclusive to any writer thread in the resource critical section. (resource critical section starts)
			}
			m_semaphoreRC.Signal();
		}
		m_semaphoreShared.Signal();

		std::string res = m_s;
		std::ostringstream oss;
		oss << "[" << boost::this_thread::get_id() << "]";
		std::cout << oss.str();

		m_semaphoreRC.Wait();
		{
			--m_readCount;
			if (m_readCount == 0)//check if you are the last reader thread
				m_semaphoreResource.Signal();//(resource critical section ends)
		}
		m_semaphoreRC.Signal();

		return res;
	}
	void Write(const std::string & s)
	{
		m_semaphoreShared.Wait();
		{
			m_semaphoreResource.Wait();//(resource critical section starts)
			{
				m_s = s;
				std::ostringstream oss;
				oss << "<" << boost::this_thread::get_id() << ">";
				std::cout << oss.str();
			}
			m_semaphoreResource.Signal();//(resource critical section ends)
		}
		m_semaphoreShared.Signal();
	}
private:
	std::string m_s;

	Semaphore m_semaphoreShared;//between both reader and writer threads
	Semaphore m_semaphoreResource;//between both reader and writer threads

	Semaphore m_semaphoreRC;//between reader threads
	int m_readCount;
};

class SimpleReaderWriter
{
public:
	explicit SimpleReaderWriter(const std::string & s) : m_s(s), m_sharedMutex() {}
	~SimpleReaderWriter() {}
	std::string Read()
	{
		boost::shared_lock<boost::shared_mutex> shared_lock(m_sharedMutex);
		std::string res = m_s;
		std::ostringstream oss;
		oss << "[" << boost::this_thread::get_id() << "]";
		std::cout << oss.str();
		return res;
	}
	void Write(const std::string & s)
	{
		boost::unique_lock<boost::shared_mutex> unique_lock(m_sharedMutex);
		m_s = s;
		std::ostringstream oss;
		oss << "<" << boost::this_thread::get_id() << ">";
		std::cout << oss.str();
	}
private:
	std::string m_s;
	boost::shared_mutex m_sharedMutex;
};

/*the following functions are for test*/
std::string Reader1(boost::shared_ptr<PreferReader> pr)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pr->Read();
	}
	return "";
}
std::string Writer1(boost::shared_ptr<PreferReader> pr)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pr->Write("");
	}
	return "";
}
std::string Reader2(boost::shared_ptr<PreferWriter> pw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pw->Read();
	}
	return "";
}
std::string Writer2(boost::shared_ptr<PreferWriter> pw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		pw->Write("");
	}
	return "";
}
std::string Reader3(boost::shared_ptr<FairReaderWriter> frw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		frw->Read();
	}
	return "";
}
std::string Writer3(boost::shared_ptr<FairReaderWriter> frw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		frw->Write("");
	}
	return "";
}
std::string Reader4(boost::shared_ptr<SimpleReaderWriter> srw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		srw->Read();
	}
	return "";
}
std::string Writer4(boost::shared_ptr<SimpleReaderWriter> srw)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		srw->Write("");
	}
	return "";
}
void Test()
{
	{
		std::cout << "Test SyncReadersWriters PreferReader:" << std::endl;
		boost::shared_ptr<PreferReader> pr(new PreferReader(""));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Reader1, pr));
			else
				m.Dispatch(std::bind(Writer1, pr));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
	{
		std::cout << "Test SyncReadersWriters PreferWriter:" << std::endl;
		boost::shared_ptr<PreferWriter> pw(new PreferWriter(""));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Reader2, pw));
			else
				m.Dispatch(std::bind(Writer2, pw));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
	{
		std::cout << "Test SyncReadersWriters FairReaderWriter:" << std::endl;
		boost::shared_ptr<FairReaderWriter> frw(new FairReaderWriter(""));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Reader3, frw));
			else
				m.Dispatch(std::bind(Writer3, frw));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
	{
		std::cout << "Test SyncReadersWriters SimpleReaderWriter:" << std::endl;
		boost::shared_ptr<SimpleReaderWriter> srw(new SimpleReaderWriter(""));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 60; ++i)
		{
			if (i & 1)
				m.Dispatch(std::bind(Reader4, srw));
			else
				m.Dispatch(std::bind(Writer4, srw));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
}

}
#endif