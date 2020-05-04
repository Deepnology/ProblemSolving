#ifndef UNION_INTERSECTION_2_SORTED_ARRAYS_H
#define UNION_INTERSECTION_2_SORTED_ARRAYS_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Intersection of Two Arrays (intersections without duplicate)
Leetcode: Intersection of Two Arrays II (intersections including all duplicates)
Leetcode: Intersection of Three Sorted Arrays
Elements of programming interview, Sorting: Compute the intersection of two sorted arrays
http://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
http://www.geeksforgeeks.org/find-common-elements-three-sorted-arrays/
Given 2 sorted arrays.
{1,3,4,5,7}
{2,3,5,6}

Union of the 2 arrays: {1,2,3,4,5,6,7}
Intersection of the 2 arrays: {3,5}

Union: O(M+N) time
Intersection: O(M+N) time
*/
class UnionIntersection2SortedArrays
{
public:
	UnionIntersection2SortedArrays(){}
	~UnionIntersection2SortedArrays(){}

	std::vector<int> Union(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();

		int i = 0;
		int j = 0;
		std::vector<int> res;
		while (i < M && j < N)
		{
			if (v1[i] < v2[j])
			{
				res.push_back(v1[i]);
				++i;
			}
			else if (v1[i] > v2[j])
			{
				res.push_back(v2[j]);
				++j;
			}
			else
			{
				res.push_back(v1[i]);
				++i;
				++j;
			}
		}
		while (i < M)
			res.push_back(v1[i++]);
		while (j < N)
			res.push_back(v2[j++]);

		std::cout << "Union2SortedArrays for \"" << Debug::ToStr1D<int>()(v1) << "\" and \"" << Debug::ToStr1D<int>()(v2) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Intersection(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();

		int i = 0;
		int j = 0;
		std::vector<int> res;
		while (i < M && j < N)
		{
			if (v1[i] < v2[j])
			{
				++i;
			}
			else if (v1[i] > v2[j])
			{
				++j;
			}
			else
			{
				res.push_back(v1[i]);
				++i;
				++j;
			}
		}

		std::cout << "Intersection2SortedArrays for \"" << Debug::ToStr1D<int>()(v1) << "\" and \"" << Debug::ToStr1D<int>()(v2) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Intersection_WoDup(const std::vector<int> & v1, const std::vector<int> & v2)
	{
		int M = v1.size();
		int N = v2.size();

		int i = 0;
		int j = 0;
		std::vector<int> res;
		while (i < M && j < N)
		{
			if (v1[i] == v2[j])
			{
				if (!res.empty() && res.back() == v1[i])//skip duplicate
				{}
				else
					res.push_back(v1[i]);
				++i;
				++j;
			}
			else if (v1[i] < v2[j])
			{
				++i;
			}
			else//(v1[i] > v2[j])
			{
				++j;
			}
		}

		std::cout << "Intersection2SortedArrays WoDup for \"" << Debug::ToStr1D<int>()(v1) << "\" and \"" << Debug::ToStr1D<int>()(v2) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Intersection3(const std::vector<int> & v1, const std::vector<int> & v2, const std::vector<int> & v3)
	{
		int M = v1.size();
		int N = v2.size();
		int S = v3.size();
		int i = 0;
		int j = 0;
		int k = 0;
		std::vector<int> res;
		while (i < M && j < N && k < S)
		{
			if (v1[i] == v2[j] && v2[j] == v3[k])
			{
				res.push_back(v1[i]);
				++i;
				++j;
				++k;
			}
			else
			{
				int minVal = std::min(v1[i], std::min(v2[j], v3[k]));
				if (v1[i] == minVal) ++i;
				if (v2[j] == minVal) ++j;
				if (v3[k] == minVal) ++k;
			}
		}

		std::cout << "Intersection3SortedArrays for \"" << Debug::ToStr1D<int>()(v1) << "\" and \"" << Debug::ToStr1D<int>()(v2) << "\" and \"" << Debug::ToStr1D<int>()(v3) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}

	std::vector<int> Intersection3_WoDup(const std::vector<int> & v1, const std::vector<int> & v2, const std::vector<int> & v3)
	{
		int M = v1.size();
		int N = v2.size();
		int S = v3.size();
		int i = 0;
		int j = 0;
		int k = 0;
		std::vector<int> res;
		while (i < M && j < N && k < S)
		{
			if (v1[i] == v2[j] && v2[j] == v3[k])
			{
				if (!res.empty() && res.back() == v1[i])//skip duplicate
				{}
				else
					res.push_back(v1[i]);
				++i;
				++j;
				++k;
			}
			else
			{
				int minVal = std::min(v1[i], std::min(v2[j], v3[k]));
				if (v1[i] == minVal) ++i;
				if (v2[j] == minVal) ++j;
				if (v3[k] == minVal) ++k;
			}
		}

		std::cout << "Intersection3SortedArrays WoDup for \"" << Debug::ToStr1D<int>()(v1) << "\" and \"" << Debug::ToStr1D<int>()(v2) << "\" and \"" << Debug::ToStr1D<int>()(v3) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
};
/*
Union2SortedArrays for "1, 3, 4, 5, 7" and "2, 3, 5, 6": 1, 2, 3, 4, 5, 6, 7
Intersection2SortedArrays for "1, 3, 4, 5, 7" and "2, 3, 5, 6": 3, 5
Intersection2SortedArrays for "1, 3, 3, 3, 3, 3, 4, 4, 5, 5, 7" and "2, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5, 5, 5, 6": 3, 3, 3, 4, 4, 5, 5
Intersection2SortedArrays WoDup for "1, 3, 3, 3, 3, 3, 4, 4, 5, 5, 7" and "2, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5, 5, 5, 6": 3, 4, 5
Intersection3SortedArrays for "1, 1, 5, 10, 20, 20, 40, 80, 80, 100" and "1, 1, 1, 6, 7, 20, 20, 80, 100" and "1, 1, 3, 4, 15, 20, 20, 30, 70, 80, 80, 80, 80, 80, 120": 1, 1, 20, 20, 80
Intersection3SortedArrays WoDup for "1, 1, 5, 10, 20, 20, 40, 80, 80, 100" and "1, 1, 1, 6, 7, 20, 20, 80, 100" and "1, 1, 3, 4, 15, 20, 20, 30, 70, 80, 80, 80, 80, 80, 120": 1, 20, 80
Intersection3SortedArrays WoDup for "0, 1, 2, 3, 3, 4, 5" and "1, 2, 2, 3, 5, 5" and "1, 1, 3, 3, 5, 6, 6": 1, 3, 5
*/
#endif