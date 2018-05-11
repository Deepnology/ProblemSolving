#ifndef _LONGEST_WORD_IN_DICT_THRU_DELETING_H
#define _LONGEST_WORD_IN_DICT_THRU_DELETING_H
#include "Debug.h"
/*
Leetcode: Longest Word In Dictionary Through Deleting
Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string.
If there are more than one possible results, return the longest word with the smallest lexicographical order.
If there is no possible result, return the empty string.
Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]
Output:
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]
Output:
"a"
 */
class LongestWordInDictThruDeleting
{
public:
    LongestWordInDictThruDeleting(){}

    std::string Solve(std::string s, const std::vector<std::string> & dict)
    {
        std::string res;
        for (const auto & w : dict)
        {
            int i = 0;
            int j = 0;
            while (i < s.size() && j < w.size())
            {
                if (s[i] == w[j])
                {
                    ++j;
                }
                ++i;
            }
            if (j == w.size())//means w can be formed by deleting some chars from s
            {
                if (res.size() < w.size() || (res.size() == w.size() && res > w))
                    res = w;
            }
        }

        std::cout << "LongestWordInDictThruDeleting for \"" << s << "\", from [" << Debug::ToStr1D<std::string>()(dict) << "]: " << res << std::endl;
        return res;
    }
};
/*
LongestWordInDictThruDeleting for "abpcplea", from [ale, apple, monkey, plea]: apple
 */
#endif
