#ifndef _FIND_ANAGRAM_MAPPINGS_H
#define _FIND_ANAGRAM_MAPPINGS_H
#include "Debug.h"
/*
Leetcode: Find Anagram Mappings
Given two lists Aand B, and B is an anagram of A.
B is an anagram of A means B is made by randomizing the order of the elements in A.
We want to find an index mapping P, from A to B.
A mapping P[i] = j means the ith element in A appears in B at index j.
These lists A and B may contain duplicates.
If there are multiple answers, output any of them.
For example, given
A = [12, 28, 46, 32, 50]
B = [50, 12, 32, 46, 28]
We should return
[1, 4, 3, 2, 0]
as P[0] = 1 because the 0th element of A appears at B[1], and P[1] = 4 because the 1st element of A appears at B[4], and so on.
Note:
A, B have equal lengths in range [1, 100].
A[i], B[i] are integers in range [0, 10^5].
 */
class FindAnagramMappings
{
public:
    FindAnagramMappings(){}

    std::vector<int> UseHashMap(const std::vector<int> & A, const std::vector<int> & B)
    {
        std::unordered_map<int, std::vector<int>> map;//<entry, array of idx>
        int N = A.size();
        for (int i = 0; i < N; ++i)
            map[A[i]].push_back(i);
        std::vector<int> res(N);
        for (int i = 0; i < N; ++i)
        {
            int tgtIdx = map[B[i]].back();
            map[B[i]].pop_back();
            if (map[B[i]].empty()) map.erase(B[i]);
            res[tgtIdx] = i;
        }

        std::cout << "FindAnagramMappings UseHashMap for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
FindAnagramMappings UseHashMap for [12, 28, 46, 32, 50], [50, 12, 32, 46, 28]: 1, 4, 3, 2, 0
 */
#endif
