#ifndef _KTH_SMALLEST_NUM_IN_MISSING_RANGE_OF_SORTED_ARR_H
#define _KTH_SMALLEST_NUM_IN_MISSING_RANGE_OF_SORTED_ARR_H
#include "Debug.h"
/*
Leetcode: Missing Element in Sorted Array
Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.
Example 1:
Input: A = [4,7,9,10], K = 1
Output: 5
Explanation:
The first missing number is 5.
Example 2:
Input: A = [4,7,9,10], K = 3
Output: 8
Explanation:
The missing numbers are [5,6,8,...], hence the third missing number is 8.
Example 3:
Input: A = [1,2,4], K = 3
Output: 6
Explanation:
The missing numbers are [3,5,6,7,...], hence the third missing number is 6.

Leetcode: Kth Missing Positive Number
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
Find the kth positive integer that is missing from this array.
Example 1:
Input: arr = [2,3,4,7,11], k = 5
Output: 9
Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
Example 2:
Input: arr = [1,2,3,4], k = 2
Output: 6
Explanation: The missing positive integers are [5,6,7,...]. The 2nd missing positive integer is 6.
 */
class KthSmallestNumInMissingRangeOfSortedArr
{
public:
    KthSmallestNumInMissingRangeOfSortedArr(){}

    int BinarySearch(std::vector<int> && nums, int k)
    {
        int kBefore = k;
        int N = nums.size();
        int i = 0, j = N - 1;

        while (i + 1 < j) //keep 3 entries in between
        {
            int mid = (i + j) / 2;
            int missing = (nums[mid] - nums[i]) - (mid - i); //count of missing nums in range (i:mid)
            if (missing >= k) //too big: go left
                j = mid;
            else //too small: go right
            {
                i = mid;
                k -= missing;
            }
        }
        //now i+1==j
        //int res = nums[i] + k >= nums[j] ? -1 : nums[i] + k;
        int res = nums[i] + k >= nums[j] ? nums[i]+k+1 : nums[i] + k;

        std::cout << "KthSmallestNumInMissingRangeOfSortedArr for " << kBefore << "th in [" << Debug::ToStr1D<int>()(nums) << "]: " << res << std::endl;
        return res;
    }
};
class KthSmallestMissingPositiveNumInSortedArr
{
public:
    int BinarySearch(std::vector<int> & nums, int k)
    {
        int N = nums.size();
        int i = 0, j = N-1;

        while (i + 1 < j) //keep 3 entries in between
        {
            int mid = (i + j) / 2;
            int missing = nums[mid] - (mid+1); //count of missing nums before num[mid]
            if (missing >= k) //too big: go left
                j = mid;
            else //too small: go right
                i = mid;
        }
        //now i+1>=j: either i+1==j or i==j
        if (nums[j]-(j+1) < k) return k - (nums[j]-(j+1)) + nums[j];//kth num is on j's right
        if (nums[i]-(i+1) < k) return k - (nums[i]-(i+1)) + nums[i];//kth num is in between i and j
        return k;//kth num is on i's left
    }
};
/*
KthSmallestNumInMissingRangeOfSortedArr for 1th in [2, 4, 7, 8, 9, 15]: 3
KthSmallestNumInMissingRangeOfSortedArr for 2th in [2, 4, 7, 8, 9, 15]: 5
KthSmallestNumInMissingRangeOfSortedArr for 3th in [2, 4, 7, 8, 9, 15]: 6
KthSmallestNumInMissingRangeOfSortedArr for 4th in [2, 4, 7, 8, 9, 15]: 10
KthSmallestNumInMissingRangeOfSortedArr for 5th in [2, 4, 7, 8, 9, 15]: 11
KthSmallestNumInMissingRangeOfSortedArr for 6th in [2, 4, 7, 8, 9, 15]: 12
KthSmallestNumInMissingRangeOfSortedArr for 7th in [2, 4, 7, 8, 9, 15]: 13
KthSmallestNumInMissingRangeOfSortedArr for 8th in [2, 4, 7, 8, 9, 15]: 14
KthSmallestNumInMissingRangeOfSortedArr for 9th in [2, 4, 7, 8, 9, 15]: -1
 */
#endif
