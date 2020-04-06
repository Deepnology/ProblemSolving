#ifndef _EXIST_SUB_ARR_W_SUM_MULTIPLE_OF_K_H
#define _EXIST_SUB_ARR_W_SUM_MULTIPLE_OF_K_H
#include "Debug.h"
/*
Leetcode: Continuous Subarray sum
Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2
that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.
Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
*/
class ExistSubArrWSumMultipleOfK
{
public:
    bool PrefixSumMap(const std::vector<int> & v, int k)
    {
        bool res = solve(v, k);
        std::cout << "ExistSubArrSumMultipleOfK for k=" << k << ", \"" << Debug::ToStr1D<int>()(v) << "\": " << res << std::endl;
        return res;
    }
private:
    bool solve(const std::vector<int> & v, int k)
    {
        std::unordered_map<int, int> prefixSumMap;//<prefixSum%k, first occur idx>
        int prefixSum = 0;
        int N = v.size();
        for (int i = 0; i < N; ++i)
        {
            prefixSum += v[i];
            if (k != 0) prefixSum %= k;
            if (prefixSum == 0 && i >= 1)//cur prefixSum is a multiple of k
                return true;
            if (prefixSumMap.count(prefixSum))
            {
                if (i - prefixSumMap[prefixSum] > 1)//[prefixSumMap[prefixSum]+1,...,i] must contain at least 2 elements
                    return true;
            }
            else
                prefixSumMap.insert({ prefixSum, i });
        }
        return false;
    }
};
/*
ExistSubArrSumMultipleOfK for k=6, "23, 2, 4, 6, 7": 1
ExistSubArrSumMultipleOfK for k=6, "23, 2, 6, 4, 7": 1
 */
#endif
