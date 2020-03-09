#ifndef CLOSEST_REPETITION_H
#define CLOSEST_REPETITION_H
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Find the nearest repeated entries in an array
Let s be an array of strings.
Write a function which finds the distance of any closest pair of equal entries.
For example, if s = { "All", "work", "and", "no", "play", "makes", "for", "no", "work", "no", "fun", "and", "no", "results" }, then the 2nd and 3rd occurrences of "no" is the closest pair.

O(n) time, O(d) space, where d is the number of distinct strings in the array
*/
class ClosestRepetition
{
public:
	ClosestRepetition(){}
	~ClosestRepetition(){}

	int Iterate_HashTable(const std::vector<std::string> & v)
	{
		int N = v.size();
		std::unordered_map<std::string, int> location;//the index of the latest occurrence of any string
		int minDist = INT_MAX;
		std::string minDistStr;
		for (int i = 0; i < N; ++i)
		{
			auto itr = location.find(v[i]);
			if (itr != location.end())
			{
				if (i - itr->second < minDist)
				{
					minDist = i - itr->second;
					minDistStr = v[i];
				}
			}
			location[v[i]] = i;
		}

		std::cout << "ClosestRepetition Iterate_HashTable for \"" << Debug::ToStr1D<std::string>()(v) << "\": " << minDist << ", " << minDistStr << std::endl;
		return minDist;
	}
};
/*
ClosestRepetition Iterate_HashTable for "All, work, and, no, play, makes, for, no, work, no, fun, and, no, results": 2, no
*/
#endif