#ifndef LARGEST_RECT_HISTOGRAM_H
#define LARGEST_RECT_HISTOGRAM_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Compute the largest rectangle under the skyline
Leetcode: Largest Rectangle In Histogram
// Given n non-negative integers representing the histogram's bar height where
// the width of each bar is 1, find the area of largest rectangle in the
// histogram.
//
// For example,
// Given height = [2,1,5,6,2,3],
// return 10.
//
// Complexity:
// Brute Force O(n^2)
// Sorted Stack O(n)

{ 1, 3, 4, 7, 6, 9, 5, 2 }

9            X
8            |
7        X   |
6        | X |
5        | | | X
4      X | | | |
3    X | | | | |
2    | | | | | | X
1  X | | | | | | |
0  0 1 2 3 4 5 6 7 X

largest rect = width * height = (7-4+1) * 5 or (7-3+1) * 4 = 20

see also AllStockSpans.h, CartesianTree.h
*/
class LargestRectHistogram
{
public:
	LargestRectHistogram(){}
	~LargestRectHistogram(){}

	//enumerate all possible pairs of heights
	int BruteForce(const std::vector<int> & heights)
	{
		std::cout << "LargestRectHistogram BruteForce for \"" << Debug::ToStr1D<int>()(heights) << "\": " << std::endl;
		int res = 0;
		for (int i = 0; i < (int)heights.size(); ++i)
		{
			int minHt = heights[i];
			for (int j = i; j < (int)heights.size(); ++j)
			{
				if (heights[j] < minHt)
					minHt = heights[j];
				int area = minHt * (j - i + 1);
				if (area > res)
					res = area;

				//std::cout << "=>" << heights[i] << "<->" << heights[j] << ": " << minHt << "*" << j - i + 1 << std::endl;
			}
		}
		std::cout << res << std::endl;
		return res;
	}

	int SortedStack(std::vector<int> && heights)
	{
		if (heights.empty())
			return 0;
		std::string before = Debug::ToStr1D<int>()(heights);
		heights.push_back(0);//adding a dummy bar with 0 height at the end for computing the last one
		int N = heights.size();
		std::stack<int> stk;//store the index of the histogram bar in strickly increasing order (pop out all greater equal indices before pushing new index)
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			/*debug*/
			std::ostringstream oss;
			oss << "=>" << heights[i] << ": ";

			while (!stk.empty() && heights[stk.top()] >= heights[i])//pop out all greater equal indices before pushing new index
			{
				//calculate the area of height stk[N-1] in between (stk[N-2],i), exclusive
				//left boundary: height of stk[N-2] is strickly less than height of stk[N-1]
				//right boundary: height of i is less equal than height of stk[N-1]

				//now stk.top() is the central height index
				int h = heights[stk.top()];
				stk.pop();
				//now stk.top() is the left boundary index
				int w = stk.empty() ? i : i - stk.top() - 1;//width: exclude both left boundary stk.top() and right boundary i
				res = std::max(res, h*w);

				/*debug*/
				oss << h << "*" << w;
				stk.empty() ? oss << "(N)" : oss << "(" << this->histoFromStkToStr(stk, heights) << "<->" << heights[i] << ")";
				oss << " ";
			}
			stk.push(i);//push new index

			/*debug*/
			stk.empty() ? oss << "[N]" : oss << "[" << this->histoFromStkToStr(stk, heights) << "]";
			std::cout << oss.str() << std::endl;
		}

		std::cout << "LargestRectHistogram SortedStack for \"" << before << "\": " << res << std::endl;
		return res;
	}

private:
	/*for debug only*/
	std::string histoFromStkToStr(const std::stack<int> & stk, const std::vector<int> & heights)
	{
		std::stack<int> copy(stk);
		std::stack<int> rev;
		while (!copy.empty())
			rev.push(copy.top()), copy.pop();
		rev.swap(copy);
		std::ostringstream oss;
		while (!copy.empty())
		{
			oss << heights[copy.top()];
			copy.pop();
			if (!copy.empty())
				oss << ",";
		}
		return oss.str();
	}

public:
	int SortedStack2(const std::vector<int> & heights)
	{
		if (heights.empty())
			return 0;
		int N = heights.size();
		std::stack<int> stk;//increasing order
		std::vector<int> left;
		for (int i = 0; i < N; ++i)
		{
			while (!stk.empty() && heights[stk.top()] >= heights[i])
				stk.pop();
			
			left.push_back(stk.empty() ? -1 : stk.top());
			stk.push(i);
		}

		while (!stk.empty())
			stk.pop();

		std::vector<int> right(N);
		for (int i = N - 1; i >= 0; --i)
		{
			while (!stk.empty() && heights[stk.top()] >= heights[i])
				stk.pop();
			
			right[i] = stk.empty() ? N : stk.top();
			stk.push(i);
		}

		int maxArea = 0;
		for (int i = 0; i < N; ++i)
		{
			maxArea = std::max(maxArea, heights[i] * (right[i] - left[i] - 1));//exclusive boundaries
		}

		std::cout << "Left:  " << Debug::ToStr1D<int>()(left) << std::endl;
		std::cout << "right: " << Debug::ToStr1D<int>()(right) << std::endl;
		std::cout << "LargestRectHistogram for SortedStack2 for \"" << Debug::ToStr1D<int>()(heights) << "\": " << maxArea << std::endl;
		return maxArea;
	}
};
/*
LargestRectHistogram BruteForce for "1, 3, 4, 7, 6, 9, 5, 2":
20
=>1: [1]
=>3: [1,3]
=>4: [1,3,4]
=>7: [1,3,4,7]
=>6: 7*1(1,3,4<->6) [1,3,4,6]
=>9: [1,3,4,6,9]
=>5: 9*1(1,3,4,6<->5) 6*3(1,3,4<->5) [1,3,4,5]
=>2: 5*4(1,3,4<->2) 4*5(1,3<->2) 3*6(1<->2) [1,2]
=>0: 2*7(1<->0) 1*8(N) [0]
LargestRectHistogram SortedStack for "1, 3, 4, 7, 6, 9, 5, 2": 20
Left:  -1, 0, 1, 2, 2, 4, 2, 0
right: 8, 7, 7, 4, 6, 6, 7, 8
LargestRectHistogram for SortedStack2 for "1, 3, 4, 7, 6, 9, 5, 2": 20
*/
#endif