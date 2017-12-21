#ifndef SALARY_THRESHOLD_FOR_SMALLER_BUDGET_H
#define SALARY_THRESHOLD_FOR_SMALLER_BUDGET_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Sorting: Compute a salary threshold
Given an array of salaries of employees.
Given a budget which is smaller than the sum of all salaries.
Compute a salary threshold such that salaries higher than the threshold will be cut to the threshold, whereas salaries equal to or smaller than threshold will keep unchanged
, and the sum of all salaries after adjusted should be equal to the new budget.

O(nlogn) time, O(n) space
*/
class SalaryThresholdForSmallerBudget
{
public:
	SalaryThresholdForSmallerBudget(){}
	~SalaryThresholdForSmallerBudget(){}

	double Solve(std::vector<double> & v, double budget)
	{
		int N = v.size();

		//1. sort all salaries in ascending order: O(nlogn) time
		std::sort(v.begin(), v.end(), std::less<double>());

		//2. compute prefixSum of all salaries: O(n) time
		std::vector<double> prefixSum(N);
		prefixSum[0] = v[0];
		for (int i = 1; i < N; ++i)
			prefixSum[i] = prefixSum[i - 1] + v[i];

		//3. compute a budgets array where budgets[i] represents the total payroll required if the "max salary allowed" is v[i]: O(n) time
		std::vector<double> budgets;
		for (int i = 0; i < N; ++i)
			budgets.push_back(prefixSum[i] + (N - i - 1) * v[i]);

		//4. binary search the budgets array for the target budget: O(logn) time
		auto lbIter = std::lower_bound(budgets.begin(), budgets.end(), budget);
		double threshold;
		if (lbIter == budgets.end())
			threshold = -1.0;//no solution since budget is too large
		else if (lbIter == budgets.begin())//budget is too small
			threshold = budget / N;
		else
		{
			int maxUnchangedSalaryIdx = lbIter - budgets.cbegin() - 1;//the one before lower bound
			threshold = v[maxUnchangedSalaryIdx] + 
				(budget - budgets[maxUnchangedSalaryIdx]) / (N - maxUnchangedSalaryIdx - 1);//split extra budget evenly with (N-maxUnchangedSalaryIdx-1) employees
		}

		std::cout << Debug::ToStr1D<double>()(prefixSum) << std::endl;
		std::cout << Debug::ToStr1D<double>()(budgets) << std::endl;
		std::string lbval = lbIter == budgets.end() ? "End" : std::to_string(*lbIter);
		std::cout << "LowerBound: " << lbval << std::endl;
		std::cout << "SalaryThresholdForSmallerBudget for \"" << budget << "\" in \"" << Debug::ToStr1D<double>()(v) << "\": " << threshold << std::endl;
		return threshold;
	}
};
/*
20, 50, 90, 180, 280
100, 140, 170, 270, 280
LowerBound: 270.000000
SalaryThresholdForSmallerBudget for "210" in "20, 30, 40, 90, 100": 60
*/
#endif