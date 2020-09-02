#ifndef _K_TH_SMALLEST_COL_SUM_FROM_SORTED_ROWS_H
#define _K_TH_SMALLEST_COL_SUM_FROM_SORTED_ROWS_H
#include "Debug.h"
/*
Leetcode: Find the Kth Smallest Sum of a Matrix With Sorted Rows
You are given an m * n matrix, mat, and an integer k, which has its rows sorted in non-decreasing order.
You are allowed to choose exactly 1 element from each row to form an array.
Return the Kth smallest array sum among all possible arrays.
Example 1:
Input: mat = [[1,3,11],[2,4,6]], k = 5
Output: 7
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
Example 2:
Input: mat = [[1,3,11],[2,4,6]], k = 9
Output: 17
Example 3:
Input: mat = [[1,10,10],[1,4,5],[2,3,6]], k = 7
Output: 9
Explanation: Choosing one element from each row, the first k smallest sum are:
[1,1,2], [1,1,3], [1,4,2], [1,4,3], [1,1,6], [1,5,2], [1,5,3]. Where the 7th sum is 9.
Example 4:
Input: mat = [[1,1,10],[2,2,9]], k = 7
Output: 12
 */
class KthSmallestColSumFromSortedRows
{
public:
    int BruteForceMinHeap(std::vector<std::vector<int>> & mat, int k)
    {
        //O(k*logk*N*M) time
        int N = mat.size();
        std::multiset<int> minHeap; //allows duplicates
        for (int i = 0; i < std::min(k,(int)mat[0].size()); ++i)
            minHeap.insert(mat[0][i]);

        for (int i = 1; i < N; ++i)
        {
            std::multiset<int> nxtMinHeap;
            for (auto itr = minHeap.begin(); itr != minHeap.end(); ++itr)
                for (int j = 0; j < mat[i].size(); ++j)
                {
                    nxtMinHeap.insert(*itr + mat[i][j]);
                    if (nxtMinHeap.size() > k) nxtMinHeap.erase(std::prev(nxtMinHeap.end()));
                }
            minHeap = nxtMinHeap;
        }
        return *minHeap.rbegin();
    }

    int RepeatGetMinKPairSumsFrom2Arr(std::vector<std::vector<int>> & mat, int k)
    {
        //O(k*logk*N) time
        int N = mat.size();
        std::vector<int> minKPairSums;
        for (int i = 0; i < std::min(k, (int)mat[0].size()); ++i)
            minKPairSums.push_back(mat[0][i]);

        for (int i = 1; i < N; ++i)
        {
            minKPairSums = GetMinKPairSums(minKPairSums, mat[i], k);
        }
        return minKPairSums.back();
    }
private:
    std::vector<int> GetMinKPairSums(const std::vector<int> & a, const std::vector<int> & b, int k)
    {
        std::multimap<int, std::pair<int,int>> minHeap; //allows duplicate
        minHeap.insert({a[0]+b[0],{0,0}});
        k = std::min(k, (int)a.size()*(int)b.size());
        std::unordered_set<int> visit;
        visit.insert(0*5000+0);
        std::vector<int> res;
        while (k-- > 0)
        {
            res.push_back(minHeap.begin()->first);
            int i = minHeap.begin()->second.first;
            int j = minHeap.begin()->second.second;
            minHeap.erase(minHeap.begin());
            if (i+1 < a.size() && !visit.count((i+1)*5000+j))
            {
                visit.insert((i+1)*5000+j);
                minHeap.insert({a[i+1]+b[j],{i+1,j}});
            }
            if (j+1 < b.size() && !visit.count(i*5000+j+1))
            {
                visit.insert(i*5000+j+1);
                minHeap.insert({a[i]+b[j+1],{i,j+1}});
            }
        }
        return res;
    }
};
#endif
