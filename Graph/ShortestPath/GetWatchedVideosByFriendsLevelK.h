#ifndef _GET_WATCHED_VIDEOS_BY_FRIENDS_LEVEL_K_H
#define _GET_WATCHED_VIDEOS_BY_FRIENDS_LEVEL_K_H
#include "Debug.h"
/*
Leetcode: Get Watched Videos by Your Friends
There are n people, each person has a unique id between 0 and n-1.
Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on.
In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest.

Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
Output: ["D"]
Explanation:
You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
 */
class GetWatchedVideosByFriendsLevelK
{
public:
    std::vector<std::string> BFS(std::vector<std::vector<std::string>>& watchedVideos, std::vector<std::vector<int>> & friends, int id, int level)
    {
        std::unordered_map<std::string,int> vCount;
        std::unordered_set<int> visit;
        std::queue<int> que;
        visit.insert(id);
        que.push(id);
        int dist = 0;
        while (!que.empty() && dist <= level)
        {
            int count = que.size();
            while (count-- > 0)
            {
                int cur = que.front();
                que.pop();
                if (dist == level)
                    for (auto & s : watchedVideos[cur])
                        ++vCount[s];
                for (auto & f : friends[cur])
                {
                    if (!visit.count(f))
                    {
                        visit.insert(f);
                        que.push(f);
                    }
                }
            }
            ++dist;
        }
        std::vector<std::pair<int,std::string>> v;
        for (auto & p : vCount)
            v.push_back({p.second, p.first});
        std::sort(v.begin(), v.end());
        std::vector<std::string> res;
        for (auto & p : v)
            res.push_back(p.second);
        return res;
    }
};
#endif
