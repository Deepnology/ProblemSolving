#ifndef _PATH_CROSSING_H
#define _PATH_CROSSING_H
#include "Debug.h"
/*
Leetcode: Path Crossing
Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively.
 You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
Return True if the path crosses itself at any point, that is, if at any time you are on a location you've previously visited.
 Return False otherwise.

 see also SelfCrossing.h
 */
class PathCrossing
{
public:
    bool IsPathCrossing(std::string path)
    {
        int x = 0;
        int y = 0;
        std::unordered_set<std::string> visit;
        visit.insert("0,0");
        for(char d: path)
        {
            if (d=='N') y++;
            else if (d=='S') y--;
            else if (d=='E') x++;
            else x--;

            if (visit.count(std::to_string(x)+","+std::to_string(y)))
                return true;
            visit.insert(std::to_string(x)+","+std::to_string(y));
        }
        return false;
    }
};
#endif
