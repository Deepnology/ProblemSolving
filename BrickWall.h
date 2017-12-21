#ifndef BRICK_WALL_H
#define BRICK_WALL_H
#include "Debug.h"
/*
Leetcode: Brick Wall
There is a brick wall in front of you.
The wall is rectangular and has several rows of bricks.
The bricks have the same height but different width.
You want to draw a vertical line from the top to the bottom and cross the least bricks.
The brick wall is represented by a list of rows.
Each row is a list of integers representing the width of each brick in this row from left to right.
If your line go through the edge of a brick, then the brick is not considered as crossed.
You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
Example:
Input:
[[1,2,2,1],
 [3,1,2],
 [1,3,2],
 [2,4],
 [3,1,2],
 [1,3,1,1]]
Output: 2

*/
class BrickWall
{
public:
	BrickWall() {}

	int HashMap(std::vector<std::vector<int>> & wall)
	{
		int N = wall.size();
		std::unordered_map<int, int> holeCount;
		for (int i = 0; i < N; ++i)
		{
			int M = wall[i].size();
			int prefixSum = 0;
			for (int j = 0; j < M; ++j)
			{
				prefixSum += wall[i][j];
				if (j != M - 1)
					++holeCount[prefixSum];
			}
		}

		int maxHoleCount = 0;
		for (const auto & p : holeCount)
		{
			//std::cout << p.first << "," << p.second << std::endl;
			maxHoleCount = std::max(maxHoleCount, p.second);
		}

		Debug::Print2D<int>()(wall, false);
		std::cout << "BrickWall CountLeastBricks HashTable for the above wall: " << N - maxHoleCount << std::endl;
		return N - maxHoleCount;
	}
};
/*
[rY][cX]
Row#0	= 1, 2, 2, 1
Row#1	= 3, 1, 2,
Row#2	= 1, 3, 2,
Row#3	= 2, 4,  ,
Row#4	= 3, 1, 2,
Row#5	= 1, 3, 1, 1

BrickWall CountLeastBricks HashTable for the above wall: 2
*/
#endif
