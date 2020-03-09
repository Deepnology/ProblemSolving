#ifndef _SORT_ARR_WITH_MULTI_SORTED_SUB_ARRS_H
#define _SORT_ARR_WITH_MULTI_SORTED_SUB_ARRS_H
#include "Debug.h"
/*

 */
class SortArrWithMultiSortedSubArrs
{
public:
    SortArrWithMultiSortedSubArrs(){}

    std::vector<int> MinHeap(const std::vector<int> & v)
    {
        int N = v.size();
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> minHeap;
        minHeap.push({v[0],0});
        std::unordered_set<int> visit;
        visit.insert(0);
        for (int i = 0; i < N-1; ++i)
        {
            if (v[i] > v[i+1])
            {
                minHeap.push({v[i+1],i+1});
                visit.insert(i+1);
            }
        }
        std::vector<int> res;
        while(!minHeap.empty())
        {
            auto top = minHeap.top(); minHeap.pop();
            int val = top.first;
            int idx = top.second;
            res.push_back(val);
            if (idx+1 < N && !visit.count(idx+1))
            {
                visit.insert(idx+1);
                minHeap.push({v[idx+1],idx+1});
            }
        }

        std::cout << "SortArrWithMultiSortedSubArrs MinHeap for [" << Debug::ToStr1D<int>()(v) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
SortArrWithMultiSortedSubArrs MinHeap for [7, 1, 3, 5, 2, 4, 6, 0, 9, 7]: 0, 1, 2, 3, 4, 5, 6, 7, 7, 9
 */
#endif
