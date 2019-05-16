#ifndef CONNECT_ALL_STR_IN_CHAIN_H
#define CONNECT_ALL_STR_IN_CHAIN_H
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
http://stackoverflow.com/questions/17706124/given-an-array-of-strings-return-true-if-each-string-could-be-connected-to-othe
http://www.careercup.com/question?id=6362892580421632
http://stackoverflow.com/questions/9268709/detecting-when-matrix-multiplication-is-possible/9268893#9268893
Given an array of strings.
A chain of two strings can be connected if the last char of one string matches the first char of the other.
Determine if all the strings can be connected in one chain.
Example:
"abc", "cde", "cad", "def", "eac" can be connected in a chain:
"abc"->"cde"->"eac"->"cad"->"def"
Solution:
Create a directed graph from the strings.
The vertices of the graph are the 26 letters.
The edge between two letters represents an existing string with starting and ending letters, respectively.
If an Eulerian path exists in the directed graph, all the string can be connected in a chain.

can be solved using topological sort, see also UniqueSequenceReconstructable.h
*/
class ConnectAllStrInChain
{
public:
	ConnectAllStrInChain(){}
	~ConnectAllStrInChain(){}

	bool ExistEulerPathInDigraph(const std::vector<std::string> & strs)
	{
		int N = 26;
		std::vector<std::vector<int> > adjMatrix(N, std::vector<int>(N, 0));//adjacency matrix for directed graph

		int strCount = strs.size();
		for (int i = 0; i < strCount; ++i)
		{
			std::string str = strs[i];
			adjMatrix[str.front() - 'a'][str.back() - 'a'] = 1;
		}

		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::vector<int> componentLabel(N, -1);
		int curComponentLabel = -1;
		std::vector<std::pair<int, int> > degree(N, std::make_pair(0, 0));//first: in-degree, second: out-degree
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				++curComponentLabel;
				this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
		}
		//1. determine if all non-zero degree vertices in the graph are weakly connected
		bool isWeaklyConnected = true;
		bool firstNonZeroDegree = true;
		int weakComponentLabel = -1;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first + degree[i].second > 0)
			{
				if (firstNonZeroDegree)
				{
					firstNonZeroDegree = false;
					weakComponentLabel = componentLabel[i];
				}
				else
				{
					if (componentLabel[i] != weakComponentLabel)
					{
						isWeaklyConnected = false;
						break;
					}
				}
			}
		}
		//2. count vertices with diff in/out degree and vertices with difference btw in/out degree equals to 1
		int diffInOutDegreeCount = 0;
		int inDegreeOneMoreCount = 0;
		int outDegreeOneMoreCount = 0;
		for (int i = 0; i < N; ++i)
		{
			if (degree[i].first != degree[i].second)
			{
				++diffInOutDegreeCount;
				if (degree[i].first - degree[i].second == 1)
					++inDegreeOneMoreCount;
				if (degree[i].second - degree[i].first == 1)
					++outDegreeOneMoreCount;
			}
		}

		bool res;
		if (isWeaklyConnected &&
			(inDegreeOneMoreCount == 0 || inDegreeOneMoreCount == 1) &&
			(outDegreeOneMoreCount == 0 || outDegreeOneMoreCount == 1) &&
			(inDegreeOneMoreCount + outDegreeOneMoreCount == diffInOutDegreeCount))
			res = true;
		else
			res = false;
		//Debug::Print2D<int>()(adjMatrix, false);
		//std::cout << Debug::ToStr1D<int>()(degree) << std::endl;
		//std::cout << "WeaklyConnected: " << isWeaklyConnected << "; InDegreeOneMoreCount: " << inDegreeOneMoreCount << "; OutDegreeOneMoreCount: " << outDegreeOneMoreCount << "; DiffInOutDegreeCount: " << diffInOutDegreeCount << std::endl;
		std::cout << "ConnectAllStrInChain for \"" << Debug::ToStr1D<std::string>()(strs) << "\": " << res << std::endl;
		return res;
	}
	void UndirectedDFS_Directed_AdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int v, int & visitCount, std::vector<int> & visitIndex, 
		int & curComponentLabel, std::vector<int> & componentLabel, std::vector<std::pair<int, int> > & degree)
	{
		int N = adjMatrix.size();
		visitIndex[v] = ++visitCount;
		componentLabel[v] = curComponentLabel;
		for (int i = 0; i < N; ++i)
		{
			if (adjMatrix[v][i] > 0)//out-degree of vertex v, in-degree of vertex i
				++degree[i].first;
			if (adjMatrix[i][v] > 0)//in-degree of vertex v, out-degree of vertex i
				++degree[i].second;
			if (adjMatrix[v][i] > 0 && i != v)//out-degree of vertex v
			{
				if (visitIndex[i] == -1)
					this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
			if (adjMatrix[i][v] > 0 && i != v)//in-degree of vertex v (since adjMatrix is directed, we also need to check reversed edge when running undirected DFS)
			{
				if (visitIndex[i] == -1)
					this->UndirectedDFS_Directed_AdjacencyMatrix(adjMatrix, i, visitCount, visitIndex, curComponentLabel, componentLabel, degree);
			}
		}
	}
};
/*
		a-->c<->e
		    |
			v
			d-->f

ConnectAllStrInChain for "abc, cde, cad, def, eac": 1


		c-->e
		| /
		vv
		d-->f-->b

ConnectAllStrInChain for "fcb, cde, cad, def, ead": 0



		a<-->k--->l
		| ^   ^   |
		|  \   \  |
		|    \  \ |
		v      \ \v
		b--->c--->f<--
		|         |   |
		v          ---
		d

ConnectAllStrInChain for "bd, fk, ab, kl, cf, ff, fa, ak, ka, lf, bc": 1
*/
#endif