/*MEMO*/
#ifndef STRONGLY_CONNECTED_COMPONENTS_H
#define STRONGLY_CONNECTED_COMPONENTS_H
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
http://stanford.edu/~liszt90/acm/notebook.html
http://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
http://www.geeksforgeeks.org/strongly-connected-components/
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module7/module7.html
http://www.sanfoundry.com/java-program-tarjan-algorithm/
http://www.sanfoundry.com/java-program-kosaraju-algorithm/
In a directed graph, a strongly connected component is a set of vertices,
along with edges associated with those vertices,
such that there is a path from every vertex in that set to every other in that set.

Tarjan: O(V+E) time with 1 DFS traversal
in DFS traversal, for the vertex whose adjacent vertices don't have any back edge to ancestors or itself, use a stack to store and pop out all its descendants and itself, and assign a same strong component label
Kosaraju: O(V+E) time with 2 DFS traversals
1st DFS is to compute the reversed completionVertices order on a reversed adjMatrix
2nd DFS traverse in reversed completionVertices order on reversed adjMatrix, and the strong component label can be distinguished by each different DFS traversal, which is idential to the component label of an undirected graph

See also CutVerticesInGraph.h, BridgesInGraph.h, BiconnectedGraph.h
*/
class StronglyConnectedComponents
{
public:
	StronglyConnectedComponents(){}
	~StronglyConnectedComponents(){}

	std::vector<int> Tarjan_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;

		std::vector<int> strongComponentLabel(N, -1);
		int curStrongComponentLabel = -1;
		std::vector<int> lowestReachable(N, N);
		std::stack<int> stack;

		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curStrongComponentLabel;
				this->tarjan_DFS_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex,
					curStrongComponentLabel, strongComponentLabel, lowestReachable, stack);
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "StronglyConnectedComponents Tarjan_DFS_AdjacencyMatrix VisitIndex: " << Debug::ToStr1D<int>()(visitIndex)
			<< "; StrongComponentLabel: " << Debug::ToStr1D<int>()(strongComponentLabel) << std::endl;
		return strongComponentLabel;
	}
private:
	void tarjan_DFS_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex, 
		int & curStrongComponentLabel, std::vector<int> & strongComponentLabel, std::vector<int> & lowestReachable, std::stack<int> & stack)//most relevant vars to SCC
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;

		lowestReachable[v] = visitIndex[v];
		int adjMinLowestReachable = lowestReachable[v];//adjMinLowestReachable: the lowest reachable vertex of all v's adjacent vertices
		stack.push(v);

		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					this->tarjan_DFS_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, 
						curStrongComponentLabel, strongComponentLabel, lowestReachable, stack);
				}
				if (lowestReachable[i] < adjMinLowestReachable)
					adjMinLowestReachable = lowestReachable[i];
			}
		}

		if (adjMinLowestReachable < lowestReachable[v])//1. v's descendants on DFS path have at least one back edge to v's ancestors
		{
			lowestReachable[v] = adjMinLowestReachable;
		}
		else//2. v's descendants on DFS path don't have any back edge to any of v's ancestors
		{
			//pop out all v's descendants and v itself from stack, and assign them a new component label
			int cur;
			do
			{
				cur = stack.top();
				stack.pop();
				strongComponentLabel[cur] = curStrongComponentLabel;
				lowestReachable[cur] = N;
			} while (cur != v);
			++curStrongComponentLabel;
		}
	}


public:
	std::vector<int> Kosaraju_DFS_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> completionVertices;
		
		//1. compute reversed adjMatrix
		std::vector<std::vector<int> > reversed = this->transposeDirectedGraph_AdjacencyMatrix(adjMatrix);

		//2. compute reversed completionVertices array
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				this->kosaraju_DFS_AdajcencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, completionVertices);
		}
		std::vector<int> reversedCompletionVertices = completionVertices;
		std::reverse(reversedCompletionVertices.begin(), reversedCompletionVertices.end());
		
		std::vector<int>(N, -1).swap(visitIndex);
		visitCount = -1;
		std::vector<int> componentLabel(N, -1);
		int curComponentLabel = -1;

		//3. perform DFS in reversed completionVertices order on reversed adjMatrix
		for (int i = 0; i < N; ++i)
		{
			int v = reversedCompletionVertices[i];
			if (visitIndex[v] == -1)
			{
				++curComponentLabel;
				this->kosaraju_reverseDFS_AdajcencyMatrix_Recur(reversed, v, visitCount, visitIndex, reversedCompletionVertices, curComponentLabel, componentLabel);
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		//Debug::Print2D<int>()(reversed, false);
		std::cout << "StronglyConnectedComponents Kosaraju_DFS_AdjacencyMatrix StrongComponentLabel: " << Debug::ToStr1D<int>()(componentLabel) << std::endl;
		return componentLabel;
	}
private:
	void kosaraju_DFS_AdajcencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v, 
		int & visitCount, std::vector<int> & visitIndex, std::vector<int> & completionVertices)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					this->kosaraju_DFS_AdajcencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, completionVertices);
				}
			}
		}
		completionVertices.push_back(v);
	}
	void kosaraju_reverseDFS_AdajcencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v,
		int & visitCount, std::vector<int> & visitIndex, std::vector<int> & reversedCompletionVertices, 
		int & curComponentLabel, std::vector<int> & componentLabel)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		componentLabel[v] = curComponentLabel;
		for (int i = 0; i < N; ++i)
		{
			int r = reversedCompletionVertices[i];
			if (adjMatrix[v][r] > 0 && r != v)
			{
				if (visitIndex[r] == -1)
				{
					this->kosaraju_reverseDFS_AdajcencyMatrix_Recur(adjMatrix, r, visitCount, visitIndex, reversedCompletionVertices, curComponentLabel, componentLabel);
				}
			}
		}
	}
	std::vector<std::vector<int> > transposeDirectedGraph_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::vector<int> > res(N, std::vector<int>(N, 0));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				res[i][j] = adjMatrix[j][i];
			}
		}
		return res;
	}
};
/*
		                -------
		               /       \
					  v         v
		    -----     3--->4--->6
		   /     \   ^^
		  v       \ / |
		 0--->1--->2  |     ---
		            \ |    |   |
					 v|    v   |
		              5--->7---

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 0, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 0, 0, 0, 1, 0
Row#5	= 0, 0, 0, 1, 0, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1

StronglyConnectedComponents Tarjan_DFS_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 6, 5, 7; StrongComponentLabel: 3, 3, 3, 0, 0, 2, 0, 1
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 0, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 0, 0, 0, 1, 0
Row#5	= 0, 0, 0, 1, 0, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 1

StronglyConnectedComponents Kosaraju_DFS_AdjacencyMatrix StrongComponentLabel: 0, 0, 0, 3, 3, 1, 3, 2


		0<---2<---5<-->6
		|   ^^    ^    ^
		|  / |    |    |
		v /  |    |    |
		1<---3<-->4<---7<--
		               |   |
                        ---

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 1, 0, 0
Row#5	= 0, 0, 1, 0, 0, 0, 1, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 0
Row#7	= 0, 0, 0, 0, 1, 0, 1, 1

StronglyConnectedComponents Tarjan_DFS_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 5, 6, 7; StrongComponentLabel: 0, 0, 0, 3, 3, 2, 2, 5
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 1, 0, 0
Row#5	= 0, 0, 1, 0, 0, 0, 1, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 0
Row#7	= 0, 0, 0, 0, 1, 0, 1, 1

StronglyConnectedComponents Kosaraju_DFS_AdjacencyMatrix StrongComponentLabel: 3, 3, 3, 1, 1, 2, 2, 0
*/
#endif