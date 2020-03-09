#ifndef _ARR_PERMUTATION_CONSECU_NUM_SUM_IS_SQUARE_H
#define _ARR_PERMUTATION_CONSECU_NUM_SUM_IS_SQUARE_H
#include "Debug.h"
/*
Leetcode: Number of Squareful Arrays
Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.
Return the number of permutations of A that are squareful.
Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].
Example 1:
Input: [1,17,8]
Output: 2
Explanation:
[1,8,17] and [17,8,1] are the valid permutations.
Example 2:
Input: [2,2,2]
Output: 1
 */
class ArrPermutationConsecuNumSumIsSquare
{
public:
    ArrPermutationConsecuNumSumIsSquare(){}

    int DFS(std::vector<int> && A)
    {
        //O(N!) time
        int res = 0;
        recur(A, 0, res);
        std::cout << "ArrPermutationConsecuNumSumIsSquare DFS for [" << Debug::ToStr1D<int>()(A) << "]: " << res << std::endl;
        return res;
    }
    void recur(std::vector<int> & A, int begin, int & res)
    {
        int N = A.size();
        if (begin == N)
        {
            ++res;
            return;
        }
        std::unordered_set<int> visit;
        for (int cur = begin; cur < N; ++cur)
        {
            if (visit.count(A[cur])) continue;
            visit.insert(A[cur]);
            if (begin==0 || pow((int)sqrt(A[begin-1]+A[cur]),2) == A[begin-1]+A[cur])
            {
                std::swap(A[begin],A[cur]);
                recur(A, begin+1, res);
                std::swap(A[begin],A[cur]);
            }
        }
    }
};
/*
ArrPermutationConsecuNumSumIsSquare DFS for [1, 17, 8]: 2
 */
#endif
