#ifndef KILL_PROCESS_H
#define KILL_PROCESS_H
#include "Debug.h"
/*
Leetcode: Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).
Each process only has one parent process, but may have one or more children processes.
This is just like a tree structure.
Only one process has PPID that is 0, which means this process has no parent process.
All the PIDs will be distinct positive integers.
We use two list of integers to represent a list of processes, where the first list contains PID for each process and the second list contains the corresponding PPID.
Now given the two lists, and a PID representing a process you want to kill, return a list of PIDs of processes that will be killed in the end.
You should assume that when a process is killed, all its children processes will be killed.
No order is required for the final answer.
Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.
*/
class KillProcess
{
public:
	std::vector<int> DFS_Stack(std::vector<int> & pid, std::vector<int> & ppid, int kill)
	{
		std::unordered_map<int, std::unordered_set<int>> adj;//adjacency list<parent id, set of child ids>
		int N = pid.size();
		for (int i = 0; i < N; ++i)
			adj[ppid[i]].insert(pid[i]);

		std::vector<int> res;
		std::stack<int> stk;
		stk.push(kill);//start DFS W Stack from the "kill process id"
		while (!stk.empty())
		{
			while (!adj[stk.top()].empty())
			{
				int top = stk.top();
				stk.push(*adj[top].begin());
				adj[top].erase(adj[top].begin());
			}
			//now visit cur node in reversed preorder
			int cur = stk.top();
			stk.pop();
			res.push_back(cur);
		}
		std::reverse(res.begin(), res.end());
		return res;
	}
};
/*

*/
#endif
