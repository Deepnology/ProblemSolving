#ifndef SMALLEST_PERMUTATION_FROM_INCR_DECR_ARRAY_H
#define SMALLEST_PERMUTATION_FROM_INCR_DECR_ARRAY_H
#include "Debug.h"
/*
Leetcode: Find Permutation
By now, you are given a secret signature consisting of character 'D' and 'I'.
'D' represents a decreasing relationship between two numbers, 'I' represents an increasing relationship between two numbers.
And our secret signature was constructed by a special integer array, which contains uniquely all the different number from 1 to n (n is the length of the secret signature plus 1).
For example, the secret signature "DI" can be constructed by array [2,1,3] or [3,1,2], but won't be constructed by array [3,2,4] or [2,1,3,4], which are both illegal constructing special string that can't represent the "DI" secret signature.
On the other hand, now your job is to find the lexicographically smallest permutation of [1, 2, ... n] could refer to the given secret signature in the input.
Example 1:
Input: "I"
Output: [1,2]
Explanation: [1,2] is the only legal initial spectial string can construct secret signature "I", where the number 1 and 2 construct an increasing relationship.
Example 2:
Input: "DI"
Output: [2,1,3]
Explanation: Both [2,1,3] and [3,1,2] can construct the secret signature "DI",
but since we want to find the one with the smallest lexicographical permutation, you need to output [2,1,3]

 I I I I I I I
1 2 3 4 5 6 7 8
 I D I D D D I
1 3 2 7 6 5 4 8
=> reverse consecutive Ds' nums

Leetcode: DI String Match (not necessarily the smallest permutation)
Given a string S that only contains "I" (increase) or "D" (decrease), let N = S.length.
Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:
If S[i] == "I", then A[i] < A[i+1]
If S[i] == "D", then A[i] > A[i+1]
Example 1:
Input: "IDID"
Output: [0,4,1,3,2]
Example 2:
Input: "III"
Output: [0,1,2,3]
Example 3:
Input: "DDI"
Output: [3,2,0,1]
*/
class SmallestPermutationFromIncrDecrArray
{
public:
	SmallestPermutationFromIncrDecrArray() {}

	std::vector<int> FindSmallestPermutation(std::string s)
	{
		int N = s.size();
		std::vector<int> res;//[1:N+1] permutation
		for (int i = 1; i <= N + 1; ++i)
			res.push_back(i);

		int i = 0;
		while (i < N)
		{
			if (s[i] == 'I')
			{
				++i;
				continue;
			}
			int j = i;
			while (s[j] == 'D')
				++j;
			--j;
			//now s[i:j] are all Ds: reverse res[i:j+1]

			int ii = i;
			int jj = j + 1;
			while (ii < jj)
				std::swap(res[ii++], res[jj--]);

			i = j + 1;
		}

		std::cout << "SmallestPermutationFromIncrDecrArray for \"" << s << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> FindAnyPermutation(std::string s)
	{
		int i = 0; int j = s.size();
		std::vector<int> res;
		for (auto & c : s)
			res.push_back(c == 'I' ? i++ : j--);
		res.push_back(i);

		std::cout << "SmallestPermutationFromIncrDecrArray FindAny for \"" << s << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
SmallestPermutationFromIncrDecrArray for "IDIDDDI": 1, 3, 2, 7, 6, 5, 4, 8
SmallestPermutationFromIncrDecrArray for "DDIIDDD": 3, 2, 1, 4, 8, 7, 6, 5
SmallestPermutationFromIncrDecrArray FindAny for "IDIDDDI": 0, 7, 1, 6, 5, 4, 2, 3
SmallestPermutationFromIncrDecrArray FindAny for "DDIIDDD": 7, 6, 0, 1, 5, 4, 3, 2
*/
#endif
