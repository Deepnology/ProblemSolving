#ifndef _FALLING_SQUARES_H
#define _FALLING_SQUARES_H
#include "Debug.h"
/*
Leetcode: Falling Squares
On an infinite number line (x-axis), we drop given squares in the order they are given.
The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].
The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares.
We wait for each square to stick before dropping the next.
The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface they touch (either the number line or another square). Squares dropped adjacent to each other will not stick together prematurely.
Return a list ans of heights.
Each height ans[i] represents the current highest height of any square we have dropped, after dropping squares represented by positions[0], positions[1], ..., positions[i].
Example 1:
Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:

After the first drop of positions[0] = [1, 2]:
_aa
_aa
-------
The maximum height of any square is 2.


After the second drop of positions[1] = [2, 3]:
__aaa
__aaa
__aaa
_aa__
_aa__
--------------
The maximum height of any square is 5.
The larger square stays on top of the smaller square despite where its center
of gravity is, because squares are infinitely sticky on their bottom edge.


After the third drop of positions[1] = [6, 1]:
__aaa
__aaa
__aaa
_aa
_aa___a
--------------
The maximum height of any square is still 5.

Thus, we return an answer of [2, 5, 5].

Example 2:
Input: [[100, 100], [200, 100]]
Output: [100, 100]
Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.
 */
class FallingSquares
{
public:
    FallingSquares(){}

    std::vector<int> FindCurMaxHeights(const std::vector<std::pair<int, int>> & positions) //<start, len>
    {
        std::vector<int> res;
        std::map<int, std::pair<int,int>> topIntervals;//<start, <end, max height>>
        int maxH = 0;
        for (const auto & p : positions)
        {
            int curH = 0;
            int left = p.first;
            int right = p.first + p.second - 1;
            auto itr = topIntervals.upper_bound(left);
            if (itr != topIntervals.begin() && std::prev(itr)->second.first >= left)
                --itr;
            //now itr is the leftmost interval that overlaps with [left,right]
            while (itr != topIntervals.end() && itr->first <= right)//overlap
            {
                curH = std::max(curH, itr->second.second);
                if (right < itr->second.first)//cur interval extends to the right of [left,right]:
                    topIntervals[right+1] = itr->second;//add an interval
                if (itr->first < left)//cur interval extends to the left of [left,right]:
                {
                    itr->second = {left-1, itr->second.second};//shrink cur interval
                    ++itr;
                }
                else//erase overlapped intervals
                    topIntervals.erase(itr++);
            }
            topIntervals[left] = {right, curH + p.second};
            maxH = std::max(maxH, curH + p.second);
            res.push_back(maxH);
        }

        std::cout << "FallingSquares FindCurMaxHeights for [" << Debug::ToStr1D<int>()(positions) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
FallingSquares FindCurMaxHeights for [[1,2], [2,3], [6,1]]: 2, 5, 5
 */
#endif
