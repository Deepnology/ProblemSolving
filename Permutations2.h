#ifndef PERMUTATIONS2_H
#define PERMUTATIONS2_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, Recursion: Enumerate permutations
Write a function which takes as input an array A of n distinct integers and prints all permutations of A.
No permutation appear more than once.
Your function should use O(n) space.
https://github.com/anson627/leetcode/blob/master/Permutations/Permutations.cpp
// Given a collection of numbers, return all possible permutations.
//
// For example,
// [1,2,3] have the following permutations:
// [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

https://github.com/anson627/leetcode/blob/master/PermutationsII/PermutationsII.cpp
// Permutations II
// Given a collection of numbers that might contain duplicates, return all
// possible unique permutations.
//
// For example,
// [1,1,2] have the following unique permutations:
// [1,1,2], [1,2,1], and [2,1,1].
*/
class Permutations2
{
public:
	Permutations2(){}
	~Permutations2(){}

	//1. Permutation FromNoDupArray: n!
	//1.1 Iterate
	std::vector<std::vector<int> > FindAll_FromNoDupArray_InPlace_Iterate(std::vector<int> & num)//num are all supposed to be unique
	{
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int> > res;
		do
		{
			res.push_back(num);
		} while (std::next_permutation(std::begin(num), std::end(num)));
		
		std::cout << "Permutations2 FindAll_FromNoDupArray_InPlace_Iterate for \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	//1.2 Back Track
	std::vector<std::vector<int> > FindAll_FromNoDupArray_InPlace_Recur(std::vector<int> & num)//num are all supposed to be unique
	{
		std::vector<std::vector<int> > res;
		this->PermuteRecur(num, 0, res);

		std::cout << "Permutations2 FindAll_FromNoDupArray_InPlace_Recur for \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void PermuteRecur(std::vector<int> & num, int begin, std::vector<std::vector<int> > & res)
	{
		int N = num.size();
		if (begin == N)//the next level of the depth
		{
			res.push_back(num);
			return;
		}
		for (int cur = begin; cur < N; ++cur)//num[0]~num[begin-1] are fixed, swap num[begin] with num[begin]~num[N-1]
		{
			std::swap(num[begin], num[cur]);//swap num[begin] and num[cur]
			this->PermuteRecur(num, begin + 1, res);//fix num[0]~num[begin], swap num[begin+1] with num[begin+1]~num[N-1]
			std::swap(num[begin], num[cur]);//swap back
		}
	}


public:
	//2. Permutation FromDupArray: n! / ((dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!)
	//2.1 Iterate
	std::vector<std::vector<int> > FindAllUnique_FromDupArray_InPlace_Iterate(std::vector<int> & num)//num might have duplicates
	{
		std::sort(std::begin(num), std::end(num));
		std::vector<std::vector<int> > res;
		do
		{
			res.push_back(num);
		} while (std::next_permutation(begin(num), std::end(num)));

		std::cout << "Permutations2 FindAllUnique_FromDupArray_Iterate for \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	//2.2 Back Track
	std::vector<std::vector<int> > FindAllUnique_FromDupArray_InPlace_Recur(std::vector<int> & num)//num might have duplicates
	{
		std::vector<std::vector<int> > res;
		this->PermuteUniqueRecur(num, 0, res);

		std::cout << "Permutations2 FindAllUnique_FromDupArray_InPlace_Recur for \"" << Debug::ToStr1D<int>()(num) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void PermuteUniqueRecur(std::vector<int> & num, int begin, std::vector<std::vector<int> > & res)
	{
		int N = num.size();
		if (begin == N)
		{
			res.push_back(num);
			return;
		}
		std::unordered_set<int> visited;
		for (int cur = begin; cur < N; ++cur)//num[0]~num[begin-1] are fixed, swap num[begin] with num[begin]~num[N-1]
		{
			if (visited.count(num[cur]))
				continue;//skip those visited numbers from num[begin]~num[cur-1]
			visited.insert(num[cur]);

			std::swap(num[begin], num[cur]);//swap num[begin] and num[cur]
			this->PermuteUniqueRecur(num, begin + 1, res);//fix num[0]~num[begin], swap num[begin+1] with num[begin+1]~num[N-1]
			std::swap(num[begin], num[cur]);//restore
		}
	}


public:
	//2.3 Formula: n! / ((dupCount_1)! * (dupCount_2)! * (dupCount_3)! * ... * (dupCount_DistinctNumCount)!)
	int Count_FromDupArray_Formula(std::vector<int> & num)
	{
		int N = num.size();

		std::vector<int> dupCount;
		std::sort(num.begin(), num.end(), std::less<int>());
		
		int curDups = 1;
		for (int i = 1; i < N; ++i)
		{
			if (num[i] == num[i - 1])
			{
				++curDups;
			}
			else
			{
				dupCount.push_back(curDups);
				curDups = 1;
			}
		}
		dupCount.push_back(curDups);

		int res = this->factorial(N);
		for (const int & dupNum : dupCount)
		{
			res /= this->factorial(dupNum);
		}

		std::cout << Debug::ToStr1D<int>()(dupCount) << std::endl;
		std::cout << "Permutations2 Count_From_DupArray_Formula for \"" << Debug::ToStr1D<int>()(num) << "\": " << res << std::endl;
		return res;
	}
private:
	int factorial(int n)
	{
		if (n == 0)
			return 1;
		return n * this->factorial(n - 1);
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
Permutations2 FindAll_FromNoDupArray_InPlace_Iterate for "1, 2, 3": [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]
Permutations2 FindAll_FromNoDupArray_InPlace_Recur for "2, 3, 1": [2,3,1], [2,1,3], [3,2,1], [3,1,2], [1,3,2], [1,2,3]
Permutations2 FindAllUnique_FromDupArray_Iterate for "1, 1, 2, 2": [1,1,2,2], [1,2,1,2], [1,2,2,1], [2,1,1,2], [2,1,2,1], [2,2,1,1]
Permutations2 FindAllUnique_FromDupArray_InPlace_Recur for "1, 2, 1, 2": [1,2,1,2], [1,2,2,1], [1,1,2,2], [2,1,1,2], [2,1,2,1], [2,2,1,1]
Permutations2 FindAllUnique_FromDupArray_InPlace_Recur for "2, 1, 3, 1, 2": [2,1,3,1,2], [2,1,3,2,1], [2,1,1,3,2], [2,1,1,2,3], [2,1,2,1,3], [2,1,2,3,1], [2,3,1,1,2], [2,3,1,2,1], [2,3,2,1,1], [2,2,3,1,1], [2,2,1,3,1], [2,2,1,1,3], [1,2,3,1,2], [1,2,3,2,1], [1,2,1,3,2], [1,2,1,2,3], [1,2,2,1,3], [1,2,2,3,1], [1,3,2,1,2], [1,3,2,2,1], [1,3,1,2,2], [1,1,3,2,2], [1,1,2,3,2], [1,1,2,2,3], [3,1,2,1,2], [3,1,2,2,1], [3,1,1,2,2], [3,2,1,1,2], [3,2,1,2,1], [3,2,2,1,1]
2, 2, 1
Permutations2 Count_From_DupArray_Formula for "1, 1, 2, 2, 3": 30
Permutations2 FindAllUnique_FromDupArray_InPlace_Recur for "1, 1, 1, 2, 2": [1,1,1,2,2], [1,1,2,1,2], [1,1,2,2,1], [1,2,1,1,2], [1,2,1,2,1], [1,2,2,1,1], [2,1,1,1,2], [2,1,1,2,1], [2,1,2,1,1], [2,2,1,1,1]
Permutations2 FindAll_FromNoDupArray_InPlace_Iterate for "1, 2, 3, 4": [1,2,3,4], [1,2,4,3], [1,3,2,4], [1,3,4,2], [1,4,2,3], [1,4,3,2], [2,1,3,4], [2,1,4,3], [2,3,1,4], [2,3,4,1], [2,4,1,3], [2,4,3,1], [3,1,2,4], [3,1,4,2], [3,2,1,4], [3,2,4,1], [3,4,1,2], [3,4,2,1], [4,1,2,3], [4,1,3,2], [4,2,1,3], [4,2,3,1], [4,3,1,2], [4,3,2,1]
Permutations2 FindAll_FromNoDupArray_InPlace_Recur for "1, 2, 3, 4": [1,2,3,4], [1,2,4,3], [1,3,2,4], [1,3,4,2], [1,4,3,2], [1,4,2,3], [2,1,3,4], [2,1,4,3], [2,3,1,4], [2,3,4,1], [2,4,3,1], [2,4,1,3], [3,2,1,4], [3,2,4,1], [3,1,2,4], [3,1,4,2], [3,4,1,2], [3,4,2,1], [4,2,3,1], [4,2,1,3], [4,3,2,1], [4,3,1,2], [4,1,3,2], [4,1,2,3]
*/
#endif