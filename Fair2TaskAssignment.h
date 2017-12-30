#ifndef FAIR_2_TASK_ASSIGNMENT_H
#define FAIR_2_TASK_ASSIGNMENT_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Compute an optimum assignment of tasks
We consider the problem of scheduling n = 2m tasks to be performed by m workers.
Each worker must be assigned exactly two tasks.
Each task has a duration.
Tasks are independent, i.e., there are no constraints of the form "Task 4 cannot start before Task 3 is completed."
We want to assign tasks to workers so as to minimize how long it takes before all tasks are completed.

Given an array of even task durations.
Divide the array into subsets where each subset has exactly 2 tasks
, such that the maximum subset sum of the 2-task durations over all subsets is minimized.
(Special case of PaintersPartitionFairWorkload.h)
O(nlogn) time
*/
class Fair2TaskAssignment
{
public:
	Fair2TaskAssignment(){}
	~Fair2TaskAssignment(){}

	std::vector<std::pair<int, int>> Partition(std::vector<int> && v)
	{
		std::string before = Debug::ToStr1D<int>()(v);
		std::sort(v.begin(), v.end(), std::less<int>());
		int N = v.size();
		std::vector<std::pair<int, int> > res;
		for (int i = 0, j = N - 1; i < j; ++i, --j)
			res.emplace_back(v[i], v[j]);

		std::cout << "Fair2TaskAssignment for \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
Fair2TaskAssignment for "18, 3, 12, 9, 7, 17, 4, 11, 14, 20, 5, 1, 8, 15, 6, 10, 13, 16, 19, 2": [1,20], [2,19], [3,18], [4,17], [5,16], [6,15], [7,14], [8,13], [9,12], [10,11]
*/
#endif