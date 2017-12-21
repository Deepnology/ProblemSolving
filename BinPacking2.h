#ifndef BIN_PACKING_2_H
#define BIN_PACKING_2_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Google
http://www.careercup.com/question?id=6282171643854848
Given M servers with different memory quota and N tasks with different memory usage requirements.
Determine if all the tasks can be executed by these servers simultaneously.
Or
Given M boxes with different sizes and N items with different volumes.
Determine if all the items can be filled into these boxes.

First thought:
Go over all the permutations of the tasks. 
This can be done through backtracking recursion.
For each permutation order of the tasks, assign tasks to first available server in a fixed order (the first server whose remaining memory quota is greater than 0)
, and subtrack the memory quota from that server.
When first available server is not able to run current task, try next.
If all the remaining servers cannot run current task, this permutation of tasks (a path down to the leaf node of backtracking tree) doesn't work, return false.
If a particular permutation of tasks can be assigned to servers, return true, and done.
When gone over all permutations of tasks and cannot find a solution, return false.

Second thought (correct):
Since the order of assigning a task to a particular server doesn't matter, just need to assign all tasks in a fixed order to all available servers with remaining quotas in a fixed order.
That is, assign a task to an available server with its memory quota subtracted, do it from the first server to the last in a fixed order, fix that, and repeat for the next task.
This will skip repeated permutations in the 1st method.

Greedy Algorithm (wrong):
Always choose the server with the largest remaining memory quota and choose the task with the largest memory requirement, then assign the task to the server and subtrack the memory quota from the server.
Repeat this process.
This can be done with 2 maxHeaps or always sort the server array and task array after each assignment.
It doesn't work for this problem.
Consider this case which should return true:
Servers with memory quota: 5, 4
Tasks with memory requirement: 4, 3, 2
After 1st assignment:
4, 1
3, 2
After 2nd assignement:
1, 1
2
=> return false, which is wrong.

*/
class BinPacking2
{
public:
	BinPacking2(){}
	~BinPacking2(){}

	bool Valid_EnumerateAll_Recur(const std::vector<int> & tasks, std::vector<int> & servers)
	{
		std::string before = Debug::ToStr1D<int>()(servers);
		bool res = this->validRecur(tasks, servers, 0);
		std::cout << "BinPacking2 Valid for tasks: \"" << Debug::ToStr1D<int>()(tasks) << "\", servers: \"" << before << "\": " << res << std::endl;
		return res;
	}
private:
	bool validRecur(const std::vector<int> & tasks, std::vector<int> & servers, int curTask)
	{
		int N = tasks.size();
		if (curTask == N)
			return true;

		int M = servers.size();
		for (int i = 0; i < M; ++i)//always start from the 1st server to enumerate all cases
		{
			if (tasks[curTask] <= servers[i])
			{
				servers[i] -= tasks[curTask];
				if (this->validRecur(tasks, servers, curTask + 1))
					return true;
				servers[i] += tasks[curTask];//backtracking (restore)
			}
		}
		return false;
	}

public:
	//find the optimum solution to use as min number of servers as possible
	int MinBin_EnumerateAll_Recur(const std::vector<int> & tasks, std::vector<int> & servers)
	{
		std::string before = Debug::ToStr1D<int>()(servers);
		int usedBins = 0;
		std::vector<std::vector<int>> path(servers.size(), std::vector<int>());//configuration of all servers containing any tasks

		int minBins = INT_MAX;
		std::vector<std::vector<int>> res;//configuration of all servers containing any tasks

		this->minBinRecur(tasks, servers, 0, usedBins, path, minBins, res);
		std::cout << "BinPacking2 MinBin for tasks: \"" << Debug::ToStr1D<int>()(tasks) << "\", servers: \"" << before << "\": " << minBins << std::endl;
		Debug::Print2D<int>()(res, false);
		return minBins;
	}
private:
	void minBinRecur(const std::vector<int> & tasks, std::vector<int> & servers, int curTask
		, int & usedBins, std::vector<std::vector<int>> & path
		, int & minBins, std::vector<std::vector<int>> & res)
	{
		int N = tasks.size();
		if (curTask == N)
		{
			if (usedBins < minBins)
			{
				minBins = usedBins;
				res.clear();
				res = path;
			}
			return;
		}

		int M = servers.size();
		for (int i = 0; i < M; ++i)
		{
			if (tasks[curTask] <= servers[i])
			{
				//add curTask to servers[i]
				servers[i] -= tasks[curTask];
				if (path[i].empty())
					++usedBins;
				path[i].push_back(tasks[curTask]);

				this->minBinRecur(tasks, servers, curTask + 1, usedBins, path, minBins, res);

				//remove curTask from servers[i]
				path[i].pop_back();
				if (path[i].empty())
					--usedBins;
				servers[i] += tasks[curTask];
			}
		}
	}
};
/*
BinPacking2 Valid for tasks: "2, 3, 4", servers: "4, 5": 1
BinPacking2 Valid for tasks: "2, 3, 5", servers: "4, 5": 0
BinPacking2 Valid for tasks: "18, 4, 8, 4, 6, 6, 8, 8", servers: "8, 16, 8, 32": 1
BinPacking2 MinBin for tasks: "2, 3, 4", servers: "4, 5": 2
[rY][cX]
Row#0	= 4,
Row#1	= 2, 3

BinPacking2 MinBin for tasks: "2, 3, 5", servers: "4, 5": 2147483647
BinPacking2 MinBin for tasks: "18, 4, 8, 4, 6, 6, 8, 8", servers: "8, 16, 8, 32": 4
[rY][cX]
Row#0	= 4, 4,
Row#1	= 8, 6,
Row#2	= 8,  ,
Row#3	= 18, 6, 8
*/
#endif