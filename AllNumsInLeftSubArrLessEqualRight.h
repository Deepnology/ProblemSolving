#ifndef _ALL_NUMS_IN_LEFT_SUB_ARR_LESS_EQUAL_RIGHT_H
#define _ALL_NUMS_IN_LEFT_SUB_ARR_LESS_EQUAL_RIGHT_H
#include "Debug.h"
/*
Leetcode: Partition Array into Disjoint Intervals
Given an array A, partition it into two (contiguous) subarrays left and right so that:
Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.
Example 1:
Input: [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
Example 2:
Input: [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
 */
class AllNumsInLeftSubArrLessEqualRight
{
public:
    AllNumsInLeftSubArrLessEqualRight(){}
    ~AllNumsInLeftSubArrLessEqualRight(){}

    void Test(std::vector<int> && A)
    {
        int res = Partition(A);
        std::cout << "AllNumsInLeftSubArrLessEqualRight Partition for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
    }

    int Partition(std::vector<int> & A)
    {
        int N = A.size();
        std::vector<int> minRight(N);
        for (int i = N-1; i >= 0; --i)
            minRight[i] = i==N-1? A[i] : std::min(minRight[i+1],A[i]);
        int maxLeft;
        for (int i = 0; i < N-1; ++i)
        {
            maxLeft = i==0? A[i] : std::max(maxLeft,A[i]);
            if (maxLeft <= minRight[i+1])
                return i+1;
        }
        return -1;
    }

};
/*
AllNumsInLeftSubArrLessEqualRight Partition for [1, 1, 1, 0, 6, 12]: 4
 */
#endif
