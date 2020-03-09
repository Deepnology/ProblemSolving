#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <limits>
/*
Semaphore: to limit a certain number of threads' access to a resource
a thread will be blocked by wait() when the number of threads that have access to a resource reaches the limit
a thread will signal() one other thread that is blocked by wait() to access to a resource when it releases access to the resource

https://www.justsoftwaresolutions.co.uk/threading/locks-mutexes-semaphores.html
A semaphore is a very relaxed type of lockable object. 
A given semaphore has a predefined maximum count, and a current count. 
You take ownership of a semaphore with a wait operation, also referred to as decrementing the semaphore, or even just abstractly called P. 
You release ownership with a signal operation, also referred to as incrementing the semaphore, a post operation, or abstractly called V. 
The single-letter operation names are from Dijkstra's original paper on semaphores.

Every time you wait on a semaphore, you decrease the current count. 
If the count was greater than zero then the decrement just happens, and the wait call returns. 
If the count was already zero then it cannot be decremented, so the wait call will block until another thread increases the count by signalling the semaphore.

Every time you signal a semaphore, you increase the current count. 
If the count was zero before you called signal, and there was a thread blocked in wait then that thread will be woken. 
If multiple threads were waiting, only one will be woken. 
If the count was already at its maximum value then the signal is typically ignored, although some semaphores may report an error.

Whereas mutex ownership is tied very tightly to a thread, and only the thread that acquired the lock on a mutex can release it, semaphore ownership is far more relaxed and ephemeral. 
Any thread can signal a semaphore, at any time, whether or not that thread has previously waited for the semaphore.

http://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
http://stackoverflow.com/questions/3928853/how-can-i-achieve-something-similar-to-a-semaphore-using-boost-in-c
*/
class Semaphore
{
	boost::mutex m_mutex;
	boost::condition m_condition;
	unsigned long m_count;
public:
	explicit Semaphore(unsigned long count) : m_count(count)
	{

	}
	void Wait()//called when a thread entering the shared critical section
	{
		boost::mutex::scoped_lock lock(m_mutex);
		while (m_count == 0)
			m_condition.wait(lock);
		--m_count;
	}
	void Signal()//called when a thread leaving the shared critical section
	{
		boost::mutex::scoped_lock lock(m_mutex);
		++m_count;
		m_condition.notify_one();
	}
};
#endif