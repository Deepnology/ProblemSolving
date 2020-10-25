#ifndef _COUNT_PAIRS_W_PAIR_SUM_DIVISIBLE_BY_TGT_H
#define _COUNT_PAIRS_W_PAIR_SUM_DIVISIBLE_BY_TGT_H
#include "Debug.h"
/*
Amazon OA
Leetcode: Pairs of Songs With Total Durations Divisible by 60
In a list of songs, the i-th song has a duration of time[i] seconds.
Return the number of pairs of songs for which their total duration in seconds is divisible by 60.
Formally, we want the number of indices i, j such that i < j with (time[i] + time[j]) % 60 == 0.
Example 1:
Input: [30,20,150,100,40]
Output: 3
Explanation: Three pairs have a total duration divisible by 60:
(time[0] = 30, time[2] = 150): total duration 180
(time[1] = 20, time[3] = 100): total duration 120
(time[1] = 20, time[4] = 40): total duration 60
Example 2:
Input: [60,60,60]
Output: 3
Explanation: All three pairs have a total duration of 120, which is divisible by 60.
 */
class CountPairsWPairSumDivisibleByTgt
{
public:
    int UseHashMap(std::vector<int> & time) //similar to 2Sum
    {
        int N = time.size();
        std::unordered_map<int,int> count;//<time%60, count>
        int res = 0;
        for (auto & t : time)
        {
            int t1 = t % 60;
            res += (t1==0 ? count[t1] : count[60-t1]);
            ++count[t1];
        }
        return res;
    }
};
#endif
