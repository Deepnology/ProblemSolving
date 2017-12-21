#ifndef DESIGN_PHONE_DIRECTORY_H
#define DESIGN_PHONE_DIRECTORY_H
#include "Debug.h"
/*
Leetcode: Design Phone Directory
Design a Phone Directory which supports the following operations:

get: Provide a number which is not assigned to anyone.
check: Check if a number is available or not.
release: Recycle or release a number.

Example:
// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);

// It can return any available phone number. Here we assume it returns 0.
directory.get();

// Assume it returns 1.
directory.get();

// The number 2 is available, so return true.
directory.check(2);

// It returns 2, the only number that is left.
directory.get();

// The number 2 is no longer available, so return false.
directory.check(2);

// Release number 2 back to the pool.
directory.release(2);

*/
class DesignPhoneDirectory
{
	int m_maxCount;
	int m_next;//the next number that has never been used to provide

	std::vector<int> m_inUse;//m_inUse[i]==1: number i is in use, 0: number i is not in use
	std::vector<int> m_recycle;//m_recycle[m_rIdx]: holds a list of recycled numbers from m_recycle[0] to m_recycle[m_rIdx]
	int m_rIdx;

public:
	/** Initialize your data structure here
	@param maxNumbers - The maximum numbers that can be stored in the phone directory. */
	DesignPhoneDirectory(int maxNumbers) : m_maxCount(maxNumbers)
		, m_next(0), m_inUse(maxNumbers, 0), m_recycle(maxNumbers, 0), m_rIdx(-1)
	{

	}
	~DesignPhoneDirectory() {}

	/** Provide a number which is not assigned to anyone.
	@return - Return an available number. Return -1 if none is available. */
	int get()
	{
		if (m_next == m_maxCount && m_rIdx < 0)
			return -1;
		if (m_rIdx >= 0)
		{
			int num = m_recycle[m_rIdx--];
			m_inUse[num] = 1;

			std::cout << "DesignPhoneDirectory get: " << num << std::endl;
			return num;
		}
		else
		{
			m_inUse[m_next] = 1;

			std::cout << "DesignPhoneDirectory get: " << m_next << std::endl;
			return m_next++;
		}
	}

	/** Check if a number is available or not. */
	bool check(int number)
	{
		bool notInUse = number >= 0 && number < m_maxCount && m_inUse[number] == 0;

		std::cout << "DesignPhoneDirectory check \"" << number << "\": " << notInUse << std::endl;
		return notInUse;
	}

	/** Recycle or release a number. */
	void release(int number)
	{
		if (number >= 0 && number < m_maxCount && m_inUse[number] == 1)
		{
			m_recycle[++m_rIdx] = number;
			m_inUse[number] = 0;

			std::cout << "DesignPhoneDirectory release: " << number << std::endl;
		}
	}
};
/*
DesignPhoneDirectory get: 0
DesignPhoneDirectory get: 1
DesignPhoneDirectory check "2": 1
DesignPhoneDirectory get: 2
DesignPhoneDirectory check "2": 0
DesignPhoneDirectory release: 2
DesignPhoneDirectory check "2": 1
*/
#endif
