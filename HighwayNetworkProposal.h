#ifndef HIGHWAY_NETWORK_PROPOSAL_H
#define HIGHWAY_NETWORK_PROPOSAL_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <limits>
#include "Debug.h"
/*
Elements of programming interview, Graph: Road network
Given an existing highway network sections (specified as a list of distances between pairs of cities) and a proposal highway network sections (also specified as a list of distances between pairs of cities)
, two target cities, and the total count of cities, return a proposal section which minimizes the shortest distance between the two target cities.
All sections, existing and proposed, allow for bi-directional traffic.

Floyd Warshall: O(V^3) time
*/
class HighwayNetworkProposal
{
public:
	HighwayNetworkProposal(){}
	~HighwayNetworkProposal(){}

	typedef std::pair<std::pair<int, int>, double> Section;//first.first: vertex1, first.second: vertex2, second: distance
	
	Section ShortestPath(const std::vector<Section> & Highway, const std::vector<Section> & Proposal, int a, int b, int N)
	{
		//1. construct the undirected graph from existing highway newtwork
		std::vector<std::vector<double> > adjMatrix(N, std::vector<double>(N, std::numeric_limits<double>::max()));
		for (int i = 0; i < N; ++i)
			adjMatrix[i][i] = 0;
		for (const auto & p : Highway)
		{
			adjMatrix[p.first.first][p.first.second] = p.second;
			adjMatrix[p.first.second][p.first.first] = p.second;
		}

		//2. perform Floyd Warshall to compute all pairs shortest paths from the undirected graph
		//note that to run Floyd Warshall, the adjMatrix must present 0 for dist between same vertices, and infinity for dist between disconnected vertices
		std::vector<std::vector<double> > adjMatrix2 = this->FloydWarshall(adjMatrix);

		//3. examine each proposal section for shortest path between vertex a and vertex b
		//for each proposal section between x and y, need to check 2 possible paths: a->x->y->b and a->y->x->b
		double minDist = adjMatrix2[a][b];
		Section bestProposal = { { -1, -1 }, 0.0 };
		for (const auto & p : Proposal)
		{
			//check the path a->p.first.first->p.first.second->b
			if (adjMatrix2[a][p.first.first] != std::numeric_limits<double>::max() && adjMatrix2[p.first.second][b] != std::numeric_limits<double>::max() &&
				adjMatrix2[a][p.first.first] + p.second + adjMatrix2[p.first.second][b] < minDist)
			{
				minDist = adjMatrix2[a][p.first.first] + p.second + adjMatrix2[p.first.second][b];
				bestProposal = p;
			}

			//check the path a->p.first.second->p.first.first->b
			if (adjMatrix2[a][p.first.second] != std::numeric_limits<double>::max() && adjMatrix2[p.first.first][b] != std::numeric_limits<double>::max() &&
				adjMatrix2[a][p.first.second] + p.second + adjMatrix2[p.first.first][b] < minDist)
			{
				minDist = adjMatrix2[a][p.first.second] + p.second + adjMatrix2[p.first.first][b];
				bestProposal = p;
			}
		}

		Debug::Print2D<double>()(adjMatrix, false);
		Debug::Print2D<double>()(adjMatrix2, false);
		std::cout << "HighwayNetworkProposal ShortestPath for Highway=\"" << Debug::ToStr1D<int, double>()(Highway) << "\", Proposal=\"" << Debug::ToStr1D<int, double>()(Proposal) << "\", between=[" << a << "," << b << "], Vertices=\"" << N << "\": [(" << bestProposal.first.first << "," << bestProposal.first.second << "), " << bestProposal.second << "], minDist: " << minDist << std::endl;
		return bestProposal;
	}
private:
	std::vector<std::vector<double> > FloydWarshall(const std::vector<std::vector<double> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::vector<double> > dp(adjMatrix);

		for (int middle = 0; middle < N; ++middle)
		{
			for (int source = 0; source < N; ++source)
			{
				for (int target = 0; target < N; ++target)
				{
					if (source != target)
					{
						if (dp[source][middle] != std::numeric_limits<double>::max() && dp[middle][target] != std::numeric_limits<double>::max() &&
							dp[source][middle] + dp[middle][target] < dp[source][target])
						{
							dp[source][target] = dp[source][middle] + dp[middle][target];
						}
					}
				}
			}
		}

		return dp;
	}
};
/*
		           9
		       5------4
		     / |      |
		 11/  2|      |
		 /  9  |      |
		0------2     6|
		 \     | \    |
		  7\ 10| 11\  |
		     \ |     \|
		       1------3
		          15

[rY][cX]
Row#0	= 0, 7, 9, 1.79769e+308, 1.79769e+308, 11
Row#1	= 7, 0, 10, 15, 1.79769e+308, 1.79769e+308
Row#2	= 9, 10, 0, 11, 1.79769e+308, 2
Row#3	= 1.79769e+308, 15, 11, 0, 6, 1.79769e+308
Row#4	= 1.79769e+308, 1.79769e+308, 1.79769e+308, 6, 0, 9
Row#5	= 11, 1.79769e+308, 2, 1.79769e+308, 9, 0

[rY][cX]
Row#0	= 0, 7, 9, 20, 20, 11
Row#1	= 7, 0, 10, 15, 21, 12
Row#2	= 9, 10, 0, 11, 11, 2
Row#3	= 20, 15, 11, 0, 6, 13
Row#4	= 20, 21, 11, 6, 0, 9
Row#5	= 11, 12, 2, 13, 9, 0

HighwayNetworkProposal ShortestPath for Highway="[(0,1),7], [(0,2),9], [(0,5),11], [(1,2),10], [(1,3),15], [(2,3),11], [(2,5),2], [(3,4),6], [(4,5),9]", Proposal="[(3,5),2], [(0,4),21], [(2,4),12], [(1,4),11], [(0,3),11], [(1,5),11]", between=[0,4], Vertices="6": [(0,3), 11], minDist: 17
*/
#endif