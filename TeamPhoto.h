#ifndef TEAM_PHOTO_H
#define TEAM_PHOTO_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, Sorting, Graph: Team photo day--1,2
Given 2 team of players of heights, and you want to take a group photo of all the members.
All the players of a team must stand in a row.
A player in the back row must be taller than the player in front of him.
Design an algorithm that takes as input two teams and the heights of the players in the teams and checks if it is possible to place players to take photo subject to the placement constraint.

O(nlogn) time

How would you generalize your solution to determine the largest number of teams that can be photographed simultaneously subject to the same constraints?
We can construct a DAG, where each vertex is a team, and an directed edge can be connected from a source vertex team to a target vertex team if the soruce vertex team < the target vertex team.
Then perform topological sort to find out the ordering of the DAG, and the smallest vertex.
Then compute the longest path in DAG from the smallest vertex in the topological sort.
This Longest Increasing Team Sequence in DAG cannot be reduced to LongestIncreasingSubsequence in 1D array is because "teamA < teamB && teamB < teamC" doesn't mean "teamA < teamC", so it cannot just sort all the teams in increasing order and find LIS.
O(V+E) for longest path in DAG
See also LongestPathInDAG.h
*/
class TeamPhoto
{
	std::vector<int> m_members;
public:
	explicit TeamPhoto(const std::vector<int> & height) : m_members(height)
	{}
	~TeamPhoto(){}
	bool operator<(const TeamPhoto & rhs) const
	{
		std::vector<int> sorted(this->Sort());
		std::vector<int> rhsSorted(rhs.Sort());
		for (int i = 0; i < (int)sorted.size() && i < (int)rhsSorted.size(); ++i)
		{
			if (!(sorted[i] < rhsSorted[i]))
				return false;
		}
		return true;
	}
private:
	std::vector<int> Sort() const
	{
		std::vector<int> copy(m_members);
		std::sort(copy.begin(), copy.end(), std::less<int>());
		return copy;
	}

public:
	static bool CheckPossible(const TeamPhoto & a, const TeamPhoto & b)//for 2 teams ONLY
	{
		/*
		it is possible only when all sorted members in Team a are smaller than corresponding sorted members in Team b
		or all sorted members in Team b are smaller than corresponding sorted members in Team a
		*/
		bool res = false;
		if (a < b || b < a)
			res = true;

		std::cout << "TeamPhoto CheckPossible for \"" << Debug::ToStr1D<int>()(a.m_members) << "\" and \"" << Debug::ToStr1D<int>()(b.m_members) << "\": " << res << std::endl;
		return res;
	}
};

class TeamPhoto2
{
public:
	TeamPhoto2(){}
	~TeamPhoto2(){}
	void LongestTeamSequenceDAG(const std::vector<std::vector<int> > & teams)//for N teams
	{
		//1. construct a DAG, where a directed edge means the source team is smaller than the target team
		int N = teams.size();
		std::vector<TeamPhoto> t;
		for (int i = 0; i < N; ++i)
			t.push_back(TeamPhoto(teams[i]));
		std::vector<std::vector<int> > adjMatrix(N, std::vector<int>(N, 0));//DAG
		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (t[j] < t[i])
					adjMatrix[j][i] = 1;
				else if (t[i] < t[j])
					adjMatrix[i][j] = 1;
			}
		}

		//2. compute the topological sort in DAG
		std::vector<int> visitIndex(N, -1);
		int visitCount = -1;
		std::stack<int> stk;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				this->DFS_AdjacencyMatrix_Recur(adjMatrix, i, visitCount, visitIndex, stk);
			}
		}
		std::string topologicalSort = Debug::ToStr1D<int>()(stk);

		//3. find all root vertices (w/ 0 in-degree)
		std::vector<int> roots;
		for (int j = 0; j < N; ++j)//colX
		{
			bool rootVertex = true;
			for (int i = 0; i < N; ++i)//rowY
			{
				if (adjMatrix[i][j])
				{
					rootVertex = false;
					break;
				}
			}
			if (rootVertex)//a root vertex must have a straight 0 column, which means no other vertices has an edge to it
				roots.push_back(j);
		}
		std::cout << "Roots: " << Debug::ToStr1D<int>()(roots) << std::endl;

		//4. compute longest path for each vertex from its CONNECTED FAREST root in DAG with topological sort order
		std::vector<int> dist(N, INT_MIN);
		for (const int & r : roots)
			dist[r] = 0;//init all root vertices (w/ 0 in-degree) with 0
		std::vector<std::vector<int> > paths(N, std::vector<int>());
		while (!stk.empty())
		{
			int v = stk.top();
			stk.pop();
			if (dist[v] != INT_MIN)
			{
				for (int i = 0; i < N; ++i)
				{
					if (adjMatrix[v][i] > 0)
						if (dist[i] < dist[v] + adjMatrix[v][i])
						{
							dist[i] = dist[v] + adjMatrix[v][i];
							paths[i] = paths[v];
							paths[i].push_back(v);
						}
				}
			}
		}

		Debug::Print2D<int>()(teams, false);
		Debug::Print2D<int>()(adjMatrix, false);
		Debug::Print2D<int>()(paths, false);
		std::cout << "TeamPhoto2 LongestTeamSequenceDAG for \"" << topologicalSort << "\": " << Debug::ToStr1D<int>()(dist) << std::endl;
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
};
/*
TeamPhoto CheckPossible for "1, 2, 3, 17, 18, 19, 20" and "11, 12, 13, 14, 15, 21, 22": 0
TeamPhoto CheckPossible for "11, 12, 13, 14, 15, 16, 17" and "1, 2, 3, 4, 5, 6, 7": 1
TeamPhoto CheckPossible for "1, 2, 3, 14, 15, 16, 17" and "1, 2, 3, 4, 5, 6, 7": 0

		             5-------->2
				   / |  \   /  |
				 /	 |    X    |
			   / 	 |  /   \  |
			 v		 v v     v v
		    4------->0<--------6<---------
			|	     ^ ^     ^ ^         |
			|	   	 |  \   /  |         |
			|	 	 |    X    |         |
			| 		 |  /   \  |         |
		  	|		 1         3         |
			|____________________________|

Roots: 1, 3, 5
[rY][cX]
Row#0	= 41, 42, 43, 44, 45, 46, 47
Row#1	= 1, 2, 3, 17, 18, 19, 20
Row#2	= 11, 12, 13, 14, 15, 16, 17
Row#3	= 1, 2, 3, 14, 15, 16, 17
Row#4	= 11, 12, 13, 14, 15, 21, 22
Row#5	= 1, 2, 3, 4, 5, 6, 7
Row#6	= 31, 32, 33, 34, 35, 36, 37

[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0, 0
Row#1	= 1, 0, 0, 0, 0, 0, 1
Row#2	= 1, 0, 0, 0, 0, 0, 1
Row#3	= 1, 0, 0, 0, 0, 0, 1
Row#4	= 1, 0, 0, 0, 0, 0, 1
Row#5	= 1, 0, 1, 0, 1, 0, 1
Row#6	= 1, 0, 0, 0, 0, 0, 0

[rY][cX]
Row#0	= 5, 4, 6
Row#1	=  ,  ,  
Row#2	= 5,  ,  
Row#3	=  ,  ,  
Row#4	= 5,  ,  
Row#5	=  ,  ,  
Row#6	= 5, 4,  

TeamPhoto2 LongestTeamSequenceDAG for "0, 6, 1, 2, 3, 4, 5": 3, 0, 1, 0, 1, 0, 2
*/
#endif