#ifndef _SUBTRACT_NUM_BY_ITS_DIVISOR_GAME_H
#define _SUBTRACT_NUM_BY_ITS_DIVISOR_GAME_H
#include "Debug.h"
/*
Leetcode: Divisor Game
Alice and Bob take turns playing a game, with Alice starting first.
Initially, there is a number N on the chalkboard.
On each player's turn, that player makes a move consisting of:
Choosing any x with 0 < x < N and N % x == 0.
Replacing the number N on the chalkboard with N - x.
Also, if a player cannot make a move, they lose the game.
Return True if and only if Alice wins the game, assuming both players play optimally.
Example 1:
Input: 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.
Example 2:
Input: 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.
 */
class SubtractNumByItsDivisorGame
{
public:
    bool Recur(int N)
    {
        std::vector<int> memo(N+1, -1);
        return recur(N, memo);
    }
    bool recur(int cur, std::vector<int> & memo)
    {
        if (memo[cur] != -1) return memo[cur];
        if (cur == 1) return memo[cur] = 0;
        for (auto i = 1; i*i <= cur; ++i)
        {
            if (cur % i != 0) continue;
            bool other = recur(cur-i, memo) || recur(cur-cur/i, memo);
            if (!other) return memo[cur] = 1;
        }
        return memo[cur] = 0;
    }
};
#endif
