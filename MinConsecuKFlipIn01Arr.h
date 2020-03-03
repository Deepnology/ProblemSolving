#ifndef _MIN_CONSECU_K_FLIP_IN_01_ARR_H
#define _MIN_CONSECU_K_FLIP_IN_01_ARR_H
#include "Debug.h"
/*
Leetcode: Minimum Number of K Consecutive Bit Flips
In an array A containing only 0s and 1s, a K-bit flip consists of choosing a (contiguous) subarray of length K and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
Return the minimum number of K-bit flips required so that there is no 0 in the array.
If it is not possible, return -1.
Example 1:
Input: A = [0,1,0], K = 1
Output: 2
Explanation: Flip A[0], then flip A[2].
Example 2:
Input: A = [1,1,0], K = 2
Output: -1
Explanation: No matter how we flip subarrays of size 2, we can't make the array become [1,1,1].
Example 3:
Input: A = [0,0,0,1,0,1,1,0], K = 3
Output: 3
Explanation:
Flip A[0],A[1],A[2]: A becomes [1,1,1,1,0,1,1,0]
Flip A[4],A[5],A[6]: A becomes [1,1,1,1,1,0,0,0]
Flip A[5],A[6],A[7]: A becomes [1,1,1,1,1,1,1,1]
 */
class MinConsecuKFlipIn01Arr
{
public:
    int SlideWindow(const std::vector<int> & A, int K)
    {
        int N = A.size();
        std::vector<int> isKFlip(N, 0);//isKFlip[i]==1: perform K flip at A[i]
        int countFlip = 0;//count of flips in window A[i-k+1:i-1], which affects num flips of A[i]
        int res = 0;
        for (int i = 0; i < N; ++i)
        {
            if (i >= K)
                countFlip -= isKFlip[i-K];
            //the two cases we need to flip A[i]:
            if (A[i]==0 && countFlip%2==0 || //A[i]=0 and hasn't been flipped
                A[i]==1 && countFlip%2==1) //A[i]=1 and has been flipped to 0
            {
                if (i+K-1 >= N) return -1;
                isKFlip[i] = 1;
                ++countFlip;
                ++res;
            }
        }
        std::cout << "MinConsecuKFlipIn01Arr SlideWindow for [" << Debug::ToStr1D<int>()(A) << "], K=" << K << ": " << res << std::endl;
        return res;
    }
};
/*
MinConsecuKFlipIn01Arr SlideWindow for [0, 0, 0, 1, 0, 1, 1, 0], K=3: 3
 */
#endif
