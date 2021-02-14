#ifndef _RAY_REFLECTION_IN_SQUARE_MIRRORS_H
#define _RAY_REFLECTION_IN_SQUARE_MIRRORS_H
#include "Debug.h"
/*
Leetcode: Mirror Reflection
There is a special square room with mirrors on each of the four walls.
Except for the southwest corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.
The square room has walls of length p, and a laser ray from the southwest corner first meets the east wall at a distance q from the 0th receptor.
Return the number of the receptor that the ray meets first.  (It is guaranteed that the ray will meet a receptor eventually.)
 */
class RayReflectionInSquareMirrors
{
public:
    int Solve(int p, int q)
    {
        int height = q;
        bool left = false;

        while(height % p != 0) //iterate for number of reflection times
        {
            height += q;
            left = !left;
        }
        if(left)
            return 2;//upper left corner
        else
            return (height/p)%2;//lower right or upper right corner
    }
};
#endif
