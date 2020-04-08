#ifndef _LONGEST_VOWELS_REMOVE_AT_MOST_2_SUBSTRS_H
#define _LONGEST_VOWELS_REMOVE_AT_MOST_2_SUBSTRS_H
#include "Debug.h"
/*
Amazon OA
You are given with a string .
Your task is to remove atmost two substrings of any length from the given string such that the remaining string contains vowels('a','e','i','o','u') only.
Your aim is the maximise the length of the remaining string. Output the length of remaining string after removal of atmost two substrings.
NOTE: The answer may be 0, i.e. removing the entire string.
Sample Input
2
earthproblem
letsgosomewhere
Sample Output
3
2


3 cases:
1. keep leading vowels substr from begin, find the longest vowels substr from remaining string (equivalent to remove at most 2 substr in the remaining string)
2. keep trailing vowels substr from end, find the longest vowels substr from remaining string (equivalent to remove at most 2 substr in the remaining string)
3. keep both leading and trailing vowels substrs, find the longest vowels substr from middle string (equivalent to remove at most 2 substr in the middle string)
=>
 both case 1 and case 2 can converge to case 3


 */
class LongestVowelsRemoveAtMost2Substrs
{
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
public:
    LongestVowelsRemoveAtMost2Substrs(){}

    int Solve(const std::string & s)
    {
        int N = s.size();
        int res;
        int left = 0;
        while (left < N && isVowel(s[left]))
            ++left;
        int right = N-1;
        while (right >= 0 && isVowel(s[right]))
            --right;

        if (left > right)
            res = N;
        else
        {
            //now left <= right (at least 1 consonant in between [left,right])
            int maxLen = 0; //maxLen of vowels in [left,right]
            int cur = left;
            while (true)
            {
                int begin = cur;
                while (cur <= right && isVowel(s[cur]))
                    ++cur;
                if (cur - begin > maxLen)
                    maxLen = cur - begin;
                while (cur <= right && !isVowel(s[cur]))
                    ++cur;
                if (cur > right) break;
            }

            res = left + maxLen + (N-1-right);
        }

        std::cout << "LongestVowelsRemoveAtMost2Substrs for [" << s << "]: " << res << std::endl;
        return res;
    }
};
/*
LongestVowelsRemoveAtMost2Substrs for [aaabbbaabbabaaababaaa]: 9
LongestVowelsRemoveAtMost2Substrs for [bbaaaaabbaabb]: 5
LongestVowelsRemoveAtMost2Substrs for [aaaa]: 4
LongestVowelsRemoveAtMost2Substrs for [bbbb]: 0
 */
#endif
