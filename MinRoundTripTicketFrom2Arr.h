#ifndef _MIN_ROUND_TRIP_TICKET_FROM_2_ARR_H
#define _MIN_ROUND_TRIP_TICKET_FROM_2_ARR_H
#include "Debug.h"
/*
https://www.1point3acres.com/bbs/thread-451737-1-1.html
Facebook
Given 2 same sized array representing ticket prices of departure and return on each day.
Find 2 indices i and j from the departure array and return array such that the round trip ticket prices are smallest.
0 <= i <= j <= N
 */
class MinRoundTripTicketFrom2Arr
{
public:
    MinRoundTripTicketFrom2Arr(){}

    std::pair<int,int> ThreeScans(std::vector<int> && Depart, std::vector<int> && Return)
    {
        int N = Depart.size();
        std::vector<std::pair<int,int>> leftMin(N);
        for (int i = 0; i < N; ++i)
        {
            leftMin[i] = i==0 ? std::pair<int,int>({Depart[i],i}) : leftMin[i-1].first < Depart[i] ? leftMin[i-1] : std::pair<int,int>({Depart[i],i});
        }
        std::vector<std::pair<int,int>> rightMin(N);
        for (int i = N-1; i >= 0; --i)
        {
            rightMin[i] = i==N-1 ? std::pair<int,int>({Return[i],i}) : rightMin[i+1].first < Return[i] ? rightMin[i+1] : std::pair<int,int>({Return[i],i});
        }
        std::pair<int,int> resP(-1,-1);
        int res = INT_MAX;
        for (int i = 0; i < N; ++i)
        {
            if (leftMin[i].first+rightMin[i].first < res)
            {
                res = leftMin[i].first+rightMin[i].first;
                resP = {leftMin[i].second, rightMin[i].second};
            }
        }

        std::cout << "MinRoundTripTicketFrom2Arr ThreeScans for [" << Debug::ToStr1D<int>()(Depart) << "], [" << Debug::ToStr1D<int>()(Return) << "]: (" << resP.first << "," << resP.second << ") " << res << std::endl;
        return resP;
    }
};
#endif
