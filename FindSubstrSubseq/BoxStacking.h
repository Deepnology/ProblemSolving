/*DP*/
#ifndef BOX_STACKING_H
#define BOX_STACKING_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/dynamic-programming-set-14-variations-of-lis/
http://www.geeksforgeeks.org/dynamic-programming-set-21-box-stacking-problem/
Cracking the coding interview: recursion and dynamic programming
variation of LIS

You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers). 
You want to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base. 
It is also allowable to use multiple instances of the same type of box.

base area = width * depth (depth can be viewed as length)(assume the bigger one of width/depth is always wdith, the smaller one is depth)

n types of boxes with each has 3 rotations {w,d,h},{h,w,d},{h,d,w} (suppose the first 2 forms the base area) based on the different base area combinations
=> it can be thought of there are totally 3*n boxes to stack
=> we can sort the 3*n boxes with the base area of each box in decreasing order
=> then find the longest decreasing subsequence of (w,d) pairs (boxes), where both w and d in pairs must be in decreasing order, respectively
=> sum up the height of each box in the longest decreasing subsequence

Sort: O(nlogn) time
LDS with DP1D: O(n^2) time, O(n) space
=> O(n^2) time, O(n) space in total
*/
class BoxStacking
{
public:
	BoxStacking(){}
	~BoxStacking(){}

	int Solve(const std::vector<std::pair<std::pair<int, int>, int> > & boxes)//width, depth, height
	{
		int N = boxes.size();

		/*1. create an array containing all 3 base-area combinations of each box*/
		std::vector<std::pair<std::pair<int, int>, int> > rot3;
		for (int i = 0; i < N; ++i)
		{
			//select (width, depth) as base area
			auto b = boxes[i];
			b.first.first = std::max(boxes[i].first.first, boxes[i].first.second);//select max(width, depth) as width
			b.first.second = std::min(boxes[i].first.first, boxes[i].first.second);//select min(width, depth) as depth
			rot3.push_back(b);
			
			//select (width, height) as base area
			auto b2 = b;
			b2.first.first = std::max(b.first.first, b.second);//select max(width, height) as width
			b2.first.second = std::min(b.first.first, b.second);//select min(width, height) as depth
			b2.second = b.first.second;//select depth as height
			rot3.push_back(b2);

			//select (depth, height) as base area
			auto b3 = b;
			b3.first.first = std::max(b.first.second, b.second);//select max(depth, height) as width
			b3.first.second = std::min(b.first.second, b.second);//select min(depth, height) as depth
			b3.second = b.first.first;//select width as height
			rot3.push_back(b3);
		}

		N *= 3;
		/*2. sort by base area in decreasing order*/
		std::sort(rot3.begin(), rot3.end(), [](const std::pair<std::pair<int, int>, int> & a, const std::pair<std::pair<int, int>, int> & b)->bool
		{
			return a.first.first * a.first.second > b.first.first * b.first.second;
		});

		/*3. find the longest decreasing subsequence in rot3*/
		std::vector<int> dp(N, 1);//longest length at each index
		std::vector<int> prevIdx(N, -1);//previous index of LDS at each index
		int maxDecrCount = 1;
		int maxDecrIdx = 0;//the last index of the LDS
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (rot3[curStart].first.first > rot3[curEnd].first.first && rot3[curStart].first.second > rot3[curEnd].first.second && dp[curStart] + 1 > dp[curEnd])
				{
					dp[curEnd] = dp[curStart] + 1;
					prevIdx[curEnd] = curStart;
				}
			}
			if (dp[curEnd] > maxDecrCount)
			{
				maxDecrCount = dp[curEnd];
				maxDecrIdx = curEnd;
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::vector<std::pair<std::pair<int, int>, int> > lds(maxDecrCount);
		int ldsLen = maxDecrCount;
		while (ldsLen-- > 0)
		{
			lds[ldsLen] = rot3[maxDecrIdx];
			maxDecrIdx = prevIdx[maxDecrIdx];
		}

		int heightSum = 0;
		int M = lds.size();
		for (int i = 0; i < M; ++i)
			heightSum += lds[i].second;

		std::cout << "BoxStacking for \"" << Debug::ToStr1D<int>()(rot3) << "\": " << heightSum << " (" << Debug::ToStr1D<int>()(lds) << ")" << std::endl;
		return heightSum;
	}
};
/*
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 4, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 4, 3, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 4, 3, 4, 1, 1, 1, 1, 1
1, 1, 2, 3, 4, 3, 4, 4, 1, 1, 1, 1
1, 1, 2, 3, 4, 3, 4, 4, 5, 1, 1, 1
1, 1, 2, 3, 4, 3, 4, 4, 5, 6, 1, 1
1, 1, 2, 3, 4, 3, 4, 4, 5, 6, 6, 1
1, 1, 2, 3, 4, 3, 4, 4, 5, 6, 6, 7
BoxStacking for "[(32,12),10], [(32,10),12], [(12,10),32], [(7,6),4], [(6,5),4], [(7,4),6], [(6,4),7], [(6,4),5], [(5,4),6], [(3,2),1], [(3,1),2], [(2,1),3]": 60 ([(32,12),10], [(12,10),32], [(7,6),4], [(6,5),4], [(5,4),6], [(3,2),1], [(2,1),3])
*/
#endif