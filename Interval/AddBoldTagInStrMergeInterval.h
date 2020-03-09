#ifndef _ADD_BOLD_TAG_IN_STR_MERGE_INTERVAL_H
#define _ADD_BOLD_TAG_IN_STR_MERGE_INTERVAL_H
#include "Debug.h"
/*
Leetcode: Add Bold Tag In String
Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict.
If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag.
Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
Example 1:
Input:
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"
Example 2:
Input:
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"
 */
class AddBoldTagInStrMergeInterval
{
public:
    AddBoldTagInStrMergeInterval(){}

    std::string MergeInterval(std::string s, const std::vector<std::string> & dict)
    {
        std::string before(s);
        int N = s.size();
        std::vector<std::vector<int>> intervals;
        for (const auto & word : dict)
        {
            size_t i = 0;
            while ((i = s.find(word, i)) != std::string::npos)
            {
                intervals.push_back({(int)i,(int)(i+word.size()-1)});
                ++i;
            }
        }
        if (intervals.empty()) return s;
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int> & a, const std::vector<int> & b)
        {
            return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1];
        });
        std::cout << "Intervals: " << Debug::ToStr1D<int>()(intervals) << std::endl;

        std::vector<std::vector<int>> merged;
        std::vector<int> pre = intervals[0];
        int M = intervals.size();
        for (int i = 1; i < M; ++i)
        {
            if (pre[1] >= intervals[i][0] || pre[1]+1 == intervals[i][0])//consecutive nums must be merged !
            {
                pre[0] = std::min(pre[0], intervals[i][0]);
                pre[1] = std::max(pre[1], intervals[i][1]);
            }
            else
            {
                merged.push_back(pre);
                pre = intervals[i];
            }
        }
        merged.push_back(pre);
        M = merged.size();
        for (int i = M-1; i >= 0; --i)//insert from back of s
        {
            s.insert(merged[i][1]+1, "</b>");
            s.insert(merged[i][0], "<b>");
        }

        std::cout << "Intervals: " << Debug::ToStr1D<int>()(merged) << std::endl;
        std::cout << "AddBoldTagInStrMergeInterval for \"" << before << "\", [" << Debug::ToStr1D<std::string>()(dict) << "]: " << s << std::endl;
        return s;
    }
};
/*
Intervals: [0,2], [1,3], [4,5]
Intervals: [0,5]
AddBoldTagInStrMergeInterval for "aaabbcc", [aaa, aab, bc]: <b>aaabbc</b>c
 */
#endif
