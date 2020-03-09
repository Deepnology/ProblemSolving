#ifndef FIRST_K_CLOSEST_STARS_H
#define FIRST_K_CLOSEST_STARS_H
#include <string>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Elements of programming interview, Heaps: Compute the K closest stars
Given a very large array of distances of stars to earth.
How would you compute the first K stars which are closest to the earth?
You have a limited RAM.
(This problem is equivalent to find the first K smallest elements.)

MaxHeap:
Keep a maxHeap with at most K elements.
O(nlogk) time, O(k) space

Selection: O(n) time, O(1) space
*/
class FirstKClosestStars
{
public:
	FirstKClosestStars(){}
	~FirstKClosestStars(){}
	struct SmallerThanComp
	{
		bool operator()(const std::pair<int, int> & a, const std::pair<int, int> & b)
		{
			return a.first < b.first;
		}
	};
	std::vector<std::pair<int, int> > MaxHeap(const std::vector<int> & v, int K)//K: 1-based
	{
		int N = v.size();
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, SmallerThanComp> maxHeap;
		//first: val (distance), second: idx

		for (int i = 0; i < K && i < N; ++i)
		{
			maxHeap.push(std::make_pair(v[i], i));
		}
		for (int i = K; i < N; ++i)
		{
			if (v[i] < maxHeap.top().first)
			{
				maxHeap.pop();
				maxHeap.push(std::make_pair(v[i], i));
			}
		}

		std::vector<std::pair<int, int> > res;
		while (!maxHeap.empty())
		{
			res.push_back(maxHeap.top());
			maxHeap.pop();
		}

		std::cout << "FirstKClosestStars MaxHeap for \"" << K << "\" in \"" << Debug::ToStr1D<int>()(v) << "\" [val,idx]: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<std::pair<int, int> > MaxHeap_FromISS(std::istringstream && iss, int K)//K: 1-based
	{
		std::string before = iss.str();
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, SmallerThanComp> maxHeap;
		std::string line;
		while (getline(iss, line))
		{
			std::istringstream linestream(line);
			std::string buf;
			getline(linestream, buf, ',');
			int val = stoi(buf);
			getline(linestream, buf, ',');
			int idx = stoi(buf);
			if (maxHeap.size() == K)
			{
				if (val < maxHeap.top().first)
				{
					maxHeap.pop();
					maxHeap.push(std::make_pair(val, idx));
				}
			}
			else
				maxHeap.push(std::make_pair(val, idx));
		}

		std::vector<std::pair<int, int> > res;
		while (!maxHeap.empty())
		{
			res.push_back(maxHeap.top());
			maxHeap.pop();
		}

		std::cout << before << std::endl;
		std::cout << "FirstKClosestStars MaxHeap_FromISS for \"" << K << "\" in above lists [val,idx]: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Selection(std::vector<int> && v, int K)//K: 1-based
	{
		std::string before = Debug::ToStr1D<int>()(v);
		int N = v.size();
		int left = 0;
		int right = N - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			int pivotVal = v[mid];
			int pivot = std::partition(v.begin() + left, v.begin() + right + 1, [&](const int & a)->bool
			{
				return a < pivotVal;
			}) - v.begin();
			for (int i = pivot; i < right; ++i)
			{
				if (!(v[pivot] < v[i]))
					std::swap(v[pivot], v[i]);
			}

			if (K < pivot - left + 1)
				right = pivot - 1;
			else if (K > pivot - left + 1)
			{
				K -= (pivot - left + 1);
				left = pivot + 1;
			}
			else
				break;
		}

		std::vector<int> res;
		for (int i = 0; i < K; ++i)
			res.push_back(v[i]);

		std::cout << "FirstKClosestStars Selection for \"" << K << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> STL_Nth_Element(std::vector<int> && v, int K)//K: 1-based
	{
		std::string before = Debug::ToStr1D<int>()(v);

		std::nth_element(v.begin(), v.begin() + (K - 1), v.end(), std::less<int>());

		std::vector<int> res;
		for (int i = 0; i < K; ++i)
			res.push_back(v[i]);

		std::cout << "FirstKClosestStars STL_Nth_Element for \"" << K << "\" in \"" << before << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
FirstKClosestStars MaxHeap for "5" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 59, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72" [val,idx]: [30,10], [29,11], [26,16], [23,14], [18,17]
65, 0
93, 1
94, 2
81, 3
63, 4
48, 5
53, 6
74, 7
60, 8
59, 9
30, 10
29, 11
88, 12
77, 13
23, 14
54, 15
26, 16
18, 17
37, 18
59, 19
32, 20
72, 21
FirstKClosestStars MaxHeap_FromISS for "5" in above lists [val,idx]: [30,10], [29,11], [26,16], [23,14], [18,17]
FirstKClosestStars Selection for "5" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 59, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": 18, 26, 23, 29, 30
FirstKClosestStars STL_Nth_Element for "5" in "65, 93, 94, 81, 63, 48, 53, 74, 60, 59, 30, 29, 88, 77, 23, 54, 26, 18, 37, 59, 32, 72": 18, 23, 26, 29, 30
*/
#endif