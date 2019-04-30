#ifndef _COUNT_NUMS_W_SAME_DIGIT_DIFF_H
#define _COUNT_NUMS_W_SAME_DIGIT_DIFF_H
#include "Debug.h"
/*
Leetcode: Numbers With Same Consecutive Differences
Return all non-negative integers of length N such that the absolute difference between every two consecutive digits is K.
Note that every number in the answer must not have leading zeros except for the number 0 itself.
For example, 01 has one leading zero and is invalid, but 0 is valid.
You may return the answer in any order.
Example 1:
Input: N = 3, K = 7
Output: [181,292,707,818,929]
Explanation: Note that 070 is not a valid number, because it has leading zeroes.
Example 2:
Input: N = 2, K = 1
Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
Note:
1 <= N <= 9
0 <= K <= 9
 */
class CountNumsWSameDigitDiff
{
public:
    CountNumsWSameDigitDiff(){}

    std::vector<int> BFS(int N, int K) //N: numDigits, K: diff
    {
        int numDigits = N;

        std::queue<long> que({1,2,3,4,5,6,7,8,9});
        if (N == 1) que.push(0);
        while (N-- > 1)//loop for numDigits times
        {
            int count = que.size();
            while (count -- > 0)//loop for all same numDigits nums
            {
                long num = que.front();
                que.pop();
                int nxtGreaterDigit = num % 10 + K;
                int nxtLessDigit = num % 10 - K;
                if (nxtGreaterDigit <= 9)
                    que.push(num*10+nxtGreaterDigit);
                if (nxtLessDigit >= 0 && nxtLessDigit != nxtGreaterDigit)
                    que.push(num*10+nxtLessDigit);
            }
        }
        std::vector<int> res;
        while (!que.empty())
        {
            res.push_back(que.front());
            que.pop();
        }
        std::cout << "CountNumsWSameDigitDiff BFS for numDigits=" << numDigits << ", diff=" << K << ": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
CountNumsWSameDigitDiff BFS for numDigits=2, diff=1: 12, 10, 23, 21, 34, 32, 45, 43, 56, 54, 67, 65, 78, 76, 89, 87, 98
 */
#endif
