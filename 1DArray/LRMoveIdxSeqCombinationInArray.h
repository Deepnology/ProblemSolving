#ifndef _L_R_MOVE_IDX_SEQ_COMBINATION_IN_ARRAY_H
#define _L_R_MOVE_IDX_SEQ_COMBINATION_IN_ARRAY_H
#include "Debug.h"
/*
Leetcode: Number of Ways to Stay in the Same Place After Some Steps
You have a pointer at index 0 in an array of size arrLen.
At each step, you can move 1 position to the left, 1 position to the right in the array
 or stay in the same place  (The pointer should not be placed outside the array at any time).
Given two integers steps and arrLen, return the number of ways such that your pointer still at index 0 after exactly steps steps.
Since the answer may be too large, return it modulo 10^9 + 7.
Example 1:
Input: steps = 3, arrLen = 2
Output: 4
Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
Right, Left, Stay
Stay, Right, Left
Right, Stay, Left
Stay, Stay, Stay
Example 2:
Input: steps = 2, arrLen = 4
Output: 2
Explanation: There are 2 differents ways to stay at index 0 after 2 steps
Right, Left
Stay, Stay
Example 3:
Input: steps = 4, arrLen = 2
Output: 8

see also LMoveIdxSeqCombinationInMatrix.h
 */
class LRMoveIdxSeqCombinationInArray
{
public:
    const int MOD=1e9+7;

    int DP2D(int steps, int arrLen)
    {
        int maxIdx = std::min(arrLen, steps); //time limit exceeded w/o this condition
        std::vector<std::vector<int>> dp(maxIdx, std::vector<int>(steps+1, 0));
        dp[0][1] = 1; dp[1][1] = 1; //init all cases when remaining steps==1
        for (int step = 2; step <= steps; ++step)
        {
            for (int idx = 0; idx < maxIdx; ++idx)
            {
                int stay = dp[idx][step-1];
                int left = (idx>0?dp[idx-1][step-1]:0);
                int right = (idx<maxIdx-1?dp[idx+1][step-1]:0);
                dp[idx][step] = ((stay + left)%MOD + right)%MOD;
            }
        }
        return dp[0][steps];
    }


    //O(3^steps) time w/o memo
    //O(steps^2) tiem w/ memo
    int Recur(int steps, int arrLen)
    {
        std::vector<std::vector<int>> memo(arrLen, std::vector<int>(steps+1, -1));
        return recur(0, steps, arrLen, memo);
    }
private:
    int recur(int idx, int steps, int N, std::vector<std::vector<int>> & memo)
    {
        if (idx == 0 && steps == 0)
            return 1;
        if (idx < 0 || idx == N || steps == 0 || idx > steps) //note: idx>steps: idx will never return 0
            return 0;
        if (memo[idx][steps] != -1)
            return memo[idx][steps];

        return memo[idx][steps] = ((recur(idx, steps-1, N, memo)%MOD + recur(idx-1, steps-1, N, memo))%MOD + recur(idx+1, steps-1, N, memo))%MOD;
    }
};
#endif
