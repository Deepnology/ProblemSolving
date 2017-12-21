#ifndef NTH_UGLY_NUM_H
#define NTH_UGLY_NUM_H
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Ugly number
http://www.geeksforgeeks.org/ugly-numbers/
http://stackoverflow.com/questions/4600048/nth-ugly-number
Ugly numbers are numbers whose prime factors are 2, 3, or 5.
The sequence 1,2,3,4,5,6,8,9,10,12,15,... shows the first 11 ugly numbers.
By convention, 1 is included.
Find the N-th ugly number.

Google
http://www.careercup.com/question?id=23823662
Given an equation in the form 2^i * 3^j * 5^k * 7^l where i,j,k,l are positive integers.
Generate a sequence of numbers from the equation in sorted order efficiently.

DP: O(n) time, O(n) space
BruteForce: O(1) space

Leetcode: Super Ugly Number
Find the nth super ugly number.
Super ugly numbers are positive numbers whose all prime factors are in the given prime list of size k.

MinHeap: O(n * logk) ~ O(n * k * logk) time, O(n + k) space
LinearFindingMin: O(n * k) time, O(n + k) space

see also FirstKAPlusBSqrt2.h, ShortestStraightLineProgramXPowN.h
*/
class NthUglyNum
{
public:
	NthUglyNum(){}
	~NthUglyNum(){}

	unsigned int DP1D_3Primes(int n)
	{
		std::vector<unsigned int> uglyVec(n);
		unsigned int nxtMul2Val = 2;
		unsigned int nxtMul3Val = 3;
		unsigned int nxtMul5Val = 5;
		int nxtMul2 = 0;
		int nxtMul3 = 0;
		int nxtMul5 = 0;
		uglyVec[0] = 1;
		for (int i = 1; i < n; ++i)
		{
			uglyVec[i] = this->MinOf3(nxtMul2Val, nxtMul3Val, nxtMul5Val);

			//update nxtMul2Val, nxtMul3Val, nxtMul5 and advance nxtMul2, nxtMul3, nxtMul5 if whose val was taken
			if (uglyVec[i] == nxtMul2Val)
				nxtMul2Val = uglyVec[++nxtMul2] * 2;
			if (uglyVec[i] == nxtMul3Val)
				nxtMul3Val = uglyVec[++nxtMul3] * 3;
			if (uglyVec[i] == nxtMul5Val)
				nxtMul5Val = uglyVec[++nxtMul5] * 5;
		}
		std::cout << "NthUglyNum DP1D_3Primes for \"" << n << "-th\": " << Debug::ToStr1D<unsigned int>()(uglyVec) << std::endl;
		return uglyVec[n - 1];
	}

	unsigned int DP1D_4Primes(int n)
	{
		std::vector<unsigned int> uglyVec(n);
		unsigned int nxtMul2Val = 2;
		unsigned int nxtMul3Val = 3;
		unsigned int nxtMul5Val = 5;
		unsigned int nxtMul7Val = 7;
		int nxtMul2 = 0;
		int nxtMul3 = 0;
		int nxtMul5 = 0;
		int nxtMul7 = 0;
		uglyVec[0] = 1;
		for (int i = 1; i < n; ++i)
		{
			uglyVec[i] = this->MinOf4(nxtMul2Val, nxtMul3Val, nxtMul5Val, nxtMul7Val);

			//update nxtMul2Val, nxtMul3Val, nxtMul5, mxtMul7 and advance nxtMul2, nxtMul3, nxtMul5, nxtMul7 if whose val was taken
			if (uglyVec[i] == nxtMul2Val)
				nxtMul2Val = uglyVec[++nxtMul2] * 2;
			if (uglyVec[i] == nxtMul3Val)
				nxtMul3Val = uglyVec[++nxtMul3] * 3;
			if (uglyVec[i] == nxtMul5Val)
				nxtMul5Val = uglyVec[++nxtMul5] * 5;
			if (uglyVec[i] == nxtMul7Val)
				nxtMul7Val = uglyVec[++nxtMul7] * 7;
		}
		std::cout << "NthUglyNum DP1D_4Primes for \"" << n << "-th\": " << Debug::ToStr1D<unsigned int>()(uglyVec) << std::endl;
		return uglyVec[n - 1];
	}

	unsigned int BruteForce_3Primes(int n)
	{
		int uglyNumCount = 1;
		int curNum = 1;
		while (uglyNumCount < n)
		{
			++curNum;
			if (this->IsUgly(curNum))
				++uglyNumCount;
		}
		std::cout << "NthUglyNum BruteForce_3Primes for \"" << n << "-th\": " << curNum << std::endl;
		return curNum;
	}
	bool IsUgly(int n)
	{
		if (n == 0)
			return false;
		n = this->RemoveFactor(n, 2);
		n = this->RemoveFactor(n, 3);
		n = this->RemoveFactor(n, 5);
		return n == 1 ? true : false;
	}
	int RemoveFactor(int n, int factor)
	{
		while (n % factor == 0)
			n /= factor;
		return n;
	}

	unsigned int MinHeap_MultiPrimes(int n, std::vector<unsigned int> & primes)
	{
		std::priority_queue<std::pair<unsigned int, unsigned int>, std::vector<std::pair<unsigned int, unsigned int>>, std::greater<std::pair<unsigned int, unsigned int>>> minHeap;//first: nxtPrimeMultiples val, second: prime index
		int N = primes.size();
		for (int i = 0; i < N; ++i)
			minHeap.push({ primes[i], i });
		std::vector<unsigned int> res;
		res.push_back(1);
		std::vector<unsigned int> nxtPrimeMulIdx(N, 0);//keep track of the index of "next prime multiples for each prime" in res
		for (int i = 1; i < n; ++i)
		{
			res.push_back(minHeap.top().first);

			do
			{
				auto p = minHeap.top();
				minHeap.pop();

				++nxtPrimeMulIdx[p.second];
				minHeap.push({ res[nxtPrimeMulIdx[p.second]] * primes[p.second], p.second });

			} while (!minHeap.empty() && minHeap.top().first == res.back());
		}

		std::cout << Debug::ToStr1D<unsigned int>()(res) << std::endl;
		std::cout << "NthUglyNum MinHeap_MultiPrimes for \"" << n << "\"th from \"" << Debug::ToStr1D<unsigned int>()(primes) << "\": " << res[n - 1] << std::endl;
		return res[n - 1];
	}

	//this is faster
	unsigned int MultiPrimes(int n, std::vector<unsigned int> & primes)
	{
		std::vector<std::pair<unsigned int, unsigned int>> nxtPrimeMul;//first: nxtPrimeMultiples val, second: idx of nxtPrimeMultiple in res
		int N = primes.size();
		for (int k = 0; k < N; ++k)
			nxtPrimeMul.push_back({ primes[k], 0 });
		std::vector<unsigned int> res;
		res.push_back(1);

		for (int i = 1; i < n; ++i)
		{
			unsigned int minVal = this->MinOf(nxtPrimeMul);
			res.push_back(minVal);
			for (int k = 0; k < N; ++k)
				if (minVal == nxtPrimeMul[k].first)
				{
					++nxtPrimeMul[k].second;
					nxtPrimeMul[k].first = res[nxtPrimeMul[k].second] * primes[k];
				}
		}

		std::cout << Debug::ToStr1D<unsigned int>()(res) << std::endl;
		std::cout << "NthUglyNum MultiPrimes for \"" << n << "\"th from \"" << Debug::ToStr1D<unsigned int>()(primes) << "\": " << res[n - 1] << std::endl;
		return res[n - 1];
	}

private:
	unsigned int MinOf3(unsigned int a, unsigned int b, unsigned int c)
	{
		return std::min(a, std::min(b, c));
	}
	unsigned int MinOf4(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
	{
		return std::min(a, std::min(b, std::min(c, d)));
	}
	unsigned int MinOf(const std::vector<std::pair<unsigned int, unsigned int>> & v)
	{
		unsigned int min = UINT32_MAX;
		for (const auto & i : v)
			min = std::min(min, i.first);
		return min;
	}
};
/*
NthUglyNum DP1D_3Primes for "20-th": 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 27, 30, 32, 36
NthUglyNum DP1D_4Primes for "20-th": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 24, 25, 27
NthUglyNum BruteForce_3Primes for "20-th": 36
1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32
NthUglyNum MinHeap_MultiPrimes for "12"th from "2, 7, 13, 19": 32
1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32
NthUglyNum MultiPrimes for "12"th from "2, 7, 13, 19": 32
*/
#endif