#ifndef MAX_FLOW_IN_FLOW_NETWORK_H
#define MAX_FLOW_IN_FLOW_NETWORK_H
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
/*
http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
http://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/
Given a graph which represents a flow network where every edge has a capacity.
Also given tow vertices source 's' and sink 't' in the graph, find the max possible flow from s to t with these constraints:
1. Flow on an edge doesn't exceed the given capacity of the edge
2. Incoming flow is equal to outgoing flow for every vertex except s and t

O(maxFlow * E) time

Edmonds-Karp Implementation: use BFS to implement FordFulkerson, O(VE^2) time
Dinics Implementation: use BFS to compute BFS level of each node, then use DFS to send flow to all the s-t-increasing-level-paths, O(EV^2) time

Residual graph of a flow network:
a graph which indicates additional possible flow
Residual capacity of an edge:
original capacity of the edge minus current flow
or the current capacity of the edge

See also MaxNumEdgeDisjointPaths.h, MinSTCutInFlowNetwork.h
*/
class MaxFlowInFlowNetwork
{
public:
	MaxFlowInFlowNetwork(){}
	~MaxFlowInFlowNetwork(){}

	int FordFulkerson_ConnectedDirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int s, int t)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		std::vector<std::vector<int> > residualAdjMatrix;
		int maxFlow = this->FordFulkerson_ConnectedDirectedAdjacencyMatrix(adjMatrix, s, t, residualAdjMatrix);
		std::cout << "MaxFlowInFlowNetwork FordFulkerson_ConnectedDirectedAdjacencyMatrix for \"" << s << "->" << t << "\": " << maxFlow << std::endl;
		return maxFlow;
	}

	//Edmonds-Karp Implementation: use BFS to implement FordFulkerson, O(VE^2) time
	int FordFulkerson_ConnectedDirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int s, int t, std::vector<std::vector<int> > & residualAdjMatrix)
	{
		int N = adjMatrix.size();
		residualAdjMatrix = adjMatrix;
		std::vector<int> dad(N, -1);
		int maxFlow = 0;

		//augment the flow while there is path from source to target
		while (this->bFS_StoT_ConnectedDirectedAdjacencyMatrix(residualAdjMatrix, s, t, dad))
		{
			std::cout << "Path: " << this->getPath(dad, s, t) << std::endl;
			int curPathFlow = INT_MAX;

			//1. find the min residual capacity among all the edges (max flow avaliable) in the found path
			for (int v = t; v != s; v = dad[v])
			{
				int u = dad[v];
				curPathFlow = std::min(curPathFlow, residualAdjMatrix[u][v]);
			}
			//2. update residual capacity of each edge and reverse edge in the found path
			for (int v = t; v != s; v = dad[v])
			{
				int u = dad[v];
				residualAdjMatrix[u][v] -= curPathFlow;//residual capacity = original capacity - current flow
				//residualAdjMatrix[v][u] += curPathFlow;//reverse edge (the BFS impl traverses shorter path first, the longer path is left to last, so don't need to consider reversed edge)
			}

			maxFlow += curPathFlow;
			//Debug::Print2D<int>()(residualAdjMatrix, false);
		}
		return maxFlow;
	}
private:
	bool bFS_StoT_ConnectedDirectedAdjacencyMatrix(const std::vector<std::vector<int> > & rAdjMatrix, int s, int t, 
		std::vector<int> & dad)
	{
		int N = rAdjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::queue<int> que;
		
		visitIndex[s] = ++visitCount;
		dad[s] = -1;
		que.push(s);
		while (!que.empty())
		{
			int v = que.front();
			que.pop();
			//enumerate all adj vertices
			for (int i = 0; i < N; ++i)
			{
				if (rAdjMatrix[v][i] > 0)
					if (visitIndex[i] == -1)
					{
						visitIndex[i] = ++visitCount;
						dad[i] = v;
						que.push(i);
					}
			}
		}
		bool reachT = (visitIndex[t] == -1) ? false : true;
		return reachT;
	}

	std::string getPath(const std::vector<int> & dad, int s, int t)
	{
		std::stack<int> stk;
		for (int v = t; v != s; v = dad[v])
		{
			stk.push(v);
		}
		stk.push(s);
		return Debug::ToStr1D<int>()(stk);
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
MaxFlowInFlowNetwork FordFulkerson_ConnectedDirectedAdjacencyMatrix for "0->3": 20

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
MaxFlowInFlowNetwork FordFulkerson_ConnectedDirectedAdjacencyMatrix for "0->5": 28

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
MaxFlowInFlowNetwork FordFulkerson_ConnectedDirectedAdjacencyMatrix for "0->5": 23
*/
#endif