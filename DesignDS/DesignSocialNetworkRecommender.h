#ifndef _DESIGN_SOCIAL_NETWORK_RECOMMENDER_H
#define _DESIGN_SOCIAL_NETWORK_RECOMMENDER_H
#include "Debug.h"
/*
https://courses.cs.washington.edu/courses/cse140/13wi/homework/hw4/homework4.html
Social network can be modeled as an undirected graph.
Use collaborative filtering to recommend friends for a given user.
For a given user node, perform BFS to iterate friends of friends.
Return a list of user nodes for friends recommendation.
Approach I: Recommend by number of common friends.
sort by
1) distance >= 2
2) number of paths w/ min distance
Approach II: Recommend by influence.
sort by
1) distance >= 2
2) sum of path scores w/ min distance

   4-------------
0  |    2       |     6
 \ |  / |       |   / |
  \|/   |       | /   |
   1 ---|-------5-----7
    \   |       |     |
     \  |       |     |
      \ |       |     |
       3----9---|------
        \  | \  |
         \ |  \ |
          10----8

DesignSocialNetworkRecommender for 8:
SortByNumPath: 7, 3, 1, 6, 4
SortBySumPathScore: 3, 7, 1, 6, 4
 */
class DesignSocialNetworkRecommender
{
public:
    std::vector<int> BFS_SortByNumPath(std::unordered_map<int, std::unordered_set<int>> & G, int node, int maxDist)
    {
        //<minDist, map<numPathWithMinDist, unordered_set<Node>>>
        std::map<int, std::map<int, std::unordered_set<int>>> minHeap;
        //unordered_map<Node, pair<minDist, numPathWithMinDist>>
        std::unordered_map<int, std::pair<int, int>> visit;
        std::queue<int> que;
        que.push(node);
        visit.insert({node, {0,0}});
        int dist = 0;
        std::vector<int> res;
        while (!que.empty())
        {
            int N = que.size();
            while (N-- > 0)
            {
                int curNode = que.front();
                que.pop();
                for (int nbor : G[curNode]) //neighbor has dist+1
                {
                    if (!visit.count(nbor)) //first time visit with min dist
                    {
                        visit.insert({nbor, {dist+1, 1}});
                        minHeap[dist+1][1].insert(nbor);
                        que.push(nbor);
                    }
                    else //non first time visit
                    {
                        int minDist = visit[nbor].first;
                        if (dist+1 == minDist) //only when cur dist is minDist
                        {
                            int numPath = visit[nbor].second;
                            visit[nbor].second++; //incr numPathWithMinDist
                            minHeap[minDist][numPath].erase(nbor);
                            minHeap[minDist][numPath+1].insert(nbor);
                        }
                    }
                }
            }
            ++dist;
            if (dist == maxDist)
                break;
        }
        for (auto itr = minHeap.begin(); itr != minHeap.end(); ++itr)
        {
            if (itr->first < 2) continue;
            for (auto itr2 = itr->second.rbegin(); itr2 != itr->second.rend(); ++itr2)
                for (auto n : itr2->second)
                    res.push_back(n);
        }
        return res;
    }

    std::vector<int> BFS_SortBySumPathScore(std::unordered_map<int, std::unordered_set<int>> & G, int node, int maxDist)
    {
        //<minDist, map<sumPathScoreWithMinDist, unordered_set<Node>>>
        std::map<int, std::map<int, std::unordered_set<int>>> minHeap;
        //unordered_map<Node, pair<minDist, sumPathScoreWithMinDist>>
        std::unordered_map<int, std::pair<int, int>> visit;
        std::queue<int> que;
        que.push(node);
        visit.insert({node, {0,1}});
        int dist = 0;
        std::vector<int> res;
        while (!que.empty())
        {
            int N = que.size();
            while (N-- > 0)
            {
                int curNode = que.front();
                que.pop();
                for (int nbor : G[curNode]) //neighbor has dist+1
                {
                    if (!visit.count(nbor)) //first time visit with min dist
                    {
                        int sumPathScore = (int)(100.0 * 1.0/(double)G[curNode].size() * (double)visit[curNode].second);
                        visit.insert({nbor, {dist+1, sumPathScore}});
                        minHeap[dist+1][sumPathScore].insert(nbor);
                        que.push(nbor);
                    }
                    else //non first time visit
                    {
                        int minDist = visit[nbor].first;
                        if (dist+1 == minDist) //only when cur dist is minDist
                        {
                            int sumPathScore = visit[nbor].second;
                            visit[nbor].second += (int)(100.0 * 1.0/(double)G[curNode].size() * (double)visit[curNode].second);
                            minHeap[minDist][sumPathScore].erase(nbor);
                            minHeap[minDist][visit[nbor].second].insert(nbor);
                        }
                    }
                }
            }
            ++dist;
            if (dist == maxDist)
                break;
        }
        for (auto itr = minHeap.begin(); itr != minHeap.end(); ++itr)
        {
            if (itr->first < 2) continue;
            for (auto itr2 = itr->second.rbegin(); itr2 != itr->second.rend(); ++itr2)
                for (auto n : itr2->second)
                    res.push_back(n);
        }
        return res;
    }

    void Test()
    {
        std::unordered_map<int, std::unordered_set<int>> G;
        G[0].insert(1);
        G[1].insert(0);
        G[1].insert(2);
        G[1].insert(3);
        G[1].insert(4);
        G[1].insert(5);
        G[2].insert(1);
        G[2].insert(3);
        G[3].insert(1);
        G[3].insert(2);
        G[3].insert(9);
        G[3].insert(10);
        G[4].insert(1);
        G[4].insert(5);
        G[5].insert(1);
        G[5].insert(4);
        G[5].insert(6);
        G[5].insert(7);
        G[5].insert(8);
        G[6].insert(5);
        G[6].insert(7);
        G[7].insert(5);
        G[7].insert(6);
        G[7].insert(9);
        G[8].insert(5);
        G[8].insert(9);
        G[8].insert(10);
        G[9].insert(3);
        G[9].insert(7);
        G[9].insert(8);
        G[9].insert(10);
        G[10].insert(3);
        G[10].insert(8);
        G[10].insert(9);
        std::vector<int> r1 = BFS_SortByNumPath(G, 8, 2);
        std::vector<int> r2 = BFS_SortBySumPathScore(G, 8, 2);
        std::cout << "DesignSocialNetworkRecommender for 8: " << std::endl;
        std::cout << "SortByNumPath: " << Debug::ToStr1D<int>()(r1) << std::endl;
        std::cout << "SortBySumPathScore: " << Debug::ToStr1D<int>()(r2) << std::endl;
    }
};
#endif
