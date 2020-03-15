#ifndef EULERIAN_GRAPH_H
#define EULERIAN_GRAPH_H
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
#include "../Tarjan/BridgesInGraph.h"
/*
http://www.geeksforgeeks.org/eulerian-path-and-circuit/
http://en.wikipedia.org/wiki/Euler_path
http://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/
Eulerian graph: if it has an Eulerian circuit
Semi-Eulerian graph: if it has an Eulerian trail

Eulerian trail: a path that traverses all EDGES exactly once
Eulerian circuit: a cycle that traverses all EDGES exactly once (but may repeat vertices)

Undierected graph:

	Eulerian trail: 
		iff at most 2 vertices have odd degree, and if all of its vertices with nonzero degree belong to a single connected component
		a) All vertices with non-zero degree are connected.
		   (We don't care about vertices with zero because they don't belong to Eulerian path. We only consider all edges.)
		b) 0 or 2 vertices have odd degree and all other vertices have even degree.
		   (Note that only 1 vertex with odd degree is not possible in an undirected graph. Sum of all degree is always even in an undirected graph.)

	Eulerian circuit: 
		iff every vertex has even degree, and all of its vertices with nonzero degree belong to a single connected component
		a) same as above
		b) Every vertex has even degree.

Directed graph:

	Eulerian directed trail: 
		iff at most 1 vertex has (out-degree) - (in-degree) = 1, at most 1 vertex has (in-degree) - (out-degree) = 1, every other vertex has equal in-degree and out-degree, and all of its vertices with nonzero degree belong to a single connected component
		a) same as above
		b) 0 or 1 vertex has (out-degree) - (in-degree) = 1.
		c) 0 or 1 vertex has (in-degree) - (out-degree) = 1.
		d) Every other vertex has equal in-dgree and out-degree.

	Eulerian directed circuit: 
		iff every vertex has equal in degree and out degree, and all of its vertices with nonzero degree belong to a single strongly connected component
		a) All vertices with non-zero degree are strongly connected.
		b) Every vertex has equal in-degree and out-degree.
O(V+E) time
*/
class EulerianGraph
{
public:
	EulerianGraph(){}
	~EulerianGraph(){}
	//I. Determine Eulerian for Undirected graph
	void Undirected_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> componentLabel(N, -1);
		int curComponentLabel = -1;
		std::vector<int> degree(N, 0);//edge (neighbor vertex) count of each vertex

		//compute degree and componentLabel for each vertex
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curComponentLabel;
				this->DFS_Undirected_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, degree, curComponentLabel, componentLabel);
			}
		}

		//1. check if all vertices with non-zero degree in this graph are connected
		bool isConnected = true;
		bool firstNonZeroDegree = true;
		int nonZeroDegreeComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i] > 0)
			{
				if (firstNonZeroDegree)
				{
					firstNonZeroDegree = false;
					nonZeroDegreeComponentLabel = componentLabel[i];
				}
				else
				{
					if (componentLabel[i] != nonZeroDegreeComponentLabel)//found a vertex with non-zero degree that has a diff component label
					{
						isConnected = false;
						break;
					}
				}
			}
		}

		//2. count vertices with odd degree
		int oddDegreeVertexCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i] & 1)
				++oddDegreeVertexCount;
		}

		//3. determine Eulerian for UNDIRECTED graph based on isConnected && oddDegreeVertexCount
		std::ostringstream oss;
		if (isConnected)
		{
			if (oddDegreeVertexCount > 2)
				oss << "not Eulerian";
			else if (oddDegreeVertexCount == 2)
				oss << "Semi-Eulerian (has Eulerian Path)";
			else if (oddDegreeVertexCount == 0)
				oss << "Eulerian (has Eulerian Cycle)";
			else
				throw std::runtime_error("Invalid Odd Degree Vertex Count");
		}
		else
			oss << "not Eulerian";

		Debug::Print2D<int>()(adjMatrix, false);
		//std::cout << "VisitIndex: " << Debug::ToStr1D<int>()(visitIndex) << "; ComponentLabel: " << Debug::ToStr1D<int>()(componentLabel) << "; Degree: " << Debug::ToStr1D<int>()(degree) << std::endl;
		std::cout << "EulerianGraph Undirected_AdjacencyMatrix IsConnected: " << isConnected << ", OddDegreeVertices: " << oddDegreeVertexCount << " => " << oss.str() << std::endl;
	}
private:
	void DFS_Undirected_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v, 
		int & visitCount, std::vector<int> & visitIndex, std::vector<int> & degree,
		int & curComponentLabel, std::vector<int> & componentLabel)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		componentLabel[v] = curComponentLabel;
		int edgeCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					this->DFS_Undirected_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, degree, curComponentLabel, componentLabel);
				}
				++edgeCount;
			}
		}
		degree[v] = edgeCount;
	}

	//II. Determine Eulerian for Directed graph
public:
	void Directed_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> strongComponentLabel(N, -1);
		int curStrongComponentLabel = -1;
		std::vector<int> lowestReachable(N, N);
		std::stack<int> stk;
		std::vector<std::pair<int, int> > degree(N, std::make_pair(0, 0));//first: in-degree, second: out-degree

		//compute in/out degree and strongComponentLabel for each vertex
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curStrongComponentLabel;
				this->DFS_Directed_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, degree, curStrongComponentLabel, strongComponentLabel, lowestReachable, stk);
			}
		}
		//1.1 check if all vertices with non-zero degree in this graph are strongly connected
		bool isStronglyConnected = true;
		bool firstNonZeroDegree = true;
		int nonZeroDegreeStrongComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first + degree[i].second > 0)//in-degree + out-degree > 0
			{
				if (firstNonZeroDegree)
				{
					firstNonZeroDegree = false;
					nonZeroDegreeStrongComponentLabel = strongComponentLabel[i];
				}
				else
				{
					if (strongComponentLabel[i] != nonZeroDegreeStrongComponentLabel)//found a vertex with non-zero degree that has a diff strong component label
					{
						isStronglyConnected = false;
						break;
					}
				}
			}
		}
		//compute weakComponentLabel for each vertex
		std::vector<int> undirectedVisitIndex(N, -1);
		int undirectedVisitCount = -1;
		std::vector<int> weakComponentLabel(N, -1);
		int curWeakComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (undirectedVisitIndex[i] == -1)
			{
				++curWeakComponentLabel;
				this->UndirectedDFS_Directed_AdjacencyMatrix_Recur(adjMatrix, i, undirectedVisitCount, undirectedVisitIndex, curWeakComponentLabel, weakComponentLabel);
			}
		}
		//1.2 check if all vertices with non-zero degree in this graph are weakly connected
		bool isWeaklyConnected = true;
		firstNonZeroDegree = true;
		int nonZeroDegreeWeakComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first + degree[i].second > 0)//in-degree + out-degree > 0
			{
				if (firstNonZeroDegree)
				{
					firstNonZeroDegree = false;
					nonZeroDegreeWeakComponentLabel = weakComponentLabel[i];
				}
				else
				{
					if (weakComponentLabel[i] != nonZeroDegreeWeakComponentLabel)//found a vertex with non-zero degree that has a diff weak component label
					{
						isWeaklyConnected = false;
						break;
					}
				}
			}
		}
		//2. count vertices with (in-degree != out-degree), vertices with (in-degree - out-degree) == 1, and vertices with (out-degree - in-degree) == 1
		int diffInOutDegreeCount = 0;
		int inDegreeOneMoreCount = 0;
		int outDegreeOneMoreCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first != degree[i].second)//in-degree != out-degree
			{
				++diffInOutDegreeCount;
				if (degree[i].first - degree[i].second == 1)//in-degree - out-degree == 1
					++inDegreeOneMoreCount;
				if (degree[i].second - degree[i].first == 1)//out-degree - in-degree == 1
					++outDegreeOneMoreCount;
			}
		}
		
		//3. determine Eulerian for DIRECTED graph based on (isStronglyConnected && diffInOutDegreeCount) and (isWeaklyConnected && inDegreeOneMoreCount && outDegreeOneMoreCount && diffInOutDegreeCount)
		std::ostringstream oss;
		if (isStronglyConnected && diffInOutDegreeCount == 0)
			oss << "Eulerian (has Eulerian Directed Cycle)";
		else if (isWeaklyConnected &&
				(inDegreeOneMoreCount == 0 || inDegreeOneMoreCount == 1) &&
				(outDegreeOneMoreCount == 0 || outDegreeOneMoreCount == 1) &&
				(inDegreeOneMoreCount + outDegreeOneMoreCount == diffInOutDegreeCount))
			oss << "Semi-Eulerian (has Eulerian Directed Path)";
		else
			oss << "not Eulerian";
		Debug::Print2D<int>()(adjMatrix, false);
		//std::cout << "Degree: " << Debug::ToStr1D<int>()(degree) << "; StrongComponentLabel: " << Debug::ToStr1D<int>()(strongComponentLabel) << "; WeakComponentLabel: " << Debug::ToStr1D<int>()(weakComponentLabel) << std::endl;
		std::cout << "EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: " << isStronglyConnected << "; IsWeaklyConnected: " << isWeaklyConnected << "; DiffInOutDegreeCount: " << diffInOutDegreeCount << "; InDegreeOneMoreCount: " << inDegreeOneMoreCount << "; OutDegreeOneMoreCount: " << outDegreeOneMoreCount << " => " << oss.str() << std::endl;
	}
private:
	//Tarjan's strongly connected components algorithm
	void DFS_Directed_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v,
		int & visitCount, std::vector<int> & visitIndex, std::vector<std::pair<int, int> > & degree,
		int & curStrongComponentLabel, std::vector<int> & strongComponentLabel, std::vector<int> & lowestReachable, std::stack<int> & stk)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		lowestReachable[v] = visitIndex[v];
		int adjMinLowestReachable = lowestReachable[v];//adjMinLowestReachable: the lowest reachable vertex of all v's adjacent vertices
		stk.push(v);
		
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					this->DFS_Directed_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, degree, curStrongComponentLabel, strongComponentLabel, lowestReachable, stk);
				}
				if (lowestReachable[i] < adjMinLowestReachable)
					adjMinLowestReachable = lowestReachable[i];
			}
			if (adjMatrix[v][i] > 0)//there exist an edge from v to i
			{
				++degree[v].second;//out-degree of v
				++degree[i].first;//in-degree of i
			}
		}

		if (adjMinLowestReachable < lowestReachable[v])//1. v's descendants on DFS path have at least one back edge to v's ancestors
		{
			lowestReachable[v] = adjMinLowestReachable;
		}
		else//2. v's descendants on DFS path don't have any back edge to any of v's ancestors
		{
			//pop out all v's descendants and v from stack, and assign them a new component label
			int cur;
			do
			{
				cur = stk.top();
				stk.pop();
				strongComponentLabel[cur] = curStrongComponentLabel;
				lowestReachable[cur] = N;
			} while (cur != v);
			++curStrongComponentLabel;
		}
	}
	void UndirectedDFS_Directed_AdjacencyMatrix_Recur(const std::vector<std::vector<int> > & adjMatrix, int v,
		int & visitCount, std::vector<int> & visitIndex,
		int & curWeakComponentLabel, std::vector<int> & weakComponentLabel)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		weakComponentLabel[v] = curWeakComponentLabel;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0 && i != v)//out-degree edge of vertex v
			{
				if (visitIndex[i] == -1)
				{
					this->UndirectedDFS_Directed_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, curWeakComponentLabel, weakComponentLabel);
				}
			}
			if (adjMatrix[i][v] > 0 && i != v)//in-degree edge of vertex v (since adjMatrix is directed, we also need to check reversed edge when running undirected DFS)
			{
				if (visitIndex[i] == -1)
				{
					this->UndirectedDFS_Directed_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, curWeakComponentLabel, weakComponentLabel);
				}
			}
		}
	}

	//III. Find Euler Path for Undirected graph
	//a graph that has a Euler path must be:
	//1. all vertices with non-zero degree are connected
	//2. 0 or 2 vertices have odd degree and all other vertices have even degree
public:
	std::vector<std::pair<int, int> > Fleury_FindEulerPath_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & EulerAdjMatrix)
	{
		int N = EulerAdjMatrix.size();
		//1. find the first vertex with odd degree if possible, otherwise, find any vertex with non-zero degree
		int vOddDegree;
		int vNonZeroDegree = -1;
		for (vOddDegree = 0; vOddDegree < N; ++vOddDegree)
		{
			int adjCount = 0;
			for (int i = 0; i < N; ++i)
				if (i != vOddDegree && EulerAdjMatrix[vOddDegree][i] != 0)
					++adjCount;
			if (vNonZeroDegree == -1 && adjCount > 0)//found first vertex with non zero degree
				vNonZeroDegree = vOddDegree;
			if (adjCount & 1)//found first vertex with odd degree
				break;
		}
		int headVertex = vOddDegree == N ? vNonZeroDegree : vOddDegree;
		//std::cout << "vOddDegree: " << vOddDegree << ", vNonZeroDegree: " << vNonZeroDegree << " => headVertex: " << headVertex << std::endl;

		//2. DFS find Euler path from head vertex and with a copied graph that can remove edges
		std::vector<std::vector<int> > copy(EulerAdjMatrix);
		std::vector<std::pair<int, int> > path;
		this->dFS_Fleury_FindEulerPath_UndirectedAdjacencyMatrix(copy, headVertex, path);
		std::cout << "EulerianGraph Fleury_FindEulerPath_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(path) << std::endl;
		return path;
	}
private:
	void dFS_Fleury_FindEulerPath_UndirectedAdjacencyMatrix(std::vector<std::vector<int> > & adjMatrix, int v, std::vector<std::pair<int, int> > & path)
	{
		int N = adjMatrix.size();
		for (int i = 0; i < N; ++i)
			if (i != v && adjMatrix[v][i] != 0)
			{
				int adjCount = 0;
				for (int ii = 0; ii < N; ++ii)
					if (ii != v && adjMatrix[v][ii] != 0)
						++adjCount;

				//2 cases for choosing next adj vertex for Euler path:
				//1. if i is the only adj vertex of v
				//2. if there are multiple adj vertices, choose the non-bridge
				if (adjCount == 1 || !BridgesInGraph().Valid_DFS_ConnectedUndirectedAdjacencyMatrix(adjMatrix, v, i))
				{
					path.push_back(std::make_pair(v, i));
					adjMatrix[v][i] = 0;//remove edge (v, i)
					adjMatrix[i][v] = 0;//remove edge (i, v)
					this->dFS_Fleury_FindEulerPath_UndirectedAdjacencyMatrix(adjMatrix, i, path);
				}
			}
	}

public:
	//IV. Find Euler Path for Directed Graph using Hierholzer Algorithm in a single connected component
	void Hierholzer_FindEulerPath_ConnectedDiGraph(const std::vector<std::vector<int>> & adjM)
	{
		std::unordered_map<int,std::unordered_set<int>> DiG;
		int N = adjM.size();
		int totalEdges = 0;
		for (int i = 0; i < N; ++i)
		{
		    DiG.insert({i,{}});
			for (int j = 0; j < N; ++j)
			{
				if (adjM[i][j]) //might have self-cycle
				{
					DiG[i].insert(j);
					++totalEdges;
				}
			}
		}
		bool allEulerPaths = true;
		bool anyEulerPath = false;
		std::cout << "EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph: " << std::endl;
		for (auto & p : DiG)
		{
			std::unordered_map<int,std::unordered_set<int>> G(DiG);
			std::stack<int> stk;
			stk.push(p.first);
			std::vector<int> res;
			while (!stk.empty())
			{
				while (!G[stk.top()].empty())
				{
					int top = stk.top();
					stk.push(*G[top].begin());
					G[top].erase(G[top].begin());
				}
				int cur = stk.top();
				stk.pop();
				res.push_back(cur);
			}
			std::reverse(res.begin(), res.end());

			int numEdges = res.size()-1;
			bool containAllEdges = (numEdges==totalEdges);
			for (int i = 0; i < numEdges; ++i)
			{
				if (!DiG.count(res[i]) || !DiG[res[i]].count(res[i+1]))
				{
					containAllEdges = false;
					break;
				}
			}
			anyEulerPath |= containAllEdges;
			allEulerPaths &= containAllEdges;
			std::cout << "EulerPath@" << p.first << " [" << Debug::ToStr1D<int>()(res) << "]: " << containAllEdges << std::endl;
		}
		std::cout << "AnyEulerPath: " << anyEulerPath << ", AllEulerPaths(EulerCircuit): " << allEulerPaths << std::endl;
	}
};
/*
		1---0---3   5
		| /     |
		2       4

[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0
Row#1	= 1, 0, 1, 0, 0, 0
Row#2	= 1, 1, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 1, 0
Row#4	= 0, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Undirected_AdjacencyMatrix IsConnected: 1, OddDegreeVertices: 2 => Semi-Eulerian (has Eulerian Path)
EulerianGraph Fleury_FindEulerPath_UndirectedAdjacencyMatrix: [0,1], [1,2], [2,0], [0,3], [3,4]


		1---0---3   5
		| /   \ |
		2       4

[rY][cX]
Row#0	= 0, 1, 1, 1, 1, 0
Row#1	= 1, 0, 1, 0, 0, 0
Row#2	= 1, 1, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 1, 0
Row#4	= 1, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Undirected_AdjacencyMatrix IsConnected: 1, OddDegreeVertices: 0 => Eulerian (has Eulerian Cycle)
EulerianGraph Fleury_FindEulerPath_UndirectedAdjacencyMatrix: [0,1], [1,2], [2,0], [0,3], [3,4], [4,0]


		   ---
		 /     \
		1---0---3   5
		| /     |
		2       4

[rY][cX]
Row#0	= 0, 1, 1, 1, 0, 0
Row#1	= 1, 0, 1, 1, 0, 0
Row#2	= 1, 1, 0, 0, 0, 0
Row#3	= 1, 1, 0, 0, 1, 0
Row#4	= 0, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Undirected_AdjacencyMatrix IsConnected: 1, OddDegreeVertices: 4 => not Eulerian


		               -------
		              /       \
		             v         v
		   -----     3--->4--->6
		  /     \   ^^
		 v       \ / |
		0--->1--->2  |
		           \ |
		            v|
		             5--->7

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0, 0, 0
Row#2	= 1, 0, 0, 1, 0, 1, 0, 0
Row#3	= 0, 0, 0, 0, 1, 0, 1, 0
Row#4	= 0, 0, 0, 0, 0, 0, 1, 0
Row#5	= 0, 0, 0, 1, 0, 0, 0, 1
Row#6	= 0, 0, 0, 1, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0

EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: 0; IsWeaklyConnected: 1; DiffInOutDegreeCount: 5; InDegreeOneMoreCount: 3; OutDegreeOneMoreCount: 1 => not Eulerian
EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph:
EulerPath@7 [7]: 0
EulerPath@6 [6, 3, 6, 4, 6]: 0
EulerPath@5 [5, 7, 3, 4, 6, 3, 6]: 0
EulerPath@4 [4, 6, 3, 6, 4]: 0
EulerPath@3 [3, 4, 6, 3, 6]: 0
EulerPath@2 [2, 0, 1, 2, 3, 5, 7, 3, 4, 6, 3, 6]: 0
EulerPath@1 [1, 2, 3, 5, 7, 3, 4, 6, 3, 6, 0, 1]: 0
EulerPath@0 [0, 1, 2, 3, 5, 7, 3, 4, 6, 3, 6, 0]: 0
AnyEulerPath: 0, AllEulerPaths(EulerCircuit): 0


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

EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: 0; IsWeaklyConnected: 1; DiffInOutDegreeCount: 5; InDegreeOneMoreCount: 2; OutDegreeOneMoreCount: 0 => not Eulerian
EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph:
EulerPath@7 [7, 7, 6, 4, 3, 4, 5, 6, 5, 2, 2, 1, 2, 0, 1]: 0
EulerPath@6 [6, 5, 6, 2, 0, 1, 2]: 0
EulerPath@5 [5, 6, 5, 2, 0, 1, 2]: 0
EulerPath@4 [4, 3, 4, 5, 6, 5, 2, 2, 1, 2, 0, 1]: 0
EulerPath@3 [3, 4, 5, 6, 5, 2, 3, 2, 1, 2, 0, 1]: 0
EulerPath@2 [2, 0, 1, 2]: 0
EulerPath@1 [1, 2, 0, 1]: 0
EulerPath@0 [0, 1, 2, 0]: 0
AnyEulerPath: 0, AllEulerPaths(EulerCircuit): 0


		1<--0<--3   5
		|  ^    ^
		| /     |
		v/      |
		2       4

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0
Row#1	= 0, 0, 1, 0, 0, 0
Row#2	= 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: 0; IsWeaklyConnected: 1; DiffInOutDegreeCount: 2; InDegreeOneMoreCount: 1; OutDegreeOneMoreCount: 1 => Semi-Eulerian (has Eulerian Directed Path)
EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph:
EulerPath@4 [4, 3, 0, 1, 2, 0]: 1
EulerPath@3 [3, 0, 1, 2, 0]: 0
EulerPath@2 [2, 0, 1, 2]: 0
EulerPath@1 [1, 2, 0, 1]: 0
EulerPath@0 [0, 1, 2, 0]: 0
AnyEulerPath: 1, AllEulerPaths(EulerCircuit): 0


		1<--0<--3   5
		|  ^ \  ^
		| /   \ |
		v/     v|
		2       4

[rY][cX]
Row#0	= 0, 1, 0, 0, 1, 0
Row#1	= 0, 0, 1, 0, 0, 0
Row#2	= 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: 1; IsWeaklyConnected: 1; DiffInOutDegreeCount: 0; InDegreeOneMoreCount: 0; OutDegreeOneMoreCount: 0 => Eulerian (has Eulerian Directed Cycle)
EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph:
EulerPath@4 [4, 3, 0, 1, 2, 0, 4]: 1
EulerPath@3 [3, 0, 1, 2, 0, 4, 3]: 1
EulerPath@2 [2, 0, 4, 3, 0, 1, 2]: 1
EulerPath@1 [1, 2, 0, 4, 3, 0, 1]: 1
EulerPath@0 [0, 1, 2, 0, 4, 3, 0]: 1
AnyEulerPath: 1, AllEulerPaths(EulerCircuit): 1


		   ----
		  /    \
		 /      v
		1<--0<--3   5
		|  ^    ^
		| /     |
		v/      |
		2       4

[rY][cX]
Row#0	= 0, 1, 0, 0, 0, 0
Row#1	= 0, 0, 1, 1, 0, 0
Row#2	= 1, 0, 0, 0, 0, 0
Row#3	= 1, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 1, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0

EulerianGraph Directed_AdjacencyMatrix IsStronglyConnected: 0; IsWeaklyConnected: 1; DiffInOutDegreeCount: 4; InDegreeOneMoreCount: 2; OutDegreeOneMoreCount: 2 => not Eulerian
EulerianGraph Hierholzer_FindEulerPath_ConnectedDiGraph:
EulerPath@4 [4, 3, 0, 1, 3, 2, 0]: 0
EulerPath@3 [3, 0, 1, 3, 2, 0]: 0
EulerPath@2 [2, 0, 1, 3, 0, 2]: 0
EulerPath@1 [1, 2, 0, 1, 3, 0]: 0
EulerPath@0 [0, 1, 3, 0, 2, 0]: 0
AnyEulerPath: 0, AllEulerPaths(EulerCircuit): 0
*/
#endif