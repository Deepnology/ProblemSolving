#ifndef MIN_CASH_FLOW_H
#define MIN_CASH_FLOW_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/
Given a directed graph where each edge weight represents the money that the source vertex needs to pay the target vertex.
Design an algorithm to minimize the cash flow.
		     1000
		    0---->1
		2000|   /
		    | /5000
		    vv
		    2
		
		    0    1
		3000|   /
		    | /4000
		    vv
		    2

Greedy: O(V^2) time

Leetcode: Optimal Account Balancing
A group of friends went on holiday and sometimes lent each other money.
For example, Alice paid for Bill's lunch for $10.
Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means person x gave person y $z.
Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].
Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.
Note:
A transaction will be given as a tuple (x, y, z). Note that x �� y and z > 0.
Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.
Example 1:
Input:
[[0,1,10], [2,0,5]]
Output:
2
Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.
Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.
Example 2:
Input:
[[0,1,10], [1,0,1], [1,2,5], [2,0,5]]
Output:
1
Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.
Therefore, person #1 only need to give person #0 $4, and all debt is settled.
*/
class MinCashFlow
{
public:
	MinCashFlow(){}
	~MinCashFlow(){}

	std::vector<std::vector<int>> Greedy_DirectedAdjMatrix(const std::vector<std::vector<int>> & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> netAmount(N, 0);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i != j)
					netAmount[i] += (adjMatrix[j][i] - adjMatrix[i][j]);//income - outcome
			}
		}
		std::cout << "NetAmount: " << Debug::ToStr1D<int>()(netAmount) << std::endl;

		std::vector<std::vector<int>> res(N, std::vector<int>(N, 0));
		this->recur(netAmount, res);

		std::cout << "MinCashFlow Greedy_DirectedAdjMatrix for above graph, netAmount: " << Debug::ToStr1D<int>()(netAmount) << ", result adjMatrix:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}
private:
	void recur(std::vector<int> & netAmount, std::vector<std::vector<int>> & res)
	{
		int maxVertex = std::max_element(netAmount.begin(), netAmount.end()) - netAmount.begin();
		int minVertex = std::min_element(netAmount.begin(), netAmount.end()) - netAmount.begin();

		//if both amounts are 0, then all amounts are settled
		if (netAmount[maxVertex] == 0 && netAmount[minVertex] == 0)
			return;

		//minVertex needs to pay min(netAmount[maxVertex], -netAmount[minVertex]) to maxVertex
		//such that at least one of netAmount[maxVertex] and netAmount[minVertex] will become 0 after cancellation
		int minAmount = std::min(netAmount[maxVertex], -netAmount[minVertex]);
		netAmount[maxVertex] -= minAmount;//maxVertex gains minAmount
		netAmount[minVertex] += minAmount;//minVertex pays minAmount

		res[minVertex][maxVertex] = minAmount;//record: minVertex pays minAmount to maxVertex

		this->recur(netAmount, res);
	}

public:
	//Leetcode: Optimal Account Balancing
	int MinTransfers(const std::vector<std::vector<int>> & transactions)
	{
		int maxIdx = 0;
		for (auto & v : transactions)
			maxIdx = std::max(maxIdx, std::max(v[0], v[1]));
		std::vector<int> netAmount(maxIdx + 1, 0);
		for (auto & v : transactions)
		{
			netAmount[v[0]] -= v[2];
			netAmount[v[1]] += v[2];
		}
		int res = recur(netAmount, 0, 0);

		Debug::Print2D<int>()(transactions, false);
		std::cout << "MinCashFlow MinTransfers for the above transactions: " << res << std::endl;
		return res;
	}
	int recur(std::vector<int> & netAmount, int begin, int totalCount)
	{
		int count = INT_MAX;
		int N = netAmount.size();
		while (begin < N && netAmount[begin] == 0)
			++begin;
		for (int i = begin + 1; i < N; ++i)
		{
			if (netAmount[i] == 0) continue;
			if (netAmount[begin] < 0 && netAmount[i] > 0)
			{
				int minAmount = std::min(std::abs(netAmount[begin]), std::abs(netAmount[i]));
				netAmount[begin] += minAmount;
				netAmount[i] -= minAmount;
				count = std::min(count, recur(netAmount, begin, totalCount + 1));
				netAmount[begin] -= minAmount;
				netAmount[i] += minAmount;
			}
			else if (netAmount[begin] > 0 && netAmount[i] < 0)
			{
				int minAmount = std::min(std::abs(netAmount[begin]), std::abs(netAmount[i]));
				netAmount[begin] -= minAmount;
				netAmount[i] += minAmount;
				count = std::min(count, recur(netAmount, begin, totalCount + 1));
				netAmount[begin] += minAmount;
				netAmount[i] -= minAmount;
			}
		}
		return count == INT_MAX ? totalCount : count;
	}
};
/*
		     1000
		    0---->1
		2000|   /
		    | /5000
		    vv
		    2
		
		    0    1
		3000|   /
		    | /4000
		    vv
		    2
[rY][cX]
Row#0	= 0, 1000, 2000
Row#1	= 0, 0, 5000
Row#2	= 0, 0, 0

NetAmount: -3000, -4000, 7000
MinCashFlow Greedy_DirectedAdjMatrix for above graph, netAmount: 0, 0, 0, result adjMatrix:
[rY][cX]
Row#0	= 0, 0, 3000
Row#1	= 0, 0, 4000
Row#2	= 0, 0, 0

[rY][cX]
Row#0	= 0, 1, 10
Row#1	= 1, 0, 1
Row#2	= 1, 2, 5
Row#3	= 2, 0, 5

MinCashFlow MinTransfers for the above transactions: 1
*/
#endif