#ifndef TRAPPING_RAIN_WATER_H
#define TRAPPING_RAIN_WATER_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Trapping Water, (ConstSpace, StackLinearSpace)
Leetcode: Trapping Rain Water
// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it is able to trap after raining.
//
// For example,
// Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
//
// Complexity:
// O(n)

{ 6, 1, 7, 3, 4, 9, 2, 5 }

                   __
9                 |  |
8         __      |  |
7   __   |  |     |  |
6  |  |  |  |     |  |   __
5  |  |  |  |   __|  |  |  |
4  |  |  |  |__|     |  |  |
3  |  |  |           |__|  |
2  |  |__|                 |
1  |_______________________|
0   0  1  2  3  4  5  6  7

Total volume = 5 + 4 + 3 + 3 = 15

Leetcode: Trapping Rain Water II
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.
Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.
Example:
Given the following 3x6 height map:
[
[1,4,3,1,3,2],
[3,2,1,3,2,4],
[2,3,3,2,3,1]
]
Return 4.
*/
class TrappingRainWater
{
public:
	TrappingRainWater(){}
	~TrappingRainWater(){}

	int LinearSpace(int A[], int n)
	{
		if (n < 3)
			return 0;

		//for each height, find the max height on current height's left
		std::vector<int> maxLeft(n, 0);
		for (int i = 1; i < n; ++i)
		{
			maxLeft[i] = std::max(maxLeft[i - 1], A[i - 1]);
		}

		//for each height, find the max height on current height's right
		std::vector<int> maxRight(n, 0);
		for (int i = n - 2; i >= 0; --i)
		{
			maxRight[i] = std::max(maxRight[i + 1], A[i + 1]);
		}

		//for each A[1]~A[n-2], accumulate the volume
		int res = 0;
		for (int i = 1; i < n - 1; ++i)
		{
			int boundaryHeight = std::min(maxLeft[i], maxRight[i]);
			if (boundaryHeight > A[i])
				res += (boundaryHeight - A[i]);
		}
		std::cout << Debug::ToStr1D<int>()(maxLeft) << std::endl;
		std::cout << Debug::ToStr1D<int>()(maxRight) << std::endl;
		std::cout << "TrappingRainWater LinearSpace for \"" << Debug::ToStr1D<int>()(A, n) << "\" is: " << res << std::endl;
		return res;
	}

	int ConstSpace(int A[], int n)
	{
		if (n < 3)
			return 0;

		int maxHeightIdx = 0;
		int res = 0;

		for (int i = 1; i < n; ++i)
			if (A[i] > A[maxHeightIdx])
				maxHeightIdx = i;

		int leftMaxHeight = 0;
		for (int i = 0; i < maxHeightIdx; ++i)
		{
			if (A[i] > leftMaxHeight)
				leftMaxHeight = A[i];
			else
				res += (leftMaxHeight - A[i]);
		}

		int rightMaxHeight = 0;
		for (int i = n - 1; i > maxHeightIdx; --i)
		{
			if (A[i] > rightMaxHeight)
				rightMaxHeight = A[i];
			else
				res += (rightMaxHeight - A[i]);
		}

		std::cout << "TrappingRainWater ConstSpace for \"" << Debug::ToStr1D<int>()(A, n) << "\" is: " << res << std::endl;
		return res;
	}

	int StackLinearSpace(const std::vector<int> & v)
	{
		int N = v.size();
		std::stack<std::pair<int, int> > stk;//first: height, second: index, where height is sorted in decreasing order
		int res = 0;
		for (int i = 0; i < N; ++i)
		{
			int height = 0;
			while (!stk.empty())
			{
				int bar = stk.top().first;
				int pos = stk.top().second;
				res += (std::min(bar, v[i]) - height) * (i - pos - 1);
				height = bar;
				if (v[i] < bar)
					break;
				else
					stk.pop();
			}
			stk.push(std::make_pair(v[i], i));
		}
		
		std::cout << "TrappingRainWater StackLinearSpace for \"" << Debug::ToStr1D<int>()(v) << "\" is: " << res << std::endl;
		return res;
	}

	int StartFrom2EndsConstSpace(const std::vector<int> & v)
	{
		int N = v.size();
		int left = 0;
		int right = N - 1;
		int leftMax = v[0];
		int rightMax = v[N - 1];
		int res = 0;

		while (left < right)
		{
			if (leftMax < rightMax)
			{
				if (v[++left] < leftMax)
					res += (leftMax - v[left]);
				else
					leftMax = v[left];
			}
			else
			{
				if (v[--right] < rightMax)
					res += (rightMax - v[right]);
				else
					rightMax = v[right];
			}
		}

		std::cout << "TrappingRainWater StartFrom2EndsConstSpace for \"" << Debug::ToStr1D<int>()(v) << "\" is: " << res << std::endl;
		return res;
	}

	int FindMaxVolPair_BruteForce(const std::vector<int> & A)
	{
		int N = A.size();
		int maxVol = 0;
		int maxLeft = 0;
		int maxRight = N - 1;
		
		//1. check the volume of every pair with fixing left as the smaller height boundary
		for (int left = 0; left < N - 3; ++left)
		{
			int curVol = INT_MIN;
			int curRight = N - 1;
			for (int right = N - 1; right > left + 1; --right)
			{
				if (A[right - 1] < A[left])
				{
					if (A[curRight] >= A[left])
						curVol += A[left] - A[right - 1];
				}
				else// if (A[right - 1] >= A[left])
				{
					curVol = 0;
					curRight = right - 1;
				}
			}
			if (curVol > maxVol)
			{
				maxVol = curVol;
				maxLeft = left;
				maxRight = curRight;
			}
		}

		//2. check the volume of every pair with fixing right as the smaller height boundary
		for (int right = N - 1; right >= 2; --right)
		{
			int curVol = INT_MIN;
			int curLeft = 0;
			for (int left = 0; left < right - 1; ++left)
			{
				if (A[left + 1] < A[right])
				{
					if (A[curLeft] >= A[right])
						curVol += A[right] - A[left + 1];
				}
				else// if (A[left + 1] >= A[right])
				{
					curVol = 0;
					curLeft = left + 1;
				}
			}
			if (curVol > maxVol)
			{
				maxVol = curVol;
				maxLeft = curLeft;
				maxRight = right;
			}
		}

		std::cout << "TrappingRainWater FindMaxVolPair_BruteForce for \"" << Debug::ToStr1D<int>()(A) << "\" is: " << maxVol << ", [" << maxLeft << "," << maxRight << "]" << std::endl;
		return maxVol;
	}


	int TwoD_BFS_MinHeap(const std::vector<std::vector<int>> & heightMap)
	{
		int N = heightMap.size();
		if (N == 0) return 0;
		int M = heightMap[0].size();
		if (M == 0) return 0;
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;
		std::vector<std::vector<int>> visit(N, std::vector<int>(M, 0));
		for (int i = 0; i < N; ++i)
		{
			minHeap.push({ heightMap[i][0], i*M + 0 });//leftmost col
			visit[i][0] = 1;
			minHeap.push({ heightMap[i][M - 1], i*M + M - 1 });//rightmost col
			visit[i][M - 1] = 1;
		}
		for (int j = 0; j < M; ++j)
		{
			minHeap.push({ heightMap[0][j],0 * M + j });//top row
			visit[0][j] = 1;
			minHeap.push({ heightMap[N - 1][j],(N - 1)*M + j });//bottom row
			visit[N - 1][j] = 1;
		}

		int res = 0;
		int curMax = INT_MIN;
		while (!minHeap.empty())//BFS w/ minHeap
		{
			auto p = minHeap.top();
			minHeap.pop();
			int h = p.first;
			int i = p.second / M;
			int j = p.second % M;
			curMax = std::max(curMax, h);
			std::vector<std::vector<int>> dir({ { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } });
			for (int k = 0; k < 4; ++k)
			{
				int ii = i + dir[k][0];
				int jj = j + dir[k][1];
				if (ii >= 0 && ii < N && jj >= 0 && jj < M && visit[ii][jj] == 0)
				{
					if (heightMap[ii][jj] < curMax)
						res += curMax - heightMap[ii][jj];
					minHeap.push({ heightMap[ii][jj],ii*M + jj });
					visit[ii][jj] = 1;
				}
			}
		}

		Debug::Print2D<int>()(heightMap, false);
		std::cout << "TrappingRainWater TwoD_BFS_MinHeap for the above height map: " << res << std::endl;
		return res;
	}
};
/*
0, 6, 6, 7, 7, 7, 9, 9
9, 9, 9, 9, 9, 5, 5, 0
TrappingRainWater LinearSpace for "6, 1, 7, 3, 4, 9, 2, 5" is: 15
TrappingRainWater ConstSpace for "6, 1, 7, 3, 4, 9, 2, 5" is: 15
TrappingRainWater StackLinearSpace for "6, 1, 7, 3, 4, 9, 2, 5" is: 15
TrappingRainWater StartFrom2EndsConstSpace for "6, 1, 7, 3, 4, 9, 2, 5" is: 15
TrappingRainWater FindMaxVolPair_BruteForce for "6, 1, 7, 3, 4, 9, 2, 5" is: 7, [2,5]
TrappingRainWater ConstSpace for "1, 2, 1, 3, 4, 4, 5, 1, 2, 0, 3" is: 7
TrappingRainWater FindMaxVolPair_BruteForce for "1, 2, 1, 3, 4, 4, 5, 1, 2, 0, 3" is: 6, [6,10]
TrappingRainWater ConstSpace for "1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1" is: 18
TrappingRainWater FindMaxVolPair_BruteForce for "1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1" is: 17, [7,16]
[rY][cX]
Row#0	= 1, 4, 3, 1, 3, 2
Row#1	= 3, 2, 1, 3, 2, 4
Row#2	= 2, 3, 3, 2, 3, 1

TrappingRainWater TwoD_BFS_MinHeap for the above height map: 4
*/

#endif

/*
http://www.programering.com/a/MDM4QzMwATU.html
http://massivealgorithms.blogspot.tw/2014/06/leetcode-trapping-rain-water-darrens.html
http://www.techsamaritan.org/courses/defasun/interviewQ2.html
*/