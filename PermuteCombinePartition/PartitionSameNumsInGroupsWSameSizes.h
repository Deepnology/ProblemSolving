#ifndef _PARTITION_SAME_NUMS_IN_GROUPS_W_SAME_SIZES_H
#define _PARTITION_SAME_NUMS_IN_GROUPS_W_SAME_SIZES_H
#include "Debug.h"
#include <numeric>
/*
Leetcode: X of a Kind in a Deck of Cards
In a deck of cards, each card has an integer written on it.
Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:
Each group has exactly X cards.
All the cards in each group have the same integer.
Example 1:
Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]
Example 2:
Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.
Example 3:
Input: [1]
Output: false
Explanation: No possible partition.
Example 4:
Input: [1,1]
Output: true
Explanation: Possible partition [1,1]
Example 5:
Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]
*/
class PartitionSameNumsInGroupsWSameSizes
{
public:
    PartitionSameNumsInGroupsWSameSizes(){}
    ~PartitionSameNumsInGroupsWSameSizes(){}

    bool Valid(std::vector<int> && deck)
    {
        std::unordered_map<int,int> count;
        for (auto & n : deck)
            ++count[n];
        int GCD = 0;
        for (auto & p : count)
            GCD = std::gcd(GCD, p.second);
        bool res = GCD >= 2;

        std::cout << "PartitionSameNumsInGroupsWSameSizes Valid for [" << Debug::ToStr1D<int>()(deck) << "]: " << res << std::endl;
        return res;
    }
};
/*
PartitionSameNumsInGroupsWSameSizes Valid for [1, 1, 2, 2, 2, 2]: 1
 */
#endif
