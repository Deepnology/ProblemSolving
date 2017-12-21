#ifndef MIN_COST_CONNECT_ROPES_H
#define MIN_COST_CONNECT_ROPES_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/connect-n-ropes-minimum-cost/
There are given n ropes of different lengths, we need to connect these ropes into one rope. 
The cost to connect two ropes is equal to sum of their lengths. 
We need to connect the ropes with minimum cost.

The lengths of the ropes which are picked first are included more than once in total cost.
The idea is to connect smallest 2 ropes first and recur for remaining ropes.

For example: 2, 3, 4, 6
1. connect 2 and 3 to 5, with cost 5
2. connect 4 and 5 to 9, with cost 9
3. connect 6 and 9 to 15, with cost 15
=> total cost = 5 + 9 + 15 = 29

MinHeap: O(nlogn) time, O(n) space
*/
class MinCostConnectRopes
{
public:
	MinCostConnectRopes(){}
	~MinCostConnectRopes(){}

	int MinHeap(const std::vector<int> & A)
	{
		std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap(A.begin(), A.end());
		int sum = 0;
		while (minHeap.size() > 1)
		{
			int first = minHeap.top();
			minHeap.pop();
			int second = minHeap.top();
			minHeap.pop();

			sum += first + second;
			minHeap.push(first + second);
		}

		std::cout << "MinCostConnectRopes MinHeap for \"" << Debug::ToStr1D<int>()(A) << "\": " << sum << ". left in heap: " << minHeap.top() << std::endl;
		return sum;
	}

};
/*
MinCostConnectRopes MinHeap for "4, 3, 2, 6": 29. left in heap: 15
MinCostConnectRopes MinHeap for "4, 3, 2, 6, 5, 9, 7, 8, 1": 135. left in heap: 45
*/
#endif