#ifndef _PARTITION_ARR_TO_DOUBLE_VALUED_PAIRS_H
#define _PARTITION_ARR_TO_DOUBLE_VALUED_PAIRS_H
#include "Debug.h"
/*
Leetcode: Array of Double Pairs
Given an array of integers A with even length, return true if and only if it is possible to
 reorder it such that A[2 * i + 1] = 2 * A[2 * i] for every 0 <= i < len(A) / 2.
Example 1:
Input: [3,1,3,6]
Output: false
Example 2:
Input: [2,1,2,6]
Output: false
Example 3:
Input: [4,-2,2,-4]
Output: true
Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
Example 4:
Input: [1,2,4,16,8,4]
Output: false
 */
class PartitionArrToDoubleValuedPairs
{
public:
    PartitionArrToDoubleValuedPairs(){}
    ~PartitionArrToDoubleValuedPairs(){}

    void Test(std::vector<int> && A)
    {
        bool res = Valid(A);
        std::cout << "ParititonArrToDoubleValuedPairs Valid for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
    }

    bool Valid(std::vector<int> & A)
    {
        /*
        i==0: A[1]=2*A[0]
        i==1: A[3]=2*A[2]
        i==2: A[5]=2*A[4]
        i==3: A[7]=2*A[6]
        */
        //O(N+KlogK) time
        std::unordered_map<int,int> count;
        for (auto & n : A)
            ++count[n];
        std::vector<int> keys;//keys are distinct
        for (auto & p : count)
            keys.push_back(p.first);
        std::sort(keys.begin(), keys.end(),
                  [](auto & a, auto & b)
                  {return std::abs(a)<std::abs(b);});//O(KlogK) time
        for (auto & k : keys)//iterate all keys in abs value incr order
        {
            if (count[k] > count[2*k])//we got extra k that won't get matched later
                return false;
            count[2*k] -= count[k];//cancel out matched keys
            //the extra 2*k will be tested later
        }
        return true;
    }
};
/*
ParititonArrToDoubleValuedPairs Valid for [4, -2, 2, -4]: 1
 */
#endif
