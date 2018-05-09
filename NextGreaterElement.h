#ifndef NEXT_GREATER_ELEMENT_H
#define NEXT_GREATER_ELEMENT_H
#include "Debug.h"
/*
Leetcode: Next Greater Element
You are given two arrays (without duplicates) nums1 and nums2 where nums1��s elements are subset of nums2.
Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2.
If it does not exist, output -1 for this number.
Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
For number 1 in the first array, the next greater number for it in the second array is 3.
For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
For number 2 in the first array, the next greater number for it in the second array is 3.
For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.

Leetcode: Next Greater Element II
Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element.
The Next Greater Number of a number x is the first greater number to its traversing-order next in the array
, which means you could search circularly to find its next greater number.
If it doesn't exist, output -1 for this number.
Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2;
The number 2 can't find next greater number;
The second 1's next greater number needs to search circularly, which is also 2.
Note: The length of given array won't exceed 10000.

Leetcode: Daily Temperatures
Given a list of daily temperatures, produce a list that, for each day in the input, tells you how many days you would have to wait until a warmer temperature.
If there is no future day for which this is possible, put 0 instead.
For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
Note: The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].
*/
class NextGreaterElement
{
public:
	NextGreaterElement() {}

	std::vector<int> NonCircular_UseStack(const std::vector<int> & findNums, const std::vector<int> & nums)
	{
		std::stack<int> stk;//sorted stack in decr order
		std::unordered_map<int, int> map;//<entry, next right greater num>
		for (const auto & i : nums)
		{
			while (!stk.empty() && stk.top() < i)
			{
				map.insert({ stk.top(), i });
				stk.pop();
			}
			stk.push(i);
		}
		//now map contains all [num, next right greater num] pairs in nums
		std::vector<int> res;
		for (const auto & i : findNums)
		{
			if (map.count(i))
				res.push_back(map[i]);
			else
				res.push_back(-1);
		}
		std::cout << Debug::ToStr1D<int>()(map) << std::endl;
		std::cout << "NextGreaterElement NonCircular_UseStack for \"" << Debug::ToStr1D<int>()(findNums) << "\", from \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Circular_UseStack(const std::vector<int> & nums)
	{
		int N = nums.size();
		std::vector<int> res(N, -1);
		std::stack<int> stk;
		for (int i = 0; i < 2 * N - 1; ++i)
		{
			while (!stk.empty() && nums[stk.top() % N] < nums[i%N])
			{
				res[stk.top() % N] = nums[i%N];
				stk.pop();
			}
			stk.push(i);
		}

		std::cout << "NextGreaterElement Circular_UseStack for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
class DailyTemperatures
{
public:
	DailyTemperatures(){}

	std::vector<int> UseStack(const std::vector<int> & temperatures)
	{
		int N = temperatures.size();
		std::stack<int> stk;
		std::vector<int> res(N, 0);
		for (int i = 0; i < N; ++i)
		{
			while (!stk.empty() && temperatures[stk.top()] < temperatures[i])
			{
				int cur = stk.top();
				stk.pop();
				res[cur] = i - cur;
			}
			stk.push(i);
		}

		std::cout << "DailyTemperatures NumOfDaysToNextHigherTemp UseStack for \"" << Debug::ToStr1D<int>()(temperatures) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
[1,2], [2,3], [3,4]
NextGreaterElement NonCircular_UseStack for "2, 4", from "1, 2, 3, 4": 3, -1

NextGreaterElement NonCircular_UseStack for "2, 4", from "4, 3, 2, 1": -1, -1
NextGreaterElement Circular_UseStack for "1, 2, 1": 2, -1, 2

DailyTemperatures NumOfDaysToNextHigherTemp UseStack for "73, 74, 75, 71, 69, 72, 76, 73": 1, 1, 4, 2, 1, 1, 0, 0
*/
#endif
