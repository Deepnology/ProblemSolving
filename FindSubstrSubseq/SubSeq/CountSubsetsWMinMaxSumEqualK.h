#ifndef _COUNT_SUBSETS_W_MIN_MAX_SUM_EQUAL_K_H
#define _COUNT_SUBSETS_W_MIN_MAX_SUM_EQUAL_K_H
#include "Debug.h"
/*
https://leetcode.com/discuss/interview-experience/275785/Facebook-Phone-Interview
Input:

Given an array A of
-positive
-sorted
-no duplicate
-integer

A positive integer k

Output:

Count of all such subsets of A,
Such that for any such subset S,
Min(S) + Max(S) = k
subset should contain atleast two elements

Backtracking approach to get subsets
Get min and max of subset
Add min and max and put them in Hashmap (or update the count)
repeat this process for all subsets
search for k in hashmap and return count of k
input: {1,2,3,4,5}, k = 5
=>
count = 5
{1,4},{2,3},{1,2,4},{1,2,3,4},{1,3,4}
*/
class CountSubsetsWMinMaxSumEqualK
{
public:
    CountSubsetsWMinMaxSumEqualK(){}

    int TwoPtrsFromSortedArr(std::vector<int> && sorted, int k) //sorted contains all distinct integers
    {
        int N = sorted.size();
        int i = 0;
        int j = N-1;
        int count = 0;
        while (i < j)
        {
            if (sorted[i] + sorted[j] == k)
            {
                count += (1 << (j-i-1));
                std::cout << "NumOfSubsetsIn [" << sorted[i] << "," << sorted[j] << "]: " << (1<<(j-i-1)) << std::endl;
                //num of subsets of a window that include at least both ends = 2^(windowLen-2)
                //ex: [1,2,3,4,5]: [1,2,3,4,5],[1,2,3,5],[1,2,4,5],[1,3,4,5],[1,2,5],[1,3,5],[1,4,5],[1,5], 2^3=8
                ++i;
                --j;
            }
            else if (sorted[i] + sorted[j] < k)
                ++i;
            else
                --j;
        }

        std::cout << "CountSubsetsWMinMaxSumEqualK TwoPtrsFromSortedArr for k=" << k << " from [" << Debug::ToStr1D<int>()(sorted) << "]: " << count << std::endl;
        return count;
    }
};
/*
NumOfSubsetsIn [1,5]: 8
NumOfSubsetsIn [2,4]: 2
CountSubsetsWMinMaxSumEqualK TwoPtrsFromSortedArr for k=6 from [1, 2, 3, 4, 5]: 10
 */
#endif
