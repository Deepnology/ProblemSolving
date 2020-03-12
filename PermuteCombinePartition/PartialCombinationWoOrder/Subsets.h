#ifndef SUBSETS_H
#define SUBSETS_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate the power set
The power set of a set S is the set of all subsets of S, including both the empty set 0 and S itself.
Implement a method that takes as input a set S of n distinct elements, and prints the power set of S.
Leetcode: Subsets
// Given a set of distinct integers, S, return all possible subsets.
//
// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// For example,
// If S = [1,2,3], a solution is:
//
// [
//  [3],
//  [1],
//  [2],
//  [1,2,3],
//  [1,3],
//  [2,3],
//  [1,2],
//  []
// ]
//
// Complexity:
// O(2^n)

Leetcode: Subsets II
// Given a collection of integers that might contain duplicates, S, return all
// possible subsets.
//
// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// For example,
// If S = [1,2,2], a solution is:
//
// [
//  [2],
//  [1],
//  [1,2,2],
//  [2,2],
//  [1,2],
//  []
// ]
//
// Complexity:
// O(2^n)
*/
class Subsets
{
public:
	Subsets(){}
	~Subsets(){}

	//1. FromNoDupArray
	//1.1 FixRecur
	std::vector<std::vector<int>> FindAll_FromNoDupArray_FixReucr(std::vector<int> && S)//S has no duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<int> path;
		std::vector<std::vector<int>> res;
		this->FixRecur(S, 0, path, res);

		std::cout << "Subsets FindAll_FromNoDupArray_FixRecur" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur(const std::vector<int> & S, int begin, std::vector<int> & path
		, std::vector<std::vector<int>> & res)
	{
		res.push_back(path);
		int end = S.size();
		for (int cur = begin; cur < end; ++cur)
		{
			path.push_back(S[cur]);
			this->FixRecur(S, cur + 1, path, res);
			path.pop_back();
		}
	}
public:
	//1.2 InExcludeRecur
	std::vector<std::vector<int>> FindAll_FromNoDupArray_InExcludeReucr(std::vector<int> && S)//S has no duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<int> path;
		std::vector<std::vector<int>> res;
		this->InExcludeRecur(S, 0, path, res);

		std::cout << "Subsets FindAll_FromNoDupArray_InExcludeRecur" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur(const std::vector<int> & S, int begin, std::vector<int> & path
		, std::vector<std::vector<int>> & res)
	{
		int end = S.size();
		if (begin == end)
		{
			res.push_back(path);
			return;
		}
		//1. include current element
		path.push_back(S[begin]);
		this->InExcludeRecur(S, begin + 1, path, res);
		path.pop_back();
		//2. exclude current element
		this->InExcludeRecur(S, begin + 1, path, res);
	}

public:
	//1.3 Iterate
	std::vector<std::vector<int>> FindAll_FromNoDupArray_Iterate(std::vector<int> && S)//S has no duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<std::vector<int>> res(1, std::vector<int>());//the first subset is an empty subset
		int N = S.size();

		for (int i = 0; i < N; ++i)
		{
			int M = res.size();//M: the looping size should be the count of existing subsets before adding new subsets
			for (int j = 0; j < M; ++j)//add S[i] to each existing subset to create new subsets
			{
				auto copy = res[j];
				copy.push_back(S[i]);
				res.push_back(copy);
			}
			Debug::Print2D<int>()(res);
		}

		std::cout << "Subsets FindAll_FromNoDupArray_Iterate" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	/*
	1.4 Iterate_BitArray
	If N is less than or equal to the width of an integer on the architecture (or language) we are working on
	, we can enumerate bit arrays by enumerating integers in [0, 2^N-1] and examing the indicies of bits set in these integers.
	These indices are determined by first isolating the lowest set bit by computing y = x&~(x-1) and then getting the index by computing log2(y).
	O(n*2^n) time, where each set takes O(n) time
	*/
	std::vector<std::vector<int>> FindAll_FromNoDupArray_Iterate_BitArray(const std::vector<int> & S)
	{
		int N = S.size();
		std::vector<std::vector<int>> res;
		for (int i = 0; i < (1 << N); ++i)//from 0 to 2^N-1
		{
			/*collect all corresponding index of i's set bit in S as a subset*/
			std::vector<int> subSet;
			int tmp = i;
			while (tmp)
			{
				int idx = (int)log2(tmp & ~(tmp - 1));//tmp & ~(tmp-1) is isolating the lowest set bit
				subSet.push_back(S[idx]);
				tmp &= (tmp - 1);//flip the lowest set bit to 0
			}
			res.push_back(subSet);
		}

		std::cout << "Subsets FindAll_FromNoDupArray_Iterate_BitArray" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	//2. FromDupArray
	//2.1 FixRecur
	std::vector<std::vector<int>> FindAllUnique_FromDupArray_FixRecur(std::vector<int> && S)//S might have duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<int> path;
		std::vector<std::vector<int>> res;
		this->FixRecurUnique(S, 0, path, res);

		std::cout << "Subsets FindAllUnique_FromDupArray_FixRecur" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecurUnique(const std::vector<int> & S, int begin, std::vector<int> & path, std::vector<std::vector<int>> & res)
	{
		res.push_back(path);
		int end = S.size();
		for (int cur = begin; cur < end; ++cur)
		{
			if (cur > begin && S[cur - 1] == S[cur])
				continue;//skip duplicates

			path.push_back(S[cur]);
			this->FixRecurUnique(S, cur + 1, path, res);
			path.pop_back();
		}
	}
public:
	//2.2 InExcludeRecur
	std::vector<std::vector<int>> FindAllUnique_FromDupArray_InExcludeRecur(std::vector<int> && S)//S might have duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<int> path;
		std::vector<std::vector<int>> res;
		this->InExcludeRecurUnique(S, 0, path, res);

		std::cout << "Subsets FindAllUnique_FromDupArray_InExcludeRecur" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecurUnique(const std::vector<int> & S, int begin, std::vector<int> & path, std::vector<std::vector<int>> & res)//better
	{
		int end = S.size();
		if (begin == end)
		{
			res.push_back(path);
			return;
		}
		//1. include current element
		path.push_back(S[begin]);
		this->InExcludeRecurUnique(S, begin + 1, path, res);
		path.pop_back();
		//2. exclude current element and all duplicates
		int stride = 1;
		while (begin + stride < end && S[begin] == S[begin + stride])
			++stride;
		this->InExcludeRecurUnique(S, begin + stride, path, res);
	}
	void InExcludeRecurUnique2(const std::vector<int> & S, int begin, std::vector<int> & path, std::vector<std::vector<int>> & res)
	{
		int end = S.size();
		if (begin == end)
		{
			res.push_back(path);
			return;
		}
		if (path.size() > 0 && path.back() == S[begin])//if S[begin] is a duplicate of prev: MUST SKIP EXCLUDE CUR NUM !!
		{
			//1. include current element
			path.push_back(S[begin]);
			this->InExcludeRecurUnique2(S, begin + 1, path, res);
			path.pop_back();
		}
		else
		{
			//1. include current element
			path.push_back(S[begin]);
			this->InExcludeRecurUnique2(S, begin + 1, path, res);
			path.pop_back();
			//2. exclude current element
			this->InExcludeRecurUnique2(S, begin + 1, path, res);
		}
	}


public:
	//2.3 Iterate
	std::vector<std::vector<int>> FindAllUnique_FromDupArray_Iterate(std::vector<int> && S)//S might have duplicates
	{
		std::sort(std::begin(S), std::end(S));
		std::vector<std::vector<int>> res(1, std::vector<int>());//the first subset is an empty subset
		int duplicateCount = 0;

		for (int i = 0; i < (int)S.size(); ++i)
		{
			if (i > 0 && S[i - 1] == S[i])
				++duplicateCount;//increment if S[i] is a duplicate of S[i-1]
			else
				duplicateCount = 0;//reset to 0

			int M = res.size();//M: the looping size should be the count of existing subsets before adding new subsets
			for (int j = 0; j < M; ++j)//add S[i] to each existing subset to create new subsets
			{
				int N = res[j].size();

				//2 cases to add S[i] to each existing subset to create new subsets:
				//1. S[i] is a non-duplicate of S[i-1] => duplicateCount == 0
				//2. S[i] is a duplicate of S[i-1], and the last number in res[j] is also S[i] => res[j][(N-1)-duplicateCount+1] == S[i]

				if (duplicateCount == 0 || (N >= duplicateCount && res[j][N - duplicateCount] == S[i]))
				{
					auto copy = res[j];
					copy.push_back(S[i]);
					res.push_back(copy);
				}
			}

			Debug::Print2D<int>()(res);
		}

		std::cout << "Subsets FindAllUnique_FromDupArray_Iterate" << " for \"" << Debug::ToStr1D<int>()(S) << "\" are: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
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
Subsets FindAll_FromNoDupArray_FixRecur for "3, 5, 7, 8" are: [], [3], [3,5], [3,5,7], [3,5,7,8], [3,5,8], [3,7], [3,7,8], [3,8], [5], [5,7], [5,7,8], [5,8], [7], [7,8], [8]
Subsets FindAll_FromNoDupArray_InExcludeRecur for "3, 5, 7, 8" are: [3,5,7,8], [3,5,7], [3,5,8], [3,5], [3,7,8], [3,7], [3,8], [3], [5,7,8], [5,7], [5,8], [5], [7,8], [7], [8], []
[cX][rY]
Row#0	=  , 3

[cX][rY]
Row#0	=  , 3, 5, 3
Row#1	=  ,  ,  , 5

[cX][rY]
Row#0	=  , 3, 5, 3, 7, 3, 5, 3
Row#1	=  ,  ,  , 5,  , 7, 7, 5
Row#2	=  ,  ,  ,  ,  ,  ,  , 7

[cX][rY]
Row#0	=  , 3, 5, 3, 7, 3, 5, 3, 8, 3, 5, 3, 7, 3, 5, 3
Row#1	=  ,  ,  , 5,  , 7, 7, 5,  , 8, 8, 5, 8, 7, 7, 5
Row#2	=  ,  ,  ,  ,  ,  ,  , 7,  ,  ,  , 8,  , 8, 8, 7
Row#3	=  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 8

Subsets FindAll_FromNoDupArray_Iterate for "3, 5, 7, 8" are: [], [3], [5], [3,5], [7], [3,7], [5,7], [3,5,7], [8], [3,8], [5,8], [3,5,8], [7,8], [3,7,8], [5,7,8], [3,5,7,8]
Subsets FindAll_FromNoDupArray_Iterate_BitArray for "8, 3, 7, 5" are: [], [8], [3], [8,3], [7], [8,7], [3,7], [8,3,7], [5], [8,5], [3,5], [8,3,5], [7,5], [8,7,5], [3,7,5], [8,3,7,5]
Subsets FindAllUnique_FromDupArray_FixRecur for "3, 3, 5, 8" are: [], [3], [3,3], [3,3,5], [3,3,5,8], [3,3,8], [3,5], [3,5,8], [3,8], [5], [5,8], [8]
Subsets FindAllUnique_FromDupArray_InExcludeRecur for "3, 3, 5, 8" are: [3,3,5,8], [3,3,5], [3,3,8], [3,3], [3,5,8], [3,5], [3,8], [3], [5,8], [5], [8], []
[cX][rY]
Row#0	=  , 3

[cX][rY]
Row#0	=  , 3, 3
Row#1	=  ,  , 3

[cX][rY]
Row#0	=  , 3, 3, 5, 3, 3
Row#1	=  ,  , 3,  , 5, 3
Row#2	=  ,  ,  ,  ,  , 5

[cX][rY]
Row#0	=  , 3, 3, 5, 3, 3, 8, 3, 3, 5, 3, 3
Row#1	=  ,  , 3,  , 5, 3,  , 8, 3, 8, 5, 3
Row#2	=  ,  ,  ,  ,  , 5,  ,  , 8,  , 8, 5
Row#3	=  ,  ,  ,  ,  ,  ,  ,  ,  ,  ,  , 8

Subsets FindAllUnique_FromDupArray_Iterate for "3, 3, 5, 8" are: [], [3], [3,3], [5], [3,5], [3,3,5], [8], [3,8], [3,3,8], [5,8], [3,5,8], [3,3,5,8]
*/
#endif