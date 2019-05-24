#ifndef _KTH_SMALLEST_NUM_IN_MISSING_RANGE_OF_SORTED_ARR_H
#define _KTH_SMALLEST_NUM_IN_MISSING_RANGE_OF_SORTED_ARR_H
#include "Debug.h"
/*
https://www.1point3acres.com/bbs/thread-525374-1-1.html
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
        int res = nums[i] + k >= nums[j] ? -1 : nums[i] + k;

        std::cout << "KthSmallestNumInMissingRangeOfSortedArr for " << kBefore << "th in [" << Debug::ToStr1D<int>()(nums) << "]: " << res << std::endl;
        return res;
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
