#ifndef _COUNT_MAX_FREQ_SUBSTR_SIZE_RANGE_MAX_DISTINCT_CHAR_H
#define _COUNT_MAX_FREQ_SUBSTR_SIZE_RANGE_MAX_DISTINCT_CHAR_H
#include "Debug.h"
/*
Leetcode: Maximum Number of Occurrences of a Substring
Given a string s, return the maximum number of ocurrences of any substring under the following rules:
The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.
Example 1:
Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 ocurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
Example 2:
Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.
Example 3:
Input: s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
Output: 3
Example 4:
Input: s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
Output: 0
Constraints:
1 <= s.length <= 10^5
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s only contains lowercase English letters.
 */
class CountMaxFreqSubstr_SizeRange_MaxDistinctChar
{
public:
    int SlideWindow(std::string s, int maxLetters, int minSize, int maxSize)
    {
        //since we just need to find "max" num of occurrences of a substring, just need to consider minSize and ignore the maxSize
        int begin = 0;
        int res = 0;
        std::unordered_map<char, int> charCount; //char count in window
        std::unordered_map<std::string, int> substrCount; //total number of occurrences of each substr
        for (auto i = 0; i < s.size(); ++i)
        {
            ++charCount[s[i]];
            if (i-begin+1 > minSize)
            {
                if (--charCount[s[begin]] == 0)
                    charCount.erase(s[begin]);
                ++begin;
            }
            if (i-begin+1 == minSize && charCount.size() <= maxLetters)
                res = std::max(res, ++substrCount[s.substr(begin, i-begin+1)]);
        }
        return res;
    }
};
#endif
