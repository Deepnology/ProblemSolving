#ifndef MATCHING_NUTS_BOLTS_PROBLEM_H
#define MATCHING_NUTS_BOLTS_PROBLEM_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
http://www.careercup.com/question?id=9960240
http://kartikkukreja.wordpress.com/2013/10/29/matching-nuts-and-bolts-problem/
Given n nuts(pens) and n bolts(caps) in unsorted order.
Sort them.
You can only compare nuts(pens) with bolts(caps), or bolts(caps) with nuts(pens).

O(nlogn) time
*/
class MatchingNutsBoltsProblem
{
public:
	MatchingNutsBoltsProblem(){}
	~MatchingNutsBoltsProblem(){}

	void RandomizedQuickSort(std::vector<int> & nuts, std::vector<int> & bolts)
	{
		std::string nutsBefore = Debug::ToStr1D<int>()(nuts);
		std::string boltsBefore = Debug::ToStr1D<int>()(bolts);

		int N = nuts.size();
		this->recur(nuts, bolts, 0, N - 1);

		std::cout << "MatchingNutsBoltsProblem for Nuts=\"" << nutsBefore << "\", Bolts=\"" << boltsBefore << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(nuts) << std::endl;
		std::cout << Debug::ToStr1D<int>()(bolts) << std::endl;
	}
private:
	void recur(std::vector<int> & nuts, std::vector<int> & bolts, int left, int right)
	{
		if (left >= right)
			return;
		int N = nuts.size();
		int mid = (left + right) / 2;/*mid is supposed to be random btw left and right*/
		int nutVal = nuts[mid];
		int pivot = this->partition(bolts, left, right, nutVal);/*use nutVal to partition bolts*/
		int boltVal = bolts[pivot];
		this->partition(nuts, left, right, boltVal);/*use boltVal to partition nuts*/
		this->recur(nuts, bolts, left, pivot - 1);
		this->recur(nuts, bolts, pivot + 1, right);
	}

	/*return an index that points to the first element, which is not necessarily the pivotVal, of the second group of elements*/
	int partition(std::vector<int> & A, int first, int last, int pivotVal)
	{
		int i = first;
		int j = last;
		while (i <= j)
		{
			if (A[i] < pivotVal)
				++i;
			else if (!(A[j] < pivotVal))
				--j;
			else
				std::swap(A[i++], A[j--]);
		}
		/*
		now i > j and i points to the first element of the second group
		make sure the first element of the second group A[i] is also the smallest element of the second group
		*/
		for (int k = i; k <= last; ++k)
		{
			if (!(A[i] < A[k]))
				std::swap(A[i], A[k]);
		}
		return i;
	}
};
/*
MatchingNutsBoltsProblem for Nuts="3, 7, 2, 5, 6, 9, 1, 4, 8", Bolts="7, 3, 1, 4, 8, 5, 9, 2, 6":
1, 2, 3, 4, 5, 6, 7, 8, 9
1, 2, 3, 4, 5, 6, 7, 8, 9
MatchingNutsBoltsProblem for Nuts="5, 4, 2, 3, 1, 8, 6, 7, 9", Bolts="1, 9, 8, 5, 7, 4, 3, 6, 2":
1, 2, 3, 4, 5, 6, 7, 8, 9
1, 2, 3, 4, 5, 6, 7, 8, 9
MatchingNutsBoltsProblem for Nuts="9, 8, 3, 1, 7, 4, 2, 6, 5", Bolts="9, 1, 4, 8, 3, 2, 5, 7, 6":
1, 2, 3, 4, 5, 6, 7, 8, 9
1, 2, 3, 4, 5, 6, 7, 8, 9
*/
#endif