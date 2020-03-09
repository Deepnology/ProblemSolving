#ifndef PEEKING_ITERATOR_H
#define PEEKING_ITERATOR_H
#include <vector>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Peeking Iterator
Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().
Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].
Call next() gets you 1, the first element in the list.
Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.
You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.

Hint:
Think of "looking ahead". You want to cache the next element.
Is one variable sufficient? Why or why not?
Test your design with call order of peek() before next() vs next() before peek().
For a clean implementation, check out Google's guava library source code.
Follow up: How would you extend your design to be generic and work with all types, not just integer?

In short: add a peek() method in the derived class with implementation in terms of base::next() and base::hasNext()
*/
class PeekingIteratorBase
{
	struct Data;
	Data* data;
public:
	PeekingIteratorBase(const std::vector<int>& nums) {}
	PeekingIteratorBase(const PeekingIteratorBase & iter) {}
	virtual ~PeekingIteratorBase() {}
	// Returns the next element in the iteration.
	int next() { return 0; }
	// Returns true if the iteration has more elements.
	bool hasNext() const { return false; }
};


class PeekingIterator : public PeekingIteratorBase
{
	bool hasPeeked;
	int nxtVal;
public:
	PeekingIterator(const std::vector<int> & nums) : PeekingIteratorBase(nums)
	{
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
		hasPeeked = false;
	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek()
	{
		if (hasPeeked)
			return nxtVal;
		if (PeekingIteratorBase::hasNext())//calling base::hasNext()
		{
			hasPeeked = true;
			nxtVal = PeekingIteratorBase::next();//calling base::next()
			return nxtVal;
		}
		//return nxtVal;
		throw new std::runtime_error("");
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next()
	{
		if (hasPeeked)
		{
			hasPeeked = false;
		}
		else
		{
			nxtVal = PeekingIteratorBase::next();//calling base::next()
		}
		return nxtVal;
	}

	bool hasNext() const
	{
		if (hasPeeked)
			return true;
		return PeekingIteratorBase::hasNext();//calling base::hasNext()
	}
};
#endif
