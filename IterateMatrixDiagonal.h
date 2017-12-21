/*MEMO*/
#ifndef ITERATE_MATRIX_DIAGONAL_H
#define ITERATE_MATRIX_DIAGONAL_H
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Diagonal Traverse
Google
http://www.careercup.com/question?id=5661939564806144
Give a N*N matrix, print it out diagonally.
Follow up, if it is a M*N matrix, how to print it out.
Example:
1 2 3
4 5 6
7 8 9
print:
1
2 4
3 5 7
6 8
9

let i be row number (0 to N-1), and j be col number (O to N-1)

diagonal 1 has i+j =0
diagonal 2 has i+j =1
...
So define D = i+j

Loop with D from 0 to 2*(N-1)

Now if D = i+j then j=D-i
So we have reduced the problem to two variables: D and i (two loops)
*/
class IterateMatrixDiagonal
{
public:
	IterateMatrixDiagonal(){}
	~IterateMatrixDiagonal(){}

	void Solve_NxN(const std::vector<std::vector<int> > & m)
	{
		int N = m.size();
		std::vector<int> res;
		for (int D = 0; D <= 2 * (N - 1); ++D)
		{
			for (int row = 0; row <= D; ++row)
			{
				if (row < N && (D - row) < N)
					res.push_back(m[row][D - row]);
			}
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "IterateMatrixDiagonal NxN: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
	
	void Solve_NxM(const std::vector<std::vector<int> > & m)
	{
		int N = m.size();//num of rows
		int M = m[0].size();//num of cols
		std::vector<int> res;
		for (int D = 0; D <= N + M - 2; ++D)
		{
			for (int row = 0; row <= D; ++row)
			{
				if (row >= 0 && row < N && (D - row) >= 0 && (D - row) < M)
					res.push_back(m[row][D - row]);
			}
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "IterateMatrixDiagonal NxM: " << Debug::ToStr1D<int>()(res) << std::endl;
	}

	void Solve_NxM_2(const std::vector<std::vector<int> > & m)
	{
		int N = m.size();//num of rows
		int M = m[0].size();//num of cols
		std::vector<int> res;
		for (int D = 0; D <= N + M - 1; ++D)
		{
			int lower = std::max(0, D - M + 1);
			int upper = std::min(N, D + 1);
			for (int row = lower; row < upper; ++row)
				res.push_back(m[row][D - row]);
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "IterateMatrixDiagonal NxM 2: " << Debug::ToStr1D<int>()(res) << std::endl;
	}

	void ReverseDiag_NxM(const std::vector<std::vector<int> > & m)
	{
		int N = m.size();//num of rows
		int M = m[0].size();//num of cols
		std::vector<int> res;
		for (int D = 0; D <= N + M - 2; ++D)
		{
			for (int row = 0; row <= D; ++row)
			{
				if (row >= 0 && row < N && ((M - 1) - (D - row)) >= 0 && ((M - 1) - (D - row)) < M)
					res.push_back(m[row][(M - 1) - (D - row)]);
			}
		}
		Debug::Print2D<int>()(m, false);
		std::cout << "IterateMatrixDiagonal ReverseDiag_NxM: " << Debug::ToStr1D<int>()(res) << std::endl;
	}
};
/*
[rY][cX]
Row#0	= 11, 12, 13, 14
Row#1	= 21, 22, 23, 24
Row#2	= 31, 32, 33, 34
Row#3	= 41, 42, 43, 44

IterateMatrixDiagonal NxN: 11, 12, 21, 13, 22, 31, 14, 23, 32, 41, 24, 33, 42, 34, 43, 44
[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45

IterateMatrixDiagonal NxM: 11, 12, 21, 13, 22, 31, 14, 23, 32, 41, 15, 24, 33, 42, 25, 34, 43, 35, 44, 45
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16
Row#1	= 21, 22, 23, 24, 25, 26

IterateMatrixDiagonal NxM: 11, 12, 21, 13, 22, 14, 23, 15, 24, 16, 25, 26
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16

IterateMatrixDiagonal NxM: 11, 12, 13, 14, 15, 16
[rY][cX]
Row#0	= 11, 12
Row#1	= 21, 22
Row#2	= 31, 32
Row#3	= 41, 42
Row#4	= 51, 52
Row#5	= 61, 62

IterateMatrixDiagonal NxM: 11, 12, 21, 22, 31, 32, 41, 42, 51, 52, 61, 62
[rY][cX]
Row#0	= 11
Row#1	= 21
Row#2	= 31
Row#3	= 41
Row#4	= 51
Row#5	= 61

IterateMatrixDiagonal NxM: 11, 21, 31, 41, 51, 61

[rY][cX]
Row#0	= 11, 12, 13, 14, 15
Row#1	= 21, 22, 23, 24, 25
Row#2	= 31, 32, 33, 34, 35
Row#3	= 41, 42, 43, 44, 45

IterateMatrixDiagonal ReverseDiag_NxM: 15, 14, 25, 13, 24, 35, 12, 23, 34, 45, 11, 22, 33, 44, 21, 32, 43, 31, 42, 41
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16
Row#1	= 21, 22, 23, 24, 25, 26

IterateMatrixDiagonal ReverseDiag_NxM: 16, 15, 26, 14, 25, 13, 24, 12, 23, 11, 22, 21
[rY][cX]
Row#0	= 11, 12, 13, 14, 15, 16

IterateMatrixDiagonal ReverseDiag_NxM: 16, 15, 14, 13, 12, 11
[rY][cX]
Row#0	= 11, 12
Row#1	= 21, 22
Row#2	= 31, 32
Row#3	= 41, 42
Row#4	= 51, 52
Row#5	= 61, 62

IterateMatrixDiagonal ReverseDiag_NxM: 12, 11, 22, 21, 32, 31, 42, 41, 52, 51, 62, 61
[rY][cX]
Row#0	= 11
Row#1	= 21
Row#2	= 31
Row#3	= 41
Row#4	= 51
Row#5	= 61

IterateMatrixDiagonal ReverseDiag_NxM: 11, 21, 31, 41, 51, 61
*/
#endif