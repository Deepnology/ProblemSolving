#ifndef _GCD_OF_2_STRINGS_H
#define _GCD_OF_2_STRINGS_H
#include "Debug.h"
/*
Leetcode: Greatest Common Divisor of Strings
For two strings s and t, we say "t divides s" if and only if s = t + ... + t  (t concatenated with itself 1 or more times)
Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
Example 1:
Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"
Example 2:
Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"
Example 3:
Input: str1 = "LEET", str2 = "CODE"
Output: ""
Example 4:
Input: str1 = "ABCDEF", str2 = "ABC"
Output: ""
 */
class GCDof2Strings
{
public:
    std::string Solve1(std::string s1, std::string s2)
    {
        return (s1+s2 == s2+s1) ? s1.substr(0, std::gcd(s1.size(),s2.size())) : "";
    }

    std::string Solve2(std::string s1, std::string s2)
    {
        return gcdRecur(s1, s2);
    }
private:
    std::string gcdRecur(std::string s1, std::string s2)
    {
        if (s1.size() > s2.size())
            return gcdRecur(s2, s1);
        if (s1.empty()) return s2;
        if (s2.substr(0, s1.size()) != s1) return "";
        return gcdRecur(s1, s2.substr(s1.size())); //subtract s1 from s2 (with same s1 in the front) recursively
    }
};
#endif
