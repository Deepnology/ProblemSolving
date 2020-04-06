#ifndef TWO_SUM_ABS_SORTED_ARRAY_H
#define TWO_SUM_ABS_SORTED_ARRAY_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Search for a pair-sum in an abs-sorted array
An abs-sorted array is an array of numbers in which |A[i]| <= |A[j]| where i < j.
For example:
-49, 75, 103, -147, 164, -197, -238, 314, 348, -422.
Design an algorithm that takes an abs-sorted array A and a number K, and returns a pair of indices of elements in A that sum up to K.
For example of the above array, if K = 167, your algorithm should output (3, 7).
Output (-1, -1) if there is no such pair.

Use the greedy algorithm for the TwoSum.h problem with some modification.
1. first check the positive-negative-pairs
   since the input array is abs-sorted, we can start with the rightmost positive and the rightmost negative
   for the positives, it must be in decreasing order from right to left
   for the negatives, it must be in ascending order from right to left
   if the pair sum is too big, find the next left positive
   if the pair sum is too small, fine the next left negative

2. if we can't find a solution of positive-negative-pair, if the target sum >= 0, which means the pair must be composed of 2 positives
, otherwise, the pair must be composed of 2 negatives

   for the case of 2-positives, start with the leftmost positive and the rightmost positive
   if the pair sum is too big, find the next left positive from the rightmost positive
   if the pair sum is too small, find the next right positive from the leftmost positive

   for the case of 2-negatives, start with the leftmost negative and the rightmost negative
   if the pair sum is too big, find the next right negative from the leftmost negative
   if the pair sum is too small, find the next left negative from the rightmost negative

O(n) time, O(1) space
*/
class TwoSumAbsSortedArray
{
public:
	TwoSumAbsSortedArray(){}
	~TwoSumAbsSortedArray(){}

	std::pair<int, int> FindPairIndex_Greedy(const std::vector<int> & v, int sum)
	{
		std::pair<int, int> res = this->findPositiveNegativePair(v, sum);//1. find positive-negative-pair
		if (res.first == -1 && res.second == -1)
			res = sum >= 0 ? this->find2PositiveOr2NegativePair(v, sum, std::less<int>())//2. sum>=0: find 2-positive-pair
			: this->find2PositiveOr2NegativePair(v, sum, std::greater_equal<int>());//3. sum<0: find 2-negative-pair

		std::cout << "TwoSumAbsSortedArray FindPairIndex_Greedy for \"" << sum << "\" from \"" << Debug::ToStr1D<int>()(v) << "\": [" << res.first << "," << res.second << "]" << std::endl;
		return res;
	}
private:
	template<class Comp>
	std::pair<int, int> find2PositiveOr2NegativePair(const std::vector<int> & v, int sum, Comp comp)
	{
		int N = v.size();
		//both positives or both negatives. (one from left and one from right)
		int left = 0;
		int right = N - 1;

		//now consider for the case where sum >= 0, comp = std::less<int>
		//find the next right positive or zero
		while (left < right && comp(v[left], 0))
			++left;
		//find the next left positive or zero
		while (left < right && comp(v[right], 0))
			--right;

		while (left < right)
		{
			if (v[left] + v[right] == sum)
				return{ left,right };
			else if (comp(v[left] + v[right], sum))//too small: need a bigger positive
			{
				//find the next right positive or zero
				do
				{
					++left;
				} while (left < right && comp(v[left], 0));
			}
			else//too big: need a smaller positive
			{
				//find the next left positive or zero
				do
				{
					--right;
				} while (left < right && comp(v[right], 0));
			}
		}
		return{ -1, -1 };
	}
	std::pair<int, int> findPositiveNegativePair(const std::vector<int> & v, int sum)
	{
		int N = v.size();
		int pos = N - 1;//from right
		int neg = N - 1;//from right

		//find the rightmost positive or zero
		while (pos >= 0 && v[pos] < 0)
			--pos;

		//find the rightmost negative
		while (neg >= 0 && v[neg] >= 0)
			--neg;

		while (pos >= 0 && neg >= 0)
		{
			if (v[pos] + v[neg] == sum)
				return{ pos, neg };
			else if (v[pos] + v[neg] > sum)//too big: need a smaller positive
			{
				//find the next left positive or zero
				do
				{
					--pos;
				} while (pos >= 0 && v[pos] < 0);
			}
			else//too small: need a bigger negative
			{
				//find the next left negative
				do
				{
					--neg;
				} while (neg >= 0 && v[neg] >= 0);
			}
		}
		return{ -1, -1 };
	}
};
/*
TwoSumAbsSortedArray FindPairIndex_Greedy for "167" from "-49, 75, 103, -147, 164, -197, -238, 314, 348, -422": [7,3]
*/
#endif