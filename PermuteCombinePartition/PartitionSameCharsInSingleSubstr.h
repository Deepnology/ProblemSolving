/*AmazonOA*/
#ifndef _PARTITION_SAME_CHARS_IN_SINGLE_SUBSTR_H
#define _PARTITION_SAME_CHARS_IN_SINGLE_SUBSTR_H
#include "Debug.h"
/*
Leetcode: Partition Labels
A string S of lowercase letters is given.
We want to partition this string into as many parts as possible so that each letter appears in at most one part
, and return a list of integers representing the size of these parts.
Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 */
class PartitionSameCharsInSingleSubstr
{
public:
    PartitionSameCharsInSingleSubstr(){}

    std::vector<int> TwoScanHashMap(const std::string & S)
    {
        int N = S.size();
        std::unordered_map<char, int> lastIdx;//<char, lastIdx>
        for (int i = 0; i < N; ++i)
            lastIdx[S[i]] = i;
        int begin = 0;
        int curMaxLastIdx = 0;
        std::vector<int> res;
        for (int i = 0; i < N; ++i)//i is end
        {
            curMaxLastIdx = std::max(curMaxLastIdx, lastIdx[S[i]]);
            if (curMaxLastIdx == i)
            {
                res.push_back(i-begin+1);
                begin = i+1;
            }
        }

        std::cout << "PartitionSameCharsInSingleSubstr TwoScanHashMap for \"" << S << "\": " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
PartitionSameCharsInSingleSubstr TwoScanHashMap for "ababcbacadefegdehijhklij": 9, 7, 8
 */
#endif
