#ifndef _BUDDY_STRINGS_SWAP_A_PAIR_MAKE_EQUAL_H
#define _BUDDY_STRINGS_SWAP_A_PAIR_MAKE_EQUAL_H
#include "Debug.h"
/*
Leetcode: Buddy Strings
Given two strings A and B of lowercase letters, return true if you can swap two letters in A so the result is equal to B, otherwise, return false.
Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at A[i] and A[j]. For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
 */
class BuddyStringsSwapAPairMakeEqual
{
public:
    bool Validate(std::string A, std::string B)
    {
        if (A.size() != B.size()) return false;
        int N = A.size();
        int charCount = std::unordered_set<char>(A.begin(), A.end()).size();
        if (A == B && charCount < N) return true;//same strings, at least one repeat
        std::vector<int> idx;
        for (int i = 0; i < N; ++i)
        {
            if (A[i] != B[i])
                idx.push_back(i);
            if (idx.size() > 2) return false;
        }
        return idx.size()==2 && A[idx[0]]==B[idx[1]] && A[idx[1]]==B[idx[0]];
    }
};
#endif
