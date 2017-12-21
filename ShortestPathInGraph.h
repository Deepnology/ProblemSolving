#ifndef SHORTEST_PATH_IN_GRAPH_H
#define SHORTEST_PATH_IN_GRAPH_H
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
Elements of programming interview, Graph: compute a shortest path with fewest edges
°ö¾i»PÁëÁå
http://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
Bellman Ford works for negative weight cycle
If there exists a negative edge in a graph, the shortest path for any two vertices in the graph is meaningful only when the graph is a DAG.
If the graph is not a DAG, the shortest path can always walk the negative edge for unlimited times (negative weight cycle).
Bellman Ford: O(V*E) time

Dijkstra: O(V^2) time
Fast Dijkstra with min heap
http://stanford.edu/~liszt90/acm/notebook.html#file17
AdjacencyMatrix: O(V^2logV) time
AdjacencyList: O(ElogV) time

Definition of "negative weight cycle" in a graph is a cycle v0 -> v1 -> v2 -> ... -> vt -> v0
in which weight(v0,v1) + weight(v1,v2) + ... + weight(vt,v0) < 0
*/
class ShortestPathInGraph
{
public:
	ShortestPathInGraph(){}
	~ShortestPathInGraph(){}

	std::vector<int> BellmanFord_UndirectedAdjacencyMatrix(const std::vector<std::vector<int>> & adjMatrix, int source)//undirected graph with negative weight edge is meaningless to find shortest path
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> dist(N, INT_MAX);
		dist[source] = 0;
		std::vector<std::vector<int>> paths(N, std::vector<int>());

		//relax all edges N - 1 times
		//a simple shortest path from source to any other vertex can have at most N - 1 edges
		for (int relaxCount = 0; relaxCount < N - 1; ++relaxCount)
		{
			//for the two directions of each edge
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					//undirected graph doesn't have self pointed edge
					if (i != j && adjMatrix[i][j] != 0)//can be negative
					{
						//update dist[j] when found a shorter path with vertex i and edge adjMatrix[i][j]
						if (dist[i] != INT_MAX && dist[i] + adjMatrix[i][j] < dist[j])
						{
							dist[j] = dist[i] + adjMatrix[i][j];
							paths[j] = paths[i];
							paths[j].push_back(i);
						}
					}
				}
			}
		}
		//now all shortest distances from source to each vertex are found in dist[]

		//when relax all edges for the N-th time and found a shorter path
		//=> there exists a negative weight cycle
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (i != j && adjMatrix[i][j] != 0)//can be negative
				{
					if (dist[i] != INT_MAX && dist[i] + adjMatrix[i][j] < dist[j])
					{
						std::cout << "Found negative weight cycle" << std::endl;
					}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "ShortestPathInGraph BellmanFord_UndirectedAdjacencyMatrix for \"" << source << "\": " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}
	std::vector<int> BellmanFord_DAGAdjacencyMatrix(const std::vector<std::vector<int>> & DAGadjMatrix, int source)//only DAG with negative weight edge is meaningful to find shortest path
	{
		Debug::Print2D<int>()(DAGadjMatrix, false);
		int N = DAGadjMatrix.size();
		std::vector<int> dist(N, INT_MAX);
		dist[source] = 0;
		std::vector<std::vector<int> > paths(N, std::vector<int>());

		//relax all edges N - 1 times
		//a simple shortest path from source to any other vertex can have at most N - 1 edges
		for (int relaxCount = 0; relaxCount < N - 1; ++relaxCount)
		{
			//for each edge
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (DAGadjMatrix[i][j] != 0)//can be negative, can be self pointed edge
					{
						//update dist[j] when found a shorter path with vertex i and edge adjMatrix[i][j]
						if (dist[i] != INT_MAX && dist[i] + DAGadjMatrix[i][j] < dist[j])
						{
							dist[j] = dist[i] + DAGadjMatrix[i][j];
							paths[j] = paths[i];
							paths[j].push_back(i);
						}
					}
				}
			}
		}
		//now all shortest distances from source to each vertex are found in dist[]

		//when relax all edges for the N-th time and found a shorter path
		//=> there exists a negative weight cycle
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (DAGadjMatrix[i][j] != 0)//can be negative, can be self pointed edge
				{
					if (dist[i] != INT_MAX && dist[i] + DAGadjMatrix[i][j] < dist[j])
					{
						std::cout << "Found negative weight cycle" << std::endl;
					}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "ShortestPathInGraph BellmanFord_DAGAdjacencyMatrix for \"" << source << "\": " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}

	std::vector<int> Dijkstra_UndirectedAdjacencyMatrix(std::vector<std::vector<int>> & adjMatrix, int source)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::vector<int> dist(N, INT_MAX);//dist[i] the distance from source to vertex i
		dist[source] = 0;
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<std::vector<int>> paths(N, std::vector<int>());
		while (true)
		{
			int v = -1;
			for (int i = 0; i < N; ++i)
			{
				//find next vertex v that has shortest distance from source
				if (visitIndex[i] == -1 && (v == -1 || dist[i] < dist[v]))
					v = i;
			}
			if (v == -1)
				break;
			visitIndex[v] = ++visitCount;
			for (int i = 0; i < N; ++i)
			{
				if (adjMatrix[v][i] > 0 && i != v)
				{
					if (dist[v] + adjMatrix[v][i] < dist[i])
					{
						dist[i] = dist[v] + adjMatrix[v][i];
						paths[i] = paths[v];
						paths[i].push_back(v);
					}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "ShortestPathInGraph Dijkstra_UndirectedAdjacencyMatrix from \"" << source << "\": " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}
	//similar to Prim in MinSpanningTree.h
	std::vector<int> Dijkstra_MinHeap_UndirectedAdjacencyMatrix(std::vector<std::vector<int>> & adjMatrix, int source)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;//key: distance from source, value: adjacent vertex
		minHeap.push({ 0, source });
		std::vector<int> dist(N, INT_MAX);//dist[i]: the distance from source to vertex i
		dist[source] = 0;
		std::vector<std::vector<int> > paths(N, std::vector<int>());
		while (!minHeap.empty())
		{
			std::pair<int, int> p = minHeap.top();//the adjacent vertex with min distance (key: distance from source, value: adjacent vertex)
			minHeap.pop();

			int curVertex = p.second;
			//for each adjacent vertex of curVertex
			for (int i = 0; i < N; ++i)
			{
				if (adjMatrix[curVertex][i] > 0 && i != curVertex)
				{
					if (dist[curVertex] + adjMatrix[curVertex][i] < dist[i])
					{
						dist[i] = dist[curVertex] + adjMatrix[curVertex][i];
						paths[i] = paths[curVertex];
						paths[i].push_back(curVertex);
						minHeap.push({ dist[i], i });
					}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyMatrtix from \"" << source  << "\": " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}


	std::vector<int> Dijkstra_MinHeap_UndirectedAdjacencyMatrix(std::vector<std::vector<int>> & graph, int source, int target)
	{
		Debug::Print2D<int>()(graph, false);
		int N = graph.size();
		std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;//key: distance from source, value: adjacent vertex
		minHeap.push({ 0, source });
		std::vector<int> dist(N, INT_MAX);//dist[i]: the distance from source to vertex i
		std::vector<int> dad(N, -1);
		dist[source] = 0;
		while (!minHeap.empty())
		{
			std::pair<int, int> p = minHeap.top();//the adjacent vertex with min distance (key: distance from source, value: adjacent vertex)
			if (p.second == target)
				break;
			minHeap.pop();

			int curVertex = p.second;
			//for each adjacent vertex of curVertex
			for (int i = 0; i < N; ++i)
			{
				if (graph[curVertex][i] > 0 && i != curVertex)
				{
					if (dist[curVertex] + graph[curVertex][i] < dist[i])
					{
						dist[i] = dist[curVertex] + graph[curVertex][i];
						dad[i] = curVertex;
						minHeap.push({ dist[i], i });
					}
				}
			}
			//std::cout << Debug::ToStr1D<int>()(dad) << std::endl;
		}
		std::cout << "ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyMatrtix from,to: " << source << "," << target << ". Dad: " << Debug::ToStr1D<int>()(dad) << ". Dist: " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}


	//key: distance, value: adjacent vertex
	std::vector<int> Dijkstra_MinHeap_UndirectedAdjacencyList(std::vector<std::vector<std::pair<int, int>>> & graph, int source, int target)
	{
		Debug::Print2D<int>()(graph, false);
		int N = graph.size();
		std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;//key: distance from source, value: adjacent vertex
		minHeap.push({ 0, source });
		std::vector<int> dist(N, INT_MAX);//dist[i]: the distance from source to vertex i
		std::vector<int> dad(N, -1);
		dist[source] = 0;
		while (!minHeap.empty())
		{
			std::pair<int, int> p = minHeap.top();//the adjacent vertex with min distance (key: distance from source, value: adjacent vertex)
			if (p.second == target)
				break;
			minHeap.pop();

			int curVertex = p.second;
			int M = graph[curVertex].size();
			//for each adjacent vertex of curVertex
			for (int i = 0; i < M; ++i)
			{
				if (dist[curVertex] + graph[curVertex][i].first < dist[graph[curVertex][i].second])
				{
					dist[graph[curVertex][i].second] = dist[curVertex] + graph[curVertex][i].first;
					dad[graph[curVertex][i].second] = curVertex;
					minHeap.push({ dist[graph[curVertex][i].second], graph[curVertex][i].second });
				}
			}
			//std::cout << Debug::ToStr1D<int>()(dad) << std::endl;
		}
		std::cout << "ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyList from,to: " << source << "," << target << ". Dad: " << Debug::ToStr1D<int>()(dad) << ". Dist: " << Debug::ToStr1D<int>()(dist) << std::endl;
		return dist;
	}


	struct GreaterThanComp
	{
		bool operator()(const std::pair<std::pair<int, int>, int> & a, const std::pair<std::pair<int, int>, int> & b)
		{
			return a.first.first != b.first.first ? a.first.first < b.first.first : a.first.second < b.first.second;//first.first: distance from source, first.second: edge count from source, second: adjacent vertex
		}
	};
	std::vector<int> Dijkstra_MinEdges_MinHeap_UndirectedAdjacencyMatrix(std::vector<std::vector<int>> & graph, int source, int target)
	{
		Debug::Print2D<int>()(graph, false);
		int N = graph.size();
		std::priority_queue <std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, GreaterThanComp> minHeap;//first.first: distance from source, first.second: edge count from source, second: adjacent vertex
		minHeap.push({ { 0, 0 }, source });
		std::vector<int> dist(N, INT_MAX);//dist[i]: the distance from source to vertex i
		std::vector<int> edge(N, INT_MAX);//edge[i]: the edge count from source to vertex i
		std::vector<int> dad(N, -1);
		dist[source] = 0;
		edge[source] = 0;
		while (!minHeap.empty())
		{
			std::pair<std::pair<int, int>, int> p = minHeap.top();//the adjacent vertex with min distance (first.first: distance from source, first.second: edge count from source, second: adjacent vertex)
			if (p.second == target)
				break;
			minHeap.pop();

			int curVertex = p.second;
			//for each adjacent vertex of curVertex
			for (int i = 0; i < N; ++i)
			{
				if (graph[curVertex][i] > 0 && i != curVertex)
				{
					if (dist[curVertex] + graph[curVertex][i] < dist[i] || 
						(dist[curVertex] + graph[curVertex][i] == dist[i] && edge[curVertex] + 1 < edge[i]))
					{
						dist[i] = dist[curVertex] + graph[curVertex][i];
						edge[i] = edge[curVertex] + 1;
						dad[i] = curVertex;
						minHeap.push({ { dist[i], edge[i] }, i });
					}
				}
			}
			//std::cout << Debug::ToStr1D<int>()(dad) << std::endl;
		}
		std::cout << "ShortestPathInGraph Dijkstra_MinEdges_MinHeap_UndirectedAdjacencyMatrtix from,to: " << source << "," << target << ". Dad: " << Debug::ToStr1D<int>()(dad) << ". Dist: " << Debug::ToStr1D<int>()(dist) << ". Edge: " << Debug::ToStr1D<int>()(edge) << std::endl;
		return dist;
	}
};
/*
		           9
		       5------4
		     / |     /|
		 14/  2|  7/  |
		 /  9  | /    |
		0------2    -6|
		 \     | \    |
		  7\ 10| 11\  |
		     \ |     \|
		       1------3
		          15
[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 7, 2
Row#3	= 0, 15, 11, 0, -6, 0
Row#4	= 0, 0, 7, -6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

Found negative weight cycle
Found negative weight cycle
Found negative weight cycle
Found negative weight cycle
Found negative weight cycle
[rY][cX]
Row#0	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 5
Row#1	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3,  ,
Row#2	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4,
Row#3	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4,
Row#4	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3,  ,
Row#5	= 0, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4,

ShortestPathInGraph BellmanFord_UndirectedAdjacencyMatrix for "0": -11, -13, -27, -40, -34, -25

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

[rY][cX]
Row#0	=  ,  ,
Row#1	= 0,  ,
Row#2	= 0,  ,
Row#3	= 0, 2,
Row#4	= 0, 2, 3
Row#5	= 0, 2,

ShortestPathInGraph BellmanFord_DAGAdjacencyMatrix for "0": 0, 7, 9, 20, 14, 11

		           9
		       5------4
		     / |      |
		 14/  2|      |
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

[rY][cX]
Row#0	=  ,  ,
Row#1	= 0,  ,
Row#2	= 0,  ,
Row#3	= 0, 2,
Row#4	= 0, 2, 5
Row#5	= 0, 2,

ShortestPathInGraph BellmanFord_UndirectedAdjacencyMatrix for "0": 0, 7, 9, 20, 20, 11

[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

[rY][cX]
Row#0	=  ,  ,
Row#1	= 0,  ,
Row#2	= 0,  ,
Row#3	= 0, 2,
Row#4	= 0, 2, 5
Row#5	= 0, 2,

ShortestPathInGraph Dijkstra_UndirectedAdjacencyMatrix from "0": 0, 7, 9, 20, 20, 11

[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

[rY][cX]
Row#0	=  ,  ,
Row#1	= 0,  ,
Row#2	= 0,  ,
Row#3	= 0, 2,
Row#4	= 0, 2, 5
Row#5	= 0, 2,

ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyMatrtix from "0": 0, 7, 9, 20, 20, 11

[rY][cX]
Row#0	= 0, 7, 9, 0, 0, 14
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 14, 0, 2, 0, 9, 0

ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyMatrtix from,to: 0,4. Dad: -1, 0, 0, 2, 5, 2. Dist: 0, 7, 9, 20, 20, 11
[rY][cX]
Row#0	= [7,1], [9,2], [14,5],
Row#1	= [7,0], [10,2], [15,3],
Row#2	= [9,0], [10,1], [11,3], [2,5]
Row#3	= [15,1], [11,2], [6,4],
Row#4	= [6,3], [9,5],  ,
Row#5	= [14,0], [2,2], [9,4],

ShortestPathInGraph Dijkstra_MinHeap_UndirectedAdjacencyList from,to: 0,4. Dad: -1, 0, 0, 2, 5, 2. Dist: 0, 7, 9, 20, 20, 11

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
Row#0	= 0, 7, 9, 0, 0, 11
Row#1	= 7, 0, 10, 15, 0, 0
Row#2	= 9, 10, 0, 11, 0, 2
Row#3	= 0, 15, 11, 0, 6, 0
Row#4	= 0, 0, 0, 6, 0, 9
Row#5	= 11, 0, 2, 0, 9, 0

ShortestPathInGraph Dijkstra_MinEdges_MinHeap_UndirectedAdjacencyMatrtix from,to: 0,4. Dad: -1, 0, 0, -1, 5, 0. Dist: 0, 7, 9, 2147483647, 20, 11. Edge: 0, 1, 1, 2147483647, 2, 1
*/
#endif