#ifndef RANGE_SUM_QUERY_BINARY_INDEXED_TREE_H
#define RANGE_SUM_QUERY_BINARY_INDEXED_TREE_H
#include <iostream>
#include <vector>
#include "Debug.h"
/*
https://www.hackerearth.com/practice/notes/binary-indexed-tree-or-fenwick-tree/
Leetcode: Range Sum Query - Mutable
Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]
sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.

Leetcode: Range Sum Query 2D - Mutable
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]
sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 <= row2 and col1 <= col2.

A Binary Indexed Tree BIT (Fenwick Tree) is an advanced prefixSum array that saves partial prefix sums.
To query a particular prefixSum[idx] from BIT is to 
	accumulate BIT[idx+1], BIT[prevIdx - IsolateRightMostSetBit(prevIdx)], ..., BIT[prev powOf2 of (idx+1)].
	O(logN) time.
To update a particular value v[idx]+idff in BIT is to
	update BIT[idx+1]+diff, BIT[prevIdx + IsolateRightMostSetBit(prevIdx)]+diff, ..., BIT[next powOf2 of (idx+1)]+diff, BIT[next powOf2 of prevIdx]+diff, ....
	O(logN) time.

Take an array v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16} for example:

Index:	   0, 1, 2,  3, 4,  5, 6,  7, 8,  9, 10, 11, 12, 13, 14,  15
Array:	   1, 2, 3,  4, 5,  6, 7,  8, 9, 10, 11, 12, 13, 14, 15,  16
		   1     3      5      7      9      11      13      15
		   -->3         -->11         -->19          --->27
		   -------->10                ---------->42
		   ---------------------->36
		   ----------------------------------------------------->136
BIT:	0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 27, 15, 136
BITidx:	0, 1, 2, 3,  4, 5,  6, 7,  8, 9, 10, 11, 12, 13, 14, 15,  16...use this idx to compute prev/next indices by -/+ IsolateRightMostSetBit(curIdx)
dummy---^
powOf2--------^------^-------------^-------------------------------^

BIT[idx] = v[idx-1] if idx is odd
BIT[idx] = v[0]+...+v[idx-1] if idx is power of 2

BIT[0] = dummy (useless)
BIT[1] = v[0]
BIT[2] = v[0]+v[1]
BIT[3] = v[2]
BIT[4] = v[0]+...+v[3]
BIT[5] = v[4]
BIT[6] = v[4]+v[5]
BIT[7] = v[6]
BIT[8] = v[0]+v[1]+...+v[7]
BIT[9] = v[8]
BIT[10] = v[8]+v[9]
BIT[11] = v[10]
BIT[12] = v[8]+...+v[11]
BIT[13] = v[12]
BIT[14] = v[12]+v[13]
BIT[15] = v[14]
BIT[16] = v[0]+v[1]+...+v[15]

To compute prefixSum from BIT array, O(logN) time:
v[0]+...+v[10] = prefixSum[10] = BIT[11] + BIT[10] + BIT[8] = (v[10]) + (v[9]+v[8]) + (v[7]+...+v[0])
v[0]+...+v[5] = prefixSum[5] = BIT[6] + BIT[4] = (v[5]+v[4]) + (v[3]+...+v[0])
v[0]+...+v[7] = prefixSum[7] = BIT[8] = (v[7]+...+v[0])

=> BIT[11] + BIT[10] + BIT[8] = BIT[11] + BIT[11-IsolateRightMostSetBit(11)=10] + BIT[10-IsolateRightMostSetBit(10)=8]
   1011      1010      1000
   BIT[6] + BIT[4] = BIT[6] + BIT[6-IsolateRightMostSetBit(6)=4]
   0110     0100
   BIT[8] = BIT[8] + BIT[8-IsolateRightMostSetBit(8)=0]
   1000

=> prefixSum[idx] = 
	BIT[idx+1] + BIT[(idx+1)-IsolateRightMostSetBit(idx+1)] + ... + BIT[prev powOf2 of (idx+1), which is an idx w/ only 1 set bit]

To update a value in BIT array, O(logN) time:
v[8]+diff = prefixSum[8]+diff, ..., prefixSum[15]+diff
= BIT[9]+diff, BIT[10]+diff, BIT[12]+diff, BIT[16]+diff
  1001         1010          1100          10000

v[4]+diff = prefixSum[4]+diff, ..., prefixSum[15]+diff
= BIT[5]+diff, BIT[6]+diff, BIT[8]+diff, BIT[16]+diff
  0101         0110         1000         10000

=> BIT[idx+1]+diff, BIT[(idx+1)+IsolateRightMostSetBit(idx+1)]+diff, ..., BIT[next powOf2 of (idx+1), which is an idx w/ only 1 set bit]+diff, BIT[next powOf2 of prev idx]+diff, ...

Note: IsolateRightMostSetBit(idx) = idx&(-idx)

When to use Binary Indexed Tree:
The operation must be associative, i.e., f(f(a,b),c)=f(a,f(b,c)), this is true even for segment tree
The operation must have an inverse:
1) addition has inverse subtraction
2) multiplication has inverse division
3) gcd has no inverse, so we can't use BIT to calculate range gcd's
4) sum of matrices has inverse
5) product of matrices would have inverse if it is given that matrices are degenerate,
i.e., determinant of any matrix is not equal to 0

Applications:
Binary indexed tree can also be used to count inversions in an array in O(NlogN) time.
*/
class RangeSumQueryBinaryIndexedTree
{
	std::vector<int> bit;
	int N;
public:
	RangeSumQueryBinaryIndexedTree(const std::vector<int> & v)//O(NlogN) time
	{
		if (v.empty()) return;
		N = v.size();
		bit.resize(N + 1, 0);//bit[0] is dummy. (binary index must be starting from 1 to N to compute its next jumped index by +/- rightmost isolated bit's value.)
		for (int i = 0; i < N; ++i)
			update(i, v[i]);

		std::cout << Debug::ToStr1D<int>()(v) << std::endl;
		std::cout << "RangeSumQueryBinaryIndexedTree BIT for the above array: " << std::endl;
		std::cout << Debug::ToStr1D<int>()(bit) << std::endl;
	}
	~RangeSumQueryBinaryIndexedTree() {}
	void update(int idx, int val)//O(logN) time
	{
		int diff = val - sumRegion(idx, idx - 1);

		for (int i = idx + 1; i <= N; i += i&(-i))//BIT's index = array index + 1.
			bit[i] += diff;

		std::cout << "RangeSumQueryBinaryIndexedTree Update \"" << idx << "\" with \"" << val << "\":" << std::endl;
		std::cout << Debug::ToStr1D<int>()(bit) << std::endl;
	}
	int sumRegion(int idx1, int idx2)//O(logN) time
	{
		int res = prefixSum(idx2) - (idx1 == 0 ? 0 : prefixSum(idx1 - 1));

		std::cout << "RangeSumQueryBinaryIndexedTree Query \"[" << idx1 << ", " << idx2 << "]\": " << res << std::endl;
		return res;
	}
private:
	int prefixSum(int idx)//O(logN) time
	{
		int res = 0;
		for (int i = idx + 1; i > 0; i -= i&(-i))
			res += bit[i];
		return res;
	}
};

class RangeSumQueryBinaryIndexedTree2D
{
	std::vector<std::vector<int>> bit;
	int N;
	int M;
public:
	RangeSumQueryBinaryIndexedTree2D(const std::vector<std::vector<int>> & matrix)//O(N * M * logN * logM) time
	{
		if (matrix.empty() || matrix[0].empty()) return;
		N = matrix.size();
		M = matrix[0].size();
		bit.resize(N + 1, std::vector<int>(M + 1, 0));//bit[0][] and bit[][0] are all dummies. (binary index must be starting from 1 to N/M to compute its next jumped index by +/- rightmost isolated bit's value.)
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				update(i, j, matrix[i][j]);
			}
		}

		Debug::Print2D<int>()(matrix, false);
		std::cout << "RangeSumQueryBinaryIndexedTree2D BIT for above matrix:" << std::endl;
		Debug::Print2D<int>()(bit, false);
	}
	~RangeSumQueryBinaryIndexedTree2D() {}

	void update(int row, int col, int val)//O(logN * logM) time
	{
		int diff = val - sumRegion(row, col, row, col);

		for (int i = row + 1; i <= N; i += i&(-i))
			for (int j = col + 1; j <= M; j += j&(-j))
				bit[i][j] += diff;

		std::cout << "RangeSumQueryBinaryIndexedTree2D Update \"(" << row << ", " << col << ")\" with \"" << val << "\":" << std::endl;
		Debug::Print2D<int>()(bit, false);
	}

	int sumRegion(int row1, int col1, int row2, int col2)//O(logN * logM) time
	{
		int res = prefixSum(row2, col2)
			- (row1 == 0 ? 0 : prefixSum(row1 - 1, col2))
			- (col1 == 0 ? 0 : prefixSum(row2, col1 - 1))
			+ (row1 == 0 || col1 == 0 ? 0 : prefixSum(row1 - 1, col1 - 1));

		std::cout << "RangeSumQueryBinaryIndexedTree2D Query \"(" << row1 << ", " << col1 << "), (" << row2 << ", " << col2 << ")\": " << res << std::endl;
		return res;
	}
private:
	int prefixSum(int bRow, int bCol)//O(logN * logM) time
	{
		int res = 0;
		for (int i = bRow + 1; i > 0; i -= i&(-i))
			for (int j = bCol + 1; j > 0; j -= j&(-j))
				res += bit[i][j];
		return res;
	}
};
/*
RangeSumQueryBinaryIndexedTree Query "[0, -1]": 0
RangeSumQueryBinaryIndexedTree Update "0" with "1":
0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1
RangeSumQueryBinaryIndexedTree Query "[1, 0]": 0
RangeSumQueryBinaryIndexedTree Update "1" with "2":
0, 1, 3, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3
RangeSumQueryBinaryIndexedTree Query "[2, 1]": 0
RangeSumQueryBinaryIndexedTree Update "2" with "3":
0, 1, 3, 3, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6
RangeSumQueryBinaryIndexedTree Query "[3, 2]": 0
RangeSumQueryBinaryIndexedTree Update "3" with "4":
0, 1, 3, 3, 10, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10
RangeSumQueryBinaryIndexedTree Query "[4, 3]": 0
RangeSumQueryBinaryIndexedTree Update "4" with "5":
0, 1, 3, 3, 10, 5, 5, 0, 15, 0, 0, 0, 0, 0, 0, 0, 15
RangeSumQueryBinaryIndexedTree Query "[5, 4]": 0
RangeSumQueryBinaryIndexedTree Update "5" with "6":
0, 1, 3, 3, 10, 5, 11, 0, 21, 0, 0, 0, 0, 0, 0, 0, 21
RangeSumQueryBinaryIndexedTree Query "[6, 5]": 0
RangeSumQueryBinaryIndexedTree Update "6" with "7":
0, 1, 3, 3, 10, 5, 11, 7, 28, 0, 0, 0, 0, 0, 0, 0, 28
RangeSumQueryBinaryIndexedTree Query "[7, 6]": 0
RangeSumQueryBinaryIndexedTree Update "7" with "8":
0, 1, 3, 3, 10, 5, 11, 7, 36, 0, 0, 0, 0, 0, 0, 0, 36
RangeSumQueryBinaryIndexedTree Query "[8, 7]": 0
RangeSumQueryBinaryIndexedTree Update "8" with "9":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 9, 0, 9, 0, 0, 0, 45
RangeSumQueryBinaryIndexedTree Query "[9, 8]": 0
RangeSumQueryBinaryIndexedTree Update "9" with "10":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 0, 19, 0, 0, 0, 55
RangeSumQueryBinaryIndexedTree Query "[10, 9]": 0
RangeSumQueryBinaryIndexedTree Update "10" with "11":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 30, 0, 0, 0, 66
RangeSumQueryBinaryIndexedTree Query "[11, 10]": 0
RangeSumQueryBinaryIndexedTree Update "11" with "12":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 0, 0, 0, 78
RangeSumQueryBinaryIndexedTree Query "[12, 11]": 0
RangeSumQueryBinaryIndexedTree Update "12" with "13":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 13, 0, 91
RangeSumQueryBinaryIndexedTree Query "[13, 12]": 0
RangeSumQueryBinaryIndexedTree Update "13" with "14":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 27, 0, 105
RangeSumQueryBinaryIndexedTree Query "[14, 13]": 0
RangeSumQueryBinaryIndexedTree Update "14" with "15":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 27, 15, 120
RangeSumQueryBinaryIndexedTree Query "[15, 14]": 0
RangeSumQueryBinaryIndexedTree Update "15" with "16":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 27, 15, 136
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
RangeSumQueryBinaryIndexedTree BIT for the above array:
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13, 27, 15, 136
RangeSumQueryBinaryIndexedTree Query "[0, 11]": 78
RangeSumQueryBinaryIndexedTree Query "[0, 5]": 21
RangeSumQueryBinaryIndexedTree Query "[0, 7]": 36
RangeSumQueryBinaryIndexedTree Query "[12, 11]": 0
RangeSumQueryBinaryIndexedTree Update "12" with "15":
0, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 28, 42, 15, 151
RangeSumQueryBinaryIndexedTree Query "[0, 13]": 120
RangeSumQueryBinaryIndexedTree2D Query "(0, 0), (0, 0)": 0
RangeSumQueryBinaryIndexedTree2D Update "(0, 0)" with "3":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 0, 3, 0
Row#2	= 0, 3, 3, 0, 3, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 3, 0, 3, 0
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(0, 1), (0, 1)": 0
RangeSumQueryBinaryIndexedTree2D Update "(0, 1)" with "0":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 0, 3, 0
Row#2	= 0, 3, 3, 0, 3, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 3, 0, 3, 0
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(0, 2), (0, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(0, 2)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 4, 0
Row#2	= 0, 3, 3, 1, 4, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 3, 1, 4, 0
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(0, 3), (0, 3)": 0
RangeSumQueryBinaryIndexedTree2D Update "(0, 3)" with "4":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 0
Row#2	= 0, 3, 3, 1, 8, 0
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 3, 1, 8, 0
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(0, 4), (0, 4)": 0
RangeSumQueryBinaryIndexedTree2D Update "(0, 4)" with "2":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 3, 3, 1, 8, 2
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 3, 3, 1, 8, 2
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(1, 0), (1, 0)": 0
RangeSumQueryBinaryIndexedTree2D Update "(1, 0)" with "5":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 8, 1, 13, 2
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 8, 8, 1, 13, 2
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(1, 1), (1, 1)": 0
RangeSumQueryBinaryIndexedTree2D Update "(1, 1)" with "6":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 1, 19, 2
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 8, 14, 1, 19, 2
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(1, 2), (1, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(1, 2)" with "3":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 22, 2
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 8, 14, 4, 22, 2
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(1, 3), (1, 3)": 0
RangeSumQueryBinaryIndexedTree2D Update "(1, 3)" with "2":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 2
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 8, 14, 4, 24, 2
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(1, 4), (1, 4)": 0
RangeSumQueryBinaryIndexedTree2D Update "(1, 4)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 0, 0, 0, 0, 0
Row#4	= 0, 8, 14, 4, 24, 3
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(2, 0), (2, 0)": 0
RangeSumQueryBinaryIndexedTree2D Update "(2, 0)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 1, 0, 1, 0
Row#4	= 0, 9, 15, 4, 25, 3
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(2, 1), (2, 1)": 0
RangeSumQueryBinaryIndexedTree2D Update "(2, 1)" with "2":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 3, 0
Row#4	= 0, 9, 17, 4, 27, 3
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(2, 2), (2, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(2, 2)" with "0":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 3, 0
Row#4	= 0, 9, 17, 4, 27, 3
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(2, 3), (2, 3)": 0
RangeSumQueryBinaryIndexedTree2D Update "(2, 3)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 0
Row#4	= 0, 9, 17, 4, 28, 3
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(2, 4), (2, 4)": 0
RangeSumQueryBinaryIndexedTree2D Update "(2, 4)" with "5":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 9, 17, 4, 28, 8
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(3, 0), (3, 0)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 0)" with "4":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 21, 4, 32, 8
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(3, 1), (3, 1)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 1)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 33, 8
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(3, 2), (3, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 2)" with "0":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 33, 8
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(3, 3), (3, 3)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 3)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 8
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(3, 4), (3, 4)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 4)" with "7":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 0, 0, 0, 0, 0

RangeSumQueryBinaryIndexedTree2D Query "(4, 0), (4, 0)": 0
RangeSumQueryBinaryIndexedTree2D Update "(4, 0)" with "1":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 0, 1, 0

RangeSumQueryBinaryIndexedTree2D Query "(4, 1), (4, 1)": 0
RangeSumQueryBinaryIndexedTree2D Update "(4, 1)" with "0":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 0, 1, 0

RangeSumQueryBinaryIndexedTree2D Query "(4, 2), (4, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(4, 2)" with "3":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 3, 4, 0

RangeSumQueryBinaryIndexedTree2D Query "(4, 3), (4, 3)": 0
RangeSumQueryBinaryIndexedTree2D Update "(4, 3)" with "0":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 3, 4, 0

RangeSumQueryBinaryIndexedTree2D Query "(4, 4), (4, 4)": 0
RangeSumQueryBinaryIndexedTree2D Update "(4, 4)" with "5":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 3, 4, 5

[rY][cX]
Row#0	= 3, 0, 1, 4, 2
Row#1	= 5, 6, 3, 2, 1
Row#2	= 1, 2, 0, 1, 5
Row#3	= 4, 1, 0, 1, 7
Row#4	= 1, 0, 3, 0, 5

RangeSumQueryBinaryIndexedTree2D BIT for above matrix:
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 4, 34, 15
Row#5	= 0, 1, 1, 3, 4, 5

RangeSumQueryBinaryIndexedTree2D Query "(2, 1), (4, 3)": 8
RangeSumQueryBinaryIndexedTree2D Query "(3, 2), (3, 2)": 0
RangeSumQueryBinaryIndexedTree2D Update "(3, 2)" with "2":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 4, 5
Row#4	= 0, 13, 22, 6, 36, 15
Row#5	= 0, 1, 1, 3, 4, 5

RangeSumQueryBinaryIndexedTree2D Query "(2, 1), (4, 3)": 10
RangeSumQueryBinaryIndexedTree2D Query "(2, 3), (2, 3)": 1
RangeSumQueryBinaryIndexedTree2D Update "(2, 3)" with "7":
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 3, 3, 1, 8, 2
Row#2	= 0, 8, 14, 4, 24, 3
Row#3	= 0, 1, 3, 0, 10, 5
Row#4	= 0, 13, 22, 6, 42, 15
Row#5	= 0, 1, 1, 3, 4, 5

RangeSumQueryBinaryIndexedTree2D Query "(2, 1), (4, 3)": 16
*/
#endif
