#ifndef SEARCH_INTERSPERSED_SORTED_STR_ARRAY_H
#define SEARCH_INTERSPERSED_SORTED_STR_ARRAY_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Cracking the coding interview 9.5
Given a sorted array of strings which is interspersed with empty strings,
write a method to find the location of a given string.

["at","","","","ball","","","car","","","dad","",""]
find "ball" will return 4
find "ballcar" will return -1

Key idea:
When binary searching each sub range [first,last], make sure:
1. shift last to the left until last != ""
2. shift middle to the right until middle != ""
*/
class SearchInterspersedSortedStrArray
{
public:
	SearchInterspersedSortedStrArray(){}
	~SearchInterspersedSortedStrArray(){}

	int FindIndex(const std::vector<std::string> & v, std::string s)
	{
		if (v.empty())
			return -1;
		std::string before = Debug::ToStr1D<std::string>()(v);

		int N = v.size();
		if (s.compare("") == 0)
			for (int i = 0; i < N; ++i)
				if (v[i].compare("") == 0)
				{
					std::cout << "SearchInterspersedSortedStrArray for \"" << s << "\" in \"" << before << "\":" << i << std::endl;
					return i;
				}

		/*binary search*/
		int first = 0;
		int last = N - 1;
		while (first <= last)
		{
			//1. ensure there is something at the end
			while (first <= last && v[last] == "")
				--last;
			if (first > last)
			{
				std::cout << "SearchInterspersedSortedStrArray for \"" << s << "\" in \"" << before << "\": not found" << std::endl;
				return -1;
			}
			//now last != ""

			//2. find middle which is first non-empty on its right side
			int middle = (last + first) >> 1;//(last+first)/2 (for even numbers: center's left)
			while (v[middle] == "")
				++middle;//will always find one
			//now middle != ""

			//3. compare v[middle] with s
			int r = v[middle].compare(s);
			if (r == 0)
			{
				std::cout << "SearchInterspersedSortedStrArray for \"" << s << "\" in \"" << before << "\": " << middle << std::endl;
				return middle;
			}
			if (r < 0)//v[middle] < s
				first = middle + 1;//search the right side
			else
				last = middle - 1;//search the left side
		}

		std::cout << "SearchInterspersedSortedStrArray for \"" << s << "\" in \"" << before << "\": not found" << std::endl;
		return -1;
	}


};
/*
SearchInterspersedSortedStrArray for "ball" in "at, , , , ball, , , car, , , dad, , ": 4
*/
#endif