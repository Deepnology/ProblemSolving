#ifndef KTH_SMALLEST_ELEMENT_IN_SORTED_MATRIX_H
#define KTH_SMALLEST_ELEMENT_IN_SORTED_MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "Debug.h"
/*
Leetcode: Kth Smallest Element in a Sorted Matrix
http://www.quora.com/How-can-you-efficiently-determine-the-k-th-maximum-element-in-a-MxN-sorted-matrix
http://blog.csdn.net/whuwangyi/article/details/17088707
http://www.geeksforgeeks.org/kth-smallest-element-in-a-row-wise-and-column-wise-sorted-2d-array-set-1/
http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf
http://www.careercup.com/question?id=6335704
http://www.dsalgo.com/2013/02/find-kth-largest-element-in-sorted.html
http://lyle.smu.edu/~saad/courses/cse3358/ps5/problemset5sol.pdf (Young Tableau)

1. Use minHeap and keep track of all (rowY,colX) pairs in minHeap
   When you pop the current min, push its two larger neighbors to the minHeap, if they weren't processed already (need to mark the element that has been processed).
   Count for K times.
   Similar to KwayMergeSort.h, KthSmallestPairSum2SortedArrays.h
   O(KlogK) time, O(K) space

2. Use 1D QuickSelect in 2D matrix
   See KthSmallestElementInMatrix.h
   O(m*n) time

3. Selection in X + Y And Matrices With Sorted Rows and Columns.
   O(m + n) time

4. Greg N. Frederickson and Donald B. Johnson. 
   Generalized Selection and Ranking: Sorted Matrices. SIAM J. Comput. 13, pp. 14-30.
   O(K) time

5. Extract Min (Youngify)
   Replace current element with next big of its right or bottom (the smaller of right and bottom) starting from [0][0] along the path down to [N-1][M-1].
   After that, the [0][0] will be the current smallest element in the matrix.
   Repeat for K times, [0][0] will be the Kth smallest element.
   O(K * (m + n)) time
*/
class KthSmallestElementInSortedMatrix
{
public:
	KthSmallestElementInSortedMatrix(){}
	~KthSmallestElementInSortedMatrix(){}
	struct CompGreater
	{
		bool operator()(const std::pair<int, std::pair<int, int> > & a, const std::pair<int, std::pair<int, int> > & b)
		{
			return a.first > b.first;
		}
	};
	int MinHeap_InPlace(std::vector<std::vector<int> > & matrix, int K)
	{
		Debug::Print2D<int>()(matrix, false);

		int N = matrix.size();
		int M = matrix[0].size();
		
		std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, CompGreater> minHeap;
		//first: val, second.first: rowY, second.second: colX
		minHeap.push({ matrix[0][0], { 0, 0 } });
		int count = 1;
		matrix[0][0] = INT_MIN;
		int res;
		int resRowY;
		int resColX;
		while (count <= K)
		{
			res = minHeap.top().first;
			resRowY = minHeap.top().second.first;
			resColX = minHeap.top().second.second;
			minHeap.pop();

			if (resRowY + 1 < N && matrix[resRowY + 1][resColX] != INT_MIN)
			{
				minHeap.push({ matrix[resRowY + 1][resColX], {resRowY + 1, resColX} });
				matrix[resRowY + 1][resColX] = INT_MIN;//mark the processed element
			}
			if (resColX + 1 < M && matrix[resRowY][resColX + 1] != INT_MIN)
			{
				minHeap.push({ matrix[resRowY][resColX + 1], {resRowY, resColX + 1} });
				matrix[resRowY][resColX + 1] = INT_MIN;//mark the processed element
			}
			++count;
		}

		std::cout << "KthSmallestElementInSortedMatrix MinHeap_InPlace for \"" << K << "\"-th: [" << res << ",(" << resRowY << "," << resColX << ")]" << std::endl;
		return res;
	}

	int MinHeap(const std::vector<std::vector<int> > & board, int K)
	{
		int N = board.size();
		int M = board[0].size();

		std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> minHeap;
		//first: val, second.first: rowY, second.second: colX
		minHeap.push({ board[0][0], { 0, 0 } });

		std::vector<std::vector<int> > pairsInHeap(N, std::vector<int>(M, 0));
		pairsInHeap[0][0] = 1;
		if (K > N * M) K = N * M;
		for (int i = 0; i < K - 1; ++i)//extract min from minHeap for K times
		{
			auto curMin = minHeap.top();
			minHeap.pop();
			pairsInHeap[curMin.second.first][curMin.second.second] = 0;
			
			if (curMin.second.first + 1 < N &&
				pairsInHeap[curMin.second.first + 1][curMin.second.second] == 0)
			{
				minHeap.push({ board[curMin.second.first + 1][curMin.second.second], {curMin.second.first + 1, curMin.second.second} });
				pairsInHeap[curMin.second.first + 1][curMin.second.second] = 1;
			}

			if (curMin.second.second + 1 < M &&
				pairsInHeap[curMin.second.first][curMin.second.second + 1] == 0)
			{
				minHeap.push({ board[curMin.second.first][curMin.second.second + 1], {curMin.second.first, curMin.second.second + 1} });
				pairsInHeap[curMin.second.first][curMin.second.second + 1] = 1;
			}
		}
		auto curMin = minHeap.top();
		
		Debug::Print2D<int>()(board, false);
		std::cout << "KthSmallestElementInSortedMatrix MinHeap for \"" << K << "-th\": [" << curMin.first << ",(" << curMin.second.first << "," << curMin.second.second << ")]" << std::endl;
		return curMin.first;
	}

	int ExtractMin(std::vector<std::vector<int> > & matrix, int K)
	{
		Debug::Print2D<int>()(matrix, false);

		for (int i = 0; i < K - 1; ++i)
		{
			this->ExtractMinRecur(matrix, 0, 0);
			//Debug::Print2D<int>()(matrix, false);
		}

		Debug::Print2D<int>()(matrix, false);
		std::cout << "KthSmallestElementInSortedMatrix ExtractMin for \"" << K << "\"-th: " << matrix[0][0] << std::endl;
		return matrix[0][0];
	}
private:
	void ExtractMinRecur(std::vector<std::vector<int> > & matrix, int rowY, int colX)
	{
		int N = matrix.size();
		int M = matrix[0].size();
		
		if (rowY == N - 1 && colX == M - 1)
		{
			matrix[rowY][colX] = INT_MAX;
			return;
		}

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
		else if (matrix[rowY + 1][colX] < matrix[rowY][colX + 1])
		{
			nxtBigRowY = rowY + 1;
			nxtBigColX = colX;
		}
		else
		{
			nxtBigRowY = rowY;
			nxtBigColX = colX + 1;
		}
		matrix[rowY][colX] = matrix[nxtBigRowY][nxtBigColX];
		this->ExtractMinRecur(matrix, nxtBigRowY, nxtBigColX);
	}
};
/*
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap_InPlace for "11"-th: [11,(2,1)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap_InPlace for "22"-th: [22,(0,5)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap_InPlace for "33"-th: [33,(4,5)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap for "11-th": [11,(2,1)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap for "22-th": [22,(0,5)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

KthSmallestElementInSortedMatrix MinHeap for "33-th": [33,(4,5)]
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

[rY][cX]
Row#0	= 11, 12, 17, 18, 22, 25, 30
Row#1	= 13, 15, 20, 23, 27, 32, 2147483647
Row#2	= 14, 16, 21, 26, 28, 34, 2147483647
Row#3	= 19, 29, 31, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 24, 33, 35, 2147483647, 2147483647, 2147483647, 2147483647

KthSmallestElementInSortedMatrix ExtractMin for "11"-th: 11
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

[rY][cX]
Row#0	= 22, 25, 27, 30, 2147483647, 2147483647, 2147483647
Row#1	= 23, 26, 32, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 24, 28, 34, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 29, 31, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 33, 35, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647

KthSmallestElementInSortedMatrix ExtractMin for "22"-th: 22
[rY][cX]
Row#0	= 1, 3, 4, 8, 12, 22, 25
Row#1	= 2, 5, 6, 9, 18, 27, 30
Row#2	= 7, 11, 15, 20, 23, 28, 32
Row#3	= 10, 13, 17, 21, 26, 31, 34
Row#4	= 14, 16, 19, 24, 29, 33, 35

[rY][cX]
Row#0	= 33, 34, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#1	= 35, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#3	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647
Row#4	= 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647, 2147483647

KthSmallestElementInSortedMatrix ExtractMin for "33"-th: 33
[rY][cX]
Row#0	= 1, 5, 9
Row#1	= 10, 11, 13
Row#2	= 12, 13, 15

KthSmallestElementInSortedMatrix MinHeap_InPlace for "8"-th: [13,(2,1)]
[rY][cX]
Row#0	= 1, 5, 9
Row#1	= 10, 11, 13
Row#2	= 12, 13, 15

KthSmallestElementInSortedMatrix MinHeap for "8-th": [13,(2,1)]
[rY][cX]
Row#0	= 1, 5, 9
Row#1	= 10, 11, 13
Row#2	= 12, 13, 15

[rY][cX]
Row#0	= 13, 15, 2147483647
Row#1	= 2147483647, 2147483647, 2147483647
Row#2	= 2147483647, 2147483647, 2147483647

KthSmallestElementInSortedMatrix ExtractMin for "8"-th: 13
*/
#endif