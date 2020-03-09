#ifndef _EQUAL_GLOBAL_AND_LOCAL_INVERSIONS_H
#define _EQUAL_GLOBAL_AND_LOCAL_INVERSIONS_H
#include "Debug.h"
/*
Leetcode: Global And Local Inversions
We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.
The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].
The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].
Return true if and only if the number of global inversions is equal to the number of local inversions.
Example 1:
Input: A = [1,0,2]
Output: true
Explanation: There is 1 global inversion, and 1 local inversion.
Example 2:
Input: A = [1,2,0]
Output: false
Explanation: There are 2 global inversions, and 1 local inversion.
 */
class EqualGlobalAndLocalInversions
{
public:
    EqualGlobalAndLocalInversions(){}

    void Test(const std::vector<int> & A)
    {
        bool bf = BruteForce(A);
        bool lr = Linear(A);
        std::cout << "EqualGlobalAndLocalInversions BruteForce and Linear for [" << Debug::ToStr1D<int>()(A) << "]: " << bf << ", " << lr << std::endl;
    }

    bool BruteForce(const std::vector<int> & A)
    {
        int N = A.size();
        for (int i = 0; i < N; ++i)
            for (int j = i + 2; j < N; ++j)
                if (A[i] > A[j])//A[i] > A[i+2:N-1]
                    return false;
        return true;
    }

    bool Linear(const std::vector<int> & A)
    {
        int N = A.size();
        int curMin = INT_MAX;
        for (int i = N-1; i >= 2; --i)
        {
            curMin = std::min(curMin, A[i]);
            if (A[i-2] > curMin)
                return false;
        }
        return true;
    }
};
/*
EqualGlobalAndLocalInversions BruteForce and Linear for [1, 0, 2]: 1, 1
EqualGlobalAndLocalInversions BruteForce and Linear for [1, 2, 0]: 0, 0
 */
#endif
