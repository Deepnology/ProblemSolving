#ifndef _INSERT_DELETE_GET_WEIGHTED_RANDOM_H
#define _INSERT_DELETE_GET_WEIGHTED_RANDOM_H
#include "Debug.h"
/*
Two Sigma
 */
class InsertDeleteGetWeightedRandom
{
    std::unordered_map<std::string, int> keyToIdx;
    std::vector<std::pair<std::string, int>> prefixSum;
public:
    InsertDeleteGetWeightedRandom(){}

    std::string GetRandom() const
    {
        if (prefixSum.empty()) return "";
        int r = (rand() % prefixSum.back().second) + 1;
        int left = 0;
        int right = prefixSum.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (prefixSum[mid].second >= r)
                right = mid - 1;
            else
                left = mid + 1;
        }
        //now left is lower bound

        std::cout << "GetRandomFrom [" << Debug::ToStr1D<std::string, int>()(prefixSum) << "]: " << prefixSum[left].first << std::endl;
        return prefixSum[left].first;
    }

    void Insert(const std::string & key, int weight)
    {
        auto itr = keyToIdx.find(key);
        if (itr == keyToIdx.end())
        {
            if (weight != 0)//add
            {
                prefixSum.push_back({key, prefixSum.empty() ? weight : prefixSum.back().second + weight});
                keyToIdx.insert({key, prefixSum.size() - 1});
            }
        }
        else//already exist
        {
            int idx = itr->second;
            if (weight != 0)//update
            {
                int diff = weight - prefixSum[idx].second;
                for (int i = idx; i < prefixSum.size(); ++i)
                    prefixSum[i].second += diff;
            }
            else//reomve
            {
                int diff = prefixSum[idx].second - (idx==0 ? 0 : prefixSum[idx-1].second);
                auto nxt = prefixSum.erase(prefixSum.begin() + idx);
                for (int i = nxt - prefixSum.begin(); i < prefixSum.size(); ++i)
                {
                    prefixSum[i].second -= diff;
                    keyToIdx[prefixSum[i].first] = i;
                }
                keyToIdx.erase(itr);
            }
        }
    }
};
/*
GetRandomFrom [[A,1]]: A
GetRandomFrom [[A,1], [B,3]]: B
GetRandomFrom [[A,3], [B,5]]: A
GetRandomFrom [[A,3], [B,5], [C,6]]: B
GetRandomFrom [[B,2], [C,3]]: C
GetRandomFrom [[C,1]]: C
GetRandomFrom [[A,1], [B,3], [C,6]]: A
GetRandomFrom [[B,2], [C,5]]: C
GetRandomFrom [[C,3]]: C
 */
#endif
