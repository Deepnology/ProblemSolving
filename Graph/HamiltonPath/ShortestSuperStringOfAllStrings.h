#ifndef _SHORTEST_SUPER_STRING_OF_ALL_STRINGS_H
#define _SHORTEST_SUPER_STRING_OF_ALL_STRINGS_H
#include "Debug.h"
/*
Find the shortest superstring
Given an array A of strings, find any smallest string that contains each string in A as a substring.
We may assume that no string in A is substring of another string in A.
Example 1:
Input: ["alex","loves","leetcode"]
Output: "alexlovesleetcode"
Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
Example 2:
Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
Output: "gctaagttcatgcatc"
Note:
1 <= A.length <= 12
1 <= A[i].length <= 20
 */
class ShortestSuperStringOfAllStrings
{
public:
    //traveling salesman problem: find shortest path from a src node that visit each node only once and return to it
    //(shortest Hamiltonian cycle)
    std::string DP(std::vector<std::string> && A)
    {//O(N^2 * 2^N) time
        int N = A.size();
        std::vector<std::vector<int>> graph(N, std::vector<int>(N, 0));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (i != j)
                {
                    //ex: catg, atgcatc: 3
                    for (int k = std::min(A[i].size(), A[j].size()); k > 0; --k)
                    {
                        if (A[i].substr(A[i].size()-k) == A[j].substr(0, k))
                        {
                            graph[i][j] = k; //A[i][N-k:N-1] == A[j][0:k-1]
                            break;
                        }
                    }
                }

        std::vector<std::vector<std::string>> dp(1<<N, std::vector<std::string>(N));
        //dp[state][lastVisitNode] = shortest super string
        for (int i = 0; i < N; ++i)
            dp[1<<i][i] = A[i];

        for (int state = 1; state < 1<<N; ++state) //enumerate all possible states
        {
            for (int i = 0; i < N; ++i) //cur
                if (state & (1<<i))
                {
                    for (int j = 0; j < N; ++j) //try j to i
                        if (j != i && (state & (1<<j)))
                        {
                            //now state contains both i and j
                            //see if cur path j->i is a shorter path to i
                            std::string nxt = dp[state^(1<<i)][j] + A[i].substr(graph[j][i]);//append A[i]'s uncommon part
                            if (dp[state][i].empty() || nxt.size() < dp[state][i].size())
                                dp[state][i] = nxt;
                        }
                }
        }

        int lastState = (1<<N)-1;//111...111 when all nodes have been visited
        std::string res = dp[lastState][0];
        for (auto & s : dp[lastState])
            if (s.size() < res.size())
                res = s;

        std::cout << "ShortestSuperStringOfAllStrings DP for [" << Debug::ToStr1D<std::string>()(A) << "]: " << res << std::endl;
        return res;
    }
};
/*
ShortestSuperStringOfAllStrings DP for [catg, ctaagt, gcta, ttca, atgcatc]: gctaagttcatgcatc
 */
#endif
