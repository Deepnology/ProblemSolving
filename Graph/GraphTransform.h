#ifndef GRAPH_TRANSFORM_H
#define GRAPH_TRANSFORM_H
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

*/
class GraphTransform
{
public:
	GraphTransform(){}
	~GraphTransform(){}

	std::vector<std::pair<int, std::pair<int, int> > > Undirected_AdjacencyMatrixToEdgeList(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::pair<int, std::pair<int, int> > > edgeList;//weight, source, destination
		//diagonal is self vertex which can be ignored
		//we only need to record the upper right half of the diagonal of the adj matrix
		int diagonalNextRightIdx = 0;
		for (int i = 0; i < N; ++i)
		{
			++diagonalNextRightIdx;
			for (int j = diagonalNextRightIdx; j < N; ++j)
			{
				if (adjMatrix[i][j] > 0)
					edgeList.push_back(std::make_pair(adjMatrix[i][j], std::make_pair(i, j)));
			}
		}
		return edgeList;
	}
	std::vector<std::pair<int, std::pair<int, int> > > Directed_AdjacencyMatrixToEdgeList(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<std::pair<int, std::pair<int, int> > > edgeList;//weight, source, destination
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (adjMatrix[i][j] > 0)
					edgeList.push_back(std::make_pair(adjMatrix[i][j], std::make_pair(i, j)));
			}
		}
		return edgeList;
	}

};
#endif