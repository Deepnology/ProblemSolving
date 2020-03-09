#ifndef SYNC_DINING_PHILOSOPHERS_H
#define SYNC_DINING_PHILOSOPHERS_H
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <string>
#include <boost/function.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "Semaphore.h"
#include "ThreadMgr.h"
/*
http://en.wikipedia.org/wiki/Dining_philosophers_problem
https://homepages.warwick.ac.uk/~cssbd/cs224/sun/dpp.html
5 silent philosophers sit at a round table with bowls of rice.
Chopsticks are placed between each pair of adjacent philosophers.
Each philosopher must alternately think and eat.
However, a philosopher can only eat when he has both left and right chopsticks.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that each philosopher will not starve; 
i.e. can forever continue to alternate between eating and thinking, assuming that any philosopher cannot know when others may want to eat or think.

1. Resource hierarchy solution by Dijkstra
The chopsticks will be numbered 0 through 4 and each philosopher will always pick up the lower-numbered chopstick first, and then the higher-numbered chopstick, from among the 2 chopsticks he plans to use.
The order in which each philosopher puts down does not matter.
If 4 of the 5 philosophers simultaneously pick up their lower-numbered chopstick, only the highest numbered chopstick will remain on the table, so the 5th philosopher will not be able to pick up any chopstick.
Moreover, only 1 philosopher will have access to that highest-numbered chopstick, so he will be able to eat using two chopsticks.

2. Semaphore solution
Without the constraint that each philosopher must always pick the lower-numbered chopstick, the system can easily deadlock.
This can be fixed by adding another semaphore to ensure that not all philosophers may hold a chopstick at the same time.
However, this solution is unfair.

3. A critical section solution
*/
namespace SyncDiningPhilosophers
{
class DiningPhilosophers1
{
public:
	explicit DiningPhilosophers1(int count) : m_size(count)
	{
		for (int i = 0; i < count; ++i)
		{
			m_semaphoreChopstick.push_back(boost::shared_ptr<Semaphore>(new Semaphore(1)));
		}
	}

	void Philosopher(int id)
	{
		//thinking

		int lower = id;
		int higher = (id + 1) % m_size;
		if (lower > higher)
			std::swap(lower, higher);
		m_semaphoreChopstick[lower]->Wait();//must always choose lowest chopstick first to avoid deadlock
		m_semaphoreChopstick[higher]->Wait();

		//eating
		std::ostringstream oss;
		oss << "<" << id << ">";
		std::cout << oss.str();

		m_semaphoreChopstick[lower]->Signal();
		m_semaphoreChopstick[higher]->Signal();
	}
private:
	std::vector<boost::shared_ptr<Semaphore> > m_semaphoreChopstick;
	int m_size;
};

class DiningPhilosophers2
{
public:
	explicit DiningPhilosophers2(int count) : m_size(count), m_semaphore(count - 1)
	{
		for (int i = 0; i < count; ++i)
		{
			m_semaphoreChopstick.push_back(boost::shared_ptr<Semaphore>(new Semaphore(1)));
		}
	}

	void Philosopher(int id)
	{
		//thinking

		m_semaphore.Wait();//ensure max count-1 philosophers can hold chopstick(s)
		{
			m_semaphoreChopstick[id]->Wait();
			m_semaphoreChopstick[(id + 1) % m_size]->Wait();

			//eating
			std::ostringstream oss;
			oss << "[" << id << "]";
			std::cout << oss.str();

			m_semaphoreChopstick[id]->Signal();
			m_semaphoreChopstick[(id + 1) % m_size]->Signal();
		}
		m_semaphore.Signal();
	}
private:
	std::vector<boost::shared_ptr<Semaphore> > m_semaphoreChopstick;
	int m_size;

	Semaphore m_semaphore;
};

class DiningPhilosophers3
{
public:
	explicit DiningPhilosophers3(int count) : m_size(count)
	{
		for (int i = 0; i < count; ++i)
		{
			m_semaphoreChopstick.push_back(boost::shared_ptr<Semaphore>(new Semaphore(1)));
		}
	}

	void Philosopher(int id)
	{
		//thinking

		//ensure only 1 philosopher can hold chopsticks
		{
			boost::mutex::scoped_lock lock(m_mutex);
			m_semaphoreChopstick[id]->Wait();
			m_semaphoreChopstick[(id + 1) % m_size]->Wait();
		}

		//eating
		std::ostringstream oss;
		oss << "{" << id << "}";
		std::cout << oss.str();

		m_semaphoreChopstick[id]->Signal();
		m_semaphoreChopstick[(id + 1) % m_size]->Signal();
	}
private:
	std::vector<boost::shared_ptr<Semaphore> > m_semaphoreChopstick;
	int m_size;

	boost::mutex m_mutex;
};



/*the following functions are for test*/
std::string Philosopher1(boost::shared_ptr<DiningPhilosophers1> dp, int id)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		dp->Philosopher(id);
	}
	return "";
}
std::string Philosopher2(boost::shared_ptr<DiningPhilosophers2> dp, int id)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		dp->Philosopher(id);
	}
	return "";
}
std::string Philosopher3(boost::shared_ptr<DiningPhilosophers3> dp, int id)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		dp->Philosopher(id);
	}
	return "";
}
void Test()
{
	{
		std::cout << "Test SyncDiningPhilosophers DiningPhilosophers1:" << std::endl;
		boost::shared_ptr<DiningPhilosophers1> dp(new DiningPhilosophers1(5));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 5; ++i)
		{
			m.Dispatch(std::bind(Philosopher1, dp, i));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();

	}
	{
		std::cout << "Test SyncDiningPhilosophers DiningPhilosophers2:" << std::endl;
		boost::shared_ptr<DiningPhilosophers2> dp(new DiningPhilosophers2(5));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 5; ++i)
		{
			m.Dispatch(std::bind(Philosopher2, dp, i));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
	{
		std::cout << "Test SyncDiningPhilosophers DiningPhilosophers3:" << std::endl;
		boost::shared_ptr<DiningPhilosophers3> dp(new DiningPhilosophers3(5));
		thread_mgr::ThreadMgr m;
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
		for (int i = 0; i < 5; ++i)
		{
			m.Dispatch(std::bind(Philosopher3, dp, i));
		}
		std::cout << "Hit ENTER to continue ..." << std::endl;
		std::cin.ignore();
	}
}

}
#endif