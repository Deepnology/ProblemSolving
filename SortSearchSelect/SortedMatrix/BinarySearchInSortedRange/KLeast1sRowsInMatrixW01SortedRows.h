#ifndef _K_LEAST_1S_ROWS_IN_MATRIX_W_01_SORTED_ROWS_H
#define _K_LEAST_1S_ROWS_IN_MATRIX_W_01_SORTED_ROWS_H
#include "Debug.h"
/*
Leetcode: The K Weakest Rows in a Matrix
Given a m * n matrix mat of ones (representing soldiers) and zeros (representing civilians), return the indexes of the k weakest rows in the matrix ordered from the weakest to the strongest.
A row i is weaker than row j, if the number of soldiers in row i is less than the number of soldiers in row j, or they have the same number of soldiers but i is less than j.
Soldiers are always stand in the frontier of a row, that is, always ones may appear first and then zeros.
Example 1:
Input: mat =
[[1,1,0,0,0],
 [1,1,1,1,0],
 [1,0,0,0,0],
 [1,1,0,0,0],
 [1,1,1,1,1]],
k = 3
Output: [2,0,3]
Explanation:
The number of soldiers for each row is:
row 0 -> 2
row 1 -> 4
row 2 -> 1
row 3 -> 2
row 4 -> 5
Rows ordered from the weakest to the strongest are [2,0,3,1,4]
Example 2:
Input: mat =
[[1,0,0,0],
 [1,1,1,1],
 [1,0,0,0],
 [1,0,0,0]],
k = 2
Output: [0,2]
Explanation:
The number of soldiers for each row is:
row 0 -> 1
row 1 -> 4
row 2 -> 1
row 3 -> 1
Rows ordered from the weakest to the strongest are [0,2,3,1]
 */
class KLeast1sRowsInMatrixW01SortedRows
{
public:
    std::vector<int> Find_MaxHeapBinarySearch(std::vector<std::vector<int>> & mat, int k)
    {
        std::vector<int> res;
        int N = mat.size();
        std::priority_queue<std::vector<int>> maxHeap;//default comparator: LESS
        for (int i = 0; i < N; ++i)
        {
            int numOnes = BinarySearch(mat[i]) + 1;
            maxHeap.push({numOnes, i});
            if (maxHeap.size() > k)
                maxHeap.pop();
        }
        while (!maxHeap.empty())
        {
            res.push_back(maxHeap.top()[1]);
            maxHeap.pop();
        }
        std::reverse(res.begin(),res.end());
        return res;
    }
private:
    int BinarySearch(const std::vector<int> & v)
    {
        int left = 0;
        int right = v.size()-1;
        while (left <= right)
        {
            int mid = (left+right)/2;
            if (v[mid]==0)
                right = mid-1;
            else
                left = mid+1;
        }
        return left;
    }
};
#endif
