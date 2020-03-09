#ifndef _COUNT_PAIR_W_SUM_DIVISIBLE_BY_K_H
#define _COUNT_PAIR_W_SUM_DIVISIBLE_BY_K_H
#include "Debug.h"
/*
Leetcode: Pairs of Songs With Total Durations Divisible by 60
 In a list of songs, the i-th song has a duration of time[i] seconds.
Return the number of pairs of songs for which their total duration in seconds is divisible by 60.
Formally, we want the number of indices i < j with (time[i] + time[j]) % 60 == 0.
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
class CountPairWSumDivisibleByK
{
public:
    int HashMap(std::vector<int> && time, int K = 60)
    {
        int N = time.size();
        std::unordered_map<int,int> count;//<time%K, count>
        int res = 0;
        for (auto & t : time)
        {
            int t1 = t % K;
            res += (t1==0 ? count[t1] : count[K-t1]);
            ++count[t1];
        }

        std::cout << "CountPairWSumDivisibleByK HashMap for [" << Debug::ToStr1D<int>()(time) << "], K=" << K << ": " << res << std::endl;
        return res;
    }
};
/*
CountPairWSumDivisibleByK HashMap for [30, 20, 150, 100, 40], K=60: 3
 */
#endif
