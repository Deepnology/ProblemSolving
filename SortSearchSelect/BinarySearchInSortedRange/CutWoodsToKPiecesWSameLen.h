#ifndef _CUT_WOODS_TO_K_PIECES_W_SAME_LEN_H
#define _CUT_WOODS_TO_K_PIECES_W_SAME_LEN_H
#include "Debug.h"
/*
Lintcode: Wood Cut
Given n pieces of wood with length L[i] (integer array).
Cut them into small pieces to guarantee you could have equal or more than k pieces with the same length.
What is the longest length you can get from the n pieces of wood?
Given L & k, return the maximum length of the small pieces.
 */
class CutWoodsToKPiecesWSameLen
{
public:
    CutWoodsToKPiecesWSameLen(){}

    int FindMaxLen_BinarySearch(const std::vector<int> & v, int k)//O(N*log(maxLen)) time
    {
        int N = v.size();
        if (N == 0) return 0;
        int maxLen = *std::max_element(v.begin(), v.end());
        if (k == 0) return maxLen;
        int left = maxLen/k;
        int right = maxLen;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (mid == 0) return 0;
            int count = 0;
            for (const int & len : v)
                count += len/mid;
            if (count >= k)
                left = mid+1;
            else
                right = mid-1;
        }
        //now right is lower bound
        if (right == 0) return 0;
        int count = 0;
        for (const int & len : v)
            count += len/right;
        int res = count >= k ? right : 0;

        std::cout << "CutWoodsToKPiecesWSameLen FindMaxLen_BinarySearch for k=" << k << ", from [" << Debug::ToStr1D<int>()(v) << "]: " << res << std::endl;
        return res;
    }
};
/*
CutWoodsToKPiecesWSameLen FindMaxLen_BinarySearch for k=7, from [232, 124, 456]: 114
 */
#endif
