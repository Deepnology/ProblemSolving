#ifndef SELF_CROSSING_H
#define SELF_CROSSING_H
#include "Debug.h"
/*
Leetcode: Self Crossing
You are given an array x of n positive numbers.
You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on.
In other words, after each move your direction changes counter-clockwise.
Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.
Example 1:
Given x = [2, 1, 1, 2],
¢z¢w¢w¢w¢{
¢x   ¢x
¢|¢w¢w¢w¢q¢w¢w>
    ¢x
Return true (self crossing)
Example 2:
Given x = [1, 2, 3, 4],
¢z¢w¢w¢w¢w¢w¢w¢{
¢x      ¢x
¢x
¢x
¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w>
Return false (not self crossing)
Example 3:
Given x = [1, 1, 1, 1],
¢z¢w¢w¢w¢{
¢x   ¢x
¢|¢w¢w¢w¢q>
Return true (self crossing)



"Self Crossing" means the current moving path intersects with one of all old moving paths.

                 i-2
    case 1 : i-1¢z¢w¢{
                ¢|¢w¢q¢w>i
                 i-3
                 
                    i-2
    case 2 : i-1 ¢z¢w¢w¢w¢w¢{
                 ¢|¢wùùùù>¢}i-3
                 i  i-4      (i overlapped i-4)

    case 3 :    i-4
               ¢z¢w¢w¢{ 
               ¢xi<¢q¢w¢{
            i-3¢x i-5¢xi-1
               ¢|¢w¢w¢w¢w¢}
                i-2


This case can be reduced to case1. (i intersects with i-3)
                    ^
               ¢z¢w¢w¢w¢w¢q¢w¢w¢w¢{
               ¢x    |   |
               ¢x    ¢x
               ¢|¢w¢w¢w¢w¢}

This case can be reduced to case3. (i intersects with i-5)
                  ¢z¢w¢{
				  v |
               ¢z¢w¢w¢{ |
               ¢x  | |
               ¢x    ¢x
               ¢|¢w¢w¢w¢w¢}
                
This case can be reduced to case2. (i overlapped i-4)
               ¢z¢w¢w¢w¢w¢{
               ¢x    |
               ¢x    ^
               ¢|¢w¢w¢w¢w¢}
*/
class SelfCrossing
{
public:
	SelfCrossing() {}
	~SelfCrossing() {}

	bool check(const std::vector<int> & v)
	{
		std::cout << "SelfCrossing for \"" << Debug::ToStr1D<int>()(v) << "\": ";

		int N = v.size();
		for (int i = 3; i < N; ++i)
		{
			if (v[i] >= v[i - 2] && v[i - 1] <= v[i - 3])
			{
				std::cout << "True (Case1)" << std::endl;
				return true;
			}

			if (i >= 4 && v[i] + v[i - 4] >= v[i - 2] && v[i - 1] == v[i - 3])
			{
				std::cout << "True (Case2)" << std::endl;
				return true;
			}

			if (i >= 5 && (v[i - 2] >= v[i - 4] && v[i] + v[i - 4] >= v[i - 2])
				&& (v[i - 1] <= v[i - 3] && v[i - 1] + v[i - 5] >= v[i - 3]))
			{
				std::cout << "True (Case3)" << std::endl;
				return true;
			}
		}

		std::cout << "False" << std::endl;
		return false;
	}
};
/*
SelfCrossing for "1, 5, 5, 3, 6": True (Case1)
SelfCrossing for "1, 2, 3, 4, 6, 2, 3": True (Case3)
SelfCrossing for "1, 3, 4, 3, 3": True (Case2)
*/
#endif
