#ifndef IS_ARBITRAGE_EXIST_H
#define IS_ARBITRAGE_EXIST_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <limits>
#include "Debug.h"
/*
Elements of programming interview, Graph: Test if arbitrage is possible
Design an efficient algorithm to determine whether there exists an arbitrage--a way to start with a single unit of some commodity C and convert it back to more than one unit of C through a sequence of exchanges.

Solution:
Define a weighted directed graph G = (V, E = V x V), where V corresponds to the set of commodities.
The weight w(e) of edge e = (u, v) is the amount of commodity v we can buy with one unit of commodity u.
Observe that an arbitrage exists if and only if there exists a cycle in G whose edge weights multiply out to more than 1.

Create a new graph G' = (V, E) with weight function w' = -log(w(e)).
Since log(a*b) = loga + logb, there exists a cycle in G whose edge weights multiply out to more than 1 if and only if
there exists a cycle in G' whose edge weights sum up to less than log1 = 0.
(This property is true for logarithms to any base, so if its more efficient for example to use base-e, we can do so.)

The Bellman-Ford algorithm detects negative-weight cycles.
Usually, finding a negative-weight cycle is done by adding a dummy vertex s with 0-weight edges to each vertex in the given graph and running the Bellman-Ford single-source shortest path algorithm from s.
However, for the arbitrage problem, the graph is complete.
Hence, we can run Bellman-Ford algorithm from any single vertex, and get the right result.

BellmanFord: O(V*E) = O(n*n^2) = O(n^3) time
*/
class IsArbitrageExist
{
public:
	IsArbitrageExist(){}
	~IsArbitrageExist(){}

	bool BellmanFord_ExistNegativeWeightCycle(std::vector<std::vector<double> > & DAGadjMatrix)
	{
		Debug::Print2D<double>()(DAGadjMatrix, false);
		//1. transform the DAG
		int N = DAGadjMatrix.size();
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				DAGadjMatrix[i][j] = -log10(DAGadjMatrix[i][j]);
			}
		}
		Debug::Print2D<double>()(DAGadjMatrix, false);

		//2. run BellmanFord to check to find shortest dist[] from an arbirary vertex
		//then use dist[] to check for negative weight cycle
		bool res = false;
		bool hasUpdated = false;
		std::vector<double> dist(N, std::numeric_limits<double>::max());
		dist[0] = 0.0;//choose an arbitrary vertex as source
		for (int relaxCount = 0; relaxCount < N - 1; ++relaxCount)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (dist[i] != std::numeric_limits<double>::max() && dist[i] + DAGadjMatrix[i][j] < dist[j])
					{
						hasUpdated = true;
						dist[j] = dist[i] + DAGadjMatrix[i][j];
					}
				}
			}
		}
		if (hasUpdated)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (dist[i] != std::numeric_limits<double>::max() && dist[i] + DAGadjMatrix[i][j] < dist[j])
					{
						res = true;
					}
				}
			}
		}

		std::cout << Debug::ToStr1D<double>()(dist) << std::endl;
		std::cout << "IsArbitrageExist BellmanFord_ExistNegativeWeightCycle: " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 1, 0.8123, 0.6404, 78.125, 0.9784, 0.9924, 0.9465
Row#1	= 1.2275, 1, 0.786, 96.55, 1.201, 1.2182, 1.1616
Row#2	= 1.5617, 1.2724, 1, 122.83, 1.528, 1.5498, 1.4778
Row#3	= 0.0128, 0.0104, 0.0081, 1, 1.2442, 0.0126, 0.012
Row#4	= 1.0219, 0.8327, 0.6546, 80.39, 1, 1.0142, 0.9672
Row#5	= 1.0076, 0.8206, 0.6453, 79.26, 0.9859, 1, 0.9535
Row#6	= 1.0567, 0.8609, 0.6767, 83.12, 1.0339, 1.0487, 1

[rY][cX]
Row#0	= -0, 0.0902835, 0.193549, -1.89279, 0.00948356, 0.00331324, 0.0238794
Row#1	= -0.0890215, -0, 0.104577, -1.98475, -0.079543, -0.0857186, -0.0650566
Row#2	= -0.193598, -0.104624, -0, -2.0893, -0.184123, -0.190276, -0.169616
Row#3	= 1.89279, 1.98297, 2.09151, -0, -0.0948902, 1.89963, 1.92082
Row#4	= -0.0094084, 0.0795114, 0.184024, -1.9052, -0, -0.00612361, 0.0144837
Row#5	= -0.00328816, 0.0858685, 0.190238, -1.89905, 0.00616713, -0, 0.0206793
Row#6	= -0.0239517, 0.0650473, 0.169604, -1.91971, -0.0144785, -0.0206513, -0

-12.001, -11.912, -11.8075, -13.8967, -11.9915, -11.9977, -11.977
IsArbitrageExist BellmanFord_ExistNegativeWeightCycle: 1
*/
#endif