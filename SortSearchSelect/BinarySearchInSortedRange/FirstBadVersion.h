#ifndef FIRST_BAD_VERSION_H
#define FIRST_BAD_VERSION_H
#include <iostream>
#include <string>
#include "Debug.h"
/*
You are a product manager and currently leading a team to develop a new product.
Unfortunately, the latest version of your product fails the quality check.
Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version.
You should minimize the number of calls to the API.

We want to find the first bad version in [1, 2, ..., n], and all versions after the 1st bad version are bad.
=> Find the lower bound.
*/
class FirstBadVersion
{
public:
	FirstBadVersion() {}
	~FirstBadVersion() {}

	int BinarySearch(int N)
	{
		int left = 1;
		int right = N;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (isBadVersion(mid))
				right = mid - 1;
			else
				left = mid + 1;
		}
		//now left is lower bound

		std::cout << "FirstBadVersion BinarySerach for \"" << N << "\": " << left << std::endl;
		return left;
	}

	bool isBadVersion(int version)
	{
		if (version < 1)
			return false;
		if (version > 1000)//N
			return false;
		if (version < 777)//777 is the first bad version
			return false;
		else//777~1000 are all bad versions
			return true;
	}
};
/*
FirstBadVersion BinarySerach for "1000": 777
*/
#endif
