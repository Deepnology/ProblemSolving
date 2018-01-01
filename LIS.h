/*Greedy*DP*Recur*/
#ifndef _LIS_H_
#define _LIS_H_
//Longest Increasing Subsequence
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Longest Increasing Subsequence (requires O(n^2) time)
http://stackoverflow.com/questions/6129682/longest-increasing-subsequenceonlogn
http://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithms
http://stackoverflow.com/questions/3992697/longest-increasing-subsequence?rq=1
http://stackoverflow.com/questions/13781979/memoization-for-recursive-longest-increasing-subsequence
http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/

1. Greedy Find length of LIS with lower bound: O(nlogn) time, O(n) space
(Note: Greedy approach can only find the length of LIS, its result sorted array is not necessarily the correct LIS.)
2. DP 1D Find length of LIS and one possible LIS: O(n^2) time, O(n) space
3. Backtracking In/Exclude Find All IS and length of LIS: O(2^n) time
4. Backtracking Find All IS and length of LIS: O(2^n) time

Count all increasing subsequences
http://www.geeksforgeeks.org/count-all-increasing-subsequences/

Leetcode: Number of Longest Increasing Subsequence
Given an unsorted array of integers, find the number of longest increasing subsequence.
Example 1:
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
Example 2:
Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.
*/
class LIS
{
public:
	LIS(){}
	~LIS(){}
	/*
	Normal lower bound:
	Returns an index of the first element in the range [first,last) which does not compare less than val (can compare both equal to or greater than val).
	Normal upper bound:
	Returns an index of the first element in the range [first,last) which compares ONLY greater than val.
	*/
	int Len_Greedy_LowerBound(const std::vector<int> & x)
	{
		int N = x.size();
		if (N == 1)
			return 1;
		std::vector<int> sorted(N, INT_MAX);
		for (int i = 0; i < N; ++i)
		{
			//1. insert x[i] to the first element which does not compare less than x[i] in dp
			std::vector<int>::iterator lb = std::lower_bound(sorted.begin(), sorted.end(), x[i]);
			*lb = x[i];//update *lb, which is INT_MAX or existing num, with x[i]
			std::cout << "sorted: " << Debug::ToStr1D<int>()(sorted) << std::endl;
		}
		//2. the LIS length is the number of all elements before the first INT_MAX
		int res = std::lower_bound(sorted.begin(), sorted.end(), INT_MAX) - sorted.begin();

		std::cout << "LIS Len_Greedy_LowerBound for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << std::endl;
		return res;
	}
	int Len_Greedy_LowerBound2(const std::vector<int> & x)//better
	{
		int N = x.size();
		std::vector<int> sorted;
		for (int i = 0; i < N; ++i)
		{
			std::vector<int>::iterator lb = std::lower_bound(sorted.begin(), sorted.end(), x[i]);

			if (lb == sorted.end())
				sorted.push_back(x[i]);
			else
				*lb = x[i];
			
			std::cout << "sorted: " << Debug::ToStr1D<int>()(sorted) << std::endl;
		}
		int res = sorted.size();

		std::cout << "LIS Len_Greedy_LowerBound2 for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << std::endl;
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
				if (x[curEnd] > x[curStart] && dp[curStart] + 1 > dp[curEnd])//end > cur
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
		std::cout << "LIS Len_DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << " (" << Debug::ToStr1D<int>()(lis) << ")" << std::endl;
		return maxIncrCount;
	}

	//to count LIS, just collect dp[i] where dpMaxLen[i]==maxLen
	int Count_IS_DP1D_Quadratic(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> dp(N, 1);//dp[i]: count of incr subseq ending at i

		for (int j = 1; j < N; ++j)
		{
			for (int i = 0; i < j; ++i)
			{
				if (v[i] < v[j])
					dp[j] += dp[i];
			}
		}
		
		int res = 0;
		for (int i = 0; i < N; ++i)
			res += dp[i];

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "LIS Count_IS_DP1D_Quadratic for \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
		return res;
	}
	int Count_IS_DP1D_Linear(const std::string & s)//assume s contains only lower case chars
	{
		std::vector<int> dp(26, 0);//dp[i]: count of incr subseq ending at char i+'a'
		int N = s.size();
		for (int i = 0; i < N; ++i)
		{
			for (int c = s[i] - 'a' - 1; c >= 0; --c)
				dp[s[i] - 'a'] += dp[c];
			++dp[s[i] - 'a'];
		}

		int res = 0;
		for (int i = 0; i < 26; ++i)
			res += dp[i];

		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "LIS Count_IS_DP1D_Linear for \"" << s << "\": " << res << std::endl;
		return res;
	}
	//Leetcode: Number of Longest Increasing Subsequence
	int Count_LIS_DP1D(const std::vector<int> & v)
	{
		int N = v.size();
		std::vector<int> dp(N, 1);//dp[i]: len of longest incr subseq ending at i
		std::vector<int> dp2(N, 1);//dp2[i]: count of longest incr subseq ending at i
		int maxLen = 0;
		int res = 0;
		for (int j = 0; j < N; ++j)
		{
			for (int i = 0; i < j; ++i)
			{
				if (v[i] < v[j])
				{
					if (dp[i] + 1 > dp[j])
					{
						dp[j] = dp[i] + 1;
						dp2[j] = dp2[i];
					}
					else if (dp[i] + 1 == dp[j])
						dp2[j] += dp2[i];
				}
			}
			if (maxLen < dp[j])
			{
				maxLen = dp[j];
				res = dp2[j];
			}
			else if (maxLen == dp[j])
				res += dp2[j];
		}
		return res;
	}


public:
	int FindAll_InExcludeRecur(const std::vector<int> & x)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > incrSeqs;
		int res = this->findAll_InExcludeRecur(x, 0, INT_MIN, 0, path, incrSeqs);
		std::cout << "LIS FindAll_InExcludeRecur for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << std::endl;
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
		if (x[curBegin] > curMaxVal)
		{
			path.push_back(x[curBegin]);
			incrCountIncludeThis = this->findAll_InExcludeRecur(x, curBegin + 1, x[curBegin], curIncrCount + 1, path, incrSeqs);//include current element
			path.pop_back();
		}
		return std::max(incrCountExcludeThis, incrCountIncludeThis);
	}

public:
	int Len_InExcludeRecur(const std::vector<int> & x)//O(2^n) time
	{
		int res = this->len_InExcludeRecur(x, 0, INT_MIN, 0);
		std::cout << "LIS InExcludeRecur for \"" << Debug::ToStr1D<int>()(x) << "\": " << res << std::endl;
		return res;
	}
private:
	int len_InExcludeRecur(const std::vector<int> & x, int curBegin, int curMaxVal, int curIncrCount)
	{
		int N = x.size();
		if (curBegin == N)
			return curIncrCount;

		int incrCountExcludeThis = this->len_InExcludeRecur(x, curBegin + 1, curMaxVal, curIncrCount);//exclude and skip current element
		int incrCountIncludeThis = 0;
		if (x[curBegin] > curMaxVal)
			incrCountIncludeThis = this->len_InExcludeRecur(x, curBegin + 1, x[curBegin], curIncrCount + 1);//include current element
		return std::max(incrCountExcludeThis, incrCountIncludeThis);
	}

public:
	//Leetcode: Increasing Subsequences
	//find all distinct increasing subsequences whose length >= 2 (equality is treated as increasing)
	std::vector<std::vector<int>> FindAllDistinct_FixRecur(const std::vector<int> & x)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > incrSeqs;
		this->findAllDistinct_FixRecur(x, 0, path, incrSeqs);
		std::cout << "LIS FindAllDistinct_FixRecur for \"" << Debug::ToStr1D<int>()(x) << "\": " << std::endl;
		Debug::Print2D<int>()(incrSeqs, false);
		return incrSeqs;
	}
private:
	void findAllDistinct_FixRecur(const std::vector<int> & x, int begin, std::vector<int> & path, std::vector<std::vector<int>> & incrSeqs)
	{
		int N = x.size();
		if (path.size() >= 2)
		{
			incrSeqs.push_back(path);
		}
		std::unordered_set<int> visit;
		for (int i = begin; i < N; ++i)
		{
			if (begin > 0 && x[i] < x[begin - 1])
				continue;
			if (visit.count(x[i]))
				continue;
			visit.insert(x[i]);
			path.push_back(x[i]);
			findAllDistinct_FixRecur(x, i + 1, path, incrSeqs);
			path.pop_back();
		}
	}



public:
	/*
	O(2^n) time
	*/
	int Len_ShrinkLen_Recur(const std::vector<int> & x)
	{
		int N = x.size();
		int maxIncrCount = 1;
		this->len_CurTotalLen_Recur(x, N, maxIncrCount);

		std::cout << "LIS Len_ShrinkLen_Recur for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << std::endl;
		return maxIncrCount;
	}
private:
	int len_CurTotalLen_Recur(const std::vector<int> & x, int curTotalLen, int & maxIncrCount)
	{
		if (curTotalLen == 1)
			return 1;

		int curIncrCount = 1;
		for (int curLen = 1; curLen < curTotalLen; ++curLen)
		{
			int prevIncrCount = this->len_CurTotalLen_Recur(x, curLen, maxIncrCount);

			//post order
			if (x[curLen - 1] < x[curTotalLen - 1] && prevIncrCount + 1 > curIncrCount)
			{
				curIncrCount = prevIncrCount + 1;
			}
		}
		if (maxIncrCount < curIncrCount)
			maxIncrCount = curIncrCount;

		return curIncrCount;
	}
public:
	int Len_ShrinkLen_DP_Recur(const std::vector<int> & x)
	{
		int N = x.size();
		int maxIncrCount = 1;
		std::vector<int> dp(N, -1);
		this->len_CurTotalLen_DP_Recur(x, N, maxIncrCount, dp);
		std::cout << Debug::ToStr1D<int>()(dp) << std::endl;
		std::cout << "LIS Len_ShrinkLen_DP_Recur for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << std::endl;
		return maxIncrCount;
	}
private:
	int len_CurTotalLen_DP_Recur(const std::vector<int> & x, int curTotalLen, int & maxIncrCount, std::vector<int> & dp)
	{
		if (curTotalLen == 1)
			return 1;

		int curIncrCount = 1;
		for (int curLen = 1; curLen < curTotalLen; ++curLen)
		{
			int prevIncrCount = dp[curLen] == -1 ? dp[curLen] = this->len_CurTotalLen_Recur(x, curLen, maxIncrCount) : dp[curLen];

			//post order
			if (x[curLen - 1] < x[curTotalLen - 1] && prevIncrCount + 1 > curIncrCount)
			{
				curIncrCount = prevIncrCount + 1;
			}
		}
		if (maxIncrCount < curIncrCount)
			maxIncrCount = curIncrCount;

		return curIncrCount;
	}



public:
	/*
	O(2^n) time
	*/
	int FindAll_FixRecur(const std::vector<int> & x)//this is still not working....
	{
		std::vector<int> path;
		std::vector<std::vector<int> > incrSeqs;
		int maxIncrCount = INT_MIN;
		this->findAll_FixRecur(x, 0, INT_MIN, 0, path, incrSeqs, maxIncrCount);

		std::cout << "LIS FindAll_FixRecur for \"" << Debug::ToStr1D<int>()(x) << "\": " << maxIncrCount << std::endl;
		Debug::Print2D<int>()(incrSeqs, false);
		return maxIncrCount;
	}
private:
	void findAll_FixRecur(const std::vector<int> & x, int curBegin, int curMaxVal, int curIncrCount
		, std::vector<int> & path, std::vector<std::vector<int> > & incrSeqs, int & maxIncrCount)
	{
		int N = x.size();
		if (curBegin == N)
		{
			std::cout << Debug::ToStr1D<int>()(path) << std::endl;
			incrSeqs.push_back(path);
			if (curIncrCount > maxIncrCount)
				maxIncrCount = curIncrCount;
		}
		for (int cur = curBegin; cur < N; ++cur)
		{
			if (x[cur] > curMaxVal)
			{
				path.push_back(x[cur]);
				this->findAll_FixRecur(x, cur + 1, x[cur], curIncrCount + 1, path, incrSeqs, maxIncrCount);
				path.pop_back();
			}
			else
			{
				this->findAll_FixRecur(x, cur + 1, curMaxVal, curIncrCount, path, incrSeqs, maxIncrCount);
			}
		}
	}
};

/*
sorted: 3, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 7, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 8, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 2, 6, 8, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, 2, 6, 8, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, 2, 4, 8, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, 4, 8, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, 4, 5, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, -3, 5, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, -3, 5, 6, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, -3, -2, 6, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, -3, -2, 6, 7, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: -5, -4, -3, -2, -1, 7, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
LIS Len_Greedy_LowerBound for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
sorted: 1, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 7, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 7, 2147483647, 2147483647, 2147483647, 2147483647
sorted: 1, 5, 6, 7, 8, 2147483647, 2147483647, 2147483647
LIS Len_Greedy_LowerBound for "1, 1, 5, 5, 6, 7, 7, 8": 5
sorted: 3
sorted: 1
sorted: 1, 5
sorted: 1, 5, 7
sorted: 1, 5, 6
sorted: 1, 5, 6, 8
sorted: 1, 2, 6, 8
sorted: -5, 2, 6, 8
sorted: -5, 2, 4, 8
sorted: -5, -4, 4, 8
sorted: -5, -4, 4, 5
sorted: -5, -4, -3, 5
sorted: -5, -4, -3, 5, 6
sorted: -5, -4, -3, -2, 6
sorted: -5, -4, -3, -2, 6, 7
sorted: -5, -4, -3, -2, -1, 7
LIS Len_Greedy_LowerBound2 for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
sorted: 1
sorted: 1
sorted: 1, 5
sorted: 1, 5
sorted: 1, 5, 6
sorted: 1, 5, 6, 7
sorted: 1, 5, 6, 7
sorted: 1, 5, 6, 7, 8
LIS Len_Greedy_LowerBound2 for "1, 1, 5, 5, 6, 7, 7, 8": 5
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 1, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 1, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 1, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 5, 1, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 5, 4, 1, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 5, 4, 6, 1
1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 5, 4, 6, 5
LIS Len_DP1D_Quadratic for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6 (1, 2, 4, 5, 6, 7)
1, 1, 1, 1, 1, 1, 1, 1
1, 1, 2, 1, 1, 1, 1, 1
1, 1, 2, 2, 1, 1, 1, 1
1, 1, 2, 2, 3, 1, 1, 1
1, 1, 2, 2, 3, 4, 1, 1
1, 1, 2, 2, 3, 4, 4, 1
1, 1, 2, 2, 3, 4, 4, 5
LIS Len_DP1D_Quadratic for "1, 1, 5, 5, 6, 7, 7, 8": 5 (1, 5, 6, 7, 8)
LIS FindAll_InExcludeRecur for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
[rY][cX]
Row#0	=  ,  ,  ,  ,  ,
Row#1	= -1,  ,  ,  ,  ,
Row#2	= 7,  ,  ,  ,  ,
Row#3	= -2,  ,  ,  ,  ,
Row#4	= -2, -1,  ,  ,  ,
Row#5	= -2, 7,  ,  ,  ,
Row#6	= 6,  ,  ,  ,  ,
Row#7	= 6, 7,  ,  ,  ,
Row#8	= -3,  ,  ,  ,  ,
Row#9	= -3, -1,  ,  ,  ,
Row#10	= -3, 7,  ,  ,  ,
Row#11	= -3, -2,  ,  ,  ,
Row#12	= -3, -2, -1,  ,  ,
Row#13	= -3, -2, 7,  ,  ,
Row#14	= -3, 6,  ,  ,  ,
Row#15	= -3, 6, 7,  ,  ,
Row#16	= 5,  ,  ,  ,  ,
Row#17	= 5, 7,  ,  ,  ,
Row#18	= 5, 6,  ,  ,  ,
Row#19	= 5, 6, 7,  ,  ,
Row#20	= -4,  ,  ,  ,  ,
Row#21	= -4, -1,  ,  ,  ,
Row#22	= -4, 7,  ,  ,  ,
Row#23	= -4, -2,  ,  ,  ,
Row#24	= -4, -2, -1,  ,  ,
Row#25	= -4, -2, 7,  ,  ,
Row#26	= -4, 6,  ,  ,  ,
Row#27	= -4, 6, 7,  ,  ,
Row#28	= -4, -3,  ,  ,  ,
Row#29	= -4, -3, -1,  ,  ,
Row#30	= -4, -3, 7,  ,  ,
Row#31	= -4, -3, -2,  ,  ,
Row#32	= -4, -3, -2, -1,  ,
Row#33	= -4, -3, -2, 7,  ,
Row#34	= -4, -3, 6,  ,  ,
Row#35	= -4, -3, 6, 7,  ,
Row#36	= -4, 5,  ,  ,  ,
Row#37	= -4, 5, 7,  ,  ,
Row#38	= -4, 5, 6,  ,  ,
Row#39	= -4, 5, 6, 7,  ,
Row#40	= 4,  ,  ,  ,  ,
Row#41	= 4, 7,  ,  ,  ,
Row#42	= 4, 6,  ,  ,  ,
Row#43	= 4, 6, 7,  ,  ,
Row#44	= 4, 5,  ,  ,  ,
Row#45	= 4, 5, 7,  ,  ,
Row#46	= 4, 5, 6,  ,  ,
Row#47	= 4, 5, 6, 7,  ,
Row#48	= -5,  ,  ,  ,  ,
Row#49	= -5, -1,  ,  ,  ,
Row#50	= -5, 7,  ,  ,  ,
Row#51	= -5, -2,  ,  ,  ,
Row#52	= -5, -2, -1,  ,  ,
Row#53	= -5, -2, 7,  ,  ,
Row#54	= -5, 6,  ,  ,  ,
Row#55	= -5, 6, 7,  ,  ,
Row#56	= -5, -3,  ,  ,  ,
Row#57	= -5, -3, -1,  ,  ,
Row#58	= -5, -3, 7,  ,  ,
Row#59	= -5, -3, -2,  ,  ,
Row#60	= -5, -3, -2, -1,  ,
Row#61	= -5, -3, -2, 7,  ,
Row#62	= -5, -3, 6,  ,  ,
Row#63	= -5, -3, 6, 7,  ,
Row#64	= -5, 5,  ,  ,  ,
Row#65	= -5, 5, 7,  ,  ,
Row#66	= -5, 5, 6,  ,  ,
Row#67	= -5, 5, 6, 7,  ,
Row#68	= -5, -4,  ,  ,  ,
Row#69	= -5, -4, -1,  ,  ,
Row#70	= -5, -4, 7,  ,  ,
Row#71	= -5, -4, -2,  ,  ,
Row#72	= -5, -4, -2, -1,  ,
Row#73	= -5, -4, -2, 7,  ,
Row#74	= -5, -4, 6,  ,  ,
Row#75	= -5, -4, 6, 7,  ,
Row#76	= -5, -4, -3,  ,  ,
Row#77	= -5, -4, -3, -1,  ,
Row#78	= -5, -4, -3, 7,  ,
Row#79	= -5, -4, -3, -2,  ,
Row#80	= -5, -4, -3, -2, -1,
Row#81	= -5, -4, -3, -2, 7,
Row#82	= -5, -4, -3, 6,  ,
Row#83	= -5, -4, -3, 6, 7,
Row#84	= -5, -4, 5,  ,  ,
Row#85	= -5, -4, 5, 7,  ,
Row#86	= -5, -4, 5, 6,  ,
Row#87	= -5, -4, 5, 6, 7,
Row#88	= -5, 4,  ,  ,  ,
Row#89	= -5, 4, 7,  ,  ,
Row#90	= -5, 4, 6,  ,  ,
Row#91	= -5, 4, 6, 7,  ,
Row#92	= -5, 4, 5,  ,  ,
Row#93	= -5, 4, 5, 7,  ,
Row#94	= -5, 4, 5, 6,  ,
Row#95	= -5, 4, 5, 6, 7,
Row#96	= 2,  ,  ,  ,  ,
Row#97	= 2, 7,  ,  ,  ,
Row#98	= 2, 6,  ,  ,  ,
Row#99	= 2, 6, 7,  ,  ,
Row#100	= 2, 5,  ,  ,  ,
Row#101	= 2, 5, 7,  ,  ,
Row#102	= 2, 5, 6,  ,  ,
Row#103	= 2, 5, 6, 7,  ,
Row#104	= 2, 4,  ,  ,  ,
Row#105	= 2, 4, 7,  ,  ,
Row#106	= 2, 4, 6,  ,  ,
Row#107	= 2, 4, 6, 7,  ,
Row#108	= 2, 4, 5,  ,  ,
Row#109	= 2, 4, 5, 7,  ,
Row#110	= 2, 4, 5, 6,  ,
Row#111	= 2, 4, 5, 6, 7,
Row#112	= 8,  ,  ,  ,  ,
Row#113	= 6,  ,  ,  ,  ,
Row#114	= 6, 7,  ,  ,  ,
Row#115	= 6, 8,  ,  ,  ,
Row#116	= 7,  ,  ,  ,  ,
Row#117	= 7, 8,  ,  ,  ,
Row#118	= 5,  ,  ,  ,  ,
Row#119	= 5, 7,  ,  ,  ,
Row#120	= 5, 6,  ,  ,  ,
Row#121	= 5, 6, 7,  ,  ,
Row#122	= 5, 8,  ,  ,  ,
Row#123	= 5, 6,  ,  ,  ,
Row#124	= 5, 6, 7,  ,  ,
Row#125	= 5, 6, 8,  ,  ,
Row#126	= 5, 7,  ,  ,  ,
Row#127	= 5, 7, 8,  ,  ,
Row#128	= 1,  ,  ,  ,  ,
Row#129	= 1, 7,  ,  ,  ,
Row#130	= 1, 6,  ,  ,  ,
Row#131	= 1, 6, 7,  ,  ,
Row#132	= 1, 5,  ,  ,  ,
Row#133	= 1, 5, 7,  ,  ,
Row#134	= 1, 5, 6,  ,  ,
Row#135	= 1, 5, 6, 7,  ,
Row#136	= 1, 4,  ,  ,  ,
Row#137	= 1, 4, 7,  ,  ,
Row#138	= 1, 4, 6,  ,  ,
Row#139	= 1, 4, 6, 7,  ,
Row#140	= 1, 4, 5,  ,  ,
Row#141	= 1, 4, 5, 7,  ,
Row#142	= 1, 4, 5, 6,  ,
Row#143	= 1, 4, 5, 6, 7,
Row#144	= 1, 2,  ,  ,  ,
Row#145	= 1, 2, 7,  ,  ,
Row#146	= 1, 2, 6,  ,  ,
Row#147	= 1, 2, 6, 7,  ,
Row#148	= 1, 2, 5,  ,  ,
Row#149	= 1, 2, 5, 7,  ,
Row#150	= 1, 2, 5, 6,  ,
Row#151	= 1, 2, 5, 6, 7,
Row#152	= 1, 2, 4,  ,  ,
Row#153	= 1, 2, 4, 7,  ,
Row#154	= 1, 2, 4, 6,  ,
Row#155	= 1, 2, 4, 6, 7,
Row#156	= 1, 2, 4, 5,  ,
Row#157	= 1, 2, 4, 5, 7,
Row#158	= 1, 2, 4, 5, 6,
Row#159	= 1, 2, 4, 5, 6, 7
Row#160	= 1, 8,  ,  ,  ,
Row#161	= 1, 6,  ,  ,  ,
Row#162	= 1, 6, 7,  ,  ,
Row#163	= 1, 6, 8,  ,  ,
Row#164	= 1, 7,  ,  ,  ,
Row#165	= 1, 7, 8,  ,  ,
Row#166	= 1, 5,  ,  ,  ,
Row#167	= 1, 5, 7,  ,  ,
Row#168	= 1, 5, 6,  ,  ,
Row#169	= 1, 5, 6, 7,  ,
Row#170	= 1, 5, 8,  ,  ,
Row#171	= 1, 5, 6,  ,  ,
Row#172	= 1, 5, 6, 7,  ,
Row#173	= 1, 5, 6, 8,  ,
Row#174	= 1, 5, 7,  ,  ,
Row#175	= 1, 5, 7, 8,  ,
Row#176	= 3,  ,  ,  ,  ,
Row#177	= 3, 7,  ,  ,  ,
Row#178	= 3, 6,  ,  ,  ,
Row#179	= 3, 6, 7,  ,  ,
Row#180	= 3, 5,  ,  ,  ,
Row#181	= 3, 5, 7,  ,  ,
Row#182	= 3, 5, 6,  ,  ,
Row#183	= 3, 5, 6, 7,  ,
Row#184	= 3, 4,  ,  ,  ,
Row#185	= 3, 4, 7,  ,  ,
Row#186	= 3, 4, 6,  ,  ,
Row#187	= 3, 4, 6, 7,  ,
Row#188	= 3, 4, 5,  ,  ,
Row#189	= 3, 4, 5, 7,  ,
Row#190	= 3, 4, 5, 6,  ,
Row#191	= 3, 4, 5, 6, 7,
Row#192	= 3, 8,  ,  ,  ,
Row#193	= 3, 6,  ,  ,  ,
Row#194	= 3, 6, 7,  ,  ,
Row#195	= 3, 6, 8,  ,  ,
Row#196	= 3, 7,  ,  ,  ,
Row#197	= 3, 7, 8,  ,  ,
Row#198	= 3, 5,  ,  ,  ,
Row#199	= 3, 5, 7,  ,  ,
Row#200	= 3, 5, 6,  ,  ,
Row#201	= 3, 5, 6, 7,  ,
Row#202	= 3, 5, 8,  ,  ,
Row#203	= 3, 5, 6,  ,  ,
Row#204	= 3, 5, 6, 7,  ,
Row#205	= 3, 5, 6, 8,  ,
Row#206	= 3, 5, 7,  ,  ,
Row#207	= 3, 5, 7, 8,  ,

LIS InExcludeRecur for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
LIS Len_ShrinkLen_Recur for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
-1, 1, 1, 2, 3, 3, 4, 2, 1, 3, 2, 4, 3, 5, 4, 6
LIS Len_ShrinkLen_DP_Recur for "3, 1, 5, 7, 6, 8, 2, -5, 4, -4, 5, -3, 6, -2, 7, -1": 6
LIS FindAllDistinct_FixRecur for "4, 6, 7, 7":
[rY][cX]
Row#0	= 4, 6,  ,
Row#1	= 4, 6, 7,
Row#2	= 4, 6, 7, 7
Row#3	= 4, 7,  ,
Row#4	= 4, 7, 7,
Row#5	= 6, 7,  ,
Row#6	= 6, 7, 7,
Row#7	= 7, 7,  ,

1, 1, 3, 6, 3
LIS Count_IS_DP1D_Quadratic for "3, 2, 4, 5, 4": 14
0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
LIS Count_IS_DP1D_Linear for "dcefe": 14
*/
#endif