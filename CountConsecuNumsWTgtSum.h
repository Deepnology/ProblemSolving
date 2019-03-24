#ifndef _COUNT_CONSECU_NUMS_W_TGT_SUM_H
#define _COUNT_CONSECU_NUMS_W_TGT_SUM_H
#include "Debug.h"
/*
Leetcode: Consecutive Numbers Sum
Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?
Example 1:
Input: 5
Output: 2
Explanation: 5 = 5 = 2 + 3
Example 2:
Input: 9
Output: 3
Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
Example 3:
Input: 15
Output: 4
Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 */
class CountConsecuNumsWTgtSum
{
public:
    CountConsecuNumsWTgtSum(){}
    ~CountConsecuNumsWTgtSum(){}

    int UseFormula(int N)
    {
        //arithmetic sequence summation
        //Sn = (a1 + an) * n / 2
        //   = a1 * n + n * (n - 1) * d / 2
        //so
        //a1 * n = Sn - n * (n - 1) * d / 2, where d=1
        //a1 = Sn / n - (n - 1) / 2 > 0
        //n * (n - 1) < 2 * Sn
        int res = 0;
        for (int n = 1; n*(n-1) < 2*N; ++n) //enumerate n in [1:sqrt(N)]: O(sqrt(N)) time
        {
            int a1n = N - n*(n-1)/2; //a1n means a1*n
            //now a1n must be > 0
            if (a1n % n == 0) //means a1 can be a valid integer
                ++res;
        }
        std::cout << "CountConsecuNumsWTgtSum UseFormula for " << N << ": " << res << std::endl;
        return res;
    }
};
/*
CountConsecuNumsWTgtSum UseFormula for 15: 4
 */
#endif
