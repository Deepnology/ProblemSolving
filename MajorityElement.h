#ifndef MAJORITY_ELEMENT_H
#define MAJORITY_ELEMENT_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Debug.h"
/*
https://leetcode.com/problems/majority-element/
Elements of programming interview, Greedy: Find the majority element
http://www.geeksforgeeks.org/majority-element/
A majority element in an array A[] of size n is an element that appears more than n/2 times
(and hence there is at most one such element).
majorityElementCount > n/2

The majority property is still valid in the remaining set of elements when we take out a pair of 2 different elements.
So we can repeatedly take out any 2 different elements until we cannot find any 2 different elements in the remaining set.
Then all the elements in the final remaining set should be the majority elements.
Proof:
case 1: neither of the 2 different elements are the majority element.
majorityElementCount > n/2 > (n-2)/2
case 2: one of the 2 different elements is the majority element.
majorityElementCount-1 > n/2 - 1 = (n-2)/2

Moore's Voting Algo: O(n) time, O(1) space
Repeat Exclude 2 Diff Elements: O(n) time, O(1) space

Leetcode: Majority Element II
Given an integer array of size n, find all elements that appear more than |_ n/3 _| times.
The algorithm should run in linear time and in O(1) space.
Hint: How many majority elements could it possibly have?
Equivalent to GeneralizedMajorityElements.h

*/
class MajorityElement
{
public:
	MajorityElement(){}
	~MajorityElement(){}

	int MooresVotingAlgo(const std::vector<int> & A)
	{
		int N = A.size();
		int count = 0;
		int candidate;
		for (int i = 0; i < N; ++i)
		{
			if (count == 0)//reset candidate to A[i]
			{
				candidate = A[i];
				count = 1;
			}
			else if (candidate == A[i])
				++count;
			else
				--count;
		}

		std::cout << "MajorityElement MooresVotingAlgo for \"" << Debug::ToStr1D<int>()(A) << "\": " << candidate << std::endl;
		return candidate;
	}
	std::string MooresVotingAlgo_FromInputStream(std::istringstream & sin)
	{
		std::string candidate;
		std::string buf;
		int count = 0;
		while (sin >> buf)
		{
			if (count == 0)//reset candidate to cur
			{
				candidate = buf;
				count = 1;
			}
			else if (candidate == buf)
				++count;
			else
				--count;
		}

		std::cout << "MajorityElement MooresVotingAlgo_FromInputStream for \"" << sin.str() << "\": " << candidate << std::endl;
		return candidate;
	}

	void MooresVotingAlgo2(const std::vector<int> & A)
	{
		int N = A.size();

		//1. find a candidate
		int curMaj = 0;
		int curMajCount = 1;
		for (int i = 1; i < N; ++i)
		{
			if (A[curMaj] == A[i])
				++curMajCount;
			else
				--curMajCount;
			if (curMajCount == 0)
			{
				curMaj = i;
				curMajCount = 1;
			}
		}
		int majCand = A[curMaj];
		//2. check if the candidate occurs more than n/2 times
		int candCount = 0;
		for (int i = 0; i < N; ++i)
			if (A[i] == majCand)
				++candCount;
		bool foundMaj = candCount > N / 2 ? true : false;

		std::ostringstream oss;
		if (foundMaj)
			oss << majCand;
		else
			oss << "Null";
		std::cout << "MajorityElement MooresVotingAlgo2 for \"" << Debug::ToStr1D<int>()(A) << "\": " << oss.str() << std::endl;
	}

	void RepeatExclude2DiffElements(std::vector<int> & A)
	{
		int N = A.size();
		std::string before = Debug::ToStr1D<int>()(A);

		/*
		1. repeatedly move diff pairs to the left side
		keep track of the 2nd element of the last diff pair and compare its next element with cur element
		if diff, make them a pair and update the ptr to the 2nd element of the last diff pair
		*/
		int j = -1;//j always points to the 2nd element of the last diff pair
		for (int i = 0; i < N; ++i)
		{
			if (A[i] != A[j + 1])//current element is diff from the next element of the last diff pair
			{
				//make current element and the next element of the last diff pair a new pair
				//by moving current element to the next of next element of the last diff pair
				j += 2;
				std::swap(A[j], A[i]);
			}
		}
		int majCand = A[j + 1];//j+1 points to the next element of all diff pairs
		std::cout << Debug::ToStr1D<int>()(A) << std::endl;

		//2. check if the candidate occurs more than n/2 times
		int candCount = 0;
		for (int i = 0; i < N; ++i)
			if (A[i] == majCand)
				++candCount;
		bool foundMaj = candCount > N / 2 ? true : false;

		std::ostringstream oss;
		if (foundMaj)
			oss << majCand;
		else
			oss << "Null";
		std::cout << "MajorityElement RepeatExclude2DiffElements for \"" << before << "\": " << oss.str() << std::endl;
	}
};

class MajorityElement2
{
public:
	MajorityElement2(){}
	~MajorityElement2(){}

	//majority element appears at least N/3 times, which means it must appear at least once in every 3 distinct elements in average
	std::vector<int> MoreThanNDividedBy3(const std::vector<int> & nums)
	{
		int N = nums.size();
		std::unordered_map<int, int> candidateCount;//first: val, second: count (keep track of at most 3 distinct entries)

		//1. If majority element count should be more than N/3, it can possibly have at most 3 candidates. Keep track of 3 candidates and their counts
		for (int i = 0; i < N; ++i)
		{
			++candidateCount[nums[i]];

			if (candidateCount.size() == 4)
			{
				auto itr = candidateCount.begin();
				while (itr != candidateCount.end())
				{
					if (--(itr->second) == 0)
						candidateCount.erase(itr++);
					else
						++itr;
				}
			}
		}

		//2. now we found 3 candidates. reset their counts
		for (auto & itr : candidateCount)
		{
			itr.second = 0;
		}

		//3. compute the counts for each of the 3 candidates
		for (int i = 0; i < N; ++i)
		{
			auto itr = candidateCount.find(nums[i]);
			if (itr != candidateCount.end())
				++itr->second;
		}

		std::vector<int> res;
		for (const auto & itr : candidateCount)
		{
			if (itr.second > N / 3)
				res.push_back(itr.first);
		}

		std::cout << "MajorityElement2 MoreThanNDividedBy3 for \"" << Debug::ToStr1D<int>()(nums) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
MajorityElement MooresVotingAlgo for "1, 1, 2, 3, 4, 1, 6, 1, 7, 1, 1": 1
MajorityElement MooresVotingAlgo2 for "1, 1, 2, 3, 4, 1, 6, 1, 7, 1, 1": 1
1, 2, 1, 3, 4, 1, 6, 1, 7, 1, 1
MajorityElement RepeatExclude2DiffElements for "1, 1, 2, 3, 4, 1, 6, 1, 7, 1, 1": 1
MajorityElement MooresVotingAlgo for "3, 2, 4, 4, 4, 2, 1, 1, 3, 6, 1, 1, 1, 1, 6, 1, 1, 2, 7, 1, 1, 6, 1, 1, 1, 1, 7, 1": 1
MajorityElement MooresVotingAlgo2 for "3, 2, 4, 4, 4, 2, 1, 1, 3, 6, 1, 1, 1, 1, 6, 1, 1, 2, 7, 1, 1, 6, 1, 1, 1, 1, 7, 1": 1
3, 2, 4, 2, 4, 1, 4, 1, 3, 6, 1, 6, 1, 2, 1, 7, 1, 6, 1, 7, 1, 1, 1, 1, 1, 1, 1, 1
MajorityElement RepeatExclude2DiffElements for "3, 2, 4, 4, 4, 2, 1, 1, 3, 6, 1, 1, 1, 1, 6, 1, 1, 2, 7, 1, 1, 6, 1, 1, 1, 1, 7, 1": 1
MajorityElement MooresVotingAlgo_FromInputStream for "a b d f a f e f c f f e f f a f b f d f": f
MajorityElement2 MoreThanNDividedBy3 for "1, 1, 4, 5, 2, 3, 3, 3, 3, 2, 2, 4, 1, 3, 2, 2, 1, 2, 3, 2, 3, 2, 3": 3, 2
*/
#endif