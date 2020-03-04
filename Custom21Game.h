#ifndef _CUSTOM_21_GAME_H
#define _CUSTOM_21_GAME_H
#include "Debug.h"
/*
Leetcode: New 21 Game
Alice plays the following game, loosely based on the card game "21".
Alice starts with 0 points, and draws numbers while she has less than K points.
During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.
Each draw is independent and the outcomes have equal probabilities.
Alice stops drawing numbers when she gets K or more points.
What is the probability that she has N or less points?
Example 1:
Input: N = 10, K = 1, W = 10
Output: 1.00000
Explanation:  Alice gets a single card, then stops.
Example 2:
Input: N = 6, K = 1, W = 10
Output: 0.60000
Explanation:  Alice gets a single card, then stops.
In 6 out of W = 10 possibilities, she is at or below N = 6 points.
Example 3:
Input: N = 21, K = 17, W = 10
Output: 0.73278
Note:
0 <= K <= N <= 10000
1 <= W <= 10000
 */
class Custom21Game
{
public:
    Custom21Game(){}

    double DP(int tgt, int thd, int maxNum) //N, K, W
    {
        /*
        dp[i] represents the total probability to get points i
        dp[i] = dp[1] * 1/W + dp[2] * 1/W + dp[3] * 1/W + ... dp[i-2] * 1/W + dp[i-1] * 1/W
        So dp[i] = (dp[1] + dp[2] + ... + dp[i - 1]) / W = Wsum / W
        Conditional probability: keep a window with size K (assume K = 10), the probability of getting point i is the sum of probability from point i - 10 to i, point i - 9 to i, ... , i -1 to i.
        Since every card has equal probability, the probability to get any one of cards is 1/10.
        So the total probability of dp[i] is sum of all conditional probability.
        Once i is greater than or equal to K, we can accumulate probability to final result
        */
        if (thd == 0 || tgt >= thd + maxNum)
            return 1.0;
        double res = 0;
        double windowSum = 1.0;
        std::vector<double> dp(tgt+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= tgt; ++i)
        {
            dp[i] = windowSum / maxNum;
            if (i < thd)// when points is less than K, all previous card could go to current i by only drawing one card
                windowSum += dp[i];
            else// when points is equal to or more than K, all probability will be accumulated to results
                res += dp[i];

            if (i - maxNum >= 0)// when i is over than maxNum, then we need to move the window
                windowSum -= dp[i - maxNum];
        }

        std::cout << "Custom21Game DP for tgt=" << tgt << ", thd=" << thd << ", maxNum=" << maxNum << ": " << res << std::endl;
        return res;
    }
};
/*
Custom21Game DP for tgt=21, thd=17, maxNum=10: 0.732778
 */
#endif
