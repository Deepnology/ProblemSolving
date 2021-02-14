#ifndef _MAX_NUM_OF_VOWELS_IN_SUBSTR_LEN_K_H
#define _MAX_NUM_OF_VOWELS_IN_SUBSTR_LEN_K_H
#include "Debug.h"
/*
Leetcode: Maximum Number of Vowels in a Substring of Given Length
Given a string s and an integer k.
Return the maximum number of vowel letters in any substring of s with length k.
Vowel letters in English are (a, e, i, o, u).
Example 1:
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
Example 2:
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
Example 3:
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.
 */
class MaxNumOfVowelsInSubstrLenK
{
public:
    int SlidingWindow(std::string s, int k)
    {
        std::unordered_set<char> vol({'a','e','i','o','u'});
        int res = 0;
        int N = s.size();
        int begin = 0;
        int volCount = 0;
        for (int i = 0; i < N; ++i)
        {
            if (vol.count(s[i]))
                ++volCount;
            if (i-begin+1>=k)
            {
                res = std::max(res, volCount);
                if (vol.count(s[begin]))
                    --volCount;
                ++begin;
            }
        }
        return res;
    }
};
#endif
