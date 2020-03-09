#ifndef _MIN_LEXICOGRAPHIC_STR_BY_SWAP_PAIRS_H
#define _MIN_LEXICOGRAPHIC_STR_BY_SWAP_PAIRS_H
#include "Debug.h"
/*
Leetcode: Smallest String with Swaps
You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.
You can swap the characters at any pair of indices in the given pairs any number of times.
Return the lexicographically smallest string that s can be changed to after using the swaps.
Example 1:
Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"
Example 2:
Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination:
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"
Example 3:
Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination:
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"
 */
class MinLexicographicStrBySwapPairs
{
public:
    std::string UnionFind(std::string s, const std::vector<std::vector<int>> & pairs)
    {
        //UnionFind
        int N = s.size();
        std::vector<int> chdToP(N);
        for (int i = 0; i < N; ++i) chdToP[i]=i;
        for (auto & p : pairs)
        {
            int root1 = Find(chdToP, p[0]);
            int root2 = Find(chdToP, p[1]);
            if (root1 != root2)
                chdToP[root2] = root1;
        }
        //construct rootToChd
        std::unordered_map<int,std::set<int>> rootToChd;//<root, sorted set of chd that contains root>
        for (int i = 0; i < N; ++i)
            rootToChd[Find(chdToP,i)].insert(i);
        //sort all chars in each group, then insert to string
        std::string res(N, ' ');
        for (auto & p : rootToChd)
        {
            std::string chars;
            for (auto & i : p.second)//note: p.second already contains p.first
            {
                chars.push_back(s[i]);
            }
            std::sort(chars.begin(), chars.end());
            int j = 0;
            for (auto & i : p.second)
                res[i] = chars[j++];
        }
        std::cout << "MinLexicographicStrBySwapPairs UnionFind for " << s << ", [" << Debug::ToStr1D<int>()(pairs) << "]: " << res << std::endl;
        return res;
    }
private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (chdToP[cur] != cur)
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
};
/*
MinLexicographicStrBySwapPairs UnionFind for dcab, [[0,3], [1,2], [0,2]]: abcd
 */
#endif
