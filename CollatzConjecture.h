#ifndef COLLATZ_CONJECTURE_H
#define COLLATZ_CONJECTURE_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Debug.h"
/*
Elements of programming interview, HashTable: Test the Collatz conjecture
Take any natural number n.
If n is even, divide it by 2 to get n/2.
If n is odd, multiply it by 3 and add 1 to obtain 3n + 1.
Repeat the process indefinitely.
The conjecture is that no matter what number you start with, you will always eventually reach 1.
The property has also been called oneness.

Despite intense efforts, the Collatz Conjecture has not been proved or disproved.
Suppose you were given the task of checking the Collatz Conjecture for the first billion integers.
A direct approach would be to compute the convergence sequence for each number in this set.
How would you test the Collatz Conjecture for the first n positive integers?

O(n) time

Leetcode: Integer Replacement
Given a positive integer n and you can do operations as follow:
If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?
Example 1:
Input:
8
Output:
3
Explanation:
8 -> 4 -> 2 -> 1
Example 2:
Input:
7
Output:
4
Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1
*/
class CollatzConjecture
{
public:
	CollatzConjecture(){}
	~CollatzConjecture(){}

	std::vector<long> FindSequenceRecur(int n)
	{
		std::vector<long> res;
		this->recur((long)n, res);
		std::cout << "CollatzConjecture FindSequenceRecur for \"" << n << "\": " << Debug::ToStr1D<long>()(res) << std::endl;
		return res;
	}
private:
	void recur(long n, std::vector<long> & res)
	{
		res.push_back(n);
		if (n == 1)
			return;
		if (n & 1)//odd
			this->recur(3 * n + 1, res);
		else//even
			this->recur(n >> 1, res);
	}

public:
	bool TestFirstNNums_HashTable(int n)
	{
		std::unordered_set<long> visitedOddNums;//visited odd nums that converge to 1

		//start from 2 since we don't need to test 1
		for (int i = 2; i <= n; ++i)
		{
			std::unordered_set<long> visitedGreaterNums;
			long num = i;

			//test all greater equal nums
			//all smaller nums have already been verified so don't need to test
			while (num >= i)
			{
				if (visitedGreaterNums.find(num) != visitedGreaterNums.end())//found a repetition which will be stuck in a loop and won't converge
				{
					std::cout << "CollatzConjecture TestFirstNNums_HashTable for \"" << n << "\": Failed at " << i << " which visited " << num << " for twice." << std::endl;
					return false;
				}
				visitedGreaterNums.insert(num);

				if (num & 1)//odd
				{
					if (visitedOddNums.find(num) != visitedOddNums.end())
						break;//num has already been verified to converge to 1
					visitedOddNums.insert(num);//since only odd nums can grow greater than its original value, we keep track only odd nums (even nums will be divided by 2, and smaller nums have already been verified)

					long nextNum = 3 * num + 1;
					if (nextNum <= num)
						throw std::overflow_error("");
					num = nextNum;//num = 3 * num + 1
				}
				else//even
					num >>= 1;//num /= 2
			}
		}

		std::cout << "CollatzConjecture TestFirstNNums_HashTable for \"" << n << "\": Succeeded, verified odd nums: " << Debug::ToStr1D<long>()(visitedOddNums) << std::endl;
		return true;
	}

	bool TestFirstNNums_BruteForce(int n)
	{
		for (int i = 2; i <= n; ++i)
		{
			std::unordered_set<long> visitedGreaterNums;
			long num = i;

			//test all greater equal nums
			//all smaller nums have already been verified so don't need to test
			while (num >= i)
			{
				if (visitedGreaterNums.find(num) != visitedGreaterNums.end())//found a repetition which will be stuck in a loop and won't converge
				{
					std::cout << "CollatzConjecture TestFirstNNums_BruteForce for \"" << n << "\": Failed at " << i << " which visited " << num << " for twice." << std::endl;
					return false;
				}
				visitedGreaterNums.insert(num);

				if (num & 1)
					num = 3 * num + 1;
				else
					num >>= 1;
			}
		}

		std::cout << "CollatzConjecture TestFirstNNums_BruteForce for \"" << n << "\": Succeeded" << std::endl;
		return true;
	}

	//Leetcode: Integer Replacement
	int IntegerReplacement(int n)
	{
		int res = INT_MAX;
		recur(n, 0, res);
		int res2 = INT_MAX;
		recur2(n, 0, res2);

		std::cout << "CollatzConjecture IntegerReplacement for \"" << n << "\": " << res << ", " << res2 << std::endl;
		return res;
	}
private:
	void recur(long long cur, int curLen, int & minLen)
	{
		if (cur == 1)
		{
			minLen = std::min(minLen, curLen);
			return;
		}
		if (cur & 1)
		{
			recur(cur + 1, curLen + 1, minLen);
			recur(cur - 1, curLen + 1, minLen);
		}
		else
			recur(cur >> 1, curLen + 1, minLen);
	}
	void recur2(long long cur, int curLen, int & minLen)
	{
		if (cur == 1)
		{
			minLen = std::min(minLen, curLen);
			return;
		}
		if (cur & 1)
		{
			if ((cur + 1) % 4 == 0 && cur != 3)
				recur(cur + 1, curLen + 1, minLen);
			else
				recur(cur - 1, curLen + 1, minLen);
		}
		else
			recur(cur >> 1, curLen + 1, minLen);
	}
};
/*
CollatzConjecture FindSequenceRecur for "17": 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
CollatzConjecture TestFirstNNums_BruteForce for "17": Succeeded
CollatzConjecture TestFirstNNums_HashTable for "17": Succeeded, verified odd nums: 11, 3, 13, 5, 23, 15, 7, 9, 17, 35, 53
CollatzConjecture IntegerReplacement for "8": 3, 3
CollatzConjecture IntegerReplacement for "7": 4, 4
*/
#endif