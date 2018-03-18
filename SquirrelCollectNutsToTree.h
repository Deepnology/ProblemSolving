#ifndef _SQUIRREL_COLLECT_NUTS_TO_TREE_H
#define _SQUIRREL_COLLECT_NUTS_TO_TREE_H
#include "Debug.h"
/*
Leetcode: Squirrel Simulation
There's a tree, a squirrel, and several nuts.
Positions are represented by the cells in a 2D grid.
Your goal is to find the minimal distance for the squirrel to collect all the nuts and put them under the tree one by one.
The squirrel can only take at most one nut at one time and can move in four directions - up, down, left and right, to the adjacent cell.
The distance is represented by the number of moves.
Example 1:
Input:
Height : 5
Width : 7
Tree position : [2,2]
Squirrel : [4,4]
Nuts : [[3,0], [2,5]]
Output: 12
 */
class SquirrelCollectNutsToTree
{
public:
    SquirrelCollectNutsToTree(){}

    int MinDist(int height, int width, const std::vector<int>& tree, const std::vector<int>& squirrel, const std::vector<std::vector<int>>& nuts)
    {
        int sum = 0;
        int maxOverlap = INT_MIN;
        for (const auto & nut : nuts)
        {
            int nutToTree = dist(tree, nut);
            sum += 2 * nutToTree;
            int squirrelToNut = dist(squirrel, nut);
            maxOverlap = std::max(maxOverlap, nutToTree - squirrelToNut);
        }

        std::cout << "SquirrelCollectNutsToTree MinDist for " << height << "*" << width << " grid, tree=[" << Debug::ToStr1D<int>()(tree) << "], squirrel=[" << Debug::ToStr1D<int>()(squirrel) << "], nuts=[" << Debug::ToStr1D<int>()(nuts) << "]: " << sum-maxOverlap << std::endl;
        return sum - maxOverlap;//find maxOverlap such that sum-maxOverlap can result in Min Dist
    }
private:
    int dist(const std::vector<int> & a, const std::vector<int> & b)
    {
        return std::abs(a[0]-b[0]) + std::abs(a[1]-b[1]);
    }
};
/*
SquirrelCollectNutsToTree MinDist for 5*7 grid, tree=[2, 2], squirrel=[4, 4], nuts=[[3,0], [2,5]]: 12
 */
#endif
