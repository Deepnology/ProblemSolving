#ifndef KTH_SMALLEST_ELEMENT_IN_MATRIX_H
#define KTH_SMALLEST_ELEMENT_IN_MATRIX_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug.h"
/*
Microsoft
http://www.careercup.com/question?id=13475667

1D QuickSelect: O(m*n) time
*/
class KthSmallestElementInMatrix
{
public:
	KthSmallestElementInMatrix(){}
	~KthSmallestElementInMatrix(){}
private:
	/*
	idx1D = rowY * M + colX
	rowY = idx1D / M
	colX = idx1D % M
	*/
	int To1D(int rowY, int colX, int numCol)
	{
		return rowY*numCol + colX;
	}
	std::pair<int, int> To2D(int idx, int numCol)
	{
		return std::make_pair(idx / numCol, idx % numCol);
	}
public:
	int OneDQuickSelectIterate(std::vector<std::vector<int> > & A, int K)
	{
		int N = A.size();
		int M = A[0].size();
		if (K < 1 || K > N*M)//K-th: starting from 1 to N*M
			throw (std::runtime_error("KthSmallestElementInMatrix OneDQuickSelectIterate K out of bound"));
		int Kbefore = K;
		Debug::Print2D<int>()(A, false);

		int lo = this->To1D(0, 0, M);
		int hi = this->To1D(N - 1, M - 1, M);
		int res = INT_MIN;
		while (lo <= hi)
		{
			int mid = (hi + lo) / 2;
			int pivot = this->OneDPartition(A, lo, hi, mid);
			
			if (K < pivot - lo + 1)
				hi = pivot - 1;
			else if (K > pivot - lo + 1)
			{
				K -= (pivot - lo + 1);
				lo = pivot + 1;
			}
			else
			{
				res = A[this->To2D(pivot, M).first][this->To2D(pivot, M).second];
				break;
			}
		}
		Debug::Print2D<int>()(A, false);
		std::cout << "KthSmallestElementInMatrix OneDQuickSelectIterate for \"" << Kbefore << "\": " << res << std::endl;
		return res;
	}

	int OneDPartition(std::vector<std::vector<int> > & A, int lo, int hi, int pivot)
	{
		int N = A.size();
		int M = A[0].size();
		
		int pivotRowY = this->To2D(pivot, M).first;
		int pivotColX = this->To2D(pivot, M).second;
		//std::cout << "Pivot: " << pivot << ",[" << pivotRowY << "," << pivotColX << "] = " << A[pivotRowY][pivotColX] << std::endl;

		int hiRowY = this->To2D(hi, M).first;
		int hiColX = this->To2D(hi, M).second;
		int pivotVal = A[pivotRowY][pivotColX];
		std::swap(A[pivotRowY][pivotColX], A[hiRowY][hiColX]);

		int i = lo;
		int j = hi;

		while (i <= j)
		{
			if (A[this->To2D(i, M).first][this->To2D(i, M).second] < pivotVal)
				++i;
			else if(A[this->To2D(j, M).first][this->To2D(j, M).second] >= pivotVal)
				--j;
			else
			{
				std::swap(A[this->To2D(i, M).first][this->To2D(i, M).second], A[this->To2D(j, M).first][this->To2D(j, M).second]);
				++i;
				--j;
			}
		}

		std::swap(A[this->To2D(i, M).first][this->To2D(i, M).second], A[hiRowY][hiColX]);
		
		//Debug::Print2D<int>()(A, false);
		return i;
	}
	
	int OneDPartition2(std::vector<std::vector<int> > & A, int lo, int hi, int pivot)
	{
		int N = A.size();
		int M = A[0].size();

		int pivotRowY = this->To2D(pivot, M).first;
		int pivotColX = this->To2D(pivot, M).second;
		//std::cout << "Pivot: " << pivot << ",[" << pivotRowY << "," << pivotColX << "] = " << A[pivotRowY][pivotColX] << std::endl;

		int hiRowY = this->To2D(hi, M).first;
		int hiColX = this->To2D(hi, M).second;
		int pivotVal = A[pivotRowY][pivotColX];
		std::swap(A[pivotRowY][pivotColX], A[hiRowY][hiColX]);

		int curFrontCount = lo;
		for (int i = lo; i <= hi; ++i)
		{
			if (A[this->To2D(i, M).first][this->To2D(i, M).second] < pivotVal)
			{
				std::swap(A[this->To2D(curFrontCount, M).first][this->To2D(curFrontCount, M).second], A[this->To2D(i, M).first][this->To2D(i, M).second]);
				++curFrontCount;
			}
			//curFrontCount points to the leftmost element that is >= pivotVal
		}
		//now:
		//all elements on res's left side: < pivotVal
		//all elements on res's right side: >= pivotVal
		//the element on res: >= pivotVal
		std::swap(A[this->To2D(curFrontCount, M).first][this->To2D(curFrontCount, M).second], A[hiRowY][hiColX]);

		//Debug::Print2D<int>()(A, false);
		return curFrontCount;
	}

};
/*
[rY][cX]
Row#0	= 21, 34, 4, 24, 18, 27, 1
Row#1	= 25, 17, 35, 29, 13, 3, 31
Row#2	= 7, 20, 6, 15, 22, 9, 23
Row#3	= 26, 33, 30, 16, 8, 14, 5
Row#4	= 11, 10, 2, 12, 32, 28, 19

[rY][cX]
Row#0	= 1, 2, 4, 10, 11, 5, 7
Row#1	= 14, 8, 9, 6, 13, 3, 12
Row#2	= 15, 20, 29, 19, 22, 35, 23
Row#3	= 26, 33, 30, 16, 17, 25, 27
Row#4	= 18, 24, 34, 21, 32, 28, 31

KthSmallestElementInMatrix OneDQuickSelectIterate for "1": 1
[rY][cX]
Row#0	= 21, 34, 4, 24, 18, 27, 1
Row#1	= 25, 17, 35, 29, 13, 3, 31
Row#2	= 7, 20, 6, 15, 22, 9, 23
Row#3	= 26, 33, 30, 16, 8, 14, 5
Row#4	= 11, 10, 2, 12, 32, 28, 19

[rY][cX]
Row#0	= 12, 2, 4, 10, 11, 5, 1
Row#1	= 14, 8, 9, 6, 13, 3, 7
Row#2	= 15, 16, 17, 19, 18, 20, 21
Row#3	= 26, 25, 24, 22, 23, 27, 35
Row#4	= 31, 30, 34, 33, 32, 28, 29

KthSmallestElementInMatrix OneDQuickSelectIterate for "21": 21
*/
#endif