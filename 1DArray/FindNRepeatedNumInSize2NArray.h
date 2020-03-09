#ifndef _FIND_N_REPEATED_NUM_IN_SIZE_2N_ARRAY_H
#define _FIND_N_REPEATED_NUM_IN_SIZE_2N_ARRAY_H
#include "Debug.h"
/*
Similar to Majority Element, but differernt!
Leetcode: N-Repeated Element in Size 2N Array (with all other nums unique)
In a array A of size 2N, there are N+1 unique elements, and exactly one of these elements is repeated N times.
Return the element repeated N times.
Example 1:
Input: [1,2,3,3]
Output: 3
Example 2:
Input: [2,1,2,5,3,2]
Output: 2
Example 3:
Input: [5,1,5,2,5,3,5,4]
Output: 5
 */
class FindNRepeatedNumInSize2NArray
{
public:
    FindNRepeatedNumInSize2NArray(){}
    ~FindNRepeatedNumInSize2NArray(){}

    void Test(std::vector<int> && A)
    {
        int res1 = UseHashSet(A);
        int res2 = InPlace(A);
        std::cout << "FindNRepeatedNumInSize2NArray UseHashSet, InPlace for [" << Debug::ToStr1D<int>()(A) << "]: " << res1 << "," << res2 << std::endl;
    }

    int UseHashSet(std::vector<int> & A)
    {
        //N-Repeated nums in size-2N array with all other nums unique
        //if there is a repeated num in any ring consecutive 3 nums, that repeated num is answer
        std::unordered_set<int> visit;
        for (int & n : A)
        {
            if (visit.count(n))
                return n;
            visit.insert(n);
        }
        return -1;//won't happen

    }

    int InPlace(std::vector<int> & A)
    {
        //N-Repeated nums in size-2N array with all other nums unique
        //if there is a repeated num in any ring consecutive 3 nums, that repeated num is answer
        int N = A.size();
        for (int i = 0; i < N; ++i)
            if (A[i] == A[((i-2)+N)%N] || A[i] == A[((i-1)+N)%N])
                return A[i];
        return -1;//won't happen
    }
};
/*
FindNRepeatedNumInSize2NArray UseHashSet, InPlace for [5, 1, 5, 2, 5, 3, 5, 4]: 5,5
 */
#endif
