#ifndef _KTH_SMALLEST_NUM_IN_MULTIPLICATION_TABLE_H
#define _KTH_SMALLEST_NUM_IN_MULTIPLICATION_TABLE_H
#include "Debug.h"
/*
Leetcode: Kth Smallest Number in Multiplication Table
Nearly every one have used the Multiplication Table.
But could you find out the k-th smallest number quickly from the multiplication table?
Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.
Example 1:
Input: m = 3, n = 3, k = 5
Output:
Explanation:
The Multiplication Table:
1	2	3
2	4	6
3	6	9
The 5-th smallest number is 3 (1, 2, 2, 3, 3).
Example 2:
Input: m = 2, n = 3, k = 6
Output:
Explanation:
The Multiplication Table:
1	2	3
2	4	6
The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
 */
class KthSmallestNumInMultiplicationTable
{
public:
    KthSmallestNumInMultiplicationTable(){}

    struct Greater
    {
        bool operator()(const std::pair<int,int> & a, const std::pair<int,int> & b) const
        {
            return a.first > b.first;
        }
    };
    int MinHeap(int m, int n, int k)
    {
        std::unordered_set<int> visit;
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, Greater> minHeap;
        minHeap.push({1, 0});
        visit.insert(0);
        --k;
        while(k-- > 0)
        {
            auto cur = minHeap.top(); minHeap.pop();
            int val = cur.first;
            int i = cur.second / n;
            int j = cur.second % n;
            if (i+1 < m && !visit.count((i+1)*n+j))
            {
                visit.insert((i+1)*n+j);
                minHeap.push({(i+1+1)*(j+1),(i+1)*n+j});
            }
            if (j+1 < n && !visit.count(i*n+j+1))
            {
                visit.insert(i*n+j+1);
                minHeap.push({(i+1)*(j+1+1),i*n+j+1});
            }
        }
        return minHeap.top().first;
    }

    int BinarySearchSpace(int m, int n, int k)
    {
        int left = 1;
        int right = m*n;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            int count = 0;
            for (int row = 1; row <= m; ++row)
                count += std::min(mid / row, n);
            if (count >= k)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
#endif
