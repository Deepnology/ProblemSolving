#ifndef _FIND_NUM_IDX_MOVE_TO_FRONT_IDX_SEQ_ARR_H
#define _FIND_NUM_IDX_MOVE_TO_FRONT_IDX_SEQ_ARR_H
#include "Debug.h"
/*
Leetcode: Queries on a Permutation With Key
Given the array queries of positive integers between 1 and m, you have to process all queries[i] (from i=0 to i=queries.length-1) according to the following rules:
In the beginning, you have the permutation P=[1,2,3,...,m].
For the current i, find the position of queries[i] in the permutation P (indexing from 0) and then move this at the beginning of the permutation P.
 Notice that the position of queries[i] in P is the result for queries[i].
Return an array containing the result for the given queries.
Example 1:
Input: queries = [3,1,2,1], m = 5
Output: [2,1,2,1]
Explanation: The queries are processed as follow:
For i=0: queries[i]=3, P=[1,2,3,4,5], position of 3 in P is 2, then we move 3 to the beginning of P resulting in P=[3,1,2,4,5].
For i=1: queries[i]=1, P=[3,1,2,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,3,2,4,5].
For i=2: queries[i]=2, P=[1,3,2,4,5], position of 2 in P is 2, then we move 2 to the beginning of P resulting in P=[2,1,3,4,5].
For i=3: queries[i]=1, P=[2,1,3,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,2,3,4,5].
Therefore, the array containing the result is [2,1,2,1].
Example 2:
Input: queries = [4,1,2,2], m = 4
Output: [3,1,2,0]
Example 3:
Input: queries = [7,5,5,8,3], m = 8
Output: [6,5,0,7,5]
 */
class FindNumIdxMoveToFrontIdxSeqArr
{
public:
    std::vector<int> BruteForce(std::vector<int> & query, int m)
    {
        //Approach1: O(N^2) time
        std::vector<int> perm;
        for (auto i = 0; i < m; ++i)
            perm.push_back(i+1);
        std::vector<int> res;
        for (auto i = 0; i < query.size(); ++i)
        {
            int foundIdx = 0;
            while (foundIdx < m && perm[foundIdx] != query[i])
                ++foundIdx;
            perm.erase(perm.begin()+foundIdx);
            perm.insert(perm.begin(), query[i]);
            res.push_back(foundIdx);
        }
        return res;
    }
private:
    std::vector<int> bit;//bit[0] is dummy
    void update(int i, int val)
    {
        ++i;//convert to bit index
        while (i < bit.size())
        {
            bit[i] += val;
            i += i & -i;
        }
    }
    int prefixSum(int i)
    {
        ++i;//convert to bit index
        int res = 0;
        while(i)
        {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }
public:
    std::vector<int> UseBinaryIndexedTree(std::vector<int> & query, int m)
    {
        //Approach2: binary indexed tree: use prefixSum for the all the movements of previous nums
        int N = query.size();
        bit.resize(N+m+1, 0);
        std::vector<int> res;//position of cur query[i] in perm
        std::unordered_map<int,int> toIdx;
        for (auto i = 1; i <= m; ++i)
        {
            toIdx[i] = i+N-1;
            update(toIdx[i], 1);//init 1 at each index such that prefixSum at each index represent dist from begin
        }
        //[0:N-1]<-[N:N+m-1]: move query[i] num from [N:N+m-1]] to [0:N-1] in reverse order: N-1, N-2, N-3, ..., 0
        //such that later moved nums will contribute prefixSums for early moved nums
        int cur = N-1;
        for (auto i = 0; i < query.size(); ++i)
        {
            res.push_back(prefixSum(toIdx[query[i]])-1);//-1: convert to 0-based index
            update(toIdx[query[i]], -1);//remove the num from that index
            update(cur, 1);//add the num at the new index
            toIdx[query[i]] = cur;
            --cur;
        }
        return res;
    }
};
#endif
