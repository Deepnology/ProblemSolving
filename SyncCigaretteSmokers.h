#ifndef SYNC_CIGARETTE_SMOKERS_H
#define SYNC_CIGARETTE_SMOKERS_H
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
http://en.wikipedia.org/wiki/Cigarette_smokers_problem
Assume a cigarette requires 3 ingredients to smoke:
1. Tobacco
2. Smoking paper
3. A match
Assume there are also 3 chain smokers around a table, each of whom has an infinite supply of one of the 3 ingredients --- one smoker has an infinite supply of tobacco, another has an infinite supply of paper, and the third has an infinte supply of matches.
Assume there is also a non-smoking arbiter.
The arbiter enables the smokers to make their cigarettes by arbitrarily selecting 2 of the smokers, taking one item out of each of their supplies, and placing the item on the table.
The arbiter then notifies the third smoker that they have done this.
The third smoker removes the two items from the table and uses them (along with their own supply) to make a cigarette, which they smoke for a while.
Meanwhile, the arbiter, seeing the table empty, again chooses 2 smokers at random and places their items on the table.
The porcess continues forever.

The smokers do not hoard items from the table; a smoker only begins to roll a new cigarette once they have finished smoking the last one.
For instance if the arbiter places tobacco and paper on the table while the match-supply smoker is smoking, the tobacco and paper will remain untouched on the table until the match-supply smoker is finished with his/her cigarette and then collects the items.
*/
namespace SyncCigaretteSmokers
{
class CigaretteSmoker
{
public:
	CigaretteSmoker() : m_semaphoreArbiter(1)
	{
		for (int i = 0; i < 3; ++i)
			m_semaphoreSmokers.push_back(boost::shared_ptr<Semaphore>(new Semaphore(0)));
	}
	void Arbiter()
	{
		m_semaphoreArbiter.Wait();

		//choose 2 smokers nondeterministically to take one item out of each of their supplies, and place the items on the table
		//then notify the 3rd smoker that they have done this
		int smoker3rd = rand() % 3;
		std::ostringstream oss;
		oss << "{" << smoker3rd << "}";
		std::cout << oss.str();

		m_semaphoreSmokers[smoker3rd]->Signal();
	}
	void Smoker(int id)
	{
		m_semaphoreSmokers[id]->Wait();

		//make a cigarette
		std::ostringstream oss;
		oss << "<" << id << ">";
		std::cout << oss.str();

		m_semaphoreArbiter.Signal();

		//smoke the cigarette
		oss.str(std::string());
		oss << "[" << id << "]";
		std::cout << oss.str();
	}
private:
	Semaphore m_semaphoreArbiter;
	std::vector<boost::shared_ptr<Semaphore> > m_semaphoreSmokers;//since the mutex in Semaphore is not copy-constructable, so Semaphore can't be put in vector. use ptr instead
};



/*the following functions are for test*/
std::string Arbiter(boost::shared_ptr<CigaretteSmoker> cs)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		cs->Arbiter();
	}
	return "";
}
std::string Smoker(boost::shared_ptr<CigaretteSmoker> cs, int id)
{
	while (true)
	{
		int microsec = rand() % 1000000 + 1;
		boost::this_thread::sleep(boost::posix_time::microseconds(microsec));
		cs->Smoker(id);
	}
	return "";
}
void Test()
{
	std::cout << "Test SyncCigaretteSmokers:" << std::endl;
	boost::shared_ptr<CigaretteSmoker> cs(new CigaretteSmoker());
	thread_mgr::ThreadMgr m;
	system("pause");
	m.Dispatch(std::bind(Arbiter, cs));
	m.Dispatch(std::bind(Smoker, cs, 0));
	m.Dispatch(std::bind(Smoker, cs, 1));
	m.Dispatch(std::bind(Smoker, cs, 2));
	system("pause");
}

}
#endif