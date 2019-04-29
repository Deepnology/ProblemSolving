#ifndef _MIN_SWAP_TO_PAIR_COUPLES_IN_ARRAY_H
#define _MIN_SWAP_TO_PAIR_COUPLES_IN_ARRAY_H
#include "Debug.h"
/*
Leetcode: Couples Holding Hands
N couples sit in 2N seats arranged in a row and want to hold hands.
We want to know the minimum number of swaps so that every couple is sitting side by side.
A swap consists of choosing any two people, then they stand up and switch seats.
The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order,
 the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).
The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.
Example 1:
Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
Example 2:
Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.
 */
class MinSwapToPairCouplesInArray
{
public:
    MinSwapToPairCouplesInArray(){}

    int UnionFind(std::vector<int> && row)
    {
        int N = row.size() / 2;//N is couple count
        //each couple is a vertex in graph without any edges
        std::vector<int> coupleToP(N);
        for (int i = 0; i < N; ++i)
            coupleToP[i] = i;
        int countComponent = N;

        for (int i = 0; i < N; ++i)
        {
            int p1 = row[2*i];
            int p2 = row[2*i+1];
            int coupleIdx1 = p1 / 2;
            int coupleIdx2 = p2 / 2;
            int coupleRoot1 = Find(coupleToP, coupleIdx1);
            int coupleRoot2 = Find(coupleToP, coupleIdx2);
            if (coupleRoot1 != coupleRoot2)
            {
                //union coupleRoot1 with coupleRoot2
                coupleToP[coupleRoot2] = coupleRoot1;
                --countComponent;
            }
        }
        //now there are countComponent connected components of couple
        int res = N - countComponent;//countCouple - countCoupleComponent

        //============DEBUG=============
        std::vector<int> coupleIdx;
        std::vector<int> coupleRoot;
        for (int i = 0; i < N; ++i)
        {
            coupleIdx.push_back(i);
            coupleRoot.push_back(Find(coupleToP, i));
        }
        std::cout << "coupleIdx:    " << Debug::ToStr1D<int>()(coupleIdx) << std::endl;
        std::cout << "coupleRoot:   " << Debug::ToStr1D<int>()(coupleRoot) << std::endl;

        std::cout << "MinSwapToPairCouplesInArray UnionFind for [" << Debug::ToStr1D<int>()(row) << "]: " << res << std::endl;
        return res;
    }
private:
    int Find(std::vector<int> & coupleToP, int chd)
    {
        int cur = chd;
        while (coupleToP[cur] != cur)
        {
            coupleToP[cur] = coupleToP[coupleToP[cur]];
            cur = coupleToP[cur];
        }
        return cur;
    }
};
/*
coupleIdx:    0, 1
coupleRoot:   0, 0
MinSwapToPairCouplesInArray UnionFind for [0, 2, 1, 3]: 1
 */
#endif
