#ifndef MIN_SPANNING_TREE_H
#define MIN_SPANNING_TREE_H
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
#include "UnionFindGraphComponent.h"
#include "GraphTransform.h"
/*
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module8/module8.html
http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
http://www.cprogramming.com/tutorial/computersciencetheory/mst.html
Leetcode: Minimum Height Trees
Given a connected and undirected weighted graph, a spanning tree of the graph is a subgraph that is a tree and connects all the vertices together.
A single graph can have many different spanning trees.
A minimum spanning tree is a spanning tree with weight less than or equal to the weight of every other spanning tree.
The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.

Kruskal (use sorted edge list and union-find): greedy
O(ElogE+ElogV) = O(ElogE) or O(ElogV)
Prim (use min heap): greedy
O(ElogV)
*/
class MinSpanningTree
{
public:
	MinSpanningTree(){}
	~MinSpanningTree(){}

	std::vector<std::pair<int, std::pair<int, int>>> Kruskal_UnionFind_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)//adjMatrix is supposed to be undirected, weighted, and weakly connected
	{
		Debug::Print2D<int>()(adjMatrix);
		int N = adjMatrix.size();

		//1. transform adjMatrix to a list of edges sorted by weight
		std::vector<std::pair<int, std::pair<int, int> > > sortedEdges;//weight, source, destination
		sortedEdges = GraphTransform().Undirected_AdjacencyMatrixToEdgeList(adjMatrix);
		std::sort(sortedEdges.begin(), sortedEdges.end(),
			[](const std::pair<int, std::pair<int, int> > & a, const std::pair<int, std::pair<int, int> > & b)
		{return a.first < b.first; });//in non-decreasing order of weight
		int E = sortedEdges.size();

		std::vector<int> parentIndex(N, -1);

		std::vector<std::pair<int, std::pair<int, int> > > resEdges;//weight, source, destination
		int weightSum = 0;

		//2. for each edge in non-decreasing order of weight, find the root vertices of subsets where its 2 end vertices belong to
		//if they belong to 2 diff subsets, add the current edge to result and union the 2 diff subsets
		for (int i = 0; i < E; ++i)
		{
			std::pair<int, std::pair<int, int> > curEdge = sortedEdges[i];
			int root1 = UnionFindGraphComponent().FindRecur(parentIndex, curEdge.second.first);
			int root2 = UnionFindGraphComponent().FindRecur(parentIndex, curEdge.second.second);
			if (root1 != root2)
			{
				resEdges.push_back(curEdge);
				weightSum += curEdge.first;
				UnionFindGraphComponent().Union(parentIndex, root1, root2);
			}
			//std::cout << Debug::ToStr1D<int>()(parentIndex) << std::endl;
		}
		std::cout << "MinSpanningTree Kruskal_UnionFind_AdjacencyMatrix for \"" << Debug::ToStr1D<int>()(sortedEdges) << "\": " << Debug::ToStr1D<int>()(resEdges) << ". WeightSum: " << weightSum << std::endl;
		return resEdges;
	}
	std::vector<std::pair<int, std::pair<int, int>>> Kruskal_UnionFind2_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)//adjMatrix is supposed to be undirected, weighted, and weakly connected
	{
		Debug::Print2D<int>()(adjMatrix);
		int N = adjMatrix.size();

		//1. transform adjMatrix to a list of edges sorted by weight
		std::vector<std::pair<int, std::pair<int, int> > > sortedEdges;//weight, source, destination
		sortedEdges = GraphTransform().Undirected_AdjacencyMatrixToEdgeList(adjMatrix);
		std::sort(sortedEdges.begin(), sortedEdges.end(), 
			[](const std::pair<int, std::pair<int, int> > & a, const std::pair<int, std::pair<int, int> > & b)
			{return a.first < b.first; });//in non-decreasing order of weight
		int E = sortedEdges.size();

		std::vector<std::pair<int, int> > parentRankPairs(N, std::make_pair(0, 0));
		for (int i = 0; i < N; ++i)
			parentRankPairs[i].first = i;

		std::vector<std::pair<int, std::pair<int, int> > > resEdges;//weight, source, destination
		int weightSum = 0;

		//2. for each edge in non-decreasing order of weight, find the root vertices of subsets where its 2 end vertices belong to
		//if they belong to 2 diff subsets, add the current edge to result and union the 2 diff subsets
		for (int i = 0; i < E; ++i)
		{
			std::pair<int, std::pair<int, int> > curEdge = sortedEdges[i];
			int root1 = UnionFindGraphComponent().FindRecur(parentRankPairs, curEdge.second.first);
			int root2 = UnionFindGraphComponent().FindRecur(parentRankPairs, curEdge.second.second);
			if (root1 != root2)
			{
				resEdges.push_back(curEdge);
				weightSum += curEdge.first;
				UnionFindGraphComponent().Union(parentRankPairs, root1, root2);
			}
			//std::cout << Debug::ToStr1D<int>()(parentRankPairs) << std::endl;
		}
		std::cout << "MinSpanningTree Kruskal_UnionFind2_AdjacencyMatrix for \"" << Debug::ToStr1D<int>()(sortedEdges) << "\": " << Debug::ToStr1D<int>()(resEdges) << ". WeightSum: " << weightSum << std::endl;
		return resEdges;
	}

	//similar to Dijkstra in ShortestPathInGraph.h
	std::vector<int> Prim_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int source)//adjMatrix is supposed to be undirected, weighted, and weakly connected
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();
		std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > minHeap;//first: distance (weight) from dad, second: adjacent vertex
		std::vector<int> dist(N, INT_MAX);//dist[i] the distance (weight) from dad to vertex i
		std::vector<int> dad(N, -1);
		dist[source] = 0;
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		minHeap.push(std::make_pair(0, source));
		while (!minHeap.empty())
		{
			std::pair<int, int> p = minHeap.top();//the adjacent vertex with min distance (first: distance from dad, second: adjacent vertex)
			minHeap.pop();
			int curVertex = p.second;
			if (visitIndex[curVertex] != -1)
				continue;
			visitIndex[curVertex] = ++visitCount;
			
			//for each adjacent vertex of curVertex
			for (int i = 0; i < N; ++i)
			{
				if (adjMatrix[curVertex][i] > 0 && i != curVertex)
				if (visitIndex[i] == -1)
					if (adjMatrix[curVertex][i] < dist[i])
					{
						dist[i] = adjMatrix[curVertex][i];
						dad[i] = curVertex;
						minHeap.push(std::make_pair(adjMatrix[curVertex][i], i));
					}
			}
			//std::cout << Debug::ToStr1D<int>()(dad) << std::endl;
		}
		int weightSum = 0;
		for (int i = 0; i < N; ++i)
			weightSum += dist[i];
		std::cout << "MinSpanningTree Prim_AdjacencyMatrix Dad: " << Debug::ToStr1D<int>()(dad) << ". Dist: " << Debug::ToStr1D<int>()(dist)  << ". WeightSum: " << weightSum << ". VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << std::endl;
		return dad;
	}

	//first: weight, second: adj vertex
	std::vector<int> Prim_AdjacencyList(const std::vector<std::vector<std::pair<int, int> > > & adjList, int source)//adjList is supposed to be undirected, weighted, and weakly connected
	{
		Debug::Print2D<int>()(adjList, false);
		int N = adjList.size();
		std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > minHeap;//first: weight, second: adj vertex
		std::vector<int> dist(N, INT_MAX);
		std::vector<int> dad(N, -1);
		dist[source] = 0;
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		minHeap.push(std::make_pair(0, source));
		while (!minHeap.empty())
		{
			std::pair<int, int> p = minHeap.top();
			minHeap.pop();
			int curVertex = p.second;
			if (visitIndex[curVertex] != -1)
				continue;
			visitIndex[curVertex] = ++visitCount;

			int M = adjList[curVertex].size();
			//for each adjacent vertex of curVertex
			for (int i = 0; i < M; ++i)
			{
				if (visitIndex[adjList[curVertex][i].second] == -1)
				if (adjList[curVertex][i].first < dist[adjList[curVertex][i].second])
				{
					dist[adjList[curVertex][i].second] = adjList[curVertex][i].first;
					dad[adjList[curVertex][i].second] = curVertex;
					minHeap.push(std::make_pair(adjList[curVertex][i].first, adjList[curVertex][i].second));
				}
			}
			//std::cout << Debug::ToStr1D<int>()(dad) << std::endl;
		}
		int weightSum = 0;
		for (int i = 0; i < N; ++i)
			weightSum += dist[i];
		std::cout << "MinSpanningTree Prim_AdjacencyList Dad: " << Debug::ToStr1D<int>()(dad) << ". Dist: " << Debug::ToStr1D<int>()(dist) << ". WeightSum: " << weightSum << ". VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << std::endl;
		return dad;
	}
};
/*
		          24   15   31
		        -----3----4----6
		  11  / 46 5/ \   39  /
		0----1-----2    -----
		 \        / \52
		   ------    5----7
		     48        60
		Only 1 possible min spanning tree:
		          24   15   31
		        -----3----4----6
		  11  /    5/
		0----1     2
		            \52
		             5----7
		               60
[cX][rY]
Row#0	= 0, 11, 48, 0, 0, 0, 0, 0
Row#1	= 11, 0, 46, 24, 0, 0, 0, 0
Row#2	= 48, 46, 0, 5, 0, 52, 0, 0
Row#3	= 0, 24, 5, 0, 15, 0, 39, 0
Row#4	= 0, 0, 0, 15, 0, 0, 31, 0
Row#5	= 0, 0, 52, 0, 0, 0, 0, 60
Row#6	= 0, 0, 0, 39, 31, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 60, 0, 0

MinSpanningTree Kruskal_UnionFind_AdjacencyMatrix for "[5,(2,3)], [11,(0,1)], [15,(3,4)], [24,(1,3)], [31,(4,6)], [39,(3,6)], [46,(1,2)], [48,(0,2)], [52,(2,5)], [60,(5,7)]": [5,(2,3)], [11,(0,1)], [15,(3,4)], [24,(1,3)], [31,(4,6)], [52,(2,5)], [60,(5,7)]. WeightSum: 198
[cX][rY]
Row#0	= 0, 11, 48, 0, 0, 0, 0, 0
Row#1	= 11, 0, 46, 24, 0, 0, 0, 0
Row#2	= 48, 46, 0, 5, 0, 52, 0, 0
Row#3	= 0, 24, 5, 0, 15, 0, 39, 0
Row#4	= 0, 0, 0, 15, 0, 0, 31, 0
Row#5	= 0, 0, 52, 0, 0, 0, 0, 60
Row#6	= 0, 0, 0, 39, 31, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 60, 0, 0

MinSpanningTree Kruskal_UnionFind2_AdjacencyMatrix for "[5,(2,3)], [11,(0,1)], [15,(3,4)], [24,(1,3)], [31,(4,6)], [39,(3,6)], [46,(1,2)], [48,(0,2)], [52,(2,5)], [60,(5,7)]": [5,(2,3)], [11,(0,1)], [15,(3,4)], [24,(1,3)], [31,(4,6)], [52,(2,5)], [60,(5,7)]. WeightSum: 198
[rY][cX]
Row#0	= 0, 11, 48, 0, 0, 0, 0, 0
Row#1	= 11, 0, 46, 24, 0, 0, 0, 0
Row#2	= 48, 46, 0, 5, 0, 52, 0, 0
Row#3	= 0, 24, 5, 0, 15, 0, 39, 0
Row#4	= 0, 0, 0, 15, 0, 0, 31, 0
Row#5	= 0, 0, 52, 0, 0, 0, 0, 60
Row#6	= 0, 0, 0, 39, 31, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 60, 0, 0

MinSpanningTree Prim_AdjacencyMatrix Dad: 1, 3, 3, -1, 3, 2, 4, 5. Dist: 11, 24, 5, 0, 15, 52, 31, 60. WeightSum: 198. VisitIndex: 4, 3, 1, 0, 2, 6, 5, 7


		      8   7
		    1---2---3
		 4/ |  2|\  | \9
		0   |11 8 \4|14 4
		 8\ | /7|6 \| /10
		    7---6---5
			  1   2
		2 possible min spanning trees:
			      7
		    1   2---3
		 4/    2|\    \9
		0       8 \4    4
		 8\        \
		    7---6---5
			  1   2
			  8   7
		    1---2---3
		 4/    2|\    \9
		0       8 \4    4
		           \
		    7---6---5
			  1   2
[cX][rY]
Row#0	= 0, 4, 0, 0, 0, 0, 0, 8, 0
Row#1	= 4, 8, 8, 0, 0, 0, 0, 11, 0
Row#2	= 0, 0, 0, 7, 0, 4, 0, 0, 2
Row#3	= 0, 0, 7, 0, 9, 14, 0, 0, 0
Row#4	= 0, 0, 0, 9, 0, 10, 0, 0, 0
Row#5	= 0, 0, 4, 14, 10, 0, 2, 0, 0
Row#6	= 0, 0, 0, 0, 0, 2, 0, 1, 6
Row#7	= 8, 11, 0, 0, 0, 0, 1, 0, 7
Row#8	= 0, 0, 2, 0, 0, 0, 6, 7, 0

MinSpanningTree Kruskal_UnionFind_AdjacencyMatrix for "[1,(6,7)], [2,(2,8)], [2,(5,6)], [4,(0,1)], [4,(2,5)], [6,(6,8)], [7,(2,3)], [7,(7,8)], [8,(0,7)], [9,(3,4)], [10,(4,5)], [11,(1,7)], [14,(3,5)]": [1,(6,7)], [2,(2,8)], [2,(5,6)], [4,(0,1)], [4,(2,5)], [7,(2,3)], [8,(0,7)], [9,(3,4)]. WeightSum: 37
[cX][rY]
Row#0	= 0, 4, 0, 0, 0, 0, 0, 8, 0
Row#1	= 4, 8, 8, 0, 0, 0, 0, 11, 0
Row#2	= 0, 0, 0, 7, 0, 4, 0, 0, 2
Row#3	= 0, 0, 7, 0, 9, 14, 0, 0, 0
Row#4	= 0, 0, 0, 9, 0, 10, 0, 0, 0
Row#5	= 0, 0, 4, 14, 10, 0, 2, 0, 0
Row#6	= 0, 0, 0, 0, 0, 2, 0, 1, 6
Row#7	= 8, 11, 0, 0, 0, 0, 1, 0, 7
Row#8	= 0, 0, 2, 0, 0, 0, 6, 7, 0

MinSpanningTree Kruskal_UnionFind2_AdjacencyMatrix for "[1,(6,7)], [2,(2,8)], [2,(5,6)], [4,(0,1)], [4,(2,5)], [6,(6,8)], [7,(2,3)], [7,(7,8)], [8,(0,7)], [9,(3,4)], [10,(4,5)], [11,(1,7)], [14,(3,5)]": [1,(6,7)], [2,(2,8)], [2,(5,6)], [4,(0,1)], [4,(2,5)], [7,(2,3)], [8,(0,7)], [9,(3,4)]. WeightSum: 37
[rY][cX]
Row#0	= 0, 4, 0, 0, 0, 0, 0, 8, 0
Row#1	= 4, 8, 0, 0, 0, 0, 0, 11, 0
Row#2	= 0, 8, 0, 7, 0, 4, 0, 0, 2
Row#3	= 0, 0, 7, 0, 9, 14, 0, 0, 0
Row#4	= 0, 0, 0, 9, 0, 10, 0, 0, 0
Row#5	= 0, 0, 4, 14, 10, 0, 2, 0, 0
Row#6	= 0, 0, 0, 0, 0, 2, 0, 1, 6
Row#7	= 8, 11, 0, 0, 0, 0, 1, 0, 7
Row#8	= 0, 0, 2, 0, 0, 0, 6, 7, 0

MinSpanningTree Prim_AdjacencyMatrix Dad: 7, 0, 3, -1, 3, 2, 5, 6, 2. Dist: 8, 4, 7, 0, 9, 4, 2, 1, 2. WeightSum: 37. VisitIndex: 6, 7, 1, 0, 8, 3, 4, 5, 2
[rY][cX]
Row#0	= [4,1], [8,7],  ,  
Row#1	= [4,0], [8,1], [11,7],  
Row#2	= [8,1], [7,3], [4,5], [2,8]
Row#3	= [7,2], [9,4], [14,5],  
Row#4	= [9,3], [10,5],  ,  
Row#5	= [4,2], [14,3], [10,4], [2,6]
Row#6	= [2,5], [1,7], [6,8],  
Row#7	= [8,0], [11,1], [1,6], [7,8]
Row#8	= [2,2], [6,6], [7,7],  

MinSpanningTree Prim_AdjacencyList Dad: -1, 0, 5, 2, 3, 6, 7, 0, 2. Dist: 0, 4, 4, 7, 9, 2, 1, 8, 2. WeightSum: 37. VisitIndex: 0, 1, 5, 7, 8, 4, 3, 2, 6
*/
#endif