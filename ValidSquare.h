#ifndef VALID_SQUARE_H
#define VALID_SQUARE_H
#include "Debug.h"
/*
Leetcode: Valid Square
Given the coordinates of four points in 2D space, return whether the four points could construct a square.
The coordinate (x,y) of a point is represented by an integer array with two integers.
Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
*/
class ValidSquare
{
public:
	ValidSquare() {}

	bool UseHashMap(std::vector<int> & p1, std::vector<int> & p2, std::vector<int> & p3, std::vector<int> & p4)
	{
		std::unordered_map<int, int> lenCount;//<side length, count>
		++lenCount[dist(p1, p2)];
		++lenCount[dist(p1, p3)];
		++lenCount[dist(p1, p4)];
		++lenCount[dist(p2, p3)];
		++lenCount[dist(p2, p4)];
		++lenCount[dist(p3, p4)];
		if (lenCount.size() > 2) return false;
		for (auto & p : lenCount)//now lenCount contains 1 or 2 side lengths
		{
			if (p.first == 0) return false;
			if (p.second != 2 && p.second != 4 && p.second != 6) return false;
		}
		return true;
	}
private:
	int dist(std::vector<int> & p1, std::vector<int> & p2)
	{
		return (p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]);
	}
};
#endif
