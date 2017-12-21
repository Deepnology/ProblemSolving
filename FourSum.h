#ifndef FOUR_SUM_H
#define FOUR_SUM_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: 4Sum
// 4Sum
// Given an array S of n integers, are there elements a, b, c, and d in S such
// that a + b + c + d = target?
// Find all unique quadruplets in the array which gives the sum of target.
// Note:
// Elements in a quadruplet (a,b,c,d) must be in non-descending order.
// (ie, a <= b <= c <= d)
// The solution set must not contain duplicate quadruplets.
// For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
// A solution set is:
// (-1,  0, 0, 1)
// (-2, -1, 1, 2)
// (-2,  0, 0, 2)
//
// Complexity: O(n^3) time, O(1) space

Leetcode: 4Sum II
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.
To make problem a bit easier, all A, B, C, D have same length of N where 0 <= N <= 500.
All integers are in the range of -2^28 to 2^28 - 1 and the result is guaranteed to be at most 2^31 - 1.
Example:
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]
Output:
2
Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/
class FourSum
{
public:
	FourSum(){}
	~FourSum(){}

	std::vector<std::vector<int>> FindAll_Sort_Greedy(std::vector<int> & num, int target)
	{
		int N = num.size();
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int> > res;

		for (int i = 0; i < N - 3; ++i)//num[0]~num[N-4]
		{
			if (i > 0 && num[i] == num[i - 1])
				continue;//skip repeats

			for (int start = i + 1; start < N - 2; ++start)//num[i+1]~num[N-3]
			{
				if (start > i + 1 && num[start] == num[start - 1])
					continue;//skip repeats

				int middle = start + 1;//num[index+1+1]
				int end = N - 1;//num[N-1]

				while (middle < end)
				{
					int sum = num[i] + num[start] + num[middle] + num[end];
					if (sum < target)
						++middle;
					else if (sum > target)
						--end;
					else
					{
						res.push_back(std::vector<int>({ num[i], num[start], num[middle], num[end] }));
						do
						{
							++middle;
						} while (middle < end && num[middle] == num[middle - 1]);//skip repeats
						do
						{
							--end;
						} while (middle < end && num[end] == num[end + 1]);//skip repeats
					}

				}
			}
		}

		std::cout << "FourSum FindAll_Sort_Greedy for " << target << " in \"" << Debug::ToStr1D<int>()(num) << "\":" << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//4Sum II
	int CountSumTo0_HashMap(std::vector<int> & A, std::vector<int> & B, std::vector<int> & C, std::vector<int> & D)
	{
		std::unordered_map<int, int> sumMap;
		int a = A.size();
		int b = B.size();
		int c = C.size();
		int d = D.size();
		for (int i = 0; i < a; ++i)
			for (int j = 0; j < b; ++j)
				++sumMap[A[i] + B[j]];

		int count = 0;
		for (int i = 0; i < c; ++i)
			for (int j = 0; j < d; ++j)
				if (sumMap.count(-C[i] - D[j]))
					count += sumMap[-C[i] - D[j]];

		std::cout << "FourSum_CountSumTo0_HashMap for \"" << Debug::ToStr1D<int>()(A) << "\", \"" << Debug::ToStr1D<int>()(B) << "\", \"" << Debug::ToStr1D<int>()(C) << "\", \"" << Debug::ToStr1D<int>()(D) << "\": " << count << std::endl;
		return count;
	}
	int CountSumTo0_2SortedArraysGreedy(std::vector<int> & A, std::vector<int> & B, std::vector<int> & C, std::vector<int> & D)
	{
		int N = A.size(); if (N == 0) return 0;
		std::vector<int> AB;
		std::vector<int> CD;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				AB.push_back(A[i] + B[j]);
				CD.push_back(C[i] + D[j]);
			}
		}
		std::sort(AB.begin(), AB.end());
		std::sort(CD.begin(), CD.end());
		int i = 0;
		int j = N*N - 1;
		int res = 0;
		while (i < N*N && j >= 0)
		{
			if (AB[i] + CD[j] > 0)//too big
				--j;
			else if (AB[i] + CD[j] < 0)//too small
				++i;
			else
			{
				int ii = i;
				while (ii + 1 < N*N && AB[ii + 1] == AB[ii])
					++ii;
				int jj = j;
				while (jj - 1 >= 0 && CD[jj - 1] == CD[jj])
					--jj;
				res += (ii - i + 1)*(j - jj + 1);
				i = ii + 1;
				j = jj - 1;
			}
		}
		
		std::cout << "FourSum_CountSumTo0_2SortedArrayGreedy for \"" << Debug::ToStr1D<int>()(A) << "\", \"" << Debug::ToStr1D<int>()(B) << "\", \"" << Debug::ToStr1D<int>()(C) << "\", \"" << Debug::ToStr1D<int>()(D) << "\": " << res << std::endl;
		return res;
	}
};
/*
FourSum FindAll_Sort_Greedy for 0 in "-2, -1, 0, 0, 1, 2":[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]
FourSum_CountSumTo0_HashMap for "1, 2", "-2, -1", "-1, 2", "0, 2": 2
FourSum_CountSumTo0_2SortedArrayGreedy for "1, 2", "-2, -1", "-1, 2", "0, 2": 2
*/
#endif