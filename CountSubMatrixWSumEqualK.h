#ifndef _COUNT_SUB_MATRIX_W_SUM_EQUAL_K_H
#define _COUNT_SUB_MATRIX_W_SUM_EQUAL_K_H
#include "Debug.h"
/*
Leetcode: 1074. Number of Submatrices That Sum to Target
Given a matrix, and a target, return the number of non-empty submatrices that sum to target.
A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
Example 1:
Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.
Example 2:
Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
Note:
1 <= matrix.length <= 300
1 <= matrix[0].length <= 300
-1000 <= matrix[i] <= 1000
-10^8 <= target <= 10^8
 */
class CountSubMatrixWSumEqualK
{
public:
    int UsePrefixSumMap(std::vector<std::vector<int>> && matrix, int target)
    {
        int N = matrix.size();
        int M = matrix[0].size();
        int res = 0;

        for (int topR = 0; topR < N; ++topR)
        {
            std::vector<int> subMatrixSum(M,0);
            for (int bottomR = topR; bottomR < N; ++bottomR)
            {
                for (int col = 0; col < M; ++col)
                    subMatrixSum[col] += matrix[bottomR][col];

                std::unordered_map<int,int> prefixSumCount;
                prefixSumCount[0] = 1;//in case the prefixSum equal to target
                int prefixSum = 0;
                for (int col = 0; col < M; ++col)
                {
                    prefixSum += subMatrixSum[col];
                    if (prefixSumCount.count(prefixSum-target))
                        res += prefixSumCount[prefixSum-target];
                    ++prefixSumCount[prefixSum];
                }
            }
        }
        Debug::Print2D<int>()(matrix, false);
        std::cout << "CountSubMatrixWSumEqualK for above matrix, k=" << target<< ": " << res << std::endl;
        return res;
    }
};
/*
[rY][cX]
Row#0	= 0, 1, 0
Row#1	= 1, 1, 1
Row#2	= 0, 1, 0

CountSubMatrixWSumEqualK for above matrix, k=0: 4
 */
#endif
