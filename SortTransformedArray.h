#ifndef SORT_TRANSFORMED_ARRAY_H
#define SORT_TRANSFORMED_ARRAY_H
#include "Debug.h"
/*
Leetcode: Sort Transformed Array
Given a sorted array of integers nums and integer values a, b and c.
Apply a function of the form f(x) = ax^2 + bx + c to each element x in the array.
The returned array must be in sorted order.
Expected time complexity: O(n)

Example:
nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,
Result: [3, 9, 15, 33]
nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5
Result: [-23, -5, 1, 7]

UseMinHeap: O(nlogn) time
Greedy: O(n) time
*/
class SortTransformedArray
{
public:
	SortTransformedArray() {}
	~SortTransformedArray() {}

	std::vector<int> UseMinHeap(const std::vector<int> & nums, int a, int b, int c)
	{
		int N = nums.size();
		std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
		for (int i = 0; i < N; ++i)
		{
			minHeap.push(this->cal(nums[i], a, b, c));
		}

		std::vector<int> res;
		while (!minHeap.empty())
			res.push_back(minHeap.top()), minHeap.pop();

		std::cout << "SortTransformedArray UseMinHeap for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Greedy(const std::vector<int> & nums, int a, int b, int c)
	{
		int N = nums.size();
		int i = 0;
		int j = N - 1;
		std::vector<int> res(N);
		int cur;
		if (a > 0)
			cur = N - 1;
		else if (a < 0)
			cur = 0;
		else
			cur = N - 1;

		while (i <= j)
		{
			if (a > 0) //U shape: the 2 ends i, j are from large to small, so use greedy to fill res from back to front
			{
				res[cur--] = this->cal(nums[i], a, b, c) >= this->cal(nums[j], a, b, c) ? this->cal(nums[i++], a, b, c) : this->cal(nums[j--], a, b, c);
			}
			else if (a < 0) //n shape: the 2 ends i, j are from small to large, so use greedy to fill res from front to back
			{
				res[cur++] = this->cal(nums[i], a, b, c) <= this->cal(nums[j], a, b, c) ? this->cal(nums[i++], a, b, c) : this->cal(nums[j--], a, b, c);
			}
			else //a==0, linear shape: can be either from small to large or from large to small for the case from i to j, here we combine it into the U shape case
			{
				res[cur--] = this->cal(nums[i], a, b, c) >= this->cal(nums[j], a, b, c) ? this->cal(nums[i++], a, b, c) : this->cal(nums[j--], a, b, c);
			}
		}

		std::cout << "SortTransformedArray Greedy for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

private:
	int cal(int x, int a, int b, int c)
	{
		return a * x * x + b * x + c;
	}

public:
	/*
	Leetcode: Squares of a sorted array
	Given a sorted integer array, output a sorted array that are composed of squares of the input array nums.
	input = [-4,1,3,5], output = [1,9,16,25]
	*/
	std::vector<int> TransformToSortedSquares_Greedy(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> res(N);
		int i = 0;
		int j = N - 1;
		int k = N - 1;
		while (i <= j)
		{
			if (v[i] * v[i] > v[j] * v[j])
			{
				res[k--] = v[i] * v[i];
				++i;
			}
			else
			{
				res[k--] = v[j] * v[j];
				--j;
			}
		}
		std::cout << "SortTransformedArray TransformToSortedSquares_Greedy for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
SortTransformedArray UseMinHeap for "-4, -2, 2, 4": 3, 9, 15, 33
SortTransformedArray Greedy for "-4, -2, 2, 4": 3, 9, 15, 33
SortTransformedArray UseMinHeap for "-4, -2, 2, 4": -23, -5, 1, 7
SortTransformedArray Greedy for "-4, -2, 2, 4": -23, -5, 1, 7
SortTransformedArray TransformToSortedSquares_Greedy for "-4, 1, 3, 5": 1, 9, 16, 25
SortTransformedArray TransformToSortedSquares_Greedy for "-5, -2, -1, 0, 1, 2, 2, 3, 5": 0, 1, 1, 4, 4, 4, 9, 25, 25
*/
#endif
