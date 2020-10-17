#ifndef _PARTITION_ARR_MAXIMIZE_SUM_OF_EACH_SUB_ARR_AVG_H
#define _PARTITION_ARR_MAXIMIZE_SUM_OF_EACH_SUB_ARR_AVG_H
#include "Debug.h"
/*
Leetcode: Largest Sum of Averages
We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group.
What is the largest score we can achieve?
Note that our partition must use every number in A, and that scores are not necessarily integers.
Example:
Input:
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation:
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
Note:
1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
Answers within 10^-6 of the correct answer will be accepted as correct.
 */
class PartitionArrMaximizeSumOfEachSubArrAvg
{
public:
    double DFS(std::vector<int> & A, int K)
    {
        int N = A.size();
        std::vector<int> prefixSum(N, 0);
        for (auto i = 0; i < N; ++i)
            prefixSum[i] += (i>0?prefixSum[i-1]:0) + A[i];
        std::vector<std::vector<double>> memo(N+1, std::vector<double>(K+1, -1));
        return recur(A, 0, K, memo, prefixSum); //O(N^2) time
    }
    double recur(std::vector<int> & A, int idx, int k, std::vector<std::vector<double>> & memo, const std::vector<int> & prefixSum)
    {
        int N = A.size();
        if (memo[idx][k] != -1) return memo[idx][k];
        if (k == 1)
            return memo[idx][k] = (double)(prefixSum[N-1]-(idx>0?prefixSum[idx-1]:0))/(double)(N-idx);
        double maxAvg = 0;
        for (int i = idx; i < N-(k-1); ++i)//note: right side must have at least k-1 nums
            maxAvg = std::max(maxAvg, (double)(prefixSum[i]-(idx>0?prefixSum[idx-1]:0))/(double)(i-idx+1) + recur(A, i+1, k-1, memo, prefixSum) );

        return memo[idx][k] = maxAvg;
    }
};
#endif
