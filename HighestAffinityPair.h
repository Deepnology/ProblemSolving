#ifndef HIGHEST_AFFINITY_PAIR_H
#define HIGHEST_AFFINITY_PAIR_H
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>
#include "Debug.h"
/*
Elements of programming interview, HashTable: find a highest affinity pair
Given a list of pairs of {website, username}.
Find a pair of websites which have most intersected usernames.

Let P be the number of pages, and V the number of views.
Space: O(P+V) = O(V), since V >= P.
Time: O(min(P^2*V, V^2))
*/
class HighestAffinityPair
{
public:
	HighestAffinityPair(){}
	~HighestAffinityPair(){}

	std::pair<std::string, std::string> HashTable(const std::vector<std::pair<std::string, std::string>> & v)//first: website, second: username
	{
		//1. build a website hash map
		std::unordered_map<std::string, std::set<std::string> > hashMap;//first: website, second: a sorted set of distinct usernames
		for (const auto & p : v)
		{
			hashMap[p.first].emplace(p.second);
		}

		int maxAffinityCount = 0;
		std::string maxPair1;
		std::string maxPair2;

		//2. enumerate all possible pairs of distinct websites
		for (auto itr1 = hashMap.begin(); itr1 != hashMap.end(); ++itr1)
		{
			auto itr2 = itr1;
			for (++itr2; itr2 != hashMap.end(); ++itr2)
			{
				//see also UnionIntersection2SortedArrays.h
				std::vector<std::string> intersection;
				auto i1 = itr1->second.begin();
				auto i2 = itr2->second.begin();
				while (i1 != itr1->second.end() && i2 != itr2->second.end())
				{
					if (*i1 == *i2)
					{
						intersection.push_back(*i1);
						++i1;
						++i2;
					}
					else if (*i1 < *i2)
					{
						++i1;//advance smaller one
					}
					else
					{
						++i2;//advance smaller one
					}
				}
				if ((int)intersection.size() > maxAffinityCount)
				{
					maxAffinityCount = intersection.size();
					maxPair1 = itr1->first;
					maxPair2 = itr2->first;
				}
			}
		}

		Debug::Print2D<std::string>()(hashMap);
		std::cout << "HighestAffinityPair HashTable for \"" << Debug::ToStr1D<std::string>()(v) << "\": " << maxAffinityCount << ", [" << maxPair1 << "," << maxPair2 << "]" << std::endl;
		return{ maxPair1, maxPair2 };
	}
};
/*
Row#0	= yahoo: aa314, ap42
Row#1	= google: aa314, ap42, th1
Row#2	= twitter: aa314, ap42, th1

HighestAffinityPair HashTable for "[yahoo,ap42], [google,ap42], [twitter,th1], [google,aa314], [google,aa314], [google,th1], [twitter,aa314], [twitter,ap42], [yahoo,aa314]": 3, [google,twitter]
*/
#endif