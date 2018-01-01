#ifndef GENERALIZED_MAJORITY_ELEMENTS_H
#define GENERALIZED_MAJORITY_ELEMENTS_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
Elements of programming interview, Greedy: The heavy hitter problem
You are reading a sequence of strings separated by whitespaces.
You are allowed to read the sequence twice.
                                                                                    --  n  --
Device an algorithm that uses O(k) memory to identify the words that occur at least | ----- | times, where n is the length of the sequence.
                                                                                        k

The code may appear to take O(n*k) time since the inner loop may take k steps (decrementing count for all k entries) and the outer loop is called n times.
However each word in the sequence can be erased only once, so the total time spent erasing is O(n) and the rest of the steps inside the outer loop run in O(1) time.

see also MajorityElement.h
*/
class GeneralizedMajorityElements
{
public:
	GeneralizedMajorityElements(){}
	~GeneralizedMajorityElements(){}

	//majority element appears at least N/k times, which means it must appear at least once in every k distinct elements in average
	std::vector<std::string> FromInputStream(std::istringstream && sin, int k)
	{
		std::string buf;
		std::unordered_map<std::string, int> candidates;//first: entry, second: count (keep track of at most k distinct entries)
		int N = 0;

		//1. first pass: compute k DISTINCT candidates
		while (sin >> buf)
		{
			++candidates[buf];
			++N;

			//keep only k DISTINCT candidates
			//each distinct majority element must have at least one in the candidates
			//when there are k+1 DISTINCT candidates, substract each candidate's count by 1, and discard the candidate whose count is 0
			//after discard, only k DISTINCT candidates will remain
			if (candidates.size() == k + 1)
			{
				auto itr = candidates.begin();
				while (itr != candidates.end())
				{
					if (--(itr->second) == 0)
						candidates.erase(itr++);
					else
						++itr;
				}
			}
		}
		std::cout << Debug::ToStr1D<std::string, int>()(candidates) << std::endl;

		//reset each candidate's count
		for (auto & itr : candidates)
			itr.second = 0;

		sin.clear();
		sin.seekg(0, std::ios::beg);

		//2. second pass: compute each candidate's count
		while (sin >> buf)
		{
			auto itr = candidates.find(buf);
			if (itr != candidates.end())
				++itr->second;
		}
		std::cout << Debug::ToStr1D<std::string, int>()(candidates) << std::endl;

		//collect candidates whose count >= N/k times, which will be final majority elements
		std::vector<std::string> res;
		for (const auto & itr : candidates)
		{
			if (itr.second >= (double)(N) / k)
				res.push_back(itr.first);
		}

		std::cout << "GeneralizedMajorityElements for \"" << k << "\" from \"" << sin.str() << "\": " << Debug::ToStr1D<std::string>()(res) << std::endl;
		return res;
	}
};
/*
[a,3], [d,3], [f,3], [b,1]
[a,5], [d,5], [f,5], [b,2]
GeneralizedMajorityElements for "4" from "a b d d a d e f c f a e d f a a b f d f": a, d, f
*/
#endif