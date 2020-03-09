#ifndef K_SUM_H
#define K_SUM_H
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "Debug.h"
/*
Leetcode: Combination Sum III
Find all possible combinations of k numbers that add up to a number n, 
given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
Ensure that numbers within the set are sorted in ascending order.
Example 1:
Input: k = 3, n = 7
Output: [[1,2,4]]
Example 2:
Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]

Elements of programming interview, Greedy: The 3-sum problem, variant
Solve the same problem when k is an additional input.
http://tech-wonderland.net/blog/k-sum-problem-analysis-recursive-implementation-lower-bound.html
Recursively reduce K Sum to K-1 Sum, K-2 Sum, ..., 2 Sum, where 2 Sum problem can be solved by a greedy linear time approach.

See also TwoSum.h, ThreeSum.h, FourSum.h, CombinationSum.h
*/
class KSum
{
public:
	KSum(){}
	~KSum(){}

	std::vector<std::vector<int>> TwoSum_FixRecur(std::vector<int> & v, int target, int K)
	{
		//sort for skipping duplicates and greedy linear time approach for 2-Sum base cases
		std::sort(v.begin(), v.end(), std::less<int>());
		std::vector<std::vector<int>> res = this->twoSumFixRecur(v, target, K, 0);
		std::cout << "KSum TwoSum_FixRecur for \"" << K << "-Sum, " << target << ", From " << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	std::vector<std::vector<int>> twoSumFixRecur(const std::vector<int> & v, int target, int K, int begin)
	{
		int N = v.size();
		std::vector<std::vector<int>> res;
		if (K == 2)//reduced to 2-sum problem
		{
			//greedy (since v is sorted)
			int i = begin;
			int j = N - 1;
			while (i < j)
			{
				if (i > begin && v[i] == v[i - 1])//skip duplicate
				{
					++i;
					continue;
				}
				int sum = v[i] + v[j];
				if (sum < target)
					++i;
				else if (sum > target)
					--j;
				else
				{
					res.push_back({ v[i], v[j] });
					++i;
					--j;
				}
			}
			return res;
		}

		//now K > 2
		for (int i = begin; i < N; ++i)
		{
			if (i > begin && v[i] == v[i - 1])//skip duplicate
				continue;

			//find all (K-1) sum combinations excluding current number on the right
			std::vector<std::vector<int>> Kminus1Sums = this->twoSumFixRecur(v, target - v[i], K - 1, i + 1);

			//append each (K-1) sum combination to current number, and add to res
			int M = Kminus1Sums.size();
			for (int j = 0; j < M; ++j)
			{
				std::vector<int> kSum;
				kSum.push_back(v[i]);
				kSum.insert(kSum.end(), Kminus1Sums[j].begin(), Kminus1Sums[j].end());
				res.push_back(kSum);
			}
		}
		return res;
	}


public:
	std::vector<std::vector<int>> FindAllUnique_NoRepeats_FromDupArray_FixRecur(std::vector<int> & nums, int targetSum, int K)//nums might have duplicates
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int> > res;
		std::vector<int> path;
		this->FixRecur_NoRepeats_FromDupArray(nums, targetSum, K, 0, path, res);

		std::cout << "KSum FixRecur for \"" << K << "-Sum, " << targetSum << " From " << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void FixRecur_NoRepeats_FromDupArray(std::vector<int> & nums, int targetSum, int count, int start
		, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			if (targetSum == 0)
				res.push_back(path);
			return;
		}

		int N = nums.size();
		for (int index = start; index < N; ++index)//next pick(combine) one number from nums[start]~nums[N-1]
		{
			if (index > start && nums[index] == nums[index - 1])
				continue;//skip duplicates because nums might have duplicates (nums was already sorted)

			if (nums[start] > targetSum)
				continue;

			path.push_back(nums[index]);
			this->FixRecur_NoRepeats_FromDupArray(nums, targetSum - nums[index], count - 1, index + 1, path, res);//take index+1 to not allow repeats
			path.pop_back();
		}
	}

public:
	std::vector<std::vector<int> > FindAllUnique_NoRepeats_FromDupArray_InExcludeRecur(std::vector<int> & nums, int targetSum, int K)//nums might have duplicates
	{
		std::sort(std::begin(nums), std::end(nums));
		std::vector<std::vector<int> > res;
		std::vector<int> path;
		this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum, K, 0, path, res);

		std::cout << "KSum InExcludeRecur for \"" << K << "-Sum, " << targetSum << " From " << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
private:
	void InExcludeRecur_NoRepeats_FromDupArray(std::vector<int> & nums, int targetSum, int count, int start
		, std::vector<int> & path, std::vector<std::vector<int> > & res)
	{
		if (count == 0)
		{
			if (targetSum == 0)
				res.push_back(path);
			return;
		}
		int N = nums.size();
		if (start == N)
			return;

		if (nums[start] <= targetSum)
		{
			//1. include current element
			path.push_back(nums[start]);
			this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum - nums[start], count - 1, start + 1, path, res);//take start+1 to not allow repeats
			path.pop_back();
		}
		//2. exclude current element and all duplicates
		int stride = 1;
		while (start + stride < N && nums[start] == nums[start + stride])
			++stride;
		this->InExcludeRecur_NoRepeats_FromDupArray(nums, targetSum, count, start + stride, path, res);
	}
};
/*
KSum TwoSum_FixRecur for "4-Sum, 42, From 2, 3, 4, 5, 8, 10, 12, 12, 16, 18": [2,10,12,18], [2,12,12,16], [3,5,16,18], [4,8,12,18], [4,10,12,16], [8,10,12,12]
KSum FixRecur for "4-Sum, 42 From 2, 3, 4, 5, 8, 10, 12, 12, 16, 18": [2,10,12,18], [2,12,12,16], [3,5,16,18], [4,8,12,18], [4,10,12,16], [8,10,12,12]
KSum InExcludeRecur for "4-Sum, 42 From 2, 3, 4, 5, 8, 10, 12, 12, 16, 18": [2,10,12,18], [2,12,12,16], [3,5,16,18], [4,8,12,18], [4,10,12,16], [8,10,12,12]
KSum TwoSum_FixRecur for "4-Sum, 46, From 2, 3, 4, 13, 13, 14, 14, 14, 15, 20": [3,14,14,15], [4,13,14,15], [4,14,14,14]
KSum FixRecur for "4-Sum, 46 From 2, 3, 4, 13, 13, 14, 14, 14, 15, 20": [3,14,14,15], [4,13,14,15], [4,14,14,14]
KSum InExcludeRecur for "4-Sum, 46 From 2, 3, 4, 13, 13, 14, 14, 14, 15, 20": [3,14,14,15], [4,13,14,15], [4,14,14,14]
*/
#endif