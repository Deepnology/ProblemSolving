#ifndef _MOVE_EVEN_NUMS_TO_FRONT_IN_ARRAY_H
#define _MOVE_EVEN_NUMS_TO_FRONT_IN_ARRAY_H
#include "Debug.h"
/*
Leetcode: Sort Array By Parity
Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.
You may return any answer array that satisfies this condition.
Example 1:
Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
 */
class MoveEvenNumsToFrontInArray
{
public:
    MoveEvenNumsToFrontInArray(){}
    ~MoveEvenNumsToFrontInArray(){}

    std::vector<int> UnStable(std::vector<int> && A)
    {
        std::cout << "MoveEvenNumsToFrontInArray UnStable for [" << Debug::ToStr1D<int>()(A) << "]: ";
        int N = A.size();
        int newEnd = 0;
        for (int i = 0; i < N; ++i)
        {
            if (A[i] % 2 == 0)
                std::swap(A[newEnd++], A[i]);
        }

        std::cout << Debug::ToStr1D<int>()(A) << std::endl;
        return A;
    }
};
/*
MoveEvenNumsToFrontInArray UnStable for [3, 1, 2, 4]: 2, 4, 3, 1
 */
#endif
