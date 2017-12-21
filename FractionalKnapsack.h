#ifndef FRACTIONAL_KNAPSACK_H
#define FRACTIONAL_KNAPSACK_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview: Knapsack problem, variant
Solve the knapsack problem when the thief can take a fractional amount of an item.
https://www.cse.ust.hk/~dekai/271/notes/L14/L14.pdf
http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/Greedy/knapscakFrac.htm

Greedy:
1. sort all items based on the cp value (val/wt) in descending order
2. always pick the item with the highest cp value first until total weight exceeds the knapsack's limit.

Greedy: O(nlogn) time bounded by the sorting part, O(n) space
*/
class FractionalKnapsack
{
public:
	FractionalKnapsack(){}
	~FractionalKnapsack(){}

	typedef std::pair<double, std::pair<double, double> > CP_Pair;

	double Greedy(const std::vector<std::pair<double, double> > & v, double W)//first: wt, second: val
	{
		int N = v.size();
		std::vector<CP_Pair> cp;//first: val/wt, second.first: wt, second.second: val
		for (int i = 0; i < N; ++i)
		{
			cp.push_back({ v[i].second / v[i].first, v[i] });
		}
		std::sort(cp.begin(), cp.end(), [](const CP_Pair & a, const CP_Pair & b)->bool
		{
			return a.first > b.first;//sort cp in descending order
		});

		//greedy, always pick the highest cp item first
		std::vector<std::pair<double, double> > res;
		double weight = 0;
		int item = 0;
		while (weight < W && item < N)
		{
			if (weight + cp[item].second.first <= W)
			{
				weight += cp[item].second.first;
				res.push_back(cp[item].second);
				++item;
			}
			else
			{
				double fractionWt = W - weight;
				weight += fractionWt;
				res.push_back({ fractionWt, cp[item].second.second });
				++item;
			}
		}
		
		int count = res.size();
		double totalVal = 0;
		for (int i = 0; i < count; ++i)
		{
			totalVal += res[i].second;
		}

		std::cout << "FractionalKnapsack Greedy for MaxWt=\"" << W << "\" from [Wt,Val]=\"" << Debug::ToStr1D<double>()(v) << "\": " << totalVal << ", from: " << Debug::ToStr1D<double>()(res) << "." << std::endl;
		return totalVal;
	}
};
/*
FractionalKnapsack Greedy for MaxWt="5" from [Wt,Val]="[2,140], [3,240], [5,150], [1,200]": 580, from: [1,200], [3,240], [1,140].
*/
#endif