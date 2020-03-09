#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H
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
WelshPowell: O(VlogV + V^2) time
http://mrsleblancsmath.pbworks.com/w/file/fetch/46119304/vertex%20coloring%20algorithm.pdf
Assign min number of diff colors to vertices in an undirected graph such that no two adjacent vertices share the same color.
It may not always give the best solution, but it will usually perform better than just coloring the vertices without a plan will.

1. sort all the vertices by their degrees in non-increasing order
2. assign a new color to the vertex with max degree, and all other non-adjacent vertices in non-increasing order of degree
, repeat this process untill all vertices have been colored

The idea is that, by starting with the vertices that have the highest degrees
, you will be able to take care of the vertices with the largest number of conflicts as early as possible.

Backtrack: O(V * m^V) time
http://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/
Determine if an undirected graph can be colored with at most C colors such that no two adjacent vertices share the same color.

Greedy: O(V^2 + E) time
http://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/
http://www.geeksforgeeks.org/graph-coloring-applications/

*/
class VertexColoring
{
public:
	VertexColoring(){}
	~VertexColoring(){}

	//WelshPowell guarantees min number of colors
	std::vector<std::pair<int, std::pair<int, int>>> WelshPowell_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		Debug::Print2D<int>()(adjMatrix, false);
		int N = adjMatrix.size();

		//1. sort all the vertices by degree
		std::vector<std::pair<int, std::pair<int, int> > > sortedDegree(N, std::make_pair(-1, std::make_pair(-1, -1)));//<vertexIndex, <vertexDegree, colorIndex> >
		for (int i = 0; i < N; ++i)
		{
			int degree = 0;
			for (int j = 0; j < N; ++j)
			{
				if (i != j && adjMatrix[i][j] != 0)
					++degree;
			}
			sortedDegree[i].first = i;
			sortedDegree[i].second.first = degree;
		}
		std::sort(sortedDegree.begin(), sortedDegree.end(), 
			[](const std::pair<int, std::pair<int, int> > & a, const std::pair<int, std::pair<int, int> > & b)->bool
		{
			return a.second.first > b.second.first;
		});//sortedDegree has degree in non-increasing order
		
		int coloredVertexCount = 0;
		int colorIndex = -1;

		//2. assign a new color to the vertex with max degree, and all other non-adjacent vertices
		//repeat this process until all vertices have been colored
		while (coloredVertexCount < N)
		{
			++colorIndex;
			std::vector<int> curColorVertices;//keep track of all vertices that will be assigned colorIndex
			//iterate through all vertices in non-increasing order of their degrees, and assign colorIndex to all non-adj vertices
			for (int i = 0; i < N; ++i)
			{
				if (sortedDegree[i].second.second == -1)//vertex i hasn't been colored yet
				{
					int curVertex = sortedDegree[i].first;
					bool isAdjCurColorVertex = false;
					for (int j = 0; j < (int)curColorVertices.size(); ++j)//check if vertex i is an adj vertex
						if (adjMatrix[curVertex][curColorVertices[j]] != 0 || adjMatrix[curColorVertices[j]][curVertex] != 0)
						{
							isAdjCurColorVertex = true;
							break;
						}

					if (!isAdjCurColorVertex)//vertex i isn't an adj vertex
					{
						sortedDegree[i].second.second = colorIndex;//assign colorIndex to vertex i
						++coloredVertexCount;
						curColorVertices.push_back(curVertex);
					}
				}
			}
			//std::cout << Debug::ToStr1D<int>()(curColorVertices) << std::endl;
		}
		std::cout << "VertexColoring WelshPowell_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(sortedDegree) << std::endl;
		return sortedDegree;
	}

	bool BacktrackRecur_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int C)//C is the count of diff colors
	{
		int N = adjMatrix.size();
		std::vector<int> color(N, -1);
		bool colorable =
			this->backtrackRecur_UndirectedAdjacencyMatrix(adjMatrix, 0, color, C);
		
		if (colorable)
			std::cout << Debug::ToStr1D<int>()(color) << std::endl;
		std::cout << "VertexColoring BacktrackRecur_UndirectedAdjacencyMatrix for \"" << C << "-colors\": " << colorable << std::endl;
		return colorable;
	}
private:
	bool backtrackRecur_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix, int curVertex,
		std::vector<int> & color, int C)
	{
		int N = adjMatrix.size();
		if (curVertex == N)
			return true;

		//try all possible colors for curVertex
		for (int curColor = 0; curColor < C; ++curColor)
		{
			//1. check if curColor is same as any adjacent vertices
			bool validCurColor = true;
			for (int i = 0; i < N; ++i)
			{
				if (i != curVertex && adjMatrix[curVertex][i] != 0)
				{
					if (color[i] != -1 && color[i] == curColor)
					{
						validCurColor = false;
						break;
					}
				}
			}
			//2. DFS recur down for the next vertex
			if (validCurColor)
			{
				color[curVertex] = curColor;//label curVertex with curColor
				if (this->backtrackRecur_UndirectedAdjacencyMatrix(adjMatrix, curVertex + 1, color, C))
					return true;
				color[curVertex] = -1;//restore (this is easier done with recur instead of iterate)
				//the spirit of backtrack!
			}
		}
		return false;
	}


public:
	//Greedy doesn't guarantee min number of colors
	//but it guarantees an upper bound of d+1 number of colors, where d is the max degree of a vertex in the graph
	//(the worse case is to assign each vertex with a different color)
	std::vector<int> GreedyIterate_UndirectedAdjacencyMatrix(const std::vector<std::vector<int> > & adjMatrix)
	{
		int N = adjMatrix.size();
		std::vector<int> color(N, -1);
		std::vector<int> adjColorSet(N, 0);//index: colorIndex, value: appears or not
		for (int curVertex = 0; curVertex < N; ++curVertex)
		{
			//1. mark all the colors that have been used by adjacent vertices
			for (int i = 0; i < N; ++i)
			{
				if (i != curVertex && adjMatrix[curVertex][i] != 0)
				{
					if (color[i] != -1)
						adjColorSet[color[i]] = 1;
				}
			}

			//2. find the next available color that hasn't been used by adjacent vertices
			//and assign it to curVertex
			int curColor;
			for (curColor = 0; curColor < N; ++curColor)
				if (adjColorSet[curColor] == 0)
					break;
			color[curVertex] = curColor;

			//3. restore all the colors that have been used by adjacent vertices (same as step 1)
			for (int i = 0; i < N; ++i)
			{
				if (i != curVertex && adjMatrix[curVertex][i] != 0)
				{
					if (color[i] != -1)
						adjColorSet[color[i]] = 0;
				}
			}
		}
		//std::cout << Debug::ToStr1D<int>()(adjColorSet) << std::endl;
		std::cout << "VertexColoring GreedyIterate_UndirectedAdjacencyMatrix: " << Debug::ToStr1D<int>()(color) << std::endl;
		return color;
	}
};
#endif