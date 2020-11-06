#ifndef _FIND_MIN_COMMON_NUM_OF_ALL_ROWS_IN_ROW_SORTED_MATRIX_H
#define _FIND_MIN_COMMON_NUM_OF_ALL_ROWS_IN_ROW_SORTED_MATRIX_H
#include "Debug.h"
/*
Leetcode: Find Smallest Common Element in All Rows
Given a matrix mat where every row is sorted in strictly increasing order, return the smallest common element in all rows.
If there is no common element, return -1.
Example 1:
Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
Output: 5
 */
class FindMinCommonNumOfAllRowsInRowSortedMatrix
{
public:
    int Solve(std::vector<std::vector<int>>& mat)
    {
        //Approach1: use minHeap to keep track of 1 element from each row, similar to KWayMergeSort: O(M*NlogN) time
        //Approach2: for each element in 1st row, binary search all the other rows: O(M*NlogM) time
        //Approach3: since all element in a row are distinct, and if we know the num range, we can use buckets to count each num: O(N*M) time
        std::vector<int> count(10001, 0);
        int N = mat.size();
        int M = mat[0].size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                count[mat[i][j]]++;
        for (auto i = 0; i < count.size(); ++i)
            if (count[i] == N)
                return i;
        return -1;
    }
};
#endif
