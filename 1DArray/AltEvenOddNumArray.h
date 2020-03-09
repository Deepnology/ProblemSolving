#ifndef _ALT_EVEN_ODD_NUM_ARRAY_H
#define _ALT_EVEN_ODD_NUM_ARRAY_H
#include "Debug.h"
/*
Leetcode: Sort Array By Parity II
Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.
Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.
You may return any answer array that satisfies this condition.
Example 1:
Input: [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
 */
class AltEvenOddNumArray
{
public:
    AltEvenOddNumArray(){}
    ~AltEvenOddNumArray(){}

    std::vector<int> TwoPointers(std::vector<int> && A)
    {
        std::cout << "AltEvenOddNumArray TwoPointers for [" << Debug::ToStr1D<int>()(A) << ": ";
        int N = A.size();
        int i = 0;
        int j = 1;
        while (i < N && j < N)
        {
            while (i < N && A[i] % 2 == 0)
                i += 2;
            while (j < N && A[j] % 2 == 1)
                j += 2;
            if (i < N && j < N)
                std::swap(A[i], A[j]);
        }
        std::cout << Debug::ToStr1D<int>()(A) << std::endl;
        return A;
    }
};
/*
AltEvenOddNumArray TwoPointers for [4, 2, 5, 7: 4, 5, 2, 7
 */
#endif
