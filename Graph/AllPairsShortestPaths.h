#ifndef ALL_PAIRS_SHORTEST_PATHS_H
#define ALL_PAIRS_SHORTEST_PATHS_H
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
http://www.geeksforgeeks.org/dynamic-programming-set-16-floyd-warshall-algorithm/
http://www.geeksforgeeks.org/johnsons-algorithm/
Floyd Warshall's algorithm:
It's a way to find the shortest paths between all pairs of vertices in weighted graph with positive or negative weights (but with no negative cycles).
Floyd Warshall: O(V^3) time

Johnson's algorithm: 
It's a way to find the shortest paths between all pairs of vertices in a sparse, edge weighted, directed graph.
It allows some of the edge weights to be negative numbers, but no negative-weight cycles may exist.
It works by using the Bellman-Ford algorithm to compute a transformation of the input graph that removes all negative weights, allowing Dijkstra's algorithm to be used on the transformed graph.

add a dummy vertex and run Bellman Ford single source shortest path algorithm to transform to a graph with all non-negative weight edges
the dummy vertex is the dummy source with 0-weighted edges to all exiting vertices
the shortest path from Bellman Ford for the dummy source to each existing vertex i is h[i]
then, the shortest distance from the dummy source to a vertex v must be <= the shortest distance from the dummy source to a vertex u plus the edge from u to v, w(u, v)
h[v] <= h[u] + w(u, v)
new weight of vertex u to vertex v, w(u, v), is: w(u, v) + h[u] - h[v], which guarantees >= 0
Johnson: O(V^2logV + V*E) = For Each Vertex O(V) * Fast Dijkstra O(VlogV) + Bellman Ford O(V*E) time

The time complexity of Johnson's algorithm becomes same as Floyd Warshall when the graph is complete (For a complete graph E = O(V^2).)
But for sparse graphs, Johnson's algorithm performs much better than Floyd Warshall.
*/
class AllPairsShortestPaths
{
public:
	AllPairsShortestPaths(){}
	~AllPairsShortestPaths(){}

	std::vector<std::vector<int>> FloydWarshall_DP2D_DAGAdjacencyMatrix(const std::vector<std::vector<int> > & DAGadjMatrix)//only DAG with negative weight edges is meaningful to find shortest path
	{
		//note that to run Floyd Warshall, the adjMatrix must present 0 for dist between same vertices, and infinity for dist between disconnected vertices
		int N = DAGadjMatrix.size();
		std::vector<std::vector<int> > dp(DAGadjMatrix);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i != j && dp[i][j] == 0)
					dp[i][j] = INT_MAX;
			}
		}

		for (int middle = 0; middle < N; ++middle)
		{
			for (int source = 0; source < N; ++source)
			{
				for (int target = 0; target < N; ++target)
				{
					if (source != target)
					{
						if (dp[source][middle] != INT_MAX && dp[middle][target] != INT_MAX &&
							dp[source][middle] + dp[middle][target] < dp[source][target])
						{
							dp[source][target] = dp[source][middle] + dp[middle][target];
						}
					}
				}
			}
		}
		Debug::Print2D<int>()(DAGadjMatrix, false);
		std::cout << "AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:" << std::endl;
		Debug::Print2D<int>()(dp, false);
		return dp;
	}
	std::vector<std::vector<int>> FloydWarshall_DP2D_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		//note that to run Floyd Warshall, the adjMatrix must present 0 for dist between same vertices, and infinity for dist between disconnected vertices
		int N = adjMatrix.size();
		std::vector<std::vector<int> > dp(adjMatrix);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i != j && dp[i][j] == 0)
					dp[i][j] = INT_MAX;
			}
		}

		for (int middle = 0; middle < N; ++middle)
		{
			for (int source = 0; source < N; ++source)
			{
				for (int target = 0; target < N; ++target)
				{
					if (source != target)
					{
						if (dp[source][middle] != INT_MAX && dp[middle][target] != INT_MAX &&
							dp[source][middle] + dp[middle][target] < dp[source][target])
						{
							dp[source][target] = dp[source][middle] + dp[middle][target];
						}
					}
				}
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "AllPairsShortestPaths FloydWarshall_DP2D_UndirectedAdjacencyMatrix:" << std::endl;
		Debug::Print2D<int>()(dp, false);
		return dp;
	}

	struct GreaterComp
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first > b.first;
		}
	};
	std::vector<std::vector<int>> Johnson_DAGAdjacencyMatrix(const std::vector<std::vector<int> > & DAGadjMatrix)//only DAG with negative weight edges is meaningful to find shortest path
	{
		Debug::Print2D<int>()(DAGadjMatrix, false);
		int N = DAGadjMatrix.size();

		//1. add a dummy vertex (with index N in the adjMatrix) as the dummy source with 0-weighted edges to all existing vertices
		//, then run BellmanFord to find dist[] to transform negative weighted edges
		//1.1 add a dummy vertex
		std::vector<std::vector<int> > DAGadjMatrix2(N + 1, std::vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i == j)
					DAGadjMatrix2[i][j] = 0;//self-pointed edges should be 0 for BellmanFord Algo
				else if (DAGadjMatrix[i][j] == 0)
					DAGadjMatrix2[i][j] = INT_MAX;//disconnected edges should be infinity for BellmanFord Algo
				else
					DAGadjMatrix2[i][j] = DAGadjMatrix[i][j];
			}
		}
		for (int j = 0; j < N + 1; ++j)
			DAGadjMatrix2[N][j] = 0;//dummy vertex has 0-weighted edges to all existing vertices and itself
		for (int i = 0; i < N; ++i)
			DAGadjMatrix2[i][N] = INT_MAX;//all existing vertices have infinity-weighted edges to dummy vertex
		std::cout << "1.1 Add a dummy vertex:" << std::endl; Debug::Print2D<int>()(DAGadjMatrix2, false);
		//1.2 compute dist[]
		//since we have N+1 vertiecs, relax all edges N times
		//a simple shortest path from source to any other vertex can have at most N edges
		std::vector<int> dist(N + 1, 0);//dist[i]: shortest distance from the dummy vertex to i
		for (int relaxCount = 0; relaxCount < N; ++relaxCount)
		{
			for (int i = 0; i < N + 1; ++i)
			{
				for (int j = 0; j < N + 1; ++j)
				{
					if (i != j && DAGadjMatrix2[i][j] != INT_MAX)
					{
						if (dist[i] + DAGadjMatrix2[i][j] < dist[j])
						{
							dist[j] = dist[i] + DAGadjMatrix2[i][j];
						}
					}
				}
			}
		}
		std::cout << "1.2 BellmanFord dist[]: " << Debug::ToStr1D<int>()(dist) << std::endl;
		//1.3 use dist[] to check for negative weight cycles (relax all edges for the (N+1)-th time)
		for (int i = 0; i < N + 1; ++i)
		{
			for (int j = 0; j < N + 1; ++j)
			{
				if (i != j && DAGadjMatrix2[i][j] != INT_MAX)
				{
					if (dist[i] + DAGadjMatrix2[i][j] < dist[j])
					{
						std::cout << "AllPairsShortestPaths JohnsonDAGAdjacencyMatrix Found negative weight cycle, stop !!!" << std::endl;
						return std::vector<std::vector<int>>();
					}
				}
			}
		}
		//1.4 use dist[] to replace each edge w(u, v) with w(u, v) + dist[u] - dist[v], such that negative weighted edges can be transformed
		for (int i = 0; i < N + 1; ++i)
		{
			for (int j = 0; j < N + 1; ++j)
			{
				if (i != j && DAGadjMatrix2[i][j] != INT_MAX)
				{
					DAGadjMatrix2[i][j] += (dist[i] - dist[j]);
				}
			}
		}
		std::cout << "1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:" << std::endl; Debug::Print2D<int>()(DAGadjMatrix2, false);

		//2. run Fast Dijkstra for dist of each pair of vertices by taking each vertex as source
		std::vector<std::vector<int> > distAdjMatrix(N, std::vector<int>(N, INT_MAX));
		for (int s = 0; s < N; ++s)
		{
			distAdjMatrix[s][s] = 0;
			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, GreaterComp> minHeap;//first: distance from source, second: adjacent vertex
			minHeap.push({ 0, s });
			while (!minHeap.empty())
			{
				std::pair<int, int> p = minHeap.top();
				minHeap.pop();
				int curVertex = p.second;
				for (int i = 0; i < N; ++i)
				{
					if (DAGadjMatrix2[curVertex][i] != INT_MAX && i != curVertex)
					{
						if (distAdjMatrix[s][curVertex] + DAGadjMatrix2[curVertex][i] < distAdjMatrix[s][i])
						{
							distAdjMatrix[s][i] = distAdjMatrix[s][curVertex] + DAGadjMatrix2[curVertex][i];
							minHeap.push({ distAdjMatrix[s][i], i });
						}
					}
				}
			}
		}
		std::cout << "AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: " << std::endl;
		Debug::Print2D<int>()(distAdjMatrix, false);
		return distAdjMatrix;
	}


	std::vector<std::vector<int>> Johnson_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)//undirected graph with negative weight edges is meaningless to find shortest path
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();

		//1. add a dummy vertex (with index N in the adjMatrix) as the dummy source with 0-weighted edges to all existing vertices
		//, then run BellmanFord to find dist[] to transform negative weighted edges
		//1.1 add a dummy vertex
		std::vector<std::vector<int> > adjMatrix2(N + 1, std::vector<int>(N + 1, 0));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i == j)
					adjMatrix2[i][j] = 0;//self-pointed edges should be 0 for BellmanFord Algo
				else if (adjMatrix[i][j] == 0)
					adjMatrix2[i][j] = INT_MAX;//disconnected edges should be infinity for BellmanFord Algo
				else
					adjMatrix2[i][j] = adjMatrix[i][j];
			}
		}
		for (int j = 0; j < N + 1; ++j)
			adjMatrix2[N][j] = 0;//dummy vertex has 0-weighted edges to all existing vertices and itself
		for (int i = 0; i < N; ++i)
			adjMatrix2[i][N] = INT_MAX;//all existing vertices have infinity-weighted edges to dummy vertex
		std::cout << "1.1 Add a dummy vertex:" << std::endl; Debug::Print2D<int>()(adjMatrix2, false);
		//1.2 compute dist[]
		//since we have N+1 vertiecs, relax all edges N times
		//a simple shortest path from source to any other vertex can have at most N edges
		std::vector<int> dist(N + 1, 0);//dist[i]: shortest distance from the dummy vertex to i
		for (int relaxCount = 0; relaxCount < N; ++relaxCount)
		{
			for (int i = 0; i < N + 1; ++i)
			{
				for (int j = 0; j < N + 1; ++j)
				{
					if (i != j && adjMatrix2[i][j] != INT_MAX)
					{
						if (dist[i] + adjMatrix2[i][j] < dist[j])
						{
							dist[j] = dist[i] + adjMatrix2[i][j];
						}
					}
				}
			}
		}
		std::cout << "1.2 BellmanFord dist[]: " << Debug::ToStr1D<int>()(dist) << std::endl;
		//1.3 use dist[] to check for negative weight cycles (relax all edges for the (N+1)-th time)
		for (int i = 0; i < N + 1; ++i)
		{
			for (int j = 0; j < N + 1; ++j)
			{
				if (i != j && adjMatrix2[i][j] != INT_MAX)
				{
					if (dist[i] + adjMatrix2[i][j] < dist[j])
					{
						std::cout << "AllPairsShortestPaths JohnsonUndirectedAdjacencyMatrix Found negative weight cycle, stop !!!" << std::endl;
						return std::vector<std::vector<int>>();
					}
				}
			}
		}
		//1.4 use dist[] to replace each edge w(u, v) with w(u, v) + dist[u] - dist[v], such that negative weighted edges can be transformed
		for (int i = 0; i < N + 1; ++i)
		{
			for (int j = 0; j < N + 1; ++j)
			{
				if (i != j && adjMatrix2[i][j] != INT_MAX)
				{
					adjMatrix2[i][j] += (dist[i] - dist[j]);
				}
			}
		}
		std::cout << "1.4 BellmanFord-Reweighted-Undirected-AdjMatrix-without-negative-edges:" << std::endl; Debug::Print2D<int>()(adjMatrix2, false);

		//2. run Fast Dijkstra for dist of each pair of vertices by taking each vertex as source
		std::vector<std::vector<int> > distAdjMatrix(N, std::vector<int>(N, INT_MAX));
		for (int s = 0; s < N; ++s)
		{
			distAdjMatrix[s][s] = 0;
			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, GreaterComp> minHeap;//first: distance from source, second: adjacent vertex
			minHeap.push({ 0, s });
			while (!minHeap.empty())
			{
				std::pair<int, int> p = minHeap.top();
				minHeap.pop();
				int curVertex = p.second;
				for (int i = 0; i < N; ++i)
				{
					if (adjMatrix2[curVertex][i] != INT_MAX && i != curVertex)
					{
						if (distAdjMatrix[s][curVertex] + adjMatrix2[curVertex][i] < distAdjMatrix[s][i])
						{
							distAdjMatrix[s][i] = distAdjMatrix[s][curVertex] + adjMatrix2[curVertex][i];
							minHeap.push({ distAdjMatrix[s][i], i });
						}
					}
				}
			}
		}
		std::cout << "AllPairsShortestPaths Johnson_UndirectedAdjacencyMatrix for BellmanFord-Reweighted-Undirect-AdjMatrix-without-negative-edges: " << std::endl;
		Debug::Print2D<int>()(distAdjMatrix, false);
		return distAdjMatrix;
	}
};
/*
		          9
		       5----->4
		     ^ ^     ^^
		 14/  2|  7/  |
		 /  9  | /    |
		0----->2    -6|
		 \     | \    |
		  7\ 10| 11\  |
		     v v     v|
		       1----->3
		          15
[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 0, 0, 0, 15, 0, 0
Row#2	= 0, 10, 0, 11, 7, 2
Row#3	= 0, 0, 0, 0, -6, 0
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 9, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, 7, 9, 20, 14, 11
Row#1	= 2147483647, 0, 2147483647, 15, 9, 2147483647
Row#2	= 2147483647, 10, 0, 11, 5, 2
Row#3	= 2147483647, 2147483647, 2147483647, 0, -6, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 9, 0

[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 0, 0, 0, 15, 0, 0
Row#2	= 0, 10, 0, 11, 7, 2
Row#3	= 0, 0, 0, 0, -6, 0
Row#4	= 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 9, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, 7, 9, 2147483647, 2147483647, 14, 2147483647
Row#1	= 2147483647, 0, 2147483647, 15, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 10, 0, 11, 7, 2, 2147483647
Row#3	= 2147483647, 2147483647, 2147483647, 0, -6, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 9, 0, 2147483647
Row#6	= 0, 0, 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: 0, 0, 0, 0, -6, 0, 0
1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 7, 9, 2147483647, 2147483647, 14, 2147483647
Row#1	= 2147483647, 0, 2147483647, 15, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 10, 0, 11, 13, 2, 2147483647
Row#3	= 2147483647, 2147483647, 2147483647, 0, 0, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 15, 0, 2147483647
Row#6	= 0, 0, 0, 0, 6, 0, 0

AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 7, 9, 20, 20, 11
Row#1	= 2147483647, 0, 2147483647, 15, 15, 2147483647
Row#2	= 2147483647, 10, 0, 11, 11, 2
Row#3	= 2147483647, 2147483647, 2147483647, 0, 0, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647
Row#5	= 2147483647, 2147483647, 2147483647, 2147483647, 15, 0

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
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

AllPairsShortestPaths FloydWarshall_DP2D_UndirectedAdjacencyMatrix:
[rY][cX]
Row#0	= 0, 7, 9, 20, 20, 11
Row#1	= 7, 0, 10, 15, 21, 12
Row#2	= 9, 10, 0, 11, 11, 2
Row#3	= 20, 15, 11, 0, 6, 13
Row#4	= 20, 21, 11, 6, 0, 9
Row#5	= 11, 12, 2, 13, 9, 0

[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, 7, 9, 2147483647, 2147483647, 14, 2147483647
Row#1	= 7, 0, 10, 15, 2147483647, 2147483647, 2147483647
Row#2	= 9, 10, 0, 11, 2147483647, 2, 2147483647
Row#3	= 2147483647, 15, 11, 0, 6, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 6, 0, 9, 2147483647
Row#5	= 14, 2147483647, 2, 2147483647, 9, 0, 2147483647
Row#6	= 0, 0, 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: 0, 0, 0, 0, 0, 0, 0
1.4 BellmanFord-Reweighted-Undirected-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 7, 9, 2147483647, 2147483647, 14, 2147483647
Row#1	= 7, 0, 10, 15, 2147483647, 2147483647, 2147483647
Row#2	= 9, 10, 0, 11, 2147483647, 2, 2147483647
Row#3	= 2147483647, 15, 11, 0, 6, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 6, 0, 9, 2147483647
Row#5	= 14, 2147483647, 2, 2147483647, 9, 0, 2147483647
Row#6	= 0, 0, 0, 0, 0, 0, 0

AllPairsShortestPaths Johnson_UndirectedAdjacencyMatrix for BellmanFord-Reweighted-Undirect-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 7, 9, 20, 20, 11
Row#1	= 7, 0, 10, 15, 21, 12
Row#2	= 9, 10, 0, 11, 11, 2
Row#3	= 20, 15, 11, 0, 6, 13
Row#4	= 20, 21, 11, 6, 0, 9
Row#5	= 11, 12, 2, 13, 9, 0

		   4    5    2
		0<---3<---6<---8
		  3/   7/     / ^
		 v 3  v     /     \3
		1<---4   6/    7    10
		 ^      /      ^  /9
		  3\  v       5|v
		2<---5<--------9
		   1       6
		   [rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#3	= 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 6, 2, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#1	= 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 4, 3, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 3, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 3, 1, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#6	= 9, 8, 2147483647, 5, 7, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647
Row#8	= 11, 9, 7, 7, 9, 6, 2, 2147483647, 0, 2147483647, 2147483647
Row#9	= 2147483647, 9, 7, 2147483647, 2147483647, 6, 2147483647, 5, 2147483647, 0, 2147483647
Row#10	= 14, 12, 10, 10, 12, 9, 5, 14, 3, 9, 0

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#3	= 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 6, 2, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 6, 0, 5, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#1	= 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 4, 3, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 3, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 3, 1, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#6	= 2147483647, 2147483647, 2147483647, 5, 7, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 6, 2, 2147483647, 0, 2147483647, 2147483647, 2147483647
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 6, 2147483647, 5, 2147483647, 0, 2147483647, 2147483647
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 9, 0, 2147483647
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#1	= 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 4, 3, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 3, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 3, 1, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#6	= 2147483647, 2147483647, 2147483647, 5, 7, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647
Row#8	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 6, 2, 2147483647, 0, 2147483647, 2147483647, 2147483647
Row#9	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 6, 2147483647, 5, 2147483647, 0, 2147483647, 2147483647
Row#10	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 3, 9, 0, 2147483647
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#1	= 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 4, 3, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 3, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#5	= 2147483647, 3, 1, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#6	= 9, 8, 2147483647, 5, 7, 2147483647, 0, 2147483647, 2147483647, 2147483647, 2147483647
Row#7	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 0, 2147483647, 2147483647, 2147483647
Row#8	= 11, 9, 7, 7, 9, 6, 2, 2147483647, 0, 2147483647, 2147483647
Row#9	= 2147483647, 9, 7, 2147483647, 2147483647, 6, 2147483647, 5, 2147483647, 0, 2147483647
Row#10	= 14, 12, 10, 10, 12, 9, 5, 14, 3, 9, 0

		    -5
		0--------->1
		|  \       |
		|3    \2   |4
		v        v v
		3<---------2
		     1
			 [rY][cX]
Row#0	= 0, -5, 2, 3
Row#1	= 0, 0, 4, 0
Row#2	= 0, 0, 0, 1
Row#3	= 0, 0, 0, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, -5, -1, 0
Row#1	= 2147483647, 0, 4, 5
Row#2	= 2147483647, 2147483647, 0, 1
Row#3	= 2147483647, 2147483647, 2147483647, 0

[rY][cX]
Row#0	= 0, -5, 2, 3
Row#1	= 0, 0, 4, 0
Row#2	= 0, 0, 0, 1
Row#3	= 0, 0, 0, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, -5, 2, 3, 2147483647
Row#1	= 2147483647, 0, 4, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 1, 2147483647
Row#3	= 2147483647, 2147483647, 2147483647, 0, 2147483647
Row#4	= 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: 0, -5, -1, 0, 0
1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 0, 3, 3, 2147483647
Row#1	= 2147483647, 0, 0, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 0, 0, 2147483647
Row#3	= 2147483647, 2147483647, 2147483647, 0, 2147483647
Row#4	= 0, 5, 1, 0, 0

AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 0, 0, 0
Row#1	= 2147483647, 0, 0, 0
Row#2	= 2147483647, 2147483647, 0, 0
Row#3	= 2147483647, 2147483647, 2147483647, 0

		      2
		3-------->2
		^ ^  -3/ ^|
		|4  \/ /  |-7
		|  / /\6  |
		|v /5   \ v
		1<--------0
		      3
			  [rY][cX]
Row#0	= 0, 3, 0, 6
Row#1	= 0, 0, 5, 4
Row#2	= -7, -3, 0, 0
Row#3	= 0, 0, 2, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, 3, 8, 6
Row#1	= -2, 0, 5, 4
Row#2	= -7, -4, 0, -1
Row#3	= -5, -2, 2, 0

[rY][cX]
Row#0	= 0, 3, 0, 6
Row#1	= 0, 0, 5, 4
Row#2	= -7, -3, 0, 0
Row#3	= 0, 0, 2, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, 3, 2147483647, 6, 2147483647
Row#1	= 2147483647, 0, 5, 4, 2147483647
Row#2	= -7, -3, 0, 2147483647, 2147483647
Row#3	= 2147483647, 2147483647, 2, 0, 2147483647
Row#4	= 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: -7, -4, 0, -1, 0
1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 0, 2147483647, 0, 2147483647
Row#1	= 2147483647, 0, 1, 1, 2147483647
Row#2	= 0, 1, 0, 2147483647, 2147483647
Row#3	= 2147483647, 2147483647, 1, 0, 2147483647
Row#4	= 7, 4, 0, 1, 0

AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 0, 1, 0
Row#1	= 1, 0, 1, 1
Row#2	= 0, 0, 0, 0
Row#3	= 1, 1, 1, 0

		-----------------
		|       8       |
		|   3       4   v
		0------>3<------4
		|^    7/|      ^
	  -4|  \ /  |1   /-5
		|  / \  |  /
		vv    2\v/
		1------>2
		    6
			[rY][cX]
Row#0	= 0, -4, 0, 3, 8
Row#1	= 0, 0, 6, 0, 0
Row#2	= 2, 0, 0, 0, -5
Row#3	= 0, 7, 1, 0, 0
Row#4	= 0, 0, 0, 4, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, -4, 2, 1, -3
Row#1	= 8, 0, 6, 5, 1
Row#2	= 2, -2, 0, -1, -5
Row#3	= 3, -1, 1, 0, -4
Row#4	= 7, 3, 5, 4, 0

[rY][cX]
Row#0	= 0, -4, 0, 3, 8
Row#1	= 0, 0, 6, 0, 0
Row#2	= 2, 0, 0, 0, -5
Row#3	= 0, 7, 1, 0, 0
Row#4	= 0, 0, 0, 4, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, -4, 2147483647, 3, 8, 2147483647
Row#1	= 2147483647, 0, 6, 2147483647, 2147483647, 2147483647
Row#2	= 2, 2147483647, 0, 2147483647, -5, 2147483647
Row#3	= 2147483647, 7, 1, 0, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 4, 0, 2147483647
Row#5	= 0, 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: 0, -4, 0, -1, -5, 0
1.4 BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges:
[rY][cX]
Row#0	= 0, 0, 2147483647, 4, 13, 2147483647
Row#1	= 2147483647, 0, 2, 2147483647, 2147483647, 2147483647
Row#2	= 2, 2147483647, 0, 2147483647, 0, 2147483647
Row#3	= 2147483647, 10, 0, 0, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 0, 0, 2147483647
Row#5	= 0, 4, 0, 1, 5, 0

AllPairsShortestPaths Johnson_DAGAdjacencyMatrix for BellmanFord-Reweighted-DAG-AdjMatrix-without-negative-edges: 
[rY][cX]
Row#0	= 0, 0, 2, 2, 2
Row#1	= 4, 0, 2, 2, 2
Row#2	= 2, 2, 0, 0, 0
Row#3	= 2, 2, 0, 0, 0
Row#4	= 2, 2, 0, 0, 0

		-----------------
		|       8       |
		|   3       -4  v
		0------>3<------4
		|^    7/|      ^
	  -4|  \ /  |-1  /-5
		|  / \  |  /
		vv    2\v/
		1------>2
		    6
			[rY][cX]
Row#0	= 0, -4, 0, 3, 8
Row#1	= 0, 0, 6, 0, 0
Row#2	= 2, 0, 0, 0, -5
Row#3	= 0, 7, -1, 0, 0
Row#4	= 0, 0, 0, -4, 0

AllPairsShortestPaths FloydWarshall_DP2D_DAGAdjacencyMatrix:
[rY][cX]
Row#0	= 0, -10, -8, -7, -3
Row#1	= -2, 0, -4, -3, 1
Row#2	= -8, -12, 0, -9, -5
Row#3	= -9, -13, -11, 0, -6
Row#4	= -3, -7, -5, -4, 0

[rY][cX]
Row#0	= 0, -4, 0, 3, 8
Row#1	= 0, 0, 6, 0, 0
Row#2	= 2, 0, 0, 0, -5
Row#3	= 0, 7, -1, 0, 0
Row#4	= 0, 0, 0, -4, 0

1.1 Add a dummy vertex:
[rY][cX]
Row#0	= 0, -4, 2147483647, 3, 8, 2147483647
Row#1	= 2147483647, 0, 6, 2147483647, 2147483647, 2147483647
Row#2	= 2, 2147483647, 0, 2147483647, -5, 2147483647
Row#3	= 2147483647, 7, -1, 0, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, -4, 0, 2147483647
Row#5	= 0, 0, 0, 0, 0, 0

1.2 BellmanFord dist[]: -18, -13, -21, -29, -25, 0
AllPairsShortestPaths JohnsonDAGAdjacencyMatrix Found negative weight cycle, stop !!!
*/
#endif