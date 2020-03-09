#ifndef CONTAINER_W_MOST_WATER_H
#define CONTAINER_W_MOST_WATER_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Container With Most Water
// Given n non-negative integers a1, a2, ..., an, where each represents a
// point at coordinate (i, ai). n vertical lines are drawn such that the two
// endpoints of line i is at (i, ai) and (i, 0). Find two lines, which
// together with x-axis forms a container, such that the container contains
// the most water.
//
// Note: You may not slant the container.
//
// Complexity:
// Greedy: O(n) time, O(1) space
// Burte Force: O(n^2) time, O(1) space

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
0  1 2 3 4 5 6 7 8

max area = width * height = (7-3) * 4 = 16

Elements of programming interview, Greedy: Compute the maximum water trapped by a pair of vertical lines
Given an array of n lines, each parallel to the y-axis.
Define the water trapped by lines i and j in the array to be |j-i| * min(A[i],A[j]).
Find the pair of lines that together with the x-axis traps the most water.

{ 1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1 }

6                       X
5                    X  |
4              X  X  |  |                          X
3           X  |  |  |  |        X     X           |
2     X     |  |  |  |  |  X     |     |  X     X  |
1  X  |  X  |  |  |  |  |  |  X  |  X  |  |  X  |  |  X
0  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17


6                       X
5              ______X__|___________________________
4              X  X  |  |                          X
3           X  |  |  |  |        X     X           |
2     X     |  |  |  |  |  X     |     |  X     X  |
1  X  |  X  |  |  |  |  |  |  X  |  X  |  |  X  |  |  X
0  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17

The line pair that traps most water is A[4] and A[16] = 4 * (16-4) = 48
*/
class ContainerWMostWater
{
public:
	ContainerWMostWater(){}
	~ContainerWMostWater(){}

	int Greedy(const std::vector<int> & heights)
	{
		int start = 0;
		int end = heights.size() - 1;
		int res = 0;
		while (start < end)
		{
			res = std::max(res, std::min(heights[start], heights[end])*(end - start));
			
			//keep the bigger bound, check the area by advancing the smaller bound
			if (heights[start] <= heights[end])//advance start to right
			{
				do
				{
					++start;
				} while (start < end && heights[start] <= heights[start - 1]);
				/*
				always skip smaller or equal bounds because smaller width after advance won't produce bigger area
				only bigger bound has a chance to produce a bigger area
				now start points to the next right bigger bound
				*/
			}
			else//advance end to left
			{
				do
				{
					--end;
				} while (start < end && heights[end] <= heights[end + 1]);
				/*
				always skip smaller or equal bounds because smaller width after advance won't produce bigger area
				only bigger bound has a chance to produce a bigger area
				now end points to the next left bigger bound
				*/
			}
		}

		std::cout << "ContainerWMostWater Greedy for \"" << Debug::ToStr1D<int>()(heights) << "\": " << res << std::endl;
		return res;
	}
	int Greedy2(const std::vector<int> & A)//same thing (better)
	{
		int N = A.size();
		int left = 0;
		int right = N - 1;
		int maxVol = 0;
		int maxLeft = 0;
		int maxRight = N - 1;

		while (left < right)
		{
			int curVol = std::min(A[left], A[right]) * (right - left);
			if (curVol > maxVol)
			{
				maxVol = curVol;
				maxLeft = left;
				maxRight = right;
			}

			if (A[left] > A[right])
				--right;//advance the shorter boundary
			else if (A[left] < A[right])
				++left;//advance the shorter boundary
			else
			{
				++left;
				--right;
			}
		}

		std::cout << "ContainerWMostWater Greedy2 for \"" << Debug::ToStr1D<int>()(A) << "\" is: " << maxVol << ", [" << maxLeft << "," << maxRight << "]" << std::endl;
		return maxVol;
	}

	/*enumerate all possible pairs of points*/
	int BruteForce(const std::vector<int> & heights)
	{
		int res = 0;
		int N = heights.size();
		if (N < 2)
			return res;
		for (int end = 1; end < N; ++end)
		{
			for (int start = 0; start < end; ++start)
			{
				int area = std::abs(end - start) * std::min(heights[start], heights[end]);
				if (area > res)
					res = area;
			}
		}

		std::cout << "ContainerWMostWater BruteForce for \"" << Debug::ToStr1D<int>()(heights) << "\": " << res << std::endl;
		return res;
	}

};
/*
ContainerWMostWater BruteForce for "1, 3, 4, 7, 6, 9, 5, 2": 16
ContainerWMostWater Greedy for "1, 3, 4, 7, 6, 9, 5, 2": 16
ContainerWMostWater Greedy2 for "1, 3, 4, 7, 6, 9, 5, 2" is: 16, [2,6]
ContainerWMostWater BruteForce for "1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1": 48
ContainerWMostWater Greedy for "1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1": 48
ContainerWMostWater Greedy2 for "1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1" is: 48, [4,16]
*/
#endif