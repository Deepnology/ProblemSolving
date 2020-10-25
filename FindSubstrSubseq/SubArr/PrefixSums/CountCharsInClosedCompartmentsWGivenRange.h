#ifndef _COUNT_CHARS_IN_CLOSED_COMPARTMENTS_W_GIVEN_RANGE_H
#define _COUNT_CHARS_IN_CLOSED_COMPARTMENTS_W_GIVEN_RANGE_H
#include "Debug.h"
/*
Amazon OA
Items in Containers
Amazon would like to know how much inventory exists in their closed inventory compartments. Given a string s
consisting of items as "*" and closed compartments as an open and close "|", an array of starting indices
startIndices, and an array of ending indices endIndices, determine the number of items in closed compartments
within the substring between the two indices, inclusive.
An item is represented as an asterisk ('*' = ascii decimal 42)
A compartment is represented as a pair of pipes that may or may not have items between them ('|' = ascii decimal 124).
Example
s = '|**|*|*'
startIndices = [1, 1]
endIndices = [5, 6]
The string has a total of 2 closed compartments, one with 2 items and one with 1 item. For the first pair of
indices, (1, 5), the substring is '|**|*'. There are 2 items in a compartment.
For the second pair of indices, (1, 6), the substring is '|**|*|' and there are 2 + 1 = 3 items in compartments.
Both of the answers are returned in an array, [2, 3].
Function Description .
Complete the numberOfItems function in the editor below. The function must return an integer array that contains
the results for each of the startIndices[i] and endIndices[i] pairs.
numberOfItems has three parameters:
s: A string to evaluate
startIndices: An integer array, the starting indices.
endIndices: An integer array, the ending indices.
Constraints
1 <= m, n <= 105
1 <= startIndices[i] <= endIndices[i] <= n
Each character of s is either '*' or '|'
Input Format For Custom Testing
The first line contains a string, S.
The next line contains an integer, n, the number of elements in startIndices.
Each line i of the n subsequent lines (where 1 <= i <= n) contains an integer, startIndices[i].
The next line repeats the integer, n, the number of elements in endIndices.
Each line i of the n subsequent lines (where 1 <= i <= n) contains an integer, endIndices[i].
Sample Case 0
Sample Input For Custom Testing
STDIN Function
*|*| -> s = "*|*|"
1 -> startIndices[] size n = 1
1 -> startIndices = 1
1 -> endIndices[] size n = 1
3 -> endIndices = 3
** Sample Output**
0
Explanation
s = *|*|
n = 1
startIndices = [1]
n = 1
startIndices = [3]
The substring from index = 1 to index = 3 is '|'. There is no compartments in this string.
Sample Case 1
Sample Input For Custom Testing
STDIN Function
*|*|*| -> s = "*|*|*|"
1 -> startIndices[] size n = 1
1 -> startIndices = 1
1 -> endIndices[] size n = 1
6 -> endIndices = 6
Sample Output
2
Explanation
s = '*|*|*|'
n = 1
startIndices = [1]
n = 1
startIndices = [1]
The substring from index = 1 to index = 6 is '||*|'. There are two compartments in this string at (index = 2,
index = 4) and (index = 4, index = 6). There are 2 items between these compartments.
 */
class CountCharsInClosedCompartmentsWGivenRange
{
public:
    std::vector<int> UsePrefixSumMap(const std::string & s, const std::vector<int> & starts, const std::vector<int> & ends)//note: starts, ends are 1-based indices
    {
        std::map<int, int> idxCount; //<pipeIdx, prefixSum> where pipeIdx are sorted in incr order
        int prefixSum = 0;
        for (auto i = 0; i < s.size(); ++i)
        {
            if (s[i] == '*') ++prefixSum;
            else if (s[i] == '|') idxCount.insert({i, prefixSum});
        }
        std::vector<int> res;
        for (auto i = 0; i < starts.size(); ++i)
        {
            auto lb = idxCount.lower_bound(starts[i]-1);
            auto ub = std::prev(idxCount.upper_bound((ends[i]-1)));
            res.push_back(ub->second-lb->second);
        }

        std::cout << "CountCharsInClosedCompartmentsWGivenRange for \"" << s << "\", starts=[" << Debug::ToStr1D<int>()(starts) << "], ends=[" << Debug::ToStr1D<int>()(ends) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
CountCharsInClosedCompartmentsWGivenRange for "|**|*|*", starts=[1, 1], ends=[5, 6]: 2, 3
CountCharsInClosedCompartmentsWGivenRange for "*|*|", starts=[1], ends=[3]: 0
CountCharsInClosedCompartmentsWGivenRange for "*|*|*|", starts=[1], ends=[6]: 2
 */
#endif
