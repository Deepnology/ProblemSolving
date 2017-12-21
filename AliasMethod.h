#ifndef ALIAS_METHOD_H
#define ALIAS_METHOD_H
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"
/*
http://www.keithschwarz.com/interesting/code/?dir=alias-method
http://www.keithschwarz.com/darts-dice-coins/
http://stackoverflow.com/questions/5027757/data-structure-for-loaded-dice

not understood
the output seems incorrect

See also RandomFromProbDist.h
*/
class AliasMethod
{
	std::vector<int> m_alias;
	std::vector<double> m_probability;
	std::string m_probDist;
public:
	explicit AliasMethod(std::vector<double> probDist) : m_alias(probDist.size()), m_probability(probDist.size()), m_probDist(Debug::ToStr1D<double>()(probDist))
	{
		int N = probDist.size();
		double average = 1.0 / N;

		std::stack<int> small;
		std::stack<int> large;

		for (int i = 0; i < N; ++i)
			if (probDist[i] >= average)
				large.push(i);
			else
				small.push(i);

		while (!small.empty() && !large.empty())
		{
			int less = small.top();
			small.pop();
			int more = large.top();
			large.pop();

			m_probability[less] = probDist[less] * N;
			m_alias[less] = more;

			probDist[more] = (probDist[more] + probDist[less]) - average;

			if (probDist[more] >= average)
				large.push(more);
			else
				small.push(more);
		}

		while (!small.empty())
		{
			m_probability[small.top()] = 1.0;
			small.pop();
		}
		while (!large.empty())
		{
			m_probability[large.top()] = 1.0;
			large.pop();
		}

		srand((unsigned int)time(NULL));
	}
	~AliasMethod(){}

	int NextIndex()
	{
		int N = m_probability.size();
		int r = rand() % N;//0~(n-1)
		bool coinToss = ((rand() % 1000) / 1000) < m_probability[r];
		return coinToss ? r : m_alias[r];
	}

	void Roll(const std::vector<int> & v, int times)
	{
		if (v.size() != m_probability.size())
			throw std::runtime_error("");
		int N = v.size();
		std::vector<std::pair<int,int>> res;//(v[i],count)
		for (int i = 0; i < N; ++i)
			res.push_back(std::make_pair(v[i], 0));
		for (int i = 0; i < times; ++i)
			++res[this->NextIndex()].second;

		std::cout << "AliasMethod for \"" << Debug::ToStr1D<int>()(v) << "\"" << std::endl
			<< ", with InputProbDist \"" << m_probDist << "\", AvgProb \"" << (double)(1.0/N) << "\"" << std::endl
			<< ", with Probability \"" << Debug::ToStr1D<double>()(m_probability) << "\"" << std::endl
			<< ", with Alias \"" << Debug::ToStr1D<int>()(m_alias) << "\"" << std::endl
			<< ", Roll \"" << times << "\"-times: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
AliasMethod for "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14"
, with InputProbDist "0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.04, 0.06, 0.06, 0.07, 0.09, 0.11, 0.13, 0.15, 0.17", AvgProb "0.0666667"
, with Probability "0.15, 0.15, 0.3, 0.3, 0.45, 0.45, 0.6, 0.9, 0.9, 1, 0.95, 0.6, 0.8, 0.7, 0.85"
, with Alias "11, 12, 13, 13, 14, 14, 14, 14, 14, 0, 9, 10, 11, 12, 13"
, Roll "1000"-times: [0,73], [1,66], [2,61], [3,69], [4,66], [5,65], [6,73], [7,63], [8,70], [9,62], [10,68], [11,64], [12,57], [13,78], [14,65]
*/
#endif