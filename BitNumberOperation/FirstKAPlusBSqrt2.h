#ifndef FIRST_K_A_PLUS_B_SQRT2_H
#define FIRST_K_A_PLUS_B_SQRT2_H
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include "Debug.h"
/*
Elements of programming interview, Greedy: Enumerate numbers of the form a + b*Sqrt(2)
Let Sq be the set of real numbers of the form a + b*Sqrt(q), where a and b are nonnegative integers, and q is an integer which is not the square of another integer.
Such sets have special properties, e.g., they are closed under addition and multiplication.
Design an algorithm for efficiently computing the k smallest real numbers of the form a + b*Sqrt(2) for nonnegative integers a and b.

A key fact about Sqrt(2) is that it is irrational, i.e., it cannot equal to a/b for any integers a, b.
This implies that if x + y*Sqrt(2) == m + n*Sqrt(2), then x == m and y == n. (Since otherwise Sqrt(2) == (x-m)/(y-n).)

Greedy:
The key idea is that the (n+1)-th entry in res will be the sum of 1 or Sqrt(2) with a previous entry.
We could iterate through the first n entries in res and track the smallest value of the form res[i]+1 or res[i]+Sqrt(2) which is greater than res[n-1].

UseMinHeap: O(klogk) time, O(k) space
Greedy: O(k) time, O(1) space

see also NthUglyNum.h, ShortestStraightLineProgramXPowN.h
*/
class FirstKAPlusBSqrt2
{
public:
	FirstKAPlusBSqrt2(){}
	~FirstKAPlusBSqrt2(){}
	typedef std::pair<std::pair<int, int>, double> Num;//first.first: a, first.second: b, second: a + b*Sqrt(2)
	struct NumSmallerThan
	{
		bool operator()(const Num & a, const Num & b) const
		{
			return a.second != b.second ? a.second < b.second : a.first.first != b.first.first ? a.first.first < b.first.first : a.first.second < b.first.second;
		}
	};
	std::vector<Num> BFS_MinHeap(int k)
	{
		std::set<Num, NumSmallerThan> minHeap;
		std::vector<Num> res;
		minHeap.insert({ { 0, 0 }, 0 });
		while ((int)res.size() < k)
		{
			auto itr = minHeap.cbegin();
			res.push_back(*itr);

			minHeap.insert({ { itr->first.first + 1, itr->first.second }, this->APlusBSqrt2(itr->first.first + 1, itr->first.second) });//(prevA+1) + prevB*Sqrt(2)
			minHeap.insert({ { itr->first.first, itr->first.second + 1 }, this->APlusBSqrt2(itr->first.first, itr->first.second + 1) });//prevA + (prevB+1)*Sqrt(2)
			minHeap.erase(itr);
		}

		std::cout << "FirstKAPlusBSqrt2 BFS_MinHeap for \"" << k << "\": " << Debug::ToStr1D<int, double>()(res) << std::endl;
		return res;
	}

	std::vector<Num> Greedy(int k)
	{
		std::vector<Num> res;
		res.push_back({ { 0, 0 }, 0 });
		int largestA = 0;//keep track of the index of cur max a
		int largestB = 0;//keep track of the index of cur max b
		while ((int)res.size() < k)
		{
			Num nextA({ { res[largestA].first.first + 1, res[largestA].first.second }, this->APlusBSqrt2(res[largestA].first.first + 1, res[largestA].first.second) });//(largestA_A+1) + largestA_B*Sqrt(2)
			Num nextB({ { res[largestB].first.first, res[largestB].first.second + 1 }, this->APlusBSqrt2(res[largestB].first.first, res[largestB].first.second + 1) });//largestB_B + (largestB_B+1)*Sqrt(2)

			if (nextA.second < nextB.second)
			{
				++largestA;
				res.push_back(nextA);
			}
			else if (nextB.second < nextA.second)
			{
				++largestB;
				res.push_back(nextB);
			}
			else//nextA.second == nextB.second
			{
				++largestA;
				++largestB;
				res.push_back(nextA);
			}
		}

		std::cout << "FirstKAPlusBSqrt2 Greedy for \"" << k << "\": " << Debug::ToStr1D<int, double>()(res) << std::endl;
		return res;
	}

private:
	double APlusBSqrt2(int a, int b)
	{
		return a + b * std::sqrt(2);
	}
};
/*
FirstKAPlusBSqrt2 BFS_MinHeap for "20": [(0,0),0], [(1,0),1], [(0,1),1.41421], [(2,0),2], [(1,1),2.41421], [(0,2),2.82843], [(3,0),3], [(2,1),3.41421], [(1,2),3.82843], [(4,0),4], [(0,3),4.24264], [(3,1),4.41421], [(2,2),4.82843], [(5,0),5], [(1,3),5.24264], [(4,1),5.41421], [(0,4),5.65685], [(3,2),5.82843], [(6,0),6], [(2,3),6.24264]
FirstKAPlusBSqrt2 Greedy for "20": [(0,0),0], [(1,0),1], [(0,1),1.41421], [(2,0),2], [(1,1),2.41421], [(0,2),2.82843], [(3,0),3], [(2,1),3.41421], [(1,2),3.82843], [(4,0),4], [(0,3),4.24264], [(3,1),4.41421], [(2,2),4.82843], [(5,0),5], [(1,3),5.24264], [(4,1),5.41421], [(0,4),5.65685], [(3,2),5.82843], [(6,0),6], [(2,3),6.24264]
*/
#endif