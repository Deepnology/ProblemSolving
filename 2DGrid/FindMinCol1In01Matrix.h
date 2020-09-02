/*Facebook*/
#ifndef _FIND_MIN_COL_1_IN_01_MATRIX_H
#define _FIND_MIN_COL_1_IN_01_MATRIX_H
#include "Debug.h"
/*
Given a 2d matrix with only 0 and 1, where all 0s in each row come before 1s.
Find the row that contains max number of 1s, and return the leftmost column index of 1s in that row.
(Find a 1 that has min column index)

Leetcode: Leftmost Column with at Least a One
A binary matrix means that all elements are 0 or 1.
For each individual row of the matrix, this row is sorted in non-decreasing order.
Given a row-sorted binary matrix binaryMatrix, return leftmost column index(0-indexed) with at least a 1 in it.
If such index doesn't exist, return -1.
You can't access the Binary Matrix directly.
You may only access the matrix using a BinaryMatrix interface:
BinaryMatrix.get(row, col) returns the element of the matrix at index (row, col) (0-indexed).
BinaryMatrix.dimensions() returns a list of 2 elements [rows, cols], which means the matrix is rows * cols.
Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.
Also, any solutions that attempt to circumvent the judge will result in disqualification.
For custom testing purposes you're given the binary matrix mat as input in the following four examples.
You will not have access the binary matrix directly.
 */
class FindMinCol1In01Matrix
{
public:
    FindMinCol1In01Matrix(){}

    int LinearSearchFromUpperRightCorner(const std::vector<std::vector<int>> & v)//O(N+M) time
    {
        int N = v.size();
        int M = v[0].size();
        int i = 0;
        int j = M-1;
        while (i < N && j >= 0)
        {
            if (v[i][j] == 1)
                --j;
            else
                ++i;
        }
        Debug::Print2D<int>()(v, false);
        std::cout << "FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: " << j+1 << std::endl;
        return j+1;
    }

    class BinaryMatrix
    {
    public:
        int get(int row, int col);
        std::vector<int> dimensions();
    };
    int LinearSearch(BinaryMatrix & binaryMatrix) //O(N+M) time
    {
        int N = binaryMatrix.dimensions()[0];
        int M = binaryMatrix.dimensions()[1];
        int col = M-1;
        for (int row = 0; row < N; ++row)
        {
            while (col >= 0 && binaryMatrix.get(row, col) == 1)
                --col;
        }
        return col == M-1 ? -1 : col+1;
    }
    int BinarySearch(BinaryMatrix & binaryMatrix) //O(NlogM) time
    {
        int N = binaryMatrix.dimensions()[0];
        int M = binaryMatrix.dimensions()[1];
        int left = 0; int right = M-1; int resCol = -1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            //test if column mid has any 1
            bool midColHas1 = false;
            for (int i = 0; i < N; ++i)
                if (binaryMatrix.get(i,mid) == 1)
                {
                    midColHas1 = true;
                    break;
                }
            if (midColHas1)
            {
                resCol = mid;
                right = mid-1;
            }
            else
                left = mid+1;
        }
        //return resCol;
        return left==M ? -1 : left;
    }
};
/*
[rY][cX]
Row#0	= 0, 0, 1, 1, 1
Row#1	= 0, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1
Row#3	= 0, 0, 0, 0, 0

FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: 1
[rY][cX]
Row#0	= 0, 0, 0, 0, 1
Row#1	= 0, 1, 1, 1, 1
Row#2	= 0, 0, 1, 1, 1
Row#3	= 1, 1, 1, 1, 1

FindMinCol1In01Matrix LinearSearchFromUpperRightCorner for above matrix: 0
 */
#endif
