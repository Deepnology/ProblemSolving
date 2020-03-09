#ifndef GRAPH_SEARCH_H
#define GRAPH_SEARCH_H
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
Leetcode: Number of Connected Components in an Undirected Graph
http://www.seas.gwu.edu/~simhaweb/alg/lectures/module7/module7.html
1. Graph data structure
1)
AdjacencyMatrix
(use a 2D matrix)
(row i has "neighbor" info about vertex i)
Undirected: 
AdjacencyMatrix[i][j] = 1 iff there's an edge between vertices i and j. (or a value >= 1 to represent the weight(distance))
AdjacencyMatrix[i][j] = 0 otherwise.
AdjacencyMatrix[i][j] == AdjacencyMatrix[j][i] is convention for undirected graphs (diagonally symmetric)
Directed:
AdjacencyMatrix[i][j] = 1 iff there's an edge from i to j. (or a value >= 1 to represent the weight(distance))
AdjacencyMatrix[i][j] = 0 otherwise.
Advantages:
Simple to program.
Some matrix operations (multiplication) are useful in some applications (connectivity).
Efficient for dense (lots of edges) graphs.
2)
AdjacencyList
(use an array of vertex-lists)
(each vertex list is a list of neighbors for undirected graph)
(each vertex list is a list of out-going neighbors for directed graph)
Undirected:
AdjacencyList[i][j] = (d, v) means vertex i's j-th neighbor vertex is v and the weight(distance) between vertex i and vertex v is d.
Directed:
AdjacencyList[i][j] = (d, v) means vertex i's j-th out-going neighbor vertex is v and the weight(distance) from vertex i to vertex v is d.
(Convention: in each list, keep vertices in order of insertion => add to rear of list)
Advantages:
Less storage for sparse (few edges) graphs.
Easy to store additional information in the data structure. (e.g., vertex degree, edge weight)

2. BFS for Undirected
w/ adjacency matrix: O(V^2+E) = O(V^2)
w/ adjacency list: O(V+E) = O(E)

(BFS for Directed is same as for Undirected)

3. DFS for Undirected
A graph with no back edges revealed by DFS is an acyclic graph.
Down edges are useful in identifying so-called articulation edges.

DFS is most often used for identifying connected components in an undirected graph.

w/ adjacency matrix: O(V^2)
w/ adjacency list: O(V+E)

4. DFS for Directed
Back or down edge: when the vertex on the other side is "visited" but not yet "completed"
Cross edge: when the vertex on the other side is "completed"

w/ adjacency matrix: O(V^2)
w/ adjacency list: O(V+E)
*/
class GraphSearch
{
public:
	GraphSearch(){}
	~GraphSearch(){}
	void BFS_Undirected_AdjacencyMatrix(const std::vector<std::vector<int>> & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
				this->BFS_Undirected_AdjacencyMatrix_Iterate(adjMatrix, i, visitCount, visitIndex);
		}
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "GraphSearch BFS_Undirected_AdjacencyMatrix VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << std::endl;
	}
	void BFS_Undirected_AdjacencyMatrix_Iterate(const std::vector<std::vector<int>> & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex)
	{
		int N = adjMatrix.size();
		int M = adjMatrix[0].size();//should be equal to N
		std::queue<int> que;
		que.push(v);
		while (!que.empty())
		{
			v = que.front();
			que.pop();
			if (visitIndex[v] != -1)//if not mark visited before enqueue: check AGAIN if visited before visiting it
				continue;
			visitIndex[v] = ++visitCount;//visit it (mark visited)
			for (int i = 0; i < M; ++i)
			{
				if (adjMatrix[v][i] > 0 && i != v)
					if (visitIndex[i] == -1)
						que.push(i);//not mark visited before enqueue (the vertices in que might have duplicates)
			}
		}
	}

	void DFS_Undirected_AdjacencyMatrix(const std::vector<std::vector<int>> & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> completionIndex(N, -1);
		int completionCount = -1;

		std::vector<std::pair<int, std::pair<int, int> > > treeEdges;
		std::vector<std::pair<int, std::pair<int, int> > > backEdges;
		std::vector<std::pair<int, std::pair<int, int> > > downEdges;
		std::vector<std::pair<int, std::pair<int, int> > > crossEdges;

		std::vector<int> componentLabel(N, -1);
		int curComponentLabel = -1;

		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curComponentLabel;
				this->DFS_Undirected_AdjacencyMatrix_Recur(adjMatrix, -1, i, visitCount, visitIndex, completionCount, completionIndex,
					treeEdges, backEdges, downEdges,
					curComponentLabel, componentLabel);
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TreeEdges: " << Debug::ToStr1D<int>()(treeEdges) << std::endl;
		std::cout << "BackEdges: " << Debug::ToStr1D<int>()(backEdges) << std::endl;
		std::cout << "DownEdges: " << Debug::ToStr1D<int>()(downEdges) << std::endl;
		std::cout << "CrossEdges: " << Debug::ToStr1D<int>()(crossEdges) << std::endl;
		std::cout << "GraphSearch DFS_Undirected_AdjacencyMatrix VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << "; CompletionIndex: " << Debug::ToStr1D<int>()(completionIndex) 
			<< "; ComponentLabel: " << Debug::ToStr1D<int>()(componentLabel) << std::endl;
	}
	void DFS_Undirected_AdjacencyMatrix_Recur(const std::vector<std::vector<int>> & adjMatrix, int from, int v,
		int & visitCount, std::vector<int> & visitIndex, int & completionCount, std::vector<int> & completionIndex,
		std::vector<std::pair<int, std::pair<int, int>>> & treeEdges, std::vector<std::pair<int, std::pair<int, int>>> & backEdges, std::vector<std::pair<int, std::pair<int, int>>> & downEdges,
		int & curComponentLabel, std::vector<int> & componentLabel)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		componentLabel[v] = curComponentLabel;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					treeEdges.push_back({ adjMatrix[v][i], {v, i} });
					this->DFS_Undirected_AdjacencyMatrix_Recur(adjMatrix, v, i, visitCount, visitIndex, completionCount, completionIndex,
						treeEdges, backEdges, downEdges,
						curComponentLabel, componentLabel);
				}
				else if (i != from)
				{
					if (visitIndex[i] < visitIndex[v])
						backEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a back edge
					else
						downEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a down edge
				}
			}
		}
		completionIndex[v] = ++completionCount;
	}

	void DFS_Directed_AdjacencyMatrix(const std::vector<std::vector<int>> & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> completionIndex(N, -1);
		int completionCount = -1;

		std::vector<std::pair<int, std::pair<int, int>>> treeEdges;
		std::vector<std::pair<int, std::pair<int, int>>> backEdges;
		std::vector<std::pair<int, std::pair<int, int>>> downEdges;
		std::vector<std::pair<int, std::pair<int, int>>> crossEdges;

		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				this->DFS_Directed_AdjacencyMatrix_Recur(adjMatrix, -1, i, visitCount, visitIndex, completionCount, completionIndex,
					treeEdges, backEdges, downEdges, crossEdges);
			}
		}
		Debug::Print2D<int>()(adjMatrix, false);
		std::cout << "TreeEdges: " << Debug::ToStr1D<int>()(treeEdges) << std::endl;
		std::cout << "BackEdges: " << Debug::ToStr1D<int>()(backEdges) << std::endl;
		std::cout << "DownEdges: " << Debug::ToStr1D<int>()(downEdges) << std::endl;
		std::cout << "CrossEdges: " << Debug::ToStr1D<int>()(crossEdges) << std::endl;
		std::cout << "GraphSearch DFS_Directed_AdjacencyMatrix VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << "; CompletionIndex: " << Debug::ToStr1D<int>()(completionIndex) << std::endl;
	}
	void DFS_Directed_AdjacencyMatrix_Recur(const std::vector<std::vector<int>> & adjMatrix, int from, int v,
		int & visitCount, std::vector<int> & visitIndex, int & completionCount, std::vector<int> & completionIndex,
		std::vector<std::pair<int, std::pair<int, int>>> & treeEdges, std::vector<std::pair<int, std::pair<int, int>>> & backEdges, std::vector<std::pair<int, std::pair<int, int>>> & downEdges, std::vector<std::pair<int, std::pair<int, int>>> & crossEdges)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0) //&& i != v)//directed graph can have vertex's self pointed edges
			{
				if (visitIndex[i] == -1)
				{
					treeEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a tree edge
					this->DFS_Directed_AdjacencyMatrix_Recur(adjMatrix, v, i, visitCount, visitIndex, completionCount, completionIndex,
						treeEdges, backEdges, downEdges, crossEdges);
				}
				else// if (i != from)//directed graph can differentiate an edge between 2 vertices into 2 different directional edges
				{
					if (completionIndex[i] == -1)//not finished processing i yet
					{
						backEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a back edge
					}
					else if (visitIndex[i] > visitIndex[v])
					{
						downEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a down edge
					}
					else
					{
						crossEdges.push_back({ adjMatrix[v][i], {v, i} });//(v, i) is a cross edge
					}
				}
			}
		}
		completionIndex[v] = ++completionCount;
	}
};
/*
		1      3----4
		|     / \
		0----2   6
		      \
		       5----7

[rY][cX]
Row#0	= 0, 1, 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 1, 0, 0, 0, 0
Row#5	= 0, 0, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

GraphSearch BFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 5, 4, 6, 7
[rY][cX]
Row#0	= 0, 1, 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 1, 0, 0, 0, 0
Row#5	= 0, 0, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

TreeEdges: [1,(0,1)], [1,(0,2)], [1,(2,3)], [1,(3,4)], [1,(3,6)], [1,(2,5)], [1,(5,7)]
BackEdges:
DownEdges:
CrossEdges:
GraphSearch DFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 6, 5, 7; CompletionIndex: 7, 0, 6, 3, 1, 5, 2, 4; ComponentLabel: 0, 0, 0, 0, 0, 0, 0, 0


		      2-----3-----------
		          /   \         |
		        /       \       |
		4-----10----9-----8     1
		|     | \   |   /     /
		|     |   \ | /     /
		5-----6-----7-----0

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1
Row#7	= 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1
Row#10	= 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0

GraphSearch BFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 8, 3, 10, 9, 4, 2, 5, 6, 7
[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0
Row#1	= 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1
Row#4	= 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
Row#5	= 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0
Row#6	= 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1
Row#7	= 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1
Row#8	= 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1
Row#10	= 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0

TreeEdges: [1,(0,1)], [1,(1,3)], [1,(3,2)], [1,(3,8)], [1,(8,7)], [1,(7,6)], [1,(6,5)], [1,(5,4)], [1,(4,10)], [1,(10,9)]
BackEdges: [1,(7,0)], [1,(10,3)], [1,(10,6)], [1,(10,7)], [1,(9,7)], [1,(9,8)]
DownEdges: [1,(6,10)], [1,(7,9)], [1,(7,10)], [1,(8,9)], [1,(3,10)], [1,(0,7)]
CrossEdges:
GraphSearch DFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 3, 2, 8, 7, 6, 5, 4, 10, 9; CompletionIndex: 10, 9, 0, 8, 3, 4, 5, 6, 7, 1, 2; ComponentLabel: 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0


		            3----4----6
		           /
		0----1----2
		           \
				    5----7

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 1, 0, 1, 0, 0, 0, 0, 0
Row#2	= 0, 1, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0
Row#5	= 0, 0, 1, 0, 0, 0, 0, 1
Row#6	= 0, 0, 0, 0, 1, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

TreeEdges: [1,(0,1)], [1,(1,2)], [1,(2,3)], [1,(3,4)], [1,(4,6)], [1,(2,5)], [1,(5,7)]
BackEdges:
DownEdges:
CrossEdges:
GraphSearch DFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 6, 5, 7; CompletionIndex: 7, 6, 5, 2, 1, 4, 0, 3; ComponentLabel: 0, 0, 0, 0, 0, 0, 0, 0


		   -----    3----4----6
		 /       \ /        /
		0----1----2      /
		           \  /
		            5----7

[rY][cX]
Row#0	= 0, 1, 1, 0, 0, 0, 0, 0
Row#1	= 1, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 1, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 1, 0, 1, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0, 1, 0
Row#5	= 0, 0, 1, 0, 0, 0, 1, 1
Row#6	= 0, 0, 0, 0, 1, 1, 0, 0
Row#7	= 0, 0, 0, 0, 0, 1, 0, 0

TreeEdges: [1,(0,1)], [1,(1,2)], [1,(2,3)], [1,(3,4)], [1,(4,6)], [1,(6,5)], [1,(5,7)]
BackEdges: [1,(2,0)], [1,(5,2)]
DownEdges: [1,(2,5)], [1,(0,2)]
CrossEdges:
GraphSearch DFS_Undirected_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 6, 5, 7; CompletionIndex: 7, 6, 5, 4, 3, 1, 2, 0; ComponentLabel: 0, 0, 0, 0, 0, 0, 0, 0


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

TreeEdges: [1,(0,1)], [1,(1,2)], [1,(2,3)], [1,(3,4)], [1,(4,6)], [1,(2,5)], [1,(5,7)]
BackEdges: [1,(2,0)], [1,(6,3)], [1,(7,7)]
DownEdges: [1,(3,6)]
CrossEdges: [1,(5,3)]
GraphSearch DFS_Directed_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 6, 5, 7; CompletionIndex: 7, 6, 5, 2, 1, 4, 0, 3


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

TreeEdges: [1,(0,1)], [1,(1,2)], [1,(3,4)], [1,(4,5)], [1,(5,6)]
BackEdges: [1,(2,0)], [1,(4,3)], [1,(6,5)], [1,(7,7)]
DownEdges: 
CrossEdges: [1,(3,1)], [1,(3,2)], [1,(5,2)], [1,(7,4)], [1,(7,6)]
GraphSearch DFS_Directed_AdjacencyMatrix VisitIndex: 0, 1, 2, 3, 4, 5, 6, 7; CompletionIndex: 2, 1, 0, 6, 5, 4, 3, 7
*/
#endif