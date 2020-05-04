#ifndef SINGLES_FROM_2_SORTED_STR_ARR_H
#define SINGLES_FROM_2_SORTED_STR_ARR_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
The top 20 coding interview
The non-crooks problem
Given 2 string arrays containing names in ascending order without duplicates.
Find the names that are not crooks: appear in at least one array but not in both.

O(n+m) time
*/
class SinglesFrom2SortedStrArr
{
public:
	void Solve(const std::vector<std::string> & v1, const std::vector<std::string> & v2)
	{
		int N = v1.size();
		int M = v2.size();
		int i = 0;
		int j = 0;
		std::vector<std::string> res;
		while (i < N && j < M)
		{
			int cmp = strcmp(v1[i].c_str(), v2[j].c_str());
			if (cmp > 0)
			{
				res.push_back(v2[j++]);//advance the vector that has the smaller one
			}
			else if (cmp < 0)
			{
				res.push_back(v1[i++]);//advance the vector that has the smaller one
			}
			else//equal, advance both vectors
			{
				++i;
				++j;
			}
		}
		while (i < N)
			res.push_back(v1[i++]);
		while (j < M)
			res.push_back(v2[j++]);

		std::cout << "SinglesFrom2SortedStrArr for \"" << Debug::ToStr1D<std::string>()(v1) << "\" and \"" << Debug::ToStr1D<std::string>()(v2) << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
	}
};
#endif