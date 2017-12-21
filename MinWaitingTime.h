#ifndef MIN_WAITING_TIME_H
#define MIN_WAITING_TIME_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Implement a schedule which minimizes waiting time
A database has to respond to n simultaneous client SQL queries.
The service time required for Query i, where 1 <= i <= n, equals ti milliseconds and is known in advance.
The query lookups are processed by the database one at a time, but can be done in any order.
													  n
It is natural to minimize the total waiting time Sigma    Ti, where Ti is the time at which processing for Query i begins.
													  i=1
Given n queries, compute an order in which to process queries that minimizes the total waiting time.

O(nlogn) time, O(1) space
*/
class MinWaitingTime
{
public:
	MinWaitingTime(){}
	~MinWaitingTime(){}

	int Schedule(std::vector<int> & serviceTime)
	{
		std::string before = Debug::ToStr1D<int>()(serviceTime);
		int N = serviceTime.size();
		std::sort(serviceTime.begin(), serviceTime.end(), std::less<int>());
		std::cout << Debug::ToStr1D<int>()(serviceTime) << std::endl;

		int sumWaiting = 0;
		for (int i = 0; i < N; ++i)
		{
			sumWaiting += serviceTime[i] * (N - (i + 1));//accumulate (each service time * remaining service count)
		}

		std::cout << "MinWaitingTime Schedule for \"" << before << "\": " << sumWaiting << std::endl;
		return sumWaiting;
	}
};
/*
2, 5, 6, 9, 9, 30, 32, 35, 49, 50, 52, 58, 62, 65, 68, 72, 77, 84, 88, 93
MinWaitingTime Schedule for "84, 9, 77, 68, 50, 88, 9, 62, 49, 32, 5, 30, 2, 35, 52, 58, 72, 6, 93, 65": 5675
*/
#endif