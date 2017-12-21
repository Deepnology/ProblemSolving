#ifndef EVALUATE_DIVISIONS_H
#define EVALUATE_DIVISIONS_H
#include "Debug.h"
/*
Leetcode: Evaluate Division
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number).
Given some queries, return the answers.
If the answer does not exist, return -1.0.
Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is:
vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries
, where equations.size() == values.size(), and the values are positive. This represents the equations.
Return vector<double>.

According to the example above:
equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

Floyd Warshall's algorithm: O(V^3) time
see also AllPairsShortestPaths.h
*/
class EvaluateDivisions
{
public:
	EvaluateDivisions() {}

	std::vector<double> calcEquation(std::vector<std::pair<std::string, std::string>> equations, std::vector<double> & values, std::vector<std::pair<std::string, std::string>> queries)
	{
		//construct DAG
		std::unordered_map<std::string, std::unordered_map<std::string, double>> DAG;
		int N = equations.size();
		for (int i = 0; i < N; ++i)
		{
			auto p = equations[i];
			auto v = values[i];
			DAG[p.first][p.second] = v;
			DAG[p.second][p.first] = 1.0 / v;//reversed edge !!
			DAG[p.first][p.first] = 1.0;//self
			DAG[p.second][p.second] = 1.0;//self
		}

		//run FloydWarshall
		for (auto & mid : DAG)
		{
			for (auto & beg : DAG)
			{
				for (auto & end : DAG)
				{
					if (beg.first != end.first)
					{
						if (DAG[beg.first].count(mid.first) && DAG[mid.first].count(end.first))
						{
							DAG[beg.first][end.first] = DAG[beg.first][mid.first] * DAG[mid.first][end.first];
						}
					}
					//else
					//    DAG[beg.first][end.first] = 1.0;
				}
			}
		}

		std::vector<double> res;
		for (auto & p : queries)
		{
			if (DAG.count(p.first) && DAG[p.first].count(p.second))
				res.push_back(DAG[p.first][p.second]);
			else
				res.push_back(-1.0);
		}

		Debug::Print2D<std::string, double>()(DAG);
		std::cout << "EvaluateDivisions for the above DAG with queries=\"" << Debug::ToStr1D<std::string>()(queries) << "\": " << Debug::ToStr1D<double>()(res) << std::endl;
		return res;
	}
};
/*
Row#0	= a: [b,2], [a,1], [c,6]
Row#1	= b: [a,0.5], [b,1], [c,3]
Row#2	= c: [b,0.333333], [c,1], [a,0.166667]

EvaluateDivisions for the above DAG with queries="[a,c], [b,a], [a,e], [a,a], [x,x]": 6, 0.5, -1, 1, -1
*/
#endif
