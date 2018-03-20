#ifndef _SORT_BY_MIN_SWAP_PAIRS_OF_2_ARRAYS_H
#define _SORT_BY_MIN_SWAP_PAIRS_OF_2_ARRAYS_H
#include "Debug.h"
/*
Leetcode:
We have two integer sequences A and B of the same non-zero length.
We are allowed to swap elements A[i] and B[i].
Note that both elements are in the same index position in their respective sequences.
At the end of some number of swaps, A and B are both strictly increasing.
(A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)
Given A and B, return the minimum number of swaps to make both sequences strictly increasing.
It is guaranteed that the given input always makes it possible.
Example:
Input: A = [1,3,5,4], B = [1,2,3,7]
Output: 1
Explanation:
Swap A[3] and B[3].  Then the sequences are:
A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
which are both strictly increasing.
 */
class SortByMinSwapPairsOf2Arrays
{
public:
    SortByMinSwapPairsOf2Arrays(){}

    int DP(const std::vector<int> & A, const std::vector<int> & B)
    {
        int N = A.size();
        std::vector<int> notSwap(N, N);//notSwap[i]: min swaps in [0:i] when not swap at (A[i], B[i])
        std::vector<int> swap(N, N);//swap[i]: min swaps in [0:i] when swap at (A[i], B[i])
        notSwap[0] = 0;
        swap[0] = 1;
        for (int i = 1; i < N; ++i)
        {
            if (A[i-1] < A[i] && B[i-1] < B[i])
            {
                notSwap[i] = notSwap[i-1];
                swap[i] = swap[i-1]+1;
            }
            if (A[i-1] < B[i] && B[i-1] < A[i])
            {
                notSwap[i] = std::min(notSwap[i], swap[i-1]);
                swap[i] = std::min(swap[i], notSwap[i-1]+1);
            }
        }

        std::cout << "notSwap:  " << Debug::ToStr1D<int>()(notSwap) << std::endl;
        std::cout << "swap:     " << Debug::ToStr1D<int>()(swap) << std::endl;
        std::cout << "SortByMinSwapPairsOf2Arrays DP for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << std::min(notSwap[N-1], swap[N-1]) << std::endl;

        return std::min(notSwap[N-1], swap[N-1]);
    }

    int DP2(const std::vector<int> & A, const std::vector<int> & B)
    {
        int N = A.size();
        std::vector<int> notSwap(N, N);//notSwap[i]: min swaps in [0:i] when not swap at (A[i], B[i])
        std::vector<int> swap(N, N);//swap[i]: min swaps in [0:i] when swap at (A[i], B[i])
        notSwap[0] = 0;
        swap[0] = 1;
        for (int i = 1; i < N; ++i)
        {
            if (!(A[i-1] < A[i]) || !(B[i-1] < B[i]))//must swap
            {
                notSwap[i] = swap[i-1];
                swap[i] = notSwap[i-1] + 1;
            }
            else if (!(A[i-1] < B[i]) || !(B[i-1] < A[i]))//cannot swap
            {
                notSwap[i] = notSwap[i-1];
                swap[i] = swap[i-1] + 1;//if already swapped at i-1, need to swap at i back, so +1
            }
            else//either swap or notSwap
            {
                notSwap[i] = std::min(notSwap[i-1], swap[i-1]);
                swap[i] = std::min(notSwap[i-1], swap[i-1]) + 1;
            }
        }

        std::cout << "notSwap:  " << Debug::ToStr1D<int>()(notSwap) << std::endl;
        std::cout << "swap:     " << Debug::ToStr1D<int>()(swap) << std::endl;
        std::cout << "SortByMinSwapPairsOf2Arrays DP2 for [" << Debug::ToStr1D<int>()(A) << "], [" << Debug::ToStr1D<int>()(B) << "]: " << std::min(notSwap[N-1], swap[N-1]) << std::endl;

        return std::min(notSwap[N-1], swap[N-1]);
    }
};
/*
notSwap:  0, 0, 0, 2
swap:     1, 1, 2, 1
SortByMinSwapPairsOf2Arrays DP for [1, 3, 5, 4], [1, 2, 3, 7]: 1
notSwap:  0, 0, 0, 2
swap:     1, 1, 2, 1
SortByMinSwapPairsOf2Arrays DP2 for [1, 3, 5, 4], [1, 2, 3, 7]: 1
notSwap:  0, 0, 1, 1, 1
swap:     1, 1, 1, 2, 2
SortByMinSwapPairsOf2Arrays DP for [0, 4, 4, 5, 9], [0, 1, 6, 8, 10]: 1
notSwap:  0, 0, 1, 1, 1
swap:     1, 1, 1, 2, 2
SortByMinSwapPairsOf2Arrays DP2 for [0, 4, 4, 5, 9], [0, 1, 6, 8, 10]: 1
 */
#endif
