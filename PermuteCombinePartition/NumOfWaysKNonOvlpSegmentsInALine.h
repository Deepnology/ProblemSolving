#ifndef _NUM_OF_WAYS_K_NON_OVLP_SEGMENTS_IN_A_LINE_H
#define _NUM_OF_WAYS_K_NON_OVLP_SEGMENTS_IN_A_LINE_H
#include "Debug.h"
/*
Leetcode: Number of Sets of K Non-Overlapping Line Segments
Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i,
 find the number of ways we can draw exactly k non-overlapping line segments such that
 each segment covers two or more points.
The endpoints of each segment must have integral coordinates.
The k line segments do not have to cover all n points, and they are allowed to share endpoints.
Return the number of ways we can draw k non-overlapping line segments.
Since this number can be huge, return it modulo 109 + 7.
Example 1:
Input: n = 4, k = 2
Output: 5
Explanation:
The two line segments are shown in red and blue.
The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
 */
class NumOfWaysKNonOvlpSegmentsInALine
{
public:
    int DFS(int n, int k)
    {
        std::vector<std::vector<std::vector<int>>> memo(n+1, std::vector<std::vector<int>>(k+1, std::vector<int>(2, -1)));
        return recur(n, 0, k, 1, memo);
    }
private:
    int recur(int n, int cur, int curK, int isStart, std::vector<std::vector<std::vector<int>>> & memo)
    {
        if (memo[cur][curK][isStart] != -1) return memo[cur][curK][isStart];
        if (curK==0) return 1;//consumes all k lines
        if (cur==n) return 0;//cannot consume all k lines when reach end
        int res = 0;
        res += recur(n, cur+1, curK, isStart, memo);//skip cur point being a start or end
        if (isStart == 1)
            res += recur(n, cur+1, curK, 0, memo);//take cur point as start
        else
            res += recur(n, cur, curK-1, 1, memo);//take cur point as end

        return memo[cur][curK][isStart] = res % 1000000007;
    }
};
#endif
