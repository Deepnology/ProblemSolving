#ifndef	YOUNG_TABLEAU_H
#define YOUNG_TABLEAU_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
http://lyle.smu.edu/~saad/courses/cse3358/ps5/problemset5sol.pdf
http://www.dsalgo.com/2013/02/find-kth-largest-element-in-sorted.html
An m x n Young tableau is an m x n matrix such that the entries of each row are in sorted order from left to right
and the entries of each column are in sorted order from top to bottom.
Some of the entries of a Young tableau may be infinity, which we treat as nonexistent elements.
Thus a Young tableau can be used to hold r <= m*n finite numbers.

1. a m x n Young tableau Y is empty if Y[0][0] = infinity
2. the minimum element of a Young tableau Y is always Y[0][0]
3. implement ExtractMin method on a nonempty m x n Young tableau that runs in O(m + n) time
4. implement Insert a new element method into a nonfull m x n Young tableau in O(m + n) time
5. using no other sorting method as subroutine, use an n x n Young tableau to sort n^2 numbers in O(n^3) time, O(n^1.5) time in worst case

see also BinaryMinHeap.h, HeapSort.h
*/
class YoungTableau
{
public:
	YoungTableau(){}
	~YoungTableau(){}

	int Extract_K_Min(std::vector<std::vector<int> > & matrix, int K)
	{
		Debug::Print2D<int>()(matrix, false);
		int min;
		for (int i = 0; i < K; ++i)
		{
			min = matrix[0][0];
			matrix[0][0] = INT_MAX;
			this->YoungifyRecur(matrix, 0, 0);
			//Debug::Print2D<int>()(matrix, false);
		}
		
		Debug::Print2D<int>()(matrix, false);
		std::cout << "YoungTableau Extract_K_Min for \"" << K << "\": " << min << std::endl;
		return min;
	}
	int ExtractMin(std::vector<std::vector<int> > & matrix)
	{
		Debug::Print2D<int>()(matrix, false);

		int min = matrix[0][0];
		matrix[0][0] = INT_MAX;
		this->YoungifyRecur(matrix, 0, 0);

		Debug::Print2D<int>()(matrix, false);
		std::cout << "YoungTableau ExtractMin: " << min << std::endl;
		return min;
	}
private:
	void YoungifyRecur(std::vector<std::vector<int> > & matrix, int rowY, int colX)//bubble down recur
	{
		int N = matrix.size();
		int M = matrix[0].size();

		if (rowY == N - 1 && colX == M - 1)
			return;

		int nxtBigRowY;
		int nxtBigColX;

		if (rowY == N - 1)
		{
			nxtBigRowY = rowY;
			nxtBigColX = colX + 1;
		}
		else if (colX == M - 1)
		{
			nxtBigColX = colX;
			nxtBigRowY = rowY + 1;
		}
		else if (matrix[rowY + 1][colX] < matrix[rowY][colX + 1])//bottom < right: bottom is closer
		{
			nxtBigRowY = rowY + 1;
			nxtBigColX = colX;
		}
		else//right is closer
		{
			nxtBigRowY = rowY;
			nxtBigColX = colX + 1;
		}

		if (matrix[rowY][colX] > matrix[nxtBigRowY][nxtBigColX])//bubble down recur
		{
			std::swap(matrix[rowY][colX], matrix[nxtBigRowY][nxtBigColX]);
			this->YoungifyRecur(matrix, nxtBigRowY, nxtBigColX);
		}
	}

public:
	void Insert(std::vector<std::vector<int> > & matrix, const std::vector<int> & vals)
	{
		Debug::Print2D<int>()(matrix, false);

		int N = matrix.size();
		int M = matrix[0].size();

		for (int i = 0; i < (int)vals.size(); ++i)
		{
			matrix[N - 1][M - 1] = vals[i];
			this->DecreaseKeyRecur(matrix, N - 1, M - 1);
			//Debug::Print2D<int>()(matrix, false);
		}
		
		Debug::Print2D<int>()(matrix, false);
		std::cout << "YoungTableau Insert for \"" << Debug::ToStr1D<int>()(vals) << "\": see above" << std::endl;
	}
	void Insert(std::vector<std::vector<int> > & matrix, int val)
	{
		Debug::Print2D<int>()(matrix, false);

		int N = matrix.size();
		int M = matrix[0].size();
		matrix[N - 1][M - 1] = val;
		this->DecreaseKeyRecur(matrix, N - 1, M - 1);

		Debug::Print2D<int>()(matrix, false);
		std::cout << "YoungTableau Insert for \"" << val << "\": see above" << std::endl;
	}
private:
	void DecreaseKeyRecur(std::vector<std::vector<int> > & matrix, int rowY, int colX)//bubble up recur
	{
		int N = matrix.size();
		int M = matrix[0].size();

		if (rowY == 0 && colX == 0)
			return;

		int prevSmallRowY;
		int prevSmallColX;

		if (rowY == 0)
		{
			prevSmallRowY = rowY;
			prevSmallColX = colX - 1;
		}
		else if (colX == 0)
		{
			prevSmallColX = colX;
			prevSmallRowY = rowY - 1;
		}
		else if (matrix[rowY - 1][colX] > matrix[rowY][colX - 1])//left > up: left is closer
		{
			prevSmallRowY = rowY - 1;
			prevSmallColX = colX;
		}
		else//up is closer
		{
			prevSmallRowY = rowY;
			prevSmallColX = colX - 1;
		}

		if (matrix[rowY][colX] < matrix[prevSmallRowY][prevSmallColX])//bubble up recur
		{
			std::swap(matrix[rowY][colX], matrix[prevSmallRowY][prevSmallColX]);
			this->DecreaseKeyRecur(matrix, prevSmallRowY, prevSmallColX);
		}
	}


public:
	void Sort(std::vector<int> & v)
	{
		std::string before = Debug::ToStr1D<int>()(v);

		//find sqrt(N) in O(logn) time
		int N = v.size();
		int left = -1;
		int right = N + 1;
		while (right - left > 1)
		{
			int mid = (left + right) / 2;
			if (mid * mid >= N)
				right = mid;
			else
				left = mid;
		}
		//now right is the lower bound of sqrt(N)

		//1. insert all elements in v to a sqrt(N)*sqrt(N) young tableau
		std::vector<std::vector<int> > matrix(right, std::vector<int>(right, INT_MAX));
		for (int i = 0; i < N; ++i)
		{
			matrix[right - 1][right - 1] = v[i];
			this->DecreaseKeyRecur(matrix, right - 1, right - 1);
		}
		//Debug::Print2D<int>()(matrix, false);

		//2. extract min for N times from young tableau
		for (int i = 0; i < N; ++i)
		{
			v[i] = matrix[0][0];
			matrix[0][0] = INT_MAX;
			this->YoungifyRecur(matrix, 0, 0);
		}
		//Debug::Print2D<int>()(matrix, false);
		std::cout << "YoungTableau Sort for \"" << before << "\": " << Debug::ToStr1D<int>()(v) << std::endl;
	}
};
/*
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

[rY][cX]
Row#0	= 2, 3, 4, 8, 12, 22, 25
Row#1	= 5, 6, 9, 18, 23, 27, 30
Row#2	= 7, 11, 15, 20, 26, 28, 32
Row#3	= 10, 13, 17, 21, 29, 31, 34
Row#4	= 14, 16, 19, 24, 33, 35, 2147483647

YoungTableau ExtractMin: 1
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

[rY][cX]
Row#0	= 18, 20, 22, 25, 30, 2147483647, 2147483647
Row#1	= 19, 23, 27, 32, 2147483647, 2147483647, 2147483647
Row#2	= 21, 26, 28, 34, 2147483647, 2147483647, 2147483647
Row#3	= 24, 29, 31, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 33, 35, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647

YoungTableau Extract_K_Min for "17": 17
[rY][cX]
Row#0	= 11, 13, 14, 19, 2147483647, 2147483647, 2147483647
Row#1	= 12, 15, 16, 32, 2147483647, 2147483647, 2147483647
Row#2	= 17, 18, 33, 34, 2147483647, 2147483647, 2147483647
Row#3	= 20, 35, 36, 39, 2147483647, 2147483647, 2147483647
Row#4	= 31, 37, 38, 40, 2147483647, 2147483647, 2147483647

[rY][cX]
Row#0	= 1, 11, 13, 14, 19, 2147483647, 2147483647
Row#1	= 12, 15, 16, 32, 2147483647, 2147483647, 2147483647
Row#2	= 17, 18, 33, 34, 2147483647, 2147483647, 2147483647
Row#3	= 20, 35, 36, 39, 2147483647, 2147483647, 2147483647
Row#4	= 31, 37, 38, 40, 2147483647, 2147483647, 2147483647

YoungTableau Insert for "1": see above
[rY][cX]
Row#0	= 11, 13, 14, 19, 2147483647, 2147483647, 2147483647
Row#1	= 12, 15, 16, 32, 2147483647, 2147483647, 2147483647
Row#2	= 17, 18, 33, 34, 2147483647, 2147483647, 2147483647
Row#3	= 20, 35, 36, 39, 2147483647, 2147483647, 2147483647
Row#4	= 31, 37, 38, 40, 2147483647, 2147483647, 2147483647

[rY][cX]
Row#0	= 1, 6, 11, 13, 14, 19, 22
Row#1	= 2, 7, 12, 15, 16, 23, 32
Row#2	= 3, 8, 17, 18, 24, 33, 34
Row#3	= 4, 9, 20, 25, 35, 36, 39
Row#4	= 5, 21, 26, 31, 37, 38, 40

YoungTableau Insert for "1, 2, 3, 4, 5, 6, 7, 8, 9, 21, 22, 23, 24, 25, 26": see above
YoungTableau Sort for "15, 3, 14, 16, 12, 7, 9, 17, 18, 11, 5, 8, 10, 4, 2, 13, 1, 6": 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18
*/
#endif