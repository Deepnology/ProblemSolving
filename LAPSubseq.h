/*DP*/
#ifndef LAP_SUBSEQ_H
#define LAP_SUBSEQ_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
http://www.geeksforgeeks.org/length-of-the-longest-arithmatic-progression-in-a-sorted-array/
An arithmetic progression (AP) or arithmetic sequence is a sequence of numbers such that difference between the consecutive terms is constant.
Given a set of SORTED numbers, find the length of the longest arithmetic progression (LLAP) in it.

DP2D: O(n^2) time, O(n^2) space
*/
class LAPSubseq
{
public:
	LAPSubseq(){}
	~LAPSubseq(){}

	//special case for 3 entries
	bool ExistArithmeitcThree_Sorted(const std::vector<int> & v)//O(n^2) time
	{
		int N = v.size();
		bool res = false;
		/*consider each element in v as the second element of AP*/
		for (int mid = 1; mid < N - 1; ++mid)
		{
			int left = mid - 1;
			int right = mid + 1;
			while (left >= 0 && right < N)
			{
				if (v[left] + v[right] == 2 * v[mid])
				{
					res = true;
					break;
				}
				else if (v[left] + v[right] < 2 * v[mid])
					++right;
				else
					--left;
			}
			if (res)
				break;
		}

		std::cout << "LAPSubseq ExistArithmeticThree_Sorted for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}

	int Len_DP2D_Sorted(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::vector<int> > dp(N, std::vector<int>(N));
		/*
		dp[left][mid]: LLAP with v[left], v[mid] as first two elements of AP
		*/
		int llap = 2;

		/*
		dp[0][N-1]...dp[N-1][N-1]: LLAP with (v[0],v[N-1])...(v[N-1],v[N-1]) are all 2
		(the LLAP with first any element and second the last element in v are all 2)
		0  1  2  3  .... N-3  N-2  N-1
		|                 |    |____|
		|				  |      2  |
		|				  |_________|
		|				       2    |
		|		    ....            |
		|___________________________|
		             2
		*/
		for (int i = 0; i < N; ++i)
			dp[i][N - 1] = 2;

		/*
		consider each element in v as the second element
		since initial LLAP between each element and the last element is 2, we start from back
		*/
		for (int mid = N - 2; mid >= 1; --mid)
		{
			int left = mid - 1;
			int right = mid + 1;
			while (left >= 0 && right < N)
			{
				if (v[left] + v[right] < 2 * v[mid])
					++right;
				else if (v[left] + v[right] > 2 * v[mid])
				{
					/*before changing left, set dp[left][mid] as 2*/
					dp[left][mid] = 2;
					--left;
				}
				else
				{
					/*
					LLAP with left and mid as first two elements is equal to
					LLAP with mid and right as first two elements plus 1
					*/
					dp[left][mid] = dp[mid][right] + 1;
					llap = std::max(llap, dp[left][mid]);
					--left;
					++right;
				}
			}

			/*
			if the loop was stopped due to right becoming more than N-1
			, set the remaining entities in column mid as 2
			*/
			while (left >= 0)
			{
				dp[left][mid] = 2;
				--left;
			}
		}
		Debug::Print2D<int>()(dp, false);
		std::cout << "LAPSubseq Len_DP2D_Sorted for \"" << Debug::ToStr1D<int>()(v) << "\": " << llap << std::endl;
		return llap;
	}

	int Len_DP2D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<std::unordered_map<int,int>> dp(N, std::unordered_map<int,int>());
		int res = 2;
		for (int i = 1; i < N; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				long diff = (long)v[i] - (long)v[j];
				if (diff > INT_MAX || diff < INT_MIN)
					continue;
				if (dp[j].count(diff))
				{
					dp[i][diff] = dp[j][diff]+1;
					res = std::max(res, dp[i][diff]);
				}
				else
				{
					dp[i][diff] = 2;
				}
			}
		}

		std::cout << "LAPSubseq Len_DP2D for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
};
/*
LAPSubseq ExistArithmeticThree_Sorted for "1, 7, 10, 13, 14, 19": 1
[rY][cX]
Row#0	= 0, 4, 3, 2, 2, 2
Row#1	= 0, 0, 3, 3, 2, 2
Row#2	= 0, 0, 0, 2, 2, 2
Row#3	= 0, 0, 0, 0, 2, 2
Row#4	= 0, 0, 0, 0, 0, 2
Row#5	= 0, 0, 0, 0, 0, 2

LAPSubseq Len_DP2D_Sorted for "1, 7, 10, 13, 14, 19": 4
LAPSubseq ExistArithmeticThree_Sorted for "1, 7, 10, 15, 27, 29": 1
[rY][cX]
Row#0	= 0, 2, 2, 3, 2, 2
Row#1	= 0, 0, 2, 2, 2, 2
Row#2	= 0, 0, 0, 2, 2, 2
Row#3	= 0, 0, 0, 0, 2, 2
Row#4	= 0, 0, 0, 0, 0, 2
Row#5	= 0, 0, 0, 0, 0, 2

LAPSubseq Len_DP2D_Sorted for "1, 7, 10, 15, 27, 29": 3
LAPSubseq ExistArithmeticThree_Sorted for "2, 4, 6, 8, 10": 1
[rY][cX]
Row#0	= 0, 5, 3, 2, 2
Row#1	= 0, 0, 4, 2, 2
Row#2	= 0, 0, 0, 3, 2
Row#3	= 0, 0, 0, 0, 2
Row#4	= 0, 0, 0, 0, 2

LAPSubseq Len_DP2D_Sorted for "2, 4, 6, 8, 10": 5
LAPSubseq Len_DP2D for "20, 1, 15, 3, 10, 5, 8": 4
*/
#endif