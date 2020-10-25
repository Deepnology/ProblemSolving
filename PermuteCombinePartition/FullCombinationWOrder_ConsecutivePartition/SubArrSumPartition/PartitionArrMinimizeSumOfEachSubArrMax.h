#ifndef _PARTITION_ARR_MINIMIZE_SUM_OF_EACH_SUB_ARR_MAX_H
#define _PARTITION_ARR_MINIMIZE_SUM_OF_EACH_SUB_ARR_MAX_H
#include "Debug.h"
/*
AIG hackerrank online coding, Amazon OA
Given an integer array, partition the array into k subarrays such that the sum of each subarray's max integer is minimized.
ex:
 [30, 10, 40, 20, 50], k=2: 80 ([30],[10,40,20,50] where sum=30+50=80)
 [74303, 20452, 66120, 44483, 5370, 68585], k=5: 234830 ([74303],[20452],[66120,44483],[5370],[68585] where sum=74303+20452+66120+5370+68585)

Leetcode: Minimum Difficulty of a Job Schedule
You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).
You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.
Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].
Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

see also PaintersPartitionFairWorkload.h
 */
class PartitionArrMinimizeSumOfEachSubArrMax
{
public:
    //partition into d subarrays to minimize sum of max of each subarray
    //DFS: O(N^3*d) time, O(N*d) space
    int Recur1(std::vector<int> && jobDifficulty, int d)
    {
        int N = jobDifficulty.size();
        if (N < d) return -1;
        std::vector<std::vector<int>> memo(N+1, std::vector<int>(d+1,-1));
        int res = recur1(jobDifficulty, N, d, memo);
        std::cout << "PartitionArrMinimizeSumOfEachSubArrMax Recur1 for [" << Debug::ToStr1D<int>()(jobDifficulty) << "], k=" << d << ": " << res << std::endl;
        return res;
    }
    int recur1(std::vector<int> & v, int curSize, int k, std::vector<std::vector<int>> & memo)
    {
        if (memo[curSize][k] != -1)
            return memo[curSize][k];
        if (k == 1)
            return memo[curSize][k] = Max(v, 0, curSize-1);
        //if (curSize == 1)
        //    return memo[curSize][k] = v[0];

        int minMaxSum = INT_MAX;
        for (int leftSize = 1; leftSize < curSize; ++leftSize)
        {
            if (k-1 > leftSize) continue; //condition to make sure left array size >= k-1  !!!
            minMaxSum = std::min(minMaxSum, recur1(v, leftSize, k-1, memo) +
                                            Max(v, leftSize, curSize-1));
        }
        return memo[curSize][k] = minMaxSum;
    }

    //improved DFS: O(N^2*d) time, O(N*d) space
    int Recur2(std::vector<int> && jobDifficulty, int d)
    {
        int N = jobDifficulty.size();
        if (N < d) return -1;
        std::vector<std::vector<int>> memo(N+1, std::vector<int>(d+1,-1));
        int res = recur2(jobDifficulty, N, d, memo);
        std::cout << "PartitionArrMinimizeSumOfEachSubArrMax Recur2 for [" << Debug::ToStr1D<int>()(jobDifficulty) << "], k=" << d << ": " << res << std::endl;
        return res;
    }
    int recur2(std::vector<int> & v, int curSize, int k, std::vector<std::vector<int>> & memo)
    {
        if (memo[curSize][k] != -1)
            return memo[curSize][k];
        if (k == 1)
            return memo[curSize][k] = Max(v, 0, curSize-1);

        int minMaxSum = INT_MAX;
        int rightMax = INT_MIN;
        for (int rightSize = 1; rightSize <= curSize-k+1; ++rightSize)
        {
            //note: leftSize must be >= k-1, so rightSize must be <= curSize-(k-1)
            rightMax = std::max(rightMax, v[curSize-rightSize]);
            minMaxSum = std::min(minMaxSum, recur2(v, curSize-rightSize, k-1, memo) + rightMax);
        }
        return memo[curSize][k] = minMaxSum;
    }
    int Max(std::vector<int> & v, int begin, int end)
    {
        int res = v[begin];
        for (int i = begin; i <= end; ++i)
            res = std::max(res, v[i]);
        return res;
    }

    //DFS: O(N^2*d) time, O(N*d) space
    int Recur3(std::vector<int> && jobDifficulty, int d)
    {
        int N = jobDifficulty.size();
        if (N < d) return -1;
        std::vector<std::vector<int>> memo(N+1, std::vector<int>(d+1,-1));
        int res = recur3(jobDifficulty, 0, d, memo);
        std::cout << "PartitionArrMinimizeSumOfEachSubArrMax Recur3 for [" << Debug::ToStr1D<int>()(jobDifficulty) << "], k=" << d << ": " << res << std::endl;
        return res;
    }
    int recur3(std::vector<int> & v, int idx, int k, std::vector<std::vector<int>> & memo)
    {
        int N = v.size();
        if (idx == N && k == 0) return 0;
        if (idx == N || k == 0) return INT_MAX;
        if (memo[idx][k] != -1) return memo[idx][k];
        int curMax = v[idx];
        long long minMaxSum = INT_MAX;
        for (auto i = idx; i < N; ++i)
        {
            curMax = std::max(curMax, v[i]);
            minMaxSum = std::min(minMaxSum, (long long)curMax + (long long)recur3(v, i+1, k-1, memo));
        }
        return memo[idx][k] = (int)minMaxSum;
    }

    //there are iterative DP solutions with O(N*d) time ....
};
/*
PartitionArrMinimizeSumOfEachSubArrMax Recur for [30, 10, 40, 20, 50], k=2: 80
PartitionArrMinimizeSumOfEachSubArrMax Recur for [74303, 20452, 66120, 44483, 5370, 68585], k=5: 234830
 */
/*
Recur2:
the question is equivalent to partition an array into k subarrays such that the sum of each subarray's max value is minimized
we can perform a DFS: keep track of current size of v[0:curSize-1] and current group k that should be applied in v[0:curSize-1] and get current sum of left subarray's max value and right subarray's max value
the corner case: when there is only 1 group left in the range v[0:curSize-1]: just find the max number in the range
otherwise, we enumerate all possible partitions in v[0:curSize-1] to apply (k-1) groups in the left part and 1 group in the right part, while we also keep track of the max value in the right part
since the left size must be >= k-1 (need to have at least k-1 groups for left part), so right size must be <= curSize-(k-1)
then we can get the sum of the two subarray's max from the next level DFS (which is for the left subarray) and the running max value from right subarray
then we keep track of minimized max sum, and return it
since the DFS will encounter many duplicated cases, we can memorize the answers that have already been calculated
Analysis:
O(N^2*k) time, where N is total number of complexity, k is total number of days
O(N*k) space, where N is total number of complexity, k is total number of days
 */
#endif
