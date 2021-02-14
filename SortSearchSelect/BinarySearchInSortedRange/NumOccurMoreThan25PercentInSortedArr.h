#ifndef _NUM_OCCUR_MORE_THAN_25_PERCENT_IN_SORTED_ARR_H
#define _NUM_OCCUR_MORE_THAN_25_PERCENT_IN_SORTED_ARR_H
#include "Debug.h"
/*
Leetcode: Element Appearing More Than 25% In Sorted Array
Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time.
Return that integer.
Example 1:
Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6
Constraints:
1 <= arr.length <= 10^4
0 <= arr[i] <= 10^5
 */
class NumOccurMoreThan25PercentInSortedArr
{
public:
    int BinarySearch(std::vector<int>& arr)
    {
        int N = arr.size();

        for (int i : {N/4, N/2, N*3/4})
        {
            auto lb = std::lower_bound(arr.begin(), arr.end(), arr[i]);
            auto ub = std::upper_bound(arr.begin(), arr.end(), arr[i]);
            if ((ub-lb)*4>N)
                return arr[i];
        }
        return -1;
    }
};
#endif
