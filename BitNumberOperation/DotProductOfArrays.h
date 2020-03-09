/*Facebook*/
#ifndef _DOT_PRODUCT_OF_ARRAYS_H
#define _DOT_PRODUCT_OF_ARRAYS_H
#include "Debug.h"
/*
1. Given 2 sparse arrays with many 0s.
Compute the dot product of them.

2. Given 2 compressed arrays with <count,val> pairs.
Compute the dot product of them.

https://www.geeksforgeeks.org/find-maximum-dot-product-two-arrays-insertion-0s/
3. Find Maximum dot product of two arrays with insertion of 0’s
Given two arrays of positive integers of size m and n where m > n.
We need to maximize the dot product by inserting zeros in the second array but we cannot disturb the order of elements.
 */
class DotProductOfArrays
{
public:
    DotProductOfArrays(){}

    int TwoSparseArrays(const std::vector<int> & A, const std::vector<int> & B)
    {
        std::unordered_map<int,int> idxToVal1;
        int N = A.size();
        for (int i = 0; i < N; ++i)
            if (A[i] != 0)
                idxToVal1[i] = A[i];
        std::unordered_map<int,int> idxToVal2;
        int M = B.size();
        for (int i = 0; i < M; ++i)
            if (B[i] != 0)
                idxToVal2[i] = B[i];

        int res = 0;
        for (const auto & p : idxToVal1)
            if (idxToVal2.count(p.first))
                res += p.second * idxToVal2[p.first];

        std::cout << "DotProductOfArrays TwoSparseArrays for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << res << std::endl;
        return res;
    }


    int TwoCompressedArrays(const std::vector<std::vector<int>> & A, const std::vector<std::vector<int>> & B)//<count,val>
    {
        int N = A.size();
        int M = B.size();
        int i = 0; int ii = 0;
        int j = 0; int jj = 0;
        int res = 0;
        while (i < N && j < M)
        {
            res += A[i][1] * B[j][1];
            ++ii;
            if (ii == A[i][0])
            {
                ii = 0;
                ++i;
            }
            ++jj;
            if (jj == B[j][0])
            {
                jj = 0;
                ++j;
            }
        }

        std::cout << "DotProductOfArrays TwoCompressedArrays for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << res << std::endl;
        return res;
    }

    int MaxWInsert0s_DP2D(const std::vector<int> & A, const std::vector<int> & B)//Assume A.size() <= B.size()
    {
        int N = A.size();
        int M = B.size();
        std::vector<std::vector<int>> dp(N+1, std::vector<int>(M+1, 0));
        for (int i = 1; i <= N; ++i)//loop thru the smaller array
            for (int j = i; j <= M; ++j)//loop thru the larger array
                dp[i][j] = std::max(dp[i-1][j-1] + A[i-1]*B[j-1] //include B[j]
                        , dp[i][j-1]); //exclude B[j], which means insert 0 in A

        Debug::Print2D<int>()(dp, false);
        std::cout << "DotProductOfArrays MaxWInsert0s_DP2D for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << dp[N][M] << std::endl;
        return dp[N][M];
    }
};
/*
DotProductOfArrays TwoSparseArrays for [1, 0, 0, 0, 3, 2, 0, 5], [0, 0, 2, 1, 0, 4, 5, 0, 1, 0]: 8
DotProductOfArrays TwoCompressedArrays for [[3,2], [4,1], [2,3]], [[6,2], [8,1]]: 25
[rY][cX]
Row#0	= 0, 0, 0, 0, 0, 0
Row#1	= 0, 6, 9, 9, 21, 24
Row#2	= 0, 0, 24, 24, 51, 69
Row#3	= 0, 0, 0, 31, 73, 107

DotProductOfArrays MaxWInsert0s_DP2D for [3, 6, 7], [2, 3, 1, 7, 8]: 107
 */
#endif
