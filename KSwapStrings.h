#ifndef _K_SWAP_STRINGS_H
#define _K_SWAP_STRINGS_H
#include "Debug.h"
/*
Leetcode: K-Similar Strings
Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.
Given two anagrams A and B, return the smallest K for which A and B are K-similar.
Example 1:
Input: A = "ab", B = "ba"
Output: 1
Example 2:
Input: A = "abc", B = "bca"
Output: 2
Example 3:
Input: A = "abac", B = "baca"
Output: 2
Example 4:
Input: A = "aabc", B = "abca"
Output: 2
Note:
1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
 */
class KSwapStrings
{
public:
    int BFS(std::string A, std::string B)
    {
        std::unordered_set<std::string> visit;
        std::queue<std::pair<std::string, int>> que;//<stringOfA, indexOfNxtToTest>
        int steps = 0;
        int N = A.size();
        for (int i = 0; i < N; ++i)
        {
            if (A[i] != B[i])
            {
                que.push({A,i});
                visit.insert(A);
                break;
            }
        }
        while (!que.empty())
        {
            int levelCount = que.size();
            while (levelCount-->0)
            {
                auto p = que.front(); que.pop();
                std::string cur = p.first;
                int idx = p.second;
                if (cur == B)
                {
                    std::cout << "KSwapStrings BFS for " << A << " and " << B << ": " << steps << std::endl;
                    return steps;
                }
                while (cur[idx] == B[idx])
                    ++idx;
                //now idx is the nxt non match
                for (int i = idx+1; i < N; ++i)
                {
                    if (cur[i]==B[i]) continue;
                    if (cur[i]==B[idx])
                    {
                        std::swap(cur[idx],cur[i]);
                        if (!visit.count(cur))
                        {
                            visit.insert(cur);
                            que.push({cur,idx+1});
                        }
                        std::swap(cur[idx],cur[i]);
                    }
                }
            }
            ++steps;
        }

        return steps;
    }
};
/*
KSwapStrings BFS for aabc and abca: 2
 */
#endif
