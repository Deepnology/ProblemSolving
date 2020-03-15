#ifndef _CONNECTED_COMPONENTS_BY_INT_COMMON_FACTOR_H
#define _CONNECTED_COMPONENTS_BY_INT_COMMON_FACTOR_H
#include "Debug.h"
/*
Leetcode: Largest Component Size by Common Factor
Given a non-empty array of unique positive integers A, consider the following graph:
There are A.length nodes, labelled A[0] to A[A.length - 1];
There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.
Example 1:
Input: [4,6,15,35]
Output: 4
Example 2:
Input: [20,50,9,63]
Output: 2
Example 3:
Input: [2,3,6,7,4,12,21,39]
Output: 8
 */
class ConnectedComponentsByIntCommonFactor
{
public:
    ConnectedComponentsByIntCommonFactor(){}


public:
    //similar to SimilarStringGroups
    int BFS(std::vector<int> && A)
    {
        //BFS: O(N) time
        int N = A.size();
        std::unordered_map<int, std::unordered_set<int>> pfToNums;//primeFactorToNums
        std::unordered_map<int, std::unordered_set<int>> numToPFs;//numToPrimeFactors
        for (auto & n : A)
        {
            auto primeFactors = AllPrimeFactors(n);
            for (auto & pf : primeFactors)
                pfToNums[pf].insert(n);
            numToPFs.insert({n, primeFactors});
        }
        int res = 0;
        std::unordered_set<int> visit;
        while (!pfToNums.empty())//BFS
        {
            int count = 0;
            std::queue<int> que;
            for (auto & n : pfToNums.begin()->second)
            {
                visit.insert(n);
                que.push(n);
            }
            pfToNums.erase(pfToNums.begin());
            while (!que.empty())
            {
                int cur = que.front();
                que.pop();
                ++count;
                for (auto & pf : numToPFs[cur])
                {
                    if (pfToNums.count(pf))
                    {
                        for (auto & num : pfToNums[pf])
                            if (!visit.count(num))
                            {
                                visit.insert(num);
                                que.push(num);
                            }
                        pfToNums.erase(pf);
                    }
                }
            }
            res = std::max(res, count);
        }
        std::cout << "ConnectedComponentsByIntCommonFactor BFS for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
    int DFS(std::vector<int> && A)
    {
        //DFS: O(N!) time
        int N = A.size();
        std::unordered_set<int> visit;
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (!visit.count(A[i]))
            {
                visit.insert(A[i]);
                int count = 1;
                DFS(A, i+1, A[i], visit, count);
                res = std::max(res, count);
            }
        }
        std::cout << "ConnectedComponentsByIntCommonFactor DFS for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
    int UnionFind(std::vector<int> && A)
    {
        //Union Find: O(N^2logN) time
        int N = A.size();
        std::vector<int> chdToP(N);
        for (int i = 0; i < N; ++i)
            chdToP[i] = i;
        int countComponent = N;
        std::vector<int> countNode(N, 1);
        for (int i = 0; i < N-1; ++i)
            for (int j = i+1; j < N; ++j)
            {
                if (std::gcd(A[i],A[j]) > 1)
                {
                    int root1 = Find(chdToP, i);
                    int root2 = Find(chdToP, j);
                    if (root1 != root2)
                    {
                        chdToP[root2] = root1;
                        countNode[root1] += countNode[root2];
                        --countComponent;
                    }
                }
            }
        //std::cout << countComponent << std::endl;
        int res = 0;
        for (auto & nodes : countNode)
            res = std::max(res, nodes);
        std::cout << "ConnectedComponentsByInCommonFactor UnionFind for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
private:
    int Find(std::vector<int> & chdToP, int chd)
    {
        int cur = chd;
        while (cur != chdToP[cur])
        {
            chdToP[cur] = chdToP[chdToP[cur]];
            cur = chdToP[cur];
        }
        return cur;
    }
    void DFS(std::vector<int> & A, int begin, int cur, std::unordered_set<int> & visit, int & count)
    {
        int N = A.size();
        for (int i = begin; i < N; ++i)
        {
            if (!visit.count(A[i]) && std::gcd(cur,A[i]) > 1)
            {
                visit.insert(A[i]);
                ++count;
                DFS(A, begin, A[i], visit, count);
            }
        }
    }
    std::unordered_set<int> AllPrimeFactors(int n)
    {
        std::unordered_set<int> res;
        while (n % 2 == 0)
        {
            res.insert(2);
            n /= 2;
        }
        for (int i = 3; i*i <= n; i += 2)
        {
            while (n % i == 0)
            {
                res.insert(i);
                n /= i;
            }
        }
        if (n > 2) res.insert(n);
        return res;
    }
};
/*
ConnectedComponentsByInCommonFactor DFS for [4, 6, 15, 35]: 4
ConnectedComponentsByInCommonFactor BFS for [4, 6, 15, 35]: 4
ConnectedComponentsByInCommonFactor UnionFind for [4, 6, 15, 35]: 4
 */
#endif
