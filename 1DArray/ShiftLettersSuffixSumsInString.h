#ifndef _SHIFT_LETTERS_SUFFIX_SUMS_IN_STRING_H
#define _SHIFT_LETTERS_SUFFIX_SUMS_IN_STRING_H
#include "Debug.h"
/*
Leetcode: Shifting Letters
We have a string S of lowercase letters, and an integer array shifts.
Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a').
For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.
Return the final string after all such shifts to S are applied.
Example 1:
Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation:
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.
 */
class ShiftLettersSuffixSumsInString
{
public:
    std::string Solve(std::string S, std::vector<int> & shifts)
    {
        int N = shifts.size();
        std::vector<int> suffixSums(N, 0);
        for (int i = N-1; i >= 0; --i)
        {
            suffixSums[i] += shifts[i] + (i<N-1? suffixSums[i+1] : 0);
            suffixSums[i] %= 26;
        }
        for (int i = 0; i < N; ++i)
            S[i] = ((S[i]-'a') + suffixSums[i])%26 + 'a';
        return S;
    }
};
#endif
