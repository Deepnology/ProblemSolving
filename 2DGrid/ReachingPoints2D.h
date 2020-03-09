#ifndef _REACHING_POINTS_2D_H
#define _REACHING_POINTS_2D_H
#include "Debug.h"
/*
Leetcode: Reaching Points
A move consists of taking a point (x, y) and transforming it to either (x, x+y) or (x+y, y).
Given a starting point (sx, sy) and a target point (tx, ty), return True if and only if a sequence of moves exists to transform the point (sx, sy) to (tx, ty). Otherwise, return False.
Examples:
Input: sx = 1, sy = 1, tx = 3, ty = 5
Output: True
Explanation:
One series of moves that transforms the starting point to the target is:
(1, 1) -> (1, 2)
(1, 2) -> (3, 2)
(3, 2) -> (3, 5)
Input: sx = 1, sy = 1, tx = 2, ty = 2
Output: False
Input: sx = 1, sy = 1, tx = 1, ty = 1
Output: True

Example:
                       (3,7)
                      /     \
                (10,7)        (3,10)
               /      \      /      \
           (17,7) (10,17) (13,10)  (3,13)
                  /    \
            (27,17)    (10,27)
                       /     \
                (37,27)      (10,37)
                /     \
           (64,27)   (37,64)

    (sx,sy) = (3,7), (tx,ty) = (64,27)
    (64%27,27) -> (10,27)
    (10,27%10) -> (10,17)
    (10,17%10) -> (10,7)
    (10%7,7) -> (3,7)
 */
class ReachingPoints2D
{
public:
    ReachingPoints2D(){}
    ~ReachingPoints2D(){}

    bool Recur(int sx, int sy, int tx, int ty)
    {
        bool res = recur(sx, sy, tx, ty);
        std::cout << "ReachingPoints2D Recur for [" << sx << "," << sy << "] to [" << tx << "," << ty << "]: " << res << std::endl;
        return res;
    }
    bool recur(int sx, int sy, int curX, int curY) //move (curX, curY) from leaf to root
    {
        if (curX < sx || curY < sy) return false;
        if (curX == sx && curY == sy) return true;
        if (curX == sx) return (curY-sy) % curX == 0; //diffY must be a multiple of curX
        if (curY == sy) return (curX-sx) % curY == 0; //diffX must be a multiple of curY
        if (curX > curY)
            return recur(sx, sy, curX % curY, curY); //subtract curX with a multiple of curY
        else
            return recur(sx, sy, curX, curY % curX); //subtract curY with a multiple of curX
    }
};
/*
ReachingPoints2D Recur for [3,7] to [64,27]: 1
 */
#endif
