/*AmazonOA*/
#ifndef _ALL_SUBSTR_SIZE_K_CONTAIN_DISTINCT_CHARS_H
#define _ALL_SUBSTR_SIZE_K_CONTAIN_DISTINCT_CHARS_H
#include "Debug.h"
/*
Michelle has created a word game for her students. The word game begins with Michelle writing a string and a number, K, on the board.
The students have to find the substrings of size K with K distinct characters.
Write an algorithm to help the students find the correct answer.
If the given string does not have K distinct characters then output an empty list.
Input
The input to the function/method consists of two arguments - inputStr, representing the number, K, written by the teacher on the board.
Output
Return distinct substrings of input string of size K with K distinct characters
Constraints
0 <= num <= 26
Examples
Input
inputStr = awaglknagawunagwkwagl
num = 4
Output:
{wagl, aglk, glkn, lkna, knag, gawu, awun, wuna, unag, nagw, agwk, kwag}
Note that "wagl" appeared twice, but should output only one


Given a string s (only lowercase chars) and a integer K, find all substrings in s with size K that contain distinct chars.
see also LongestSubstrWoRepeatChars.h, LongestSubArrWDistinctEntries.h
 */
class AllSubstrSizeKContainDistinctChars
{
public:
    AllSubstrSizeKContainDistinctChars(){}

    std::vector<std::string> SlideWindow1(const std::string & s, int K)
    {
        std::unordered_set<std::string> res;
        int N = s.size();
        std::vector<int> found(26, 0);
        int begin = 0;
        for (int i = 0; i < N; ++i)//i is end
        {
            if (found[s[i]-'a'])
            {
                while (s[begin] != s[i])
                {
                    found[s[begin]-'a'] = 0;
                    ++begin;
                }
                found[s[begin]-'a'] = 0;//exclude s[begin] == s[i]
                ++begin;
            }

            found[s[i]-'a'] = 1;//include s[i]
            //now s[begin:i] is a local longest substr containing distinct chars
            if (i-begin+1 >= K)
                res.insert(s.substr(i-K+1, K));
        }

        std::vector<std::string> res2(res.begin(), res.end());
        std::cout << "AllSubstrSizeKContainDistinctChars SlideWindow1 for \"" << s << "\", \"" << K << "\": " << Debug::ToStr1D<std::string>()(res2) << std::endl;
        return res2;
    }

    std::vector<std::string> SlideWindow2(const std::string & s, int K)
    {
        std::unordered_set<std::string> res;
        int N = s.size();
        std::unordered_map<char, int> lastIdx;//<char, lastIdx>
        int begin = 0;
        for (int i = 0; i < N; ++i)//i is end
        {
            auto itr = lastIdx.find(s[i]);
            if (itr == lastIdx.end())
                lastIdx.insert({s[i], i});
            else
            {
                if (itr->second >= begin)
                    begin = itr->second + 1;
                itr->second = i;
            }

            //now s[begin:i] is a local longest substr containing distinct chars
            if (i-begin+1 >= K)
                res.insert(s.substr(i-K+1, K));
        }

        std::vector<std::string> res2(res.begin(), res.end());
        std::cout << "AllSubstrSizeKContainDistinctChars SlideWindow2 for \"" << s << "\", \"" << K << "\": " << Debug::ToStr1D<std::string>()(res2) << std::endl;
        return res2;
    }
};
/*
AllSubstrSizeKContainDistinctChars SlideWindow1 for "awaglknagawunagwkwagl", "4": kwag, agwk, unag, nagw, wuna, lkna, awun, aglk, knag, gawu, glkn, wagl
AllSubstrSizeKContainDistinctChars SlideWindow2 for "awaglknagawunagwkwagl", "4": kwag, agwk, unag, nagw, wuna, lkna, awun, aglk, knag, gawu, glkn, wagl
 */
#endif
