#ifndef MIN_DELAY_TASK_SCHEDULING_DAG_H
#define MIN_DELAY_TASK_SCHEDULING_DAG_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <limits>
#include "Debug.h"
/*
Elements of programming interview, Graph: Compute a minimum delay schedule, unlimited resources
Given a set of tasks.
Each task runs on a single server.
Each task has a duration and a set of tasks that must be completed before it can be started.
The set of tasks is feasible if there doesn't exist a sequence of tasks starting and ending at the same task such that for each consecutive pair of tasks in the sequence, the first task must be completed before the second task can start.
Assume there are unlimited servers.
Check if the set of tasks is feasible.
If feasible, compute the least amount of time in which all the tasks can be started.

We can model the system with a DAG.
Each vertex represents a task.
Each edge represents the source task must be completed before the target task can be started.
The weight of each edge from a vertex(task) represents the duration of that task.
The system is infeasible if and only if a cycle is present in the DAG.
If feasible, the sequence of tasks can be completed in the topological order.
The least amount of time in which all the tasks can be started is the longest path in DAG, which is also the min delay time required to start the last task.

When the number of servers is limited, the problem becomes NP-complete.

DFS(detectCycle+topologicalSort): O(V+E) time
FindRoots: O(V^2) time
LongestPath: O(V+E) time
*/
class MinDelayTaskSchedulingDAG
{
public:
	MinDelayTaskSchedulingDAG(){}
	~MinDelayTaskSchedulingDAG(){}

	int Solve(const std::vector<std::pair<int, int>> & taskDependicies, const std::vector<int> & taskDurations, int N)
	{
		//1. construct the DAG adjacency matrix
		std::vector<std::vector<int> > DAG(N, std::vector<int>(N, 0));
		for (auto & p : taskDependicies)
		{
			DAG[p.first][p.second] = 1;
		}
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
				if (DAG[i][j])
					DAG[i][j] = taskDurations[i];
		}
		Debug::Print2D<int>()(DAG, false);
		
		//2. run DFS to 1) detect if cycle exists in DAG and 2) compute topological sort
		int visitCount = -1;
		std::vector<int> visitIndex(N, -1);
		int completionCount = -1;
		std::vector<int> completionIndex(N, -1);
		std::vector<int> stk;
		bool hasCycle = false;
		for (int i = 0; i < N; ++i)
		{
			if (visitIndex[i] == -1)
			{
				if (this->DFSRecur(DAG, i, visitCount, visitIndex, completionCount, completionIndex, stk))
				{
					hasCycle = true;
					break;
				}
			}
		}
		if (hasCycle)
			return -1;//task scheduling is not feasible if cycle exists in DAG
		std::cout << "TopologicalSort: " << Debug::ToStr1D<int>()(stk) << std::endl;

		//3. find all root vertices (w/ 0 in-degree) for multiple disconnected DAGs
		std::vector<int> roots;
		for (int j = 0; j < N; ++j)//colX
		{
			bool rootVertex = true;
			for (int i = 0; i < N; ++i)//rowY
			{
				if (DAG[i][j])
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
		std::vector<int> dist(N, INT_MIN);//dist[i]: max dist from root to vertex i
		for (const int & r : roots)
			dist[r] = 0;
		std::vector<std::vector<int> > paths(N, std::vector<int>());
		while (!stk.empty())
		{
			int v = stk.back();
			stk.pop_back();
			if (dist[v] != INT_MIN)
			{
				for (int i = 0; i < N; ++i)
				{
					if (DAG[v][i])
						if (dist[i] < dist[v] + DAG[v][i])
						{
							dist[i] = dist[v] + DAG[v][i];
							paths[i] = paths[v];
							paths[i].push_back(v);
						}
				}
			}
		}

		int res = INT_MIN;
		for (const int & d : dist)
			if (d > res)
				res = d;
		Debug::Print2D<int>()(paths, false);
		std::cout << "MinDelayTaskSchedulingDAG for taskDependencies=\"" << Debug::ToStr1D<int>()(taskDependicies) << ", taskDurations=\"" << Debug::ToStr1D<int>()(taskDurations) << "\", N=\"" << N << "\":" << std::endl;
		std::cout << "minDelayTimeRequiredToStartTheLastTask: " << res << ", maxDelayTimeRequiredForEachTaskToStart: " << Debug::ToStr1D<int>()(dist) << std::endl;
		return res;
	}
private:
	bool DFSRecur(const std::vector<std::vector<int>> & DAG, int v, int & visitCount, std::vector<int> & visitIndex, int & completionCount, std::vector<int> & completionIndex, std::vector<int> & stk)
	{
		int N = DAG.size();
		visitIndex[v] = ++visitCount;
		for (int i = 0; i < N; ++i)
		{
			if (DAG[v][i] > 0 && i != v)
			{
				if (visitIndex[i] == -1)
				{
					if (this->DFSRecur(DAG, i, visitCount, visitIndex, completionCount, completionIndex, stk))
						return true;
				}
				else
				{
					if (completionIndex[i] == -1)
					{
						//(v, i) is a back edge in a directed graph
						std::cout << "Found Back Edge: " << v << "->" << i << std::endl;
						return true;
					}
				}
			}
		}
		completionIndex[v] = ++completionCount;
		stk.push_back(v);
		return false;
	}
};
/*
		   6     3
		1---->4---->6
	   6| \6  |3 5/ |5
	    |   \ | /   |
		v  5 vvv  8 v  24              5
		0---->3---->8<----13       9---->11
	   5|   / | \   |              |5   ^|
		| /8  |8 8\ |7             |  3/ |7
		vv  9 v  5 vv           4  v / 3 v
		2---->5---->7       14---->10--->12
[rY][cX]
Row#0	= 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#2	= 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#3	= 0, 0, 8, 0, 0, 8, 0, 8, 8, 0, 0, 0, 0, 0, 0
Row#4	= 0, 0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0
Row#5	= 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0
Row#6	= 0, 0, 0, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0
Row#7	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#8	= 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0
Row#9	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0
Row#10	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0
Row#11	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0
Row#12	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
Row#13	= 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0
Row#14	= 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0

TopologicalSort: 7, 5, 2, 8, 3, 0, 6, 4, 1, 12, 11, 10, 9, 13, 14
Roots: 1, 9, 13, 14
[rY][cX]
Row#0	= 1,  ,  ,  ,  ,  
Row#1	=  ,  ,  ,  ,  ,  
Row#2	= 1, 4, 6, 3,  ,  
Row#3	= 1, 4, 6,  ,  ,  
Row#4	= 1,  ,  ,  ,  ,  
Row#5	= 1, 4, 6, 3, 2,  
Row#6	= 1, 4,  ,  ,  ,  
Row#7	= 1, 4, 6, 3, 2, 5
Row#8	= 13,  ,  ,  ,  ,  
Row#9	=  ,  ,  ,  ,  ,  
Row#10	= 9,  ,  ,  ,  ,  
Row#11	= 9, 10,  ,  ,  ,  
Row#12	= 9, 10, 11,  ,  ,  
Row#13	=  ,  ,  ,  ,  ,  
Row#14	=  ,  ,  ,  ,  ,  

MinDelayTaskSchedulingDAG for taskDependencies="[1,0], [1,4], [1,3], [0,3], [0,2], [4,3], [4,6], [3,8], [3,5], [3,7], [3,2], [6,8], [6,3], [8,7], [5,7], [2,5], [13,8], [9,10], [9,11], [10,11], [10,12], [11,12], [14,10], taskDurations="5, 6, 9, 8, 3, 5, 5, 1, 7, 5, 3, 7, 1, 24, 4", N="15":
minDelayTimeRequiredToStartTheLastTask: 36, maxDelayTimeRequiredForEachTaskToStart: 6, 0, 22, 14, 6, 31, 9, 36, 24, 0, 5, 8, 15, 0, 0

*/
#endif