#ifndef _SHORTEST_SUBARR_TO_REMOVE_TO_MAKE_ARR_SORTED_H
#define _SHORTEST_SUBARR_TO_REMOVE_TO_MAKE_ARR_SORTED_H
#include "Debug.h"
/*
Leetcode: Shortest Subarray to be Removed to Make Array Sorted
Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
A subarray is a contiguous subsequence of the array.
Return the length of the shortest subarray to remove.
Example 1:
Input: arr = [1,2,3,10,4,2,3,5]
Output: 3
Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
Another correct solution is to remove the subarray [3,10,4].
Example 2:
Input: arr = [5,4,3,2,1]
Output: 4
Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] or [4,3,2,1].

see also ShortestSubarrToSortToMakeArrSorted.h
 */
class ShortestSubarrToRemoveToMakeArrSorted
{
public:
    int FindSubarrLen(std::vector<int> & A)
    {
        int N = A.size();

        //left: end of sorted subarray from begin inclusive
        int left = 0;
        while (left < N-1 && A[left] <= A[left+1])
            ++left;
        if (left == N-1) return 0;

        //right: begin of sorted subarray from end inclusive
        int right = N-1;
        while (right > 0 && A[right-1] <= A[right])
            --right;
        //now A[0:left] and A[right:N-1] are sorted

        int i = 0;//iterate in A[0:left]
        int j = right;//iterate in A[right:N-1]
        int res = std::min(right, N-left-1);//edge cases: either remove A[0:right-1] or A[left+1:N-1]
        while (i <= left && j <= N-1)
        {
            if (A[j] >= A[i])
            {
                res = std::min(res, j-i-1);//can remove A[i+1:j-1], and tighten the window
                ++i;
            }
            else
                ++j;//cannot remove any points, just loose the window
        }
        return res;
    }
};
#endif
