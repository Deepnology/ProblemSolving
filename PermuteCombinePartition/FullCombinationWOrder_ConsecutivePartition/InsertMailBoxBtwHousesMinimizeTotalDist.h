#ifndef _INSERT_MAIL_BOX_BTW_HOUSES_MINIMIZE_TOTAL_DIST_H
#define _INSERT_MAIL_BOX_BTW_HOUSES_MINIMIZE_TOTAL_DIST_H
#include "Debug.h"
/*
Leetcode: Allocate Mailboxes
Given the array houses and an integer k. where houses[i] is the location of the ith house along a street, your task is to allocate k mailboxes in the street.
Return the minimum total distance between each house and its nearest mailbox.
The answer is guaranteed to fit in a 32-bit signed integer.

see also MinimizeMaxDistBtwGasStationAddKMore.h
 */
class InsertMailBoxBtwHousesMinimizeTotalDist
{
public:
    int DFS(std::vector<int> & houses, int k)
    {
        int N = houses.size();
        std::sort(houses.begin(), houses.end());
        std::vector<std::vector<int>> cost(N, std::vector<int>(N, 0));
        for (auto i = 0; i < N; ++i)//O(N^3) time
            for (auto j = 0; j < N; ++j)
                for (auto t = i; t <= j; ++t)
                    cost[i][j] += std::abs(houses[(i+j)/2] - houses[t]);
        //the total cost of placing a mailbox in between i and j
        std::vector<std::vector<int>> memo(N+1, std::vector<int>(k+1, -1));
        return recur(houses, 0, k, memo, cost);//O(N^2*k) time
    }
    int recur(std::vector<int> & houses, int curIdx, int curK, std::vector<std::vector<int>> & memo, std::vector<std::vector<int>> & cost)
    {
        int N = houses.size();
        if (curIdx == N && curK == 0) return 0;
        if (curIdx == N || curK == 0) return INT_MAX;
        if (memo[curIdx][curK] != -1) return memo[curIdx][curK];

        long long minDist = INT_MAX;
        for (auto i = curIdx; i < N; ++i)
            minDist = std::min(minDist, (long long)cost[curIdx][i] + (long long)recur(houses, i+1, curK-1, memo, cost));

        return memo[curIdx][curK] = (int)minDist;
    }
};
#endif
