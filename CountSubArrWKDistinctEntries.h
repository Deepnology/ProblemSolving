#ifndef _COUNT_SUBARR_W_K_DISTINCT_ENTRIES_H
#define _COUNT_SUBARR_W_K_DISTINCT_ENTRIES_H
#include "Debug.h"
/*
Leetcode: Subarrays with K Different Integers
Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.
(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
Return the number of good subarrays of A.
Example 1:
Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
Example 2:
Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 */
class CountSubArrWKDistinctEntries
{
public:
    CountSubArrWKDistinctEntries(){}
    ~CountSubArrWKDistinctEntries(){}

    int Solve(std::vector<int> && A, int K)
    {
        int res = 0;
        std::unordered_map<int, int> lastIdx;//lastIdx of all entries in window
        int left = 0;
        int right = 0;
        while(right < A.size())
        {
            lastIdx[A[right]] = right;

            while (lastIdx.size() > K)
            {
                if (lastIdx[A[left]] == left)
                    lastIdx.erase(A[left]);
                ++left;//shrink window
            }
            if (lastIdx.size() == K)
            {
                int minIdx = right;
                for (auto p : lastIdx)
                    minIdx = std::min(minIdx, p.second);
                res += minIdx - left + 1;
                // Any window start between [left, minIdx] and end with right is a qualified answer
            }
            ++right;
        }
        std::cout << "CountSubArrWKDistinctEntries for [" << Debug::ToStr1D<int>()(A) << "], K=" << K << ": " << res << std::endl;
        return res;
    }

    int Solve2(std::vector<int> && A, int K)
    {
        int atMostK = CountSubarrAtMostKDistinct(A, K);
        int atMostKMinus1 = CountSubarrAtMostKDistinct(A, K-1);
        int res = atMostK - atMostKMinus1;
        std::cout << "CountSubArrWKDistinctEntries for [" << Debug::ToStr1D<int>()(A) << "], K=" << K << ": " << res << std::endl;
        return res;
    }
    int CountSubarrAtMostKDistinct(std::vector<int> & A, int K)
    {
        int N = A.size();
        int res = 0;
        std::unordered_map<int,int> count;
        int begin = 0;
        for (int i = 0; i < N; ++i)
        {
            ++count[A[i]];
            while (count.size() > K)
            {
                int curVal = A[begin++];
                int curCount = count[curVal];
                if (curCount > 1)
                    --count[curVal];
                else
                    count.erase(curVal);
            }
            res += i-begin+1;
            //ex: cur subarr is [1,2,3,4] with an added num 4, total num subarr end at 4:
            //[1,2,3,4],[2,3,4],[3,4],[4]
        }
        return res;
    }
};
/*
CountSubArrWKDistinctEntries for [1, 2, 1, 2, 3], K=2: 7
 */
#endif
