#ifndef _BUS_ROUTES_H
#define _BUS_ROUTES_H
#include "Debug.h"
/*
Leetcode: Bus Routes
We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever.
For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.
We start at bus stop S (initially not on a bus), and we want to go to bus stop T.
Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.
Example:
Input:
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
Output: 2
Explanation:
The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
 */
class BusRoutes
{
public:
    BusRoutes(){}

    int BFS_NumOfBuses(const std::vector<std::vector<int>> & routes, int S, int T)
    {
        Debug::Print2D<int>()(routes, false);

        std::unordered_map<int,std::unordered_set<int>> stopToRoute;
        int N = routes.size();
        for (int i = 0; i < N; ++i)
        {
            int M = routes[i].size();
            for (int j = 0; j < routes[i].size(); ++j)
                stopToRoute[routes[i][j]].insert(i);
        }
        std::unordered_set<int> visitStop;
        std::unordered_set<int> visitRoute;
        std::queue<std::pair<int,int>> que;
        que.push({S, 0});
        visitStop.insert(S);
        while (!que.empty())
        {
            auto p = que.front(); que.pop();
            if (p.first == T)
            {
                std::cout << "BusRoutes BFS_NumOfBuses for above bus routes from " << S << " to " << T << ": " << p.second << std::endl;
                return p.second;
            }
            for (auto & r : stopToRoute[p.first])
            {
                if (visitRoute.count(r))
                    continue;
                for (auto & s : routes[r])
                {
                    if (visitStop.count(s))
                        continue;
                    visitStop.insert(s);
                    que.push({s, p.second+1});
                }
                visitRoute.insert(r);
            }
        }
        std::cout << "BusRoutes BFS_NumOfBuses for above bus routes from " << S << " to " << T << ": -1" << std::endl;
        return -1;
    }
};
/*
[rY][cX]
Row#0	= 1, 2, 7
Row#1	= 3, 6, 7

BusRoutes BFS_NumOfBuses for above bus routes from 1 to 6: 2
 */
#endif
