#ifndef _MAX_NUM_PARTITIONS_TO_SORT_H
#define _MAX_NUM_PARTITIONS_TO_SORT_H
#include "Debug.h"
/*
Leetcode: Max Chunks to Make Sorted
Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.
After concatenating them, the result equals the sorted array.
What is the most number of chunks we could have made?
Example 1:
Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
Example 2:
Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
Leetcode: Max Chunks to Make Sorted II
Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.
After concatenating them, the result equals the sorted array.
What is the most number of chunks we could have made?
Example 1:
Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
Example 2:
Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
 */
class MaxNumPartitionsToSort // and then make array sorted
{
public:
    MaxNumPartitionsToSort(){}

    int FromIdxSeqNums(const std::vector<int> & arr)
    {
        int N = arr.size();
        int curMax = -1;
        int count = 0;
        for (int i = 0; i < N; ++i)
        {
            curMax = std::max(curMax, arr[i]);
            if (curMax == i)
                ++count;
        }
        std::cout << "MaxNumPartitionsToSort FromIdxSeqNums for [" << Debug::ToStr1D<int>()(arr) << "]: " << count << std::endl;
        return count;
    }
    int WithDuplicates(const std::vector<int> & arr)
    {
        int N = arr.size();
        std::vector<int> maxLeft(N);
        for (int i = 0; i < N; ++i)
            maxLeft[i] = i==0? arr[i] : std::max(arr[i],maxLeft[i-1]);
        std::vector<int> minRight(N);
        for (int i = N-1; i >= 0; --i)
            minRight[i] = i==N-1? arr[i] : std::min(arr[i],minRight[i+1]);
        int res = 0;
        for (int i = 0; i < N-1; ++i)
            if (maxLeft[i] <= minRight[i+1])
                ++res;
        std::cout << "MaxNumPartitionsToSort WithDuplicates for [" << Debug::ToStr1D<int>()(arr) << "]: " << res+1 << std::endl;
        return res + 1;
    }
};
/*
MaxNumPartitionsToSort FromIdxSeqNums for [1, 0, 2, 3, 4]: 4
MaxNumPartitionsToSort WithDuplicates for [2, 1, 3, 4, 4]: 4
 */
#endif
