/*Greedy*DP*Recur*/
#ifndef LONGEST_NONDECREASING_SUBSEQ_H
#define LONGEST_NONDECREASING_SUBSEQ_H
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, DynamicProgramming: Find the longest nondecreasing subsequence
variation of LIS
Len_Greedy_UpperBound: O(nlogn) time, O(n) space
Len_DP1D_Quadratic: O(n^2) time, O(n) space
FindAll_InExcludeRecur: O(2^n) time

See also LIS.h
*/
class LongestNondecreasingSubseq
{
public:
	LongestNondecreasingSubseq(){}
	~LongestNondecreasingSubseq(){}

	int Len_Greedy_UpperBound(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> sorted;
		for (int i = 0; i < N; ++i)
		{
			std::vector<int>::iterator ub = std::upper_bound(sorted.begin(), sorted.end(), v[i]);

			if (ub == sorted.end())
				sorted.push_back(v[i]);
			else
				*ub = v[i];

			std::cout << "sorted: " << Debug::ToStr1D<int>()(sorted) << std::endl;
		}
		int res = sorted.size();

		std::cout << "LongestNondecreasingSubseq Len_Greedy_LowerBound for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
	int Len_DP1D_Quadratic(const std::vector<int> & x)
	{
		int N = x.size();
		std::vector<int> dp(N, 1);//longest length at each index
		std::vector<int> prevIdx(N, -1);//previous index of LIS at each index
		int maxIncrCount = 1;
		int maxIncrIdx = 0;//the last index of the LIS
		for (int curEnd = 1; curEnd < N; ++curEnd)
		{
			for (int curStart = 0; curStart < curEnd; ++curStart)
			{
				if (x[curEnd] >= x[curStart] && dp[curStart] + 1 > dp[curEnd])//end > cur
				{
					dp[curEnd] = dp[curStart] + 1;
					prevIdx[curEnd] = curStart;
				}
			}
			if (dp[curEnd] > maxIncrCount)
			{
				maxIncrCount = dp[curEnd];
				maxIncrIdx = curEnd;
			}
			std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		}

		std::vector<int> lis(maxIncrCount);
		int lisLen = maxIncrCount;
		while (lisLen-- > 0)
		{
			lis[lisLen] = x[maxIncrIdx];
			maxIncrIdx = prevIdx[maxIncrIdx];
		}
		std::cout << "LongestNondecreasingSubseq DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << " (" << Debug::ToStr1D<int>()(lis) << ")" << std::endl;
		return maxIncrCount;
	}

public:
	int FindAll_InExcludeRecur(const std::vector<int> & x)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > incrSeqs;
		int res = this->findAll_InExcludeRecur(x, 0, INT_MIN, 0, path, incrSeqs);
		std::cout << "LongestNondecreasingSubseq FindAll_InExcludeRecur for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << std::endl;
		Debug::Print2D<int>()(incrSeqs, false);
		return res;
	}
private:
	int findAll_InExcludeRecur(const std::vector<int> & x, int curBegin, int curMaxVal, int curIncrCount
		, std::vector<int> & path, std::vector<std::vector<int> > & incrSeqs)
	{
		int N = x.size();
		if (curBegin == N)
		{
			incrSeqs.push_back(path);
			return curIncrCount;
		}

		int incrCountExcludeThis = this->findAll_InExcludeRecur(x, curBegin + 1, curMaxVal, curIncrCount, path, incrSeqs);//exclude and skip current element
		int incrCountIncludeThis = 0;
		if (x[curBegin] >= curMaxVal)
		{
			path.push_back(x[curBegin]);
			incrCountIncludeThis = this->findAll_InExcludeRecur(x, curBegin + 1, x[curBegin], curIncrCount + 1, path, incrSeqs);//include current element
			path.pop_back();
		}
		return std::max(incrCountExcludeThis, incrCountIncludeThis);
	}
};
#endif