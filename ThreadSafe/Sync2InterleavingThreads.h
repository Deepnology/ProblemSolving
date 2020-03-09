#ifndef SYNC_2_INTERLEAVING_THREADS_H
#define SYNC_2_INTERLEAVING_THREADS_H
#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include "Semaphore.h"
/*
Elements of programming interview, ParallelComputing: Implement synchronization for two interleaving threads
Thread T1 prints odd numbers from 1 to 100; Thread T2 prints even numbers from 1 to 100.
Write code in which 2 threads, running concurrently, print the numbers from 1 to 100 in order.
*/
namespace Sync2InterleavingThreads
{
	//better way
	static std::mutex m_mutex;
	static int m_count = 1;
	static bool m_wait1 = false;
	static bool m_wait2 = false;
	static std::condition_variable m_condition1;
	static std::condition_variable m_condition2;
	void Func1()
	{
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		for (int i = 1; i <= 1000; )
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_wait1 = false;
			if (!(m_count & 1))//even
			{
				m_wait1 = true;
				m_condition1.wait(lock);
				std::cout << "Thread1_" << i << std::endl;
				continue;
			}
			std::cout << "Thread1: " << i << " (" << m_count << ")" << std::endl;
			++m_count;
			if (m_wait2)
				m_condition2.notify_one();
			i += 2;
		}
	}
	void Func2()
	{
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		for (int i = 2; i <= 1000; )
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_wait2 = false;
			if (m_count & 1)//odd
			{
				m_wait2 = true;
				m_condition2.wait(lock);
				std::cout << "Thread2_" << i << std::endl;
				continue;
			}
			std::cout << "Thread2: " << i << " (" << m_count << ")" << std::endl;
			++m_count;
			if (m_wait1)
				m_condition1.notify_one();
			i += 2;
		}
	}

	//bad way
	static Semaphore m_semaphore(1);
	static int m_count_ = 1;
	static bool m_waitA = false;
	static bool m_waitB = false;
	static Semaphore m_semaphoreA(0);
	static Semaphore m_semaphoreB(0);
	void FuncA()
	{
		for (int i = 1; i <= 1000; )
		{
			m_semaphore.Wait();
			m_waitA = false;
			if (!(m_count_ & 1))//even
			{
				m_waitA = true;
				m_semaphore.Signal();
				m_semaphoreA.Wait();
				std::cout << "Thread1_" << i << std::endl;
				continue;
			}
			std::cout << "Thread1: " << i << " (" << m_count_ << ")" << std::endl;
			++m_count_;
			if (m_waitB)//WARNING: m_waitB might not be sync with m_semaphoreB !!
				m_semaphoreB.Signal();
			m_semaphore.Signal();
			i += 2;
		}
	}
	void FuncB()
	{
		for (int i = 2; i <= 1000; )
		{
			m_semaphore.Wait();
			m_waitB = false;
			if (m_count_ & 1)//odd
			{
				m_waitB = true;
				m_semaphore.Signal();
				m_semaphoreB.Wait();
				std::cout << "Thread2_" << i << std::endl;
				continue;
			}
			std::cout << "Thread2: " << i << " (" << m_count_ << ")" << std::endl;
			++m_count_;
			if (m_waitA)//WARNING: m_waitA might not be sync with m_semaphoreA !!
				m_semaphoreA.Signal();
			m_semaphore.Signal();
			i += 2;
		}
	}
	void Solve()
	{
		std::thread t1(std::bind(&Func1));
		std::thread t2(std::bind(&Func2));
		t1.join();
		t2.join();
	}
	void Solve2()
	{
		std::thread t1(std::bind(&FuncA));
		std::thread t2(std::bind(&FuncB));
		t1.join();
		t2.join();
	}
}

#endif