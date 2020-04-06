#ifndef _MIN_SWAP_TO_GROUP_1_FROM_01_ARR_H
#define _MIN_SWAP_TO_GROUP_1_FROM_01_ARR_H
#include "Debug.h"
/*
Leetcode: Min Swap to Group all 1's together
Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.
Example 1:
Input: [1,0,1,0,1]
Output: 1
Explanation:
There are 3 ways to group all 1's together:
[1,1,1,0,0] using 1 swap.
[0,1,1,1,0] using 2 swaps.
[0,0,1,1,1] using 1 swap.
The minimum is 1.
Example 2:
Input: [0,0,0,1,0]
Output: 0
Explanation:
Since there is only one 1 in the array, no swaps needed.
Example 3:
Input: [1,0,1,0,1,0,0,1,1,0,1]
Output: 3
Explanation:
One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].
 */
class MinSwapToGroup1From01Arr
{
public:
    int SlideWindow(std::vector<int> && v)
    {
        int total1 = 0;
        int N = v.size();
        for (int i = 0; i < N; ++i)
            if (v[i]==1)
                ++total1;
        if (total1 == 0) return 0;
        int k = total1;//window size is total count of 1
        int count1 = 0;//count of 1 in window
        int minCount0 = N;//min count of 0 in window
        for (int i = 0; i < N; ++i)
        {
            if (v[i]==1)
                ++count1;
            if (i - k + 1 >= 0)//window begin = i-k+1
            {
                int count0 = k - count1;
                minCount0 = std::min(minCount0, count0);
                if (v[i-k+1]==1)
                    --count1;
            }
        }

        std::cout << "MinSwapToGroup1From01Arr SlideWindow for [" << Debug::ToStr1D<int>()(v) << "]: " << minCount0 << std::endl;
        return minCount0;
    }
};
/*
MinSwapToGroup1From01Arr SlideWindow for [1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1]: 3
 */
#endif
