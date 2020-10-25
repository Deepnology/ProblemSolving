#ifndef _N_UNIQUE_NUMS_SUM_TO_ZERO_H
#define _N_UNIQUE_NUMS_SUM_TO_ZERO_H
#include "Debug.h"
/*
Leetcode: Find N Unique Integers Sum up To Zero
Given an integer n, return any array containing n unique integers such that they add up to 0.
Example 1:
Input: n = 5
Output: [-7,-1,1,3,4]
Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
Example 2:
Input: n = 3
Output: [-1,0,1]
Example 3:
Input: n = 1
Output: [0]
 */
class NUniqueNumsSumToZero
{
public:
    std::vector<int> Solve(int n)
    {
        std::vector<int> res;
        int cur = n%2?0:1;
        if (n%2)//if n is odd, add 0
            res.push_back(cur++);
        //now cur==1
        while(res.size() < n)
        {
            res.push_back(cur);
            res.push_back(-cur);
            ++cur;
        }
        return res;
    }
};
#endif
