#ifndef MIN_ST_CUT_IN_FLOW_NETWORK_H
#define MIN_ST_CUT_IN_FLOW_NETWORK_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include "Debug.h"
#include "MaxFlowInFlowNetwork.h"
/*
http://www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/
Find all edges of the minimum capacity of s-t cut of the given flow network.
The capacity of an s-t cut is the sum of capacity of each edge in the cut-set.
An s-t cut in a flow network is a cut that requires the source 's' and sink 't' to be in different subsets,
which consists of edges going from s's subset to t's subset.

From max-flow min-cut theorem:
In a flow network, the amount of maximum flow is equal to capacity of the minimum cut.

See also MaxFlowInFlowNetwork.h, MaxNumEdgeDisjointPaths.h
*/
class MinSTCutInFlowNetwork
{
public:
	MinSTCutInFlowNetwork(){}
	~MinSTCutInFlowNetwork(){}

	std::vector<std::pair<int, int> > FindAll_ConnectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int s, int t)
	{
		int N = adjMatrix.size();

		//1. compute the result residual graph of FordFulkerson algorithm
		std::vector<std::vector<int> > residualAdjMatrix;
		MaxFlowInFlowNetwork().FordFulkerson_ConnectedDirectedAdjacencyMatrix(adjMatrix, s, t, residualAdjMatrix);

		//2. mark the set of vertices that are reachable from source in the residual graph with DFS
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		this->dFS_ConnectedAdjacencyMatrix(residualAdjMatrix, s, visitCount, visitIndex);

		//3. the min s-t cut edges are all the edges that are from source-reachable vertices to source non-reachable vertices
		std::vector<std::pair<int, int> > stCut;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (visitIndex[i] != -1 && visitIndex[j] == -1 && adjMatrix[i][j] != 0)//i is reachable && j is non-reachable && [i,j] was an edge
					stCut.push_back(std::make_pair(i, j));

		std::cout << "MinSTCutInFlowNetwork FindAll_ConnectedAdjacencyMatrix for \"" << s << "->" << t << "\": " << Debug::ToStr1D<int>()(stCut) << std::endl;
		return stCut;
	}
private:
	void dFS_ConnectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		//enumerate all adj vertices
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] != 0)
				if (visitIndex[i] == -1)
					this->dFS_ConnectedAdjacencyMatrix(adjMatrix, i, visitCount, visitIndex);
		}
	}
};
/*
		    ---> 1 ---
		10/      |     \9
		 /       |      v
		0        |1     3
		 \       |      ^
		10\      v     /11
		    ---> 2 ---
		residual graph for above:
		0->1->3 (9)
		0->2->3 (10)
		0->1->2->3 (1)
		    ---> 1 ---
		 0/      |     \0
		 /       |      v
		0        |0     3
		 \       |      ^
		 0\      v     /0
		    ---> 2 ---
[rY][cX]
Row#0	= 0, 10, 10, 0
Row#1	= 0, 0, 1, 9
Row#2	= 0, 0, 0, 11
Row#3	= 0, 0, 0, 0

Path: 3, 1, 0
Path: 3, 2, 0
Path: 3, 2, 1, 0
MinSTCutInFlowNetwork FindAll_ConnectedAdjacencyMatrix for "0->3": [0,1], [0,2]

		            9
		    ---> 1 ---> 3 ---
		10/     4|  \15 |15   \10
		 /   5   v  8 v v  10  v
		0------->6----->7----->5
		 \      4| ^    |15    ^
		15\      v   \6 v     /10
		    ---> 2 ---> 4 ---
			        16
		residual graph of above:
		0->1->3->5 (9)
		0->1->7->5 (1)
		0->2->4->5 (10)
		0->6->7->5 (5)
		0->2->4->6->7->5 (3)
		            0
		    ---> 1 ---> 3 ---
		 0/     4|  \14 |15   \1
		 /   0   v  0 v v   1  v
		0------->6----->7----->5
		 \      4| ^    |15    ^
		 2\      v   \3 v     /0
		    ---> 2 ---> 4 ---
			        3
[rY][cX]
Row#0	= 0, 10, 15, 0, 0, 0, 5, 0
Row#1	= 0, 0, 0, 9, 0, 0, 4, 15
Row#2	= 0, 0, 0, 0, 16, 0, 0, 0
Row#3	= 0, 0, 0, 0, 0, 10, 0, 15
Row#4	= 0, 0, 0, 0, 0, 10, 6, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 4, 0, 0, 0, 0, 8
Row#7	= 0, 0, 0, 0, 15, 10, 0, 0

Path: 5, 3, 1, 0
Path: 5, 7, 1, 0
Path: 5, 4, 2, 0
Path: 5, 7, 6, 0
Path: 5, 7, 6, 4, 2, 0
MinSTCutInFlowNetwork FindAll_ConnectedAdjacencyMatrix for "0->5": [0,1], [4,5], [6,7]

		            12
		    ---> 1 ---> 3 ---
		16/     |^    / ^     \20
		 /      ||   /  |      v
		0     10||4 /9  |7      5
		 \      || /    |      ^
		13\     v|v     |     /4
		    ---> 2 ---> 4 ---
			        14
		residual graph for above:
		0->1->3->5 (12)
		0->2->4->5 (4)
		0->2->4->3->5 (7)
		            0
		    ---> 1 ---> 3 ---
		 4/     |^    / ^     \1
		 /      ||   /  |      v
		0     10||4 /9  |0      5
		 \      || /    |      ^
		 2\     v|v     |     /0
		    ---> 2 ---> 4 ---
			        3
[rY][cX]
Row#0	= 0, 16, 13, 0, 0, 0
Row#1	= 0, 0, 10, 12, 0, 0
Row#2	= 0, 4, 0, 0, 14, 0
Row#3	= 0, 0, 9, 0, 0, 20
Row#4	= 0, 0, 0, 7, 0, 4
Row#5	= 0, 0, 0, 0, 0, 0

Path: 5, 3, 1, 0
Path: 5, 4, 2, 0
Path: 5, 3, 4, 2, 0
MinSTCutInFlowNetwork FindAll_ConnectedAdjacencyMatrix for "0->5": [1,3], [4,3], [4,5]
*/
#endif