#ifndef SPARSE_MATRIX_MULTIPLICATION_H
#define SPARSE_MATRIX_MULTIPLICATION_H
#include "Debug.h"
/*
Leetcode: Sparse Matrix Multiplication
Given two sparse matrices A and B, return the result of AB.
You may assume that A's column number is equal to B's row number.
Example:
A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |

Similar problem: Sparse Array Dot Product
Given two sparse arrays contain many 0s.
Return the dot product of the two arrays.
O(N) time
*/
class SparseMatrixMultiplication
{
public:
	SparseMatrixMultiplication() {}
	~SparseMatrixMultiplication() {}

	std::vector<std::vector<int>> Normal(const std::vector<std::vector<int>> & A, const std::vector<std::vector<int>> & B)//Time Limit Exceeded
	{
		int N = A.size();
		int M = A[0].size();
		int L = B[0].size();

		std::vector<std::vector<int>> res(N, std::vector<int>(L, 0));//A's row size * B's col size
		for (int i = 0; i < N; ++i)//iterate A's row
		{
			for (int j = 0; j < M; ++j)//iterate A's col && B's row
			{
				for (int k = 0; k < L; ++k)//iterate B's col
					res[i][k] += A[i][j] * B[j][k];
			}
		}

		Debug::Print2D<int>()(A, false);
		Debug::Print2D<int>()(B, false);
		std::cout << "SparseMatrixMultiplication Normal for the above 2 Matrix:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

	std::vector<std::vector<int>> Naive(const std::vector<std::vector<int>> & A, const std::vector<std::vector<int>> & B)//passed OJ
	{
		int N = A.size();
		int M = A[0].size();
		int L = B[0].size();

		std::vector<std::vector<int>> res(N, std::vector<int>(L, 0));//A's row size * B's col size
		for (int i = 0; i < N; ++i)//iterate A's row
		{
			for (int j = 0; j < M; ++j)//iterate A's col && B's row
			{
				if (A[i][j] != 0)
					for (int k = 0; k < L; ++k)//iterate B's col
						if (B[j][k] != 0)
							res[i][k] += A[i][j] * B[j][k];
			}
		}

		Debug::Print2D<int>()(A, false);
		Debug::Print2D<int>()(B, false);
		std::cout << "SparseMatrixMultiplication Naive for the above 2 Matrix:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}

	std::vector<std::vector<int>> SaveBinHashMap(const std::vector<std::vector<int>> & A, const std::vector<std::vector<int>> & B)//passed OJ
	{
		int N = A.size();
		int M = A[0].size();
		int L = B[0].size();
		int NN = B.size();
		std::unordered_map<int, std::unordered_map<int, int>> BB;
		for (int i = 0; i < NN; ++i)
		{
			for (int j = 0; j < L; ++j)
				if (B[i][j] != 0)
					BB[i].insert({ j,B[i][j] });
		}
		std::vector<std::vector<int>> res(N, std::vector<int>(L, 0));//A's row size * B's col size
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (A[i][j] != 0 && BB.count(j))
					for (auto & p : BB[j])
						res[i][p.first] += A[i][j] * p.second;
			}
		}

		Debug::Print2D<int>()(A, false);
		Debug::Print2D<int>()(B, false);
		std::cout << "SparseMatrixMultiplication SaveBinHashMap for the above 2 Matrix:" << std::endl;
		Debug::Print2D<int>()(res, false);
		return res;
	}


	//Sparse Array Dot Product
	//naive: [a1,a2,a3] dot [b1,b2,b3] = a1*b1+a2*b2+a3*b3
	//hash table: save (idx,non-0-Val) pairs in two hash table
	int SparseArrayDotProduct_ModifiedMergeTwoSortedArrays(std::vector<int> & A, std::vector<int> & B)
	{
		std::vector<std::pair<int, int>> a;
		std::vector<std::pair<int, int>> b;
		int N = A.size();
		for (int i = 0; i < N; ++i)
			if (A[i] != 0)
				a.push_back({ i, A[i] });
		int M = B.size();
		for (int i = 0; i < M; ++i)
			if (B[i] != 0)
				b.push_back({ i, B[i] });
		N = a.size();
		M = b.size();
		int i = 0;
		int j = 0;
		int res = 0;
		while (i < N && j < M)
		{
			if (a[i].first < b[j].first)
				++i;
			else if (a[i].first > b[j].first)
				++j;
			else//a[i].first == b[i].first (intersection)
			{
				res += a[i].second * b[j].second;
				++i;
				++j;
			}
		}

		std::cout << "SparseArrayDotProduct ModifiedMergeTwoSortedArrays for \"" << Debug::ToStr1D<int>()(A) << "\", \"" << Debug::ToStr1D<int>()(B) << "\": " << res << std::endl;
		return res;
	}
};
/*
[rY][cX]
Row#0	= 1, 0, 0
Row#1	= -1, 0, 3

[rY][cX]
Row#0	= 7, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 1

SparseMatrixMultiplication Normal for the above 2 Matrix:
[rY][cX]
Row#0	= 7, 0, 0
Row#1	= -7, 0, 3

[rY][cX]
Row#0	= 1, 0, 0
Row#1	= -1, 0, 3

[rY][cX]
Row#0	= 7, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 1

SparseMatrixMultiplication Naive for the above 2 Matrix:
[rY][cX]
Row#0	= 7, 0, 0
Row#1	= -7, 0, 3

[rY][cX]
Row#0	= 1, 0, 0
Row#1	= -1, 0, 3

[rY][cX]
Row#0	= 7, 0, 0
Row#1	= 0, 0, 0
Row#2	= 0, 0, 1

SparseMatrixMultiplication SaveBinHashMap for the above 2 Matrix:
[rY][cX]
Row#0	= 7, 0, 0
Row#1	= -7, 0, 3

SparseArrayDotProduct ModifiedMergeTwoSortedArrays for "1, 2, 0, 0, 5, 0, 0, 0, 4, 0, 0, 3", "1, 0, 0, 2, 0, 0, 0, 0, 4, 0, 2, 3": 26
*/
#endif
