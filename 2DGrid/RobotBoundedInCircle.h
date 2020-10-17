#ifndef _ROBOT_BOUNDED_IN_CIRCLE_H
#define _ROBOT_BOUNDED_IN_CIRCLE_H
#include "Debug.h"
/*
Leetcode: Robot Bounded In Circle
On an infinite plane, a robot initially stands at (0, 0) and faces north.
The robot can receive one of three instructions:
"G": go straight 1 unit;
"L": turn 90 degrees to the left;
"R": turn 90 degress to the right.
The robot performs the instructions given in order, and repeats them forever.
Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.
 */
class RobotBoundedInCircle
{
public:
    bool isRobotBounded(std::string instructions)
    {
        //                                 North,East ,South ,West
        std::vector<std::vector<int>> dir({{0,1},{1,0},{0,-1},{-1,0}});
        int x = 0; int y = 0; int d = 0;
        for (auto & c : instructions)
        {
            if (c == 'R')
                d = (d+1)%4;
            else if (c == 'L')
                d = (d-1+4)%4;
            else //'G'
            {
                x += dir[d][0];
                y += dir[d][1];
            }
        }
        return x == 0 && y == 0 || d != 0;
        //1. it goes back to origin
        //2. it's direction doesn't face north after a repeat
        //(as long as the direction after a repeat is diff from the initial direction, it's on a path of a circle with a few repeats)
    }
};
#endif
