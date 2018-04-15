/*Facebook*/
#ifndef _TWO_PAIRS_SUM_H
#define _TWO_PAIRS_SUM_H
#include "Debug.h"
/*
Given an integer array, find 4 elements such that v[i]+v[j]=v[k]+v[l], where i,j,k,l are 4 different indices.
return [i,j,k,l], [i,j,l,k], [j,i,k,l], [j,i,l,k]
 */
class TwoPairsSum
{
public:
    TwoPairsSum(){}

    std::vector<std::vector<int>> FindAllIndexTwoPairs(std::vector<int> && v)//O(N^3) time avg, O(N^4) time worst case
    {
        int N = v.size();
        std::vector<std::vector<int>> res;
        for (int i = 0; i < N-3; ++i)
        {
            for (int j = i + 1; j < N-2; ++j)
            {
                int sum = v[i]+v[j];
                std::vector<std::vector<int>> right = FindAllIndexPairs(v, j+1, N-1, sum);
                for (auto & p : right)
                {
                    res.push_back({i, j, p[0], p[1]});
                    res.push_back({j, i, p[0], p[1]});
                    res.push_back({i, j, p[1], p[0]});
                    res.push_back({j, i, p[1], p[0]});
                }
            }
        }
        std::cout << "TwoPairsSum FindAllIndexTwoPairs for \"" << Debug::ToStr1D<int>()(v) << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
private:
    std::vector<std::vector<int>> FindAllIndexPairs(std::vector<int> & v, int begin, int end, int tgt)//O(N) time avg, O(N^2) time worst case
    {
        std::unordered_map<int, std::vector<int>> toIdx;//<entry, arr of idx>
        for (int i = begin; i <= end; ++i)
            toIdx[v[i]].push_back(i);
        std::vector<std::vector<int>> res;
        for (int i = begin; i <= end; ++i)
        {
            if (toIdx.count(v[i]) == 0) continue;
            if (v[i] + v[i] == tgt && toIdx[v[i]].size() >= 2)
            {
                int M = toIdx[v[i]].size();
                for (int j = 0; j < M-1; ++j)
                    for (int k = j+1; k < M; ++k)
                        res.push_back(std::vector<int>({toIdx[v[i]][j], toIdx[v[i]][k]}));
            }
            else if (toIdx.count(tgt-v[i]))
            {
                int M1 = toIdx[v[i]].size();
                int M2 = toIdx[tgt-v[i]].size();
                for (int j = 0; j < M1; ++j)
                    for (int k = 0; k < M2; ++k)
                        res.push_back(std::vector<int>({toIdx[v[i]][j], toIdx[tgt-v[i]][k]}));
            }
            toIdx.erase(v[i]);
            toIdx.erase(tgt-v[i]);
        }
        return res;
    }
public:
    std::vector<std::vector<int>> BruteForce(std::vector<int> && v)//O(N^4) time
    {
        std::vector<std::vector<int>> res;
        int N = v.size();
        for (int i = 0; i < N-3; ++i)
        {
            for (int j = i+1; j < N-2; ++j)
            {
                int sum = v[i]+v[j];
                for (int k = j+1; k < N-1; ++k)
                {
                    for (int l = k+1; l < N; ++l)
                    {
                        if (v[k]+v[l] == sum)
                        {
                            res.push_back({i, j, k, l});
                            res.push_back({j, i, k, l});
                            res.push_back({i, j, l, k});
                            res.push_back({j, i, l, k});
                        }
                    }
                }
            }
        }
        std::cout << "TwoPairsSum BruteForce for [" << Debug::ToStr1D<int>()(v) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }

};
/*
TwoPairsSum BruteForce for [1, 1, 1, 1, 1]:
 [0,1,2,3], [1,0,2,3], [0,1,3,2], [1,0,3,2], [0,1,2,4], [1,0,2,4], [0,1,4,2], [1,0,4,2], [0,1,3,4], [1,0,3,4], [0,1,4,3], [1,0,4,3], [0,2,3,4], [2,0,3,4], [0,2,4,3], [2,0,4,3], [1,2,3,4], [2,1,3,4], [1,2,4,3], [2,1,4,3]
TwoPairsSum FindAllIndexTwoPairs for "1, 1, 1, 1, 1":
 [0,1,2,3], [1,0,2,3], [0,1,3,2], [1,0,3,2], [0,1,2,4], [1,0,2,4], [0,1,4,2], [1,0,4,2], [0,1,3,4], [1,0,3,4], [0,1,4,3], [1,0,4,3], [0,2,3,4], [2,0,3,4], [0,2,4,3], [2,0,4,3], [1,2,3,4], [2,1,3,4], [1,2,4,3], [2,1,4,3]
 */
#endif
