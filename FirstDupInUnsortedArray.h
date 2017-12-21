#ifndef FIRST_DUP_IN_UNSORTED_ARRAY_H
#define FIRST_DUP_IN_UNSORTED_ARRAY_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_set>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/find-first-repeating-element-array-integers/
Given an array of integers.
Find the first repeating element in it.
We need to find the element that occurs more than once and whose index of first occurrence is smallest.

HashTable: O(n) time, O(n) space
*/
class FirstDupInUnsortedArray
{
public:
	FirstDupInUnsortedArray(){}
	~FirstDupInUnsortedArray(){}

	int HashTable(const std::vector<int> & v)
	{
		int N = v.size();
		std::unordered_set<int> set;
		int first = -1;
		for (int i = N - 1; i >= 0; --i)
		{
			if (set.count(v[i]) == 0)
				set.insert(v[i]);
			else
				first = i;
		}

		std::string res = (first == -1) ? "N" : std::to_string(v[first]);
		std::cout << "FirstDupInUnsortedArray HashTable for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return first;
	}
};
/*
FirstDupInUnsortedArray HashTable for "9, 5, 3, 4, 3, 5, 6": 5
*/
#endif