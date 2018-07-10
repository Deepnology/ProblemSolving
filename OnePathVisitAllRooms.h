#ifndef _ONE_PATH_VISIT_ALL_ROOMS_H
#define _ONE_PATH_VISIT_ALL_ROOMS_H
#include "Debug.h"
/*
Leetcode: Keys and rooms
There are N rooms and you start in room 0.
Each room has a distinct number in 0, 1, 2, ..., N-1, and each room may have some keys to access the next room.
Formally, each room i has a list of keys rooms[i], and each key rooms[i][j] is an integer in [0, 1, ..., N-1] where N = rooms.length.
A key rooms[i][j] = v opens the room with number v.
Initially, all the rooms start locked (except for room 0).
You can walk back and forth between rooms freely.
Return true if and only if you can enter every room.
Example 1:
Input: [[1],[2],[3],[]]
Output: true
Explanation:
We start in room 0, and pick up key 1.
We then go to room 1, and pick up key 2.
We then go to room 2, and pick up key 3.
We then go to room 3.  Since we were able to go to every room, we return true.
Example 2:
Input: [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can't enter the room with number 2.
 */
class OnePathVisitAllRooms
{
public:
    OnePathVisitAllRooms(){}

    bool DFS(const std::vector<std::vector<int>> & rooms)
    {
        std::unordered_set<int> visit;
        recur(rooms, 0, visit);
        bool res = visit.size() == rooms.size();
        Debug::Print2D<int>()(rooms, false);
        std::cout << "OnePathVisitAllRooms DFS for above rooms: " << res << std::endl;
        return res;
    }
private:
    void recur(const std::vector<std::vector<int>> & rooms, int cur, std::unordered_set<int> & visit)
    {
        visit.insert(cur);
        for (const auto & nxt : rooms[cur])
            if (!visit.count(nxt))
                recur(rooms, nxt, visit);
    }
};
/*
[rY][cX]
Row#0	= 1
Row#1	= 2
Row#2	= 3
Row#3	=

OnePathVisitAllRooms DFS for above rooms: 1
[rY][cX]
Row#0	= 1,  ,
Row#1	= 3, 0, 1
Row#2	= 2,  ,
Row#3	= 0,  ,

OnePathVisitAllRooms DFS for above rooms: 0
 */
#endif
