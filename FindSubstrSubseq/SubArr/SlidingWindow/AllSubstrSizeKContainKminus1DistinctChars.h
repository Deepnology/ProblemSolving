#ifndef _ALL_SUBSTR_SIZE_K_CONTAIN_K_MINUS_1_DISTINCT_CHARS_H
#define _ALL_SUBSTR_SIZE_K_CONTAIN_K_MINUS_1_DISTINCT_CHARS_H
#include "Debug.h"
/*
Amazon OA
As part of Day 1 challenge, your manager has created a word game for you and your teammates to play.
The word game begins with your manager writing a string, and a number K on the board.
You and your teammates must find a substring of size K such that there is exactly one character that is repeated once.
In other words, there should be K - 1 distinct characters in the substring.
Write an algorithm to help your teammates find the correct answer. If no such substring can be found, return an empty list;
If multiple such substrings exit, return all of them, without repetitions. The order in which the substrings are returned does not matter.
Input: it has two arguments:
inputString: representing the string written by the manager.
num: an integer representing the number K, written by the manager on the board.
Output:
Return a list of all substrings of inputString with K characters, that have K - 1 distinct character, i.e. exactly one character is repeated,
or an empty list if no such substring exists in inputString. The order in which the substrings are returned does not matter.
Constraints:
The input integer can only be greater than or equal to 0 and less than or equal to 26 (0 <= num <= 26).
The input string consists of only lowercase alphabetic characters.
Example 1:
Input:
inputString = awaglk
num = 4
Output:
[awag]
Explanation:
The substrings are {awag, wagl, aglk}
The answer is awag as it has 3 distinct characters in a string of size 4, and only one character is repeated twice.
Example 2:
Input:
inputString = democracy
num = 5
Output:
[ocrac, cracy]
Example 3:
Input:
inputString = wawaglknagagwunagkwkwagl
num = 4
Output:
[awag, naga, gagw, gkwk, wkwa]
 */
class AllSubstrSizeKContainKminus1DistinctChars
{
public:

    std::vector<std::string> SlideWindow(const std::string & s, int k)
    {
        std::unordered_map<char,int> charCount;
        int N = s.size();
        std::vector<std::string> res;
        int begin = 0;
        for (int i = 0; i < N; ++i)
        {
            charCount[s[i]]++;
            if (i - begin + 1 >= k)//window size == k
            {
                if (charCount.size() == k-1)
                    res.push_back(s.substr(begin, k));
                //advance begin
                charCount[s[begin]]--;
                if (charCount[s[begin]] == 0)
                    charCount.erase(s[begin]);
                ++begin;
            }
        }
        std::cout << "AllSubstrSizeKContainKminus1DistinctChars SlideWindow for " << s << ", k=" << k << ": " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }
};
/*
AllSubstrSizeKContainKminus1DistinctChars SlideWindow for awaglk, k=4: awag
AllSubstrSizeKContainKminus1DistinctChars SlideWindow for democracy, k=5: ocrac, cracy
AllSubstrSizeKContainKminus1DistinctChars SlideWindow for wawaglknagagwunagkwkwagl, k=4: awag, naga, gagw, gkwk, wkwa
 */
#endif
