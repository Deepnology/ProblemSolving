#ifndef _SWAP_ADJACENT_IN_LR_STRING_H
#define _SWAP_ADJACENT_IN_LR_STRING_H
#include "Debug.h"
/*
Leetcode: Swap Adjacent in LR String
In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL",
a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR".
Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.
Example:
Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: True
Explanation:
We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
 */
class SwapAdjacentInLRString
{
public:
    SwapAdjacentInLRString(){}

    bool CanTransform(std::string start, std::string end)
    {
        bool res = Linear(start, end);
        std::cout << "SwapAdjacentInLRString CanTransform for [" << start << ", " << end << "]: " << res << std::endl;
        return res;
    }
private:
    bool Linear(std::string start, std::string end)
    {
        int i = 0;
        int j = 0;
        int N = start.size();
        int M = end.size();
        while (true)
        {
            while (i < N && start[i] == 'X') ++i;
            while (j < M && end[j] == 'X') ++j;
            if (i == N && j == M) return true;
            if (i == N || j == M) return false;
            if (start[i] != end[j]) return false;
            if (start[i] == 'L' && i < j) return false;//L in start is on left side of L in end
            if (start[i] == 'R' && i > j) return false;//R in start is on right side of R in end
            ++i;
            ++j;
        }
    }
};
/*
SwapAdjacentInLRString CanTransform for [RXXLRXRXL, XRLXXRRLX]: 1
 */
#endif
