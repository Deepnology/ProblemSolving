#ifndef WATER_AND_JUG_PROBLEM_H
#define WATER_AND_JUG_PROBLEM_H
#include "Debug.h"
/*
Leetcode: Water and Jug Problem
You are given two jugs with capacities x and y litres.
There is an infinite amount of water supply available.
You need to determine whether it is possible to measure exactly z litres using these two jugs.
If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.

Operations allowed:
Fill any of the jugs completely with water.
Empty any of the jugs.
Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.

Example 1: (From the famous "Die Hard" example)
Input: x = 3, y = 5, z = 4
Output: True

Example 2:
Input: x = 2, y = 6, z = 5
Output: False



Die Hard Problem:
1. Fill in 5 liter jug, pour 3 liter from 5 liter jug to 3 liter jug, pour away 3 liter from 3 liter jug, pour the remaining 2 liter from 5 liter jug to 3 liter jug
2. Fill in 5 liter jug, pour 1 liter from 5 liter jug to 3 liter jug, pour away 3 liter from 3 liter jug, then the 4 liter water contained in the 5 liter jug is the result

4 = (-2) * 3 + 2 * 5
which means we pour away 2 times from 3 liter jug and fill 2 times in 5 liter jug

z = m * x + n * y
Given the equation and z, x, y, find out if there exists m and n such that satisfy the equation.
=> z must be a multiple of GCD(x, y)
as well as "z <= x + y" because we cannot get a greater amount of water than the size of x liter jug + y liter jug
*/
class WaterAndJugProblem
{
public:
	WaterAndJugProblem() {}
	~WaterAndJugProblem() {}

	bool canMeasureWater(int x, int y, int z)
	{
		bool res = false;
		if (z == 0)
		{
			res = true;
		}
		else
		{
			res = (z <= x + y) && (z % this->GCD(x, y) == 0);
		}

		std::cout << "WaterAndJugProblem canMeasureWater for \"" << x << "\", \"" << y << "\", \"" << z << "\": " << res << std::endl;
		return res;
	}

private:
	int GCD(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return this->GCD(b, a%b);
	}
};
/*
WaterAndJugProblem canMeasureWater for "3", "5", "4": 1
WaterAndJugProblem canMeasureWater for "2", "6", "5": 0
*/
#endif
