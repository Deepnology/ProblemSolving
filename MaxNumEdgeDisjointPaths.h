#ifndef MAX_NUM_EDGE_DISJOINT_PATHS_H
#define MAX_NUM_EDGE_DISJOINT_PATHS_H
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
http://www.geeksforgeeks.org/find-edge-disjoint-paths-two-vertices/
Given a directed graph (w/ edge weights are all equal to 1) and two vertices in it, source 's' and destination 't'.
Find out the max number of edge-disjoint-paths from s to t.
Two paths are said edge disjoint if they don't share any edge.

This problem can be solved by reducing it to max flow in flow network problem with an input digraph whose each edge's capacity equal to 1.
The max flow from s to t is equal to the max number of edge-disjoint-paths from s to t.

See also MaxFlowInFlowNetwork.h, MinSTCutInFlowNetwork.h
*/
class MaxNumEdgeDisjointPaths
{
public:
	MaxNumEdgeDisjointPaths(){}
	~MaxNumEdgeDisjointPaths(){}

	int FordFulkerson_ConnectedDirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int s, int t)//all edges' weights in adjMatrix are equal to 1
	{
		Debug::Print2D<int>()(adjMatrix, false);
		std::vector<std::vector<int> > residualAdjMatrix;
		int maxFlow = MaxFlowInFlowNetwork().FordFulkerson_ConnectedDirectedAdjacencyMatrix(adjMatrix, s, t, residualAdjMatrix);
		std::cout << "MaxNumEdgeDisjointPaths FordFulkerson_ConnectedDirectedAdjacencyMatrix for \"" << s << "->" << t << "\": " << maxFlow << std::endl;
		return maxFlow;
	}
};
/*
		      1     4
		     ^|^   /^\
		   /  |  X  |  \
		 /    vv   \|    v
		0---->2     5---->7
		 \    |\    ^    ^
		   \  |  \  |  /
			 vv    v|/
		      3---->6
[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0, 1, 0
Row#3	= 0, 0, 0, 0, 0, 0, 1, 0
Row#4	= 0, 0, 1, 0, 0, 0, 0, 1
Row#5	= 0, 1, 0, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 0, 0, 1, 0, 1
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0

Path: 7, 6, 2, 0
Path: 7, 5, 6, 3, 0
MaxNumEdgeDisjointPaths FordFulkerson_ConnectedDirectedAdjacencyMatrix for "0->7": 2
*/
#endif