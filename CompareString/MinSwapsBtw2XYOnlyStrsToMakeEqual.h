#ifndef _MIN_SWAPS_BTW_2_XY_ONLY_STRS_TO_MAKE_EQUAL_H
#define _MIN_SWAPS_BTW_2_XY_ONLY_STRS_TO_MAKE_EQUAL_H
#include "Debug.h"
/*
Leetcode: Minimum Swaps to Make Strings Equal
You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only.
Your task is to make these two strings equal to each other.
You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].
Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.
Example 1:
Input: s1 = "xx", s2 = "yy"
Output: 1
Explanation:
Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
Example 2:
Input: s1 = "xy", s2 = "yx"
Output: 2
Explanation:
Swap s1[0] and s2[0], s1 = "yy", s2 = "xx".
Swap s1[0] and s2[1], s1 = "xy", s2 = "xy".
Note that you can't swap s1[0] and s1[1] to make s1 equal to "yx", cause we can only swap chars in different strings.
Example 3:
Input: s1 = "xx", s2 = "xy"
Output: -1
 */
class MinSwapsBtw2XYOnlyStrsToMakeEqual
{
public:
    int Solve(std::string s1, std::string s2)
    {
        if (s1.size() != s2.size()) return -1;
        int numX1 = 0;//mismatched Xs in s1
        int numY1 = 0;
        int numX2 = 0;
        int numY2 = 0;
        int N = s1.size();
        for (int i = 0; i < N; ++i)
        {
            if (s1[i] == s2[i]) continue;
            if (s1[i]=='x') ++numX1;
            else if (s1[i]=='y') ++numY1;
            if (s2[i]=='x') ++numX2;
            else if (s2[i]=='y') ++numY2;
        }
        //mismatched total num of x must be even such that we can split half Xs in s1 and half Xs in s2. same for total num of y.
        if ((numX1+numX2)%2 != 0 || (numY1+numY2)%2 != 0)
            return -1;
        //case1: [xx, yy]=>[yx, yx]or[xy, xy]
        //half Xs and half Ys in s1 need to be swapped
        //case2: [xy, yx]=>[yy, xx]=>[xy, xy]
        //need two more swaps for the remainder 1 X in s1 if Xs are odd
        return numX1 / 2 + numY1 / 2 + (numX1%2?2:0);
    }
};
#endif
