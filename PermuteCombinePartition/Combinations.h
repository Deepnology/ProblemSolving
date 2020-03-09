#ifndef _COMBINATIONS_H
#define _COMBINATIONS_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate all subsets of size k
http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
Leetcode: Combinations
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
Complexity:
O(N!) time

1. Combinations NoRepeat FromNoDupArray: n! / (k! * (n-k)!)
NoRepeats_DP2D for n=9, k=9:
Initialization:
	1   2   3   4   5   6   7   8   9 (length)
1	1	0	0	0	0	0	0	0	0 (1)
2	2	1	0	0	0	0	0	0	0 (1, 2, 12)
3	3	0	1	0	0	0	0	0	0 (1, 2, 3, 123)
4	4	0	0	1	0	0	0	0	0 (1, 2, 3, 4, 1234)
5	5	0	0	0	1	0	0	0	0 (1, 2, 3, 4, 5, 12345)
6	6	0	0	0	0	1	0	0	0 (1, 2, 3, 4, 5, 6, 123456)
7	7	0	0	0	0	0	1	0	0 (1, 2, 3, 4, 5, 6, 7, 1234567)
8	8	0	0	0	0	0	0	1	0 (1, 2, 3, 4, 5, 6, 7, 8, 12345678)
9	9	0	0	0	0	0	0	0	1 (1, 2, 3, 4, 5, 6, 7, 8, 9, 123456789)
(num)

	1   2   3   4   5   6   7   8   9 (length)
1	1	0	0	0	0	0	0	0	0
2	2	1	0	0	0	0	0	0	0
3	3	3	1	0	0	0	0	0	0
4	4	6	4	1	0	0	0	0	0
5	5	10	10	5	1	0	0	0	0
6	6	15	20	15	6	1	0	0	0
7	7	21	35	35	21	7	1	0	0
8	8	28	56	70	56	28	8	1	0
9	9	36	84	126	126	84	36	9	1
(num)

2. Combinations AllowRepeat FromNoDupArray: (n+k-1)! / (k! * (n-1)!)
AllowRepeats_DP2D for n=9, k=5:
Initialization:
	1   2   3   4   5 (length)
1	1	1	1	1	1 (1, 11, 111, 1111, 11111)
2	2                 (1, 2)
3	3                 (1, 2, 3)
4	4                 (1, 2, 3, 4)
5	5                 (1, 2, 3, 4, 5)
6	6                 (1, 2, 3, 4, 5, 6)
7	7                 (1, 2, 3, 4, 5, 6, 7)
8	8                 (1, 2, 3, 4, 5, 6, 7, 8)
9	9                 (1, 2, 3, 4, 5, 6, 7, 8, 9)
(num)

	1   2   3   4   5 (length)
1	1	1	1	1	1
2	2	3	4	5	6
3	3	6	10	15	21
4	4	10	20	35	56
5	5	15	35	70	126
6	6	21	56	126	252
7	7	28	84	210	426
8	8	36	120	330	792
9	9	45	165	495	1287
(num)

NoRepeats_DP2D: O(n*k) time, O(n*k) space
AllowRepeats_DP2D: O(n*k) time, O(n*k) space

See also BalancedPartitionWMin2SumDiff.h, CombinationSum.h, MonotoneDecimalNums.h, StricklyMonotoneDecimalNums.h, BinomialCoefficient.h, PascalTriangle.h
*/

class Combinations
{
public:
	Combinations(){}
	~Combinations(){}

public:
	//1. Combinations NoRepeat FromNoDupArray: n! / (k! * (n-k)!)
	//1.1 FixRecur
	std::vector<std::vector<int> > FindAll_FixRecur_NoRepeats(int n, int k)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->FixRecur_NoRepeats(n, k, 1, path, res);

		std::cout << "Combinations FindAll_FixRecur_NoRepeats for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur_NoRepeats(int n, int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}

		//still remaining "count" numbers to pick from begin~n
		//at least "count" numbers need to be picked from begin~n to end~n
		//so we can skip begin from (end+1)~n because begin from (end+1)~n always doesn't have sufficient "count"
		int end = n - count + 1;
		for (int cur = begin; cur <= end; ++cur)//"cur <= n" also works
		{
			path.push_back(cur);
			this->FixRecur_NoRepeats(n, count - 1, cur + 1, path, res);//cur+1 for NoRepeats
			path.pop_back();
		}
	}

public:
	//1.2 InExcludeRecur
	std::vector<std::vector<int> > FindAll_InExcludeRecur_NoRepeats(int n, int k)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->InExcludeRecur_NoRepeats(n, k, 1, path, res);

		std::cout << "Combinations FindAll_InExcludeRecur_NoRepeats for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur_NoRepeats(int n, int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}
		if (begin > n)
			return;
		
		//1. include current element
		path.push_back(begin);
		this->InExcludeRecur_NoRepeats(n, count - 1, begin + 1, path, res);//begin+1 for NoRepeats
		path.pop_back();
		//2. exclude current element
		this->InExcludeRecur_NoRepeats(n, count, begin + 1, path, res);
	}

public:
	//2. Combinations AllowRepeat FromNoDupArray: (n+k-1)! / (k! * (n-1)!)
	//2.1 FixRecur
	std::vector<std::vector<int> > FindAll_FixRecur_AllowRepeats(int n, int k)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->FixRecur_AllowRepeats(n, k, 1, path, res);

		std::cout << "Combinations FindAll_FixRecur_AllowRepeats for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur_AllowRepeats(int n, int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}

		for (int cur = begin; cur <= n; ++cur)
		{
			path.push_back(cur);
			this->FixRecur_AllowRepeats(n, count - 1, cur, path, res);//cur for AllowRepeats
			path.pop_back();
		}
	}
public:
	//2.2 InExcludeRecur
	std::vector<std::vector<int> > FindAll_InExcludeRecur_AllowRepeats(int n, int k)
	{
		std::vector<int> path;
		std::vector<std::vector<int> > res;
		this->InExcludeRecur_AllowRepeats(n, k, 1, path, res);

		std::cout << "Combinations FindAll_InExcludeRecur_AllowRepeats for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur_AllowRepeats(int n, int count, int begin, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			res.push_back(path);
			return;
		}
		if (begin > n)
			return;
		
		//1. include current element
		path.push_back(begin);
		this->InExcludeRecur_AllowRepeats(n, count - 1, begin, path, res);//begin for AllowRepeats
		path.pop_back();
		//2. exclude current element
		this->InExcludeRecur_AllowRepeats(n, count, begin + 1, path, res);
	}


public:
	//1.3 Iterate
	std::vector<std::vector<int> > FindAll_Iterate_NoRepeats(int n, int k)
	{
		std::vector<std::vector<int> > res;

		for (int count = k; count > 0; --count)
		{
			if (count == k)
			{
				//init res
				for (int cur = 1; cur <= n - count + 1; ++cur)
				{
					res.push_back(std::vector<int>(1, cur));
				}
				//now res contains only one row: 1...n-k+1
				Debug::Print2D<int>()(res);
				continue;
			}

			//each column in res should be a combination
			//now count starting from k-1 to 1

			//for each existing in-complete combination, eg. each column
			//for each next possible number of that existing combination
			//copy that existing combination and append the next possible number if that next possible number isn't the last one
			//or just append the next possible number if that next possible number is the last one
			int M = res.size();
			for (int index = 0; index < M; ++index)
			{
				int begin = res[index].back() + 1;//the next big number
				int end = n - count + 1;//index1 = index2 - count + 1 = (n) - (count) + 1
				//the last number index is (the biggest number) - (count) + 1

				for (int cur = begin; cur <= end; ++cur)
				{
					if (cur == end)//=> add cur to an existing combination
					{
						res[index].push_back(cur);
					}
					else//cur != end => new combination
					{
						auto copy = res[index];
						copy.push_back(cur);
						res.push_back(copy);
					}
				}
			}

			Debug::Print2D<int>()(res);
		}

		std::cout << "Combinations FindAll_Iterate_NoRepeats for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//1.4 Count Formula: n! / (k! * (n-k)!)
	int Count_NoRepeats_Formula(int n, int k)
	{
		unsigned long long res = this->factorial(n) / (this->factorial(k) * this->factorial(n - k));
		std::cout << "Combinations Count_NoRepeats_Formula for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << res << std::endl;
		return (int)res;
	}
	//2.4 Count Formula: (n+k-1)! / (k! * (n-1)!)
	int Count_AllowRepeats_Formula(int n, int k)
	{
		unsigned long long res = this->factorial(n + k - 1) / (this->factorial(k) * this->factorial(n - 1));
		std::cout << "Combinations Count_AllowRepeats_Formula for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << res << std::endl;
		return (int)res;
	}
private:
	unsigned long long factorial(unsigned long long n)
	{
		if (n == 0)
			return 1;
		return n * this->factorial(n - 1);
	}

public:
	//1.5 Count DP2D: see also StricklyMonotoneDecimalNums.h
	int Count_NoRepeats_DP2D(int n, int k)
	{
		int cols = std::min(n, k);
		std::vector<std::vector<int> > dp(n, std::vector<int>(cols, 0));
		
		//initialization
		for (int rowY = 0; rowY < n; ++rowY)
		{
			for (int colX = 0; colX < cols; ++colX)
			{
				if (rowY == colX)
					dp[rowY][colX] = 1;
				else if (colX == 0)
					dp[rowY][colX] = rowY + 1;
			}
		}

		for (int rowY = 0; rowY < n; ++rowY)
		{
			for (int colX = 1; colX < std::min(rowY, cols); ++colX)//all cols after first before min(diagonal, cols)
			{
				dp[rowY][colX] = dp[rowY - 1][colX - 1] + dp[rowY - 1][colX];//sum of "upper left" and "upper"
			}
		}

		int res = k > n ? 0 : dp[n - 1][cols - 1];

		Debug::Print2D<int>()(dp, false);
		std::cout << "Combinations Count_NoRepeats_DP2D for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << res << std::endl;
		return res;
	}
	
	//2.5 Count DP2D: see also MonotoneDecimalNums.h
	int Count_AllowRepeats_DP2D(int n, int k)
	{
		std::vector<std::vector<int> > dp(n, std::vector<int>(k, 0));
		for (int rowY = 0; rowY < n; ++rowY)
		{
			for (int colX = 0; colX < k; ++colX)
			{
				if (rowY == 0)
					dp[rowY][colX] = 1;
				else if (colX == 0)
					dp[rowY][colX] = rowY + 1;
				else
					dp[rowY][colX] = dp[rowY - 1][colX] + dp[rowY][colX - 1];//sum of "upper" and "left"
			}
		}

		Debug::Print2D<int>()(dp, false);
		std::cout << "Combinations Count_AllowRepeats_DP2D for \"" << k << "\" numbers out of \"1..." << n << "\" are: " << dp[n - 1][k - 1] << std::endl;
		return dp[n - 1][k - 1];
	}
};

/*
Permutation FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of permutations.
n!

Permutation FromDupArray:
Given a collection of n numbers that might contain duplicates, count the number of permutations.
                                      n!
-----------------------------------------------------------------------------------
(dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!



Combination NoRepeat FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of combinations of k-distinct numbers out of n.
    n!
------------
k! * (n-k)!

Combination AllowRepeat FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of combinations of k-may-repeat numbers out of n.
  (n+k-1)!
------------
k! * (n-1)!



Combination-NoRepeat-FromNoDupArray Plus Permutation-FromNoDupArray:
Given a collection of n numbers that don't contain duplicates (1...n), count the number of DISTINCT ORDER combinations of k-distinct numbers out of n.
    n!                 k!               n!
------------ * ------------------  =  ------
k! * (n-k)!    1! * 1! * ... * 1!     (n-k)!

Combination-AllowRepeat-FromNoDupArray Plus Permutation-FromDupArray:
Given a collection of n numbers that don't contain duplicates, count the number of DISTINCT ORDER combinations of k-may-repeat numbers out of n.
n^k



For example:
Permutation FromNoDupArray: 1,2,3,4
1234,1243,1324,1342,1423,1432,2134,2143,2314,2341,2413,2431,3124,3142,3214,3241,3412,3421,4123,4132,4213,4231,4312,4321
n! = 4! = 24

Permutation FromDupArray: 1,1,2,2
1122,1212,1221,2112,2121,2211
                                      n!                                                  4!
----------------------------------------------------------------------------------- = --------- = 6
(dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!     2! * 2!



Combination NoRepeat FromNoDupArray: pick 3 out of 1,2,3,4
123,124,134,234
    n!             4!
------------ = ----------- = 4
k! * (n-k)!     3!*(4-3)!

Combination AllowRepeat FromNoDupArray: pick 3 out of 1,2,3,4
111,112,113,114,122,123,124,133,134,144,222,223,224,233,234,244,333,334,344,444
  (n+k-1)!      (4+3-1)!
------------ = ----------- = 20
k! * (n-1)!     3!*(4-1)!



Combination-NoRepeat-FromNoDupArray Plus Permutation-FromNoDupArray: pick 3 out of 1,2,3,4
123,124,134,234
132,142,143,243
213,214,314,324
231,241,341,342
312,412,413,423
321,421,431,432
  n!       4!
------ = ------- = 24
(n-k)!   (4-3)!

Combination-AllowRepeat-FromNoDupArray Plus Permutation-FromDupArray:  pick 3 out of 1,2,3,4
111,112,113,114,122,123,124,133,134,144,222,223,224,233,234,244,333,334,344,444
    121,131,141,212,132,142,313,143,414,    232,242,323,243,424,    343,434,
	211,311,411,221,213,214,331,314,441,    322,422,332,324,442,    433,443,
	                231,241,    341,                    342,
					312,412,    413,                    423,
					321,421,    431,                    432,
n^k = 4^3 = 64
*/

/*
Combinations FindAll_FixRecur_NoRepeats for "2" numbers out of "1...4" are: [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
Combinations FindAll_InExcludeRecur_NoRepeats for "2" numbers out of "1...4" are: [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
Combinations FindAll_FixRecur_NoRepeats for "3" numbers out of "1...4" are: [1,2,3], [1,2,4], [1,3,4], [2,3,4]
Combinations FindAll_InExcludeRecur_NoRepeats for "3" numbers out of "1...4" are: [1,2,3], [1,2,4], [1,3,4], [2,3,4]
[cX][rY]
Row#0	= 1, 2, 3, 4, 5

[cX][rY]
Row#0	= 1, 2, 3, 4, 5, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4
Row#1	= 6, 6, 6, 6, 6, 2, 3, 4, 5, 3, 4, 5, 4, 5, 5

[cX][rY]
Row#0	= 1, 2, 3, 4, 5, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 4
Row#1	= 6, 6, 6, 6, 6, 2, 3, 4, 5, 3, 4, 5, 4, 5, 5, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 3, 3, 3, 4, 4, 5, 4, 4, 5, 5
Row#2	= 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 4, 5, 6, 4, 5, 6, 5, 6, 6, 4, 5, 6, 5, 6, 6, 5, 6, 6, 6

Combinations FindAll_Iterate_NoRepeats for "3" numbers out of "1...7" are: [1,6,7], [2,6,7], [3,6,7], [4,6,7], [5,6,7], [1,2,7], [1,3,7], [1,4,7], [1,5,7], [2,3,7], [2,4,7], [2,5,7], [3,4,7], [3,5,7], [4,5,7], [1,2,3], [1,2,4], [1,2,5], [1,2,6], [1,3,4], [1,3,5], [1,3,6], [1,4,5], [1,4,6], [1,5,6], [2,3,4], [2,3,5], [2,3,6], [2,4,5], [2,4,6], [2,5,6], [3,4,5], [3,4,6], [3,5,6], [4,5,6]
Combinations FindAll_FixRecur_NoRepeats for "0" numbers out of "1...4" are: []
Combinations FindAll_FixRecur_NoRepeats for "1" numbers out of "1...4" are: [1], [2], [3], [4]
Combinations FindAll_FixRecur_NoRepeats for "2" numbers out of "1...4" are: [1,2], [1,3], [1,4], [2,3], [2,4], [3,4]
Combinations FindAll_FixRecur_NoRepeats for "3" numbers out of "1...4" are: [1,2,3], [1,2,4], [1,3,4], [2,3,4]
Combinations FindAll_FixRecur_NoRepeats for "4" numbers out of "1...4" are: [1,2,3,4]
Combinations Count_NoRepeats_Formula for "3" numbers out of "1...7" are: 35
Combinations Count_NoRepeats_Formula for "5" numbers out of "1...9" are: 126
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= 2, 1, 0
Row#2	= 3, 3, 1
Row#3	= 4, 6, 4
Row#4	= 5, 10, 10
Row#5	= 6, 15, 20
Row#6	= 7, 21, 35

Combinations Count_NoRepeats_DP2D for "3" numbers out of "1...7" are: 35
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0, 0
Row#1	= 2, 1, 0, 0, 0, 0, 0
Row#2	= 3, 3, 1, 0, 0, 0, 0
Row#3	= 4, 6, 4, 1, 0, 0, 0
Row#4	= 5, 10, 10, 5, 1, 0, 0
Row#5	= 6, 15, 20, 15, 6, 1, 0
Row#6	= 7, 21, 35, 35, 21, 7, 1

Combinations Count_NoRepeats_DP2D for "7" numbers out of "1...7" are: 1
[rY][cX]
Row#0	= 1, 0, 0, 0, 0, 0, 0, 0, 0
Row#1	= 2, 1, 0, 0, 0, 0, 0, 0, 0
Row#2	= 3, 3, 1, 0, 0, 0, 0, 0, 0
Row#3	= 4, 6, 4, 1, 0, 0, 0, 0, 0
Row#4	= 5, 10, 10, 5, 1, 0, 0, 0, 0
Row#5	= 6, 15, 20, 15, 6, 1, 0, 0, 0
Row#6	= 7, 21, 35, 35, 21, 7, 1, 0, 0
Row#7	= 8, 28, 56, 70, 56, 28, 8, 1, 0
Row#8	= 9, 36, 84, 126, 126, 84, 36, 9, 1

Combinations Count_NoRepeats_DP2D for "9" numbers out of "1...9" are: 1
Combinations FindAll_FixRecur_AllowRepeats for "3" numbers out of "1...4" are: [1,1,1], [1,1,2], [1,1,3], [1,1,4], [1,2,2], [1,2,3], [1,2,4], [1,3,3], [1,3,4], [1,4,4], [2,2,2], [2,2,3], [2,2,4], [2,3,3], [2,3,4], [2,4,4], [3,3,3], [3,3,4], [3,4,4], [4,4,4]
Combinations FindAll_InExcludeRecur_AllowRepeats for "3" numbers out of "1...4" are: [1,1,1], [1,1,2], [1,1,3], [1,1,4], [1,2,2], [1,2,3], [1,2,4], [1,3,3], [1,3,4], [1,4,4], [2,2,2], [2,2,3], [2,2,4], [2,3,3], [2,3,4], [2,4,4], [3,3,3], [3,3,4], [3,4,4], [4,4,4]
Combinations Count_AllowRepeats_Formula for "3" numbers out of "1...7" are: 84
Combinations Count_AllowRepeats_Formula for "7" numbers out of "1...7" are: 1716
Combinations Count_AllowRepeats_Formula for "5" numbers out of "1...9" are: 1287
Combinations Count_AllowRepeats_Formula for "9" numbers out of "1...9" are: 24310
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1
Row#1	= 2, 3, 4, 5, 6, 7, 8
Row#2	= 3, 6, 10, 15, 21, 28, 36
Row#3	= 4, 10, 20, 35, 56, 84, 120
Row#4	= 5, 15, 35, 70, 126, 210, 330
Row#5	= 6, 21, 56, 126, 252, 462, 792
Row#6	= 7, 28, 84, 210, 462, 924, 1716

Combinations Count_AllowRepeats_DP2D for "7" numbers out of "1...7" are: 1716
[rY][cX]
Row#0	= 1, 1, 1, 1, 1, 1, 1, 1, 1
Row#1	= 2, 3, 4, 5, 6, 7, 8, 9, 10
Row#2	= 3, 6, 10, 15, 21, 28, 36, 45, 55
Row#3	= 4, 10, 20, 35, 56, 84, 120, 165, 220
Row#4	= 5, 15, 35, 70, 126, 210, 330, 495, 715
Row#5	= 6, 21, 56, 126, 252, 462, 792, 1287, 2002
Row#6	= 7, 28, 84, 210, 462, 924, 1716, 3003, 5005
Row#7	= 8, 36, 120, 330, 792, 1716, 3432, 6435, 11440
Row#8	= 9, 45, 165, 495, 1287, 3003, 6435, 12870, 24310

Combinations Count_AllowRepeats_DP2D for "9" numbers out of "1...9" are: 24310
*/
#endif