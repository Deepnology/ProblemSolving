#ifndef _BREAK_PALINDROME_BY_REPLACE_A_CHAR_H
#define _BREAK_PALINDROME_BY_REPLACE_A_CHAR_H
#include "Debug.h"
/*
Leetcode: Break a Palindrome
Given a palindromic string palindrome, replace exactly one character by any lowercase English letter
 so that the string becomes the lexicographically smallest possible string that isn't a palindrome.
After doing so, return the final string.  If there is no way to do so, return the empty string.
Example 1:
Input: palindrome = "abccba"
Output: "aaccba"
Example 2:
Input: palindrome = "a"
Output: ""
 */
class BreakPalindromeByReplaceAChar
{
public:
    std::string breakPalindrome(std::string palindrome)
    {
        int N = palindrome.size();
        if (N <= 1) return "";
        for (int i = 0; i < N/2; ++i)
        {
            if (palindrome[i] != 'a')
            {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        palindrome[N-1] = 'b';//all 'a'
        return palindrome;
    }
};
#endif
