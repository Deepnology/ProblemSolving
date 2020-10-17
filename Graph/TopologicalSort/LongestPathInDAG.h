#ifndef LONGEST_PATH_IN_DAG_H
#define LONGEST_PATH_IN_DAG_H
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
http://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/
Aka critical path
Given a weighted directed acylic graph (DAG) and a source vertex in it, find the longest distances from source to all other vertices in the given graph.
O(V+E) for topological sorting
O(V+E) for calculating each vertex distance from source
so total is O(V+E)
*/
class LongestPathInDAG
{
public:
	LongestPathInDAG(){}
	~LongestPathInDAG(){}

	void DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & DAGadjMatrix, int source)
	{
		Debug::Print2D<int>()(DAGadjMatrix, false);
		int N = DAGadjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::stack<int> stk;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				this->DFS_AdjacencyMatrix_Recur(DAGadjMatrix, i, visitCount, visitIndex, stk);
			}
		}
		std::string topologicalSort = Debug::ToStr1D<int>()(stk);
		std::vector<int> dist(N, INT_MIN);//dist[i]: max dist from source to vertex i
		dist[source] = 0;
		std::vector<std::vector<int> > paths(N, std::vector<int>());
		while (!stk.empty())
		{
			int v = stk.top();
			stk.pop();
			if (dist[v] != INT_MIN)
			{
				for (int i = 0; i < N; ++i)
				{
					if (DAGadjMatrix[v][i] > 0)
						if (dist[i] < dist[v] + DAGadjMatrix[v][i])
						{
							dist[i] = dist[v] + DAGadjMatrix[v][i];
							paths[i] = paths[v];
							paths[i].push_back(v);
						}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "LongestPathInDAG DFS for source=\""<< source <<  "\", topologicalSort=\"" << topologicalSort << "\", distFromSource: " << Debug::ToStr1D<int>()(dist) << std::endl;
	}
	void DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & DAGadjMatrix)
	{
		Debug::Print2D<int>()(DAGadjMatrix, false);
		int N = DAGadjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::stack<int> stk;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				this->DFS_AdjacencyMatrix_Recur(DAGadjMatrix, i, visitCount, visitIndex, stk);
			}
		}
		std::string topologicalSort = Debug::ToStr1D<int>()(stk);
		std::vector<int> dist(N, INT_MIN);//dist[i]: max dist from inDegree=0 nodes to node i
		std::vector<int> inDegree(N, 0);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
				if (DAGadjMatrix[i][j])
					++inDegree[j];
		}
		for (int i = 0; i < N; ++i)
			if (inDegree[i] == 0)
				dist[i] = 0;
		std::vector<std::vector<int> > paths(N, std::vector<int>());
		while (!stk.empty())
		{
			int v = stk.top();
			stk.pop();
			if (dist[v] != INT_MIN)
			{
				for (int i = 0; i < N; ++i)
				{
					if (DAGadjMatrix[v][i] > 0)
						if (dist[i] < dist[v] + DAGadjMatrix[v][i])
						{
							dist[i] = dist[v] + DAGadjMatrix[v][i];
							paths[i] = paths[v];
							paths[i].push_back(v);
						}
				}
			}
		}
		Debug::Print2D<int>()(paths, false);
		std::cout << "LongestPathInDAG DFS for topologicalSort=\"" << topologicalSort << "\", dist From InDegree=0 Nodes: " << Debug::ToStr1D<int>()(dist) << std::endl;
	}
private:
	void DFS_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & DAGadjMatrix, int v, int & visitCount, std::vector<int> & visitIndex, std::stack<int> & stk)
	{
		int N = DAGadjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (DAGadjMatrix[v][i] > 0)
				if (visitIndex[i] == -1)
				{
					this->DFS_AdjacencyMatrix_Recur(DAGadjMatrix, i, visitCount, visitIndex, stk);
				}
		}
		stk.push(v);
	}

public:
    int BFS(const std::vector<std::vector<int>> & DAG)
    {
	    int N = DAG.size();
	    std::vector<int> inDegree(N, 0);
	    for (auto i = 0; i < N; ++i)
	        for (auto j = 0; j < N; ++j)
	            if (DAG[i][j])
	                ++inDegree[j];

	    std::queue<int> que;
	    for (auto i = 0; i < N; ++i)
	        if (inDegree[i] == 0)
	            que.push(i);

	    int dist = 0;
	    while (!que.empty())
        {
	        int count = que.size();
	        while (count-- > 0)
            {
	            int cur = que.front();
	            que.pop();
	            for (auto nxt = 0; nxt < N; ++nxt)
	                if (DAG[cur][nxt])
                    {
	                    --inDegree[nxt];
	                    if (inDegree[nxt] == 0)
	                        que.push(nxt);
                    }
            }
	        ++dist;
        }
        Debug::Print2D<int>()(DAG, false);
        std::cout << "LongestPathInDAG BFS: " << dist << std::endl;
	    return dist;
    }
};
/*
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

[rY][cX]
Row#0	= 10, 8, 6, 3
Row#1	= 10, 9, 5,  
Row#2	= 10, 9, 5,  
Row#3	= 10, 8, 6,  
Row#4	= 10, 8, 6,  
Row#5	= 10, 9,  ,  
Row#6	= 10, 8,  ,  
Row#7	= 10, 9,  ,  
Row#8	= 10,  ,  ,  
Row#9	= 10,  ,  ,  
Row#10	=  ,  ,  ,  

LongestPathInDAG DFS for source="10", topologicalSort="0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10", distFromSource: 14, 18, 16, 10, 12, 15, 5, 14, 3, 9, 0

		   3     4
		1---->4---->6
	   2| \9  |7 4/ |5
	    |   \ | /   |
		v  5 vvv  3 v
		0---->3---->8
	   9|   / | \   |
		| /3  |8 9\ |4
		vv  6 v  5 vv
		2---->5---->7
[rY][cX]
Row#0	= 0, 0, 9, 5, 0, 0, 0, 0, 0
Row#1	= 2, 0, 0, 9, 3, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 6, 0, 0, 0
Row#3	= 0, 0, 3, 0, 0, 8, 0, 9, 3
Row#4	= 0, 0, 0, 7, 0, 0, 4, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 5, 0
Row#6	= 0, 0, 0, 4, 0, 0, 0, 0, 5
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 4, 0

[rY][cX]
Row#0	= 1,  ,  ,  ,  ,  
Row#1	=  ,  ,  ,  ,  ,  
Row#2	= 1, 4, 6, 3,  ,  
Row#3	= 1, 4, 6,  ,  ,  
Row#4	= 1,  ,  ,  ,  ,  
Row#5	= 1, 4, 6, 3, 2,  
Row#6	= 1, 4,  ,  ,  ,  
Row#7	= 1, 4, 6, 3, 2, 5
Row#8	= 1, 4, 6, 3,  ,  

LongestPathInDAG DFS for source="1", topologicalSort="7, 5, 2, 8, 3, 0, 6, 4, 1", distFromSource: 2, 0, 14, 11, 3, 20, 7, 25, 14

0->1->2->3->4->5
4->5
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 0, 0

[rY][cX]
Row#0	=  ,  ,  ,
Row#1	= 0,  ,  ,
Row#2	= 0, 1,  ,
Row#3	= 0, 1, 2,
Row#4	=  ,  ,  ,
Row#5	= 0, 1, 2, 3

LongestPathInDAG DFS for topologicalSort="5, 3, 2, 1, 0, 4", dist From InDegree=0 Nodes: 0, 1, 2, 3, 0, 4

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0
Row#3	= 0, 0, 0, 0, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 0, 0

LongestPathInDAG BFS: 5
*/
#endif