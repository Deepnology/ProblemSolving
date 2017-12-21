#ifndef GAS_STATION_H
#define GAS_STATION_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Debug.h"
/*
Leetcode: Gas Station
// There are N gas stations along a circular route, where the amount of gas
// at station i is gas[i].
//
// You have a car with an unlimited gas tank and it costs cost[i] of gas to
// travel from station i to its next station (i+1). You begin the journey
// with an empty tank at one of the gas stations.
//
// Return the starting gas station's index if you can travel around the
// circuit once, otherwise return -1.
//
// Note:
// The solution is guaranteed to be unique.
//
Complexity:
FindStart_Greedy: O(n) time
FindStart_Greedy2: O(n) time
FindStart_BruteForce: O(n^2) time
*/
class GasStation
{
public:
	GasStation(){}
	~GasStation(){}

	int FindStart_Greedy(const std::vector<int> & gas, const std::vector<int> & cost)
	{
		int sum = 0;//local remaining gas sum
		int total = 0;//global remaining gas sum
		int res = -1;
		for (int i = 0; i < (int)gas.size(); ++i)
		{
			sum += gas[i] - cost[i];
			total += gas[i] - cost[i];
			if (sum < 0)//cannot reach index i + 1 from index i
			{
				sum = 0;
				res = i;
			}
		}
		if (total < 0)//cannot complete a circle
			res = -1;
		else//can complete circle
			res += 1;//cannot reach index res from index res - 1 => starting index should be res + 1

		std::cout << "GasStation FindStart_Greedy for \"" << Debug::ToStr1D<int>()(gas) << "\" and \"" << Debug::ToStr1D<int>()(cost) << "\" is: " << res << std::endl;
		return res;
	}

	int FindStart_Greedy2(const std::vector<int> & gas, const std::vector<int> & cost)
	{
		int lowest = 0;//the lowest remaining gas sum so far (should be negative)
		int total = 0;//global remaining gas sum
		int res = -1;
		for (int i = 0; i < (int)gas.size(); ++i)
		{
			total += gas[i] - cost[i];
			if (total < lowest)//cannot reach index i + 1 from index i
			{
				lowest = total;
				res = i;
			}
		}
		if (total < 0)//cannot complete a circle
			res = -1;
		else//can complete circle
			res += 1;//cannot reach index res from index res - 1 => starting index should be res + 1

		std::cout << "GasStation FindStart_Greedy2 for \"" << Debug::ToStr1D<int>()(gas) << "\" and \"" << Debug::ToStr1D<int>()(cost) << "\" is: " << res << std::endl;
		return res;
	}

	int FindStart_BruteForce(const std::vector<int> & gas, const std::vector<int> & cost)
	{
		int N = gas.size();
		int res = -1;
		for (int i = 0; i < N; ++i)
		{
			//test if starting from i can complete a circular route
			bool canFinish = true;
			int total = 0;
			for (int j = i; j < (i + N); ++j)
			{
				total += gas[j % N] - cost[j % N];
				if (total < 0)
				{
					canFinish = false;
					break;
				}
			}
			if (canFinish)
			{
				res = i;
				break;
			}
		}

		std::cout << "GasStation FindStart_BruteForce for \"" << Debug::ToStr1D<int>()(gas) << "\" and \"" << Debug::ToStr1D<int>()(cost) << "\" is: " << res << std::endl;
		return res;
	}
};

/*
Elements of programming interview, Greedy: The gasup problem
In the gasup problem, n cities are arranged on a circular road.
You need to visit all the n cities and comb back to the starting city.
A certain amount of gas is available at each city.
The total amount of gas is equal to the amount of gas required to go around the road once.
Your gas tank has unlimited capacity.
Call a city C ample if you can begin at C with an empty tank, refill at it, then travel through all the remaining cities, refilling at each, and return to C, without running out of gas at any point.

Given an instance of the gasup problem, how would you efficiently compute an ample city, if one exists?

Gas (Galon): 20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25
Dist (Mile): 300, 400, 1000, 300, 300, 600, 400, 1100, 400, 1000, 200, 300, 300
GasPerGalon: 20

The ample city would be the 8-th city (65, 400).

FindStart_Greedy: O(n) time, O(1) space
FindStart_BruteForce: O(n^2) time, O(1) space
*/
class GasStation2
{
public:
	GasStation2(){}
	~GasStation2(){}

	int FindStart_Greedy(const std::vector<int> gas, const std::vector<int> distance, int milePerGalon)
	{
		int N = gas.size();
		int carryGas = 0;
		int ampleCity = 0;
		int ampleCityCarryGas = 0;
		for (int i = 1; i < N; ++i)
		{
			carryGas += gas[i - 1] - distance[i - 1] / milePerGalon;
			if (carryGas < ampleCityCarryGas)
			{
				ampleCityCarryGas = carryGas;
				ampleCity = i;
			}
		}

		std::cout << "GasStation2 FindStart_Greedy for gas=\"" << Debug::ToStr1D<int>()(gas) << "\", dist=\"" << Debug::ToStr1D<int>()(distance) << "\", milePerGalon=\"" << milePerGalon << "\": " << ampleCity << std::endl;
		return ampleCity;
	}

	int FindStart_BruteForce(const std::vector<int> gas, const std::vector<int> distance, int milePerGalon)
	{
		int N = gas.size();
		int ampleCity = -1;

		for (int i = 0; i < N; ++i)
		{
			//test if starting from i can complete a circular route
			bool canFinish = true;
			int carryGas = 0;
			for (int j = i + 1; j < ((i + 1) + N); ++j)
			{
				//std::cout << i << "," << (j - 1) % N << std::endl;
				carryGas += gas[(j - 1) % N] - distance[(j - 1) % N] / milePerGalon;
				if (carryGas < 0)
				{
					canFinish = false;
					break;
				}
			}
			if (canFinish)
			{
				ampleCity = i;
				break;
			}
		}

		std::cout << "GasStation2 FindStart_BruteForce for gas=\"" << Debug::ToStr1D<int>()(gas) << "\", dist=\"" << Debug::ToStr1D<int>()(distance) << "\", milePerGalon=\"" << milePerGalon << "\": " << ampleCity << std::endl;
		return ampleCity;
	}
};
/*
GasStation FindStart_Greedy for "7, 2, 7, 1, 4, 6, 5" and "5, 3, 1, 4, 7, 2, 6" is: 0
GasStation FindStart_Greedy2 for "7, 2, 7, 1, 4, 6, 5" and "5, 3, 1, 4, 7, 2, 6" is: 0
GasStation FindStart_BruteForce for "7, 2, 7, 1, 4, 6, 5" and "5, 3, 1, 4, 7, 2, 6" is: 0
GasStation FindStart_Greedy for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 7, 2, 6" is: 2
GasStation FindStart_Greedy2 for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 7, 2, 6" is: 2
GasStation FindStart_BruteForce for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 7, 2, 6" is: 2
GasStation FindStart_Greedy for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 2, 6" is: 5
GasStation FindStart_Greedy2 for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 2, 6" is: 5
GasStation FindStart_BruteForce for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 2, 6" is: 5
GasStation FindStart_Greedy for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 7, 6" is: -1
GasStation FindStart_Greedy2 for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 7, 6" is: -1
GasStation FindStart_BruteForce for "7, 2, 7, 1, 4, 6, 5" and "5, 5, 1, 3, 9, 7, 6" is: -1
GasStation2 FindStart_Greedy for gas="20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25", dist="300, 400, 1000, 300, 300, 600, 400, 1100, 400, 1000, 200, 300, 300", milePerGalon="20": 8
GasStation2 FindStart_BruteForce for gas="20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25", dist="300, 400, 1000, 300, 300, 600, 400, 1100, 400, 1000, 200, 300, 300", milePerGalon="20": 8
*/
#endif