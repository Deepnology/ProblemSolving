#ifndef KTH_PERMUTATION_SEQUENCE_H
#define KTH_PERMUTATION_SEQUENCE_H
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Debug.h"
/*
Elements of programming interview, Array: Compute the next permutation
http://fisherlei.blogspot.tw/2013/04/leetcode-permutation-sequence-solution.html
http://suifengls.blogspot.tw/2013/09/permutation-sequenceleetcode.html
https://github.com/anson627/leetcode/blob/master/PermutationSequence/PermutationSequence.cpp
// Permutation Sequence
// The set [1,2,3,...,n] contains a total of n! unique permutations.
//
// By listing and labeling all of the permutations in order,
// We get the following sequence (ie, for n = 3):
//
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"
// Given n and k, return the kth permutation sequence.
//
// Note: Given n will be between 1 and 9 inclusive.
//
// Complexity:
// Next permutation based, O(k*n), k can be n!
// Math based, O(n^2)

Math based:
1234: total permuCount = 4! = 4*3*2*1 = 24

   0     1     2     3     4     5
1234, 1243, 1324, 1342, 1423, 1432,

   6     7     8     9    10    11
2134, 2143, 2314, 2341, 2413, 2431, 

  12    13    14    15    16    17
3124, 3142, 3214, 3241, 3412, 3421, 

  18    19    20    21    22    23
4123, 4132, 4213, 4231, 4312, 4321

Notice that the 1st digit is 1 for 0-5th, 2 for 6-11th, 3 for 12-17th, 4 for 18-23th permutation.
To determine the 1st digit of Kth permutation, need to find which section that K locates.
Each section size is equal to the total permutation count after taking out 1 element, 24/4 = 6.
If K is 0~5, K/6 = 0, which maps to the 0th element, 1. Take out the selected element: 234 left in ascending order.
If K is 6~11, K/6 = 1, which maps to the 1st element, 2. Take out the selected element: 134 left in ascending order.
If K is 12~17, K/6 = 2, which maps to the 2nd element, 3. Take out the selected element: 124 left in ascending order.
If K is 18~23, K/6 = 3, which maps to the 3rd element, 4. Take out the selected element: 123 left in ascending order.

(suppose K is 12~17)
To determine the 2nd digit, need to find which sub-section that K % 6 locates.
Each sub-section size is equal to the total permutation count after taking out 2 elements, 6/3 = 2.
If K%6 is 0~1, (K%6)/2 = 0, which maps to the 0th element of the previous 1-taken-out elements, 1. Take out the selected element: 24 left in ascending order.
If K%6 is 2~3, (K%6)/2 = 1, which maps to the 1st element of the previous 1-taken-out elements, 2. Take out the selected element: 14 left in ascending order.
If K%6 is 4~5, (K%6)/2 = 2, which maps to the 2nd element of the previous 1-taken-out elements, 4. Take out the selected element: 12 left in ascending order.

Repeat this process for 4 times.

The final result Kth permutation would be "first-taken-out-element, second-taken-out-element, third-taken-out-element, fourth-taken-out-element".

ex: n=1234, k=15

total:	24/4=6	6/3=2	2/2=1	1/1=1		(permuCount=permuCount/digitCount)
idx:	15/6=2	3/2=1	1/1=1	0/1=0		(idx=k/permuCount)
res:	3		32		324		3214		(res.push_back(nums[idx])
nums:	124		14		1					(nums.erase(nums.begin()+idx))
k:		15%6=3	3%2=1	1%1=0	0%1=0		(k=k%permuCount)
*/
class KthPermutationSequence
{
public:
	KthPermutationSequence(){}
	~KthPermutationSequence(){}

	std::string NextPermutationBased(int n, int k)
	{
		std::string res(n, '1');
		for (int i = 0; i < n; ++i)
		{
			res[i] += i;
		}
		//res is now 1...n

		std::string before(res);
		int K = k;
		for (; K > 1; --K)
		{
			std::next_permutation(std::begin(res), std::end(res));
		}

		std::cout << "KthPermutationSequence NextPermuBased for \"" << k << "\"-th of \"1..." << n << "\" (" << before << "): " << res << std::endl;
		return res;
	}

	std::string MathBased(int n, int k)//k-th: 1-based
	{
		std::vector<int> nums(n);//1...n in ascending order
		int factorial = 1;//aka permutation count
		for (int i = 0; i < n; ++i)
		{
			nums[i] = i + 1;
			factorial *= (i + 1);
		}
		std::string before = Debug::ToStr1D<int>()(nums);

		int permuCount = factorial;
		int K = k;
		--K;//to 0-based
		std::string res;
		for (int digitCount = n; digitCount >= 1; --digitCount)
		{
			permuCount /= digitCount;//remove the highest factorial factor to get remaining permuCount after taking out 1 digit
			int idx = K / permuCount;//get the leftmost digit, which is the section index (0-based)
			res.push_back(nums[idx] + '0');

			nums.erase(nums.begin() + idx);//remove the leftmost digit
			K %= permuCount;//make K in the range of all the permutations after taking out 1 digit
		}

		std::cout << "KthPermutationSequence MathBased for \"" << k << "\"-th of \"1..." << n << "\" (" << before << "): " << res << std::endl;
		return res;
	}

	std::string MathBased2(int n, int k)
	{
		std::vector<int> factorialSeq(n + 1, 1);

		for (int i = 2; i <= n; ++i)
		{
			factorialSeq[i] = factorialSeq[i - 1] * i;
		}
		std::cout << "FactorialSeq: " << Debug::ToStr1D<int>()(factorialSeq) << std::endl;

		std::string res(n, '1');
		for (int i = 0; i < n; ++i)
		{
			res[i] += i;
		}
		//res is now 1...n
		std::string before(res);
		int K = k;
		if (K > factorialSeq[n])//k > n!
		{
			std::cout << "KthPermutationSequence MathBased2 for \"" << k << "\"-th of \"1..." << n << "\" (" << before << "): " << res << std::endl;
			return res;
		}
		
		--K;
		for (int i = 0; i < n - 1; ++i)
		{
			int j = i + K / factorialSeq[n - 1 - i];
			K %= factorialSeq[n - 1 - i];
			char t = res[j];
			for (; j > i; --j)
				res[j] = res[j - 1];

			res[j] = t;
		}

		std::cout << "KthPermutationSequence MathBased2 for \"" << k << "\"-th of \"1..." << n << "\" (" << before << "): " << res << std::endl;
		return res;
	}
};
/*
KthPermutationSequence NextPermuBased for "5"-th of "1...4" (1234): 1423
KthPermutationSequence MathBased for "5"-th of "1...4" (1, 2, 3, 4): 1423
FactorialSeq: 1, 1, 2, 6, 24
KthPermutationSequence MathBased2 for "5"-th of "1...4" (1234): 1423
*/
#endif