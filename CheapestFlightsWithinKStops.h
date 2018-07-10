#ifndef _CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H
#define _CHEAPEST_FLIGHTS_WITHIN_K_STOPS_H
#include "Debug.h"
/*
Leetcode: Cheapest Flights Within K Stops
There are n cities connected by m flights.
Each fight starts from city u and arrives at v with a price w.
Now given all the cities and fights, together with starting city src and the destination dst,
your task is to find the cheapest price from src to dst with up to k stops.
If there is no such route, output -1.
 */
class CheapestFlightsWithinKStops
{
public:
    CheapestFlightsWithinKStops(){}

    struct Greater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            return a[0] > b[0];
        }
    };
    int BFS(int n, const std::vector<std::vector<int>> & flights, int src, int dst, int K)
    {
        std::unordered_map<int,std::unordered_map<int,int>> directed;
        for (const auto & p : flights)
            directed[p[0]][p[1]] = p[2];
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;//<total price,total stops,vertex>
        minHeap.push({0,0,src});
        while (!minHeap.empty())
        {
            auto cur = minHeap.top(); minHeap.pop();
            //std::cout << cur[2] << std::endl;
            if (cur[2] == dst) return cur[0];
            if (cur[1] <= K && directed.count(cur[2]))
            {
                for (const auto & p : directed[cur[2]])
                {
                    //note: p might be repeated visited !!!
                    minHeap.push({cur[0]+p.second,cur[1]+1,p.first});
                }
            }
        }
        return -1;
    }

    int BellmanFord(int n, const std::vector<std::vector<int>> & flights, int src, int dst, int K)
    {
        std::vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        //relax all edges for K times
        for (int relaxCount = 0; relaxCount < K+1; ++relaxCount)
        {
            std::vector<int> nxt(dist);
            for (const auto & edge : flights)
                if (dist[edge[0]] != INT_MAX && dist[edge[0]] + edge[2] < nxt[edge[1]])
                {
                    nxt[edge[1]] = dist[edge[0]] + edge[2];
                }
            std::swap(dist,nxt);
        }
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }

    void Test(int n, const std::vector<std::vector<int>> & flights, int src, int dst, int K)
    {
        int bfs = BFS(n, flights, src, dst, K);
        int bf = BellmanFord(n, flights, src, dst, K);
        Debug::Print2D<int>()(flights, false);
        std::cout << "CheapestFlightsWithinKStops BFS and BellmanFord for above flights from " << src << " to " << dst << " within " << K << " stops: " << bfs << "," << bf << std::endl;
    }
};
/*
[rY][cX]
Row#0	= 0, 1, 100
Row#1	= 1, 2, 100
Row#2	= 0, 2, 500

CheapestFlightsWithinKStops BFS and BellmanFord for above flights from 0 to 2 within 1 stops: 200,200
[rY][cX]
Row#0	= 0, 1, 100
Row#1	= 1, 2, 100
Row#2	= 0, 2, 500

CheapestFlightsWithinKStops BFS and BellmanFord for above flights from 0 to 2 within 0 stops: 500,500
 */
#endif
