#ifndef RANGE_MIN_QUERY_SPARSE_TABLE_H
#define RANGE_MIN_QUERY_SPARSE_TABLE_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include "Debug.h"
/*
http://www.topcoder.com/tc?d1=tutorials&d2=lowestCommonAncestor&module=Static

1 << i means 2^i
*/
class RangeMinQuerySparseTable
{
public:
	RangeMinQuerySparseTable(){}
	~RangeMinQuerySparseTable(){}

	//O(nlogn) time
	std::vector<std::vector<int> > Construct(const std::vector<int> & A)
	{
		int N = A.size();
		int treeHeight = (int)floor(log2(N)) + 1;
		std::vector<std::vector<int> > sparseTable(N, std::vector<int>(treeHeight, 0));//init with 0
		//sparseTable[rangeStart][rangeStart+2^(rangeEnd-rangeStart+1)-1]: range min
		//rowY: range start index
		//colX: 2^(size of range) = 2^(rangeEnd - rangeStart + 1)

		//the range min of each rangeStart with 2^0=1 element is itself
		//init the 1st col
		for (int i = 0; i < N; ++i)
			sparseTable[i][0] = A[i];

		for (int j = 1; 1 << j <= N; ++j)//size of range (colX): 1,2,3,...,logN (check also LowestCommonAncestorDP2D.h)
		{
			for (int i = 0; i + (1 << j) - 1 < N; ++i)//for each starting index in each range segment
			{
				/*
				compare the min of 2 ranges that have overlaps:
				the 1st range: start index is i, length is 2^(j-1) .... current left element
				the 2nd range: start index is i+2^(j-1), length is 2^(j-1) .... the left element of rowY equal to i+2^(j-1)
				*/
				if (sparseTable[i][j - 1] < sparseTable[i + (1 << (j - 1))][j - 1])
					sparseTable[i][j] = sparseTable[i][j - 1];
				else
					sparseTable[i][j] = sparseTable[i + (1 << (j - 1))][j - 1];
			}
		}
		std::cout << "RangeMinQuerySparseTable Construct for \"" << Debug::ToStr1D<int>()(A) << "\": " << std::endl;
		std::cout << "SparseTable[rowY][colX]: minimum in the range A[rowY]~A[rowY+2^colX-1]" << std::endl;
		Debug::Print2D<int>()(sparseTable, false);
		return sparseTable;
	}

	//O(1) time
	int QueryRange(const std::vector<std::vector<int> > & sparseTable, int targetStart, int targetEnd)
	{
		int N = sparseTable.size();
		if (targetStart < 0 || targetEnd > N - 1 || targetStart > targetEnd)
			throw std::runtime_error("Invalid Input");
		/*
		lookup the table, compare 2 elements and get the min of them:
		1. find the colX that represents the length of the queried range
		2. find the starting index of the 1st range and starting index of the 2nd range
		3. lookup the min values of the 2 ranges with diff starting index but same length, and compare the 2 elements
		*/
		int K = (int)log2(targetEnd - targetStart + 1);
		int res = 0;
		if (sparseTable[targetStart][K] <= sparseTable[targetEnd - (1 << K) + 1][K])
			res = sparseTable[targetStart][K];//first range starting index with queried range length
		else
			res = sparseTable[targetEnd - (1 << K) + 1][K];//second range starting index with queried range length

		std::cout << "min of [" << targetStart << "][" << K << "] and [" << targetEnd - (1 << K) + 1 << "][" << K << "]" << std::endl;
		std::cout << "RangeMinQuerySparseTable QueryRange for \"" << targetStart << "," << targetEnd << "\": " << res << std::endl;
		return res;
	}
};
/*
RangeMinQuerySparseTable Construct for "31, 41, 88, 26, 53, 77, 66, 47, 17":
SparseTable[rowY][colX]: minimum in the range A[rowY]~A[rowY+2^colX-1]
[rY][cX]
Row#0	= 31, 31, 26, 26
Row#1	= 41, 41, 26, 17
Row#2	= 88, 26, 26, 0
Row#3	= 26, 26, 26, 0
Row#4	= 53, 53, 47, 0
Row#5	= 77, 66, 17, 0
Row#6	= 66, 47, 0, 0
Row#7	= 47, 17, 0, 0
Row#8	= 17, 0, 0, 0

min of [1][1] and [2][1]
RangeMinQuerySparseTable QueryRange for "1,3": 26
min of [0][3] and [1][3]
RangeMinQuerySparseTable QueryRange for "0,8": 17
min of [4][2] and [5][2]
RangeMinQuerySparseTable QueryRange for "4,8": 17
min of [4][2] and [4][2]
RangeMinQuerySparseTable QueryRange for "4,7": 47
min of [4][1] and [5][1]
RangeMinQuerySparseTable QueryRange for "4,6": 53
min of [5][1] and [6][1]
RangeMinQuerySparseTable QueryRange for "5,7": 47
min of [5][2] and [5][2]
RangeMinQuerySparseTable QueryRange for "5,8": 17
min of [2][2] and [3][2]
RangeMinQuerySparseTable QueryRange for "2,6": 26
min of [2][2] and [4][2]
RangeMinQuerySparseTable QueryRange for "2,7": 26
min of [2][2] and [5][2]
RangeMinQuerySparseTable QueryRange for "2,8": 17
min of [3][2] and [3][2]
RangeMinQuerySparseTable QueryRange for "3,6": 26
min of [3][2] and [4][2]
RangeMinQuerySparseTable QueryRange for "3,7": 26
min of [3][2] and [5][2]
RangeMinQuerySparseTable QueryRange for "3,8": 17
*/
#endif