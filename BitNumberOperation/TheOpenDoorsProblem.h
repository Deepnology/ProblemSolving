#ifndef THE_OPEN_DOORS_PROBLEM_H
#define THE_OPEN_DOORS_PROBLEM_H
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "Debug.h"
/*
Leetcode: Bulb Switcher (count number of doors whose final states are open)
Cracking the coding interview: Math and probability
Elements of programming interview, PrimitiveTypes

There are 100 doors colsed, with index from 1 to 100.
The 1st person opens every door. (toggle 1's multiples)
The 2nd person toggles every 2nd door counted starting from the 1st door. (toggle 2's multiples)
The 3rd person toggles every 3rd door counted starting from the 1st door. (toggle 3's multiples)
....
The 100th person toggles only the 100th door counted starting from the 1st door. (toggle 100's multiple)

1. When will the door with index n be toggled?
   A door with index n will be toggled at all of its factors, including 1 and n. (all factors, not just all prime factors)
   Door 15 will be toggled by the 1st, 3rd, 5th, and 15th people.

2. Which doors whose final state are open?
   If the total number of factors of a door n is odd, that door will be open finally.
   If n is a perfect square number, n must have odd number of factors.
   (because all n's factors can be grouped into pairs, including a pair of n's square root number which is counted for 1 factor)


Leetcode: Bulb Switcher II
There is a room with n lights which are turned on initially and 4 buttons on the wall.
After performing exactly m unknown operations towards buttons, you need to return how many different kinds of status of the n lights could be.
Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4 buttons are given below:
1. Flip all the lights.
2. Flip lights with even numbers.
3. Flip lights with odd numbers.
4. Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...
Example 1:
Input: n = 1, m = 1.
Output: 2
Explanation: Status can be: [on], [off]
Example 2:
Input: n = 2, m = 1.
Output: 3
Explanation: Status can be: [on, off], [off, on], [off, off]
Example 3:
Input: n = 3, m = 1.
Output: 4
Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off], [off, on, on].
Note: n and m both fit in range [0, 1000].

Leetcode: Bulb Switcher III
There is a room with n bulbs, numbered from 1 to n, arranged in a row from left to right.
Initially, all the bulbs are turned off.
At moment k (for k from 0 to n - 1), we turn on the light[k] bulb.
A bulb change color to blue only if it is on and all the previous bulbs (to the left) are turned on too.
Return the number of moments in which all turned on bulbs are blue.
*/
class TheOpenDoorsProblem
{
public:
	TheOpenDoorsProblem(){}
	~TheOpenDoorsProblem(){}

	//index: 1, 2, 3, ..., count
	std::vector<int> AllOpenDoors(int count)
	{
		//find all the perfect square numbers that are smaller than or equal to count
		std::vector<int> res;
		for (int i = 1; i * i <= count; ++i)
			res.push_back(i * i);

		std::cout << "TheOpenDoorsProblem AllOpenDoors for \"" << count << "\" doors: " << Debug::ToStr1D<int>()(res) << std::endl;
		return res;
	}
	//index: 1, 2, 3, ..., count
	bool IsOpenFinally(int doorIdx)
	{
		//check if doorIdx is a perfect square number
		double msqrt = floor(sqrt(doorIdx));
		bool res = (doorIdx == msqrt * msqrt);
		std::cout << "TheOpenDoorsProblem IsOpenFinally for \"" << doorIdx << "-th\" door: " << res << std::endl;
		return res;
	}
	//index: 1, 2, 3, ....
	int NumOfTimesTurningBlue(std::vector<int> & light)//light[i]: the index that (i-1)th bulb is turned on
    {
        int res = 0;
        int right = 0;//rightmost bulb that is turned on
        for (int i = 0; i < light.size(); ++i)
        {
            right = std::max(right, light[i]);
            if (right == i+1) //now i+1 bulbs have been turned on, and if rightmost bulb is on, all i+1 bulbs will turn blue
                ++res;
        }
        return res;
    }
};
/*
TheOpenDoorsProblem AllOpenDoors for "100" doors: 1, 4, 9, 16, 25, 36, 49, 64, 81, 100
TheOpenDoorsProblem IsOpenFinally for "36-th" door: 1
*/
#endif