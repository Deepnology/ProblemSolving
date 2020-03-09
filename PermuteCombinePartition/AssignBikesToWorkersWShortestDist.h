#ifndef _ASSIGN_BIKES_TO_WORKERS_W_SHORTEST_DIST_H
#define _ASSIGN_BIKES_TO_WORKERS_W_SHORTEST_DIST_H
#include "Debug.h"
/*
Leetcode: Campus Bikes
On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M.
Each worker and bike is a 2D coordinate on this grid.
Our goal is to assign a bike to each worker.
Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker.
(If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index;
 if there are multiple ways to do that, we choose the pair with the smallest bike index).
We repeat this process until there are no available workers.
The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.

Leetcode: Campus Bikes II
On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M.
Each worker and bike is a 2D coordinate on this grid.
We assign one unique bike to each worker so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.
The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.
Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.
 */
class AssignBikesToWorkersWShortestDist
{
public:
    //Campus Bikes
    struct Greater
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            if (a[0] != b[0]) return a[0] > b[0];
            if (a[1] != b[1]) return a[1] > b[1];
            return a[2] > b[2];
        }
    };
    std::vector<int> ShortestPairDistFirst_MinHeap(std::vector<std::vector<int>> && workers, std::vector<std::vector<int>> && bikes)
    {
        //minHeap: O(W*B*log(W*B)) time
        int N = workers.size();
        int M = bikes.size();
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Greater> minHeap;//<wbDist, wbPair>
        for (int w = 0; w < N; ++w)
            for (int b = 0; b < M; ++b)
            {
                int dist = manhattan(workers[w], bikes[b]);
                minHeap.push({dist,w,b});
            }
        std::unordered_set<int> visitWorkers;
        std::unordered_set<int> visitBikes;
        std::vector<int> res(N);
        while (visitWorkers.size() < N)
        {
            auto v = minHeap.top(); minHeap.pop();
            int dist = v[0];
            int w = v[1];
            int b = v[2];
            if (!visitWorkers.count(w) && !visitBikes.count(b))
            {
                visitWorkers.insert(w);
                visitBikes.insert(b);
                res[w] = b;
            }
        }
        std::cout << "AssignBikesToWorkersWShortestDist ShortestPairDistFirst_MinHeap for w=[" << Debug::ToStr1D<int>()(workers) << "], b=[" << Debug::ToStr1D<int>()(bikes) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
    std::vector<int> ShortestPairDistFirst_BucketSort(std::vector<std::vector<int>> && workers, std::vector<std::vector<int>> && bikes)
    {
        //bucketSort: O(rangeOfDist + W*B) time
        int N = workers.size();
        int M = bikes.size();
        std::vector<std::vector<std::vector<int>>> buckets(2001,std::vector<std::vector<int>>());//buckets[i]: list of (w,b) pairs with dist=i
        for (int w = 0; w < N; ++w)
            for (int b = 0; b < M; ++b)
            {
                int dist = manhattan(workers[w], bikes[b]);
                buckets[dist].push_back({w,b});
            }
        std::unordered_set<int> visitWorkers;
        std::unordered_set<int> visitBikes;
        std::vector<int> res(N);
        for (int d = 0; d <= 2000 && visitWorkers.size() < N; ++d)
        {
            for (int p = 0; p < buckets[d].size() && visitWorkers.size() < N; ++p)
            {
                int w = buckets[d][p][0];
                int b = buckets[d][p][1];
                if (!visitWorkers.count(w) && !visitBikes.count(b))
                {
                    visitWorkers.insert(w);
                    visitBikes.insert(b);
                    res[w] = b;
                }
            }
        }
        std::cout << "AssignBikesToWorkersWShortestDist ShortestPairDistFirst_BuckSort for w=[" << Debug::ToStr1D<int>()(workers) << "], b=[" << Debug::ToStr1D<int>()(bikes) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }



    //Campus Bikes II
    struct Greater2
    {
        bool operator()(const std::pair<int,int> & a, const std::pair<int,int> & b) const
        {
            return a.first > b.first;
        }
    };
    int MinAllPairDistSums_DFS(std::vector<std::vector<int>> && workers, std::vector<std::vector<int>> && bikes)
    {
        //DFS: O(B*(B-1)*(B-2)*....for W times)=O(B!/(B-W)!)=O(B^W) time
        int res = INT_MAX;
        int usedBike = 0;
        DFS(workers, bikes, 0, usedBike, 0, res);
        std::cout << "AssignBikesToWorkersWShortestDist MinAllPairDistSums_DFS for w=[" << Debug::ToStr1D<int>()(workers) << "], b=[" << Debug::ToStr1D<int>()(bikes) << "]: " << res << std::endl;
        return res;
    }
    void DFS(std::vector<std::vector<int>> & workers, std::vector<std::vector<int>> & bikes, int w, int usedBike, int sumDist, int & res)
    {
        int N = workers.size();
        if (w == N)
        {
            res = std::min(res, sumDist);
            return;
        }
        int M = bikes.size();
        //enumerate all un-used bikes for w
        for (int b = 0; b < M; ++b)
        {
            if ((usedBike & (1<<b)) == 0)
            {
                DFS(workers, bikes, w+1, (usedBike|(1<<b)), sumDist + manhattan(workers[w],bikes[b]), res);
            }
        }
    }
    int MinAllPairDistSums_DFS_Memo(std::vector<std::vector<int>> && workers, std::vector<std::vector<int>> && bikes)
    {
        //DFS w/ memo
        int usedBike = 0;
        std::unordered_map<int,int> memo;
        int res = DFS(workers, bikes, 0, usedBike, memo);
        std::cout << "AssignBikesToWorkersWShortestDist MinAllPairDistSums_DFS_Memo for w=[" << Debug::ToStr1D<int>()(workers) << "], b=[" << Debug::ToStr1D<int>()(bikes) << "]: " << res << std::endl;
        return res;
    }
    int DFS(std::vector<std::vector<int>> & workers, std::vector<std::vector<int>> & bikes, int w, int usedBike, std::unordered_map<int,int> & memo)
    {
        int N = workers.size();
        if (w == N)
            return 0;
        int state = (w<<10) | usedBike;
        if (memo.count(state))
            return memo[state];
        int minDistSum = INT_MAX;
        int M = bikes.size();
        //enumerate all un-used bikes for w
        for (int b = 0; b < M; ++b)
        {
            if ((usedBike & (1<<b)) == 0)
            {
                int dist = manhattan(workers[w], bikes[b]);
                minDistSum = std::min(minDistSum, dist + DFS(workers, bikes, w+1, (usedBike|(1<<b)), memo));
            }
        }
        return memo[state] = minDistSum;
    }
    int MinAllPairDistSums_BFS_MinHeap(std::vector<std::vector<int>> && workers, std::vector<std::vector<int>> && bikes)
    {
        //BFS w/ minHeap
        //combinations+permutations C = B! / (B-W)!
        //O(C log C) time
        int N = workers.size();
        int M = bikes.size();
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Greater2> minHeap;//<sumDist, state>
        std::unordered_set<int> visit;
        int mask = (1<<10)-1;
        minHeap.push({0,mask<<10});//[19:10]=wId, [9:0]=bIds, where wId=-1=1111111111
        while (!minHeap.empty())
        {
            auto p = minHeap.top();
            minHeap.pop();
            int sumDist = p.first;
            int state = p.second;
            if (visit.count(state)) continue; //working
            visit.insert(state); //working
            int wId = (state>>10)&mask;
            if (wId == mask) wId = -1;
            int bIds = state&mask;
            //std::cout << wId << "," << bIds << "," << sumDist << std::endl;
            if (wId == N-1)
            {
                std::cout << "AssignBikesToWorkersWShortestDist MinAllPairDistSums_BFS_MinHeap for w=[" << Debug::ToStr1D<int>()(workers) << "], b=[" << Debug::ToStr1D<int>()(bikes) << "]: " << sumDist << std::endl;
                return sumDist;
            }
            for (int b = 0; b < M; ++b)
            {
                if ((bIds & (1<<b)) == 0)
                {
                    state = ((wId+1)<<10) | bIds | (1<<b);
                    //if (visit.count(state)) continue; //not working
                    //visit.insert(state); //not working
                    int dist = manhattan(workers[wId+1],bikes[b]);
                    minHeap.push({sumDist + dist,state});
                }
            }
        }
        return 0;
    }




    int manhattan(std::vector<int> & a, std::vector<int> & b)
    {
        return abs(a[0]-b[0])+abs(a[1]-b[1]);
    }
};
/*
AssignBikesToWorkersWShortestDist ShortestPairDistFirst_MinHeap for w=[[0,0], [1,1], [2,0]], b=[[1,0], [2,2], [2,1]]: 0, 2, 1
AssignBikesToWorkersWShortestDist ShortestPairDistFirst_BuckSort for w=[[0,0], [1,1], [2,0]], b=[[1,0], [2,2], [2,1]]: 0, 2, 1
AssignBikesToWorkersWShortestDist MinAllPairDistSums_DFS for w=[[0,0], [1,1], [2,0]], b=[[1,0], [2,2], [2,1]]: 4
AssignBikesToWorkersWShortestDist MinAllPairDistSums_DFS_Memo for w=[[0,0], [1,1], [2,0]], b=[[1,0], [2,2], [2,1]]: 4
AssignBikesToWorkersWShortestDist MinAllPairDistSums_BFS_MinHeap for w=[[0,0], [1,1], [2,0]], b=[[1,0], [2,2], [2,1]]: 4
 */
#endif
