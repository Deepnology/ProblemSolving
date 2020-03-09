#ifndef _CLOSEST_PALINDROME_NUM_H
#define _CLOSEST_PALINDROME_NUM_H
#include "Debug.h"
/*
Leetcode: Find the Closest Palindrome
Given an integer n, find the closest integer (not including itself), which is a palindrome.
The 'closest' is defined as absolute difference minimized between two integers.
Example 1:
Input: "123"
Output: "121"
Note:
The input n is a positive integer represented by string, whose length will not exceed 18.
If there is a tie, return the smaller one as answer.

see also NextPrePalindromeNum.h
 */
class ClosestPalindromeNum
{
public:
    ClosestPalindromeNum(){}

    std::string Check7Candidates(std::string s)
    {
        int len = s.size();
        if (len == 1)
            return std::to_string(stol(s)-1);

        //4 candidnates: ex, len=2: 101, 99, 11, 9
        std::vector<long> candidates({(long)pow(10,len)+1, (long)pow(10,len)-1, (long)pow(10,len-1)+1, (long)pow(10,len-1)-1});

        int halfLen = (len+1)/2;
        long prefix = stol(s.substr(0,halfLen));//for odd len: include middle
        std::vector<long> val({prefix-1,prefix,prefix+1});//3 other candidnates: (prefix-1)+reverse(prefix-1), prefix+reverse(prefix), (prefix+1)+reverse(prefix+1)
        for (auto v : val)
        {
            std::string postfix = std::to_string(v);
            if (len % 2 == 1)
                postfix.pop_back();//for odd len: exclude middle
            std::reverse(postfix.begin(), postfix.end());
            candidates.push_back(stol(std::to_string(v)+postfix));
        }

        long res = LONG_MAX;
        int diff = INT_MAX;
        long original = stol(s);
        for (auto num : candidates)//7 candidates in total
        {
            if (num == original) continue;
            if (labs(num-original) < diff || (labs(num-original) == diff && num < res))
            {
                diff = labs(num-original);
                res = num;
            }
        }

        std::cout << "ClosestPalindromeNum Check7Candidates for " << s << ": " << res << std::endl;
        return std::to_string(res);
    }
};
/*
ClosestPalindromeNum Check7Candidates for 99999: 100001
ClosestPalindromeNum Check7Candidates for 12921: 12821
ClosestPalindromeNum Check7Candidates for 89999: 89998
ClosestPalindromeNum Check7Candidates for 948797859: 948797849
 */
#endif
