#ifndef APPLY_PERMUTATION_ORDER_H
#define APPLY_PERMUTATION_ORDER_H
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Debug.h"
/*
Elements of programming interview, Array: Permute the elements of an array

Given an array of integers with arbitrary order.
Given another array of integers ranging from 1 to N in arbitrary order, which is a permutation of 1,2,...,N.
Move each element in the first array to its target index specified in the second array.
v[Idx[i]-1] <- v[i]

MarkVisit: O(n) time, O(n) space
InPlace: O(n^2) time, O(1) space

See also SortByPermutationOrder.h
*/
class ApplyPermutationOrder
{
public:
	ApplyPermutationOrder(){}
	~ApplyPermutationOrder(){}

	void MarkVisit(std::vector<int> & v, std::vector<int> & Idx)
	{
		std::string before1 = Debug::ToStr1D<int>()(v);
		std::string before2 = Debug::ToStr1D<int>()(Idx);
		int N = v.size();

		for (int i = 0; i < N; ++i)
		{
			if (Idx[i] > 0)//if not visited
			{
				int cur = i;
				int curVal = v[i];

				do
				{
					int tgt = Idx[cur] - 1;//save target index
					int tgtVal = v[tgt];//save target value

					v[tgt] = curVal;//move current number to target index
					Idx[cur] = -Idx[cur];//mark current index negative as visited, because curVal associated with current index has been moved to target

					cur = tgt;
					curVal = tgtVal;

				} while (cur != i);//stop when the target index is going back to i
			}
		}

		std::cout << "ApplyPermutationOrder MarkVisit for \"" << before1 << "\" with order \"" << before2 << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
	}

	void InPlace(std::vector<int> & v, const std::vector<int> & Idx)
	{
		std::string before1 = Debug::ToStr1D<int>()(v);
		std::string before2 = Debug::ToStr1D<int>()(Idx);
		int N = v.size();

		for (int i = 0; i < N; ++i)
		{
			bool isMin = true;
			int nxt = Idx[i] - 1;
			while (nxt != i)
			{
				if (nxt < i)
				{
					isMin = false;
					break;
				}
				nxt = Idx[nxt] - 1;
			}

			if (isMin)//if current index is the leftmost index of DFS, we perform DFS for the remaining elements until it goes back to i
			{
				int cur = i;
				int curVal = v[i];

				do
				{
					int tgt = Idx[cur] - 1;//save target index
					int tgtVal = v[tgt];//save target value

					v[tgt] = curVal;//move current number to target index

					cur = tgt;
					curVal = tgtVal;

				} while (cur != i);//stop when the target index is going back to i
			}
		}

		std::cout << "ApplyPermutationOrder InPlace for \"" << before1 << "\" with order \"" << before2 << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
ApplyPermutationOrder InPlace for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10" with order "10, 1, 3, 2, 6, 5, 8, 9, 4, 7":
2, 4, 3, 9, 6, 5, 10, 7, 8, 1
ApplyPermutationOrder MarkVisit for "1, 2, 3, 4, 5, 6, 7, 8, 9, 10" with order "10, 1, 3, 2, 6, 5, 8, 9, 4, 7":
2, 4, 3, 9, 6, 5, 10, 7, 8, 1
ApplyPermutationOrder MarkVisit for "10, 20, 30, 40" with order "3, 1, 2, 4":
20, 30, 10, 40
ApplyPermutationOrder InPlace for "10, 20, 30, 40" with order "3, 1, 2, 4":
20, 30, 10, 40
ApplyPermutationOrder MarkVisit for "17, 5, 1, 9" with order "3, 2, 4, 1":
9, 5, 17, 1
ApplyPermutationOrder InPlace for "17, 5, 1, 9" with order "3, 2, 4, 1":
9, 5, 17, 1
ApplyPermutationOrder MarkVisit for "5, 12, 14, 27, 3, 2, 13, 17, 7, 21" with order "3, 6, 2, 9, 7, 1, 4, 8, 5, 10":
2, 14, 5, 13, 7, 12, 3, 17, 27, 21
ApplyPermutationOrder InPlace for "5, 12, 14, 27, 3, 2, 13, 17, 7, 21" with order "3, 6, 2, 9, 7, 1, 4, 8, 5, 10":
2, 14, 5, 13, 7, 12, 3, 17, 27, 21
*/
#endif