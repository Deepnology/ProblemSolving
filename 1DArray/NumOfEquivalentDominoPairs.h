#ifndef _NUM_OF_EQUIVALENT_DOMINO_PAIRS_H
#define _NUM_OF_EQUIVALENT_DOMINO_PAIRS_H
#include "Debug.h"
/*
Leetcode: Number of Equivalent Domino Pairs
Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one domino can be rotated to be equal to another domino.
Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
Example 1:
Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1
Constraints:
1 <= dominoes.length <= 40000
1 <= dominoes[i][j] <= 9

see TwoSum.h (CountPairWSumEqualK)
 */
class NumOfEquivalentDominoPairs
{
public:
    int Solve(std::vector<std::vector<int>> && dominoes)
    {
        std::unordered_map<int,int> count;
        for (auto & v : dominoes)
            ++count[std::min(v[0],v[1])*10+std::max(v[0],v[1])];
        int res = 0;
        for (auto & p : count)
            res += p.second*(p.second-1)/2;
        //ex: [(1,2),(1,2),(1,2)]: 3 pairs

        std::cout << "NumOfEquivalentDominoPairs for [" << Debug::ToStr1D<int>()(dominoes) << "]: " << res << std::endl;
        return res;
    }
};
/*
NumOfEquivalentDominoPairs for [[1,2], [1,2], [1,2]]: 3
 */
#endif
