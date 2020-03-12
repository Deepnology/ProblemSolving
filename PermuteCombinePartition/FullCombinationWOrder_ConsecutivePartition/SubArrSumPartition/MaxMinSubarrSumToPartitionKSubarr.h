#ifndef _MAX_MIN_SUBARR_SUM_TO_PARTITION_K_SUBARR_H
#define _MAX_MIN_SUBARR_SUM_TO_PARTITION_K_SUBARR_H
#include "Debug.h"
/*
Leetcode: Divide Chocolate
You have one chocolate bar that consists of some chunks.
Each chunk has its own sweetness given by the array sweetness.
You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, each piece consists of some consecutive chunks.
Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.
Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.
Example 1:
Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
Example 2:
Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.
Example 3:
Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]

see also PaintersPartitionFairWorkload.h
 */
class MaxMinSubarrSumToPartitionKSubarr
{
public:
    int BinarySearch(const std::vector<int> & sweetness, int K)
    {
        ++K;
        int left = *std::min_element(sweetness.begin(),sweetness.end());
        int right = std::accumulate(sweetness.begin(),sweetness.end(),0);
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            bool valid = canPartitionAtLeastKSubarr(sweetness, K, mid);
            if (valid)
                left=mid+1;
            else
                right = mid-1;

        }
        std::cout << "MaxMinSubarrSumToPartitionKSubarr BinarySearch for [" << Debug::ToStr1D<int>()(sweetness) << "], k=" << K << ": " << right << std::endl;
        return right;
    }
private:
    bool canPartitionAtLeastKSubarr(const std::vector<int> & v, int K, int limit)
    {
        int curK = 0;
        int curSum = 0;
        int N = v.size();
        int i = 0;
        /*
        for (; i < N; ++i)
        {
            curSum+=v[i];
            if (curSum>=limit)
            {
                curSum=0;
                ++curK;
            }
        }
        return curK >= K;
        */

        while (i < N)
        {
            curSum += v[i++];
            if (curSum >= limit)
            {
                curSum = 0;
                ++curK;
            }
        }
        return curK >= K;
    }
};
/*
MaxMinSubarrSumToPartitionKSubarr BinarySearch for [1, 2, 3, 4, 5, 6, 7, 8, 9], k=6: 6
 */
#endif
