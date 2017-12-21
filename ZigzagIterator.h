#ifndef	ZIGZAG_ITERATOR_H
#define ZIGZAG_ITERATOR_H
#include <vector>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Leetocode: Zigzag Iterator
Given two 1d vectors, implement an iterator to return their elements alternately.
For example, given two 1d vectors:
v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].
Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

*/
class ZigzagIterator
{
	std::vector<int>::const_iterator itr1;
	std::vector<int>::const_iterator itr2;
	std::vector<int>::const_iterator end1;
	std::vector<int>::const_iterator end2;
	int cur;
public:
	ZigzagIterator(const std::vector<int> & v1, const std::vector<int> & v2) 
	{
		itr1 = v1.cbegin();
		itr2 = v2.cbegin();
		end1 = v1.cend();
		end2 = v2.cend();
		cur = 0;
	}
	~ZigzagIterator() {}

	bool hasNext()
	{
		return itr1 != end1 || itr2 != end2;
	}

	int next()
	{
		int res;
		if (itr1 == end1)
		{
			res = *itr2;
			++itr2;
		}
		else if (itr2 == end2)
		{
			res = *itr1;
			++itr1;
		}
		else
		{
			if (cur == 0)
			{
				res = *itr1;
				++itr1;
				cur = 1;
			}
			else
			{
				res = *itr2;
				++itr2;
				cur = 0;
			}
		}

		std::cout << "ZigzagIterator Next: " << res << std::endl;
		return res;
	}
};
/*
ZigzagIterator Next: 1
ZigzagIterator Next: 3
ZigzagIterator Next: 2
ZigzagIterator Next: 4
ZigzagIterator Next: 5
ZigzagIterator Next: 6
*/
#endif
