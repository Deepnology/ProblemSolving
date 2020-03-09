#ifndef MAX_CAPITAL_FOR_IPO_H
#define MAX_CAPITAL_FOR_IPO_H
#include "Debug.h"
/*
Leetcode: IPO
Suppose LeetCode will start its IPO soon.
In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO.
Since it has limited resources, it can only finish at most k distinct projects before the IPO.
Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.
You are given several projects.
For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project.
Initially, you have W capital.
When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.
To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital, and output your final maximized capital.
Example 1:
Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].
Output: 4
Explanation: Since your initial capital is 0, you can only start the project indexed 0.
After finishing it you will obtain profit 1 and your capital becomes 1.
With capital 1, you can either start the project indexed 1 or the project indexed 2.
Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
Note:
You may assume all numbers in the input are non-negative integers.
The length of Profits array and Capital array will not exceed 50,000.
The answer is guaranteed to fit in a 32-bit signed integer.
*/
class MaxCapitalForIPO
{
public:
	MaxCapitalForIPO() {}

	int SortAndMaxHeap(int k, int W, const std::vector<int> & Profits, const std::vector<int> & Capital)
	{
		std::vector<std::pair<int, int>> pc;
		int N = Profits.size();
		for (int i = 0; i < N; ++i)
			pc.push_back({ Profits[i],Capital[i] });
		std::sort(pc.begin(), pc.end(), [](const std::pair<int, int> & a, const std::pair<int, int> & b)->bool
		{
			return a.second == b.second ? a.first>b.first:a.second<b.second;//sort capitals in incr order, for equal capitals, sort profits in decr order
		});
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<std::pair<int, int>>> maxHeap;//<profit,capital> where profits in decr order
		int count = 0;
		int cur = 0;
		int totalCapital = W;

		while (count++<k)
		{
			//to start a new project, totalCapital must be >= the new project's capital
			while (cur<N && totalCapital >= pc[cur].second)//push as much as possible
			{
				maxHeap.push(pc[cur++]);
			}
			if (maxHeap.empty())
				break;
			//totalCapital doesn't need to subtract the new project's capital !!!
			totalCapital += maxHeap.top().first;//sum of profits + W
			maxHeap.pop();
		}

		std::cout << "MaxCapitalForIPO SortAndMaxHeap for InitCapital=\"" << W << "\", Select=\"" << k << "\" from \"" << Debug::ToStr1D<int>()(Profits) << "\" and \"" << Debug::ToStr1D<int>()(Capital) << "\": " << totalCapital << std::endl;
		return totalCapital;
	}
};
/*
MaxCapitalForIPO SortAndMaxHeap for InitCapital="2", Select="1" from "2, 1, 3" and "1, 1, 2": 5
MaxCapitalForIPO SortAndMaxHeap for InitCapital="11", Select="11" from "1, 2, 3" and "11, 12, 13": 17
*/
#endif
