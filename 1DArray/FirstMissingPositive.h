#ifndef FIRST_MISSING_POSITIVE_H
#define FIRST_MISSING_POSITIVE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Array: Find the first missing positive entry
Leetcode: First Missing Positive
// Given an unsorted integer array, find the first missing positive integer.
//
// For example,
// Given [1,2,0] return 3,
// and [3,4,-1,1] return 2.
//
// Your algorithm should run in O(n) time and uses constant space.

What is the most desired array we want to see? 
Something like [1,2,3] then we know 4 is missing, or [1, 8, 3, 4] then we know 2 is missing. 
In other word, ¡§all the numbers are in their correct positions¡¨. 
What are correct positions? For any i, A[i] = i+1. 
So our goal is to rearrange those numbers (in place) to their correct positions. 
We then need to decide how to arrange them. 
Let¡¦s take the [3, 4, -1, 1] as an example. 
The 1st number, 3, we know it should stay in position 2. 
So we swap A[0] = 3 with A[2]. 
We then get [-1, 4, 3, 1]. 
We can¡¦t do anything about -1 so we leave it there. 
The 2nd number, 4, we know it should sit in A[3]. 
So we swap A[1] = 4 with A[3]. 
We then get [-1, 1, 3, 4]. 
Now 1 should stay in A[0], so we keep swapping and we get [1, -1, 3, 4]. 
Notice now every positive number is staying in their correct position (A[0]=1, A[2]=3 and A[3]=4). 
We then need one more scan to find out 2 is missing.

See also FrequencyOfIdxSeqArray.h, CountingSort2.h
*/
class FirstMissingPositive
{
public:
	FirstMissingPositive(){}
	~FirstMissingPositive(){}
	/*
	swap positive elements whose value is in [1, n] in A to make A[i] = i + 1
	then the first element whose value A[i] != i + 1 will be the first missing positive
	*/
	int Find(int A[], int n)
	{
		std::string before = Debug::ToStr1D<int>()(A, n);
		int i = 0;
		while (i < n)
		{
			if (
				0 < A[i] && A[i] <= n &&//make sure A[i]-1 is in the range
				A[i] != i + 1 &&//make sure A[i] isn't the corresponding number
				A[i] != A[A[i] - 1]//make sure the swap pair are different (to avoid infinite loop)
				)
				std::swap(A[i], A[A[i] - 1]);//move A[i] to its corresponding position
			else//leave it there
				++i;
		}
		i = 0;
		while (i < n && A[i] == i + 1)
			++i;
		++i;
		std::string after = Debug::ToStr1D<int>()(A, n);
		std::cout << "FirstMissingPositive for \"" << before << "\" is: " << i << " (" << after << ")" << std::endl;
		return i;
	}

};
/*
FirstMissingPositive for "17, 16, -2, 5, 1, 4, 2, -1, 18, 0" is: 3 (1, 2, -2, 4, 5, 17, 16, -1, 18, 0)
*/
#endif