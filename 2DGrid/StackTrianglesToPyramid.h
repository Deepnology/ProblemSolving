#ifndef _STACK_TRIANGLES_TO_PYRAMID_H
#define _STACK_TRIANGLES_TO_PYRAMID_H
#include "Debug.h"
/*
Leetcode: Pyramid Transition Matrix
We are stacking blocks to form a pyramid. Each block has a color which is a one letter string, like `'Z'`.
For every block of color `C` we place not in the bottom row, we are placing it on top of a left block of color `A` and right block of color `B`.
We are allowed to place the block there only if `(A, B, C)` is an allowed triple.
We start with a bottom row of bottom, represented as a single string.
We also start with a list of allowed triples allowed. Each allowed triple is represented as a string of length 3.
Return true if we can build the pyramid all the way to the top, otherwise false.
Example 1:
Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
Output: true
Explanation:
We can stack the pyramid like this:
    A
   / \
  D   E
 / \ / \
X   Y   Z

This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are allowed triples.
Example 2:
Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
Output: false
Explanation:
We can't stack the pyramid to the top.
Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
 */
class StackTrianglesToPyramid
{
public:
    StackTrianglesToPyramid(){}

    bool DFS(std::string bottom, std::vector<std::string> && allowed)
    {
        std::unordered_map<std::string,std::unordered_set<char>> toTop;
        for (auto & s : allowed)
            toTop[s.substr(0,2)].insert(s[2]);
        bool res = recur(bottom, 0, "", toTop);

        std::cout << "StackTrianglesToPyramid DFS for bottom=[" << bottom << "], triangles=[" << Debug::ToStr1D<std::string>()(allowed) << "]: " << res << std::endl;
        return res;
    }
private:
    bool recur(std::string bottom, int begin, std::string nxt, std::unordered_map<std::string,std::unordered_set<char>> & toTop)
    {
        int N = bottom.size();
        if (N == 1) return true;
        if (begin == N-1)
            return recur(nxt, 0, "", toTop);//move up 1 level
        for (auto & c : toTop[bottom.substr(begin,2)])
            if (recur(bottom, begin+1, nxt+c, toTop))//move right 1 char
                return true;
        return false;
    }
};
/*
StackTrianglesToPyramid DFS for bottom=[XYZ], triangles=[XYD, YZE, DEA, FFF]: 1
 */
#endif
