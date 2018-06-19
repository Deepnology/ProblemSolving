#ifndef _PARTITION_INTO_FIBONACCI_SEQ_H
#define _PARTITION_INTO_FIBONACCI_SEQ_H
#include "Debug.h"
/*
Leetcode: Split Array into Fibonacci Sequence
Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].
Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:
0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
F.length >= 3;
and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.
Example 1:
Input: "123456579"
Output: [123,456,579]
Example 2:
Input: "11235813"
Output: [1,1,2,3,5,8,13]
Example 3:
Input: "112358130"
Output: []
Explanation: The task is impossible.
Example 4:
Input: "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
Example 5:
Input: "1101111"
Output: [110, 1, 111]
Explanation: The output [11, 0, 11, 11] would also be accepted.


Time complexity is O(n!) (n factorial)
First call: Branch n times worst case
Second call: Branch n-1 times worst case
Third call: Branch n-2 times worst case
etc..
In total, we do this n times worst case (depth of n calls).
So it's n * (n-1) * (n-2) * (n-3) * ... * 1= n!
 */
class PartitionIntoFibonacciSeq
{
public:
    PartitionIntoFibonacciSeq(){}

    std::vector<int> Recur_FindAnyOne(std::string S)
    {
        std::vector<int> path;
        recur(S, 0, path);
        std::cout << "PartitionIntoFibonacciSeq FindAnyOne for [" << S << "]: " << Debug::ToStr1D<int>()(path) << std::endl;
        return path;
    }
private:
    bool recur(const std::string & S, int cur, std::vector<int> & path)
    {
        int N = S.size();
        if (cur == N && path.size() >= 3)
            return true;

        for (int i = cur; i < N; ++i)
        {
            if (S[cur] == '0' && i > cur) break;
            long long curNum = stoll(S.substr(cur, i-cur+1));
            if (curNum > INT_MAX) break;
            if (path.size() <= 1 || curNum == (long long)path[path.size()-1] + (long long)path[path.size()-2])
            {
                path.push_back(curNum);
                if (recur(S, i+1, path)) return true;
                path.pop_back();
            }
        }
        return false;
    }

public:
    std::vector<std::vector<int>> Recur_FindAll(std::string S)
    {
        std::vector<int> path;
        std::vector<std::vector<int>> res;
        recur(S, 0, path, res);
        std::cout << "PartitionIntoFibonacciSeq FindAll for [" << S << "]: " << std::endl;
        Debug::Print2D<int>()(res, false);
        return res;
    }
private:
    void recur(const std::string & S, int cur, std::vector<int> & path, std::vector<std::vector<int>> & res)
    {
        int N = S.size();
        if (cur == N)
        {
            if (path.size() >= 3)
                res.push_back(path);
            return;
        }

        for (int i = cur; i < N; ++i)
        {
            if (S[cur] == '0' && i > cur) break;
            long long curNum = stoll(S.substr(cur, i-cur+1));
            if (curNum > INT_MAX) break;
            if (path.size() <= 1 || curNum == (long long)path[path.size()-1] + (long long)path[path.size()-2])
            {
                path.push_back(curNum);
                recur(S, i+1, path, res);
                path.pop_back();
            }
        }
    }
};
/*
PartitionIntoFibonacciSeq FindAnyOne for [1101111]: 11, 0, 11, 11
PartitionIntoFibonacciSeq FindAll for [1101111]:
[rY][cX]
Row#0	= 11, 0, 11, 11
Row#1	= 110, 1, 111,
 */
#endif
