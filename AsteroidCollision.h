#ifndef _ASTEROID_COLLISION_H
#define _ASTEROID_COLLISION_H
#include "Debug.h"
/*
Leetcode: Asteroid Collision
We are given an array asteroids of integers representing asteroids in a row.
For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left).
Each asteroid moves at the same speed.
Find out the state of the asteroids after all collisions.
If two asteroids meet, the smaller one will explode.
If both are the same size, both will explode.
Two asteroids moving in the same direction will never meet.
Example 1:
Input:
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation:
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
Example 2:
Input:
asteroids = [8, -8]
Output: []
Explanation:
The 8 and -8 collide exploding each other.
Example 3:
Input:
asteroids = [10, 2, -5]
Output: [10]
Explanation:
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
Example 4:
Input:
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation:
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.
 */
class AsteroidCollision
{
public:
    AsteroidCollision(){}

    std::vector<int> UseStack(const std::vector<int> & asteroids)
    {
        std::stack<int> stk;
        for (const auto &cur : asteroids)
        {
            if (stk.empty() || stk.top() < 0 || cur > 0)
                stk.push(cur);
            else//!stk.empty() && stk.top() > 0 && cur < 0
            {
                while (!stk.empty() && stk.top() > 0 && stk.top() < std::abs(cur))
                    stk.pop();//remove smaller asteriods in stk
                //now stk.empty() || stk.top() < 0 || (stk.top() > 0 && stk.top() >= abs(cur))
                if (!stk.empty() && stk.top() > 0 && stk.top() > std::abs(cur))
                {
                    continue;//cancel cur asteriod
                }
                if (!stk.empty() && stk.top() > 0 && stk.top() == std::abs(cur))
                {
                    stk.pop();
                    continue;//cancel equal sized asteriods
                }
                stk.push(cur);
            }
        }

        std::vector<int> res(stk.size());
        for (int i = stk.size() - 1; i >= 0; --i)
        {
            res[i] = stk.top();
            stk.pop();
        }

        std::cout << "AsteroidCollision UseStack for [" << Debug::ToStr1D<int>()(asteroids) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
AsteroidCollision UseStack for [1, 2, 8, -8, -2, -6]: -6
 */
#endif
