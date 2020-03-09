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
        //use formula: O(sqrt(N)) time
        //(a1+an)*n/2 = N
        //(a1+(a1+len-1))*len/2 = N
        //2*a1+len-1 = 2*N/len
        //2*a1 = 2*N/len-len+1 ..................(1)
        //a1 = ((2*N-len*len)/len + 1) / 2 ......(2)
        int res = 0;
        for (int len = 1; len*len <= 2*N; ++len) //from (2)
        {
            if (2*N % len == 0) //from (1)
            {
                if ((2*N/len - len + 1) % 2 == 0) // from (1)
                {
                    int a1 = (2*N/len-len+1)/2;
                    int aLen = a1+len-1;
                    std::cout << "[" << a1 << "," << aLen << "]" << std::endl;
                    ++res;
                }
            }
        }
        std::cout << "CountConsecuNumsWTgtSum UseFormula for " << N << ": " << res << std::endl;
        return res;
    }

    int BruteForce(int N)
    {
        //brute force: O(N^2) time
        int res = 0;
        for (int i = 1; i <= N; ++i)
        {
            int sum = 0;
            int cur = i;
            while (sum+cur <= N)
            {
                sum += cur;
                ++cur;
            }
            if (sum == N)
                ++res;
        }
        std::cout << "CountConsecuNumsWTgtSum BruteForce for " << N << ": " << res << std::endl;
        return res;
    }
};
/*
CountConsecuNumsWTgtSum BruteForce for 15: 4
[15,15]
[7,8]
[4,6]
[1,5]
CountConsecuNumsWTgtSum UseFormula for 15: 4
 */
#endif
