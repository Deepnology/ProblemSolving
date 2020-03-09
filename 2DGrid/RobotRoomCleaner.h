#ifndef _ROBOT_ROOM_CLEANER_H
#define _ROBOT_ROOM_CLEANER_H
#include "Debug.h"
/*
Leetcode: Robot Room Cleaner
Given a robot cleaner in a room modeled as a grid.
Each cell in the grid can be empty or blocked.
The robot cleaner with 4 given APIs can move forward, turn left or turn right. Each turn it made is 90 degrees.
When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.
Design an algorithm to clean the entire room using only the 4 given APIs shown below.

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
Example:

Input:
room = [
  [1,1,1,1,1,0,1,1],
  [1,1,1,1,1,0,1,1],
  [1,0,1,1,1,1,1,1],
  [0,0,0,1,0,0,0,0],
  [1,1,1,1,1,1,1,1]
],
row = 1,
col = 3

Explanation:
All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
Notes:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the mentioned 4 APIs, without knowing the room layout and the initial robot's position.
The robot's initial position will always be in an accessible cell.
The initial direction of the robot will be facing up.
All accessible cells are connected, which means the all cells marked as 1 will be accessible by the robot.
Assume all four edges of the grid are all surrounded by wall.
 */
class RobotRoomCleaner
{
public:
    RobotRoomCleaner(){}

    class Robot
    {
    public:
        // Returns true if the cell in front is open and robot moves into the cell.
        // Returns false if the cell in front is blocked and robot stays in the current cell.
        bool move(){ return true; }

        // Robot will stay in the same cell after calling turnLeft/turnRight.
        // Each turn will be 90 degrees.
        void turnLeft(){}

        void turnRight(){}

        // Clean the current cell.
        void clean(){}
    };

    void DFS(Robot & robot)
    {
        std::unordered_map<int,std::unordered_set<int>> visit;//<row,<col>>
        recur(robot, 0, 0, 0, visit);
    }
    void recur(Robot & robot, int curRow, int curCol, int curDir, std::unordered_map<int,std::unordered_set<int>> & visit)
    {
        visit[curRow].insert(curCol);
        robot.clean();

        static std::vector<std::vector<int>> dir({{-1,0},{0,1},{1,0},{0,-1}});//up, right, down, left (order doesn't matter)
        for (int d = 0; d < 4; ++d)
        {
            int nxtDir = (curDir+d)%4;
            int nxtRow = curRow + dir[nxtDir][0];
            int nxtCol = curCol + dir[nxtDir][1];
            if ((!visit.count(nxtRow) || !visit[nxtRow].count(nxtCol)) && robot.move())
            {
                recur(robot, nxtRow, nxtCol, nxtDir, visit);
                robot.turnLeft();
                robot.turnLeft();
                robot.move();//go reverse direction of current nxtDir
                robot.turnLeft();
                robot.turnLeft();
            }
            robot.turnRight();
        }
    }
};
#endif
