#ifndef COURSE_SCHEDULE_H
#define COURSE_SCHEDULE_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <limits>
#include <unordered_map>
#include "Debug.h"
/*
Leetcode: Course Schedule
There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:
2, [[1,0]]
There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1.
So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices.
Read more about how a graph is represented.

Hints:
This problem is equivalent to finding if a cycle exists in a directed graph.
If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
Topological sort could also be done via BFS.

Leetcode: Course Schedule II
Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them.
If it is impossible to finish all courses, return an empty array.

For example:
2, [[1,0]]
There are a total of 2 courses to take.
To take course 1 you should have finished course 0.
So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take.
To take course 3 you should have finished both courses 1 and 2.
Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Hints:
This problem is equivalent to finding the topological order in a directed graph.
If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.

See also MinDelayTaskSchedulingDAG.h

Leetcode: Course Schedule III
There are n different online courses numbered from 1 to n.
Each course has some duration(course length) t and closed on dth day.
A course should be taken continuously for t days and must be finished before or on the dth day.
You will start at the 1st day.
Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.
Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation:
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day.
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
*/
class CourseSchedule
{
public:
	CourseSchedule(){}
	~CourseSchedule(){}

	bool CanFinish(int numCourses, const std::vector<std::pair<int, int>> & prerequisites)//first: to, second: from
	{
		//1. construct DAG adjacency list (adjacency matrix: memory limit exceeded!)
		std::unordered_map<int, std::vector<int>> DAG;//first: from, second: a vector of to
		for (const auto & p : prerequisites)
		{
			auto itr = DAG.find(p.second);
			if (itr == DAG.end())
			{
				DAG[p.second] = std::vector<int>(1, p.first);
			}
			else
			{
				itr->second.push_back(p.first);
			}
		}
		Debug::Print2D<int>()(DAG);

		//2. run DFS to detect cycles in DAG
		int visitCount = -1;
		std::vector<int> visitIndex(numCourses, -1);
		int completionCount = -1;
		std::vector<int> completionIndex(numCourses, -1);
		std::vector<int> stk;
		bool hasCycle = false;
		for (int i = 0; i < numCourses; ++i)
		{
			if (visitIndex[i] == -1 && DAG.find(i) != DAG.end())
			{
				if (this->DFSRecur(DAG, i, visitCount, visitIndex, completionCount, completionIndex, stk))
				{
					hasCycle = true;
					break;
				}
			}
		}

		std::cout << "CourseSchedule CanFinish for \"" << numCourses << ", " << Debug::ToStr1D<int>()(prerequisites) << "\": " << !hasCycle << std::endl;
		return !hasCycle;
	}
	std::vector<int> FindOrder(int numCourses, const std::vector<std::pair<int, int>> & prerequisites)//first: to, second: from
	{
		//1. construct DAG adjacency list (adjacency matrix: memory limit exceeded!)
		std::unordered_map<int, std::vector<int>> DAG;//first: from, second: a vector of to
		for (const auto & p : prerequisites)
		{
			auto itr = DAG.find(p.second);
			if (itr == DAG.end())
			{
				DAG[p.second] = std::vector<int>(1, p.first);
			}
			else
			{
				itr->second.push_back(p.first);
			}
		}
		Debug::Print2D<int>()(DAG);

		//2. run DFS to detect cycles in DAG and compute topological sort order
		int visitCount = -1;
		std::vector<int> visitIndex(numCourses, -1);
		int completionCount = -1;
		std::vector<int> completionIndex(numCourses, -1);
		std::vector<int> stk;
		bool hasCycle = false;
		for (int i = 0; i < numCourses; ++i)
		{
			if (visitIndex[i] == -1 && DAG.find(i) != DAG.end())
			{
				if (this->DFSRecur(DAG, i, visitCount, visitIndex, completionCount, completionIndex, stk))
				{
					hasCycle = true;
					break;
				}
			}
		}
		if (hasCycle)
			return std::vector<int>();

		//3. reverse stk to get topological sort order
		std::reverse(stk.begin(), stk.end());
		std::cout << "topological sort: " << Debug::ToStr1D<int>()(stk) << std::endl;

		//4. add courses that don't have any courses to be followed
		if ((int)stk.size() < numCourses)
		{
			for (int i = 0; i < numCourses; ++i)
				if (visitIndex[i] == -1)
					stk.push_back(i);
		}

		std::cout << "CourseSchedule FindOrder for \"" << numCourses << ", " << Debug::ToStr1D<int>()(prerequisites) << "\": " << Debug::ToStr1D<int>()(stk) << std::endl;
		return stk;
	}
private:
	bool DFSRecur(const std::unordered_map<int, std::vector<int>> & DAG, int v, int & visitCount, std::vector<int> & visitIndex, int & completionCount, std::vector<int> & completionIndex, std::vector<int> & stk)
	{
		int N = DAG.size();
		visitIndex[v] = ++visitCount;
		//if v is not present in DAG: v doesn't have any out degree
		auto itr = DAG.find(v);
		if (itr != DAG.end())//adj list: for vertices that have any out degrees
		{
			for (const int i : itr->second)
			{
				if (i != v)
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
		}
		completionIndex[v] = ++completionCount;
		stk.push_back(v);
		return false;
	}

public:
	int GreedyFindMaxNumOfCourses(std::vector<std::vector<int>>& courses)//[duration,endTime]
	{
		std::sort(courses.begin(), courses.end(),
			[](const std::vector<int> & a, const std::vector<int> & b)->bool
		{
			return a[1] < b[1];//sort by end time
		});

		std::multiset<int> durations;
		int N = courses.size();
		int curEnd = 0;
		for (int i = 0; i < N; ++i)
		{
			curEnd += courses[i][0];
			durations.insert(courses[i][0]);
			while (!durations.empty() && curEnd > courses[i][1])//greedily remove longest duration courses to maximize num of total courses
			{
				curEnd -= *std::prev(durations.end());
				durations.erase(std::prev(durations.end()));
			}
		}
		return durations.size();
	}
};
/*
Row#0	= 0: 1

CourseSchedule CanFinish for "2, [1,0]": 1
Row#0	= 0: 1
Row#1	= 1: 0

Found Back Edge: 1->0
CourseSchedule CanFinish for "2, [1,0], [0,1]": 0
Row#0	= 0: 1

topological sort: 0, 1
CourseSchedule FindOrder for "2, [1,0]": 0, 1
Row#0	= 0: 1, 2
Row#1	= 1: 3
Row#2	= 2: 3

topological sort: 0, 2, 1, 3
CourseSchedule FindOrder for "4, [1,0], [2,0], [3,1], [3,2]": 0, 2, 1, 3
*/
#endif