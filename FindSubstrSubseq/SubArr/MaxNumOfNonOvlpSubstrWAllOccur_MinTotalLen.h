#ifndef _MAX_NUM_OF_NON_OVLP_SUBSTR_W_ALL_OCCUR_MIN_TOTAL_LEN_H
#define _MAX_NUM_OF_NON_OVLP_SUBSTR_W_ALL_OCCUR_MIN_TOTAL_LEN_H
#include "Debug.h"
/*
Leetcode: Maximum Number of Non-Overlapping Substrings
Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
The substrings do not overlap, that is for any two substrings s[i..j] and s[k..l], either j < k or i > l is true.
A substring that contains a certain character c must also contain all occurrences of c.
Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
Notice that you can return the substrings in any order.
Example 1:
Input: s = "adefaddaccc"
Output: ["e","f","ccc"]
Explanation: The following are all the possible substrings that meet the conditions:
[
  "adefaddaccc"
  "adefadda",
  "ef",
  "e",
  "f",
  "ccc",
]
If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
Example 2:
Input: s = "abbaccd"
Output: ["d","bb","cc"]
Explanation: Notice that while the set of substrings ["d","abba","cc"] also has length 3, it's considered incorrect since it has larger total length.

see also PartitionSameCharsInSingleSubstr.h
 */
class MaxNumOfNonOvlpSubstrWAllOccur_MinTotalLen
{
public:
    std::vector<std::string> UseIntervalScheduling(std::string s)
    {
        //1. find all 26 substrs that contain all occurrences of each char: O(N) time
        //2. extend each substr to left and right such that it cover the max ranges of all chars: O(26*N) time
        //3. then it will become the interval scheduling problem: O(26*log26) time

        std::unordered_map<char, std::pair<int,int>> idxP;//<char,<fstIdx,lstIdx>>
        for (auto i = 0; i < s.size(); ++i)
        {
            if (!idxP.count(s[i]))
                idxP[s[i]] = {i, i};
            else
                idxP[s[i]].second = i;
        }
        std::vector<std::pair<int,int>> v;
        for (auto p : idxP)
        {
            auto begin = p.second.first;
            auto end = p.second.second;
            for (auto i = begin; i <= end; ++i)
            {
                begin = std::min(begin, idxP[s[i]].first);
                end = std::max(end, idxP[s[i]].second);//update end during iteration
            }
            if (begin == p.second.first) //record interval if begin doesn't change
            {
                //if begin moves to left, then another interval will cover this
                v.push_back({begin, end});
            }
            /*
            ex: "cabbaacbbc"
            a=[1:5], b=[2:8], c=[0:9]
            when extending end of a, first update end to b's end, then update end to c's end.
            but a's begin extends to left such that another interval will cover it.
            when extending end of b, update end to c's end.
            but b's begin extends to left such that another interval will cover it.
            ex: "cbbcaabbac" (reversed)
            a=[4:8], b=[1:7], c=[0:9]
            */
        }

        std::sort(v.begin(), v.end(), [](const std::pair<int,int> & a, const std::pair<int,int> & b)->bool
        {
            //for equal ends, place smaller begin in left such that longer interval will be considered first
            return a.second == b.second ? a.first < b.first : a.second < b.second;
        });
        std::vector<std::string> res;
        res.push_back(s.substr(v[0].first, v[0].second-v[0].first+1));
        int pre = 0;
        for (auto i = 1; i < v.size(); ++i)
        {
            if (v[pre].second < v[i].first)
            {
                res.push_back(s.substr(v[i].first, v[i].second-v[i].first+1));
                pre = i;
            }
        }
        return res;
};
#endif
