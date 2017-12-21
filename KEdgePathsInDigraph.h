#ifndef K_EDGE_PATHS_IN_DIGRAPH_H
#define K_EDGE_PATHS_IN_DIGRAPH_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/count-possible-paths-source-destination-exactly-k-edges/
http://www.geeksforgeeks.org/shortest-path-exactly-k-edges-directed-weighted-graph/
1. Given a directed graph and two vertices 'u' and 'v' in it, count all possible walks from 'u' to 'v' with exactly k edges on the walk.

2. Given a directed "weighted" graph and two vertices 'u' and 'v' in it, find shortest path from 'u' to 'v' with exactly k edges on the path.

DFS: O(V^k) time in worst case, where V is the number of vertices
DP3D: O(V^3 * k) time, O(V^2 * k) space
*/
class KEdgePathsInDigraph
{
public:
	KEdgePathsInDigraph(){}
	~KEdgePathsInDigraph(){}

	int FindAll_DFS_DirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int src, int dst, int k)
	{
		int N = adjMatrix.size();
		int count = 0;
		int minWeights = INT_MAX;//the path with min weights (shortest path)
		std::vector<std::pair<int, int> > path;//DFS path of edge-pairs
		std::vector<std::pair<int, int> > shortestPath;
		std::vector<std::vector<std::pair<int, int> > > res;//all paths with k-edges
		this->findAll_DFS_DirectedAdjacencyMatrix(adjMatrix, src, dst, k, count, path, res, 0, minWeights, shortestPath);
		Debug::Print2D<int>()(adjMatrix, false);
		Debug::Print2D<int>()(res, false);
		std::cout << "KEdgePathsInDigraph FindAll_DFS for src=\"" << src << "\", dst=\"" << dst << "\", k=\"" << k << "\", count: " << count << ", minWeights: " << minWeights << ", shortestPath: " << Debug::ToStr1D<int>()(shortestPath) << std::endl;
		return count;
	}
private:
	void findAll_DFS_DirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int cur, int dst, int k
		, int & count, std::vector<std::pair<int, int> > & path, std::vector<std::vector<std::pair<int, int> > > & res
		, int curWeights, int & minWeights, std::vector<std::pair<int, int> > & shortestPath)
	{
		if (k == 0)
		{
			if (cur == dst)
			{
				++count;
				res.push_back(path);
				if (curWeights < minWeights)
				{
					minWeights = curWeights;
					shortestPath = path;
				}
				return;//reaches dst when k = 0
			}
			else
				return;//can't reach dst when k = 0
		}
		if (cur == dst)
			return;//reaches dst, but k > 0

		int N = adjMatrix.size();
		//enumerate all adj vertices (edges)
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[cur][i] != 0)
			{
				path.push_back(std::make_pair(cur, i));//push current edge
				curWeights += adjMatrix[cur][i];
				this->findAll_DFS_DirectedAdjacencyMatrix(adjMatrix, i, dst, k - 1, count, path, res, curWeights, minWeights, shortestPath);
				curWeights -= adjMatrix[cur][i];
				path.pop_back();
			}
		}
	}

public:
	int CountAll_DP3D_DirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int src, int dst, int k)
	{
		int N = adjMatrix.size();
		std::vector<std::vector<std::vector<int> > > dp(N, std::vector<std::vector<int> >(N, std::vector<int>(k + 1)));

		for (int edge = 0; edge <= k; ++edge)
		{
			for (int i = 0; i < N; ++i)//from
			{
				for (int j = 0; j < N; ++j)//to
				{
					dp[i][j][edge] = 0;

					//base cases init
					if (edge == 0 && i == j)
						dp[i][j][edge] = 1;//reaches self when k == 0
					if (edge == 1 && adjMatrix[i][j] != 0)
						dp[i][j][edge] = 1;//can reach adj vertex when k = 1

					if (edge > 1)
					{
						for (int adj = 0; adj < N; ++adj)//enumerate all adj vertices of vertex i
						{
							if (adjMatrix[i][adj] != 0)//since there is an edge "i->adj"
								dp[i][j][edge] += dp[adj][j][edge - 1];//accumulate the count of "adj->j with 1 less edge"
						}
					}
				}
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		Debug::Print3D<int>()(dp, false);
		std::cout << "KEdgePathsInDigraph CountAll_DP3D for src=\"" << src << "\", dst=\"" << dst << "\", k=\"" << k << "\": " << dp[src][dst][k] << std::endl;
		return dp[src][dst][k];
	}

	int CountShortestPathWeight_DP3D_DirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int src, int dst, int k)
	{
		int N = adjMatrix.size();
		std::vector<std::vector<std::vector<int> > > dp(N, std::vector<std::vector<int> >(N, std::vector<int>(k + 1)));

		for (int edge = 0; edge <= k; ++edge)
		{
			for (int i = 0; i < N; ++i)//from
			{
				for (int j = 0; j < N; ++j)//to
				{
					dp[i][j][edge] = INT_MAX;

					//base cases init
					if (edge == 0 && i == j)
						dp[i][j][edge] = 0;//reaches self when k = 0
					if (edge == 1 && adjMatrix[i][j] != 0)
						dp[i][j][edge] = adjMatrix[i][j];//can reach adj vertex when k = 1

					if (edge > 1)
					{
						for (int adj = 0; adj < N; ++adj)//enumerate all adj vertices of vertex i
						{
							if (adjMatrix[i][adj] != 0 && dp[adj][j][edge - 1] != INT_MAX)//there is an edge "i->adj" and "adj->j with 1 less edge" has a valid weight
							{
								int weight = dp[adj][j][edge - 1] + adjMatrix[i][adj];
								if (weight < dp[i][j][edge])
									dp[i][j][edge] = weight;
							}
						}
					}
				}
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		//Debug::Print3D<int>()(dp, false);
		std::cout << "KEdgePathsInDigraph CountShortestPathWeight_DP3D for src=\"" << src << "\", dst=\"" << dst << "\", k=\"" << k << "\": " << dp[src][dst][k] << std::endl;
		return dp[src][dst][k];
	}
};
/*
		1-->4-->6
		^ \ | / |
		|  vvv  v
		0-->3<--8
		|  ^^^  ^
		v / | \ |
		2-->5-->7
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 1, 1, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 1, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 1, 0, 0, 0, 1, 0
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#7	= 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 0, 0

[rY][cX]
Row#0	= [0,1], [1,4], [4,6], [6,3]
Row#1	= [0,2], [2,5], [5,7], [7,3]

KEdgePathsInDigraph FindAll_DFS for src="0", dst="3", k="4", count: 2, minWeights: 4, shortestPath: [0,1], [1,4], [4,6], [6,3]
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 1, 1, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 1, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 1, 0, 0, 0, 1, 0
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#7	= 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 0, 0

[rY][cX][dZ]
Row#0	= 1,0,0,0,0.	0,1,0,0,0.	0,1,0,0,0.	0,1,2,2,2.	0,0,1,0,0.	0,0,1,0,0.	0,0,0,1,0.	0,0,0,1,0.	0,0,0,0,2.
Row#1	= 0,0,0,0,0.	1,0,0,0,0.	0,0,0,0,0.	0,1,1,1,1.	0,1,0,0,0.	0,0,0,0,0.	0,0,1,0,0.	0,0,0,0,0.	0,0,0,1,0.
Row#2	= 0,0,0,0,0.	0,0,0,0,0.	1,0,0,0,0.	0,1,1,1,1.	0,0,0,0,0.	0,1,0,0,0.	0,0,0,0,0.	0,0,1,0,0.	0,0,0,1,0.
Row#3	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	1,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.
Row#4	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,1,1,1,0.	1,0,0,0,0.	0,0,0,0,0.	0,1,0,0,0.	0,0,0,0,0.	0,0,1,0,0.
Row#5	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,1,1,1,0.	0,0,0,0,0.	1,0,0,0,0.	0,0,0,0,0.	0,1,0,0,0.	0,0,1,0,0.
Row#6	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,1,1,0,0.	0,0,0,0,0.	0,0,0,0,0.	1,0,0,0,0.	0,0,0,0,0.	0,1,0,0,0.
Row#7	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,1,1,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	1,0,0,0,0.	0,1,0,0,0.
Row#8	= 0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,1,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	0,0,0,0,0.	1,0,0,0,0.

KEdgePathsInDigraph CountAll_DP3D for src="0", dst="3", k="4": 2

		1-->4-->6
		| \ | / |
		v  vvv  v
		0-->3-->8
		| / | \ |
		vv  v  vv
		2-->5-->7
[rY][cX]
Row#0	= 0, 0, 4, 7, 0, 0, 0, 0, 0
Row#1	= 5, 0, 0, 8, 2, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 3, 0, 0, 0
Row#3	= 0, 0, 9, 0, 0, 5, 0, 1, 7
Row#4	= 0, 0, 0, 7, 0, 0, 4, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 3, 0
Row#6	= 0, 0, 0, 8, 0, 0, 0, 0, 5
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 6, 0

[rY][cX]
Row#0	= [1,0], [0,3], [3,7]
Row#1	= [1,3], [3,5], [5,7]
Row#2	= [1,3], [3,8], [8,7]
Row#3	= [1,4], [4,3], [3,7]

KEdgePathsInDigraph FindAll_DFS for src="1", dst="7", k="3", count: 4, minWeights: 10, shortestPath: [1,4], [4,3], [3,7]
[rY][cX]
Row#0	= 0, 0, 4, 7, 0, 0, 0, 0, 0
Row#1	= 5, 0, 0, 8, 2, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 3, 0, 0, 0
Row#3	= 0, 0, 9, 0, 0, 5, 0, 1, 7
Row#4	= 0, 0, 0, 7, 0, 0, 4, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 3, 0
Row#6	= 0, 0, 0, 8, 0, 0, 0, 0, 5
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 6, 0

KEdgePathsInDigraph CountShortestPathWeight_DP3D for src="1", dst="7", k="3": 10
*/
#endif